
from typing import List, NewType, Optional, Tuple, Union, overload
from enum import Enum

ImGuiID = NewType("ImGuiID", int)
ImGuiKeyChord = NewType("ImGuiKeyChord", int)

class ImGuiMultiSelectFlags(Enum):
    ImGuiMultiSelectFlags_None = 0
    ImGuiMultiSelectFlags_SingleSelect = 1
    ImGuiMultiSelectFlags_NoSelectAll = 2
    ImGuiMultiSelectFlags_NoRangeSelect = 4
    ImGuiMultiSelectFlags_NoAutoSelect = 8
    ImGuiMultiSelectFlags_NoAutoClear = 16
    ImGuiMultiSelectFlags_NoAutoClearOnReselect = 32
    ImGuiMultiSelectFlags_BoxSelect1d = 64
    ImGuiMultiSelectFlags_BoxSelect2d = 128
    ImGuiMultiSelectFlags_BoxSelectNoScroll = 256
    ImGuiMultiSelectFlags_ClearOnEscape = 512
    ImGuiMultiSelectFlags_ClearOnClickVoid = 1024
    ImGuiMultiSelectFlags_ScopeWindow = 2048
    ImGuiMultiSelectFlags_ScopeRect = 4096
    ImGuiMultiSelectFlags_SelectOnClick = 8192
    ImGuiMultiSelectFlags_SelectOnClickRelease = 16384
    ImGuiMultiSelectFlags_NavWrapX = 65536

class ImGuiWindowFlags(Enum):
    ImGuiWindowFlags_None = 0
    ImGuiWindowFlags_NoTitleBar = 1 << 0
    ImGuiWindowFlags_NoResize = 1 << 1
    ImGuiWindowFlags_NoMove = 1 << 2
    ImGuiWindowFlags_NoScrollbar = 1 << 3
    ImGuiWindowFlags_NoScrollWithMouse = 1 << 4
    ImGuiWindowFlags_NoCollapse = 1 << 5
    ImGuiWindowFlags_AlwaysAutoResize = 1 << 6
    ImGuiWindowFlags_NoBackground = 1 << 7
    ImGuiWindowFlags_NoSavedSettings = 1 << 8
    ImGuiWindowFlags_NoMouseInputs = 1 << 9
    ImGuiWindowFlags_MenuBar = 1 << 10
    ImGuiWindowFlags_HorizontalScrollbar = 1 << 11
    ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12
    ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15
    ImGuiWindowFlags_NoNavInputs = 1 << 16
    ImGuiWindowFlags_NoNavFocus = 1 << 17
    ImGuiWindowFlags_UnsavedDocument = 1 << 18
    ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse
    ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    ImGuiWindowFlags_ChildWindow = 1 << 24
    ImGuiWindowFlags_Tooltip = 1 << 25
    ImGuiWindowFlags_Popup = 1 << 26
    ImGuiWindowFlags_Modal = 1 << 27
    ImGuiWindowFlags_ChildMenu = 1 << 28
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 30
    ImGuiWindowFlags_NavFlattened = 1 << 31

class ImGuiChildFlags(Enum):
    ImGuiChildFlags_None = 0
    ImGuiChildFlags_Border = 1 << 0
    ImGuiChildFlags_AlwaysUseWindowPadding = 1 << 1
    ImGuiChildFlags_ResizeX = 1 << 2
    ImGuiChildFlags_ResizeY = 1 << 3
    ImGuiChildFlags_AutoResizeX = 1 << 4
    ImGuiChildFlags_AutoResizeY = 1 << 5
    ImGuiChildFlags_AlwaysAutoResize = 1 << 6
    ImGuiChildFlags_FrameStyle = 1 << 7
    ImGuiChildFlags_NavFlattened = 1 << 8

class ImGuiItemFlags(Enum):
    ImGuiItemFlags_None = 0
    ImGuiItemFlags_NoTabStop = 1 << 0
    ImGuiItemFlags_NoNav = 1 << 1
    ImGuiItemFlags_NoNavDefaultFocus = 1 << 2
    ImGuiItemFlags_ButtonRepeat = 1 << 3
    ImGuiItemFlags_AutoClosePopups = 1 << 4

class ImGuiInputTextFlags(Enum):
    ImGuiInputTextFlags_None = 0
    ImGuiInputTextFlags_CharsDecimal = 1 << 0
    ImGuiInputTextFlags_CharsHexadecimal = 1 << 1
    ImGuiInputTextFlags_CharsScientific = 1 << 2
    ImGuiInputTextFlags_CharsUppercase = 1 << 3
    ImGuiInputTextFlags_CharsNoBlank = 1 << 4
    ImGuiInputTextFlags_AllowTabInput = 1 << 5
    ImGuiInputTextFlags_EnterReturnsTrue = 1 << 6
    ImGuiInputTextFlags_EscapeClearsAll = 1 << 7
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 8
    ImGuiInputTextFlags_ReadOnly = 1 << 9
    ImGuiInputTextFlags_Password = 1 << 10
    ImGuiInputTextFlags_AlwaysOverwrite = 1 << 11
    ImGuiInputTextFlags_AutoSelectAll = 1 << 12
    ImGuiInputTextFlags_ParseEmptyRefVal = 1 << 13
    ImGuiInputTextFlags_DisplayEmptyRefVal = 1 << 14
    ImGuiInputTextFlags_NoHorizontalScroll = 1 << 15
    ImGuiInputTextFlags_NoUndoRedo = 1 << 16
    ImGuiInputTextFlags_CallbackCompletion = 1 << 17
    ImGuiInputTextFlags_CallbackHistory = 1 << 18
    ImGuiInputTextFlags_CallbackAlways = 1 << 19
    ImGuiInputTextFlags_CallbackCharFilter = 1 << 20
    ImGuiInputTextFlags_CallbackResize = 1 << 21
    ImGuiInputTextFlags_CallbackEdit = 1 << 22

class ImGuiTreeNodeFlags(Enum):
    ImGuiTreeNodeFlags_None = 0
    ImGuiTreeNodeFlags_Selected = 1 << 0
    ImGuiTreeNodeFlags_Framed = 1 << 1
    ImGuiTreeNodeFlags_AllowOverlap = 1 << 2
    ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3
    ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4
    ImGuiTreeNodeFlags_DefaultOpen = 1 << 5
    ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6
    ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7
    ImGuiTreeNodeFlags_Leaf = 1 << 8
    ImGuiTreeNodeFlags_Bullet = 1 << 9
    ImGuiTreeNodeFlags_FramePadding = 1 << 10
    ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11
    ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12
    ImGuiTreeNodeFlags_SpanTextWidth = 1 << 13
    ImGuiTreeNodeFlags_SpanAllColumns = 1 << 14
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 15
    ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
    ImGuiTreeNodeFlags_AllowItemOverlap = ImGuiTreeNodeFlags_AllowOverlap

class ImGuiPopupFlags(Enum):
    ImGuiPopupFlags_None = 0
    ImGuiPopupFlags_MouseButtonLeft = 0
    ImGuiPopupFlags_MouseButtonRight = 1
    ImGuiPopupFlags_MouseButtonMiddle = 2
    ImGuiPopupFlags_MouseButtonMask_ = 0x1F
    ImGuiPopupFlags_MouseButtonDefault_ = 1
    ImGuiPopupFlags_NoReopen = 1 << 5
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 7
    ImGuiPopupFlags_NoOpenOverItems = 1 << 8
    ImGuiPopupFlags_AnyPopupId = 1 << 10
    ImGuiPopupFlags_AnyPopupLevel = 1 << 11
    ImGuiPopupFlags_AnyPopup = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel

class ImGuiSelectableFlags(Enum):
    ImGuiSelectableFlags_None = 0
    ImGuiSelectableFlags_NoAutoClosePopups = 1 << 0
    ImGuiSelectableFlags_SpanAllColumns = 1 << 1
    ImGuiSelectableFlags_AllowDoubleClick = 1 << 2
    ImGuiSelectableFlags_Disabled = 1 << 3
    ImGuiSelectableFlags_AllowOverlap = 1 << 4
    ImGuiSelectableFlags_Highlight = 1 << 5
    ImGuiSelectableFlags_DontClosePopups = ImGuiSelectableFlags_NoAutoClosePopups
    ImGuiSelectableFlags_AllowItemOverlap = ImGuiSelectableFlags_AllowOverlap

class ImGuiComboFlags(Enum):
    ImGuiComboFlags_None = 0
    ImGuiComboFlags_PopupAlignLeft = 1 << 0
    ImGuiComboFlags_HeightSmall = 1 << 1
    ImGuiComboFlags_HeightRegular = 1 << 2
    ImGuiComboFlags_HeightLarge = 1 << 3
    ImGuiComboFlags_HeightLargest = 1 << 4
    ImGuiComboFlags_NoArrowButton = 1 << 5
    ImGuiComboFlags_NoPreview = 1 << 6
    ImGuiComboFlags_WidthFitPreview = 1 << 7
    ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest

class ImGuiTabBarFlags(Enum):
    ImGuiTabBarFlags_None = 0
    ImGuiTabBarFlags_Reorderable = 1 << 0
    ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1
    ImGuiTabBarFlags_TabListPopupButton = 1 << 2
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3
    ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4
    ImGuiTabBarFlags_NoTooltip = 1 << 5
    ImGuiTabBarFlags_DrawSelectedOverline = 1 << 6
    ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 7
    ImGuiTabBarFlags_FittingPolicyScroll = 1 << 8
    ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll
    ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown

class ImGuiTabItemFlags(Enum):
    ImGuiTabItemFlags_None = 0
    ImGuiTabItemFlags_UnsavedDocument = 1 << 0
    ImGuiTabItemFlags_SetSelected = 1 << 1
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2
    ImGuiTabItemFlags_NoPushId = 1 << 3
    ImGuiTabItemFlags_NoTooltip = 1 << 4
    ImGuiTabItemFlags_NoReorder = 1 << 5
    ImGuiTabItemFlags_Leading = 1 << 6
    ImGuiTabItemFlags_Trailing = 1 << 7
    ImGuiTabItemFlags_NoAssumedClosure = 1 << 8

class ImGuiFocusedFlags(Enum):
    ImGuiFocusedFlags_None = 0
    ImGuiFocusedFlags_ChildWindows = 1 << 0
    ImGuiFocusedFlags_RootWindow = 1 << 1
    ImGuiFocusedFlags_AnyWindow = 1 << 2
    ImGuiFocusedFlags_NoPopupHierarchy = 1 << 3
    ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows

class ImGuiHoveredFlags(Enum):
    ImGuiHoveredFlags_None = 0
    ImGuiHoveredFlags_ChildWindows = 1 << 0
    ImGuiHoveredFlags_RootWindow = 1 << 1
    ImGuiHoveredFlags_AnyWindow = 1 << 2
    ImGuiHoveredFlags_NoPopupHierarchy = 1 << 3
    ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 5
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 7
    ImGuiHoveredFlags_AllowWhenOverlappedByItem = 1 << 8
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow = 1 << 9
    ImGuiHoveredFlags_AllowWhenDisabled = 1 << 10
    ImGuiHoveredFlags_NoNavOverride = 1 << 11
    ImGuiHoveredFlags_AllowWhenOverlapped = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow
    ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped
    ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
    ImGuiHoveredFlags_ForTooltip = 1 << 12
    ImGuiHoveredFlags_Stationary = 1 << 13
    ImGuiHoveredFlags_DelayNone = 1 << 14
    ImGuiHoveredFlags_DelayShort = 1 << 15
    ImGuiHoveredFlags_DelayNormal = 1 << 16
    ImGuiHoveredFlags_NoSharedDelay = 1 << 17

class ImGuiDragDropFlags(Enum):
    ImGuiDragDropFlags_None = 0
    ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0
    ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2
    ImGuiDragDropFlags_SourceAllowNullID = 1 << 3
    ImGuiDragDropFlags_SourceExtern = 1 << 4
    ImGuiDragDropFlags_PayloadAutoExpire = 1 << 5
    ImGuiDragDropFlags_PayloadNoCrossContext = 1 << 6
    ImGuiDragDropFlags_PayloadNoCrossProcess = 1 << 7
    ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11
    ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12
    ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect

class ImGuiDataType(Enum):
    ImGuiDataType_S8 = 0
    ImGuiDataType_U8 = 1
    ImGuiDataType_S16 = 2
    ImGuiDataType_U16 = 3
    ImGuiDataType_S32 = 4
    ImGuiDataType_U32 = 5
    ImGuiDataType_S64 = 6
    ImGuiDataType_U64 = 7
    ImGuiDataType_Float = 8
    ImGuiDataType_Double = 9
    ImGuiDataType_Bool = 10
    ImGuiDataType_COUNT = 11

class ImGuiDir(Enum):
    ImGuiDir_None = -1
    ImGuiDir_Left = 0
    ImGuiDir_Right = 1
    ImGuiDir_Up = 2
    ImGuiDir_Down = 3
    ImGuiDir_COUNT = 0

class ImGuiSortDirection(Enum):
    ImGuiSortDirection_None = 0
    ImGuiSortDirection_Ascending = 1
    ImGuiSortDirection_Descending = 2

class ImGuiKey(Enum):
    ImGuiKey_None = 0
    ImGuiKey_Tab = 512
    ImGuiKey_LeftArrow = 0
    ImGuiKey_RightArrow = 1
    ImGuiKey_UpArrow = 2
    ImGuiKey_DownArrow = 3
    ImGuiKey_PageUp = 4
    ImGuiKey_PageDown = 5
    ImGuiKey_Home = 6
    ImGuiKey_End = 7
    ImGuiKey_Insert = 8
    ImGuiKey_Delete = 9
    ImGuiKey_Backspace = 10
    ImGuiKey_Space = 11
    ImGuiKey_Enter = 12
    ImGuiKey_Escape = 13
    ImGuiKey_LeftCtrl = 14
    ImGuiKey_LeftShift = 15
    ImGuiKey_LeftAlt = 16
    ImGuiKey_LeftSuper = 17
    ImGuiKey_RightCtrl = 18
    ImGuiKey_RightShift = 19
    ImGuiKey_RightAlt = 20
    ImGuiKey_RightSuper = 21
    ImGuiKey_Menu = 22
    ImGuiKey_0 = 23
    ImGuiKey_1 = 24
    ImGuiKey_2 = 25
    ImGuiKey_3 = 26
    ImGuiKey_4 = 27
    ImGuiKey_5 = 28
    ImGuiKey_6 = 29
    ImGuiKey_7 = 30
    ImGuiKey_8 = 31
    ImGuiKey_9 = 32
    ImGuiKey_A = 33
    ImGuiKey_B = 34
    ImGuiKey_C = 35
    ImGuiKey_D = 36
    ImGuiKey_E = 37
    ImGuiKey_F = 38
    ImGuiKey_G = 39
    ImGuiKey_H = 40
    ImGuiKey_I = 41
    ImGuiKey_J = 42
    ImGuiKey_K = 43
    ImGuiKey_L = 44
    ImGuiKey_M = 45
    ImGuiKey_N = 46
    ImGuiKey_O = 47
    ImGuiKey_P = 48
    ImGuiKey_Q = 49
    ImGuiKey_R = 50
    ImGuiKey_S = 51
    ImGuiKey_T = 52
    ImGuiKey_U = 53
    ImGuiKey_V = 54
    ImGuiKey_W = 55
    ImGuiKey_X = 56
    ImGuiKey_Y = 57
    ImGuiKey_Z = 58
    ImGuiKey_F1 = 59
    ImGuiKey_F2 = 60
    ImGuiKey_F3 = 61
    ImGuiKey_F4 = 62
    ImGuiKey_F5 = 63
    ImGuiKey_F6 = 64
    ImGuiKey_F7 = 65
    ImGuiKey_F8 = 66
    ImGuiKey_F9 = 67
    ImGuiKey_F10 = 68
    ImGuiKey_F11 = 69
    ImGuiKey_F12 = 70
    ImGuiKey_F13 = 71
    ImGuiKey_F14 = 72
    ImGuiKey_F15 = 73
    ImGuiKey_F16 = 74
    ImGuiKey_F17 = 75
    ImGuiKey_F18 = 76
    ImGuiKey_F19 = 77
    ImGuiKey_F20 = 78
    ImGuiKey_F21 = 79
    ImGuiKey_F22 = 80
    ImGuiKey_F23 = 81
    ImGuiKey_F24 = 82
    ImGuiKey_Apostrophe = 83
    ImGuiKey_Comma = 84
    ImGuiKey_Minus = 85
    ImGuiKey_Period = 86
    ImGuiKey_Slash = 87
    ImGuiKey_Semicolon = 88
    ImGuiKey_Equal = 89
    ImGuiKey_LeftBracket = 90
    ImGuiKey_Backslash = 91
    ImGuiKey_RightBracket = 92
    ImGuiKey_GraveAccent = 93
    ImGuiKey_CapsLock = 94
    ImGuiKey_ScrollLock = 95
    ImGuiKey_NumLock = 96
    ImGuiKey_PrintScreen = 97
    ImGuiKey_Pause = 98
    ImGuiKey_Keypad0 = 99
    ImGuiKey_Keypad1 = 100
    ImGuiKey_Keypad2 = 101
    ImGuiKey_Keypad3 = 102
    ImGuiKey_Keypad4 = 103
    ImGuiKey_Keypad5 = 104
    ImGuiKey_Keypad6 = 105
    ImGuiKey_Keypad7 = 106
    ImGuiKey_Keypad8 = 107
    ImGuiKey_Keypad9 = 108
    ImGuiKey_KeypadDecimal = 109
    ImGuiKey_KeypadDivide = 110
    ImGuiKey_KeypadMultiply = 111
    ImGuiKey_KeypadSubtract = 112
    ImGuiKey_KeypadAdd = 113
    ImGuiKey_KeypadEnter = 114
    ImGuiKey_KeypadEqual = 115
    ImGuiKey_AppBack = 116
    ImGuiKey_AppForward = 117
    ImGuiKey_GamepadStart = 118
    ImGuiKey_GamepadBack = 119
    ImGuiKey_GamepadFaceLeft = 120
    ImGuiKey_GamepadFaceRight = 121
    ImGuiKey_GamepadFaceUp = 122
    ImGuiKey_GamepadFaceDown = 123
    ImGuiKey_GamepadDpadLeft = 124
    ImGuiKey_GamepadDpadRight = 125
    ImGuiKey_GamepadDpadUp = 126
    ImGuiKey_GamepadDpadDown = 127
    ImGuiKey_GamepadL1 = 128
    ImGuiKey_GamepadR1 = 129
    ImGuiKey_GamepadL2 = 130
    ImGuiKey_GamepadR2 = 131
    ImGuiKey_GamepadL3 = 132
    ImGuiKey_GamepadR3 = 133
    ImGuiKey_GamepadLStickLeft = 134
    ImGuiKey_GamepadLStickRight = 135
    ImGuiKey_GamepadLStickUp = 136
    ImGuiKey_GamepadLStickDown = 137
    ImGuiKey_GamepadRStickLeft = 138
    ImGuiKey_GamepadRStickRight = 139
    ImGuiKey_GamepadRStickUp = 140
    ImGuiKey_GamepadRStickDown = 141
    ImGuiKey_MouseLeft = 142
    ImGuiKey_MouseRight = 143
    ImGuiKey_MouseMiddle = 144
    ImGuiKey_MouseX1 = 145
    ImGuiKey_MouseX2 = 146
    ImGuiKey_MouseWheelX = 147
    ImGuiKey_MouseWheelY = 148
    ImGuiKey_ReservedForModCtrl = 149
    ImGuiKey_ReservedForModShift = 150
    ImGuiKey_ReservedForModAlt = 151
    ImGuiKey_ReservedForModSuper = 152
    ImGuiKey_COUNT = 153
    ImGuiMod_None = 154
    ImGuiMod_Ctrl = 155
    ImGuiMod_Shift = 156
    ImGuiMod_Alt = 157
    ImGuiMod_Super = 158
    ImGuiMod_Mask_ = 159
    ImGuiKey_NamedKey_BEGIN = 160
    ImGuiKey_NamedKey_END = 161
    ImGuiKey_NamedKey_COUNT = 162
    ImGuiKey_KeysData_SIZE = 163
    ImGuiKey_KeysData_OFFSET = 164

class ImGuiInputFlags(Enum):
    ImGuiInputFlags_None = 0
    ImGuiInputFlags_Repeat = 1
    ImGuiInputFlags_RouteActive = 1024
    ImGuiInputFlags_RouteFocused = 2048
    ImGuiInputFlags_RouteGlobal = 4096
    ImGuiInputFlags_RouteAlways = 8192
    ImGuiInputFlags_RouteOverFocused = 16384
    ImGuiInputFlags_RouteOverActive = 32768
    ImGuiInputFlags_RouteUnlessBgFocused = 65536
    ImGuiInputFlags_RouteFromRootWindow = 131072
    ImGuiInputFlags_Tooltip = 262144

class ImGuiConfigFlags(Enum):
    ImGuiConfigFlags_None = 0
    ImGuiConfigFlags_NavEnableKeyboard = 1
    ImGuiConfigFlags_NavEnableGamepad = 2
    ImGuiConfigFlags_NavEnableSetMousePos = 4
    ImGuiConfigFlags_NavNoCaptureKeyboard = 8
    ImGuiConfigFlags_NoMouse = 16
    ImGuiConfigFlags_NoMouseCursorChange = 32
    ImGuiConfigFlags_NoKeyboard = 64
    ImGuiConfigFlags_IsSRGB = 1048576
    ImGuiConfigFlags_IsTouchScreen = 2097152

class ImGuiBackendFlags(Enum):
    ImGuiBackendFlags_None = 0
    ImGuiBackendFlags_HasGamepad = 1
    ImGuiBackendFlags_HasMouseCursors = 2
    ImGuiBackendFlags_HasSetMousePos = 4
    ImGuiBackendFlags_RendererHasVtxOffset = 8

class ImGuiCol(Enum):
    ImGuiCol_Text = 0
    ImGuiCol_TextDisabled = 1
    ImGuiCol_WindowBg = 2
    ImGuiCol_ChildBg = 3
    ImGuiCol_PopupBg = 4
    ImGuiCol_Border = 5
    ImGuiCol_BorderShadow = 6
    ImGuiCol_FrameBg = 7
    ImGuiCol_FrameBgHovered = 8
    ImGuiCol_FrameBgActive = 9
    ImGuiCol_TitleBg = 10
    ImGuiCol_TitleBgActive = 11
    ImGuiCol_TitleBgCollapsed = 12
    ImGuiCol_MenuBarBg = 13
    ImGuiCol_ScrollbarBg = 14
    ImGuiCol_ScrollbarGrab = 15
    ImGuiCol_ScrollbarGrabHovered = 16
    ImGuiCol_ScrollbarGrabActive = 17
    ImGuiCol_CheckMark = 18
    ImGuiCol_SliderGrab = 19
    ImGuiCol_SliderGrabActive = 20
    ImGuiCol_Button = 21
    ImGuiCol_ButtonHovered = 22
    ImGuiCol_ButtonActive = 23
    ImGuiCol_Header = 24
    ImGuiCol_HeaderHovered = 25
    ImGuiCol_HeaderActive = 26
    ImGuiCol_Separator = 27
    ImGuiCol_SeparatorHovered = 28
    ImGuiCol_SeparatorActive = 29
    ImGuiCol_ResizeGrip = 30
    ImGuiCol_ResizeGripHovered = 31
    ImGuiCol_ResizeGripActive = 32
    ImGuiCol_TabHovered = 33
    ImGuiCol_Tab = 34
    ImGuiCol_TabSelected = 35
    ImGuiCol_TabSelectedOverline = 36
    ImGuiCol_TabDimmed = 37
    ImGuiCol_TabDimmedSelected = 38
    ImGuiCol_TabDimmedSelectedOverline = 39
    ImGuiCol_PlotLines = 40
    ImGuiCol_PlotLinesHovered = 41
    ImGuiCol_PlotHistogram = 42
    ImGuiCol_PlotHistogramHovered = 43
    ImGuiCol_TableHeaderBg = 44
    ImGuiCol_TableBorderStrong = 45
    ImGuiCol_TableBorderLight = 46
    ImGuiCol_TableRowBg = 47
    ImGuiCol_TableRowBgAlt = 48
    ImGuiCol_TextLink = 49
    ImGuiCol_TextSelectedBg = 50
    ImGuiCol_DragDropTarget = 51
    ImGuiCol_NavHighlight = 52
    ImGuiCol_NavWindowingHighlight = 53
    ImGuiCol_NavWindowingDimBg = 54
    ImGuiCol_ModalWindowDimBg = 55

class ImGuiStyleVar(Enum):
    ImGuiStyleVar_Alpha = 0
    ImGuiStyleVar_DisabledAlpha = 1
    ImGuiStyleVar_WindowPadding = 2
    ImGuiStyleVar_WindowRounding = 3
    ImGuiStyleVar_WindowBorderSize = 4
    ImGuiStyleVar_WindowMinSize = 5
    ImGuiStyleVar_WindowTitleAlign = 6
    ImGuiStyleVar_ChildRounding = 7
    ImGuiStyleVar_ChildBorderSize = 8
    ImGuiStyleVar_PopupRounding = 9
    ImGuiStyleVar_PopupBorderSize = 10
    ImGuiStyleVar_FramePadding = 11
    ImGuiStyleVar_FrameRounding = 12
    ImGuiStyleVar_FrameBorderSize = 13
    ImGuiStyleVar_ItemSpacing = 14
    ImGuiStyleVar_ItemInnerSpacing = 15
    ImGuiStyleVar_IndentSpacing = 16
    ImGuiStyleVar_CellPadding = 17
    ImGuiStyleVar_ScrollbarSize = 18
    ImGuiStyleVar_ScrollbarRounding = 19
    ImGuiStyleVar_GrabMinSize = 20
    ImGuiStyleVar_GrabRounding = 21
    ImGuiStyleVar_TabRounding = 22
    ImGuiStyleVar_TabBorderSize = 23
    ImGuiStyleVar_TabBarBorderSize = 24
    ImGuiStyleVar_TabBarOverlineSize = 25
    ImGuiStyleVar_TableAngledHeadersAngle = 26
    ImGuiStyleVar_TableAngledHeadersTextAlign = 27
    ImGuiStyleVar_ButtonTextAlign = 28
    ImGuiStyleVar_SelectableTextAlign = 29
    ImGuiStyleVar_SeparatorTextBorderSize = 30
    ImGuiStyleVar_SeparatorTextAlign = 31
    ImGuiStyleVar_SeparatorTextPadding = 32

class ImGuiButtonFlags(Enum):
    ImGuiButtonFlags_None = 0
    ImGuiButtonFlags_MouseButtonLeft = 1
    ImGuiButtonFlags_MouseButtonRight = 2
    ImGuiButtonFlags_MouseButtonMiddle = 4

class ImGuiColorEditFlags(Enum):
    ImGuiColorEditFlags_None = 0
    ImGuiColorEditFlags_NoAlpha = 2
    ImGuiColorEditFlags_NoPicker = 4
    ImGuiColorEditFlags_NoOptions = 8
    ImGuiColorEditFlags_NoSmallPreview = 16
    ImGuiColorEditFlags_NoInputs = 32
    ImGuiColorEditFlags_NoTooltip = 64
    ImGuiColorEditFlags_NoLabel = 128
    ImGuiColorEditFlags_NoSidePreview = 256
    ImGuiColorEditFlags_NoDragDrop = 512
    ImGuiColorEditFlags_NoBorder = 1024
    ImGuiColorEditFlags_AlphaBar = 65536
    ImGuiColorEditFlags_AlphaPreview = 131072
    ImGuiColorEditFlags_AlphaPreviewHalf = 262144
    ImGuiColorEditFlags_HDR = 524288
    ImGuiColorEditFlags_DisplayRGB = 1048576
    ImGuiColorEditFlags_DisplayHSV = 2097152
    ImGuiColorEditFlags_DisplayHex = 4194304
    ImGuiColorEditFlags_Uint8 = 8388608
    ImGuiColorEditFlags_Float = 16777216
    ImGuiColorEditFlags_PickerHueBar = 33554432
    ImGuiColorEditFlags_PickerHueWheel = 67108864
    ImGuiColorEditFlags_InputRGB = 134217728
    ImGuiColorEditFlags_InputHSV = 268435456

class ImGuiSliderFlags(Enum):
    ImGuiSliderFlags_None = 0
    ImGuiSliderFlags_AlwaysClamp = 16
    ImGuiSliderFlags_Logarithmic = 32
    ImGuiSliderFlags_NoRoundToFormat = 64
    ImGuiSliderFlags_NoInput = 128
    ImGuiSliderFlags_WrapAround = 256

class ImGuiMouseButton(Enum):
    ImGuiMouseButton_Left = 0
    ImGuiMouseButton_Right = 1
    ImGuiMouseButton_Middle = 2
    ImGuiMouseButton_COUNT = 5

class ImGuiMouseCursor(Enum):
    ImGuiMouseCursor_None = -1
    ImGuiMouseCursor_Arrow = 0
    ImGuiMouseCursor_TextInput = 1
    ImGuiMouseCursor_ResizeAll = 2
    ImGuiMouseCursor_ResizeNS = 3
    ImGuiMouseCursor_ResizeEW = 4
    ImGuiMouseCursor_ResizeNESW = 5
    ImGuiMouseCursor_ResizeNWSE = 6
    ImGuiMouseCursor_Hand = 7
    ImGuiMouseCursor_NotAllowed = 8
    ImGuiMouseCursor_COUNT = 9

class ImGuiMouseSource(Enum):
    ImGuiMouseSource_Mouse = 0
    ImGuiMouseSource_TouchScreen = 1
    ImGuiMouseSource_Pen = 2
    ImGuiMouseSource_COUNT = 3

class ImGuiCond(Enum):
    ImGuiCond_None = 0
    ImGuiCond_Always = 1
    ImGuiCond_Once = 2
    ImGuiCond_FirstUseEver = 4
    ImGuiCond_Appearing = 8

class ImGuiTableFlags(Enum):
    ImGuiTableFlags_None = 0
    ImGuiTableFlags_Resizable = 1
    ImGuiTableFlags_Reorderable = 2
    ImGuiTableFlags_Hideable = 4
    ImGuiTableFlags_Sortable = 8
    ImGuiTableFlags_NoSavedSettings = 16
    ImGuiTableFlags_ContextMenuInBody = 32
    ImGuiTableFlags_RowBg = 64
    ImGuiTableFlags_BordersInnerH = 128
    ImGuiTableFlags_BordersOuterH = 256
    ImGuiTableFlags_BordersInnerV = 512
    ImGuiTableFlags_BordersOuterV = 1024
    ImGuiTableFlags_BordersH = 1280
    ImGuiTableFlags_BordersV = 1536
    ImGuiTableFlags_BordersInner = 640
    ImGuiTableFlags_BordersOuter = 1280
    ImGuiTableFlags_Borders = 1920
    ImGuiTableFlags_NoBordersInBody = 2048
    ImGuiTableFlags_NoBordersInBodyUntilResize = 4096
    ImGuiTableFlags_SizingFixedFit = 8192
    ImGuiTableFlags_SizingFixedSame = 16384
    ImGuiTableFlags_SizingStretchProp = 24576
    ImGuiTableFlags_SizingStretchSame = 32768
    ImGuiTableFlags_NoHostExtendX = 65536
    ImGuiTableFlags_NoHostExtendY = 131072
    ImGuiTableFlags_NoKeepColumnsVisible = 262144
    ImGuiTableFlags_PreciseWidths = 524288
    ImGuiTableFlags_NoClip = 1048576
    ImGuiTableFlags_PadOuterX = 2097152
    ImGuiTableFlags_NoPadOuterX = 4194304
    ImGuiTableFlags_NoPadInnerX = 8388608
    ImGuiTableFlags_ScrollX = 16777216
    ImGuiTableFlags_ScrollY = 33554432
    ImGuiTableFlags_SortMulti = 67108864
    ImGuiTableFlags_SortTristate = 134217728
    ImGuiTableFlags_HighlightHoveredColumn = 268435456
    ImGuiTableFlags_SizingMask_ = 61440

class ImGuiTableColumnFlags(Enum):
    ImGuiTableColumnFlags_None = 0
    ImGuiTableColumnFlags_Disabled = 1
    ImGuiTableColumnFlags_DefaultHide = 2
    ImGuiTableColumnFlags_DefaultSort = 4
    ImGuiTableColumnFlags_WidthStretch = 8
    ImGuiTableColumnFlags_WidthFixed = 16
    ImGuiTableColumnFlags_NoResize = 32
    ImGuiTableColumnFlags_NoReorder = 64
    ImGuiTableColumnFlags_NoHide = 128
    ImGuiTableColumnFlags_NoClip = 256
    ImGuiTableColumnFlags_NoSort = 512
    ImGuiTableColumnFlags_NoSortAscending = 1024
    ImGuiTableColumnFlags_NoSortDescending = 2048
    ImGuiTableColumnFlags_NoHeaderLabel = 4096
    ImGuiTableColumnFlags_NoHeaderWidth = 8192
    ImGuiTableColumnFlags_PreferSortAscending = 16384
    ImGuiTableColumnFlags_PreferSortDescending = 32768
    ImGuiTableColumnFlags_IndentEnable = 65536
    ImGuiTableColumnFlags_IndentDisable = 131072
    ImGuiTableColumnFlags_AngledHeader = 262144
    ImGuiTableColumnFlags_IsEnabled = 16777216
    ImGuiTableColumnFlags_IsVisible = 33554432
    ImGuiTableColumnFlags_IsSorted = 67108864
    ImGuiTableColumnFlags_IsHovered = 134217728
    ImGuiTableColumnFlags_WidthMask_ = 24
    ImGuiTableColumnFlags_IndentMask_ = 196608
    ImGuiTableColumnFlags_StatusMask_ = 251658240
    ImGuiTableColumnFlags_NoDirectResize_ = 1073741824

class ImGuiTableRowFlags(Enum):
    ImGuiTableRowFlags_None = 0
    ImGuiTableRowFlags_Headers = 1

class ImGuiTableBgTarget(Enum):
    ImGuiTableBgTarget_None = 0
    ImGuiTableBgTarget_RowBg0 = 1
    ImGuiTableBgTarget_RowBg1 = 2
    ImGuiTableBgTarget_CellBg = 3

def NewFrame() -> None: ...
def EndFrame() -> None: ...
def Render() -> None: ...
def ShowDemoWindow(open: Optional[bool] = None) -> Optional[bool]: ...
def ShowMetricsWindow(open: Optional[bool] = None) -> Optional[bool]: ...
def ShowStyleEditor() -> None: ...
def ShowUserGuide() -> None: ...
def GetVersion() -> str: ...
def StyleColorsDark() -> None: ...
def StyleColorsLight() -> None: ...
def StyleColorsClassic() -> None: ...
def Begin(name: str, open: Optional[bool] = None, flags: ImGuiWindowFlags = 0) -> Tuple[bool, Optional[bool]]: ...
def End() -> None: ...
def BeginChild(str_id: str, size: Tuple[float, float] = (0, 0), child_flags: ImGuiChildFlags = 0, window_flags: ImGuiWindowFlags = 0) -> bool: ...
def EndChild() -> None: ...
def IsWindowAppearing() -> bool: ...
def IsWindowCollapsed() -> bool: ...
def IsWindowFocused(flags: ImGuiFocusedFlags = 0) -> bool: ...
def IsWindowHovered(flags: ImGuiHoveredFlags = 0) -> bool: ...
def GetWindowPos() -> Tuple[float, float]: ...
def GetWindowSize() -> Tuple[float, float]: ...
def SetNextWindowPos(pos: Tuple[float, float], cond: ImGuiCond = 0, pivot: Tuple[float, float] = (0, 0)) -> None: ...
def SetNextWindowSize(size: Tuple[float, float], cond: ImGuiCond = 0) -> None: ...
def SetNextWindowContentSize(size: Tuple[float, float]) -> None: ...
def SetNextWindowCollapsed(collapsed: bool, cond: ImGuiCond = 0) -> None: ...
def SetNextWindowFocus() -> None: ...
def SetNextWindowScroll(scroll: Tuple[float, float]) -> None: ...
def SetNextWindowBgAlpha(alpha: float) -> None: ...
def SetWindowPos(pos: Tuple[float, float], cond: ImGuiCond = 0) -> None: ...
def SetWindowSize(size: Tuple[float, float], cond: ImGuiCond = 0) -> None: ...
def SetWindowCollapsed(collapsed: bool, cond: ImGuiCond = 0) -> None: ...
def SetWindowFocus() -> None: ...
def SetWindowPos(name: str, pos: Tuple[float, float], cond: ImGuiCond = 0) -> None: ...
def SetWindowSize(name: str, size: Tuple[float, float], cond: ImGuiCond = 0) -> None: ...
def SetWindowCollapsed(name: str, collapsed: bool, cond: ImGuiCond = 0) -> None: ...
def SetWindowFocus(name: str) -> None: ...
def GetScrollX() -> float: ...
def GetScrollY() -> float: ...
def SetScrollX(scroll_x: float) -> None: ...
def SetScrollY(scroll_y: float) -> None: ...
def GetScrollMaxX() -> float: ...
def GetScrollMaxY() -> float: ...
def SetScrollHereX(center_x_ratio: float = 0.5) -> None: ...
def SetScrollHereY(center_y_ratio: float = 0.5) -> None: ...
def SetScrollFromPosX(local_x: float, center_x_ratio: float = 0.5) -> None: ...
def SetScrollFromPosY(local_y: float, center_y_ratio: float = 0.5) -> None: ...
def PushStyleColor(idx: ImGuiCol, col: int) -> None: ...
def PushStyleColor(idx: ImGuiCol, col: Tuple[float, float, float, float]) -> None: ...
def PopStyleColor(count: int = 1) -> None: ...
def PushStyleVar(idx: ImGuiStyleVar, val: float) -> None: ...
def PushStyleVar(idx: ImGuiStyleVar, val: Tuple[float, float]) -> None: ...
def PopStyleVar(count: int = 1) -> None: ...
def PushItemFlag(option: ImGuiItemFlags, enabled: bool) -> None: ...
def PopItemFlag() -> None: ...
def PushItemWidth(item_width: float) -> None: ...
def PopItemWidth() -> None: ...
def SetNextItemWidth(item_width: float) -> None: ...
def CalcItemWidth() -> float: ...
def PushTextWrapPos(wrap_local_pos_x: float = 0.0) -> None: ...
def PopTextWrapPos() -> None: ...
def GetFontSize() -> float: ...
def GetFontTexUvWhitePixel() -> Tuple[float, float]: ...
def GetColorU32(idx: ImGuiCol, alpha_mul: float = 1.0) -> int: ...
def GetColorU32(col: Tuple[float, float, float, float]) -> int: ...
def GetColorU32(col: int, alpha_mul: float = 1.0) -> int: ...
def GetStyleColorVec4(idx: ImGuiCol) -> Tuple[float, float, float, float]: ...
def GetCursorScreenPos() -> Tuple[float, float]: ...
def SetCursorScreenPos(pos: Tuple[float, float]) -> None: ...
def GetContentRegionAvail() -> Tuple[float, float]: ...
def GetCursorPos() -> Tuple[float, float]: ...
def GetCursorPosX() -> float: ...
def GetCursorPosY() -> float: ...
def SetCursorPos(local_pos: Tuple[float, float]) -> None: ...
def SetCursorPosX(local_x: float) -> None: ...
def SetCursorPosY(local_y: float) -> None: ...
def GetCursorStartPos() -> Tuple[float, float]: ...
def Separator() -> None: ...
def SameLine(offset_from_start_x: float = 0.0, spacing: float = -1.0) -> None: ...
def NewLine() -> None: ...
def Dummy(size: Tuple[float, float]) -> None: ...
def Unindent(indent_w: float = 0.0) -> None: ...
def BeginGroup() -> None: ...
def EndGroup() -> None: ...
def AlignTextToFramePadding() -> None: ...
def GetTextLineHeight() -> float: ...
def GetTextLineHeightWithSpacing() -> float: ...
def GetFrameHeight() -> float: ...
def GetFrameHeightWithSpacing() -> float: ...
def PushID(str_id: str) -> None: ...
def PushID(str_id_begin: str, str_id_end: str) -> None: ...
def PushID(int_id: int) -> None: ...
def GetID(str_id: str) -> ImGuiID: ...
def GetID(str_id_begin: str, str_id_end: str) -> ImGuiID: ...
def GetID(int_id: int) -> ImGuiID: ...
def Text(text: str) -> None: ...
def TextColored(col: Tuple[float, float, float, float], text: str) -> None: ...
def TextDisabled(text: str) -> None: ...
def TextWrapped(text: str) -> None: ...
def LabelText(label: str, text: str) -> None: ...
def BulletText(text: str) -> None: ...
def SeparatorText(label: str) -> None: ...
def Button(label: str, size: Tuple[float, float] = (0, 0)) -> bool: ...
def SmallButton(label: str) -> bool: ...
def InvisibleButton(str_id: str, size: Tuple[float, float], flags: ImGuiButtonFlags = 0) -> bool: ...
def ArrowButton(str_id: str, dir: ImGuiDir) -> bool: ...
def Checkbox(label: str, v: bool) -> Tuple[bool, bool]: ...
def CheckboxFlags(label: str, flags: int, flags_value: int) -> Tuple[bool, int]: ...
def RadioButton(label: str, active: bool) -> bool: ...
def RadioButton(label: str, v: int, v_button: int) -> Tuple[bool, int]: ...
def ProgressBar(fraction: float, size_arg: Tuple[float, float] = (-1.175494e-38, 0), overlay: Optional[str] = None) -> None: ...
def Bullet() -> None: ...
def TextLink(label: str) -> bool: ...
def TextLinkOpenURL(label: str, url: Optional[str] = None) -> None: ...
def BeginCombo(label: str, preview_value: str, flags: ImGuiComboFlags = 0) -> bool: ...
def EndCombo() -> None: ...
def Combo(label: str, current_item: int, items: List[str], popup_max_height_in_items: int = -1) -> Tuple[bool, int]: ...
def Combo(label: str, current_item: int, items_separated_by_zeros: str, popup_max_height_in_items: int = -1) -> Tuple[bool, int]: ...
def DragFloat(label: str, v: float, v_speed: float = 1.0, v_min: float = 0.0, v_max: float = 0.0, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, float]: ...
def DragFloat2(label: str, v: Tuple[float, float], v_speed: float = 1.0, v_min: float = 0.0, v_max: float = 0.0, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float]]: ...
def DragFloat3(label: str, v: Tuple[float, float, float], v_speed: float = 1.0, v_min: float = 0.0, v_max: float = 0.0, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float, float]]: ...
def DragFloat4(label: str, v: Tuple[float, float, float, float], v_speed: float = 1.0, v_min: float = 0.0, v_max: float = 0.0, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float, float, float]]: ...
def DragFloatRange2(label: str, v_current_min: float, v_current_max: float, v_speed: float = 1.0, v_min: float = 0.0, v_max: float = 0.0, format: str = "%.3f", format_max: Optional[str] = None, flags: ImGuiSliderFlags = 0) -> Tuple[bool, float, float]: ...
def DragInt(label: str, v: int, v_speed: float = 1.0, v_min: int = 0, v_max: int = 0, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, int]: ...
def DragInt2(label: str, v: Tuple[int, int], v_speed: float = 1.0, v_min: int = 0, v_max: int = 0, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int]]: ...
def DragInt3(label: str, v: Tuple[int, int, int], v_speed: float = 1.0, v_min: int = 0, v_max: int = 0, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int, int]]: ...
def DragInt4(label: str, v: Tuple[int, int, int, int], v_speed: float = 1.0, v_min: int = 0, v_max: int = 0, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int, int, int]]: ...
def DragIntRange2(label: str, v_current_min: int, v_current_max: int, v_speed: float = 1.0, v_min: int = 0, v_max: int = 0, format: str = "%d", format_max: Optional[str] = None, flags: ImGuiSliderFlags = 0) -> Tuple[bool, int, int]: ...
def SliderFloat(label: str, v: float, v_min: float, v_max: float, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, float]: ...
def SliderFloat2(label: str, v: Tuple[float, float], v_min: float, v_max: float, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float]]: ...
def SliderFloat3(label: str, v: Tuple[float, float, float], v_min: float, v_max: float, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float, float]]: ...
def SliderFloat4(label: str, v: Tuple[float, float, float, float], v_min: float, v_max: float, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[float, float, float, float]]: ...
def SliderAngle(label: str, v_rad: float, v_degrees_min: float = -360.0, v_degrees_max: float = +360.0, format: str = "%.0f deg", flags: ImGuiSliderFlags = 0) -> Tuple[bool, float]: ...
def SliderInt(label: str, v: int, v_min: int, v_max: int, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, int]: ...
def SliderInt2(label: str, v: Tuple[int, int], v_min: int, v_max: int, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int]]: ...
def SliderInt3(label: str, v: Tuple[int, int, int], v_min: int, v_max: int, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int, int]]: ...
def SliderInt4(label: str, v: Tuple[int, int, int, int], v_min: int, v_max: int, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, Tuple[int, int, int, int]]: ...
def VSliderFloat(label: str, size: Tuple[float, float], v: float, v_min: float, v_max: float, format: str = "%.3f", flags: ImGuiSliderFlags = 0) -> Tuple[bool, float]: ...
def VSliderInt(label: str, size: Tuple[float, float], v: int, v_min: int, v_max: int, format: str = "%d", flags: ImGuiSliderFlags = 0) -> Tuple[bool, int]: ...
def InputText(label: str, str: str, flags: ImGuiInputTextFlags = 0) -> Tuple[bool, str]: ...
def InputTextMultiline(label: str, str: str, size: Tuple[float, float] = (0, 0), flags: ImGuiInputTextFlags = 0) -> Tuple[bool, str]: ...
def InputTextWithHint(label: str, hint: str, str: str, flags: ImGuiInputTextFlags = 0) -> Tuple[bool, str]: ...
def InputFloat(label: str, v: float, step: float = 0.0, step_fast: float = 0.0, format: str = "%.3f", flags: ImGuiInputTextFlags = 0) -> Tuple[bool, float]: ...
def InputFloat2(label: str, v: Tuple[float, float], format: str = "%.3f", flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[float, float]]: ...
def InputFloat3(label: str, v: Tuple[float, float, float], format: str = "%.3f", flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[float, float, float]]: ...
def InputFloat4(label: str, v: Tuple[float, float, float, float], format: str = "%.3f", flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[float, float, float, float]]: ...
def InputInt(label: str, v: int, step: int = 1, step_fast: int = 100, flags: ImGuiInputTextFlags = 0) -> Tuple[bool, int]: ...
def InputInt2(label: str, v: Tuple[int, int], flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[int, int]]: ...
def InputInt3(label: str, v: Tuple[int, int, int], flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[int, int, int]]: ...
def InputInt4(label: str, v: Tuple[int, int, int, int], flags: ImGuiInputTextFlags = 0) -> Tuple[bool, Tuple[int, int, int, int]]: ...
def InputDouble(label: str, v: float, step: float = 0.0, step_fast: float = 0.0, format: str = "%.6f", flags: ImGuiInputTextFlags = 0) -> Tuple[bool, float]: ...
def ColorEdit3(label: str, col: Tuple[float, float, float], flags: ImGuiColorEditFlags = 0) -> Tuple[bool, Tuple[float, float, float]]: ...
def ColorEdit4(label: str, col: Tuple[float, float, float, float], flags: ImGuiColorEditFlags = 0) -> Tuple[bool, Tuple[float, float, float, float]]: ...
def ColorPicker3(label: str, col: Tuple[float, float, float], flags: ImGuiColorEditFlags = 0) -> Tuple[bool, Tuple[float, float, float]]: ...
def ColorPicker4(label: str, col: Tuple[float, float, float, float], flags: ImGuiColorEditFlags = 0, ref_col: Optional[Tuple[float, float, float, float]] = None) -> Tuple[bool, Tuple[float, float, float, float]]: ...
def ColorButton(desc_id: str, col: Tuple[float, float, float, float], flags: ImGuiColorEditFlags = 0, size: Tuple[float, float] = (0, 0)) -> bool: ...
def SetColorEditOptions(flags: ImGuiColorEditFlags) -> None: ...
def TreeNode(label: str) -> bool: ...
def TreeNodeEx(label: str, flags: ImGuiTreeNodeFlags = 0) -> bool: ...
def TreePush(str_id: str) -> None: ...
def TreePop() -> None: ...
def GetTreeNodeToLabelSpacing() -> float: ...
def CollapsingHeader(label: str, flags: ImGuiTreeNodeFlags = 0) -> bool: ...
def CollapsingHeader(label: str, p_visible: bool, flags: ImGuiTreeNodeFlags = 0) -> Tuple[bool, bool]: ...
def SetNextItemOpen(is_open: bool, cond: ImGuiCond = 0) -> None: ...
def Selectable(label: str, selected: bool = False, flags: ImGuiSelectableFlags = 0, size: Tuple[float, float] = (0, 0)) -> bool: ...
def Selectable(label: str, p_selected: bool, flags: ImGuiSelectableFlags = 0, size: Tuple[float, float] = (0, 0)) -> Tuple[bool, bool]: ...
def IsItemToggledSelection() -> bool: ...
def BeginListBox(label: str, size: Tuple[float, float] = (0, 0)) -> bool: ...
def EndListBox() -> None: ...
def ListBox(label: str, current_item: int, items: List[str], items_count: int, height_in_items: int = -1) -> Tuple[bool, int]: ...
def Value(prefix: str, b: bool) -> None: ...
def Value(prefix: str, v: int) -> None: ...
def Value(prefix: str, v: float, float_format: Optional[str] = None) -> None: ...
def BeginMenuBar() -> bool: ...
def EndMenuBar() -> None: ...
def BeginMainMenuBar() -> bool: ...
def EndMainMenuBar() -> None: ...
def BeginMenu(label: str, enabled: bool = True) -> bool: ...
def EndMenu() -> None: ...
def MenuItem(label: str, shortcut: Optional[str] = None, selected: bool = False, enabled: bool = True) -> bool: ...
def MenuItem(label: str, shortcut: str, p_selected: bool, enabled: bool = True) -> Tuple[bool, bool]: ...
def BeginTooltip() -> bool: ...
def EndTooltip() -> None: ...
def SetTooltip(text: str) -> None: ...
def BeginItemTooltip() -> bool: ...
def SetItemTooltip(text: str) -> None: ...
def BeginPopup(str_id: str, flags: ImGuiWindowFlags = 0) -> bool: ...
def BeginPopupModal(name: str, open: Optional[bool] = None, flags: ImGuiWindowFlags = 0) -> Tuple[bool, Optional[bool]]: ...
def EndPopup() -> None: ...
def OpenPopup(str_id: str, popup_flags: ImGuiPopupFlags = 0) -> None: ...
def OpenPopup(id: ImGuiID, popup_flags: ImGuiPopupFlags = 0) -> None: ...
def OpenPopupOnItemClick(str_id: Optional[str] = None, popup_flags: ImGuiPopupFlags = 1) -> None: ...
def CloseCurrentPopup() -> None: ...
def BeginPopupContextItem(str_id: Optional[str] = None, popup_flags: ImGuiPopupFlags = 1) -> bool: ...
def BeginPopupContextWindow(str_id: Optional[str] = None, popup_flags: ImGuiPopupFlags = 1) -> bool: ...
def BeginPopupContextVoid(str_id: Optional[str] = None, popup_flags: ImGuiPopupFlags = 1) -> bool: ...
def IsPopupOpen(str_id: str, flags: ImGuiPopupFlags = 0) -> bool: ...
def BeginTable(str_id: str, columns: int, flags: ImGuiTableFlags = 0, outer_size: Tuple[float, float] = (0.0, 0.0), inner_width: float = 0.0) -> bool: ...
def EndTable() -> None: ...
def TableNextColumn() -> bool: ...
def TableSetColumnIndex(column_n: int) -> bool: ...
def TableSetupColumn(label: str, flags: ImGuiTableColumnFlags = 0, init_width_or_weight: float = 0.0, user_id: ImGuiID = 0) -> None: ...
def TableSetupScrollFreeze(cols: int, rows: int) -> None: ...
def TableHeader(label: str) -> None: ...
def TableHeadersRow() -> None: ...
def TableAngledHeadersRow() -> None: ...
def TableGetColumnCount() -> int: ...
def TableGetColumnIndex() -> int: ...
def TableGetRowIndex() -> int: ...
def TableGetColumnName(column_n: int = -1) -> str: ...
def TableGetColumnFlags(column_n: int = -1) -> ImGuiTableColumnFlags: ...
def TableSetColumnEnabled(column_n: int, v: bool) -> None: ...
def TableGetHoveredColumn() -> int: ...
def TableSetBgColor(target: ImGuiTableBgTarget, color: int, column_n: int = -1) -> None: ...
def Columns(count: int = 1, id: Optional[str] = None, border: bool = True) -> None: ...
def NextColumn() -> None: ...
def GetColumnIndex() -> int: ...
def GetColumnWidth(column_index: int = -1) -> float: ...
def SetColumnWidth(column_index: int, width: float) -> None: ...
def GetColumnOffset(column_index: int = -1) -> float: ...
def SetColumnOffset(column_index: int, offset_x: float) -> None: ...
def GetColumnsCount() -> int: ...
def BeginTabBar(str_id: str, flags: ImGuiTabBarFlags = 0) -> bool: ...
def EndTabBar() -> None: ...
def BeginTabItem(label: str, open: Optional[bool] = None, flags: ImGuiTabItemFlags = 0) -> Tuple[bool, Optional[bool]]: ...
def EndTabItem() -> None: ...
def TabItemButton(label: str, flags: ImGuiTabItemFlags = 0) -> bool: ...
def SetTabItemClosed(tab_or_docked_window_label: str) -> None: ...
def LogToTTY(auto_open_depth: int = -1) -> None: ...
def LogToFile(auto_open_depth: int = -1, filename: Optional[str] = None) -> None: ...
def LogToClipboard(auto_open_depth: int = -1) -> None: ...
def LogFinish() -> None: ...
def LogButtons() -> None: ...
def LogText(text: str) -> None: ...
def BeginDragDropSource(flags: ImGuiDragDropFlags = 0) -> bool: ...
def SetDragDropPayload(type: str, data: bytes, cond: ImGuiCond = 0) -> bool: ...
def EndDragDropSource() -> None: ...
def BeginDragDropTarget() -> bool: ...
def AcceptDragDropPayload(type: str, flags: ImGuiDragDropFlags = 0) -> bytes: ...
def EndDragDropTarget() -> None: ...
def GetDragDropPayload() -> bytes: ...
def BeginDisabled(disabled: bool = True) -> None: ...
def EndDisabled() -> None: ...
def PushClipRect(clip_rect_min: Tuple[float, float], clip_rect_max: Tuple[float, float], intersect_with_current_clip_rect: bool) -> None: ...
def PopClipRect() -> None: ...
def SetItemDefaultFocus() -> None: ...
def SetKeyboardFocusHere(offset: int = 0) -> None: ...
def SetNextItemAllowOverlap() -> None: ...
def IsItemHovered(flags: ImGuiHoveredFlags = 0) -> bool: ...
def IsItemActive() -> bool: ...
def IsItemFocused() -> bool: ...
def IsItemClicked(mouse_button: ImGuiMouseButton = 0) -> bool: ...
def IsItemVisible() -> bool: ...
def IsItemEdited() -> bool: ...
def IsItemActivated() -> bool: ...
def IsItemDeactivated() -> bool: ...
def IsItemDeactivatedAfterEdit() -> bool: ...
def IsItemToggledOpen() -> bool: ...
def IsAnyItemHovered() -> bool: ...
def IsAnyItemActive() -> bool: ...
def IsAnyItemFocused() -> bool: ...
def GetItemID() -> ImGuiID: ...
def GetItemRectMin() -> Tuple[float, float]: ...
def GetItemRectMax() -> Tuple[float, float]: ...
def GetItemRectSize() -> Tuple[float, float]: ...
def IsRectVisible(size: Tuple[float, float]) -> bool: ...
def IsRectVisible(rect_min: Tuple[float, float], rect_max: Tuple[float, float]) -> bool: ...
def GetTime() -> float: ...
def GetStyleColorName(idx: ImGuiCol) -> str: ...
def ColorConvertRGBtoHSV(rgb: Tuple[float, float, float]) -> Tuple[float, float, float]: ...
def ColorConvertHSVtoRGB(hsv: Tuple[float, float, float]) -> Tuple[float, float, float]: ...
def IsKeyDown(key: ImGuiKey) -> bool: ...
def IsKeyPressed(key: ImGuiKey, repeat: bool = True) -> bool: ...
def IsKeyReleased(key: ImGuiKey) -> bool: ...
def IsKeyChordPressed(key_chord: ImGuiKeyChord) -> bool: ...
def GetKeyPressedAmount(key: ImGuiKey, repeat_delay: float, rate: float) -> int: ...
def GetKeyName(key: ImGuiKey) -> str: ...
def SetNextFrameWantCaptureKeyboard(want_capture_keyboard: bool) -> None: ...
def Shortcut(key_chord: ImGuiKeyChord, flags: ImGuiInputFlags = 0) -> bool: ...
def SetNextItemShortcut(key_chord: ImGuiKeyChord, flags: ImGuiInputFlags = 0) -> None: ...
def SetItemKeyOwner(key: ImGuiKey) -> None: ...
def IsMouseDown(button: ImGuiMouseButton) -> bool: ...
def IsMouseClicked(button: ImGuiMouseButton, repeat: bool = False) -> bool: ...
def IsMouseReleased(button: ImGuiMouseButton) -> bool: ...
def IsMouseDoubleClicked(button: ImGuiMouseButton) -> bool: ...
def GetMouseClickedCount(button: ImGuiMouseButton) -> int: ...
def IsMouseHoveringRect(r_min: Tuple[float, float], r_max: Tuple[float, float], clip: bool = True) -> bool: ...
def IsMousePosValid(mouse_pos: Optional[Tuple[float, float]] = None) -> bool: ...
def IsAnyMouseDown() -> bool: ...
def IsMouseDragging(button: ImGuiMouseButton, lock_threshold: float = -1.0) -> bool: ...
def GetMouseDragDelta(button: ImGuiMouseButton = 0, lock_threshold: float = -1.0) -> Tuple[float, float]: ...
def ResetMouseDragDelta(button: ImGuiMouseButton = 0) -> None: ...
def GetMouseCursor() -> ImGuiMouseCursor: ...
def SetMouseCursor(cursor_type: ImGuiMouseCursor) -> None: ...
def SetNextFrameWantCaptureMouse(want_capture_mouse: bool) -> None: ...
def GetClipboardText() -> str: ...
def LoadIniSettingsFromDisk(ini_filename: str) -> None: ...
def SaveIniSettingsToDisk(ini_filename: str) -> None: ...
def DebugTextEncoding(text: str) -> None: ...
def DebugFlashStyleColor(idx: ImGuiCol) -> None: ...
def DebugStartItemPicker() -> None: ...
def DebugCheckVersionAndDataLayout(version_str: str, sz_io: int, sz_style: int, sz_vec2: int, sz_vec4: int, sz_drawvert: int, sz_drawidx: int) -> bool: ...
