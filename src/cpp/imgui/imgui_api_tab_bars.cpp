#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_tab_bars(nb::module_& m) {

    // Tab Bars, Tab Items
    // IMGUI_API bool          BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0);
    m.def(
        "BeginTabBar",
        [](const char* str_id, ImGuiTabBarFlags flags) { return ImGui::BeginTabBar(str_id, flags); },
        nb::arg("str_id"),
        nb::arg("flags") = 0);

    // IMGUI_API void          EndTabBar();
    m.def("EndTabBar", []() { ImGui::EndTabBar(); });

    // IMGUI_API bool          BeginTabItem(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0);
    m.def(
        "BeginTabItem",
        [](const char* label, bool p_open, ImGuiTabItemFlags flags) {
            bool result = ImGui::BeginTabItem(label, &p_open, flags);
            return std::make_tuple(result, p_open);
        },
        nb::arg("label"),
        nb::arg("p_open"),
        nb::arg("flags") = 0);

    // IMGUI_API void          EndTabItem();
    m.def("EndTabItem", []() { ImGui::EndTabItem(); });

    // IMGUI_API bool          TabItemButton(const char* label, ImGuiTabItemFlags flags = 0);
    m.def(
        "TabItemButton",
        [](const char* label, ImGuiTabItemFlags flags) { return ImGui::TabItemButton(label, flags); },
        nb::arg("label"),
        nb::arg("flags") = 0);

    // IMGUI_API void          SetTabItemClosed(const char* tab_or_docked_window_label);
    m.def(
        "SetTabItemClosed",
        [](const char* tab_or_docked_window_label) { ImGui::SetTabItemClosed(tab_or_docked_window_label); },
        nb::arg("tab_or_docked_window_label"));

}
// clang-format on
