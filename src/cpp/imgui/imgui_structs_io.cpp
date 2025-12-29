// ImGuiIO struct bindings

#include "imgui_utils.h"
#include <nanobind/stl/array.h>

// clang-format off

void bind_imgui_io(nb::module_& m) {

    nb::class_<ImGuiIO>(m, "ImGuiIO")
        // Configuration
        .def_rw("ConfigFlags", &ImGuiIO::ConfigFlags)
        .def_rw("BackendFlags", &ImGuiIO::BackendFlags)
        .def_rw("DisplaySize", &ImGuiIO::DisplaySize)
        .def_rw("DeltaTime", &ImGuiIO::DeltaTime)
        .def_rw("IniSavingRate", &ImGuiIO::IniSavingRate)
        .def_rw("IniFilename", &ImGuiIO::IniFilename)
        .def_rw("LogFilename", &ImGuiIO::LogFilename)

        // Font system
        .def_rw("Fonts", &ImGuiIO::Fonts)
        .def_rw("FontGlobalScale", &ImGuiIO::FontGlobalScale)
        .def_rw("FontAllowUserScaling", &ImGuiIO::FontAllowUserScaling)
        .def_rw("FontDefault", &ImGuiIO::FontDefault)
        .def_rw("DisplayFramebufferScale", &ImGuiIO::DisplayFramebufferScale)

        // Keyboard/Gamepad Navigation options
        .def_rw("ConfigNavSwapGamepadButtons", &ImGuiIO::ConfigNavSwapGamepadButtons)
        .def_rw("ConfigNavMoveSetMousePos", &ImGuiIO::ConfigNavMoveSetMousePos)
        .def_rw("ConfigNavCaptureKeyboard", &ImGuiIO::ConfigNavCaptureKeyboard)
        .def_rw("ConfigNavEscapeClearFocusItem", &ImGuiIO::ConfigNavEscapeClearFocusItem)
        .def_rw("ConfigNavEscapeClearFocusWindow", &ImGuiIO::ConfigNavEscapeClearFocusWindow)
        .def_rw("ConfigNavCursorVisibleAuto", &ImGuiIO::ConfigNavCursorVisibleAuto)
        .def_rw("ConfigNavCursorVisibleAlways", &ImGuiIO::ConfigNavCursorVisibleAlways)

        // Miscellaneous options
        .def_rw("MouseDrawCursor", &ImGuiIO::MouseDrawCursor)
        .def_rw("ConfigMacOSXBehaviors", &ImGuiIO::ConfigMacOSXBehaviors)
        .def_rw("ConfigInputTrickleEventQueue", &ImGuiIO::ConfigInputTrickleEventQueue)
        .def_rw("ConfigInputTextCursorBlink", &ImGuiIO::ConfigInputTextCursorBlink)
        .def_rw("ConfigInputTextEnterKeepActive", &ImGuiIO::ConfigInputTextEnterKeepActive)
        .def_rw("ConfigDragClickToInputText", &ImGuiIO::ConfigDragClickToInputText)
        .def_rw("ConfigWindowsResizeFromEdges", &ImGuiIO::ConfigWindowsResizeFromEdges)
        .def_rw("ConfigWindowsMoveFromTitleBarOnly", &ImGuiIO::ConfigWindowsMoveFromTitleBarOnly)
        .def_rw("ConfigWindowsCopyContentsWithCtrlC", &ImGuiIO::ConfigWindowsCopyContentsWithCtrlC)
        .def_rw("ConfigScrollbarScrollByPage", &ImGuiIO::ConfigScrollbarScrollByPage)
        .def_rw("ConfigMemoryCompactTimer", &ImGuiIO::ConfigMemoryCompactTimer)

        // Input Behaviors
        .def_rw("MouseDoubleClickTime", &ImGuiIO::MouseDoubleClickTime)
        .def_rw("MouseDoubleClickMaxDist", &ImGuiIO::MouseDoubleClickMaxDist)
        .def_rw("MouseDragThreshold", &ImGuiIO::MouseDragThreshold)
        .def_rw("KeyRepeatDelay", &ImGuiIO::KeyRepeatDelay)
        .def_rw("KeyRepeatRate", &ImGuiIO::KeyRepeatRate)

        // Debug options
        .def_rw("ConfigErrorRecovery", &ImGuiIO::ConfigErrorRecovery)
        .def_rw("ConfigErrorRecoveryEnableAssert", &ImGuiIO::ConfigErrorRecoveryEnableAssert)
        .def_rw("ConfigErrorRecoveryEnableDebugLog", &ImGuiIO::ConfigErrorRecoveryEnableDebugLog)
        .def_rw("ConfigErrorRecoveryEnableTooltip", &ImGuiIO::ConfigErrorRecoveryEnableTooltip)
        .def_rw("ConfigDebugIsDebuggerPresent", &ImGuiIO::ConfigDebugIsDebuggerPresent)
        .def_rw("ConfigDebugHighlightIdConflicts", &ImGuiIO::ConfigDebugHighlightIdConflicts)
        .def_rw("ConfigDebugHighlightIdConflictsShowItemPicker", &ImGuiIO::ConfigDebugHighlightIdConflictsShowItemPicker)
        .def_rw("ConfigDebugBeginReturnValueOnce", &ImGuiIO::ConfigDebugBeginReturnValueOnce)
        .def_rw("ConfigDebugBeginReturnValueLoop", &ImGuiIO::ConfigDebugBeginReturnValueLoop)
        .def_rw("ConfigDebugIgnoreFocusLoss", &ImGuiIO::ConfigDebugIgnoreFocusLoss)
        .def_rw("ConfigDebugIniSettings", &ImGuiIO::ConfigDebugIniSettings)

        // Platform Identifiers
        .def_rw("BackendPlatformName", &ImGuiIO::BackendPlatformName)
        .def_rw("BackendRendererName", &ImGuiIO::BackendRendererName)

        // Input Functions
        .def("AddKeyEvent", &ImGuiIO::AddKeyEvent, nb::arg("key"), nb::arg("down"))
        .def("AddKeyAnalogEvent", &ImGuiIO::AddKeyAnalogEvent, nb::arg("key"), nb::arg("down"), nb::arg("v"))
        .def("AddMousePosEvent", &ImGuiIO::AddMousePosEvent, nb::arg("x"), nb::arg("y"))
        .def("AddMouseButtonEvent", &ImGuiIO::AddMouseButtonEvent, nb::arg("button"), nb::arg("down"))
        .def("AddMouseWheelEvent", &ImGuiIO::AddMouseWheelEvent, nb::arg("wheel_x"), nb::arg("wheel_y"))
        .def("AddMouseSourceEvent", &ImGuiIO::AddMouseSourceEvent, nb::arg("source"))
        .def("AddFocusEvent", &ImGuiIO::AddFocusEvent, nb::arg("focused"))
        .def("AddInputCharacter", &ImGuiIO::AddInputCharacter, nb::arg("c"))
        .def("AddInputCharacterUTF16", &ImGuiIO::AddInputCharacterUTF16, nb::arg("c"))
        .def("AddInputCharactersUTF8", &ImGuiIO::AddInputCharactersUTF8, nb::arg("str"))
        .def("SetKeyEventNativeData", &ImGuiIO::SetKeyEventNativeData,
            nb::arg("key"), nb::arg("native_keycode"), nb::arg("native_scancode"), nb::arg("native_legacy_index") = -1)
        .def("SetAppAcceptingEvents", &ImGuiIO::SetAppAcceptingEvents, nb::arg("accepting_events"))
        .def("ClearEventsQueue", &ImGuiIO::ClearEventsQueue)
        .def("ClearInputKeys", &ImGuiIO::ClearInputKeys)
        .def("ClearInputMouse", &ImGuiIO::ClearInputMouse)

        // Output - Updated by NewFrame() or EndFrame()/Render()
        .def_rw("WantCaptureMouse", &ImGuiIO::WantCaptureMouse)
        .def_rw("WantCaptureKeyboard", &ImGuiIO::WantCaptureKeyboard)
        .def_rw("WantTextInput", &ImGuiIO::WantTextInput)
        .def_rw("WantSetMousePos", &ImGuiIO::WantSetMousePos)
        .def_rw("WantSaveIniSettings", &ImGuiIO::WantSaveIniSettings)
        .def_rw("NavActive", &ImGuiIO::NavActive)
        .def_rw("NavVisible", &ImGuiIO::NavVisible)
        .def_rw("Framerate", &ImGuiIO::Framerate)
        .def_rw("MetricsRenderVertices", &ImGuiIO::MetricsRenderVertices)
        .def_rw("MetricsRenderIndices", &ImGuiIO::MetricsRenderIndices)
        .def_rw("MetricsRenderWindows", &ImGuiIO::MetricsRenderWindows)
        .def_rw("MetricsActiveWindows", &ImGuiIO::MetricsActiveWindows)
        .def_prop_ro("MouseDelta", [](ImGuiIO& o) { return from_vec2(o.MouseDelta); })

        // Main Input State (read-only from Python's perspective)
        .def_prop_ro("MousePos", [](ImGuiIO& o) { return from_vec2(o.MousePos); })
        .def_prop_ro("MouseDown", [](ImGuiIO& o) { return std::to_array(o.MouseDown); })
        .def_rw("MouseWheel", &ImGuiIO::MouseWheel)
        .def_rw("MouseWheelH", &ImGuiIO::MouseWheelH)
        .def_rw("MouseSource", &ImGuiIO::MouseSource)
        .def_rw("KeyCtrl", &ImGuiIO::KeyCtrl)
        .def_rw("KeyShift", &ImGuiIO::KeyShift)
        .def_rw("KeyAlt", &ImGuiIO::KeyAlt)
        .def_rw("KeySuper", &ImGuiIO::KeySuper)

        // Other state
        .def_rw("KeyMods", &ImGuiIO::KeyMods)
        .def_rw("WantCaptureMouseUnlessPopupClose", &ImGuiIO::WantCaptureMouseUnlessPopupClose)
        .def_rw("MousePosPrev", &ImGuiIO::MousePosPrev)
        .def_prop_ro("MouseClickedPos", [](ImGuiIO& o) { return std::to_array(o.MouseClickedPos); })
        .def_prop_ro("MouseClickedTime", [](ImGuiIO& o) { return std::to_array(o.MouseClickedTime); })
        .def_prop_ro("MouseClicked", [](ImGuiIO& o) { return std::to_array(o.MouseClicked); })
        .def_prop_ro("MouseDoubleClicked", [](ImGuiIO& o) { return std::to_array(o.MouseDoubleClicked); })
        .def_prop_ro("MouseClickedCount", [](ImGuiIO& o) { return std::to_array(o.MouseClickedCount); })
        .def_prop_ro("MouseClickedLastCount", [](ImGuiIO& o) { return std::to_array(o.MouseClickedLastCount); })
        .def_prop_ro("MouseReleased", [](ImGuiIO& o) { return std::to_array(o.MouseReleased); })
        .def_prop_ro("MouseDownOwned", [](ImGuiIO& o) { return std::to_array(o.MouseDownOwned); })
        .def_prop_ro("MouseDownOwnedUnlessPopupClose", [](ImGuiIO& o) { return std::to_array(o.MouseDownOwnedUnlessPopupClose); })
        .def_prop_ro("MouseDownDuration", [](ImGuiIO& o) { return std::to_array(o.MouseDownDuration); })
        .def_prop_ro("MouseDownDurationPrev", [](ImGuiIO& o) { return std::to_array(o.MouseDownDurationPrev); })
        .def_prop_ro("MouseDragMaxDistanceSqr", [](ImGuiIO& o) { return std::to_array(o.MouseDragMaxDistanceSqr); })
        .def_rw("PenPressure", &ImGuiIO::PenPressure)
        .def_rw("AppFocusLost", &ImGuiIO::AppFocusLost)
        .def_rw("InputQueueSurrogate", &ImGuiIO::InputQueueSurrogate)
        .def_rw("InputQueueCharacters", &ImGuiIO::InputQueueCharacters)

        // Note: The following are intentionally not bound:
        // - UserData, BackendPlatformUserData, BackendRendererUserData, BackendLanguageUserData (void* pointers)
        // - Ctx (internal context pointer)
        // - KeysData (low-level key state array, use IsKeyXXX functions instead)
        // - Legacy/obsolete fields
    ;
}
