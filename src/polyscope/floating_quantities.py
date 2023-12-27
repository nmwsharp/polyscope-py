import polyscope_bindings as psb

from polyscope.common import check_is_scalar_image, check_is_image3, check_is_image4, check_image_dims_compatible, process_scalar_args, process_color_args, process_image_args, process_render_image_args, process_quantity_args, check_all_args_processed
from polyscope.core import str_to_image_origin, str_to_datatype, glm3

import numpy as np

def _resolve_floating_struct_instance(struct_ref):
    if struct_ref is None:
        return psb.get_global_floating_quantity_structure()
    else:
        return struct_ref.bound_instance


def get_quantity_buffer(quantity_name, buffer_name):
    from polyscope.global_floating_quantity_structure import FloatingQuantityStructure

    floating_struct = FloatingQuantityStructure()
    return floating_struct.get_quantity_buffer(quantity_name, buffer_name)

  
def add_scalar_image_quantity(name, values, image_origin="upper_left", datatype="standard", struct_ref=None, **option_args):
    
    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(values)
    dimY = values.shape[0]
    dimX = values.shape[1]

    values_flat = values.flatten()
        
    q = struct_instance_ref.add_scalar_image_quantity(name, dimX, dimY, values_flat,              
                                             str_to_image_origin(image_origin), str_to_datatype(datatype))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_scalar_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def add_color_image_quantity(name, values, image_origin="upper_left", struct_ref=None, **option_args):
    
    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_image3(values)
    dimY = values.shape[0]
    dimX = values.shape[1]

    values_flat = values.reshape(-1,3)
        
    q = struct_instance_ref.add_color_image_quantity(name, dimX, dimY, values_flat,              
                                             str_to_image_origin(image_origin))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_color_alpha_image_quantity(name, values, image_origin="upper_left", struct_ref=None, **option_args):
    
    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_image4(values)
    dimY = values.shape[0]
    dimX = values.shape[1]

    values_flat = values.reshape(-1,4)
        
    q = struct_instance_ref.add_color_alpha_image_quantity(name, dimX, dimY, values_flat,              
                                             str_to_image_origin(image_origin))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

    
def add_depth_render_image_quantity(name, depth_values, normal_values, image_origin="upper_left", color=None, struct_ref=None, **option_args):

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(depth_values)
    if normal_values is None:
        normal_values = np.zeros((0,0,3))
    else:
        check_is_image3(normal_values)
        check_image_dims_compatible([depth_values, normal_values])
    dimY = depth_values.shape[0]
    dimX = depth_values.shape[1]

    depth_values_flat = depth_values.flatten()
    normal_values_flat = normal_values.reshape(-1,3)
        
    q = struct_instance_ref.add_depth_render_image_quantity(name, dimX, dimY, 
                                                            depth_values_flat, normal_values_flat,
                                                            str_to_image_origin(image_origin))
    
    if color is not None:
        q.set_color(glm3(color))

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_color_render_image_quantity(name, depth_values, normal_values, color_values, image_origin="upper_left", struct_ref=None, **option_args):

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(depth_values)
    check_is_image3(color_values)
    if normal_values is None:
        normal_values = np.zeros((0,0,3))
        check_image_dims_compatible([depth_values, color_values])
    else:
        check_is_image3(normal_values)
        check_image_dims_compatible([depth_values, normal_values, color_values])
    dimY = depth_values.shape[0]
    dimX = depth_values.shape[1]

    depth_values_flat = depth_values.flatten()
    normal_values_flat = normal_values.reshape(-1,3)
    color_values_flat = color_values.reshape(-1,3)
        
    q = struct_instance_ref.add_color_render_image_quantity(name, dimX, dimY, 
                                                            depth_values_flat, normal_values_flat, color_values_flat,
                                                            str_to_image_origin(image_origin))
    

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_scalar_render_image_quantity(name, depth_values, normal_values, scalar_values, image_origin="upper_left", struct_ref=None, **option_args):

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(depth_values)
    check_is_scalar_image(scalar_values)
    if normal_values is None:
        normal_values = np.zeros((0,0,3))
        check_image_dims_compatible([depth_values, scalar_values])
    else:
        check_is_image3(normal_values)
        check_image_dims_compatible([depth_values, normal_values, scalar_values])
    dimY = depth_values.shape[0]
    dimX = depth_values.shape[1]

    depth_values_flat = depth_values.flatten()
    normal_values_flat = normal_values.reshape(-1,3)
    scalar_values_flat = scalar_values.flatten()
        
    q = struct_instance_ref.add_scalar_render_image_quantity(name, dimX, dimY, 
                                                            depth_values_flat, normal_values_flat, scalar_values_flat,
                                                            str_to_image_origin(image_origin))
    

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_scalar_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)


def add_raw_color_render_image_quantity(name, depth_values, color_values, image_origin="upper_left", struct_ref=None, **option_args):

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(depth_values)
    check_is_image3(color_values)
    check_image_dims_compatible([depth_values, color_values])
    dimY = depth_values.shape[0]
    dimX = depth_values.shape[1]

    depth_values_flat = depth_values.flatten()
    color_values_flat = color_values.reshape(-1,3)
        
    q = struct_instance_ref.add_raw_color_render_image_quantity(name, dimX, dimY, 
                                                                depth_values_flat, color_values_flat,
                                                                str_to_image_origin(image_origin))
    

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def add_raw_color_alpha_render_image_quantity(name, depth_values, color_values, image_origin="upper_left", struct_ref=None, **option_args):

    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    check_is_scalar_image(depth_values)
    check_is_image4(color_values)
    check_image_dims_compatible([depth_values, color_values])
    dimY = depth_values.shape[0]
    dimX = depth_values.shape[1]

    depth_values_flat = depth_values.flatten()
    color_values_flat = color_values.reshape(-1,4)
        
    q = struct_instance_ref.add_raw_color_alpha_render_image_quantity(name, dimX, dimY, 
                                                                depth_values_flat, color_values_flat,
                                                                str_to_image_origin(image_origin))
    

    # process and act on additional arguments
    # note: each step modifies the option_args dict and removes processed args
    process_quantity_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)
