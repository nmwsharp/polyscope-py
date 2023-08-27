import polyscope_bindings as psb

from polyscope.common import check_is_scalar_image, check_is_image3, check_is_image4, check_image_dims_compatible, process_scalar_args, process_color_args, process_image_args, process_render_image_args, process_quantity_args, process_implicit_render_args, check_all_args_processed

from polyscope.core import str_to_image_origin, str_to_datatype, str_to_implicit_render_mode, glm3


  
def render_implicit_surface(name, func, mode, camera_view=None, color=None, **option_args):

    # prep args
    mode_str = str_to_implicit_render_mode(mode)
    opts = psb.ImplicitRenderOpts()
    opts = process_implicit_render_args(opts, option_args)

    if camera_view is None:
        struct_ref = psb.get_global_floating_quantity_structure()
        cam = None
    else:
        struct_ref = camera_view
        cam = camera_view.bound_instance

    q = psb.render_implicit_surface_batch(name, func, mode_str, opts, cam)

    if color is not None:
        q.set_color(glm3(color))

    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def render_implicit_surface_color(name, func, func_color, mode, camera_view=None, **option_args):

    # prep args
    mode_str = str_to_implicit_render_mode(mode)
    opts = psb.ImplicitRenderOpts()
    opts = process_implicit_render_args(opts, option_args)

    if camera_view is None:
        struct_ref = psb.get_global_floating_quantity_structure()
        cam = None
    else:
        struct_ref = camera_view
        cam = camera_view.bound_instance

    q = psb.render_implicit_surface_color_batch(name, func, func_color, mode_str, opts, cam)

    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def render_implicit_surface_scalar(name, func, func_scalar, mode, camera_view=None, **option_args):

    # prep args
    mode_str = str_to_implicit_render_mode(mode)
    opts = psb.ImplicitRenderOpts()
    opts = process_implicit_render_args(opts, option_args)

    if camera_view is None:
        struct_ref = psb.get_global_floating_quantity_structure()
        cam = None
    else:
        struct_ref = camera_view
        cam = camera_view.bound_instance

    q = psb.render_implicit_surface_scalar_batch(name, func, func_scalar, mode_str, opts, cam)

    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    process_scalar_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

def render_implicit_surface_raw_color(name, func, func_color, mode, camera_view=None, **option_args):

    # prep args
    mode_str = str_to_implicit_render_mode(mode)
    opts = psb.ImplicitRenderOpts()
    opts = process_implicit_render_args(opts, option_args)

    if camera_view is None:
        struct_ref = psb.get_global_floating_quantity_structure()
        cam = None
    else:
        struct_ref = camera_view
        cam = camera_view.bound_instance

    q = psb.render_implicit_surface_raw_color_batch(name, func, func_color, mode_str, opts, cam)

    process_quantity_args(struct_ref, q, option_args)
    process_render_image_args(struct_ref, q, option_args)
    process_color_args(struct_ref, q, option_args)
    check_all_args_processed(struct_ref, q, option_args)

