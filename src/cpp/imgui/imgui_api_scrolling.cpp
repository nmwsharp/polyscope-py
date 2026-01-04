#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_scrolling(nb::module_& m) {

    // Windows Scrolling
    // IMGUI_API float         GetScrollX();
    m.def("GetScrollX", []() { return ImGui::GetScrollX(); });

    // IMGUI_API float         GetScrollY();
    m.def("GetScrollY", []() { return ImGui::GetScrollY(); });

    // IMGUI_API void          SetScrollX(float scroll_x);
    m.def(
        "SetScrollX",
        [](float scroll_x) { ImGui::SetScrollX(scroll_x); },
        nb::arg("scroll_x"));

    // IMGUI_API void          SetScrollY(float scroll_y);
    m.def(
        "SetScrollY",
        [](float scroll_y) { ImGui::SetScrollY(scroll_y); },
        nb::arg("scroll_y"));

    // IMGUI_API float         GetScrollMaxX();
    m.def("GetScrollMaxX", []() { return ImGui::GetScrollMaxX(); });

    // IMGUI_API float         GetScrollMaxY();
    m.def("GetScrollMaxY", []() { return ImGui::GetScrollMaxY(); });

    // IMGUI_API void          SetScrollHereX(float center_x_ratio = 0.5f);
    m.def(
        "SetScrollHereX",
        [](float center_x_ratio) { ImGui::SetScrollHereX(center_x_ratio); },
        nb::arg("center_x_ratio") = 0.5f);

    // IMGUI_API void          SetScrollHereY(float center_y_ratio = 0.5f);
    m.def(
        "SetScrollHereY",
        [](float center_y_ratio) { ImGui::SetScrollHereY(center_y_ratio); },
        nb::arg("center_y_ratio") = 0.5f);

    // IMGUI_API void          SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
    m.def(
        "SetScrollFromPosX",
        [](float local_x, float center_x_ratio) { ImGui::SetScrollFromPosX(local_x, center_x_ratio); },
        nb::arg("local_x"),
        nb::arg("center_x_ratio") = 0.5f);

    // IMGUI_API void          SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);
    m.def(
        "SetScrollFromPosY",
        [](float local_y, float center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); },
        nb::arg("local_y"),
        nb::arg("center_y_ratio") = 0.5f);

}
// clang-format on
