#include "imgui_utils.h"

NB_MAKE_OPAQUE(ImGuiContext);

// clang-format off
void bind_imgui_api_context_creation(nb::module_& m) {

    // Context creation and access

    // IMGUI_API ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = NULL);
    m.def("CreateContext", [](ImFontAtlas* shared_font_atlas = nullptr) {
        return nb::capsule(ImGui::CreateContext(shared_font_atlas), "ImGuiContext");
    }, nb::arg("shared_font_atlas") = nullptr);

    // IMGUI_API void          DestroyContext(ImGuiContext* ctx = NULL);   // NULL = destroy current context
    m.def("DestroyContext", [](nb::capsule ctx) {
        ImGui::DestroyContext(static_cast<ImGuiContext*>(ctx.data("ImGuiContext")));
    }, nb::arg("ctx") = nullptr);

    // IMGUI_API ImGuiContext* GetCurrentContext();
    m.def("GetCurrentContext", []() {
        return nb::capsule(ImGui::GetCurrentContext(), "ImGuiContext");
    }, nb::rv_policy::reference);

    // IMGUI_API void          SetCurrentContext(ImGuiContext* ctx);
    m.def("SetCurrentContext", [](nb::capsule ctx) {
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(ctx.data("ImGuiContext")));
    }, nb::arg("ctx"));

}
// clang-format on