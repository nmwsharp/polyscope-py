from typing import Any, Literal

import polyscope_bindings as psb

from polyscope.common import check_is_scalar_image, check_is_image3, check_is_image4, check_image_dims_compatible, process_scalar_args, process_color_args, process_image_args, process_render_image_args, process_quantity_args, check_all_args_processed
from polyscope.core import glm3
from polyscope.enums import to_enum

import numpy as np
from numpy.typing import ArrayLike

def _resolve_floating_struct_instance(struct_ref: Any) -> Any:
    if struct_ref is None:
        return psb.get_global_floating_quantity_structure()
    else:
        return struct_ref.bound_instance


def get_quantity_buffer(quantity_name: str, buffer_name: str) -> Any:
    from polyscope.global_floating_quantity_structure import FloatingQuantityStructure

    floating_struct = FloatingQuantityStructure()
    return floating_struct.get_quantity_buffer(quantity_name, buffer_name)

  
def add_scalar_image_quantity(name: str, values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", datatype: Literal["standard", "symmetric", "magnitude", "categorical"] | str = "standard", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    values_arr = np.asarray(values)
    check_is_scalar_image(values_arr)
    dimY = values_arr.shape[0]
    dimX = values_arr.shape[1]

    values_flat = values_arr.flatten().astype(np.float32)

    q = struct_instance_ref.add_scalar_image_quantity(name, dimX, dimY, values_flat,
                                             to_enum(psb.ImageOrigin,image_origin), to_enum(psb.DataType, datatype))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_scalar_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def add_color_image_quantity(name: str, values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    values_arr = np.asarray(values)
    check_is_image3(values_arr)
    dimY = values_arr.shape[0]
    dimX = values_arr.shape[1]

    values_flat = values_arr.reshape(-1,3).astype(np.float32)

    q = struct_instance_ref.add_color_image_quantity(name, dimX, dimY, values_flat, to_enum(psb.ImageOrigin, image_origin))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_color_alpha_image_quantity(name: str, values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    values_arr = np.asarray(values)
    check_is_image4(values_arr)
    dimY = values_arr.shape[0]
    dimX = values_arr.shape[1]

    values_flat = values_arr.reshape(-1,4).astype(np.float32)

    q = struct_instance_ref.add_color_alpha_image_quantity(name, dimX, dimY, values_flat,
                                             to_enum(psb.ImageOrigin,image_origin))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

    
def add_depth_render_image_quantity(name: str, depth_values: ArrayLike, normal_values: ArrayLike | None, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", color: ArrayLike | None = None, struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    depth_values_arr = np.asarray(depth_values)
    check_is_scalar_image(depth_values_arr)
    if normal_values is None:
        normal_values_arr = np.zeros((0,0,3))
    else:
        normal_values_arr = np.asarray(normal_values)
        check_is_image3(normal_values_arr)
        check_image_dims_compatible([depth_values_arr, normal_values_arr])
    dimY = depth_values_arr.shape[0]
    dimX = depth_values_arr.shape[1]

    depth_values_flat = depth_values_arr.flatten().astype(np.float32)
    normal_values_flat = normal_values_arr.reshape(-1,3).astype(np.float32)

    q = struct_instance_ref.add_depth_render_image_quantity(name, dimX, dimY,
                                                            depth_values_flat, normal_values_flat,
                                                            to_enum(psb.ImageOrigin,image_origin))

    if color is not None:
        q.set_color(glm3(color))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_color_render_image_quantity(name: str, depth_values: ArrayLike, normal_values: ArrayLike | None, color_values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    depth_values_arr = np.asarray(depth_values)
    color_values_arr = np.asarray(color_values)
    check_is_scalar_image(depth_values_arr)
    check_is_image3(color_values_arr)
    if normal_values is None:
        normal_values_arr = np.zeros((0,0,3))
        check_image_dims_compatible([depth_values_arr, color_values_arr])
    else:
        normal_values_arr = np.asarray(normal_values)
        check_is_image3(normal_values_arr)
        check_image_dims_compatible([depth_values_arr, normal_values_arr, color_values_arr])
    dimY = depth_values_arr.shape[0]
    dimX = depth_values_arr.shape[1]

    depth_values_flat = depth_values_arr.flatten()
    normal_values_flat = normal_values_arr.reshape(-1,3)
    color_values_flat = color_values_arr.reshape(-1,3)

    q = struct_instance_ref.add_color_render_image_quantity(name, dimX, dimY,
                                                            depth_values_flat, normal_values_flat, color_values_flat,
                                                            to_enum(psb.ImageOrigin,image_origin))


    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_scalar_render_image_quantity(name: str, depth_values: ArrayLike, normal_values: ArrayLike | None, scalar_values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    depth_values_arr = np.asarray(depth_values)
    scalar_values_arr = np.asarray(scalar_values)
    check_is_scalar_image(depth_values_arr)
    check_is_scalar_image(scalar_values_arr)
    if normal_values is None:
        normal_values_arr = np.zeros((0,0,3))
        check_image_dims_compatible([depth_values_arr, scalar_values_arr])
    else:
        normal_values_arr = np.asarray(normal_values)
        check_is_image3(normal_values_arr)
        check_image_dims_compatible([depth_values_arr, normal_values_arr, scalar_values_arr])
    dimY = depth_values_arr.shape[0]
    dimX = depth_values_arr.shape[1]

    depth_values_flat = depth_values_arr.flatten().astype(np.float32)
    normal_values_flat = normal_values_arr.reshape(-1,3).astype(np.float32)
    scalar_values_flat = scalar_values_arr.flatten().astype(np.float32)

    q = struct_instance_ref.add_scalar_render_image_quantity(name, dimX, dimY,
                                                            depth_values_flat, normal_values_flat, scalar_values_flat,
                                                            to_enum(psb.ImageOrigin,image_origin))


    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_scalar_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_raw_color_render_image_quantity(name: str, depth_values: ArrayLike, color_values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    depth_values_arr = np.asarray(depth_values)
    color_values_arr = np.asarray(color_values)
    check_is_scalar_image(depth_values_arr)
    check_is_image3(color_values_arr)
    check_image_dims_compatible([depth_values_arr, color_values_arr])
    dimY = depth_values_arr.shape[0]
    dimX = depth_values_arr.shape[1]

    depth_values_flat = depth_values_arr.flatten().astype(np.float32)
    color_values_flat = color_values_arr.reshape(-1,3).astype(np.float32)

    q = struct_instance_ref.add_raw_color_render_image_quantity(name, dimX, dimY,
                                                                depth_values_flat, color_values_flat,
                                                                to_enum(psb.ImageOrigin,image_origin))


    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def add_raw_color_alpha_render_image_quantity(name: str, depth_values: ArrayLike, color_values: ArrayLike, image_origin: Literal["upper_left", "lower_left"] | str = "upper_left", struct_ref: Any = None, **option_args: Any) -> None:

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    depth_values_arr = np.asarray(depth_values)
    color_values_arr = np.asarray(color_values)
    check_is_scalar_image(depth_values_arr)
    check_is_image4(color_values_arr)
    check_image_dims_compatible([depth_values_arr, color_values_arr])
    dimY = depth_values_arr.shape[0]
    dimX = depth_values_arr.shape[1]

    depth_values_flat = depth_values_arr.flatten().astype(np.float32)
    color_values_flat = color_values_arr.reshape(-1,4).astype(np.float32)

    q = struct_instance_ref.add_raw_color_alpha_render_image_quantity(name, dimX, dimY,
                                                                depth_values_flat, color_values_flat,
                                                                to_enum(psb.ImageOrigin,image_origin))


    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)
