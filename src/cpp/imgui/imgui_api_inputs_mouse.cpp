// Inputs Utilities: Mouse

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_inputs_mouse(nb::module_& m) {
    // IMGUI_API bool          IsMouseDown(ImGuiMouseButton button);                               // is mouse button held?
    m.def("IsMouseDown", &ImGui::IsMouseDown, nb::arg("button"));

    // IMGUI_API bool          IsMouseClicked(ImGuiMouseButton button, bool repeat = false);       // did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1.
    m.def("IsMouseClicked", &ImGui::IsMouseClicked, nb::arg("button"), nb::arg("repeat") = false);

    // IMGUI_API bool          IsMouseReleased(ImGuiMouseButton button);                           // did mouse button released? (went from Down to !Down)
    m.def("IsMouseReleased", &ImGui::IsMouseReleased, nb::arg("button"));

    // IMGUI_API bool          IsMouseDoubleClicked(ImGuiMouseButton button);                      // did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)
    m.def("IsMouseDoubleClicked", &ImGui::IsMouseDoubleClicked, nb::arg("button"));

    // IMGUI_API bool          IsMouseReleasedWithDelay(ImGuiMouseButton button, float delay);     // was a mouse release right after a double-click that was previously latched by a mouse click with delay?
    m.def("IsMouseReleasedWithDelay", &ImGui::IsMouseReleasedWithDelay, nb::arg("button"), nb::arg("delay"));

    // IMGUI_API int           GetMouseClickedCount(ImGuiMouseButton button);                      // return the number of successive mouse-clicks at the time where a click happen (otherwise 0).
    m.def("GetMouseClickedCount", &ImGui::GetMouseClickedCount, nb::arg("button"));

    // IMGUI_API bool          IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);// is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.
    m.def("IsMouseHoveringRect", &ImGui::IsMouseHoveringRect, nb::arg("r_min"), nb::arg("r_max"), nb::arg("clip") = true);

    // IMGUI_API bool          IsMousePosValid(const ImVec2* mouse_pos = NULL);                    // by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available
    m.def("IsMousePosValid", [](std::optional<ImVec2> mouse_pos) {
        if (mouse_pos.has_value()) {
            ImVec2 pos = mouse_pos.value();
            return ImGui::IsMousePosValid(&pos);
        } else {
            return ImGui::IsMousePosValid(nullptr);
        }
    }, nb::arg("mouse_pos") = std::nullopt);

    // IMGUI_API bool          IsAnyMouseDown();                                                   // [WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid.
    m.def("IsAnyMouseDown", &ImGui::IsAnyMouseDown);

    // IMGUI_API ImVec2        GetMousePos();                                                      // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
    m.def("GetMousePos", []() {
        return from_vec2(ImGui::GetMousePos());
    });

    // IMGUI_API ImVec2        GetMousePosOnOpeningCurrentPopup();                                 // retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)
    m.def("GetMousePosOnOpeningCurrentPopup", []() {
        return from_vec2(ImGui::GetMousePosOnOpeningCurrentPopup());
    });

    // IMGUI_API bool          IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f);         // is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
    m.def("IsMouseDragging", &ImGui::IsMouseDragging, nb::arg("button"), nb::arg("lock_threshold") = -1.0f);

    // IMGUI_API ImVec2        GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f);   // return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
    m.def("GetMouseDragDelta", [](ImGuiMouseButton button, float lock_threshold) {
        return from_vec2(ImGui::GetMouseDragDelta(button, lock_threshold));
    }, nb::arg("button") = 0, nb::arg("lock_threshold") = -1.0f);

    // IMGUI_API void          ResetMouseDragDelta(ImGuiMouseButton button = 0);                   //
    m.def("ResetMouseDragDelta", &ImGui::ResetMouseDragDelta, nb::arg("button") = 0);

    // IMGUI_API ImGuiMouseCursor GetMouseCursor();                                                // get desired mouse cursor shape. Important: reset in ImGui::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
    m.def("GetMouseCursor", &ImGui::GetMouseCursor);

    // IMGUI_API void          SetMouseCursor(ImGuiMouseCursor cursor_type);                       // set desired mouse cursor shape
    m.def("SetMouseCursor", &ImGui::SetMouseCursor, nb::arg("cursor_type"));

    // IMGUI_API void          SetNextFrameWantCaptureMouse(bool want_capture_mouse);              // Override io.WantCaptureMouse flag next frame (said flag is left for your application to handle, typical when true it instructs your app to ignore inputs). This is equivalent to setting "io.WantCaptureMouse = want_capture_mouse;" after the next NewFrame() call.
    m.def("SetNextFrameWantCaptureMouse", &ImGui::SetNextFrameWantCaptureMouse, nb::arg("want_capture_mouse"));
}
