#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_widgets_input(nb::module_& m) {

    // Widgets: Input with Keyboard
    // IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    m.def(
        "InputText",
        [](const char* label, const std::string& buf, ImGuiInputTextFlags flags, int32_t max_str_len=1024) {
            std::string buffer = buf;
            buffer.resize(max_str_len);  // Reserve space for editing
            bool result = ImGui::InputText(label, buffer.data(), buffer.capacity(), flags);
            // Trim to actual string length
            buffer.resize(strlen(buffer.c_str()));
            return std::make_tuple(result, buffer);
        },
        nb::arg("label"),
        nb::arg("buf"),
        nb::arg("flags") = 0);
    // TODO: Callback version not bound

    // IMGUI_API bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    m.def(
        "InputTextMultiline",
        [](const char* label, const std::string& buf, const Vec2T& size, ImGuiInputTextFlags flags, int32_t max_str_len=4096) {
            std::string buffer = buf;
            buffer.resize(max_str_len);  // Reserve larger space for multiline
            bool result = ImGui::InputTextMultiline(label, buffer.data(), buffer.capacity(), to_vec2(size), flags);
            buffer.resize(strlen(buffer.c_str()));
            return std::make_tuple(result, buffer);
        },
        nb::arg("label"),
        nb::arg("buf"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("flags") = 0);
    // TODO: Callback version not bound

    // IMGUI_API bool          InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    m.def(
        "InputTextWithHint",
        [](const char* label, const char* hint, const std::string& buf, ImGuiInputTextFlags flags, int32_t max_str_len=1024) {
            std::string buffer = buf;
            buffer.resize(max_str_len);
            bool result = ImGui::InputTextWithHint(label, hint, buffer.data(), buffer.capacity(), flags);
            buffer.resize(strlen(buffer.c_str()));
            return std::make_tuple(result, buffer);
        },
        nb::arg("label"),
        nb::arg("hint"),
        nb::arg("buf"),
        nb::arg("flags") = 0);
    // TODO: Callback version not bound

    // IMGUI_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    m.def(
        "InputFloat",
        [](const char* label, float v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputFloat(label, &v, step, step_fast, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 0.0f,
        nb::arg("step_fast") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    m.def(
        "InputFloat2",
        [](const char* label, std::array<float, 2> v, const char* format, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputFloat2(label, v.data(), format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    m.def(
        "InputFloat3",
        [](const char* label, std::array<float, 3> v, const char* format, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputFloat3(label, v.data(), format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    m.def(
        "InputFloat4",
        [](const char* label, std::array<float, 4> v, const char* format, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputFloat4(label, v.data(), format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    m.def(
        "InputInt",
        [](const char* label, int v, int step, int step_fast, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputInt(label, &v, step, step_fast, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 1,
        nb::arg("step_fast") = 100,
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
    m.def(
        "InputInt2",
        [](const char* label, std::array<int, 2> v, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputInt2(label, v.data(), flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
    m.def(
        "InputInt3",
        [](const char* label, std::array<int, 3> v, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputInt3(label, v.data(), flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
    m.def(
        "InputInt4",
        [](const char* label, std::array<int, 4> v, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputInt4(label, v.data(), flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
    m.def(
        "InputDouble",
        [](const char* label, double v, double step, double step_fast, const char* format, ImGuiInputTextFlags flags) {
            bool result = ImGui::InputDouble(label, &v, step, step_fast, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 0.0,
        nb::arg("step_fast") = 0.0,
        nb::arg("format") = "%.6f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
    // TODO: InputScalar requires void* handling which is complex for Python bindings

    // IMGUI_API bool          InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
    // TODO: InputScalarN requires void* handling which is complex for Python bindings

}
// clang-format on
