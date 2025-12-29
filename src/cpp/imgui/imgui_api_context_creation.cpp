#include "imgui_utils.h"

// clang-format off
void bind_imgui_api_context_creation(nb::module_& m) {

    // Context creation and access

    // IMGUI_API ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = NULL);
    m.def("CreateContext", &ImGui::CreateContext, nb::rv_policy::reference);

    // IMGUI_API void          DestroyContext(ImGuiContext* ctx = NULL);   // NULL = destroy current context
    m.def("DestroyContext", &ImGui::DestroyContext, nb::arg("ctx") = nullptr);

    // IMGUI_API ImGuiContext* GetCurrentContext();
    m.def("GetCurrentContext", &ImGui::GetCurrentContext, nb::rv_policy::reference);

    // IMGUI_API void          SetCurrentContext(ImGuiContext* ctx);
    m.def("SetCurrentContext", &ImGui::SetCurrentContext, nb::arg("ctx"));

}
// clang-format on