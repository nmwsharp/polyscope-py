// Background/Foreground Draw Lists

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_draw_lists(nb::module_& m) {
    // IMGUI_API ImDrawList*   GetBackgroundDrawList();                                            // get background draw list for the viewport associated to the current window. this draw list will be the first rendering one. Useful to quickly draw shapes/text behind dear imgui contents.
    m.def("GetBackgroundDrawList", &ImGui::GetBackgroundDrawList, nb::rv_policy::reference);

    // IMGUI_API ImDrawList*   GetForegroundDrawList();                                            // get foreground draw list for the viewport associated to the current window. this draw list will be the last rendered one. Useful to quickly draw shapes/text over dear imgui contents.
    m.def("GetForegroundDrawList", &ImGui::GetForegroundDrawList, nb::rv_policy::reference);
}
