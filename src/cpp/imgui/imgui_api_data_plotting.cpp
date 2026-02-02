#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_data_plotting(nb::module_& m) {

    // Widgets: Data Plotting
    // IMGUI_API void          PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    m.def(
        "PlotLines",
        [](const char* label, const Eigen::Ref<const Eigen::VectorXf>& values, int values_offset, 
           std::optional<std::string> overlay_text, float scale_min, float scale_max, const Vec2T& graph_size) {
            ImGui::PlotLines(label, values.data(), static_cast<int>(values.size()), 
                             values_offset, to_char_ptr(overlay_text), scale_min, scale_max, to_vec2(graph_size));
        },
        nb::arg("label"),
        nb::arg("values"),
        nb::arg("values_offset") = 0,
        nb::arg("overlay_text") = nb::none(),
        nb::arg("scale_min") = FLT_MAX,
        nb::arg("scale_max") = FLT_MAX,
        nb::arg("graph_size") = Vec2T(0.f, 0.f)
    );

    // IMGUI_API void          PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
    // TODO: Callback version not bound

    // IMGUI_API void          PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    m.def(
        "PlotHistogram",
        [](const char* label, const Eigen::Ref<const Eigen::VectorXf>& values, int values_offset, 
           std::optional<std::string> overlay_text, float scale_min, float scale_max, const Vec2T& graph_size) {
            ImGui::PlotHistogram(label, values.data(), static_cast<int>(values.size()), 
                                 values_offset, to_char_ptr(overlay_text), scale_min, scale_max, to_vec2(graph_size));
        },
        nb::arg("label"),
        nb::arg("values"),
        nb::arg("values_offset") = 0,
        nb::arg("overlay_text") = nb::none(),
        nb::arg("scale_min") = FLT_MAX,
        nb::arg("scale_max") = FLT_MAX,
        nb::arg("graph_size") = Vec2T(0.f, 0.f)
    );

    // IMGUI_API void          PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
    // TODO: Callback version not bound

    // IMGUI_API void          Value(const char* prefix, bool b);
    m.def(
        "Value",
        [](const char* prefix, bool b) { ImGui::Value(prefix, b); },
        nb::arg("prefix"),
        nb::arg("b"));

    // IMGUI_API void          Value(const char* prefix, int v);
    m.def(
        "Value",
        [](const char* prefix, int v) { ImGui::Value(prefix, v); },
        nb::arg("prefix"),
        nb::arg("v"));

    // IMGUI_API void          Value(const char* prefix, unsigned int v);
    m.def(
        "Value",
        [](const char* prefix, unsigned int v) { ImGui::Value(prefix, v); },
        nb::arg("prefix"),
        nb::arg("v"));

    // IMGUI_API void          Value(const char* prefix, float v, const char* float_format = NULL);
    m.def(
        "Value",
        [](const char* prefix, float v, std::optional<std::string> float_format) { ImGui::Value(prefix, v, to_char_ptr(float_format)); },
        nb::arg("prefix"),
        nb::arg("v"),
        nb::arg("float_format") = nb::none());

}
// clang-format on
