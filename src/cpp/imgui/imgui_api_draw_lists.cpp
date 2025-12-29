// Background/Foreground Draw Lists

#include "imgui_utils.h"

// clang-format off

void bind_draw_lists(nb::module_& m) {
    m.def("GetBackgroundDrawList", &ImGui::GetBackgroundDrawList, nb::rv_policy::reference);
    m.def("GetForegroundDrawList", &ImGui::GetForegroundDrawList, nb::rv_policy::reference);
}
