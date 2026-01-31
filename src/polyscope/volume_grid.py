from typing import Any, Callable, Literal, overload

import polyscope_bindings as psb

from polyscope.core import glm3, glm3u
from polyscope.enums import to_enum, from_enum
from polyscope.structure import Structure
from polyscope.common import process_quantity_args, process_scalar_args, process_color_args, process_vector_args, check_all_args_processed, check_and_pop_arg

import numpy as np
from numpy.typing import NDArray, ArrayLike

def process_volume_grid_scalar_args(structure: "VolumeGrid", quantity: Any, scalar_args: dict[str, Any], defined_on: str) -> None:

    val = check_and_pop_arg(scalar_args, 'enable_gridcube_viz')
    if val is not None:
        quantity.set_gridcube_viz_enabled(val)

    if defined_on == 'nodes':

        val = check_and_pop_arg(scalar_args, 'enable_isosurface_viz')
        if val is not None:
            quantity.set_isosurface_viz_enabled(val)

        val = check_and_pop_arg(scalar_args, 'isosurface_level')
        if val is not None:
            quantity.set_isosurface_level(val)

        val = check_and_pop_arg(scalar_args, 'isosurface_color')
        if val is not None:
            quantity.set_isosurface_color(glm3(val))

        val = check_and_pop_arg(scalar_args, 'slice_planes_affect_isosurface')
        if val is not None:
            quantity.set_slice_planes_affect_isosurface(val)

        val = check_and_pop_arg(scalar_args, 'register_isosurface_as_mesh_with_name')
        if val is not None:
            quantity.register_isosurface_as_mesh_with_name(val)
        

class VolumeGrid(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope
    bound_instance: psb.VolumeGrid

    @overload
    def __init__(self, name: str, node_dims: ArrayLike, bound_low: ArrayLike, bound_high: ArrayLike) -> None: ...

    @overload
    def __init__(self, *, instance: psb.VolumeGrid) -> None: ...

    # End users should not call this constrctor, use register_volume_grid instead
    def __init__(self,
                 name: str | None = None,
                 node_dims: ArrayLike | None = None,
                 bound_low: ArrayLike | None = None,
                 bound_high: ArrayLike | None = None,
                 instance: psb.VolumeGrid | None = None
            ) -> None:

        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance

            assert name is not None
            assert node_dims is not None
            assert bound_low is not None
            assert bound_high is not None

            self.bound_instance = psb.register_volume_grid(name,
                                                           glm3u(node_dims),
                                                           glm3(bound_low),
                                                           glm3(bound_high)
                                                          )


    def n_nodes(self) -> int:
        return self.bound_instance.n_nodes()
    def n_cells(self) -> int:
        return self.bound_instance.n_cells()
    def grid_spacing(self) -> NDArray:
        return self.bound_instance.grid_spacing()
    def get_grid_node_dim(self) -> NDArray:
        return self.bound_instance.get_grid_node_dim()
    def get_grid_cell_dim(self) -> NDArray:
        return self.bound_instance.get_grid_cell_dim()
    def get_bound_min(self) -> NDArray:
        return self.bound_instance.get_bound_min()
    def get_bound_max(self) -> NDArray:
        return self.bound_instance.get_bound_max()

    ## Structure management

    ## Options

    # Color
    def set_color(self, val: ArrayLike) -> None:
        self.bound_instance.set_color(glm3(val))
    def get_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_color().as_tuple()

    # Edge Color
    def set_edge_color(self, val: ArrayLike) -> None:
        self.bound_instance.set_edge_color(glm3(val))
    def get_edge_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_edge_color().as_tuple()

    # Edge width
    def set_edge_width(self, val: float) -> None:
        self.bound_instance.set_edge_width(val)
    def get_edge_width(self) -> float:
        return self.bound_instance.get_edge_width()

    # Cube size factor
    def set_cube_size_factor(self, val: float) -> None:
        self.bound_instance.set_cube_size_factor(val)
    def get_cube_size_factor(self) -> float:
        return self.bound_instance.get_cube_size_factor()

    # Material
    def set_material(self, mat: str) -> None:
        self.bound_instance.set_material(mat)
    def get_material(self) -> str:
        return self.bound_instance.get_material()

    ## Other stateful options

    def mark_nodes_as_used(self) -> None:
        return self.bound_instance.mark_nodes_as_used()
    def mark_cells_as_used(self) -> None:
        return self.bound_instance.mark_cells_as_used()


    # Picking
    def append_pick_data(self, pick_result: Any) -> None:
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = from_enum(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index

    ## Quantities

    # Scalar

    def add_scalar_quantity(self, name: str, values: ArrayLike, defined_on: Literal["nodes", "cells"] | str = 'nodes', datatype: Literal["standard", "symmetric", "magnitude", "categorical"] | str = "standard", **scalar_args: Any) -> None:

        # NOTE: notice the .flatten('F') below to flatten in Fortran order. This assumes the input data is indexed like array[xInd,yInd,zInd],
        # and converts to the internal x-changes-fastest data layout that the volume grid uses.

        values_arr = np.asarray(values)

        if defined_on == 'nodes':

            if values_arr.shape != tuple(self.get_grid_node_dim()): raise ValueError(f"'values' should be a {self.get_grid_node_dim()} array")

            q = self.bound_instance.add_node_scalar_quantity(name, values_arr.flatten('F'), to_enum(psb.DataType, datatype))

        elif defined_on == 'cells':

            if values_arr.shape != tuple(self.get_grid_cell_dim()): raise ValueError(f"'values' should be a {self.get_grid_cell_dim()} array")

            q = self.bound_instance.add_cell_scalar_quantity(name, values_arr.flatten('F'), to_enum(psb.DataType, datatype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))


        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_volume_grid_scalar_args(self, q, scalar_args, defined_on)
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)


    def add_scalar_quantity_from_callable(self, name: str, func: Callable, defined_on: Literal["nodes", "cells"] | str = 'nodes', datatype: Literal["standard", "symmetric", "magnitude", "categorical"] | str = "standard", **scalar_args: Any) -> None:

        if defined_on == 'nodes':

            q = self.bound_instance.add_node_scalar_quantity_from_callable(name, func, to_enum(psb.DataType, datatype))

        elif defined_on == 'cells':

            q = self.bound_instance.add_cell_scalar_quantity_from_callable(name, func, to_enum(psb.DataType, datatype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))


        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_volume_grid_scalar_args(self, q, scalar_args, defined_on)
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)
   

def register_volume_grid(
    name: str,
    node_dims: ArrayLike,
    bound_low: ArrayLike,
    bound_high: ArrayLike,
    enabled: bool | None = None,
    color: ArrayLike | None = None,
    edge_color: ArrayLike | None = None,
    edge_width: float | None = None,
    cube_size_factor: float | None = None,
    material: str | None = None,
    transparency: float | None = None
) -> VolumeGrid:
    """Register a new volume grid"""

    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = VolumeGrid(name, node_dims=node_dims, bound_low=bound_low, bound_high=bound_high)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if color is not None:
        p.set_color(color)
    if edge_color is not None:
        p.set_edge_color(edge_color)
    if edge_width is not None:
        p.set_edge_width(edge_width)
    if cube_size_factor is not None:
        p.set_cube_size_factor(cube_size_factor)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p

def remove_volume_grid(name: str, error_if_absent: bool = True) -> None:
    """Remove a volume grid by name"""
    psb.remove_volume_grid(name, error_if_absent)

def get_volume_grid(name: str) -> VolumeGrid:
    """Get volume grid by name"""
    if not has_volume_grid(name):
        raise ValueError("no volume grid with name " + str(name))

    raw = psb.get_volume_grid(name)

    # Wrap the instance
    return VolumeGrid(instance=raw)

def has_volume_grid(name: str) -> bool:
    """Check if a volume grid exists by name"""
    return psb.has_volume_grid(name)
    
