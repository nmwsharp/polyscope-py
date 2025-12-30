#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_windows(nb::module_& m) {

    // Windows
    // IMGUI_API bool          Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    m.def(
        "Begin",
        [](const char* name, ImGuiWindowFlags flags) {
            const auto clicked = ImGui::Begin(name, nullptr, flags);
            return clicked;
        },
        nb::arg("name"),
        nb::arg("flags") = 0);
    m.def(
        "Begin",
        [](const char* name, bool open, ImGuiWindowFlags flags) {
            const auto clicked = ImGui::Begin(name, &open, flags);
            return std::make_tuple(clicked, open);
        },
        nb::arg("name"),
        nb::arg("open"),
        nb::arg("flags") = 0);

    // IMGUI_API void          End();
    m.def("End", []() { ImGui::End(); });

}
// clang-format on
