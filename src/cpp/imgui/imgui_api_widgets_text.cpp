#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_text(nb::module_& m) {

    // Widgets: Text
    // IMGUI_API void          TextUnformatted(const char* text, const char* text_end = NULL);
    m.def(
        "TextUnformatted",
        [](const char* text) { ImGui::TextUnformatted(text); },
        nb::arg("text"));

    // IMGUI_API void          Text(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "Text",
        [](const char* text) { ImGui::TextUnformatted(text); },
        nb::arg("text"));

    // IMGUI_API void          TextV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: variadic/va_list functions not bound - use Text() with pre-formatted string from Python

    // IMGUI_API void          TextColored(const ImVec4& col, const char* fmt, ...) IM_FMTARGS(2);
    m.def(
        "TextColored",
        [](const Vec4T& col, const char* text) { ImGui::TextColored(to_vec4(col), "%s", text); },
        nb::arg("col"),
        nb::arg("text"));

    // IMGUI_API void          TextColoredV(const ImVec4& col, const char* fmt, va_list args) IM_FMTLIST(2);
    // TODO: variadic/va_list functions not bound - use TextColored() with pre-formatted string from Python

    // IMGUI_API void          TextDisabled(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "TextDisabled",
        [](const char* text) { ImGui::TextDisabled("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          TextDisabledV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: variadic/va_list functions not bound - use TextDisabled() with pre-formatted string from Python

    // IMGUI_API void          TextWrapped(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "TextWrapped",
        [](const char* text) { ImGui::TextWrapped("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          TextWrappedV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: variadic/va_list functions not bound - use TextWrapped() with pre-formatted string from Python

    // IMGUI_API void          LabelText(const char* label, const char* fmt, ...) IM_FMTARGS(2);
    m.def(
        "LabelText",
        [](const char* label, const char* text) { ImGui::LabelText(label, "%s", text); },
        nb::arg("label"),
        nb::arg("text"));

    // IMGUI_API void          LabelTextV(const char* label, const char* fmt, va_list args) IM_FMTLIST(2);
    // TODO: variadic/va_list functions not bound - use LabelText() with pre-formatted string from Python

    // IMGUI_API void          BulletText(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "BulletText",
        [](const char* text) { ImGui::BulletText("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          BulletTextV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: variadic/va_list functions not bound - use BulletText() with pre-formatted string from Python

    // IMGUI_API void          SeparatorText(const char* label);
    m.def(
        "SeparatorText",
        [](const char* label) { ImGui::SeparatorText(label); },
        nb::arg("label"));

}
// clang-format on
