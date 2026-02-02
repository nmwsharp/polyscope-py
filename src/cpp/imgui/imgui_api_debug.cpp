// Debug Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_debug(nb::module_& m) {

    // IMGUI_API void          DebugTextEncoding(const char* text);
    m.def("DebugTextEncoding", &ImGui::DebugTextEncoding, nb::arg("text"));
    
    // IMGUI_API void          DebugFlashStyleColor(ImGuiCol idx);
    m.def("DebugFlashStyleColor", &ImGui::DebugFlashStyleColor, nb::arg("idx"));

    // IMGUI_API void          DebugStartItemPicker();
    m.def("DebugStartItemPicker", &ImGui::DebugStartItemPicker);
    
    // IMGUI_API bool          DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx); // This is called by IMGUI_CHECKVERSION() macro.
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
