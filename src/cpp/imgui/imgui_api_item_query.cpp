#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_item_query(nb::module_& m) {

    // Item/Widgets Utilities and Query Functions
    // IMGUI_API bool          IsItemHovered(ImGuiHoveredFlags flags = 0);
    m.def(
        "IsItemHovered",
        [](ImGuiHoveredFlags flags) { return ImGui::IsItemHovered(flags); },
        nb::arg("flags") = 0);

    // IMGUI_API bool          IsItemActive();
    m.def("IsItemActive", []() { return ImGui::IsItemActive(); });

    // IMGUI_API bool          IsItemFocused();
    m.def("IsItemFocused", []() { return ImGui::IsItemFocused(); });

    // IMGUI_API bool          IsItemClicked(ImGuiMouseButton mouse_button = 0);
    m.def(
        "IsItemClicked",
        [](ImGuiMouseButton mouse_button) { return ImGui::IsItemClicked(mouse_button); },
        nb::arg("mouse_button") = 0);

    // IMGUI_API bool          IsItemVisible();
    m.def("IsItemVisible", []() { return ImGui::IsItemVisible(); });

    // IMGUI_API bool          IsItemEdited();
    m.def("IsItemEdited", []() { return ImGui::IsItemEdited(); });

    // IMGUI_API bool          IsItemActivated();
    m.def("IsItemActivated", []() { return ImGui::IsItemActivated(); });

    // IMGUI_API bool          IsItemDeactivated();
    m.def("IsItemDeactivated", []() { return ImGui::IsItemDeactivated(); });

    // IMGUI_API bool          IsItemDeactivatedAfterEdit();
    m.def("IsItemDeactivatedAfterEdit", []() { return ImGui::IsItemDeactivatedAfterEdit(); });

    // IMGUI_API bool          IsItemToggledOpen();
    m.def("IsItemToggledOpen", []() { return ImGui::IsItemToggledOpen(); });

    // IMGUI_API bool          IsAnyItemHovered();
    m.def("IsAnyItemHovered", []() { return ImGui::IsAnyItemHovered(); });

    // IMGUI_API bool          IsAnyItemActive();
    m.def("IsAnyItemActive", []() { return ImGui::IsAnyItemActive(); });

    // IMGUI_API bool          IsAnyItemFocused();
    m.def("IsAnyItemFocused", []() { return ImGui::IsAnyItemFocused(); });

    // IMGUI_API ImGuiID       GetItemID();
    m.def("GetItemID", []() { return ImGui::GetItemID(); });

    // IMGUI_API ImVec2        GetItemRectMin();
    m.def("GetItemRectMin", []() { return from_vec2(ImGui::GetItemRectMin()); });

    // IMGUI_API ImVec2        GetItemRectMax();
    m.def("GetItemRectMax", []() { return from_vec2(ImGui::GetItemRectMax()); });

    // IMGUI_API ImVec2        GetItemRectSize();
    m.def("GetItemRectSize", []() { return from_vec2(ImGui::GetItemRectSize()); });

}
// clang-format on
