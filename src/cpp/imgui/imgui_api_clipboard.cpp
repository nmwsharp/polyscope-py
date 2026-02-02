// Clipboard Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_clipboard(nb::module_& m) {
    // IMGUI_API const char*   GetClipboardText();
    m.def("GetClipboardText", &ImGui::GetClipboardText);

    // IMGUI_API void          SetClipboardText(const char* text);
    m.def("SetClipboardText", &ImGui::SetClipboardText, nb::arg("text"));
}
