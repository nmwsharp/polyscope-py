// Clipboard Utilities

#include "imgui_utils.h"

// clang-format off

void bind_clipboard(nb::module_& m) {
    m.def("GetClipboardText", &ImGui::GetClipboardText);
    m.def("SetClipboardText", &ImGui::SetClipboardText, nb::arg("text"));
}
