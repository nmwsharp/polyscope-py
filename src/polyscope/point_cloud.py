import polyscope_bindings as psb

from polyscope.core import  glm3
from polyscope.enums import to_enum
from polyscope.structure import Structure
from polyscope.common import (
    process_quantity_args,
    process_scalar_args,
    process_color_args,
    process_vector_args,
    process_parameterization_args,
    check_all_args_processed,
)

import numpy as np

from collections.abc import Sequence
from typing import Any, overload
from numpy.typing import NDArray


class PointCloud(Structure):
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope
    bound_instance: psb.PointCloud

    @overload
    def __init__(self, name: str, points: NDArray) -> None: ...

    @overload
    def __init__(self, *, instance: psb.PointCloud) -> None: ...

    # End users should not call this constrctor, use register_point_cloud instead
    def __init__(
        self,
        name: str | None = None,
        points: NDArray | None = None,
        instance: psb.PointCloud | None = None,
    ) -> None:
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance
            assert name is not None
            assert points is not None

            self.check_shape(points)

            if points.shape[1] == 3:
                self.bound_instance = psb.register_point_cloud(name, points)
            elif points.shape[1] == 2:
                self.bound_instance = psb.register_point_cloud2D(name, points)
            else:
                raise ValueError("bad point cloud shape")

    def check_shape(self, points: NDArray) -> None:
        # Helper to validate arrays

        if (len(points.shape) != 2) or (points.shape[1] not in (2, 3)):
            raise ValueError(
                "Point cloud positions should have shape (N,3); shape is "
                + str(points.shape)
            )

    def n_points(self) -> int:
        return self.bound_instance.n_points()

    # Point render mode
    def set_point_render_mode(self, val: str) -> None:
        self.bound_instance.set_point_render_mode(to_enum(psb.PointRenderMode, val))

    def get_point_render_mode(self) -> psb.PointRenderMode:
        return self.bound_instance.get_point_render_mode()

    # Update
    def update_point_positions(self, points: NDArray) -> None:
        self.check_shape(points)

        if points.shape[1] == 3:
            self.bound_instance.update_point_positions(points)
        elif points.shape[1] == 2:
            self.bound_instance.update_point_positions2D(points)
        else:
            raise ValueError("bad point cloud shape")

    # Custom radius quantity
    def set_point_radius_quantity(
        self, quantity_name: str, autoscale: bool = True
    ) -> None:
        self.bound_instance.set_point_radius_quantity(quantity_name, autoscale)

    def clear_point_radius_quantity(self) -> None:
        self.bound_instance.clear_point_radius_quantity()

    # Custom transparency quantity
    def set_transparency_quantity(self, quantity_name: str) -> None:
        self.bound_instance.set_transparency_quantity(quantity_name)

    def clear_transparency_quantity(self) -> None:
        self.bound_instance.clear_transparency_quantity()

    ## Options

    # Point radius
    def set_radius(self, rad: float, relative: bool = True) -> None:
        self.bound_instance.set_radius(rad, relative)

    def get_radius(self) -> float:
        return self.bound_instance.get_radius()

    # Point color
    def set_color(self, val: Sequence[float]) -> None:
        self.bound_instance.set_color(glm3(val))

    def get_color(self) -> tuple:
        return self.bound_instance.get_color().as_tuple()

    # Point material
    def set_material(self, mat: str) -> None:
        self.bound_instance.set_material(mat)

    def get_material(self) -> str:
        return self.bound_instance.get_material()

    def append_pick_data(self, pick_result: Any) -> None:
        struct_result = self.bound_instance.interpret_pick_result(
            pick_result.raw_result
        )
        pick_result.structure_data["index"] = struct_result.index

    ## Quantities

    # Scalar
    def add_scalar_quantity(
        self, name: str, values: NDArray, datatype: str = "standard", **scalar_args: Any
    ) -> None:
        if len(values.shape) != 1 or values.shape[0] != self.n_points():
            raise ValueError("'values' should be a length-N array")

        q = self.bound_instance.add_scalar_quantity(
            name, values, to_enum(psb.DataType, datatype)
        )

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)

    # Color
    def add_color_quantity(self, name: str, values: NDArray, **color_args: Any) -> None:
        if (
            len(values.shape) != 2
            or values.shape[0] != self.n_points()
            or values.shape[1] != 3
        ):
            raise ValueError("'values' should be an Nx3 array")

        q = self.bound_instance.add_color_quantity(name, values)

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, color_args)
        process_color_args(self, q, color_args)
        check_all_args_processed(self, q, color_args)

    # Vector
    def add_vector_quantity(
        self,
        name: str,
        values: NDArray,
        vectortype: str = "standard",
        **vector_args: Any,
    ) -> None:
        if (
            len(values.shape) != 2
            or values.shape[0] != self.n_points()
            or values.shape[1] not in [2, 3]
        ):
            raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")

        if values.shape[1] == 2:
            q = self.bound_instance.add_vector_quantity2D(
                name, values, to_enum(psb.VectorType, vectortype)
            )
        elif values.shape[1] == 3:
            q = self.bound_instance.add_vector_quantity(
                name, values, to_enum(psb.VectorType, vectortype)
            )

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)

    # Parameterization
    def add_parameterization_quantity(
        self,
        name: str,
        values: NDArray,
        coords_type: str = "unit",
        **parameterization_args: Any,
    ) -> None:
        if (
            len(values.shape) != 2
            or values.shape[0] != self.n_points()
            or values.shape[1] != 2
        ):
            raise ValueError("'values' should be an Nx2 array")

        # parse the coords type in to an enum
        coords_type_enum = to_enum(psb.ParamCoordsType, coords_type)

        q = self.bound_instance.add_parameterization_quantity(
            name, values, coords_type_enum
        )

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, parameterization_args)
        process_parameterization_args(self, q, parameterization_args, is_surface=False)
        check_all_args_processed(self, q, parameterization_args)


def register_point_cloud(
    name: str,
    points: NDArray,
    enabled: bool | None = None,
    radius: float | None = None,
    point_render_mode: str | None = None,
    color: Sequence | None = None,
    material: str | None = None,
    transparency: float | None = None,
) -> PointCloud:
    """Register a new point cloud"""
    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = PointCloud(name, points)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if radius is not None:
        p.set_radius(radius)
    if point_render_mode is not None:
        p.set_point_render_mode(point_render_mode)
    if color is not None:
        p.set_color(color)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p


def remove_point_cloud(name: str, error_if_absent: bool = True) -> None:
    """Remove a point cloud by name"""
    psb.remove_point_cloud(name, error_if_absent)


def get_point_cloud(name: str) -> PointCloud:
    """Get point cloud by name"""
    if not has_point_cloud(name):
        raise ValueError("no point cloud with name " + str(name))

    raw_cloud = psb.get_point_cloud(name)

    # Wrap the instance
    return PointCloud(instance=raw_cloud)


def has_point_cloud(name: str) -> bool:
    """Check if a point cloud exists by name"""
    return psb.has_point_cloud(name)
