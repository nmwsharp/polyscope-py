#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_focus_activation(nb::module_& m) {

    // Focus, Activation
    // IMGUI_API void          SetItemDefaultFocus();
    m.def("SetItemDefaultFocus", []() { ImGui::SetItemDefaultFocus(); });

    // IMGUI_API void          SetKeyboardFocusHere(int offset = 0);
    m.def(
        "SetKeyboardFocusHere",
        [](int offset) { ImGui::SetKeyboardFocusHere(offset); },
        nb::arg("offset") = 0);

    // IMGUI_API void          SetNavCursorVisible(bool visible);
    m.def(
        "SetNavCursorVisible",
        [](bool visible) { ImGui::SetNavCursorVisible(visible); },
        nb::arg("visible"));

}
// clang-format on
