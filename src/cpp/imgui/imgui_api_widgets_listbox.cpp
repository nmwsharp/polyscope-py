#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_widgets_listbox(nb::module_& m) {

    // Widgets: List Boxes
    // IMGUI_API bool          BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0));
    m.def(
        "BeginListBox",
        [](const char* label, const Vec2T& size) { return ImGui::BeginListBox(label, to_vec2(size)); },
        nb::arg("label"),
        nb::arg("size") = Vec2T(0.f, 0.f));

    // IMGUI_API void          EndListBox();
    m.def("EndListBox", []() { ImGui::EndListBox(); });

    // IMGUI_API bool          ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
    m.def(
        "ListBox",
        [](const char* label, int current_item, const std::vector<std::string>& items, int height_in_items) {
            std::vector<const char*> item_ptrs;
            item_ptrs.reserve(items.size());
            for (const auto& item : items) {
                item_ptrs.push_back(item.c_str());
            }
            bool result = ImGui::ListBox(label, &current_item, item_ptrs.data(), static_cast<int>(item_ptrs.size()), height_in_items);
            return std::make_tuple(result, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items"),
        nb::arg("height_in_items") = -1);

    // IMGUI_API bool          ListBox(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int height_in_items = -1);
    // TODO: Callback version requires binding function pointers from Python

}
// clang-format on
