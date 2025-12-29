#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

void bind_imgui_enums(nb::module_& m);
void bind_imgui_structs(nb::module_& m);
void bind_imgui_macros(nb::module_& m);
void bind_imgui_io(nb::module_& m);
void bind_imgui_style(nb::module_& m);
void bind_imgui_drawlist(nb::module_& m);

void bind_imgui_api_main(nb::module_& m);
void bind_imgui_api_context_creation(nb::module_& m);
void bind_imgui_api_demo_debug(nb::module_& m);
void bind_imgui_api_styles(nb::module_& m);
void bind_imgui_api_windows(nb::module_& m);
void bind_imgui_api_child_windows(nb::module_& m);
void bind_imgui_api_window_utilities(nb::module_& m);
void bind_imgui_api_window_manipulation(nb::module_& m);
void bind_imgui_api_scrolling(nb::module_& m);
void bind_imgui_api_parameter_stacks(nb::module_& m);
void bind_imgui_api_style_read(nb::module_& m);
void bind_imgui_api_cursor_layout(nb::module_& m);
void bind_imgui_api_id_stack(nb::module_& m);
void bind_imgui_api_widgets_text(nb::module_& m);
void bind_imgui_api_widgets_main(nb::module_& m);
void bind_imgui_api_widgets_images(nb::module_& m);
void bind_imgui_api_widgets_combo(nb::module_& m);
void bind_imgui_api_widgets_drag(nb::module_& m);
void bind_imgui_api_widgets_sliders(nb::module_& m);
void bind_imgui_api_widgets_input(nb::module_& m);
void bind_imgui_api_widgets_color(nb::module_& m);
void bind_imgui_api_widgets_trees(nb::module_& m);
void bind_imgui_api_widgets_selectables(nb::module_& m);
void bind_imgui_api_widgets_listbox(nb::module_& m);
void bind_imgui_api_data_plotting(nb::module_& m);
void bind_imgui_api_menus(nb::module_& m);
void bind_imgui_api_tooltips(nb::module_& m);
void bind_imgui_api_popups(nb::module_& m);
void bind_imgui_api_tables(nb::module_& m);
void bind_imgui_api_columns_legacy(nb::module_& m);
void bind_imgui_api_tab_bars(nb::module_& m);
void bind_imgui_api_logging(nb::module_& m);
void bind_imgui_api_drag_drop(nb::module_& m);
void bind_imgui_api_disabling(nb::module_& m);
void bind_imgui_api_clipping(nb::module_& m);
void bind_imgui_api_focus_activation(nb::module_& m);
void bind_imgui_api_overlapping_items(nb::module_& m);
void bind_imgui_api_item_query(nb::module_& m);
void bind_imgui_api_viewports(nb::module_& m);
void bind_imgui_api_draw_lists(nb::module_& m);
void bind_imgui_api_misc_utils(nb::module_& m);
void bind_imgui_api_text_utils(nb::module_& m);
void bind_imgui_api_color_utils(nb::module_& m);
void bind_imgui_api_inputs_keyboard(nb::module_& m);
void bind_imgui_api_inputs_mouse(nb::module_& m);
void bind_imgui_api_clipboard(nb::module_& m);
void bind_imgui_api_settings(nb::module_& m);
void bind_imgui_api_debug(nb::module_& m);
void bind_imgui_api_allocators(nb::module_& m);

void bind_imgui(nb::module_& m) {
  auto imgui_module = m.def_submodule("imgui", "ImGui bindings");
  bind_imgui_enums(imgui_module);
  bind_imgui_structs(imgui_module);
  bind_imgui_macros(imgui_module);
  bind_imgui_io(imgui_module);
  bind_imgui_style(imgui_module);
  bind_imgui_drawlist(imgui_module);

  bind_imgui_api_main(imgui_module);
  bind_imgui_api_context_creation(imgui_module);
  bind_imgui_api_demo_debug(imgui_module);
  bind_imgui_api_styles(imgui_module);
  bind_imgui_api_windows(imgui_module);
  bind_imgui_api_child_windows(imgui_module);
  bind_imgui_api_window_utilities(imgui_module);
  bind_imgui_api_window_manipulation(imgui_module);
  bind_imgui_api_scrolling(imgui_module);
  bind_imgui_api_parameter_stacks(imgui_module);
  bind_imgui_api_style_read(imgui_module);
  bind_imgui_api_cursor_layout(imgui_module);
  bind_imgui_api_id_stack(imgui_module);
  bind_imgui_api_widgets_text(imgui_module);
  bind_imgui_api_widgets_main(imgui_module);
  bind_imgui_api_widgets_images(imgui_module);
  bind_imgui_api_widgets_combo(imgui_module);
  bind_imgui_api_widgets_drag(imgui_module);
  bind_imgui_api_widgets_sliders(imgui_module);
  bind_imgui_api_widgets_input(imgui_module);
  bind_imgui_api_widgets_color(imgui_module);
  bind_imgui_api_widgets_trees(imgui_module);
  bind_imgui_api_widgets_selectables(imgui_module);
  bind_imgui_api_widgets_listbox(imgui_module);
  bind_imgui_api_data_plotting(imgui_module);
  bind_imgui_api_menus(imgui_module);
  bind_imgui_api_tooltips(imgui_module);
  bind_imgui_api_popups(imgui_module);
  bind_imgui_api_tables(imgui_module);
  bind_imgui_api_columns_legacy(imgui_module);
  bind_imgui_api_tab_bars(imgui_module);
  bind_imgui_api_logging(imgui_module);
  bind_imgui_api_drag_drop(imgui_module);
  bind_imgui_api_disabling(imgui_module);
  bind_imgui_api_clipping(imgui_module);
  bind_imgui_api_focus_activation(imgui_module);
  bind_imgui_api_overlapping_items(imgui_module);
  bind_imgui_api_item_query(imgui_module);
  bind_imgui_api_viewports(imgui_module);
  bind_imgui_api_draw_lists(imgui_module);
  bind_imgui_api_misc_utils(imgui_module);
  bind_imgui_api_text_utils(imgui_module);
  bind_imgui_api_color_utils(imgui_module);
  bind_imgui_api_inputs_keyboard(imgui_module);
  bind_imgui_api_inputs_mouse(imgui_module);
  bind_imgui_api_clipboard(imgui_module);
  bind_imgui_api_settings(imgui_module);
  bind_imgui_api_debug(imgui_module);
  bind_imgui_api_allocators(imgui_module);
}