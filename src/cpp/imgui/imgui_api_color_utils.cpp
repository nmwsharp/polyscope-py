// Color Utilities

#include "imgui_utils.h"

// clang-format off

void bind_color_utils(nb::module_& m) {
    // Color conversion between U32 and Float4
    m.def("ColorConvertU32ToFloat4", &ImGui::ColorConvertU32ToFloat4, nb::arg("in"));
    m.def("ColorConvertFloat4ToU32", &ImGui::ColorConvertFloat4ToU32, nb::arg("in"));

    // RGB <-> HSV conversion (returns tuple for output parameters)
    m.def("ColorConvertRGBtoHSV", [](float r, float g, float b) {
        float h, s, v;
        ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
        return std::make_tuple(h, s, v);
    }, nb::arg("r"), nb::arg("g"), nb::arg("b"));

    m.def("ColorConvertHSVtoRGB", [](float h, float s, float v) {
        float r, g, b;
        ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
        return std::make_tuple(r, g, b);
    }, nb::arg("h"), nb::arg("s"), nb::arg("v"));
}
