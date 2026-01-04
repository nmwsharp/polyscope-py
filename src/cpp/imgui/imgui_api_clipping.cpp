#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_clipping(nb::module_& m) {

    // Clipping
    // IMGUI_API void          PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
    m.def(
        "PushClipRect",
        [](const Vec2T& clip_rect_min, const Vec2T& clip_rect_max, bool intersect_with_current_clip_rect) {
            ImGui::PushClipRect(to_vec2(clip_rect_min), to_vec2(clip_rect_max), intersect_with_current_clip_rect);
        },
        nb::arg("clip_rect_min"),
        nb::arg("clip_rect_max"),
        nb::arg("intersect_with_current_clip_rect"));

    // IMGUI_API void          PopClipRect();
    m.def("PopClipRect", []() { ImGui::PopClipRect(); });

}
// clang-format on
