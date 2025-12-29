// Debug Utilities

#include "imgui_utils.h"

// clang-format off

void bind_debug(nb::module_& m) {
    m.def("DebugTextEncoding", &ImGui::DebugTextEncoding, nb::arg("text"));
    m.def("DebugFlashStyleColor", &ImGui::DebugFlashStyleColor, nb::arg("idx"));
    m.def("DebugStartItemPicker", &ImGui::DebugStartItemPicker);
    m.def("DebugCheckVersionAndDataLayout", &ImGui::DebugCheckVersionAndDataLayout,
        nb::arg("version_str"),
        nb::arg("sz_io"),
        nb::arg("sz_style"),
        nb::arg("sz_vec2"),
        nb::arg("sz_vec4"),
        nb::arg("sz_drawvert"),
        nb::arg("sz_drawidx"));

    // DebugLog and DebugLogV are variadic - not binding them
}
