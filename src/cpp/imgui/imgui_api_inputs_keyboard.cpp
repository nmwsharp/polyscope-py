// Inputs Utilities: Keyboard/Mouse/Gamepad

#include "imgui_utils.h"

// clang-format off

void bind_inputs_keyboard(nb::module_& m) {
    // Keyboard
    m.def("IsKeyDown", &ImGui::IsKeyDown, nb::arg("key"));
    m.def("IsKeyPressed", &ImGui::IsKeyPressed, nb::arg("key"), nb::arg("repeat") = true);
    m.def("IsKeyReleased", &ImGui::IsKeyReleased, nb::arg("key"));
    m.def("IsKeyChordPressed", &ImGui::IsKeyChordPressed, nb::arg("key_chord"));
    m.def("GetKeyPressedAmount", &ImGui::GetKeyPressedAmount, nb::arg("key"), nb::arg("repeat_delay"), nb::arg("rate"));
    m.def("GetKeyName", &ImGui::GetKeyName, nb::arg("key"));
    m.def("SetNextFrameWantCaptureKeyboard", &ImGui::SetNextFrameWantCaptureKeyboard, nb::arg("want_capture_keyboard"));

    // Shortcut Testing & Routing [BETA]
    // m.def("Shortcut", &ImGui::Shortcut, nb::arg("key_chord"), nb::arg("flags") = 0);
    // m.def("SetNextItemShortcut", &ImGui::SetNextItemShortcut, nb::arg("key_chord"), nb::arg("flags") = 0);

    // Key Ownership [BETA]
    // m.def("SetItemKeyOwner", &ImGui::SetItemKeyOwner, nb::arg("key"));
}
