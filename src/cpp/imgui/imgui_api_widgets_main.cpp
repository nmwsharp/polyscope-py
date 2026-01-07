#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_main(nb::module_& m) {

    // Widgets: Main
    // IMGUI_API bool          Button(const char* label, const ImVec2& size = ImVec2(0, 0));
    m.def(
        "Button",
        [](const char* label, const Vec2T& size) { return ImGui::Button(label, to_vec2(size)); },
        nb::arg("label"),
        nb::arg("size") = Vec2T(0.f, 0.f));

    // IMGUI_API bool          SmallButton(const char* label);
    m.def(
        "SmallButton",
        [](const char* label) { return ImGui::SmallButton(label); },
        nb::arg("label"));

    // IMGUI_API bool          InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0);
    m.def(
        "InvisibleButton",
        [](const char* str_id, const Vec2T& size, ImGuiButtonFlags flags) {
            return ImGui::InvisibleButton(str_id, to_vec2(size), flags);
        },
        nb::arg("str_id"),
        nb::arg("size"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          ArrowButton(const char* str_id, ImGuiDir dir);
    m.def(
        "ArrowButton",
        [](const char* str_id, ImGuiDir dir) { return ImGui::ArrowButton(str_id, dir); },
        nb::arg("str_id"),
        nb::arg("dir"));

    // IMGUI_API bool          Checkbox(const char* label, bool* v);
    m.def(
        "Checkbox",
        [](const char* label, bool v) {
            bool result = ImGui::Checkbox(label, &v);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"));

    // IMGUI_API bool          CheckboxFlags(const char* label, int* flags, int flags_value);
    m.def(
        "CheckboxFlags",
        [](const char* label, int flags, int flags_value) {
            bool result = ImGui::CheckboxFlags(label, &flags, flags_value);
            return std::make_tuple(result, flags);
        },
        nb::arg("label"),
        nb::arg("flags"),
        nb::arg("flags_value"));

    // IMGUI_API bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    m.def(
        "CheckboxFlags",
        [](const char* label, unsigned int flags, unsigned int flags_value) {
            bool result = ImGui::CheckboxFlags(label, &flags, flags_value);
            return std::make_tuple(result, flags);
        },
        nb::arg("label"),
        nb::arg("flags"),
        nb::arg("flags_value"));

    // IMGUI_API bool          RadioButton(const char* label, bool active);
    m.def(
        "RadioButton",
        [](const char* label, bool active) { return ImGui::RadioButton(label, active); },
        nb::arg("label"),
        nb::arg("active"));

    // IMGUI_API bool          RadioButton(const char* label, int* v, int v_button);
    m.def(
        "RadioButton",
        [](const char* label, int v, int v_button) {
            bool result = ImGui::RadioButton(label, &v, v_button);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_button"));

    // IMGUI_API void          ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0), const char* overlay = NULL);
    m.def(
        "ProgressBar",
        [](float fraction, const Vec2T& size_arg, std::optional<std::string> overlay) {
            ImGui::ProgressBar(fraction, to_vec2(size_arg), to_char_ptr(overlay));
        },
        nb::arg("fraction"),
        nb::arg("size_arg") = Vec2T(-FLT_MIN, 0.f),
        nb::arg("overlay") = nb::none());

    // IMGUI_API void          Bullet();
    m.def("Bullet", []() { ImGui::Bullet(); });

    // IMGUI_API bool          TextLink(const char* label);
    m.def(
        "TextLink",
        [](std::string label) { return ImGui::TextLink(label.c_str()); },
        nb::arg("label"));

    // IMGUI_API void          TextLinkOpenURL(const char* label, const char* url = NULL);
    m.def(
        "TextLinkOpenURL",
        [](std::string label, std::optional<std::string> url) { 
            return ImGui::TextLinkOpenURL(label.c_str(), to_char_ptr(url));
        },
        nb::arg("label"),
        nb::arg("url") = nb::none());

}
// clang-format on
