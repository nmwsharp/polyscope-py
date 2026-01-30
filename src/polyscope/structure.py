import polyscope_bindings as psb

from polyscope.floating_quantities import (
    add_scalar_image_quantity,
    add_color_image_quantity,
    add_color_alpha_image_quantity,
    add_depth_render_image_quantity,
    add_color_render_image_quantity,
    add_scalar_render_image_quantity,
    add_raw_color_render_image_quantity,
    add_raw_color_alpha_render_image_quantity,
)
from polyscope.managed_buffer import ManagedBuffer
from polyscope.core import TransformationGizmo

import numpy as np

from collections.abc import Sequence
from typing import Any, overload, no_type_check
from numpy.typing import NDArray


# Base class for common properties and methods on structures
class Structure:
    bound_instance: psb.Structure

    def __init__(self):
        pass

    ## Structure management

    def get_name(self) -> str:
        """Get the name"""
        return self.bound_instance.get_name()

    def remove(self) -> None:
        """Remove the structure itself"""
        self.bound_instance.remove()

    def remove_all_quantities(self) -> None:
        """Remove all quantities on the structure"""
        self.bound_instance.remove_all_quantities()  # type: ignore

    def remove_quantity(self, name: str, error_if_absent: bool = False) -> None:
        """Remove a single quantity on the structure"""
        self.bound_instance.remove_quantity(name, error_if_absent) # type: ignore

    ## Enable/disable

    def set_enabled(self, val: bool = True) -> None:
        self.bound_instance.set_enabled(val)

    def is_enabled(self) -> bool:
        return self.bound_instance.is_enabled()

    ## Transparency

    def set_transparency(self, val: float) -> None:
        self.bound_instance.set_transparency(val)

    def get_transparency(self) -> float:
        return self.bound_instance.get_transparency()

    ## Transformation things

    def center_bounding_box(self) -> None:
        self.bound_instance.center_bounding_box()

    def rescale_to_unit(self) -> None:
        self.bound_instance.rescale_to_unit()

    def reset_transform(self) -> None:
        self.bound_instance.reset_transform()

    def set_transform(self, new_mat4x4: NDArray) -> None:
        self.bound_instance.set_transform(new_mat4x4)

    def set_position(self, new_vec3: Sequence[float]) -> None:
        self.bound_instance.set_position(np.array(new_vec3))

    def translate(self, trans_vec3: Sequence[float]) -> None:
        self.bound_instance.translate(np.array(trans_vec3))

    def get_transform(self) -> NDArray:
        return self.bound_instance.get_transform()

    def get_position(self) -> NDArray:
        return self.bound_instance.get_position()

    def set_transform_gizmo_enabled(self, val: bool) -> None:
        self.bound_instance.set_transform_gizmo_enabled(val)

    def get_transform_gizmo_enabled(self) -> bool:
        return self.bound_instance.get_transform_gizmo_enabled()

    def get_transformation_gizmo(self) -> TransformationGizmo:
        return TransformationGizmo(self.bound_instance.get_transformation_gizmo())

    ## Managed Buffers

    @no_type_check
    def get_buffer(self, buffer_name: str) -> ManagedBuffer:
        present, buffer_type = self.bound_instance.has_buffer_type(buffer_name)

        if not present:
            raise ValueError("structure has no buffer named " + buffer_name)

        return {
            psb.ManagedBufferType.Float: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Float(n), t
            ),
            psb.ManagedBufferType.Double: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Double(n), t
            ),
            psb.ManagedBufferType.Vec2: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Vec2(n), t
            ),
            psb.ManagedBufferType.Vec3: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Vec3(n), t
            ),
            psb.ManagedBufferType.Vec4: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Vec4(n), t
            ),
            psb.ManagedBufferType.Arr2Vec3: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Arr2Vec4(n), t
            ),
            psb.ManagedBufferType.Arr3Vec3: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Arr3Vec4(n), t
            ),
            psb.ManagedBufferType.Arr4Vec3: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Arr4Vec4(n), t
            ),
            psb.ManagedBufferType.UInt32: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_UInt32(n), t
            ),
            psb.ManagedBufferType.Int32: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_Int32(n), t
            ),
            psb.ManagedBufferType.UVec2: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_UVec2(n), t
            ),
            psb.ManagedBufferType.UVec3: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_UVec3(n), t
            ),
            psb.ManagedBufferType.UVec4: lambda n, t: ManagedBuffer(
                self.bound_instance.get_buffer_UVec4(n), t
            ),
        }[buffer_type](buffer_name, buffer_type)

    @no_type_check
    def get_quantity_buffer(
        self, quantity_name: str, buffer_name: str
    ) -> ManagedBuffer:
        present, buffer_type = self.bound_instance.has_quantity_buffer_type(
            quantity_name, buffer_name
        )

        if not present:
            if (
                self.get_name()
                == psb.get_global_floating_quantity_structure().get_name()
            ):
                # give a more informative error if this was called on the global floating quantity, becuase it is particularly easy for users to get confused and call this function at the global scope rather than on a quantity
                raise ValueError(
                    f"There is no quantity {quantity_name} with buffer named {buffer_name}. NOTE: calling polyscope.get_quantity_buffer() is for global floating quantities only, call structure.get_quantity_buffer() to get buffers for a quantity added to some structure."
                )
            else:
                raise ValueError(
                    f"Structure {self.get_name()} does not have a quantity {quantity_name} with buffer named {buffer_name}"
                )

        return {
            psb.ManagedBufferType.Float: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Float(q, n), t
            ),
            psb.ManagedBufferType.Double: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Double(q, n), t
            ),
            psb.ManagedBufferType.Vec2: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Vec2(q, n), t
            ),
            psb.ManagedBufferType.Vec3: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Vec3(q, n), t
            ),
            psb.ManagedBufferType.Vec4: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Vec4(q, n), t
            ),
            psb.ManagedBufferType.Arr2Vec3: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Arr2Vec4(q, n), t
            ),
            psb.ManagedBufferType.Arr3Vec3: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Arr3Vec4(q, n), t
            ),
            psb.ManagedBufferType.Arr4Vec3: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Arr4Vec4(q, n), t
            ),
            psb.ManagedBufferType.UInt32: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_UInt32(q, n), t
            ),
            psb.ManagedBufferType.Int32: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_Int32(q, n), t
            ),
            psb.ManagedBufferType.UVec2: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_UVec2(q, n), t
            ),
            psb.ManagedBufferType.UVec3: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_UVec3(q, n), t
            ),
            psb.ManagedBufferType.UVec4: lambda q, n, t: ManagedBuffer(
                self.bound_instance.get_quantity_buffer_UVec4(q, n), t
            ),
        }[buffer_type](quantity_name, buffer_name, buffer_type)

    ## Groups
    def add_to_group(self, group: str | Any) -> None:
        # take either a string or a group object as input
        if isinstance(group, str):
            self.bound_instance.add_to_group(group)
        else:
            self.bound_instance.add_to_group(group.get_name())

    ## Slice planes

    def set_cull_whole_elements(self, val: bool) -> None:
        self.bound_instance.set_cull_whole_elements(val)

    def get_cull_whole_elements(self) -> bool:
        return self.bound_instance.get_cull_whole_elements()

    def set_ignore_slice_plane(self, plane: str | Any, val: bool) -> None:
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            self.bound_instance.set_ignore_slice_plane(plane, val)
        else:
            self.bound_instance.set_ignore_slice_plane(plane.get_name(), val)

    def get_ignore_slice_plane(self, plane: str | Any) -> bool:
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            return self.bound_instance.get_ignore_slice_plane(plane)
        else:
            return self.bound_instance.get_ignore_slice_plane(plane.get_name())

    ## Image Floating Quantities

    def add_scalar_image_quantity(
        self,
        name: str,
        values: NDArray,
        image_origin: str = "upper_left",
        datatype: str = "standard",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_scalar_image_quantity(
            name,
            values,
            image_origin=image_origin,
            datatype=datatype,
            struct_ref=self,
            **option_args,
        )

    def add_color_image_quantity(
        self,
        name: str,
        values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_image_quantity(
            name, values, image_origin=image_origin, struct_ref=self, **option_args
        )

    def add_color_alpha_image_quantity(
        self,
        name: str,
        values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_alpha_image_quantity(
            name, values, image_origin=image_origin, struct_ref=self, **option_args
        )

    ## Render Image

    def add_depth_render_image_quantity(
        self,
        name: str,
        depth_values: NDArray,
        normal_values: NDArray,
        image_origin: str = "upper_left",
        color: Sequence | None = None,
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_depth_render_image_quantity(
            name,
            depth_values,
            normal_values,
            image_origin=image_origin,
            color=color,
            struct_ref=self,
            **option_args,
        )

    def add_color_render_image_quantity(
        self,
        name: str,
        depth_values: NDArray,
        normal_values: NDArray,
        color_values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_render_image_quantity(
            name,
            depth_values,
            normal_values,
            color_values,
            image_origin=image_origin,
            struct_ref=self,
            **option_args,
        )

    def add_scalar_render_image_quantity(
        self,
        name: str,
        depth_values: NDArray,
        normal_values: NDArray,
        scalar_values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_scalar_render_image_quantity(
            name,
            depth_values,
            normal_values,
            scalar_values,
            image_origin=image_origin,
            struct_ref=self,
            **option_args,
        )

    def add_raw_color_render_image_quantity(
        self,
        name: str,
        depth_values: NDArray,
        color_values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_raw_color_render_image_quantity(
            name,
            depth_values,
            color_values,
            image_origin=image_origin,
            struct_ref=self,
            **option_args,
        )

    def add_raw_color_alpha_render_image_quantity(
        self,
        name: str,
        depth_values: NDArray,
        color_values: NDArray,
        image_origin: str = "upper_left",
        **option_args: Any,
    ) -> Any:
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_raw_color_alpha_render_image_quantity(
            name,
            depth_values,
            color_values,
            image_origin=image_origin,
            struct_ref=self,
            **option_args,
        )
