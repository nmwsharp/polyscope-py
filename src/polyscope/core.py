import polyscope_bindings as psb
import polyscope.imgui as psim

import polyscope
from polyscope.enums import to_enum, from_enum, Backend

import os

import numpy as np

from typing import Literal, Tuple
from numpy.typing import NDArray, ArrayLike
from collections.abc import Sequence

### Basic setup and teardown


def init(backend: Literal["auto", "openGL3_glfw", "openGL3_egl", "openGL_mock"] = "auto") -> None:
    """Initialize Polyscope"""

    cwd_before = os.getcwd()  # see note below

    # uses the arg checking functionality from the enum
    psb.init(from_enum(to_enum(Backend, backend)))

    # NOTE: For some reason I do not understand, calling psb.init() changes the working directory, causing e.g. writes to relative file paths to write to unexpected locations afterwards.
    # As a simple workaround, we restore the CWD from before the call. Of course, this does not address the underlying cause, so there may be other subtle problems lurking.
    os.chdir(cwd_before)


def show(forFrames: int | None = None):
    """Show the Polyscope GUI (blocks until UI is exited)"""
    if forFrames is None:
        psb.show()
    else:
        psb.show(forFrames)


def unshow() -> None:
    psb.unshow()


def window_requests_close() -> bool:
    return psb.window_requests_close()


def check_initialized() -> None:
    psb.check_initialized()


def is_initialized() -> bool:
    return psb.is_initialized()


def frame_tick() -> None:
    psb.frame_tick()


def shutdown(allow_mid_frame_shutdown: bool = False) -> None:
    psb.shutdown(allow_mid_frame_shutdown)


def remove_everything() -> None:
    psb.remove_everything()


### Render engine


def get_render_engine_backend_name() -> str:
    return psb.get_render_engine_backend_name()


def is_headless() -> bool:
    return psb.is_headless()


def set_allow_headless_backends(b: bool) -> None:
    return psb.set_allow_headless_backends(b)


### Structure management


def remove_all_structures() -> None:
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


def set_screenshot_extension(ext: str) -> None:
    psb.set_screenshot_extension(ext)


def screenshot_to_buffer(transparent_bg=True, vertical_flip=True, include_UI=False) -> NDArray[np.uint8]:
    opts = psb.ScreenshotOptions()
    opts.include_UI = include_UI
    opts.transparent_background = transparent_bg

    buff = psb.screenshot_to_buffer(opts)
    w, h = get_buffer_size()
    buff = buff.reshape(h, w, 4)
    if vertical_flip:
        buff = buff[::-1, :, :]
    return buff


### Small options


def set_program_name(name: str) -> None:
    psb.set_program_name(name)


def set_verbosity(v: int) -> None:
    psb.set_verbosity(v)


def set_print_prefix(p: str) -> None:
    psb.set_print_prefix(p)


def set_errors_throw_exceptions(val: bool) -> None:
    psb.set_errors_throw_exceptions(val)


def set_max_fps(f: int) -> None:
    psb.set_max_fps(f)


def set_enable_vsync(b: bool) -> None:
    psb.set_enable_vsync(b)


def set_use_prefs_file(v: bool) -> None:
    psb.set_use_prefs_file(v)


def set_do_default_mouse_interaction(v: bool) -> None:
    psb.set_do_default_mouse_interaction(v)


def request_redraw() -> None:
    psb.request_redraw()


def get_redraw_requested() -> bool:
    return psb.get_redraw_requested()


def set_always_redraw(v: bool) -> None:
    psb.set_always_redraw(v)


def set_frame_tick_limit_fps_mode(
    v: Literal["ignore_limits", "block_to_hit_target", "skip_frames_to_hit_target"] | str,
) -> None:
    psb.set_frame_tick_limit_fps_mode(to_enum(psb.LimitFPSMode, v))


def set_enable_render_error_checks(b: bool) -> None:
    psb.set_enable_render_error_checks(b)


def set_egl_device_index(i: int) -> None:
    psb.set_egl_device_index(i)


def set_autocenter_structures(b: bool) -> None:
    psb.set_autocenter_structures(b)


def set_autoscale_structures(b: bool) -> None:
    psb.set_autoscale_structures(b)


def set_ui_scale(s: float) -> None:
    psb.set_ui_scale(s)


def get_ui_scale() -> float:
    return psb.get_ui_scale()


def set_build_gui(b: bool) -> None:
    psb.set_build_gui(b)


def set_user_gui_is_on_right_side(b: bool) -> None:
    psb.set_user_gui_is_on_right_side(b)


def set_build_default_gui_panels(b: bool) -> None:
    psb.set_build_default_gui_panels(b)


def set_right_gui_pane_width(w: int) -> None:
    psb.set_right_gui_pane_width(w)


def get_right_gui_pane_width() -> int:
    return psb.get_right_gui_pane_width()


def set_render_scene(b: bool) -> None:
    psb.set_render_scene(b)


def set_open_imgui_window_for_user_callback(b: bool) -> None:
    psb.set_open_imgui_window_for_user_callback(b)


def set_invoke_user_callback_for_nested_show(b: bool) -> None:
    psb.set_invoke_user_callback_for_nested_show(b)


def set_give_focus_on_show(b: bool) -> None:
    psb.set_give_focus_on_show(b)


def set_hide_window_after_show(b: bool) -> None:
    psb.set_hide_window_after_show(b)


def set_warn_for_invalid_values(b: bool) -> None:
    psb.set_warn_for_invalid_values(b)


def set_display_message_popups(b: bool) -> None:
    psb.set_display_message_popups(b)


def set_configure_imgui_style_callback(f):
    return psb.set_configure_imgui_style_callback(f)


def clear_configure_imgui_style_callback() -> None:
    return psb.clear_configure_imgui_style_callback()


def set_prepare_imgui_fonts_callback(f):
    return psb.set_prepare_imgui_fonts_callback(f)


def clear_prepare_imgui_fonts_callback() -> None:
    return psb.clear_prepare_imgui_fonts_callback()


def set_files_dropped_callback(f):
    return psb.set_files_dropped_callback(f)


def clear_files_dropped_callback() -> None:
    return psb.clear_files_dropped_callback()


def set_navigation_style(val: Literal["turntable", "free", "planar", "arcball", "none", "first_person"] | str):
    psb.set_navigation_style(to_enum(polyscope.NavigateStyle, val))


def get_navigation_style() -> str:
    return from_enum(psb.get_navigation_style())


def set_up_dir(d: Literal["x_up", "y_up", "z_up", "neg_x_up", "neg_y_up", "neg_z_up"] | str) -> None:
    psb.set_up_dir(to_enum(psb.UpDir, d))


def get_up_dir() -> str:
    return from_enum(psb.get_up_dir())


def set_front_dir(
    d: Literal["x_front", "y_front", "z_front", "neg_x_front", "neg_y_front", "neg_z_front"] | str,
) -> None:
    psb.set_front_dir(to_enum(psb.FrontDir, d))


def get_front_dir() -> str:
    return from_enum(psb.get_front_dir())


def set_vertical_fov_degrees(f: float) -> None:
    psb.set_vertical_fov_degrees(f)


def get_vertical_fov_degrees() -> float:
    return psb.get_vertical_fov_degrees()


def get_aspect_ratio_width_over_height() -> float:
    return psb.get_aspect_ratio_width_over_height()


### Scene extents


def set_automatically_compute_scene_extents(b: bool) -> None:
    psb.set_automatically_compute_scene_extents(b)


def set_length_scale(s: float) -> None:
    psb.set_length_scale(s)


def get_length_scale() -> float:
    return psb.get_length_scale()


def set_bounding_box(low, high):
    psb.set_bounding_box(glm3(low), glm3(high))


def get_bounding_box():
    low, high = psb.get_bounding_box()
    return np.array(low.as_tuple()), np.array(high.as_tuple())


def update_scene_extents():
    """This is usually an internal function, and should not need to be called by end users unless you are manually updating structure bounds after creation."""
    psb.update_scene_extents()


### Camera controls


def reset_camera_to_home_view() -> None:
    psb.reset_camera_to_home_view()


def look_at(camera_location, target, fly_to: bool = False) -> None:
    psb.look_at(glm3(camera_location), glm3(target), fly_to)


def look_at_dir(camera_location, target, up_dir, fly_to: bool = False) -> None:
    psb.look_at_dir(glm3(camera_location), glm3(target), glm3(up_dir), fly_to)


def get_view_projection_mode() -> Literal["orthographic", "perspective"]:
    return from_enum(psb.get_view_projection_mode())


def set_view_projection_mode(s: Literal["orthographic", "perspective"] | str) -> None:
    psb.set_view_projection_mode(to_enum(psb.ProjectionMode, s))


def set_window_size(width: int, height: int) -> None:
    width = int(width)
    height = int(height)
    psb.set_window_size(width, height)


def get_window_size():
    return psb.get_window_size()


def get_buffer_size():
    return psb.get_buffer_size()


def set_window_resizable(is_resizable: bool) -> None:
    psb.set_window_resizable(is_resizable)


def get_window_resizable() -> bool:
    return psb.get_window_resizable()


def set_view_from_json(json_str: str, fly_to: bool = False) -> None:
    psb.set_view_from_json(json_str, fly_to)


def get_view_as_json() -> str:
    return psb.get_view_as_json()


def screen_coords_to_world_ray(screen_coords):
    return np.array(psb.screen_coords_to_world_ray(glm2(screen_coords)).as_tuple())


# deprecated! use query_pick_at_screen_coords
def screen_coords_to_world_position(screen_coords):
    pick_result = pick(screen_coords=screen_coords)
    return pick_result.position


def set_background_color(c):
    if len(c) == 3:
        c = (c[0], c[1], c[2], 1.0)
    psb.set_background_color(glm4(c))


def get_background_color():
    return psb.get_background_color()


def get_view_camera_parameters():
    return CameraParameters(instance=psb.get_view_camera_parameters())


def set_view_camera_parameters(params):
    if not isinstance(params, CameraParameters):
        raise ValueError("must pass CameraParameters")
    psb.set_view_camera_parameters(params.instance)


def get_view_buffer_resolution():
    return CameraParameters(instance=psb.get_view_camera_parameters())


def set_camera_view_matrix(mat):
    mat = np.asarray(mat)
    if mat.shape != (4, 4):
        raise ValueError("mat should be a 4x4 numpy matrix")
    psb.set_camera_view_matrix(mat)


def get_camera_view_matrix():
    return psb.get_camera_view_matrix()


def set_view_center_and_look_at(pos: ArrayLike, fly_to: bool = False):
    psb.set_view_center_and_look_at(glm3(pos), fly_to)


def set_view_center_and_project(pos: ArrayLike):
    psb.set_view_center_and_project(glm3(pos))


def set_view_center_raw(pos: ArrayLike):
    psb.set_view_center_raw(glm3(pos))


def get_view_center():
    return np.array(psb.get_view_center().as_tuple())


### "Advanced" UI management


def build_polyscope_gui() -> None:
    psb.build_polyscope_gui()


def build_structure_gui() -> None:
    psb.build_structure_gui()


def build_pick_gui() -> None:
    psb.build_pick_gui()


def build_user_gui_and_invoke_callback() -> None:
    psb.build_user_gui_and_invoke_callback()


### Messages


def info(message: str, verbosity: int = 0) -> None:
    # only printed if verbosity > vebosityLevel
    psb.info(verbosity, message)


def warning(message: str, detail: str = "") -> None:
    psb.warning(message, detail)


def error(message: str) -> None:
    psb.error(message)


def terminating_error(message: str) -> None:
    psb.terminating_error(message)


### Callback
def set_user_callback(func):
    if func is None:
        psb.clear_user_callback()
    else:
        psb.set_user_callback(func)


def clear_user_callback() -> None:
    psb.clear_user_callback()


### Picking


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

        # Use local imports to avoid circular dependencies
        from polyscope import point_cloud, curve_network, surface_mesh, volume_mesh, volume_grid

        if self.structure_type_name == "Point Cloud":
            point_cloud.get_point_cloud(self.structure_name).append_pick_data(self)

        if self.structure_type_name == "Curve Network":
            curve_network.get_curve_network(self.structure_name).append_pick_data(self)

        if self.structure_type_name == "Surface Mesh":
            surface_mesh.get_surface_mesh(self.structure_name).append_pick_data(self)

        if self.structure_type_name == "Volume Mesh":
            volume_mesh.get_volume_mesh(self.structure_name).append_pick_data(self)

        if self.structure_type_name == "Volume Grid":
            volume_grid.get_volume_grid(self.structure_name).append_pick_data(self)

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


def pick(*, screen_coords: ArrayLike | None = None, buffer_inds: ArrayLike | None = None) -> PickResult:
    if screen_coords is not None and buffer_inds is not None:
        raise ValueError("pass args one of screen_coords OR buffer_inds, but not both")
    if screen_coords is None and buffer_inds is None:
        raise ValueError("must pass args one of screen_coords or buffer_inds")

    if screen_coords is not None:
        raw_result = psb.pick_at_screen_coords(glm2(screen_coords))
    if buffer_inds is not None:
        arr = np.asarray(buffer_inds)
        if not np.issubdtype(arr.dtype, np.integer) or arr.shape != (2,):
            raise ValueError("buffer_inds should be a an array/tuple/etc of two integers")
        raw_result = psb.pick_at_buffer_inds(glm2i(buffer_inds))

    return PickResult(raw_result)


def have_selection() -> bool:
    return psb.have_selection()


def get_selection() -> PickResult:
    return PickResult(psb.get_selection())


def reset_selection() -> None:
    psb.reset_selection()


## Ground plane and shadows
def set_ground_plane_mode(mode_str: Literal["none", "tile", "tile_reflection", "shadow_only"] | str) -> None:
    psb.set_ground_plane_mode(to_enum(psb.GroundPlaneMode, mode_str))


def set_ground_plane_height_mode(mode_str: Literal["automatic", "manual"] | str) -> None:
    psb.set_ground_plane_height_mode(to_enum(psb.GroundPlaneHeightMode, mode_str))


def set_ground_plane_height(h: float) -> None:
    set_ground_plane_height_mode("manual")
    psb.set_ground_plane_height(h)


def set_ground_plane_height_factor(h: float, is_relative: bool = True) -> None:
    set_ground_plane_height_mode("automatic")
    psb.set_ground_plane_height_factor(h, is_relative)


def set_shadow_blur_iters(n: int) -> None:
    psb.set_shadow_blur_iters(n)


def set_shadow_darkness(val: float) -> None:
    psb.set_shadow_darkness(val)


## Transparency
def set_transparency_mode(mode: Literal["none", "simple", "pretty"] | str) -> None:
    psb.set_transparency_mode(to_enum(psb.TransparencyMode, mode))


def set_transparency_render_passes(n: int) -> None:
    psb.set_transparency_render_passes(n)


## Rendering
def set_SSAA_factor(n: int) -> None:
    psb.set_SSAA_factor(n)


## Groups


class Group:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use add_group() instead
    def __init__(self, instance):
        # Wrap an existing instance
        self.bound_group = instance

    def get_name(self) -> str:
        return self.bound_group.name

    def add_child_group(self, child_group) -> None:
        if isinstance(child_group, str):
            self.bound_group.add_child_group(get_group(child_group).bound_group)
        else:
            self.bound_group.add_child_group(child_group.bound_group)

    def add_child_structure(self, child_structure) -> None:
        self.bound_group.add_child_structure(child_structure.bound_instance)

    def remove_child_group(self, child_group) -> None:
        if isinstance(child_group, str):
            self.bound_group.remove_child_group(get_group(child_group).bound_group)
        else:
            self.bound_group.remove_child_group(child_group.bound_group)

    def remove_child_structure(self, child_structure) -> None:
        self.bound_group.remove_child_structure(child_structure.bound_instance)

    def set_enabled(self, new_val: bool) -> None:
        self.bound_group.set_enabled(new_val)

    def set_show_child_details(self, new_val: bool) -> None:
        self.bound_group.set_show_child_details(new_val)

    def set_hide_descendants_from_structure_lists(self, new_val: bool) -> None:
        self.bound_group.set_hide_descendants_from_structure_lists(new_val)

    def get_child_structure_names(self):
        # Only returns first-level children, does not recurse
        return self.bound_group.get_child_structure_names()

    def get_child_group_names(self):
        # Only returns first-level children, does not recurse
        return self.bound_group.get_child_group_names()


def create_group(name: str) -> Group:
    return Group(psb.create_group(name))


def get_group(name: str) -> Group:
    return Group(psb.get_group(name))


def remove_group(group, error_if_absent: bool = True) -> None:
    # accept either a string or a group ref as input
    if isinstance(group, str):
        psb.remove_group(group, error_if_absent)
    else:
        psb.remove_group(group.get_name(), error_if_absent)


def remove_all_groups() -> None:
    psb.remove_all_groups()


## Low-level internals access
# (warning, 'advanced' users only, may change)
def get_final_scene_color_texture_native_handle():
    return psb.get_final_scene_color_texture_native_handle()


## Slice planes


class SlicePlane:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use add_scene_slice_plane() instead
    def __init__(self, instance: psb.SlicePlane):
        # Wrap an existing instance
        self.bound_slice_plane = instance

    def get_name(self) -> str:
        return self.bound_slice_plane.name

    def remove(self) -> None:
        self.bound_slice_plane.remove()

    def set_enabled(self, val: bool) -> None:
        self.bound_slice_plane.set_enabled(val)

    def get_enabled(self) -> bool:
        return self.bound_slice_plane.get_enabled()

    def set_active(self, val: bool) -> None:
        self.bound_slice_plane.set_active(val)

    def get_active(self) -> bool:
        return self.bound_slice_plane.get_active()

    def set_pose(self, plane_position: ArrayLike, plane_normal: ArrayLike) -> None:
        self.bound_slice_plane.set_pose(glm3(plane_position), glm3(plane_normal))

    def get_center(self):
        return self.bound_slice_plane.get_center()

    def get_normal(self):
        return self.bound_slice_plane.get_normal()

    def set_color(self, val):
        self.bound_slice_plane.set_color(glm3(val))

    def get_color(self):
        return self.bound_slice_plane.get_color()

    def set_grid_line_color(self, val):
        self.bound_slice_plane.set_grid_line_color(glm3(val))

    def get_grid_line_color(self):
        return self.bound_slice_plane.get_grid_line_color()

    def set_transparency(self, val: float) -> None:
        self.bound_slice_plane.set_transparency(val)

    def get_transparency(self) -> float:
        return self.bound_slice_plane.get_transparency()

    def set_draw_plane(self, val: bool) -> None:
        self.bound_slice_plane.set_draw_plane(val)

    def get_draw_plane(self) -> bool:
        return self.bound_slice_plane.get_draw_plane()

    def set_draw_widget(self, val: bool) -> None:
        self.bound_slice_plane.set_draw_widget(val)

    def get_draw_widget(self) -> bool:
        return self.bound_slice_plane.get_draw_widget()

    def set_volume_mesh_to_inspect(self, val: str) -> None:
        return self.bound_slice_plane.set_volume_mesh_to_inspect(val)

    def get_volume_mesh_to_inspect(self) -> str:
        return self.bound_slice_plane.get_volume_mesh_to_inspect()


def add_slice_plane(name: str | None = None) -> SlicePlane:
    if name is None:
        instance = psb.add_slice_plane()
    else:
        instance = psb.add_slice_plane(name)

    return SlicePlane(instance)


def get_slice_plane(name: str) -> SlicePlane:
    instance = psb.get_slice_plane(name)
    return SlicePlane(instance)


def remove_slice_plane(name: str) -> None:
    psb.remove_slice_plane(name)


def remove_all_slice_planes() -> None:
    psb.remove_all_slice_planes()


def add_scene_slice_plane() -> SlicePlane:
    # deprecated
    instance = psb.add_scene_slice_plane(False)
    return SlicePlane(instance)


def remove_last_scene_slice_plane() -> None:
    # deprecated
    psb.remove_last_scene_slice_plane()


## Transformation Gizmo


class TransformationGizmo:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use add_transformation_gizmo() instead
    def __init__(self, instance: psb.TransformationGizmo):
        # Wrap an existing instance
        self.bound_gizmo = instance

    def get_name(self) -> str:
        return self.bound_gizmo.name

    def remove(self) -> None:
        self.bound_gizmo.remove()

    def set_enabled(self, val: bool) -> None:
        self.bound_gizmo.set_enabled(val)

    def get_enabled(self) -> bool:
        return self.bound_gizmo.get_enabled()

    def set_transform(self, T: NDArray) -> None:
        if not isinstance(T, np.ndarray) or T.shape != (4, 4):
            raise ValueError("T should be a 4x4 numpy matrix")
        self.bound_gizmo.set_transform(T)

    def get_transform(self) -> NDArray:
        return self.bound_gizmo.get_transform()

    def set_position(self, p: ArrayLike) -> None:
        self.bound_gizmo.set_position(glm3(p))

    def get_position(self) -> NDArray:
        return self.bound_gizmo.get_position()

    def set_allow_translation(self, val: bool) -> None:
        self.bound_gizmo.set_allow_translation(val)

    def get_allow_translation(self) -> bool:
        return self.bound_gizmo.get_allow_translation()

    def set_allow_rotation(self, val: bool) -> None:
        self.bound_gizmo.set_allow_rotation(val)

    def get_allow_rotation(self) -> bool:
        return self.bound_gizmo.get_allow_rotation()

    def set_allow_scaling(self, val: bool) -> None:
        self.bound_gizmo.set_allow_scaling(val)

    def get_allow_scaling(self) -> bool:
        return self.bound_gizmo.get_allow_scaling()

    def set_allow_nonuniform_scaling(self, val: bool) -> None:
        self.bound_gizmo.set_allow_nonuniform_scaling(val)

    def get_allow_nonuniform_scaling(self) -> bool:
        return self.bound_gizmo.get_allow_nonuniform_scaling()

    def get_interact_in_local_space(self) -> bool:
        return self.bound_gizmo.get_interact_in_local_space()

    def set_interact_in_local_space(self, val: bool) -> None:
        self.bound_gizmo.set_interact_in_local_space(val)

    def get_gizmo_scale(self) -> float:
        # underlying binding uses "size"
        return self.bound_gizmo.get_gizmo_size()

    def set_gizmo_scale(self, val: float) -> None:
        # underlying binding uses "size"
        self.bound_gizmo.set_gizmo_size(float(val))

    def build_inline_transform_ui(self) -> None:
        self.bound_gizmo.build_inline_transform_ui()


def add_transformation_gizmo(name: str | None = None) -> TransformationGizmo:
    if name is None:
        # name gets automatically set internally; pass empty string
        instance = psb.add_transformation_gizmo("")
    else:
        instance = psb.add_transformation_gizmo(name)

    return TransformationGizmo(instance)


def get_transformation_gizmo(name: str) -> TransformationGizmo:
    instance = psb.get_transformation_gizmo(name)
    return TransformationGizmo(instance)


def remove_transformation_gizmo(name: str) -> None:
    psb.remove_transformation_gizmo(name)


def remove_all_transformation_gizmos() -> None:
    psb.remove_all_transformation_gizmos()


### Camera Parameters


class CameraIntrinsics:
    instance: psb.CameraIntrinsics

    def __init__(
        self,
        fov_vertical_deg: float | None = None,
        fov_horizontal_deg: float | None = None,
        aspect: float | None = None,
        instance: psb.CameraIntrinsics | None = None,
    ) -> None:
        if instance is not None:
            self.instance = instance
        elif fov_vertical_deg is not None and aspect is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_vertical_and_aspect(
                float(fov_vertical_deg), float(aspect)
            )
        elif fov_horizontal_deg is not None and aspect is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_horizontal_and_aspect(
                float(fov_horizontal_deg), float(aspect)
            )
        elif fov_vertical_deg is not None and fov_horizontal_deg is not None:
            self.instance = psb.CameraIntrinsics.from_FoV_deg_horizontal_and_vertical(
                float(fov_horizontal_deg), float(fov_vertical_deg)
            )
        else:
            raise ValueError(
                "bad arguments, at least two of (fov_vertical_deg,fov_horizontal_deg,aspect) must be given and non-None"
            )


class CameraExtrinsics:
    instance: psb.CameraExtrinsics

    def __init__(
        self,
        root: ArrayLike | None = None,
        look_dir: ArrayLike | None = None,
        up_dir: ArrayLike | None = None,
        mat: NDArray | None = None,
        instance: psb.CameraExtrinsics | None = None,
    ) -> None:
        if instance is not None:
            self.instance = instance

        elif mat is not None:
            mat = np.asarray(mat)
            if mat.shape != (4, 4):
                raise ValueError("mat should be a 4x4 numpy matrix")
            self.instance = psb.CameraExtrinsics.from_matrix(mat)

        elif (root is not None) and (look_dir is not None) and (up_dir is not None):
            self.instance = psb.CameraExtrinsics.from_vectors(
                np.asarray(root), np.asarray(look_dir), np.asarray(up_dir)
            )

        else:
            raise ValueError("bad arguments, must pass non-None (root,look_dir,up_dir) or non-None mat")


class CameraParameters:
    instance: psb.CameraParameters

    def __init__(
        self,
        intrinsics: CameraIntrinsics | None = None,
        extrinsics: CameraExtrinsics | None = None,
        instance: psb.CameraParameters | None = None,
    ):
        if instance is not None:
            self.instance = instance
        else:
            assert intrinsics is not None
            assert extrinsics is not None
            self.instance = psb.CameraParameters(intrinsics.instance, extrinsics.instance)

    # getters
    def get_intrinsics(self) -> CameraIntrinsics:
        return CameraIntrinsics(instance=self.instance.get_intrinsics())

    def get_extrinsics(self) -> CameraExtrinsics:
        return CameraExtrinsics(instance=self.instance.get_extrinsics())

    def get_T(self) -> NDArray:
        return self.instance.get_T()

    def get_R(self) -> NDArray:
        return self.instance.get_R()

    def get_view_mat(self) -> NDArray:
        return self.instance.get_view_mat()  # same as get_E()

    def get_E(self) -> NDArray:
        return self.instance.get_E()

    def get_position(self) -> NDArray:
        return self.instance.get_position()

    def get_look_dir(self) -> NDArray:
        return self.instance.get_look_dir()

    def get_up_dir(self) -> NDArray:
        return self.instance.get_up_dir()

    def get_right_dir(self) -> NDArray:
        return self.instance.get_right_dir()

    def get_camera_frame(self) -> Tuple[NDArray, NDArray, NDArray]:
        return self.instance.get_camera_frame()

    def get_fov_vertical_deg(self) -> float:
        return self.instance.get_fov_vertical_deg()

    def get_aspect(self) -> float:
        return self.instance.get_aspect()

    def generate_camera_rays(self, dims, image_origin: Literal["lower_left", "upper_left"] | str = "upper_left"):
        out_rays = self.instance.generate_camera_rays(
            int(dims[0]), int(dims[1]), to_enum(psb.ImageOrigin, image_origin)
        )
        return out_rays.reshape(dims[1], dims[0], 3)

    def generate_camera_ray_corners(self):
        return self.instance.generate_camera_ray_corners()


## Small utilities
def glm2(vals: ArrayLike) -> psb.glm_vec2:
    vals_arr = np.asarray(vals, dtype=np.float32)
    if vals_arr.shape != (2,):
        raise ValueError("vals should be length-2 float array/tuple/etc. Got shape " + str(vals_arr.shape))
    return psb.glm_vec2(vals_arr[0], vals_arr[1])


def glm2i(vals: ArrayLike) -> psb.glm_ivec2:
    vals_arr = np.asarray(vals, dtype=np.int32)
    if vals_arr.shape != (2,):
        raise ValueError("vals should be length-2 int array/tuple/etc. Got shape " + str(vals_arr.shape))
    return psb.glm_ivec2(vals_arr[0], vals_arr[1])


def glm3u(vals: ArrayLike) -> psb.glm_uvec3:
    vals_arr = np.asarray(vals, dtype=np.uint32)
    if vals_arr.shape != (3,):
        raise ValueError("vals should be length-3 int array/tuple/etc. Got shape " + str(vals_arr.shape))
    return psb.glm_uvec3(vals_arr[0], vals_arr[1], vals_arr[2])


def glm3(vals: ArrayLike) -> psb.glm_vec3:
    vals_arr = np.asarray(vals, dtype=np.float32)
    if vals_arr.shape != (3,):
        raise ValueError("vals should be length-3 float array/tuple/etc. Got shape " + str(vals_arr.shape))
    return psb.glm_vec3(vals_arr[0], vals_arr[1], vals_arr[2])


def glm4(vals: ArrayLike) -> psb.glm_vec4:
    vals_arr = np.asarray(vals, dtype=np.float32)
    if vals_arr.shape != (4,):
        raise ValueError("vals should be length-4 float array/tuple/etc. Got shape " + str(vals_arr.shape))
    return psb.glm_vec4(vals_arr[0], vals_arr[1], vals_arr[2], vals_arr[3])


def degrees(val: float) -> float:
    return 180.0 * val / np.pi


def radians(val: float) -> float:
    return np.pi * val / 180.0


### Materials


def load_static_material(mat_name: str, filename: str) -> None:
    psb.load_static_material(mat_name, filename)


def load_blendable_material(
    mat_name: str,
    filenames: Sequence[str] | None = None,
    filename_base: str | None = None,
    filename_ext: str | None = None,
):
    # list of names
    if filenames is not None:
        if filename_base is not None or filename_ext is not None:
            raise ValueError("`filenames` was specified, `filename_base`/`filename_ext` should NOT be specified")

        if len(filenames) != 4:
            raise ValueError("`filenames` should be a list of four filenames")
        filenames_tuple = (filenames[0], filenames[1], filenames[2], filenames[3])

        psb.load_blendable_material_explicit(mat_name, filenames_tuple)

    # base/ext pair
    if filename_base is not None and filename_ext is not None:
        if filenames is not None:
            raise ValueError("`filename_base`/`filename_ext` were specified, `filenames` should NOT be specified")

        psb.load_blendable_material_baseext(mat_name, filename_base, filename_ext)


### Colormaps


def load_color_map(cmap_name: str, filename: str) -> None:
    psb.load_color_map(cmap_name, filename)


# Mapping for some common characters, to support our legacy get_key_code() function.
# The more proper solution is to use the ImGui enum names directly like psim.ImGuiKey_W; only a subset of them are mapped get_key_code() and the dict below.
# The full list can be found in the ImGui source, or in this issue https://github.com/ocornut/imgui/issues/4921
keycode_dict = {
    " ": psim.ImGuiKey_Space,
    "0": psim.ImGuiKey_0,
    "1": psim.ImGuiKey_1,
    "2": psim.ImGuiKey_2,
    "3": psim.ImGuiKey_3,
    "4": psim.ImGuiKey_4,
    "5": psim.ImGuiKey_5,
    "6": psim.ImGuiKey_6,
    "7": psim.ImGuiKey_7,
    "8": psim.ImGuiKey_8,
    "9": psim.ImGuiKey_9,
    "A": psim.ImGuiKey_A,
    "B": psim.ImGuiKey_B,
    "C": psim.ImGuiKey_C,
    "D": psim.ImGuiKey_D,
    "E": psim.ImGuiKey_E,
    "F": psim.ImGuiKey_F,
    "G": psim.ImGuiKey_G,
    "H": psim.ImGuiKey_H,
    "I": psim.ImGuiKey_I,
    "J": psim.ImGuiKey_J,
    "K": psim.ImGuiKey_K,
    "L": psim.ImGuiKey_L,
    "M": psim.ImGuiKey_M,
    "N": psim.ImGuiKey_N,
    "O": psim.ImGuiKey_O,
    "P": psim.ImGuiKey_P,
    "Q": psim.ImGuiKey_Q,
    "R": psim.ImGuiKey_R,
    "S": psim.ImGuiKey_S,
    "T": psim.ImGuiKey_T,
    "U": psim.ImGuiKey_U,
    "V": psim.ImGuiKey_V,
    "W": psim.ImGuiKey_W,
    "X": psim.ImGuiKey_X,
    "Y": psim.ImGuiKey_Y,
    "Z": psim.ImGuiKey_Z,
    "'": psim.ImGuiKey_Apostrophe,
    ",": psim.ImGuiKey_Comma,
    "-": psim.ImGuiKey_Minus,
    ".": psim.ImGuiKey_Period,
    "/": psim.ImGuiKey_Slash,
    ";": psim.ImGuiKey_Semicolon,
    "=": psim.ImGuiKey_Equal,
    "[": psim.ImGuiKey_LeftBracket,
    "\\": psim.ImGuiKey_Backslash,
    "]": psim.ImGuiKey_RightBracket,
}


def get_key_code(k: str):
    if len(k) != 1:
        raise ValueError("pass a single character")
    if k.islower():
        k = k.upper()

    if k not in keycode_dict:
        raise ValueError(
            f"character {k} not in keycode mapping. For keys which have multiple characters on them, try the other character (like @ vs 2). Alternately, don't use this function, look up the appropriate enum from the imgui documentation, use them like polyscope.imgui.ImGuiKey_Semicolon"
        )

    return keycode_dict[k]
