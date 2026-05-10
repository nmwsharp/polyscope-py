from typing import Any, Literal, cast

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
    check_all_args_processed,
)

import numpy as np
from numpy.typing import NDArray, ArrayLike

if sys.version_info >= (3, 11):
    from typing import Unpack
else:
    from typing_extensions import Unpack


class SimpleTriangleMesh(Structure):
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope
    bound_instance: psb.SimpleTriangleMesh

    def __init__(
        self,
        name: str | None = None,
        vertices: ArrayLike | None = None,
        faces: ArrayLike | None = None,
        instance: psb.SimpleTriangleMesh | None = None,
    ) -> None:
        super().__init__()

        if instance is not None:
            self.bound_instance = instance
        else:
            assert name is not None
            assert vertices is not None
            assert faces is not None

            vertices_arr = np.array(vertices, dtype=np.float32)
            faces_arr = np.array(faces, dtype=np.int32)

            if vertices_arr.ndim != 2 or vertices_arr.shape[1] != 3:
                raise ValueError(
                    "simple triangle mesh vertices should have shape (N, 3); got " + str(vertices_arr.shape)
                )
            if faces_arr.ndim != 2 or faces_arr.shape[1] != 3:
                raise ValueError(
                    "simple triangle mesh faces should have shape (F, 3); got " + str(faces_arr.shape)
                )

            self.bound_instance = psb.register_simple_triangle_mesh(name, vertices_arr, faces_arr)

    def n_vertices(self) -> int:
        return self.bound_instance.n_vertices()

    def n_faces(self) -> int:
        return self.bound_instance.n_faces()

    def update_vertex_positions(self, vertices: ArrayLike) -> None:
        """Update vertex positions. Vertex count must stay the same."""
        vertices_arr = np.array(vertices, dtype=np.float32)
        self.bound_instance.update_vertex_positions(vertices_arr)

    def update_mesh(self, vertices: ArrayLike, faces: ArrayLike) -> None:
        """Update vertices and faces; counts may change."""
        vertices_arr = np.array(vertices, dtype=np.float32)
        faces_arr = np.array(faces, dtype=np.int32)
        self.bound_instance.update_mesh(vertices_arr, faces_arr)

    def reserve_mesh_capacity(self, n_verts: int, n_faces: int) -> None:
        """Pre-allocate capacity to avoid reallocations on future updates."""
        self.bound_instance.reserve_mesh_capacity(n_verts, n_faces)

    # Picking
    def append_pick_data(self, pick_result: Any) -> None:
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = from_enum(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index

    ## Options

    def set_color(self, val: ArrayLike) -> "SimpleTriangleMesh":
        self.bound_instance.set_color(glm3(val))
        return self

    def get_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_color().as_tuple()

    def set_back_face_policy(self, val: str) -> "SimpleTriangleMesh":
        self.bound_instance.set_back_face_policy(to_enum(psb.BackFacePolicy, val))
        return self

    def get_back_face_policy(self) -> str:
        return from_enum(self.bound_instance.get_back_face_policy())

    def set_back_face_color(self, val: ArrayLike) -> "SimpleTriangleMesh":
        self.bound_instance.set_back_face_color(glm3(val))
        return self

    def get_back_face_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_back_face_color().as_tuple()

    def set_material(self, mat: str) -> "SimpleTriangleMesh":
        self.bound_instance.set_material(mat)
        return self

    def get_material(self) -> str:
        return self.bound_instance.get_material()

    def set_selection_mode(self, val: str) -> "SimpleTriangleMesh":
        self.bound_instance.set_selection_mode(to_enum(psb.MeshSelectionMode, val))
        return self

    def get_selection_mode(self) -> str:
        return from_enum(self.bound_instance.get_selection_mode())

    ## Quantities

    def add_vertex_scalar_quantity(
        self,
        name: str,
        values: ArrayLike,
        datatype: Literal["standard", "symmetric", "magnitude"] | str = "standard",
        **scalar_args: Unpack[ScalarQuantityArgs],
    ) -> psb.SimpleTriangleMeshVertexScalarQuantity:
        values_arr = np.asarray(values, dtype=np.float32)
        q = self.bound_instance.add_vertex_scalar_quantity(name, values_arr, to_enum(psb.DataType, datatype))
        process_quantity_args(self, q, cast(QuantityArgsBase, scalar_args))
        process_scalar_args(self, q, cast(ScalarArgsBase, scalar_args))
        check_all_args_processed(self, q, scalar_args)
        return q

    def add_face_scalar_quantity(
        self,
        name: str,
        values: ArrayLike,
        datatype: Literal["standard", "symmetric", "magnitude"] | str = "standard",
        **scalar_args: Unpack[ScalarQuantityArgs],
    ) -> psb.SimpleTriangleMeshFaceScalarQuantity:
        values_arr = np.asarray(values, dtype=np.float32)
        q = self.bound_instance.add_face_scalar_quantity(name, values_arr, to_enum(psb.DataType, datatype))
        process_quantity_args(self, q, cast(QuantityArgsBase, scalar_args))
        process_scalar_args(self, q, cast(ScalarArgsBase, scalar_args))
        check_all_args_processed(self, q, scalar_args)
        return q

    def add_vertex_color_quantity(
        self,
        name: str,
        values: ArrayLike,
        **color_args: Unpack[ColorQuantityArgs],
    ) -> psb.SimpleTriangleMeshVertexColorQuantity:
        values_arr = np.asarray(values, dtype=np.float32)
        if values_arr.ndim != 2 or values_arr.shape[1] != 3:
            raise ValueError("'values' should be an Nx3 array")
        q = self.bound_instance.add_vertex_color_quantity(name, values_arr)
        process_quantity_args(self, q, cast(QuantityArgsBase, color_args))
        process_color_args(self, q, cast(ColorArgsBase, color_args))
        check_all_args_processed(self, q, color_args)
        return q

    def add_face_color_quantity(
        self,
        name: str,
        values: ArrayLike,
        **color_args: Unpack[ColorQuantityArgs],
    ) -> psb.SimpleTriangleMeshFaceColorQuantity:
        values_arr = np.asarray(values, dtype=np.float32)
        if values_arr.ndim != 2 or values_arr.shape[1] != 3:
            raise ValueError("'values' should be an Nx3 array")
        q = self.bound_instance.add_face_color_quantity(name, values_arr)
        process_quantity_args(self, q, cast(QuantityArgsBase, color_args))
        process_color_args(self, q, cast(ColorArgsBase, color_args))
        check_all_args_processed(self, q, color_args)
        return q


def register_simple_triangle_mesh(
    name: str, vertices: ArrayLike, faces: ArrayLike
) -> SimpleTriangleMesh:
    return SimpleTriangleMesh(name=name, vertices=vertices, faces=faces)


def remove_simple_triangle_mesh(name: str = "", error_if_absent: bool = False) -> None:
    psb.remove_simple_triangle_mesh(name, error_if_absent)


def get_simple_triangle_mesh(name: str = "") -> SimpleTriangleMesh:
    return SimpleTriangleMesh(instance=psb.get_simple_triangle_mesh(name))


def has_simple_triangle_mesh(name: str = "") -> bool:
    return psb.has_simple_triangle_mesh(name)
