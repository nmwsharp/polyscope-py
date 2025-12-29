// Inputs Utilities: Keyboard

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_inputs_keyboard(nb::module_& m) {
    // IMGUI_API bool          IsKeyDown(ImGuiKey key);                                            // is key being held.
    m.def("IsKeyDown", &ImGui::IsKeyDown, nb::arg("key"));

    // IMGUI_API bool          IsKeyPressed(ImGuiKey key, bool repeat = true);                     // was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
    m.def("IsKeyPressed", &ImGui::IsKeyPressed, nb::arg("key"), nb::arg("repeat") = true);

    // IMGUI_API bool          IsKeyReleased(ImGuiKey key);                                        // was key released (went from Down to !Down)?
    m.def("IsKeyReleased", &ImGui::IsKeyReleased, nb::arg("key"));

    // IMGUI_API bool          IsKeyChordPressed(ImGuiKeyChord key_chord);                         // was key chord (mods + key) pressed, e.g. you can pass 'ImGuiMod_Ctrl | ImGuiKey_S' as a key-chord. This doesn't do any routing or focus check, please consider using Shortcut() function instead.
    m.def("IsKeyChordPressed", &ImGui::IsKeyChordPressed, nb::arg("key_chord"));

    // IMGUI_API int           GetKeyPressedAmount(ImGuiKey key, float repeat_delay, float rate);  // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
    m.def("GetKeyPressedAmount", &ImGui::GetKeyPressedAmount, nb::arg("key"), nb::arg("repeat_delay"), nb::arg("rate"));

    // IMGUI_API const char*   GetKeyName(ImGuiKey key);                                           // [DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared.
    m.def("GetKeyName", &ImGui::GetKeyName, nb::arg("key"));

    // IMGUI_API void          SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard);        // Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard"; after the next NewFrame() call.
    m.def("SetNextFrameWantCaptureKeyboard", &ImGui::SetNextFrameWantCaptureKeyboard, nb::arg("want_capture_keyboard"));

    // Shortcut Testing & Routing [BETA]
    // IMGUI_API bool          Shortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);
    // m.def("Shortcut", &ImGui::Shortcut, nb::arg("key_chord"), nb::arg("flags") = 0);

    // IMGUI_API void          SetNextItemShortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);
    // m.def("SetNextItemShortcut", &ImGui::SetNextItemShortcut, nb::arg("key_chord"), nb::arg("flags") = 0);

    // Key Ownership [BETA]
    // IMGUI_API void          SetItemKeyOwner(ImGuiKey key);                                      // Set key owner to last item ID if it is hovered or active. Equivalent to 'if (IsItemHovered() || IsItemActive()) { SetKeyOwner(key, GetItemID());'.
    // m.def("SetItemKeyOwner", &ImGui::SetItemKeyOwner, nb::arg("key"));
}
