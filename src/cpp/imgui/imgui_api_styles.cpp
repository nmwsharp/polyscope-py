#include "imgui_utils.h"

// clang-format off
void bind_imgui_api_styles(nb::module_& m) {

    // IMGUI_API void          StyleColorsDark(ImGuiStyle* dst = NULL);
    m.def("StyleColorsDark", [](ImGuiStyle* dst) { ImGui::StyleColorsDark(dst); }, nb::arg("dst") = nullptr);

    // IMGUI_API void          StyleColorsLight(ImGuiStyle* dst = NULL);
    m.def("StyleColorsLight", [](ImGuiStyle* dst) { ImGui::StyleColorsLight(dst); }, nb::arg("dst") = nullptr); 

    // IMGUI_API void          StyleColorsClassic(ImGuiStyle* dst = NULL);
    m.def("StyleColorsClassic", [](ImGuiStyle* dst) { ImGui::StyleColorsClassic(dst); }, nb::arg("dst") = nullptr);

}
// clang-format on