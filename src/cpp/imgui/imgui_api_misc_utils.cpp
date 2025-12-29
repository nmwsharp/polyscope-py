// Miscellaneous Utilities

#include "imgui_utils.h"

// clang-format off

void bind_misc_utils(nb::module_& m) {
    // Rectangle visibility testing
    m.def("IsRectVisible", nb::overload_cast<const ImVec2&>(&ImGui::IsRectVisible), nb::arg("size"));
    m.def("IsRectVisible", nb::overload_cast<const ImVec2&, const ImVec2&>(&ImGui::IsRectVisible), nb::arg("rect_min"), nb::arg("rect_max"));

    // Time and frame count
    m.def("GetTime", &ImGui::GetTime);
    m.def("GetFrameCount", &ImGui::GetFrameCount);

    // Draw list shared data
    m.def("GetDrawListSharedData", &ImGui::GetDrawListSharedData, nb::rv_policy::reference);

    // Style color name
    m.def("GetStyleColorName", &ImGui::GetStyleColorName, nb::arg("idx"));

    // State storage
    m.def("SetStateStorage", &ImGui::SetStateStorage, nb::arg("storage"));
    m.def("GetStateStorage", &ImGui::GetStateStorage, nb::rv_policy::reference);
}
