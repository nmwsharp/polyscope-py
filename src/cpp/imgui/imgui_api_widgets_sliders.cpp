#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_sliders(nb::module_& m) {

    // Widgets: Regular Sliders
    // IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderFloat",
        [](const char* label, float v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderFloat(label, &v, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderFloat2",
        [](const char* label, std::array<float, 2> v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderFloat2(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderFloat3",
        [](const char* label, std::array<float, 3> v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderFloat3(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderFloat4",
        [](const char* label, std::array<float, 4> v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderFloat4(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderAngle",
        [](const char* label, float v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format, flags);
            return std::make_tuple(result, v_rad);
        },
        nb::arg("label"),
        nb::arg("v_rad"),
        nb::arg("v_degrees_min") = -360.0f,
        nb::arg("v_degrees_max") = +360.0f,
        nb::arg("format") = "%.0f deg",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderInt",
        [](const char* label, int v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderInt(label, &v, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderInt2",
        [](const char* label, std::array<int, 2> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderInt2(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderInt3",
        [](const char* label, std::array<int, 3> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderInt3(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "SliderInt4",
        [](const char* label, std::array<int, 4> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::SliderInt4(label, v.data(), v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    // TODO: SliderScalar requires void* handling which is complex for Python bindings

    // IMGUI_API bool          SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    // TODO: SliderScalarN requires void* handling which is complex for Python bindings

    // IMGUI_API bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "VSliderFloat",
        [](const char* label, const Vec2T& size, float v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::VSliderFloat(label, to_vec2(size), &v, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("size"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "VSliderInt",
        [](const char* label, const Vec2T& size, int v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::VSliderInt(label, to_vec2(size), &v, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("size"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    // TODO: VSliderScalar requires void* handling which is complex for Python bindings

}
// clang-format on
