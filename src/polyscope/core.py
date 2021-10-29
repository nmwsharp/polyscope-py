import polyscope_bindings as psb

import os

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

### Structure management

def remove_all_structures():
    """Remove all structures from Polyscope"""
    psb.remove_all_structures()


### Screenshots
def screenshot(filename=None, transparent_bg=True):

    if filename is None:
        psb.screenshot(transparent_bg)
    else:
        psb.named_screenshot(filename, transparent_bg)

def set_screenshot_extension(ext):
    psb.set_screenshot_extension(ext)


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

def set_use_prefs_file(v):
    psb.set_use_prefs_file(v)

def set_always_redraw(v):
    psb.set_always_redraw(v)

def set_enable_render_error_checks(b):
    psb.set_enable_render_error_checks(b)

def set_autocenter_structures(b):
    psb.set_autocenter_structures(b)

def set_autoscale_structures(b):
    psb.set_autoscale_structures(b)

def set_navigation_style(s):
    psb.set_navigation_style(str_to_navigate_style(s))

def set_up_dir(d):
    psb.set_up_dir(str_to_updir(d))

### Camera controls

def reset_camera_to_home_view():
    psb.reset_camera_to_home_view()

def look_at(camera_location, target, fly_to=False):
    psb.look_at(glm3(camera_location), glm3(target), fly_to)

def look_at_dir(camera_location, target, up_dir, fly_to=False):
    psb.look_at_dir(glm3(camera_location), glm3(target), glm3(up_dir), fly_to)

def set_view_projection_mode(s):
    psb.set_view_projection_mode(str_to_projection_mode(s))

### Messages

def info(message):
    psb.info(message)

def warning(message, detail=""):
    psb.warning(message, detail)

def error(message):
    psb.error(message)

def terminating_error(message):
    psb.terminating_error(message)

## Ground plane and shadows
def set_ground_plane_mode(mode_str):
    psb.set_ground_plane_mode(str_to_ground_plane_mode(mode_str))

def set_ground_plane_height_factor(h, is_relative=True):
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

def add_scene_slice_plane():
    instance = psb.add_scene_slice_plane(False)
    return SlicePlane(instance)

def remove_last_scene_slice_plane():
    psb.remove_last_scene_slice_plane()


## Small utilities
def glm3(vals):
    return psb.glm_vec3(vals[0], vals[1], vals[2])

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

def str_to_navigate_style(s):
    d = {
        "turntable" : psb.NavigateStyle.turntable,
        "free" : psb.NavigateStyle.free,
        "planar" : psb.NavigateStyle.planar,
    }

    if s not in d:
        raise ValueError("Bad navigate style specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_projection_mode(s):
    d = {
        "perspective" : psb.ProjectionMode.perspective,
        "orthographic" : psb.ProjectionMode.orthographic,
    }

    if s not in d:
        raise ValueError("Bad projection mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_updir(s):
    d = {
        "x_up" : psb.UpDir.x_up,
        "neg_x_up" : psb.UpDir.neg_x_up,
        "y_up" : psb.UpDir.y_up,
        "neg_y_up" : psb.UpDir.neg_y_up,
        "z_up" : psb.UpDir.z_up,
        "neg_z_up" : psb.UpDir.neg_z_up,
    }

    if s not in d:
        raise ValueError("Bad up direction specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_datatype(s):
    d = {
        "standard" : psb.DataType.standard,
        "symmetric" : psb.DataType.symmetric,
        "magnitude" : psb.DataType.magnitude,
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
        "grid" : psb.ParamVizStyle.grid,
        "local_check" : psb.ParamVizStyle.local_check,
        "local_rad" : psb.ParamVizStyle.local_rad,
    }

    if s not in d:
        raise ValueError("Bad param viz style specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def str_to_back_face_policy(s):
    d = {
        "identical" : psb.BackFacePolicy.identical,
        "different" : psb.BackFacePolicy.different,
        "cull" : psb.BackFacePolicy.cull,
    }

    if s not in d:
        raise ValueError("Bad back face policy specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]

def back_face_policy_to_str(s):
    d = {
        psb.BackFacePolicy.identical : "identical" ,
        psb.BackFacePolicy.different : "different" ,
        psb.BackFacePolicy.cull : "cull" 
    }

    if s not in d:
        raise ValueError("Bad back face policy specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]
  

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

def str_to_transparency_mode(s):
    d = {
        "none": psb.TransparencyMode.none,
        "simple" : psb.TransparencyMode.simple,
        "pretty" : psb.TransparencyMode.pretty,
    }

    if s not in d:
        raise ValueError("Bad transparenccy mode specifier '{}', should be one of [{}]".format(s, 
            ",".join(["'{}'".format(x) for x in d.keys()])))

    return d[s]
