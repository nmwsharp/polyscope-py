from typing import Any, Literal, cast, overload

import sys
import polyscope_bindings as psb

from polyscope.core import glm3
from polyscope.enums import to_enum, from_enum
from polyscope.structure import Structure

from polyscope.common import (
    QuantityArgsBase,
    process_quantity_args,
    ScalarArgsBase,
    ScalarQuantityArgs,
    process_scalar_args,
    ColorQuantityArgs,
    process_color_args,
    ColorArgsBase,
    check_all_args_processed,
)

if sys.version_info >= (3, 11):
    from typing import Unpack
else:
    from typing_extensions import Unpack

import numpy as np
from numpy.typing import NDArray, ArrayLike


class SparseVolumeGrid(Structure):
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope
    bound_instance: psb.SparseVolumeGrid

    @overload
    def __init__(self, name: str, origin: ArrayLike, grid_cell_width: ArrayLike, occupied_cells: ArrayLike) -> None: ...

    @overload
    def __init__(self, *, instance: psb.SparseVolumeGrid) -> None: ...

    # End users should not call this constructor, use register_sparse_volume_grid instead
    def __init__(
        self,
        name: str | None = None,
        origin: ArrayLike | None = None,
        grid_cell_width: ArrayLike | None = None,
        occupied_cells: ArrayLike | None = None,
        instance: psb.SparseVolumeGrid | None = None,
    ) -> None:
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance

            assert name is not None
            assert origin is not None
            assert grid_cell_width is not None
            assert occupied_cells is not None

            occupied_cells_arr = np.asarray(occupied_cells, dtype=np.int32)
            if occupied_cells_arr.ndim != 2 or occupied_cells_arr.shape[1] != 3:
                raise ValueError("'occupied_cells' should be an (N, 3) integer array")

            self.bound_instance = psb.register_sparse_volume_grid(
                name, glm3(origin), glm3(grid_cell_width), occupied_cells_arr
            )

    def n_cells(self) -> int:
        return self.bound_instance.n_cells()

    def n_nodes(self) -> int:
        return self.bound_instance.n_nodes()

    def get_origin(self) -> NDArray:
        return self.bound_instance.get_origin()

    def get_grid_cell_width(self) -> NDArray:
        return self.bound_instance.get_grid_cell_width()

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

    # Picking
    def append_pick_data(self, pick_result: Any) -> None:
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = from_enum(struct_result.element_type)
        pick_result.structure_data["cell_index"] = struct_result.cell_index
        pick_result.structure_data["cell_flat_index"] = struct_result.cell_flat_index
        pick_result.structure_data["node_index"] = struct_result.node_index

    ## Quantities

    # Scalar

    def add_scalar_quantity(
        self,
        name: str,
        values: ArrayLike,
        defined_on: Literal["nodes", "cells"] | str = "cells",
        datatype: Literal["standard", "symmetric", "magnitude", "categorical"] | str = "standard",
        node_indices: ArrayLike | None = None,
        **scalar_args: Unpack[ScalarQuantityArgs],
    ) -> None:

        values_arr = np.asarray(values, dtype=np.float32)

        if defined_on == "cells":
            if values_arr.ndim != 1:
                raise ValueError("'values' should be a 1D array for cell-defined data")

            q = self.bound_instance.add_cell_scalar_quantity(
                name, values_arr, to_enum(psb.DataType, datatype)
            )

        elif defined_on == "nodes":
            if node_indices is None:
                raise ValueError("'node_indices' must be provided for node-defined data")

            node_indices_arr = np.asarray(node_indices, dtype=np.int32)
            if node_indices_arr.ndim != 2 or node_indices_arr.shape[1] != 3:
                raise ValueError("'node_indices' should be an (N, 3) integer array")

            if values_arr.ndim != 1:
                raise ValueError("'values' should be a 1D array for node-defined data")

            q = self.bound_instance.add_node_scalar_quantity(
                name, node_indices_arr, values_arr, to_enum(psb.DataType, datatype)
            )

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))

        # process and act on additional arguments
        process_quantity_args(self, q, cast(QuantityArgsBase, scalar_args))
        process_scalar_args(self, q, cast(ScalarArgsBase, scalar_args))
        check_all_args_processed(self, q, scalar_args)

    # Color

    def add_color_quantity(
        self,
        name: str,
        colors: ArrayLike,
        defined_on: Literal["nodes", "cells"] | str = "cells",
        node_indices: ArrayLike | None = None,
        **color_args: Unpack[ColorQuantityArgs],
    ) -> None:

        colors_arr = np.asarray(colors, dtype=np.float32)

        if defined_on == "cells":
            if colors_arr.ndim != 2 or colors_arr.shape[1] != 3:
                raise ValueError("'colors' should be an (N, 3) array for cell-defined data")

            q = self.bound_instance.add_cell_color_quantity(name, colors_arr)

        elif defined_on == "nodes":
            if node_indices is None:
                raise ValueError("'node_indices' must be provided for node-defined data")

            node_indices_arr = np.asarray(node_indices, dtype=np.int32)
            if node_indices_arr.ndim != 2 or node_indices_arr.shape[1] != 3:
                raise ValueError("'node_indices' should be an (N, 3) integer array")

            if colors_arr.ndim != 2 or colors_arr.shape[1] != 3:
                raise ValueError("'colors' should be an (N, 3) array for node-defined data")

            q = self.bound_instance.add_node_color_quantity(name, node_indices_arr, colors_arr)

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))

        # process and act on additional arguments
        process_quantity_args(self, q, cast(QuantityArgsBase, color_args))
        process_color_args(self, q, cast(ColorArgsBase, color_args))
        check_all_args_processed(self, q, color_args)


def register_sparse_volume_grid(
    name: str,
    origin: ArrayLike,
    grid_cell_width: ArrayLike,
    occupied_cells: ArrayLike,
    enabled: bool | None = None,
    color: ArrayLike | None = None,
    edge_color: ArrayLike | None = None,
    edge_width: float | None = None,
    cube_size_factor: float | None = None,
    material: str | None = None,
    transparency: float | None = None,
) -> SparseVolumeGrid:
    """Register a new sparse volume grid"""

    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = SparseVolumeGrid(name, origin=origin, grid_cell_width=grid_cell_width, occupied_cells=occupied_cells)

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


def remove_sparse_volume_grid(name: str, error_if_absent: bool = True) -> None:
    """Remove a sparse volume grid by name"""
    psb.remove_sparse_volume_grid(name, error_if_absent)


def get_sparse_volume_grid(name: str) -> SparseVolumeGrid:
    """Get sparse volume grid by name"""
    if not has_sparse_volume_grid(name):
        raise ValueError("no sparse volume grid with name " + str(name))

    raw = psb.get_sparse_volume_grid(name)

    # Wrap the instance
    return SparseVolumeGrid(instance=raw)


def has_sparse_volume_grid(name: str) -> bool:
    """Check if a sparse volume grid exists by name"""
    return psb.has_sparse_volume_grid(name)
