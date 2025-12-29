// ImDrawList struct bindings

#include "imgui_utils.h"
#include <nanobind/stl/vector.h>

// clang-format off

void bind_imgui_drawlist(nb::module_& m) {

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

        // Primitives - Lines and Shapes
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
            nb::arg("num_segments"),
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
            nb::arg("num_segments")
        )
        .def(
            "AddEllipse",
            [](ImDrawList& self, const Vec2T& center, const Vec2T& radius, ImU32 col, float rot, int num_segments, float thickness) {
                self.AddEllipse(to_vec2(center), to_vec2(radius), col, rot, num_segments, thickness);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("rot") = 0.0f,
            nb::arg("num_segments") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddEllipseFilled",
            [](ImDrawList& self, const Vec2T& center, const Vec2T& radius, ImU32 col, float rot, int num_segments) {
                self.AddEllipseFilled(to_vec2(center), to_vec2(radius), col, rot, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("rot") = 0.0f,
            nb::arg("num_segments") = 0
        )

        // Text
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

        // Bezier curves
        .def(
            "AddBezierCubic",
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness, int num_segments) {
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
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness, int num_segments) {
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
            [](ImDrawList& self, const std::vector<Vec2T>& points, ImU32 col, ImDrawFlags flags, float thickness) {
                std::vector<ImVec2> points_vec2(points.size());
                for (size_t i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                }
                self.AddPolyline(points_vec2.data(), static_cast<int>(points.size()), col, flags, thickness);
            },
            nb::arg("points"),
            nb::arg("col"),
            nb::arg("flags"),
            nb::arg("thickness")
        )
        .def(
            "AddConvexPolyFilled",
            [](ImDrawList& self, const std::vector<Vec2T>& points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (size_t i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                }
                self.AddConvexPolyFilled(points_vec2.data(), static_cast<int>(points.size()), col);
            },
            nb::arg("points"),
            nb::arg("col")
        )
        .def(
            "AddConcavePolyFilled",
            [](ImDrawList& self, const std::vector<Vec2T>& points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (size_t i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                }
                self.AddConcavePolyFilled(points_vec2.data(), static_cast<int>(points.size()), col);
            },
            nb::arg("points"),
            nb::arg("col")
        )

        // Image primitives
        .def(
            "AddImage",
            [](ImDrawList& self, ImTextureID user_texture_id, const Vec2T& p_min, const Vec2T& p_max, const Vec2T& uv_min, const Vec2T& uv_max, ImU32 col) {
                self.AddImage(user_texture_id, to_vec2(p_min), to_vec2(p_max), to_vec2(uv_min), to_vec2(uv_max), col);
            },
            nb::arg("user_texture_id"),
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("uv_min") = Vec2T{0, 0},
            nb::arg("uv_max") = Vec2T{1, 1},
            nb::arg("col") = IM_COL32_WHITE
        )
        .def(
            "AddImageQuad",
            [](ImDrawList& self, ImTextureID user_texture_id, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, const Vec2T& uv1, const Vec2T& uv2, const Vec2T& uv3, const Vec2T& uv4, ImU32 col) {
                self.AddImageQuad(user_texture_id, to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), to_vec2(uv1), to_vec2(uv2), to_vec2(uv3), to_vec2(uv4), col);
            },
            nb::arg("user_texture_id"),
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("uv1") = Vec2T{0, 0},
            nb::arg("uv2") = Vec2T{1, 0},
            nb::arg("uv3") = Vec2T{1, 1},
            nb::arg("uv4") = Vec2T{0, 1},
            nb::arg("col") = IM_COL32_WHITE
        )
        .def(
            "AddImageRounded",
            [](ImDrawList& self, ImTextureID user_texture_id, const Vec2T& p_min, const Vec2T& p_max, const Vec2T& uv_min, const Vec2T& uv_max, ImU32 col, float rounding, ImDrawFlags flags) {
                self.AddImageRounded(user_texture_id, to_vec2(p_min), to_vec2(p_max), to_vec2(uv_min), to_vec2(uv_max), col, rounding, flags);
            },
            nb::arg("user_texture_id"),
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("uv_min"),
            nb::arg("uv_max"),
            nb::arg("col"),
            nb::arg("rounding"),
            nb::arg("flags") = 0
        )

        // Stateful path API
        .def("PathClear", [](ImDrawList& self) { self.PathClear(); })
        .def("PathLineTo", [](ImDrawList& self, const Vec2T& pos) { self.PathLineTo(to_vec2(pos)); }, nb::arg("pos"))
        .def("PathLineToMergeDuplicate", [](ImDrawList& self, const Vec2T& pos) { self.PathLineToMergeDuplicate(to_vec2(pos)); }, nb::arg("pos"))
        .def("PathFillConvex", [](ImDrawList& self, ImU32 col) { self.PathFillConvex(col); }, nb::arg("col"))
        .def("PathFillConcave", [](ImDrawList& self, ImU32 col) { self.PathFillConcave(col); }, nb::arg("col"))
        .def("PathStroke", [](ImDrawList& self, ImU32 col, ImDrawFlags flags, float thickness) { self.PathStroke(col, flags, thickness); },
            nb::arg("col"), nb::arg("flags") = 0, nb::arg("thickness") = 1.0f)
        .def(
            "PathArcTo",
            [](ImDrawList& self, const Vec2T& center, float radius, float a_min, float a_max, int num_segments) {
                self.PathArcTo(to_vec2(center), radius, a_min, a_max, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("a_min"),
            nb::arg("a_max"),
            nb::arg("num_segments") = 0
        )
        .def(
            "PathArcToFast",
            [](ImDrawList& self, const Vec2T& center, float radius, int a_min_of_12, int a_max_of_12) {
                self.PathArcToFast(to_vec2(center), radius, a_min_of_12, a_max_of_12);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("a_min_of_12"),
            nb::arg("a_max_of_12")
        )
        .def(
            "PathEllipticalArcTo",
            [](ImDrawList& self, const Vec2T& center, const Vec2T& radius, float rot, float a_min, float a_max, int num_segments) {
                self.PathEllipticalArcTo(to_vec2(center), to_vec2(radius), rot, a_min, a_max, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("rot"),
            nb::arg("a_min"),
            nb::arg("a_max"),
            nb::arg("num_segments") = 0
        )
        .def(
            "PathBezierCubicCurveTo",
            [](ImDrawList& self, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, int num_segments) {
                self.PathBezierCubicCurveTo(to_vec2(p2), to_vec2(p3), to_vec2(p4), num_segments);
            },
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("num_segments") = 0
        )
        .def(
            "PathBezierQuadraticCurveTo",
            [](ImDrawList& self, const Vec2T& p2, const Vec2T& p3, int num_segments) {
                self.PathBezierQuadraticCurveTo(to_vec2(p2), to_vec2(p3), num_segments);
            },
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("num_segments") = 0
        )
        .def(
            "PathRect",
            [](ImDrawList& self, const Vec2T& rect_min, const Vec2T& rect_max, float rounding, ImDrawFlags flags) {
                self.PathRect(to_vec2(rect_min), to_vec2(rect_max), rounding, flags);
            },
            nb::arg("rect_min"),
            nb::arg("rect_max"),
            nb::arg("rounding") = 0.0f,
            nb::arg("flags") = 0
        )

        // Advanced: Channels
        // Note: Prefer using your own persistent instance of ImDrawListSplitter
        .def("ChannelsSplit", [](ImDrawList& self, int count) { self.ChannelsSplit(count); }, nb::arg("count"))
        .def("ChannelsMerge", [](ImDrawList& self) { self.ChannelsMerge(); })
        .def("ChannelsSetCurrent", [](ImDrawList& self, int n) { self.ChannelsSetCurrent(n); }, nb::arg("n"))

        // Advanced: Miscellaneous
        .def("AddDrawCmd", &ImDrawList::AddDrawCmd)
        .def("CloneOutput", &ImDrawList::CloneOutput, nb::rv_policy::reference)

        // Note: The following are not bound as they are low-level or internal:
        // - PushTextureID/PopTextureID (low-level texture state management)
        // - AddCallback (requires C function pointers)
        // - PrimReserve/PrimUnreserve/PrimRect/PrimRectUV/PrimQuadUV (low-level primitive allocation)
        // - PrimWriteVtx/PrimWriteIdx/PrimVtx (low-level vertex writing)
        // - All _Internal functions (prefixed with _)
    ;
}
