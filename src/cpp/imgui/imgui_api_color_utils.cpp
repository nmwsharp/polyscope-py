// Color Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_color_utils(nb::module_& m) {
    // IMGUI_API ImVec4        ColorConvertU32ToFloat4(ImU32 in);
    m.def("ColorConvertU32ToFloat4", [](ImU32 in_val) {
        return from_vec4(ImGui::ColorConvertU32ToFloat4(in_val));
    }, nb::arg("in_val"));

    // IMGUI_API ImU32         ColorConvertFloat4ToU32(const ImVec4& in);
    m.def("ColorConvertFloat4ToU32", [](const Vec4T& in_val) {
        return ImGui::ColorConvertFloat4ToU32(to_vec4(in_val));
    }, nb::arg("in_val"));

    // IMGUI_API void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    m.def("ColorConvertRGBtoHSV", [](float r, float g, float b) {
        float h, s, v;
        ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
        return std::make_tuple(h, s, v);
    }, nb::arg("r"), nb::arg("g"), nb::arg("b"));

    // IMGUI_API void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);
    m.def("ColorConvertHSVtoRGB", [](float h, float s, float v) {
        float r, g, b;
        ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
        return std::make_tuple(r, g, b);
    }, nb::arg("h"), nb::arg("s"), nb::arg("v"));
}
