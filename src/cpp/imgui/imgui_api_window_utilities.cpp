#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_window_utilities(nb::module_& m) {

    // Windows Utilities
    // IMGUI_API bool          IsWindowAppearing();
    m.def("IsWindowAppearing", []() { return ImGui::IsWindowAppearing(); });

    // IMGUI_API bool          IsWindowCollapsed();
    m.def("IsWindowCollapsed", []() { return ImGui::IsWindowCollapsed(); });

    // IMGUI_API bool          IsWindowFocused(ImGuiFocusedFlags flags=0);
    m.def(
        "IsWindowFocused",
        [](ImGuiFocusedFlags flags) { return ImGui::IsWindowFocused(flags); },
        nb::arg("flags") = 0);

    // IMGUI_API bool          IsWindowHovered(ImGuiHoveredFlags flags=0);
    m.def(
        "IsWindowHovered",
        [](ImGuiHoveredFlags flags) { return ImGui::IsWindowHovered(flags); },
        nb::arg("flags") = 0);

    // IMGUI_API ImDrawList*   GetWindowDrawList();
    m.def("GetWindowDrawList", []() { return ImGui::GetWindowDrawList(); }, nb::rv_policy::reference);

    // IMGUI_API ImVec2        GetWindowPos();
    m.def("GetWindowPos", []() { return from_vec2(ImGui::GetWindowPos()); });

    // IMGUI_API ImVec2        GetWindowSize();
    m.def("GetWindowSize", []() { return from_vec2(ImGui::GetWindowSize()); });

    // IMGUI_API float         GetWindowWidth();
    m.def("GetWindowWidth", []() { return ImGui::GetWindowWidth(); });

    // IMGUI_API float         GetWindowHeight();
    m.def("GetWindowHeight", []() { return ImGui::GetWindowHeight(); });

}
// clang-format on
