#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_color(nb::module_& m) {

    // Widgets: Color Editor/Picker
    // IMGUI_API bool          ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    m.def(
        "ColorEdit3",
        [](const char* label, std::array<float, 3> col, ImGuiColorEditFlags flags) {
            bool result = ImGui::ColorEdit3(label, col.data(), flags);
            return std::make_tuple(result, col);
        },
        nb::arg("label"),
        nb::arg("col"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
    m.def(
        "ColorEdit4",
        [](const char* label, std::array<float, 4> col, ImGuiColorEditFlags flags) {
            bool result = ImGui::ColorEdit4(label, col.data(), flags);
            return std::make_tuple(result, col);
        },
        nb::arg("label"),
        nb::arg("col"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    m.def(
        "ColorPicker3",
        [](const char* label, std::array<float, 3> col, ImGuiColorEditFlags flags) {
            bool result = ImGui::ColorPicker3(label, col.data(), flags);
            return std::make_tuple(result, col);
        },
        nb::arg("label"),
        nb::arg("col"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
    m.def(
        "ColorPicker4",
        [](const char* label, std::array<float, 4> col, ImGuiColorEditFlags flags) {
            bool result = ImGui::ColorPicker4(label, col.data(), flags);
            return std::make_tuple(result, col);
        },
        nb::arg("label"),
        nb::arg("col"),
        nb::arg("flags") = 0);
    // TODO: ref_col parameter not bound

    // IMGUI_API bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    m.def(
        "ColorButton",
        [](const char* desc_id, const Vec4T& col, ImGuiColorEditFlags flags, const Vec2T& size) {
            return ImGui::ColorButton(desc_id, to_vec4(col), flags, to_vec2(size));
        },
        nb::arg("desc_id"),
        nb::arg("col"),
        nb::arg("flags") = 0,
        nb::arg("size") = Vec2T(0.f, 0.f));

    // IMGUI_API void          SetColorEditOptions(ImGuiColorEditFlags flags);
    m.def(
        "SetColorEditOptions",
        [](ImGuiColorEditFlags flags) { ImGui::SetColorEditOptions(flags); },
        nb::arg("flags"));

}
// clang-format on
