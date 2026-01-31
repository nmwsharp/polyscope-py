#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_logging(nb::module_& m) {

    // Logging/Capture
    // IMGUI_API void          LogToTTY(int auto_open_depth = -1);
    m.def(
        "LogToTTY",
        [](int auto_open_depth) { ImGui::LogToTTY(auto_open_depth); },
        nb::arg("auto_open_depth") = -1);

    // IMGUI_API void          LogToFile(int auto_open_depth = -1, const char* filename = NULL);
    m.def(
        "LogToFile",
        [](int auto_open_depth, std::optional<std::string> filename) { 
            ImGui::LogToFile(auto_open_depth, to_char_ptr(filename)); 
        },
        nb::arg("auto_open_depth") = -1,
        nb::arg("filename") = nb::none());

    // IMGUI_API void          LogToClipboard(int auto_open_depth = -1);
    m.def(
        "LogToClipboard",
        [](int auto_open_depth) { ImGui::LogToClipboard(auto_open_depth); },
        nb::arg("auto_open_depth") = -1);

    // IMGUI_API void          LogFinish();
    m.def("LogFinish", []() { ImGui::LogFinish(); });

    // IMGUI_API void          LogButtons();
    m.def("LogButtons", []() { ImGui::LogButtons(); });

    // IMGUI_API void          LogText(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "LogText",
        [](const char* text) { ImGui::LogText("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          LogTextV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: Variadic version not bound

}
// clang-format on
