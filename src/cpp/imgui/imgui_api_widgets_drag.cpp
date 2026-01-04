#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_drag(nb::module_& m) {

    // Widgets: Drag Sliders
    // IMGUI_API bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "DragFloat",
        [](const char* label, float v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0.0f,
        nb::arg("v_max") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "DragFloat2",
        [](const char* label, std::array<float, 2> v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragFloat2(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0.0f,
        nb::arg("v_max") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "DragFloat3",
        [](const char* label, std::array<float, 3> v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragFloat3(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1], v[2]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0.0f,
        nb::arg("v_max") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    m.def(
        "DragFloat4",
        [](const char* label, std::array<float, 4> v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragFloat4(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1], v[2], v[3]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0.0f,
        nb::arg("v_max") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    m.def(
        "DragFloatRange2",
        [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, std::string format, std::optional<std::string> format_max, ImGuiSliderFlags flags) {
            const char* format_max_ptr = nullptr;
            if(format_max.has_value()) {
                format_max_ptr = format_max->c_str();
            }
            bool result = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format.c_str(), format_max_ptr, flags);
            return std::make_tuple(result, v_current_min, v_current_max);
        },
        nb::arg("label"),
        nb::arg("v_current_min"),
        nb::arg("v_current_max"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0.0f,
        nb::arg("v_max") = 0.0f,
        nb::arg("format") = "%.3f",
        nb::arg("format_max") = nb::none(),
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "DragInt",
        [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "DragInt2",
        [](const char* label, std::array<int, 2> v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragInt2(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "DragInt3",
        [](const char* label, std::array<int, 3> v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragInt3(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1], v[2]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    m.def(
        "DragInt4",
        [](const char* label, std::array<int, 4> v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
            bool result = ImGui::DragInt4(label, v.data(), v_speed, v_min, v_max, format, flags);
            return std::make_tuple(result, std::make_tuple(v[0], v[1], v[2], v[3]));
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    m.def(
        "DragIntRange2",
        [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max, ImGuiSliderFlags flags) {
            bool result = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags);
            return std::make_tuple(result, v_current_min, v_current_max);
        },
        nb::arg("label"),
        nb::arg("v_current_min"),
        nb::arg("v_current_max"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("format_max") = nb::none(),
        nb::arg("flags") = 0);

    // IMGUI_API bool          DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
    // TODO: DragScalar requires void* handling which is complex for Python bindings

    // IMGUI_API bool          DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
    // TODO: DragScalarN requires void* handling which is complex for Python bindings

}
// clang-format on
