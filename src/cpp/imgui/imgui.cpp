#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

void bind_imgui_enums(nb::module_& m);
void bind_imgui_structs(nb::module_& m);

void bind_imgui_api_main(nb::module_& m);
void bind_imgui_api_context_creation(nb::module_& m);
void bind_demo_debug(nb::module_& m);
void bind_styles(nb::module_& m);
void bind_windows(nb::module_& m);
void bind_child_windows(nb::module_& m);
void bind_window_utilities(nb::module_& m);
void bind_window_manipulation(nb::module_& m);
void bind_scrolling(nb::module_& m);
void bind_parameter_stacks(nb::module_& m);
void bind_style_read(nb::module_& m);
void bind_cursor_layout(nb::module_& m);
void bind_id_stack(nb::module_& m);
void bind_widgets_text(nb::module_& m);
void bind_widgets_main(nb::module_& m);
void bind_widgets_images(nb::module_& m);
void bind_widgets_combo(nb::module_& m);
void bind_widgets_drag(nb::module_& m);
void bind_widgets_sliders(nb::module_& m);
void bind_widgets_input(nb::module_& m);
void bind_widgets_color(nb::module_& m);
void bind_widgets_trees(nb::module_& m);
void bind_widgets_selectables(nb::module_& m);
void bind_widgets_listbox(nb::module_& m);
void bind_data_plotting(nb::module_& m);
void bind_menus(nb::module_& m);
void bind_tooltips(nb::module_& m);
void bind_popups(nb::module_& m);
void bind_tables(nb::module_& m);
void bind_columns_legacy(nb::module_& m);
void bind_tab_bars(nb::module_& m);
void bind_logging(nb::module_& m);
void bind_drag_drop(nb::module_& m);
void bind_disabling(nb::module_& m);
void bind_clipping(nb::module_& m);
void bind_focus_activation(nb::module_& m);
void bind_overlapping_items(nb::module_& m);
void bind_item_query(nb::module_& m);
void bind_viewports(nb::module_& m);
void bind_draw_lists(nb::module_& m);
void bind_misc_utils(nb::module_& m);
void bind_text_utils(nb::module_& m);
void bind_color_utils(nb::module_& m);
void bind_inputs_keyboard(nb::module_& m);
void bind_inputs_mouse(nb::module_& m);
void bind_clipboard(nb::module_& m);
void bind_settings(nb::module_& m);
void bind_debug(nb::module_& m);
void bind_allocators(nb::module_& m);

void bind_imgui(nb::module_& m) {
  auto imgui_module = m.def_submodule("imgui", "ImGui bindings");
  bind_imgui_enums(imgui_module);
  bind_imgui_structs(imgui_module);

  bind_imgui_api_main(imgui_module);
  bind_imgui_api_context_creation(imgui_module);
  bind_demo_debug(imgui_module);
  bind_styles(imgui_module);
  bind_windows(imgui_module);
  bind_child_windows(imgui_module);
  bind_window_utilities(imgui_module);
  bind_window_manipulation(imgui_module);
  bind_scrolling(imgui_module);
  bind_parameter_stacks(imgui_module);
  bind_style_read(imgui_module);
  bind_cursor_layout(imgui_module);
  bind_id_stack(imgui_module);
  bind_widgets_text(imgui_module);
  bind_widgets_main(imgui_module);
  bind_widgets_images(imgui_module);
  bind_widgets_combo(imgui_module);
  bind_widgets_drag(imgui_module);
  bind_widgets_sliders(imgui_module);
  bind_widgets_input(imgui_module);
  bind_widgets_color(imgui_module);
  bind_widgets_trees(imgui_module);
  bind_widgets_selectables(imgui_module);
  bind_widgets_listbox(imgui_module);
  bind_data_plotting(imgui_module);
  bind_menus(imgui_module);
  bind_tooltips(imgui_module);
  bind_popups(imgui_module);
  bind_tables(imgui_module);
  bind_columns_legacy(imgui_module);
  bind_tab_bars(imgui_module);
  bind_logging(imgui_module);
  bind_drag_drop(imgui_module);
  bind_disabling(imgui_module);
  bind_clipping(imgui_module);
  bind_focus_activation(imgui_module);
  bind_overlapping_items(imgui_module);
  bind_item_query(imgui_module);
  bind_viewports(imgui_module);
  bind_draw_lists(imgui_module);
  bind_misc_utils(imgui_module);
  bind_text_utils(imgui_module);
  bind_color_utils(imgui_module);
  bind_inputs_keyboard(imgui_module);
  bind_inputs_mouse(imgui_module);
  bind_clipboard(imgui_module);
  bind_settings(imgui_module);
  bind_debug(imgui_module);
  bind_allocators(imgui_module);
}

// clang-format off

void bind_imgui_methods(nb::module_& m) {

    // Draw Commands 
    nb::class_<ImDrawList>(m, "ImDrawList")

        // Clip Rect

        .def(
            "PushClipRect",
            [](ImDrawList& self, const Vec2T& clip_rect_min, const Vec2T& clip_rect_max, bool intersect_with_current_clip_rect) {
                self.PushClipRect(to_vec2(clip_rect_min), to_vec2(clip_rect_max), intersect_with_current_clip_rect);
            },
            nb::arg("clip_rect_min"),
            nb::arg("clip_rect_max"),
            nb::arg("intersect_with_current_clip_rect") = false
        )
        .def("PushClipRectFullScreen", &ImDrawList::PushClipRectFullScreen)
        .def("PopClipRect", &ImDrawList::PopClipRect)
        .def("GetClipRectMin", [](ImDrawList& self) { return from_vec2(self.GetClipRectMin()); })
        .def("GetClipRectMax", [](ImDrawList& self) { return from_vec2(self.GetClipRectMax()); })

        // Primitives

        .def(
            "AddLine", 
            [](ImDrawList& draw_list, const Vec2T& p1, const Vec2T& p2, ImU32 col, float thickness) {
                draw_list.AddLine(to_vec2(p1), to_vec2(p2), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddRect", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags, float thickness) {
                self.AddRect(to_vec2(p_min), to_vec2(p_max), col, rounding, flags, thickness);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col"),
            nb::arg("rounding") = 0.0f,
            nb::arg("flags") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddRectFilled", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags) {
                self.AddRectFilled(to_vec2(p_min), to_vec2(p_max), col, rounding, flags);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col"),
            nb::arg("rounding") = 0.0f,
            nb::arg("flags") = 0
        )
        .def(
            "AddRectFilledMultiColor", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left) {
                self.AddRectFilledMultiColor(to_vec2(p_min), to_vec2(p_max), col_upr_left, col_upr_right, col_bot_right, col_bot_left);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col_upr_left"),
            nb::arg("col_upr_right"),
            nb::arg("col_bot_right"),
            nb::arg("col_bot_left")
        )
        .def(
            "AddQuad", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness) {
                self.AddQuad(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddQuadFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col) {
                self.AddQuadFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col")
        )
        .def(
            "AddTriangle", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness) {
                self.AddTriangle(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddTriangleFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col) {
                self.AddTriangleFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), col);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col")
        )
        .def(
            "AddCircle", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddCircle(to_vec2(center), radius, col, num_segments, thickness);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddCircleFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddCircleFilled(to_vec2(center), radius, col, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddNgon", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddNgon(to_vec2(center), radius, col, num_segments, thickness);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddNgonFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddNgonFilled(to_vec2(center), radius, col, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddText", 
            [](ImDrawList& self, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end) {
                self.AddText(to_vec2(pos), col, text_begin, text_end);
            },
            nb::arg("pos"),
            nb::arg("col"),
            nb::arg("text_begin"),
            nb::arg("text_end") = nullptr
        )
        .def(
            "AddText", 
            [](ImDrawList& self, ImFont* font, float font_size, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width) {
                self.AddText(font, font_size, to_vec2(pos), col, text_begin, text_end, wrap_width);
            },
            nb::arg("font"),
            nb::arg("font_size"),
            nb::arg("pos"),
            nb::arg("col"),
            nb::arg("text_begin"),
            nb::arg("text_end") = nullptr,
            nb::arg("wrap_width") = 0.0f
        )
        .def(
            "AddPolyline", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col, ImDrawFlags flags, float thickness) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddPolyline(points_vec2.data(), num_points, col, flags, thickness);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col"),
            nb::arg("flags"),
            nb::arg("thickness")
        )
        .def(
            "AddConvexPolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConvexPolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        .def(
            "AddBezierCubic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierCubic(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness, num_segments);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col"),
            nb::arg("thickness"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddBezierQuadratic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierQuadratic(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness, num_segments);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col"),
            nb::arg("thickness"),
            nb::arg("num_segments") = 0
        )

        // General Polygon

        .def(
            "AddPolyline", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col, ImDrawFlags flags, float thickness) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddPolyline(points_vec2.data(), num_points, col, flags, thickness);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col"),
            nb::arg("flags"),
            nb::arg("thickness")
        )
        .def(
            "AddConvexPolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConvexPolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        .def(
            "AddConcavePolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConcavePolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        
    ;
        

    // Macros etc
    m.def("IM_COL32", [](uint8_t R, uint8_t G, uint8_t B, uint8_t A) { return IM_COL32(R,G,B,A); });
}
// clang-format on