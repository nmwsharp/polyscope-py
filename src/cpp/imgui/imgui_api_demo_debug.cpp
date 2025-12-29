#include "imgui_utils.h"

// clang-format off
void bind_imgui_api_demo_debug(nb::module_& m) {

    // Demo, Debug, Information

    // IMGUI_API void          ShowDemoWindow(bool* p_open = NULL);
    m.def(
        "ShowDemoWindow",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowDemoWindow(&open_);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API void          ShowMetricsWindow(bool* p_open = NULL);
    m.def(
        "ShowMetricsWindow",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowMetricsWindow(&open_);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API void          ShowDebugLogWindow(bool* p_open = NULL);
    m.def(
        "ShowDebugLogWindow",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowDebugLogWindow(&open_);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API void          ShowIDStackToolWindow(bool* p_open = NULL);
    m.def(
        "ShowIDStackToolWindow",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowIDStackToolWindow(&open_);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API void          ShowAboutWindow(bool* p_open = NULL);
    m.def(
        "ShowAboutWindow",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowAboutWindow(&open_);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API void          ShowStyleEditor(ImGuiStyle* ref = NULL);
    m.def(
        "ShowStyleEditor",
        [](bool open) {
            auto open_ = open;
            ImGui::ShowStyleEditor(nullptr);
            return open_;
        },
        nb::arg("open") = true);

    // IMGUI_API bool          ShowStyleSelector(const char* label);
    m.def(
        "ShowStyleSelector",
        [](const char* label) {
            return ImGui::ShowStyleSelector(label);
        },
        nb::arg("label"));

    // IMGUI_API void          ShowFontSelector(const char* label);
    m.def(
        "ShowFontSelector",
        [](const char* label) {
            ImGui::ShowFontSelector(label);
        },
        nb::arg("label"));

    // IMGUI_API void          ShowUserGuide();
    m.def("ShowUserGuide", []() { ImGui::ShowUserGuide(); });

    // IMGUI_API const char*   GetVersion();
    m.def("GetVersion", []() { return ImGui::GetVersion(); });

}
// clang-format on