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

def set_autocenter_structures(b):
    psb.set_autocenter_structures(b)

def set_autoscale_structures(b):
    psb.set_autoscale_structures(b)

def set_navigation_style(s):
    psb.set_navigation_style(str_to_navigate_style(s))

def set_up_dir(d):
    psb.set_up_dir(str_to_updir(d))

def reset_camera_to_home_view():
    psb.reset_camera_to_home_view()

### Messages

def info(message):
    psb.info(message)

def warning(message, detail=""):
    psb.warning(message, detail)

def error(message):
    psb.error(message)

def terminating_error(message):
    psb.terminating_error(message)


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

def str_to_updir(s):
    d = {
        "x_up" : psb.UpDir.x_up,
        "y_up" : psb.UpDir.y_up,
        "z_up" : psb.UpDir.z_up,
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
