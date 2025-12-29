// Inputs Utilities: Mouse

#include "imgui_utils.h"

// clang-format off

void bind_inputs_mouse(nb::module_& m) {
    // Mouse buttons
    m.def("IsMouseDown", &ImGui::IsMouseDown, nb::arg("button"));
    m.def("IsMouseClicked", &ImGui::IsMouseClicked, nb::arg("button"), nb::arg("repeat") = false);
    m.def("IsMouseReleased", &ImGui::IsMouseReleased, nb::arg("button"));
    m.def("IsMouseDoubleClicked", &ImGui::IsMouseDoubleClicked, nb::arg("button"));
    m.def("IsMouseReleasedWithDelay", &ImGui::IsMouseReleasedWithDelay, nb::arg("button"), nb::arg("delay"));
    m.def("GetMouseClickedCount", &ImGui::GetMouseClickedCount, nb::arg("button"));

    // Mouse position and hovering
    m.def("IsMouseHoveringRect", &ImGui::IsMouseHoveringRect, nb::arg("r_min"), nb::arg("r_max"), nb::arg("clip") = true);
    m.def("IsMousePosValid", [](std::optional<ImVec2> mouse_pos) {
        if (mouse_pos.has_value()) {
            ImVec2 pos = mouse_pos.value();
            return ImGui::IsMousePosValid(&pos);
        } else {
            return ImGui::IsMousePosValid(nullptr);
        }
    }, nb::arg("mouse_pos") = std::nullopt);
    m.def("IsAnyMouseDown", &ImGui::IsAnyMouseDown);
    m.def("GetMousePos", &ImGui::GetMousePos);
    m.def("GetMousePosOnOpeningCurrentPopup", &ImGui::GetMousePosOnOpeningCurrentPopup);

    // Mouse dragging
    m.def("IsMouseDragging", &ImGui::IsMouseDragging, nb::arg("button"), nb::arg("lock_threshold") = -1.0f);
    m.def("GetMouseDragDelta", &ImGui::GetMouseDragDelta, nb::arg("button") = 0, nb::arg("lock_threshold") = -1.0f);
    m.def("ResetMouseDragDelta", &ImGui::ResetMouseDragDelta, nb::arg("button") = 0);

    // Mouse cursor
    m.def("GetMouseCursor", &ImGui::GetMouseCursor);
    m.def("SetMouseCursor", &ImGui::SetMouseCursor, nb::arg("cursor_type"));
    m.def("SetNextFrameWantCaptureMouse", &ImGui::SetNextFrameWantCaptureMouse, nb::arg("want_capture_mouse"));
}
