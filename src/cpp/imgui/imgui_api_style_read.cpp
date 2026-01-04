#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_style_read(nb::module_& m) {

    // Style read access

    // IMGUI_API ImVec2        GetFontTexUvWhitePixel();
    m.def("GetFontTexUvWhitePixel", []() { return from_vec2(ImGui::GetFontTexUvWhitePixel()); });

    // IMGUI_API ImU32         GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
    m.def(
        "GetColorU32",
        [](ImGuiCol idx, float alpha_mul) { return ImGui::GetColorU32(idx, alpha_mul); },
        nb::arg("idx"),
        nb::arg("alpha_mul") = 1.0f);

    // IMGUI_API ImU32         GetColorU32(const ImVec4& col);
    m.def(
        "GetColorU32",
        [](const Vec4T& col) { return ImGui::GetColorU32(to_vec4(col)); },
        nb::arg("col"));

    // IMGUI_API ImU32         GetColorU32(ImU32 col, float alpha_mul = 1.0f);
    m.def(
        "GetColorU32",
        [](ImU32 col, float alpha_mul) { return ImGui::GetColorU32(col, alpha_mul); },
        nb::arg("col"),
        nb::arg("alpha_mul") = 1.0f);

    // IMGUI_API const ImVec4& GetStyleColorVec4(ImGuiCol idx);
    m.def(
        "GetStyleColorVec4",
        [](ImGuiCol idx) { return from_vec4(ImGui::GetStyleColorVec4(idx)); },
        nb::arg("idx"));

}
// clang-format on
