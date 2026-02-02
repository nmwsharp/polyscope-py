import polyscope_bindings as psb

from polyscope.core import glm2, glm3
from polyscope.enums import to_enum

from typing import TypedDict, Any, TYPE_CHECKING

if TYPE_CHECKING:
    from polyscope.core import CameraParameters


def check_is_scalar_image(values):
    if len(values.shape) != 2:
        raise ValueError(f"'values' should be a (height,width) array. Shape is {values.shape}.")


def check_is_image3(values):
    if len(values.shape) != 3 or values.shape[2] != 3:
        raise ValueError(f"'values' should be a (height,width,3) array. Shape is {values.shape}.")


def check_is_image4(values):
    if len(values.shape) != 3 or values.shape[2] != 4:
        raise ValueError(f"'values' should be a (height,width,4) array. Shape is {values.shape}.")


def check_image_dims_compatible(images):
    dimX = None
    dimY = None

    for img in images:
        if dimX is None:
            dimX = img.shape[0]
            dimY = img.shape[1]
        else:
            new_dimX = img.shape[0]
            new_dimY = img.shape[1]

            if (dimX, dimY) != (new_dimX, new_dimY):
                raise ValueError(
                    f"image inputs must have same resolution. One is {(dimX, dimY)} but another is {(new_dimX, new_dimY)}."
                )


def check_and_pop_arg(d, argname):
    if argname in d:
        return d.pop(argname)
    return None


# ==========================================================================
# ==== Basic Arguments
# ==========================================================================


class QuantityArgsBase(TypedDict, total=False):
    enabled: bool


# Process args, removing them from the dict if they are present
def process_quantity_args(structure, quantity, quantity_args):
    val = check_and_pop_arg(quantity_args, "enabled")
    if val is not None:
        quantity.set_enabled(val)


# ==========================================================================
# ==== Color Arguments
# ==========================================================================


class ColorArgsBase(TypedDict, total=False):
    is_premultiplied: bool


class ColorQuantityArgs(QuantityArgsBase, ColorArgsBase, total=False):
    pass


# Process args, removing them from the dict if they are present
def process_color_args(structure, quantity, color_args: ColorArgsBase):

    val = check_and_pop_arg(color_args, "is_premultiplied")
    if val is not None:
        quantity.set_is_premultiplied(val)


# ==========================================================================
# ==== Scalar Arguments
# ==========================================================================


class ScalarArgsBase(TypedDict, total=False):
    vminmax: tuple[float, float]
    cmap: str
    onscreen_colorbar_enabled: bool
    onscreen_colorbar_location: tuple[float, float]
    isolines_enabled: bool
    isoline_style: str
    isoline_period: float
    isoline_period_relative: bool
    isoline_width: float  # deprecated name
    isoline_width_relative: bool  # deprecated name
    isoline_darkness: float
    isoline_contour_thickness: float


class ScalarQuantityArgs(QuantityArgsBase, ScalarArgsBase, total=False):
    pass


# Process args, removing them from the dict if they are present
# def process_scalar_args(structure, quantity, scalar_args: ScalarArgs | MutableMapping[str, Any]):
def process_scalar_args(structure, quantity, scalar_args: ScalarArgsBase):
    val = check_and_pop_arg(scalar_args, "vminmax")
    if val is not None:
        quantity.set_map_range(val)

    val = check_and_pop_arg(scalar_args, "cmap")
    if val is not None:
        quantity.set_color_map(val)

    val = check_and_pop_arg(scalar_args, "onscreen_colorbar_enabled")
    if val is not None:
        quantity.set_onscreen_colorbar_enabled(val)

    val = check_and_pop_arg(scalar_args, "onscreen_colorbar_location")
    if val is not None:
        quantity.set_onscreen_colorbar_location(glm2(val))

    val = check_and_pop_arg(scalar_args, "isolines_enabled")
    if val is not None:
        quantity.set_isolines_enabled(val)

    val = check_and_pop_arg(scalar_args, "isoline_style")
    if val is not None:
        quantity.set_isoline_style(to_enum(psb.IsolineStyle, val))

    val = check_and_pop_arg(scalar_args, "isoline_period")
    val_relative = check_and_pop_arg(scalar_args, "isoline_period_relative")
    if val is not None:
        if val_relative is None:
            val_relative = False
        quantity.set_isoline_period(val, val_relative)

    # deprecated name
    val = check_and_pop_arg(scalar_args, "isoline_width")
    val_relative = check_and_pop_arg(scalar_args, "isoline_width_relative")
    if val is not None:
        if val_relative is None:
            val_relative = False
        quantity.set_isoline_width(val, val_relative)

    val = check_and_pop_arg(scalar_args, "isoline_darkness")
    if val is not None:
        quantity.set_isoline_darkness(val)

    val = check_and_pop_arg(scalar_args, "isoline_contour_thickness")
    if val is not None:
        quantity.set_isoline_contour_thickness(val)


# ==========================================================================
# ==== Vector Arguments
# ==========================================================================


class VectorArgsBase(TypedDict, total=False):
    length: float
    radius: float
    color: tuple[float, float, float]
    material: str


class VectorQuantityArgs(QuantityArgsBase, VectorArgsBase, total=False):
    pass


# Process args, removing them from the dict if they are present
def process_vector_args(structure, quantity, vector_args: VectorArgsBase):
    val = check_and_pop_arg(vector_args, "length")
    if val is not None:
        quantity.set_length(val, True)

    val = check_and_pop_arg(vector_args, "radius")
    if val is not None:
        quantity.set_radius(val, True)

    val = check_and_pop_arg(vector_args, "color")
    if val is not None:
        quantity.set_color(glm3(val))

    val = check_and_pop_arg(vector_args, "material")
    if val is not None:
        quantity.set_material(val)


# ==========================================================================
# ==== Parameterization Arguments
# ==========================================================================


class ParameterizationArgsBase(TypedDict, total=False):
    grid_colors: tuple[tuple[float, float, float], tuple[float, float, float]]
    checker_colors: tuple[tuple[float, float, float], tuple[float, float, float]]
    checker_size: float
    cmap: str
    island_labels: Any  # NDArray
    create_curve_network_from_seams: str
    viz_style: str


class ParameterizationQuantityArgs(QuantityArgsBase, ParameterizationArgsBase, total=False):
    pass


# Process args, removing them from the dict if they are present
def process_parameterization_args(
    structure, quantity, parameterization_args: ParameterizationArgsBase, is_surface=True
):
    val = check_and_pop_arg(parameterization_args, "grid_colors")
    if val is not None:
        quantity.set_grid_colors((glm3(val[0]), glm3(val[1])))

    val = check_and_pop_arg(parameterization_args, "checker_colors")
    if val is not None:
        quantity.set_checker_colors((glm3(val[0]), glm3(val[1])))

    val = check_and_pop_arg(parameterization_args, "checker_size")
    if val is not None:
        quantity.set_checker_size(val)

    val = check_and_pop_arg(parameterization_args, "cmap")
    if val is not None:
        quantity.set_color_map(val)

    if is_surface:
        val = check_and_pop_arg(parameterization_args, "island_labels")
        if val is not None:
            if len(val.shape) != 1:
                raise ValueError("'island_labels' should be an (N_faces,) numpy array")
            quantity.set_island_labels(val)

        val = check_and_pop_arg(parameterization_args, "create_curve_network_from_seams")
        if val is not None:
            quantity.create_curve_network_from_seams(val)

    # this has to come after island_labels above
    val = check_and_pop_arg(parameterization_args, "viz_style")
    if val is not None:
        viz_style_enum = to_enum(psb.ParamVizStyle, val)
        quantity.set_style(viz_style_enum)


# Process args, removing them from the dict if they are present
def process_texture_map_args(structure, quantity, texture_map_args):
    val = check_and_pop_arg(texture_map_args, "filter_mode")
    if val is not None:
        quantity.set_filter_mode(to_enum(psb.FilterMode, val))


# ==========================================================================
# ==== Volume Grid Arguments
# ==========================================================================


class VolumeGridArgsBase(TypedDict, total=False):
    enable_gridcube_viz: bool
    enable_isosurface_viz: bool
    isosurface_level: float
    isosurface_color: tuple[float, float, float]
    slice_planes_affect_isosurface: bool
    register_isosurface_as_mesh_with_name: str

class VolumeGridScalarQuantityArgs(ScalarQuantityArgs, VolumeGridArgsBase, total=False):
    pass

def process_volume_grid_scalar_args(
    structure: Any, quantity: Any, volume_grid_args: VolumeGridArgsBase, defined_on: str
) -> None:

    val = check_and_pop_arg(volume_grid_args, "enable_gridcube_viz")
    if val is not None:
        quantity.set_gridcube_viz_enabled(val)

    if defined_on == "nodes":
        val = check_and_pop_arg(volume_grid_args, "enable_isosurface_viz")
        if val is not None:
            quantity.set_isosurface_viz_enabled(val)

        val = check_and_pop_arg(volume_grid_args, "isosurface_level")
        if val is not None:
            quantity.set_isosurface_level(val)

        val = check_and_pop_arg(volume_grid_args, "isosurface_color")
        if val is not None:
            quantity.set_isosurface_color(glm3(val))

        val = check_and_pop_arg(volume_grid_args, "slice_planes_affect_isosurface")
        if val is not None:
            quantity.set_slice_planes_affect_isosurface(val)

        val = check_and_pop_arg(volume_grid_args, "register_isosurface_as_mesh_with_name")
        if val is not None:
            quantity.register_isosurface_as_mesh_with_name(val)


# ==========================================================================
# ==== Image Arguments
# ==========================================================================

class ImageArgsBase(TypedDict, total=False):
    show_fullscreen: bool
    show_in_imgui_window: bool
    show_in_camera_billboard: bool
    transparency: float

class ScalarImageArgs(ScalarQuantityArgs, ImageArgsBase, total=False):
    pass

class ColorImageArgs(ColorQuantityArgs, ImageArgsBase, total=False):
    pass

# Process args, removing them from the dict if they are present
def process_image_args(structure, quantity, image_args: ImageArgsBase):
    val = check_and_pop_arg(image_args, "show_fullscreen")
    if val is not None:
        quantity.set_show_fullscreen(val)

    val = check_and_pop_arg(image_args, "show_in_imgui_window")
    if val is not None:
        quantity.set_show_in_imgui_window(val)

    val = check_and_pop_arg(image_args, "show_in_camera_billboard")
    if val is not None:
        quantity.set_show_in_camera_billboard(val)

    val = check_and_pop_arg(image_args, "transparency")
    if val is not None:
        quantity.set_transparency(val)

class RenderImageArgsBase(TypedDict, total=False):
    transparency: float
    material: str
    allow_fullscreen_compositing: bool

class DepthRenderImageArgs(ColorQuantityArgs, RenderImageArgsBase, total=False):
    pass

class ScalarRenderImageArgs(ScalarQuantityArgs, RenderImageArgsBase, total=False):
    pass

class ColorRenderImageArgs(ColorQuantityArgs, RenderImageArgsBase, total=False):
    pass

# Process args, removing them from the dict if they are present
def process_render_image_args(structure, quantity, image_args: RenderImageArgsBase):
    val = check_and_pop_arg(image_args, "transparency")
    if val is not None:
        quantity.set_transparency(val)

    val = check_and_pop_arg(image_args, "material")
    if val is not None:
        quantity.set_material(val)

    val = check_and_pop_arg(image_args, "allow_fullscreen_compositing")
    if val is not None:
        quantity.set_allow_fullscreen_compositing(val)


# ==========================================================================
# ==== Implicit Render Arguments
# ==========================================================================

class ImplicitRenderArgs(TypedDict, total=False):
    camera_parameters: "CameraParameters"
    dim: tuple[int, int]
    subsample_factor: int
    miss_dist: float
    miss_dist_relative: bool
    hit_dist: float
    hit_dist_relative: bool
    step_factor: float
    normal_sample_eps: float
    step_size: float
    step_size_relative: bool
    n_max_steps: int

class ImplicitDepthRenderArgs(DepthRenderImageArgs, ImplicitRenderArgs, total=False):
    pass

class ImplicitColorRenderArgs(ColorRenderImageArgs, ImplicitRenderArgs, total=False):
    pass

class ImplicitScalarRenderArgs(ScalarRenderImageArgs, ImplicitRenderArgs, total=False):
    pass

# Process args, removing them from the dict if they are present
def process_implicit_render_args(opts, implicit_args):
    val = check_and_pop_arg(implicit_args, "camera_parameters")
    if val is not None:
        opts.cameraParameters = val.instance

    val = check_and_pop_arg(implicit_args, "dim")
    if val is not None:
        opts.dimX = int(val[0])
        opts.dimY = int(val[1])

    val = check_and_pop_arg(implicit_args, "subsample_factor")
    if val is not None:
        opts.subsampleFactor = int(val)

    val = check_and_pop_arg(implicit_args, "miss_dist")
    val_relative = check_and_pop_arg(implicit_args, "miss_dist_relative")
    if val is not None:
        if val_relative is None:
            val_relative = True
        opts.set_missDist(float(val), val_relative)

    val = check_and_pop_arg(implicit_args, "hit_dist")
    val_relative = check_and_pop_arg(implicit_args, "hit_dist_relative")
    if val is not None:
        if val_relative is None:
            val_relative = True
        opts.set_hitDist(float(val), val_relative)

    val = check_and_pop_arg(implicit_args, "step_factor")
    if val is not None:
        opts.stepFactor = float(val)

    val = check_and_pop_arg(implicit_args, "normal_sample_eps")
    if val is not None:
        opts.normalSampleEps = float(val)

    val = check_and_pop_arg(implicit_args, "step_size")
    val_relative = check_and_pop_arg(implicit_args, "step_size_relative")
    if val is not None:
        if val_relative is None:
            val_relative = True
        opts.set_stepSize(float(val), val_relative)

    val = check_and_pop_arg(implicit_args, "n_max_steps")
    if val is not None:
        opts.nMaxSteps = int(val)

    return opts


def check_all_args_processed(structure, quantity, args):
    for arg, val in args.items():
        raise ValueError(f"Polyscope: Unrecognized quantity keyword argument {arg}: {val}")
