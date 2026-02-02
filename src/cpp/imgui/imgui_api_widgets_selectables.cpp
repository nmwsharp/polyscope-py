#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_selectables(nb::module_& m) {

    // Widgets: Selectables
    // IMGUI_API bool          Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    m.def(
        "Selectable",
        [](const char* label, bool selected, ImGuiSelectableFlags flags, const Vec2T& size) {
            return ImGui::Selectable(label, selected, flags, to_vec2(size));
        },
        nb::arg("label"),
        nb::arg("selected") = false,
        nb::arg("flags") = 0,
        nb::arg("size") = Vec2T(0.f, 0.f));

    // IMGUI_API bool          Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    m.def(
        "Selectable",
        [](const char* label, bool p_selected, ImGuiSelectableFlags flags, const Vec2T& size) {
            bool result = ImGui::Selectable(label, &p_selected, flags, to_vec2(size));
            return std::make_tuple(result, p_selected);
        },
        nb::arg("label"),
        nb::arg("p_selected"),
        nb::arg("flags") = 0,
        nb::arg("size") = Vec2T(0.f, 0.f));

    // IMGUI_API ImGuiMultiSelectIO*   BeginMultiSelect(ImGuiMultiSelectFlags flags, int selection_size = -1, int items_count = -1);
    m.def(
        "BeginMultiSelect",
        [](ImGuiMultiSelectFlags flags, int selection_size, int items_count) {
            return ImGui::BeginMultiSelect(flags, selection_size, items_count);
        },
        nb::arg("flags"),
        nb::arg("selection_size") = -1,
        nb::arg("items_count") = -1,
        nb::rv_policy::reference);

    // IMGUI_API ImGuiMultiSelectIO*   EndMultiSelect();
    m.def("EndMultiSelect", []() { return ImGui::EndMultiSelect(); }, nb::rv_policy::reference);

    // IMGUI_API void                  SetNextItemSelectionUserData(ImGuiSelectionUserData selection_user_data);
    m.def(
        "SetNextItemSelectionUserData",
        [](ImGuiSelectionUserData selection_user_data) {
            ImGui::SetNextItemSelectionUserData(selection_user_data);
        },
        nb::arg("selection_user_data"));

    // IMGUI_API bool                  IsItemToggledSelection();
    m.def("IsItemToggledSelection", []() { return ImGui::IsItemToggledSelection(); });

}
// clang-format on
