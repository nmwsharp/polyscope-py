#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_widgets_combo(nb::module_& m) {

    // Widgets: Combo Box (Dropdown)
    // IMGUI_API bool          BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
    m.def(
        "BeginCombo",
        [](const char* label, const char* preview_value, ImGuiComboFlags flags) {
            return ImGui::BeginCombo(label, preview_value, flags);
        },
        nb::arg("label"),
        nb::arg("preview_value"),
        nb::arg("flags") = 0);

    // IMGUI_API void          EndCombo();
    m.def("EndCombo", []() { ImGui::EndCombo(); });

    // IMGUI_API bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    m.def(
        "Combo",
        [](const char* label, int current_item, const std::vector<std::string>& items, int popup_max_height_in_items) {
            std::vector<const char*> item_ptrs;
            item_ptrs.reserve(items.size());
            for (const auto& item : items) {
                item_ptrs.push_back(item.c_str());
            }
            bool result = ImGui::Combo(label, &current_item, item_ptrs.data(), static_cast<int>(item_ptrs.size()), popup_max_height_in_items);
            return std::make_tuple(result, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items"),
        nb::arg("popup_max_height_in_items") = -1);

    // IMGUI_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);
    m.def(
        "Combo",
        [](const char* label, int current_item, const char* items_separated_by_zeros, int popup_max_height_in_items) {
            bool result = ImGui::Combo(label, &current_item, items_separated_by_zeros, popup_max_height_in_items);
            return std::make_tuple(result, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items_separated_by_zeros"),
        nb::arg("popup_max_height_in_items") = -1);

    // IMGUI_API bool          Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items = -1);
    // TODO: Callback version requires binding function pointers from Python

}
// clang-format on
