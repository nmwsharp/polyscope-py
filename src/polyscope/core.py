import polyscope_bindings as psb
import polyscope.imgui as psim

import polyscope

import os

import numpy as np

### Basic setup and teardown 

def init(backend=""):
    """Initialize Polyscope"""

    cwd_before = os.getcwd() # see note below

    psb.init(backend)
   
    # NOTE: For some reason I do not understand, calling psb.init() changes the working directory, causing e.g. writes to relative file paths to write to unexpected locations afterwards.
    # As a simple workaround, we restore the CWD from before the call. Of course, this does not address the underlying cause, so there may be other subtle problems lurking.  
    os.chdir(cwd_before)


def show(forFrames=None):
    """Show the Polyscope GUI (blocks until UI is exited)"""
    if forFrames is None:
        psb.show()
    else:
        psb.show(forFrames)

def unshow():
    psb.unshow()

def window_requests_close():
    return psb.window_requests_close()

def check_initialized():
    psb.check_initialized()

def is_initialized():
    return psb.is_initialized()

def frame_tick():
    psb.frame_tick()

def shutdown(allow_mid_frame_shutdown=False):
    psb.shutdown(allow_mid_frame_shutdown)


### Render engine

def get_render_engine_backend_name():
    return psb.get_render_engine_backend_name()

def is_headless():
    return psb.is_headless()

def set_allow_headless_backends(b):
    return psb.set_allow_headless_backends(b)

### Structure management

def remove_all_structures():
    """Remove all structures from Polyscope"""
    psb.remove_all_structures()


### Screenshots
def screenshot(filename=None, transparent_bg=True, include_UI=False):

    opts = psb.ScreenshotOptions()
    opts.include_UI = include_UI
    opts.transparent_background = transparent_bg

    if filename is None:
        psb.screenshot(opts)
    else:
        psb.named_screenshot(filename, opts)

def set_screenshot_extension(ext):
    psb.set_screenshot_extension(ext)


def screenshot_to_buffer(transparent_bg=True, vertical_flip=True, include_UI=False):

    opts = psb.ScreenshotOptions()
    opts.include_UI = include_UI
    opts.transparent_background = transparent_bg

    buff = psb.screenshot_to_buffer(opts)
    w, h = get_buffer_size()
    buff = buff.reshape(h, w, 4)
    if(vertical_flip):
        buff = buff[::-1,:,:]
    return buff

### Small options

def set_program_name(name):
    psb.set_program_name(name)

def set_verbosity(v):
    psb.set_verbosity(v)

def set_print_prefix(p):
    psb.set_print_prefix(p)

def set_errors_throw_exceptions(val):
    psb.set_errors_throw_exceptions(val)

def set_max_fps(f):
    psb.set_max_fps(f)

def set_enable_vsync(b):
    psb.set_enable_vsync(b)

def set_use_prefs_file(v):
    psb.set_use_prefs_file(v)

def set_do_default_mouse_interaction(v):
    psb.set_do_default_mouse_interaction(v)

def request_redraw():
    psb.request_redraw()

def get_redraw_requested():
    return psb.get_redraw_requested()

def set_always_redraw(v):
    psb.set_always_redraw(v)

def set_frame_tick_limit_fps_mode(v):
    psb.set_frame_tick_limit_fps_mode(str_to_enum(v, psb.LimitFPSMode))

def set_enable_render_error_checks(b):
    psb.set_enable_render_error_checks(b)

def set_egl_device_index(i):
    psb.set_egl_device_index(i)

def set_autocenter_structures(b):
    psb.set_autocenter_structures(b)

def set_autoscale_structures(b):
    psb.set_autoscale_structures(b)

def set_ui_scale(s):
    psb.set_ui_scale(s)

def get_ui_scale():
    return psb.get_ui_scale()

def set_build_gui(b):
    psb.set_build_gui(b)

def set_user_gui_is_on_right_side(b):
    psb.set_user_gui_is_on_right_side(b)

def set_build_default_gui_panels(b):
    psb.set_build_default_gui_panels(b)

def set_render_scene(b):
    psb.set_render_scene(b)

def set_open_imgui_window_for_user_callback(b):
    psb.set_open_imgui_window_for_user_callback(b)

def set_invoke_user_callback_for_nested_show(b):
    psb.set_invoke_user_callback_for_nested_show(b)

def set_give_focus_on_show(b):
    psb.set_give_focus_on_show(b)

def set_hide_window_after_show(b):
    psb.set_hide_window_after_show(b)

def set_warn_for_invalid_values(b):
    psb.set_warn_for_invalid_values(b)

def set_display_message_popups(b):
    psb.set_display_message_popups(b)

def set_navigation_style(s):
    psb.set_navigation_style(str_to_navigate_style(s))
def get_navigation_style():
    return navigate_style_to_str(psb.get_navigation_style());

def set_up_dir(d):
    psb.set_up_dir(str_to_updir(d))
def get_up_dir():
    return updir_to_str(psb.get_up_dir())

def set_front_dir(d):
    psb.set_front_dir(str_to_frontdir(d))
def get_front_dir():
    return frontdir_to_str(psb.get_front_dir())

def set_vertical_fov_degrees(f):
    psb.set_vertical_fov_degrees(f)
def get_vertical_fov_degrees():
    return psb.get_vertical_fov_degrees()

def get_aspect_ratio_width_over_height():
    return psb.get_aspect_ratio_width_over_height()

### Scene extents

def set_automatically_compute_scene_extents(b):
    psb.set_automatically_compute_scene_extents(b)

def set_length_scale(s):
    psb.set_length_scale(s)

def get_length_scale():
    return psb.get_length_scale()

def set_bounding_box(low, high):
    psb.set_bounding_box(glm3(low), glm3(high))

def get_bounding_box():
    low, high = psb.get_bounding_box()
    return np.array(low.as_tuple()), np.array(high.as_tuple())

### Camera controls

def reset_camera_to_home_view():
    psb.reset_camera_to_home_view()

def look_at(camera_location, target, fly_to=False):
    psb.look_at(glm3(camera_location), glm3(target), fly_to)

def look_at_dir(camera_location, target, up_dir, fly_to=False):
    psb.look_at_dir(glm3(camera_location), glm3(target), glm3(up_dir), fly_to)

def set_view_projection_mode(s):
    psb.set_view_projection_mode(str_to_projection_mode(s))

def set_window_size(width, height):
    width = int(width)
    height = int(height)
    psb.set_window_size(width, height)

def get_window_size():
    return psb.get_window_size()

def get_buffer_size():
    return psb.get_buffer_size()

def set_window_resizable(is_resizable):
    psb.set_window_resizable(is_resizable)

def get_window_resizable():
    return psb.get_window_resizable()

def set_view_from_json(json_str, fly_to=False):
    psb.set_view_from_json(json_str, fly_to)

def get_view_as_json():
    return psb.get_view_as_json()

def screen_coords_to_world_ray(screen_coords):
    return np.array(psb.screen_coords_to_world_ray(glm2(screen_coords)).as_tuple())

# deprecated! use query_pick_at_screen_coords
def screen_coords_to_world_position(screen_coords):
    pick_result = pick(screen_coords=screen_coords)
    return pick_result.position

def set_background_color(c):
    if len(c) == 3: c = (c[0], c[1], c[2], 1.0)
    psb.set_background_color(glm4(c))

def get_background_color():
    return psb.get_background_color()

def get_view_camera_parameters():
    return CameraParameters(instance=psb.get_view_camera_parameters())

def set_view_camera_parameters(params):
    if not isinstance(params, CameraParameters): raise ValueError("must pass CameraParameters")
    psb.set_view_camera_parameters(params.instance)

def get_view_buffer_resolution():
    return CameraParameters(instance=psb.get_view_camera_parameters())

def set_camera_view_matrix(mat):
    mat = np.asarray(mat)
    if mat.shape != (4,4): raise ValueError("mat should be a 4x4 numpy matrix")
    psb.set_camera_view_matrix(mat)

def get_camera_view_matrix():
    return psb.get_camera_view_matrix()

def set_view_center(pos, fly_to=False):
    pos = glm3(pos)
    psb.set_view_center(pos, fly_to)

def get_view_center():
    return np.array(psb.get_view_center().as_tuple())

### "Advanced" UI management

def build_polyscope_gui():
    psb.build_polyscope_gui()

def build_structure_gui():
    psb.build_structure_gui()

def build_pick_gui():
    psb.build_pick_gui()

def build_user_gui_and_invoke_callback():
    psb.build_user_gui_and_invoke_callback()


### Messages

def info(message, verbosity=0):
    # only printed if verbosity > vebosityLevel
    psb.info(verbosity, message)

def warning(message, detail=""):
    psb.warning(message, detail)

def error(message):
    psb.error(message)

def terminating_error(message):
    psb.terminating_error(message)

### Callback
def set_user_callback(func):
    psb.set_user_callback(func)

def clear_user_callback():
    psb.clear_user_callback()

### Picking

def pick(*, screen_coords=None, buffer_inds=None):
    if(screen_coords is not None and buffer_inds is not None):
        raise ValueError("pass args one of screen_coords OR buffer_inds, but not both")
    if(screen_coords is None and buffer_inds is None):
        raise ValueError("must pass args one of screen_coords or buffer_inds")

    if(screen_coords is not None):
        raw_result = psb.pick_at_screen_coords(glm2(screen_coords))
    if(buffer_inds is not None):
        raw_result = psb.pick_at_buffer_inds(glm2i(buffer_inds))

    return PickResult(raw_result)

def have_selection():
    return psb.have_selection()

def get_selection():
    return PickResult(psb.get_selection())

def reset_selection():
    psb.reset_selection()

class PickResult:

    def __init__(self, bound_pick_result):

        self.raw_result = bound_pick_result

        # translate most properties
        self.is_hit = bound_pick_result.is_hit
        self.structure_type_name = bound_pick_result.structure_type
        self.structure_name = bound_pick_result.structure_name
        self.quantity_name = bound_pick_result.quantity_name
        self.screen_coords = bound_pick_result.screen_coords.as_tuple()
        self.buffer_inds = bound_pick_result.buffer_inds.as_tuple()
        self.position = np.array(bound_pick_result.position.as_tuple())
        self.depth = bound_pick_result.depth
        self.local_index = bound_pick_result.local_index

        # additional per-structure data, such as barycentric coordinates 
        # if its a triangle in a mesh
        self.structure_data = {}

        self.resolve_additional_data()

    def resolve_additional_data(self):
        # resolve data from various types
        
        if self.structure_type_name == "Point Cloud":
            polyscope.point_cloud.get_point_cloud(self.structure_name).append_pick_data(self)
        
        if self.structure_type_name == "Curve Network":
            polyscope.curve_network.get_curve_network(self.structure_name).append_pick_data(self)
        
        if self.structure_type_name == "Surface Mesh":
            polyscope.surface_mesh.get_surface_mesh(self.structure_name).append_pick_data(self)
        
        if self.structure_type_name == "Volume Mesh":
            polyscope.volume_mesh.get_volume_mesh(self.structure_name).append_pick_data(self)
        
        if self.structure_type_name == "Volume Grid":
            polyscope.volume_grid.get_volume_grid(self.structure_name).append_pick_data(self)

    def __str__(self):
            return f"""
PickResult(
    is_hit={self.is_hit},
    structure_type_name={self.structure_type_name},
    structure_name={self.structure_name},
    quantity_name={self.quantity_name},
    screen_coords={self.screen_coords},
    buffer_inds={self.buffer_inds},
    position={self.position},
    depth={self.depth},
    local_index={self.local_index},
    structure_data={self.structure_data}
)
"""

## Ground plane and shadows
def set_ground_plane_mode(mode_str):# 
    psb.set_ground_plane_mode(str_to_ground_plane_mode(mode_str))

def set_ground_plane_height_mode(mode_str):
    psb.set_ground_plane_height_mode(str_to_ground_plane_height_mode(mode_str))

def set_ground_plane_height(h):
    set_ground_plane_height_mode('manual')
    psb.set_ground_plane_height(h)

def set_ground_plane_height_factor(h, is_relative=True):
    set_ground_plane_height_mode('automatic')
    psb.set_ground_plane_height_factor(h, is_relative)

def set_shadow_blur_iters(n):
    psb.set_shadow_blur_iters(n)

def set_shadow_darkness(val):
    psb.set_shadow_darkness(val)

## Ground plane and shadows
def set_transparency_mode(mode_str):
    psb.set_transparency_mode(str_to_transparency_mode(mode_str))

def set_transparency_render_passes(n):
    psb.set_transparency_render_passes(n)

## Rendering
def set_SSAA_factor(n):
    psb.set_SSAA_factor(n)

## Groups

class Group:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use add_group() instead
    def __init__(self, instance):
        # Wrap an existing instance
        self.bound_group = instance
    
    def get_name(self):
        return self.bound_group.name
    
    def add_child_group(self, child_group):
        if isinstance(child_group, str):
            self.bound_group.add_child_group(get_group(child_group).bound_group)
        else:
            self.bound_group.add_child_group(child_group.bound_group)

    def add_child_structure(self, child_structure):
        self.bound_group.add_child_structure(child_structure.bound_instance)
    
    def remove_child_group(self, child_group):
        if isinstance(child_group, str):
            self.bound_group.remove_child_group(get_group(child_group).bound_group)
        else:
            self.bound_group.remove_child_group(child_group.bound_group)

    def remove_child_structure(self, child_structure):
        self.bound_group.remove_child_structure(child_structure.bound_instance)
    
    def set_enabled(self, new_val):
        self.bound_group.set_enabled(new_val)
    
    def set_show_child_details(self, new_val):
        self.bound_group.set_show_child_details(new_val)
    
    def set_hide_descendants_from_structure_lists(self, new_val):
        self.bound_group.set_hide_descendants_from_structure_lists(new_val)
    
    def get_child_structure_names(self):
        # Only returns first-level children, does not recurse
        return self.bound_group.get_child_structure_names()
    
    def get_child_group_names(self):
        # Only returns first-level children, does not recurse
        return self.bound_group.get_child_group_names()

def create_group(name):
    return Group(psb.create_group(name))

def get_group(name):
    return Group(psb.get_group(name))

def remove_group(group, error_if_absent=True):
    # accept either a string or a group ref as input
    if isinstance(group, str):
        psb.remove_group(group, error_if_absent)
    else:
        psb.remove_group(group.get_name(), error_if_absent)

def remove_all_groups():
    psb.remove_all_groups()


## Low-level internals access
# (warning, 'advanced' users only, may change)
def get_final_scene_color_texture_native_handle():
    return psb.get_final_scene_color_texture_native_handle()

## Slice planes

class SlicePlane:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use add_scene_slice_plane() instead
    def __init__(self, instance):

        # Wrap an existing instance
        self.bound_slice_plane = instance
    
    def get_name(self):
        return self.bound_slice_plane.name

    def set_pose(self, plane_position, plane_normal):
        self.bound_slice_plane.set_pose(glm3(plane_position), glm3(plane_normal))
    
    def set_active(self, val):
        self.bound_slice_plane.set_active(val)
    
    def get_active(self):
        return self.bound_slice_plane.get_active()
    
    def set_draw_plane(self, val):
        self.bound_slice_plane.set_draw_plane(val)
    
    def get_draw_plane(self):
        return self.bound_slice_plane.get_draw_plane()
    
    def set_draw_widget(self, val):
        self.bound_slice_plane.set_draw_widget(val)
    
    def get_draw_widget(self):
        return self.bound_slice_plane.get_draw_widget()
    
    def set_volume_mesh_to_inspect(self, val):
        return self.bound_slice_plane.set_volume_mesh_to_inspect(val)

    def get_volume_mesh_to_inspect(self):
        return self.bound_slice_plane.get_volume_mesh_to_inspect()

def add_scene_slice_plane():
    instance = psb.add_scene_slice_plane(False)
    return SlicePlane(instance)

def remove_last_scene_slice_plane():
    psb.remove_last_scene_slice_plane()

### Camera Parameters

class CameraIntrinsics:

    def __init__(self, fov_vertical_deg=None, fov_horizontal_deg=None, aspect=None, instance=None):

        if instance is not None:
            self.instance = instance
        elif fov_vertical_deg is not None and aspect is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_vertical_and_aspect(float(fov_vertical_deg), float(aspect))
        elif fov_horizontal_deg is not None and aspect is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_horizontal_and_aspect(float(fov_horizontal_deg), float(aspect))
        elif fov_vertical_deg is not None and fov_horizontal_deg is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_horizontal_and_vertical(float(fov_horizontal_deg), float(fov_vertical_deg))
        else:
            raise ValueError("bad arguments, at least two of (fov_vertical_deg,fov_horizontal_deg,aspect) must be given and non-None")

class CameraExtrinsics:

    def __init__(self, root=None, look_dir=None, up_dir=None, mat=None, instance=None):
        
        if instance is not None:
            self.instance = instance

        elif mat is not None:
            mat = np.asarray(mat)
            if mat.shape != (4,4): raise ValueError("mat should be a 4x4 numpy matrix")
            self.instance = psb.CameraExtrinsics.from_matrix(mat)

        elif (root is not None) and (look_dir is not None) and (up_dir is not None):

            root = np.asarray(root)
            look_dir = np.asarray(look_dir)
            up_dir = np.asarray(up_dir)
            self.instance = psb.CameraExtrinsics.from_vectors(root, look_dir, up_dir)
        
        else:
            raise ValueError("bad arguments, must pass non-None (root,look_dir,up_dir) or non-None mat")

class CameraParameters:

    def __init__(self, intrinsics=None, extrinsics=None, instance=None):
        if instance is not None:
            self.instance = instance
        else:
            self.instance = psb.CameraParameters(intrinsics.instance, extrinsics.instance)

    # getters
    def get_intrinsics(self): return CameraIntrinsics(instance=self.instance.get_intrinsics())
    def get_extrinsics(self): return CameraExtrinsics(instance=self.instance.get_extrinsics())
    def get_T(self): return self.instance.get_T()
    def get_R(self): return self.instance.get_R()
    def get_view_mat(self): return self.instance.get_view_mat() # same as get_E()
    def get_E(self): return self.instance.get_E()
    def get_position(self): return self.instance.get_position()
    def get_look_dir(self): return self.instance.get_look_dir()
    def get_up_dir(self): return self.instance.get_up_dir()
    def get_right_dir(self): return self.instance.get_right_dir()
    def get_camera_frame(self): return self.instance.get_camera_frame()
    def get_fov_vertical_deg(self): return self.instance.get_fov_vertical_deg()
    def get_aspect(self): return self.instance.get_aspect()

    def generate_camera_rays(self, dims, image_origin='upper_left'): 
        out_rays = self.instance.generate_camera_rays(
                int(dims[0]), int(dims[1]),
                str_to_image_origin(image_origin)
            )
        return out_rays.reshape(dims[1], dims[0], 3)

    def generate_camera_ray_corners(self): 
        return self.instance.generate_camera_ray_corners()


## Small utilities
def glm2(vals):
    return psb.glm_vec2(vals[0], vals[1])
def glm2i(vals):
    return psb.glm_ivec2(vals[0], vals[1])
def glm3u(vals):
    return psb.glm_uvec3(vals[0], vals[1], vals[2])
def glm3(vals):
    return psb.glm_vec3(vals[0], vals[1], vals[2])
def glm4(vals):
    return psb.glm_vec4(vals[0], vals[1], vals[2], vals[3])
def degrees(val):
    return 180.*val / np.PI
def radians(val):
    return np.PI * val / 180.

### Materials

def load_static_material(mat_name, filename):
    psb.load_static_material(mat_name, filename)

def load_blendable_material(mat_name, filenames=None, filename_base=None, filename_ext=None):

    # list of names
    if filenames is not None:
        if filename_base is not None or filename_ext is not None:
            raise ValueError("`filenames` was specified, `filename_base`/`filename_ext` should NOT be specified")

        psb.load_blendable_material_explicit(mat_name, filenames)

    # base/ext pair
    if filename_base is not None and filename_ext is not None:
        if filenames is not None:
            raise ValueError("`filename_base`/`filename_ext` were specified, `filenames` should NOT be specified")

        psb.load_blendable_material_baseext(mat_name, filename_base, filename_ext)


### Colormaps

def load_color_map(cmap_name, filename):
    psb.load_color_map(cmap_name, filename)

## String-to-enum translation

# General case
# TODO: gradually replace the enum-specific methods below with this, 
# ensuring each doesn't have any special breakage
def str_to_enum(s, enum):
    if s in enum.__members__: return enum.__members__[s]
    enum_val_names = [x for x in enum.__members__]
    raise ValueError(f"Bad specifier '{s}' for {enum.__name__}, should be one of [{','.join(enum_val_names)}]")

def enum_to_str(enum_val):
    return enum_val.name

## Per-enum maps

d_navigate = {
    "turntable" : psb.NavigateStyle.turntable,
    "free" : psb.NavigateStyle.free,
    "planar" : psb.NavigateStyle.planar,
    "none" : psb.NavigateStyle.none,
    "first_person" : psb.NavigateStyle.first_person,
}
def str_to_navigate_style(s):

    if s not in d_navigate:
        raise ValueError("Bad navigate style specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_navigate.keys()])))

    return d_navigate[s]
def navigate_style_to_str(val):
    for k,v in d_navigate.items():
        if v == val:
            return k

    raise ValueError("Bad navigate style specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_navigate.values()])))


def str_to_projection_mode(s):
    d = {
        "perspective" : psb.ProjectionMode.perspective,
        "orthographic" : psb.ProjectionMode.orthographic,
    }

    if s not in d:
        raise ValueError("Bad projection mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]


d_updir = {
    "x_up" : psb.UpDir.x_up,
    "neg_x_up" : psb.UpDir.neg_x_up,
    "y_up" : psb.UpDir.y_up,
    "neg_y_up" : psb.UpDir.neg_y_up,
    "z_up" : psb.UpDir.z_up,
    "neg_z_up" : psb.UpDir.neg_z_up,
}
def str_to_updir(s):
    if s not in d_updir:
        raise ValueError("Bad up direction specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_updir.keys()])))

    return d_updir[s]

def updir_to_str(val):
    for k,v in d_updir.items():
        if v == val:
            return k

    raise ValueError("Bad up direction specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_updir.values()])))


d_frontdir = {
    "x_front" : psb.FrontDir.x_front,
    "neg_x_front" : psb.FrontDir.neg_x_front,
    "y_front" : psb.FrontDir.y_front,
    "neg_y_front" : psb.FrontDir.neg_y_front,
    "z_front" : psb.FrontDir.z_front,
    "neg_z_front" : psb.FrontDir.neg_z_front,
}
def str_to_frontdir(s):

    if s not in d_frontdir:
        raise ValueError("Bad front direction specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_frontdir.keys()])))

    return d_frontdir[s]
def frontdir_to_str(val):
    for k,v in d_frontdir.items():
        if v == val:
            return k

    raise ValueError("Bad front direction specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_frontdir.values()])))

def str_to_datatype(s):
    d = {
        "standard" : psb.DataType.standard,
        "symmetric" : psb.DataType.symmetric,
        "magnitude" : psb.DataType.magnitude,
        "categorical" : psb.DataType.categorical,
    }

    if s not in d:
        raise ValueError("Bad datatype specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_vectortype(s):
    d = {
        "standard" : psb.VectorType.standard,
        "ambient" : psb.VectorType.ambient,
    }

    if s not in d:
        raise ValueError("Bad vectortype specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_param_coords_type(s):
    d = {
        "unit" : psb.ParamCoordsType.unit,
        "world" : psb.ParamCoordsType.world,
    }

    if s not in d:
        raise ValueError("Bad param coords type specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_param_viz_style(s):
    d = {
        "checker" : psb.ParamVizStyle.checker,
        "checker_islands" : psb.ParamVizStyle.checker_islands,
        "grid" : psb.ParamVizStyle.grid,
        "local_check" : psb.ParamVizStyle.local_check,
        "local_rad" : psb.ParamVizStyle.local_rad,
    }

    if s not in d:
        raise ValueError("Bad param viz style specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

# Back face policy to/from string
d_back_face_policy = {
    "identical" : psb.BackFacePolicy.identical,
    "different" : psb.BackFacePolicy.different,
    "custom" : psb.BackFacePolicy.custom,
    "cull" : psb.BackFacePolicy.cull,
}

def str_to_back_face_policy(s):

    if s not in d_back_face_policy:
        raise ValueError("Bad back face policy specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_back_face_policy.keys()])))

    return d_back_face_policy[s]

def back_face_policy_to_str(val):

    for k,v in d_back_face_policy.items():
        if v == val:
            return k

    raise ValueError("Bad back face policy specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_back_face_policy.values()])))
  

def str_to_ground_plane_mode(s):
    d = {
        "none": psb.GroundPlaneMode.none,
        "tile" : psb.GroundPlaneMode.tile,
        "tile_reflection" : psb.GroundPlaneMode.tile_reflection,
        "shadow_only" : psb.GroundPlaneMode.shadow_only
    }

    if s not in d:
        raise ValueError("Bad ground plane mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_ground_plane_height_mode(s):
    d = {
        "automatic": psb.GroundPlaneHeightMode.automatic,
        "manual" : psb.GroundPlaneHeightMode.manual,
    }

    if s not in d:
        raise ValueError("Bad ground plane height mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_transparency_mode(s):
    d = {
        "none": psb.TransparencyMode.none,
        "simple" : psb.TransparencyMode.simple,
        "pretty" : psb.TransparencyMode.pretty,
    }

    if s not in d:
        raise ValueError("Bad transparency mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

# Point render mode to/from string
d_point_render_mode = {
        "sphere" : psb.PointRenderMode.sphere,
        "quad" : psb.PointRenderMode.quad,
    }

def str_to_point_render_mode(s):

    if s not in d_point_render_mode:
        raise ValueError("Bad point render mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_point_render_mode.keys()])))

    return d_point_render_mode[s]

def point_render_mode_to_str(val):

    for k,v in d_point_render_mode.items():
        if v == val:
            return k

    raise ValueError("Bad point render mode specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_point_render_mode.values()])))

# Filter mode to/from string
d_filter_mode = {
        "linear" : psb.FilterMode.linear,
        "nearest" : psb.FilterMode.nearest,
    }

def str_to_filter_mode(s):

    if s not in d_filter_mode:
        raise ValueError("Bad filter mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_filter_mode.keys()])))

    return d_filter_mode[s]

def filter_mode_to_str(val):

    for k,v in d_filter_mode.items():
        if v == val:
            return k

    raise ValueError("Bad filter mode specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_filter_mode.values()])))

# Image origin to/from string
d_image_origin = {
        "lower_left" : psb.ImageOrigin.lower_left,
        "upper_left" : psb.ImageOrigin.upper_left,
    }

def str_to_image_origin(s):

    if s not in d_image_origin:
        raise ValueError("Bad image origin specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_image_origin.keys()])))

    return d_image_origin[s]

def image_origin_to_str(val):

    for k,v in d_image_origin.items():
        if v == val:
            return k

    raise ValueError("Bad image origin specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_image_origin.values()])))

# Shade style to/from string
d_mesh_shade_style = {
        "smooth" : psb.MeshShadeStyle.smooth,
        "flat" : psb.MeshShadeStyle.flat,
        "tri_flat" : psb.MeshShadeStyle.tri_flat,
    }

def str_to_mesh_shade_style(s):

    if s not in d_mesh_shade_style:
        raise ValueError("Bad specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_mesh_shade_style.keys()])))

    return d_mesh_shade_style[s]

def mesh_shade_style_to_str(val):

    for k,v in d_mesh_shade_style.items():
        if v == val:
            return k
    raise ValueError("Bad specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_mesh_shade_style.values()])))

# Isoline style to/from string
d_isoline_style = {
        "stripe" : psb.IsolineStyle.stripe,
        "contour" : psb.IsolineStyle.contour,
    }

def str_to_isoline_style(s):

    if s not in d_isoline_style:
        raise ValueError("Bad specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_isoline_style.keys()])))

    return d_isoline_style[s]

def isoline_style_to_str(val):

    for k,v in d_isoline_style.items():
        if v == val:
            return k

    raise ValueError("Bad specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_isoline_style.values()])))

# Implicit render mode to/from string
d_implicit_render_mode = {
        "fixed_step" : psb.ImplicitRenderMode.fixed_step,
        "sphere_march" : psb.ImplicitRenderMode.sphere_march,
    }

def str_to_implicit_render_mode(s):

    if s not in d_implicit_render_mode:
        raise ValueError("Bad specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d_implicit_render_mode.keys()])))

    return d_implicit_render_mode[s]

def implicit_render_mode_to_str(val):

    for k,v in d_implicit_render_mode.items():
        if v == val:
            return k

    raise ValueError("Bad specifier '{}', should be one of [{}]".format(val, 
        ",".join(["'{}'".format(x) for x in d_implicit_render_mode.values()])))

# Mapping for some common characters, to support our legacy get_key_code() function.
# The more proper solution is to use the ImGui enum names directly like psim.ImGuiKey_W; only a subset of them are mapped get_key_code() and the dict below.
# The full list can be found in the ImGui source, or in this issue https://github.com/ocornut/imgui/issues/4921
keycode_dict = {
        ' ' : psim.ImGuiKey_Space,
        '0' : psim.ImGuiKey_0,
        '1' : psim.ImGuiKey_1,
        '2' : psim.ImGuiKey_2,
        '3' : psim.ImGuiKey_3,
        '4' : psim.ImGuiKey_4,
        '5' : psim.ImGuiKey_5,
        '6' : psim.ImGuiKey_6,
        '7' : psim.ImGuiKey_7,
        '8' : psim.ImGuiKey_8,
        '9' : psim.ImGuiKey_9,
        'A' : psim.ImGuiKey_A,
        'B' : psim.ImGuiKey_B,
        'C' : psim.ImGuiKey_C,
        'D' : psim.ImGuiKey_D,
        'E' : psim.ImGuiKey_E,
        'F' : psim.ImGuiKey_F,
        'G' : psim.ImGuiKey_G,
        'H' : psim.ImGuiKey_H,
        'I' : psim.ImGuiKey_I,
        'J' : psim.ImGuiKey_J,
        'K' : psim.ImGuiKey_K,
        'L' : psim.ImGuiKey_L,
        'M' : psim.ImGuiKey_M,
        'N' : psim.ImGuiKey_N,
        'O' : psim.ImGuiKey_O,
        'P' : psim.ImGuiKey_P,
        'Q' : psim.ImGuiKey_Q,
        'R' : psim.ImGuiKey_R,
        'S' : psim.ImGuiKey_S,
        'T' : psim.ImGuiKey_T,
        'U' : psim.ImGuiKey_U,
        'V' : psim.ImGuiKey_V,
        'W' : psim.ImGuiKey_W,
        'X' : psim.ImGuiKey_X,
        'Y' : psim.ImGuiKey_Y,
        'Z' : psim.ImGuiKey_Z,
        "'" : psim.ImGuiKey_Apostrophe,
        ',' : psim.ImGuiKey_Comma,
        '-' : psim.ImGuiKey_Minus,
        '.' : psim.ImGuiKey_Period,
        '/' : psim.ImGuiKey_Slash,
        ';' : psim.ImGuiKey_Semicolon,
        '=' : psim.ImGuiKey_Equal,
        '[' : psim.ImGuiKey_LeftBracket,
        '\\' : psim.ImGuiKey_Backslash,
        ']' : psim.ImGuiKey_RightBracket
    }

def get_key_code(k):

    if(len(k) != 1): raise ValueError("pass a single character")
    if k.islower():
        k = k.upper()

    if k not in keycode_dict:
        raise ValueError(f"character {k} not in keycode mapping. Keys which have multiple characters on them, try the other character (like @ vs 2). Alternately, don't use this function, look up the appropriate enum from the imgui documentation, use them like polyscope.imgui.ImGuiKey_Semicolon")

    return keycode_dict[k]
