from typing import Literal, overload, cast, Any

import sys
import polyscope_bindings as psb

from polyscope.core import glm3
from polyscope.enums import to_enum, from_enum
from polyscope.structure import Structure
from polyscope.common import (
    QuantityArgsBase,
    process_quantity_args,
    ScalarQuantityArgs,
    ScalarArgsBase,
    process_scalar_args,
    ColorQuantityArgs,
    ColorArgsBase,
    process_color_args,
    VectorQuantityArgs,
    VectorArgsBase,
    process_vector_args,
    check_all_args_processed,
)

import numpy as np
from numpy.typing import NDArray, ArrayLike

if sys.version_info >= (3, 11):
    from typing import Unpack
else:
    from typing_extensions import Unpack


class CurveNetwork(Structure):
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    bound_instance: psb.CurveNetwork

    @overload
    def __init__(
        self, name: str, nodes: ArrayLike, edges: ArrayLike | Literal["line", "loop", "segments"] | str
    ) -> None: ...

    @overload
    def __init__(self, *, instance: psb.CurveNetwork) -> None: ...

    # End users should not call this constrctor, use register_curve_network instead
    def __init__(
        self,
        name: str | None = None,
        nodes: ArrayLike | None = None,
        edges: ArrayLike | Literal["line", "loop", "segments"] | str | None = None,
        instance: psb.CurveNetwork | None = None,
    ) -> None:
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            assert name is not None
            assert nodes is not None
            assert edges is not None

            nodes_arr = np.asarray(nodes)

            # Create a new instance
            self.check_shape(nodes_arr)

            if isinstance(edges, str):
                # Special case: edges as a string key

                if edges not in ["line", "loop", "segments"]:
                    raise ValueError(
                        "bad edges setting, must either be numpy array, or must be in ['line', 'loop', 'segments'], got "
                        + str(edges)
                    )

                if nodes_arr.shape[1] == 3:
                    if edges == "line":
                        self.bound_instance = psb.register_curve_network_line(name, nodes_arr)
                    elif edges == "loop":
                        self.bound_instance = psb.register_curve_network_loop(name, nodes_arr)
                    elif edges == "segments":
                        self.bound_instance = psb.register_curve_network_segments(name, nodes_arr)
                elif nodes_arr.shape[1] == 2:
                    if edges == "line":
                        self.bound_instance = psb.register_curve_network_line2D(name, nodes_arr)
                    elif edges == "loop":
                        self.bound_instance = psb.register_curve_network_loop2D(name, nodes_arr)
                    elif edges == "segments":
                        self.bound_instance = psb.register_curve_network_segments2D(name, nodes_arr)
            else:
                # Common case: process edges as numpy array

                edges_arr = np.asarray(edges)

                if (len(edges_arr.shape) != 2) or (edges_arr.shape[1] != 2):
                    raise ValueError(
                        "curve network edges_arr should have shape (N_edge,2); shape is " + str(edges_arr.shape)
                    )

                if nodes_arr.shape[1] == 3:
                    self.bound_instance = psb.register_curve_network(name, nodes_arr, edges_arr)
                elif nodes_arr.shape[1] == 2:
                    self.bound_instance = psb.register_curve_network2D(name, nodes_arr, edges_arr)

    def check_shape(self, points):
        # Helper to validate arrays
        if (len(points.shape) != 2) or (points.shape[1] not in (2, 3)):
            raise ValueError("curve network node positions should have shape (N,3); shape is " + str(points.shape))

    def n_nodes(self) -> int:
        return self.bound_instance.n_nodes()

    def n_edges(self) -> int:
        return self.bound_instance.n_edges()

    # Update
    def update_node_positions(self, nodes: ArrayLike) -> None:
        nodes_arr = np.asarray(nodes)
        self.check_shape(nodes_arr)

        if nodes_arr.shape[1] == 3:
            self.bound_instance.update_node_positions(nodes_arr)
        elif nodes_arr.shape[1] == 2:
            self.bound_instance.update_node_positions2D(nodes_arr)
        else:
            raise ValueError("bad node shape")

    # Custom radius quantity
    def set_node_radius_quantity(self, quantity_name: str, autoscale=True) -> None:
        self.bound_instance.set_node_radius_quantity(quantity_name, autoscale)

    def clear_node_radius_quantity(self) -> None:
        self.bound_instance.clear_node_radius_quantity()

    def set_edge_radius_quantity(self, quantity_name: str, autoscale=True) -> None:
        self.bound_instance.set_edge_radius_quantity(quantity_name, autoscale)

    def clear_edge_radius_quantity(self) -> None:
        self.bound_instance.clear_edge_radius_quantity()

    ## Options

    # Radius
    def set_radius(self, rad: float, relative: bool = True) -> None:
        self.bound_instance.set_radius(rad, relative)

    def get_radius(self) -> float:
        return self.bound_instance.get_radius()

    # Color
    def set_color(self, val: ArrayLike) -> None:
        self.bound_instance.set_color(glm3(val))

    def get_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_color().as_tuple()

    # Material
    def set_material(self, mat: str) -> None:
        self.bound_instance.set_material(mat)

    def get_material(self) -> str:
        return self.bound_instance.get_material()

    # Picking
    def append_pick_data(self, pick_result):
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = from_enum(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index
        pick_result.structure_data["t_edge"] = struct_result.t_edge

    ## Quantities

    # Scalar
    def add_scalar_quantity(
        self,
        name: str,
        values: NDArray,
        defined_on: Literal["nodes", "edges"] | str = "nodes",
        datatype: Literal["standard", "symmetric", "magnitude", "categorical"] | str = "standard",
        **scalar_args: Unpack[ScalarQuantityArgs],
    ) -> None:
        if len(values.shape) != 1:
            raise ValueError("'values' should be a length-N array")

        if defined_on == "nodes":
            if values.shape[0] != self.n_nodes():
                raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_instance.add_node_scalar_quantity(name, values, to_enum(psb.DataType, datatype))
        elif defined_on == "edges":
            if values.shape[0] != self.n_edges():
                raise ValueError("'values' should be a length n_edges array")
            q = self.bound_instance.add_edge_scalar_quantity(name, values, to_enum(psb.DataType, datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, cast(QuantityArgsBase, scalar_args))
        process_scalar_args(self, q, cast(ScalarArgsBase, scalar_args))
        check_all_args_processed(self, q, scalar_args)

    # Color
    def add_color_quantity(
        self, name: str, values: NDArray, defined_on: Literal["nodes", "edges"] | str = "nodes", **color_args: Unpack[ColorQuantityArgs]
    ) -> None:
        if len(values.shape) != 2 or values.shape[1] != 3:
            raise ValueError("'values' should be an Nx3 array")

        if defined_on == "nodes":
            if values.shape[0] != self.n_nodes():
                raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_instance.add_node_color_quantity(name, values)
        elif defined_on == "edges":
            if values.shape[0] != self.n_edges():
                raise ValueError("'values' should be a length n_edges array")
            q = self.bound_instance.add_edge_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, cast(QuantityArgsBase, color_args))
        process_color_args(self, q, cast(ColorArgsBase, color_args))
        check_all_args_processed(self, q, color_args)

    # Vector
    def add_vector_quantity(
        self,
        name: str,
        values: NDArray,
        defined_on: Literal["nodes", "edges"] | str = "nodes",
        vectortype: Literal["standard", "ambient"] | str = "standard", **vector_args: Unpack[VectorQuantityArgs],
    ):
        if len(values.shape) != 2 or values.shape[1] not in [2, 3]:
            raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")

        if defined_on == "nodes":
            if values.shape[0] != self.n_nodes():
                raise ValueError("'values' should be a length n_nodes array")

            if values.shape[1] == 2:
                q = self.bound_instance.add_node_vector_quantity2D(name, values, to_enum(psb.VectorType, vectortype))
            elif values.shape[1] == 3:
                q = self.bound_instance.add_node_vector_quantity(name, values, to_enum(psb.VectorType, vectortype))

        elif defined_on == "edges":
            if values.shape[0] != self.n_edges():
                raise ValueError("'values' should be a length n_edges array")

            if values.shape[1] == 2:
                q = self.bound_instance.add_edge_vector_quantity2D(name, values, to_enum(psb.VectorType, vectortype))
            elif values.shape[1] == 3:
                q = self.bound_instance.add_edge_vector_quantity(name, values, to_enum(psb.VectorType, vectortype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, cast(QuantityArgsBase, vector_args))
        process_vector_args(self, q, cast(VectorArgsBase, vector_args))
        check_all_args_processed(self, q, vector_args)


def register_curve_network(
    name: str,
    nodes: ArrayLike,
    edges: ArrayLike | Literal["line", "loop", "segments"] | str,
    enabled: bool | None = None,
    radius: float | None = None,
    color: ArrayLike | None = None,
    material: str | None = None,
    transparency: float | None = None,
):
    """Register a new curve network"""

    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = CurveNetwork(name, nodes, edges)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if radius is not None:
        p.set_radius(radius)
    if color is not None:
        p.set_color(color)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p


def remove_curve_network(name: str, error_if_absent: bool = True) -> None:
    """Remove a curve network by name"""
    psb.remove_curve_network(name, error_if_absent)


def get_curve_network(name: str) -> CurveNetwork:
    """Get curve network by name"""
    if not has_curve_network(name):
        raise ValueError("no curve network with name " + str(name))

    raw = psb.get_curve_network(name)

    # Wrap the instance
    return CurveNetwork(instance=raw)


def has_curve_network(name: str) -> bool:
    """Check if a curve network exists by name"""
    return psb.has_curve_network(name)
