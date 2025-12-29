// Text Utilities

#include "imgui_utils.h"

// clang-format off

void bind_text_utils(nb::module_& m) {
    m.def("CalcTextSize", &ImGui::CalcTextSize,
        nb::arg("text"),
        nb::arg("text_end") = nullptr,
        nb::arg("hide_text_after_double_hash") = false,
        nb::arg("wrap_width") = -1.0f);
}
