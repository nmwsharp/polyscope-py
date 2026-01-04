// Text Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_text_utils(nb::module_& m) {
    // IMGUI_API ImVec2        CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
    m.def("CalcTextSize", [](std::string text, bool hide_text_after_double_hash, float wrap_width) {
        return from_vec2(ImGui::CalcTextSize(text.c_str(), nullptr, hide_text_after_double_hash, wrap_width));
    },
        nb::arg("text"),
        nb::arg("hide_text_after_double_hash") = false,
        nb::arg("wrap_width") = -1.0f);
}
