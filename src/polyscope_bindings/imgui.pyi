from typing import List, NewType, Optional, Tuple, Union, overload
import numpy as np

# Basic Types
ImU32 = NewType("ImU32", int)
ImVec2 = Tuple[float, float]
ImVec4 = Tuple[float, float, float, float]

# Enum Types
ImGuiCol = NewType("ImGuiCol", int)
ImGuiColorEditFlags = NewType("ImGuiColorEditFlags", int)
ImGuiComboFlags = NewType("ImGuiComboFlags", int)
ImGuiCond = NewType("ImGuiCond", int)
ImGuiDataType = NewType("ImGuiDataType", int)
ImGuiDir = NewType("ImGuiDir", int)
ImGuiFocusedFlags = NewType("ImGuiFocusedFlags", int)
ImGuiHoveredFlags = NewType("ImGuiHoveredFlags", int)
ImGuiID = NewType("ImGuiID", int)
ImGuiInputTextFlags = NewType("ImGuiInputTextFlags", int)
ImGuiKey = NewType("ImGuiKey", int)
ImGuiMouseButton = NewType("ImGuiMouseButton", int)
ImGuiMouseCursor = NewType("ImGuiMouseCursor", int)
ImGuiSelectableFlags = NewType("ImGuiSelectableFlags", int)
ImGuiStyleVar = NewType("ImGuiStyleVar", int)
ImGuiTabBarFlags = NewType("ImGuiTabBarFlags", int)
ImGuiTabItemFlags = NewType("ImGuiTabItemFlags", int)
ImGuiTreeNodeFlags = NewType("ImGuiTreeNodeFlags", int)
ImGuiWindowFlags = NewType("ImGuiWindowFlags", int)

# Draw Types
ImDrawFlags = NewType("ImDrawFlags", int)
ImDrawListFlags = NewType("ImDrawListFlags", int)

# Windows


def Begin(
    name: str, open: Optional[bool] = None, flags: ImGuiWindowFlags = ImGuiWindowFlags(0)
) -> bool: ...
def End() -> None: ...

# Child Windows


def BeginChild(
    id: Union[str, ImGuiID],
    size: ImVec2 = (0, 0),
    border: bool = False,
    flags: ImGuiWindowFlags = ImGuiWindowFlags(0),
) -> bool: ...
def Endchild() -> None: ...

# Windows Utilities


def IsWindowAppearing() -> bool: ...
def IsWindowCollapsed() -> bool: ...


def IsWindowFocused(
    flags: ImGuiFocusedFlags = ImGuiFocusedFlags(0)) -> bool: ...


def IsWindowHovered(
    flags: ImGuiFocusedFlags = ImGuiFocusedFlags(0)) -> bool: ...


def GetWindowPos() -> ImVec2: ...
def GetWindowSize() -> ImVec2: ...
def GetWindowWidth() -> float: ...
def GetWindowHeight() -> float: ...


def SetNextWindowPos(
    pos: ImVec2, cone: ImGuiCond = ImGuiCond(0), pivot: ImVec2 = (0, 0)
) -> None: ...


def SetNextWindowSize(
    size: ImVec2, cond: ImGuiCond = ImGuiCond(0)) -> None: ...
def SetNextWindowSizeConstraints(
    size_min: ImVec2, size_max: ImVec2) -> None: ...


def SetNextWindowContentSize(size: ImVec2) -> None: ...
def SetNextWindowCollapsed(
    collapsed: bool, cond: ImGuiCond = ImGuiCond(0)) -> None: ...


def SetNextWindowFocus() -> None: ...
def SetNextWindowBgAlpha(alpha: float) -> None: ...
@overload
def SetWindowPos(pos: ImVec2, cond: ImGuiCond = ImGuiCond(0)) -> None: ...


@overload
def SetWindowPos(name: str, pos: ImVec2,
                 cond: ImGuiCond = ImGuiCond(0)) -> None: ...


@overload
def SetWindowSize(size: ImVec2, cond: ImGuiCond = ImGuiCond(0)) -> None: ...


@overload
def SetWindowSize(name: str, size: ImVec2,
                  cond: ImGuiCond = ImGuiCond(0)) -> None: ...


@overload
def SetWindowCollapsed(
    collapsed: bool, cond: ImGuiCond = ImGuiCond(0)) -> None: ...


@overload
def SetWindowCollapsed(name: str, collapsed: bool,
                       cond: ImGuiCond = ImGuiCond(0)) -> None: ...


def SetWindowFontScale(scale: float) -> None: ...


def SetWindowFocus(
    name: Optional[str] = None,
) -> None: ...

# Content region


def GetContentRegionMax() -> ImVec2: ...
def GetContentRegionAvail() -> ImVec2: ...
def GetWindowContentRegionMin() -> ImVec2: ...
def GetWindowContentRegionMax() -> ImVec2: ...
def GetWindowContentRegionWidth() -> float: ...

# Windows Scrolling


def GetScrollX() -> float: ...
def GetScrollY() -> float: ...
def GetScrollMaxX() -> float: ...
def GetScrollMaxY() -> float: ...
def SetScrollX(scroll_x: float) -> None: ...
def SetScrollY(scroll_y: float) -> None: ...
def SetScrollHereX(center_x_ratio: float = 0.5) -> None: ...
def SetScrollHereY(center_y_ratio: float = 0.5) -> None: ...
def SetScrollFromPosX(local_x: float, center_x_ratio: float = 0.5) -> None: ...
def SetScrollFromPosY(local_y: float, center_y_ratio: float = 0.5) -> None: ...

# Parameters stacks (shared)


def PushStyleColor(idx: ImGuiCol, col: Union[ImU32, ImVec4]) -> None: ...
def PopStyleColor(count: int = 1) -> None: ...
def PushStyleVar(idx: ImGuiStyleVar, val: Union[float, ImVec2]) -> None: ...
def PopStyleVar(count: int = 1) -> None: ...
def GetStyleColorVec4(idx: ImGuiCol) -> ImVec4: ...
def GetFontSize() -> float: ...
def GetFontTexUvWhitePixel() -> ImVec2: ...
@overload
def GetColorU32(idx: ImGuiCol, alpha_mul: float = 1.0) -> ImU32: ...
@overload
def GetColorU32(col: ImVec4) -> ImU32: ...
@overload
def GetColorU32(col: ImU32) -> ImU32: ...

# Parameters stacks (current window)


def PushItemWidth(item_width) -> float: ...
def PopItemWidth() -> None: ...
def SetNextItemWidth(item_width) -> float: ...
def CalcItemWidth() -> float: ...
def PushTextWrapPos(wrap_local_pos_x: float = 0.0) -> None: ...
def PopTextWrapPos() -> None: ...
def PushAllowKeyboardFocus(allow_keyboard_focus: bool) -> None: ...
def PopAllowKeyboardFocus() -> None: ...
def PushButtonRepeat(repeat: bool) -> None: ...
def PopButtonRepeat() -> None: ...

# Cursor / Layout


def Separator() -> None: ...
def SameLine(offset_from_start_x: float = 0.0,
             spacing: float = -1.0) -> None: ...


def NewLine() -> None: ...
def Spacing() -> None: ...
def Dummy(size: ImVec2) -> None: ...
def Indent(intent_w: float = 0.0) -> None: ...
def Unindent(intent_w: float = 0.0) -> None: ...
def BeginGroup() -> None: ...
def EndGroup() -> None: ...
def GetCursorPos() -> ImVec2: ...
def GetCursorPosX() -> float: ...
def SetCursorPos(local_pos: ImVec2) -> None: ...
def SetCursorPosX(locol_x: float) -> None: ...
def SetCursorPosY(locol_y: float) -> None: ...
def GetCursorStartPos() -> ImVec2: ...
def GetCursorScreenPos() -> ImVec2: ...
def SetCursorScreenPos(pos: ImVec2) -> None: ...
def AlignTextToFramePadding() -> None: ...
def GetTextLineHeight() -> float: ...
def GetTextLineHeightWithSpacing() -> float: ...
def GetFrameHeight() -> float: ...
def GetFrameHeightWithSpacing() -> float: ...

# ID stack/scopes


def PushID(str_id: Union[str, int]) -> None: ...
def PopID() -> None: ...
def GetID(str_id: str) -> ImGuiID: ...

# Widgets: Text


def TextUnformatted(text: str) -> None: ...
def Text(text: str) -> None: ...
def TextColored(col: ImVec4, text: str) -> None: ...
def TextDisabled(text: str) -> None: ...
def TextWrapped(text: str) -> None: ...
def LabelText(label: str, text: str) -> None: ...
def BulletText(text: str) -> None: ...

# Widgets: Main


def Button(label: str, size: ImVec2 = (0, 0)) -> bool: ...
def SmallButton(label: str) -> bool: ...
def InvisibleButton(str_id: str, size: ImVec2) -> bool: ...
def ArrowButton(str_id: str, dir: ImGuiDir) -> bool: ...
def Checkbox(label: str, v: bool) -> Tuple[bool, bool]: ...
def CheckboxFlags(label: str, flags: int,
                  flags_value: int) -> Tuple[bool, int]: ...


@overload
def RadioButton(label: str, active: bool) -> bool: ...
@overload
def RadioButton(label: str, v: int, v_button: int) -> Tuple[bool, int]: ...


def ProgressBar(fraction: float, size_arg: ImVec2 = (-1, 0)) -> None: ...
def Bullet() -> None: ...

# Widgets: Combo Box


def BeginCombo(label: str, preview_value: str,
               flags: ImGuiComboFlags = ImGuiComboFlags(0)) -> bool: ...


def EndCombo() -> None: ...


def Combo(
    label: str,
    current_item: int,
    items: Union[str, List[str]],
    popup_max_height_in_items: int = -1,
) -> Tuple[bool, int]: ...

# Widgets: Drags


def DragFloat(
    label: str,
    v: float,
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, float]: ...


def DragFloat2(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def DragFloat3(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def DragFloat4(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def DragFloatRange2(
    label: str,
    v_current_min: List[float],
    v_current_max: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    format_max: Optional[str] = None,
    power: float = 1.0,
) -> Tuple[bool, List[float], List[float]]: ...


def DragInt(
    label: str,
    v: int,
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, float]: ...


def DragInt2(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...


def DragInt3(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...


def DragInt4(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...


def DragIntRange2(
    label: str,
    v_current_min: List[int],
    v_current_max: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
    format_max: Optional[str] = None,
) -> Tuple[bool, List[int], List[int]]: ...

# Widgets: Sliders


def SliderFloat(
    label: str,
    v: float,
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, float]: ...


def SliderFloat2(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def SliderFloat3(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def SliderFloat4(
    label: str,
    v: List[float],
    v_speed: float = 1.0,
    v_min: float = 0.0,
    v_max: float = 0.0,
    format: str = "%.3f",
    power: float = 1.0,
) -> Tuple[bool, List[float]]: ...


def SliderAngle(
    label: str, v_rad: int, v_degrees_min: float, v_degrees_max: float, format: str
) -> Tuple[bool, float]: ...


def SliderInt(
    label: str,
    v: int,
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, float]: ...


def SliderInt2(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...


def SliderInt3(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...


def SliderInt4(
    label: str,
    v: List[int],
    v_speed: float = 1.0,
    v_min: int = 0,
    v_max: int = 0,
    format: str = "%d",
) -> Tuple[bool, List[float]]: ...

# Widgets: Input with Keyboard


def InputText(
    label: str, buf: str, flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0)
) -> Tuple[bool, str]: ...


def InputTextMultiline(
    label: str, buf: str, size: ImVec2 = (0.0, 0.0), flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0)
) -> Tuple[bool, ImVec2]: ...


def InputTextWithHint(
    label: str, hint: str, buf: str, flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0)
) -> Tuple[bool, ImVec2]: ...


def InputFloat(
    label: str,
    v: float,
    step: float = 0.0,
    step_fast: float = 0.0,
    format: str = "%.3f",
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, float]: ...


def InputFloat2(
    label: str,
    v: List[float],
    format: str = "%.3f",
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[float]]: ...


def InputFloat3(
    label: str,
    v: List[float],
    format: str = "%.3f",
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[float]]: ...


def InputFloat4(
    label: str,
    v: List[float],
    format: str = "%.3f",
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[float]]: ...


def InputInt(
    label: str,
    v: int,
    step: int = 1,
    step_fast: int = 100,
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, float]: ...


def InputInt2(
    label: str,
    v: List[int],
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[int]]: ...


def InputInt3(
    label: str,
    v: List[int],
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[int]]: ...


def InputInt4(
    label: str,
    v: List[int],
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, List[int]]: ...


def InputDouble(
    label: str,
    v: float,
    step: float = 0.0,
    step_fast: float = 0.0,
    format: str = "%.6f",
    flags: ImGuiInputTextFlags = ImGuiInputTextFlags(0),
) -> Tuple[bool, float]: ...

# Widgets: Color Editor/Picker


def ColorEdit3(
    label: str, col: List[float], flags: ImGuiColorEditFlags = ImGuiColorEditFlags(0)
) -> Tuple[bool, List[float]]: ...


def ColorEdit4(
    label: str, col: List[float], flags: ImGuiColorEditFlags = ImGuiColorEditFlags(0)
) -> Tuple[bool, List[float]]: ...


def ColorPicker3(
    label: str, col: List[float], flags: ImGuiColorEditFlags = ImGuiColorEditFlags(0)
) -> Tuple[bool, List[float]]: ...


def ColorPicker4(
    label: str,
    col: List[float],
    flags: ImGuiColorEditFlags = ImGuiColorEditFlags(0),
    ref_col: Optional[List[float]] = None,
) -> Tuple[bool, List[float]]: ...


def ColorButton(
    desc_id: str, col: ImVec4, flags: ImGuiColorEditFlags = ImGuiColorEditFlags(0), size: ImVec2 = (0, 0)
) -> bool: ...
def SetColorEditOptions(flags: ImGuiColorEditFlags) -> None: ...

# Widgets: Trees


def TreeNode(label: str) -> bool: ...
def TreeNodeEx(
    label: str, flags: ImGuiTreeNodeFlags = ImGuiTreeNodeFlags(0)) -> bool: ...


def TreePush(str_id: str) -> None: ...
def TreePop() -> None: ...
def GetTreeNodeToLabelSpacing() -> float: ...


@overload
def CollapsingHeader(
    label: str, flags: ImGuiTreeNodeFlags = ImGuiTreeNodeFlags(0)) -> bool: ...


@overload
def CollapsingHeader(
    label: str, open: bool, flags: ImGuiTreeNodeFlags = ImGuiTreeNodeFlags(0)
) -> Tuple[bool, bool]: ...

# Widgets: Selectables


def Selectable(
    label: str,
    selected: bool = False,
    flags: ImGuiSelectableFlags = ImGuiSelectableFlags(0),
    size: ImVec2 = (0, 0),
) -> Tuple[bool, bool]: ...

# Widgets: List Boxes


def ListBox(
    label: str, current_item: int, items: List[str], height_in_items: int = -1
) -> Tuple[bool, int]: ...
def ListBoxHeader(label: str, size: ImVec2 = (0, 0)) -> bool: ...
def ListBoxFooter() -> None: ...

# Widgets: Data Plotting


def PlotLines(
    label: str,
    values: List[float],
    values_offset: int = 0,
    overlay_text: Optional[str] = None,
    scale_min: float = np.finfo(np.float32).max,
    scale_max: float = np.finfo(np.float32).max,
    graph_size: ImVec2 = (0, 0),
) -> None: ...


def PlotHistogram(
    label: str,
    values: List[float],
    values_offset: int = 0,
    overlay_text: Optional[str] = None,
    scale_min: float = np.finfo(np.float32).max,
    scale_max: float = np.finfo(np.float32).max,
    graph_size: ImVec2 = (0, 0),
) -> None: ...

# Widgets: Value() Helpers.


def Value(
    prefix: str, v: Union[bool, int, float], float_format: Optional[str] = None
) -> None: ...

# Widgets: Menus


def BeginMenuBar() -> bool: ...
def EndMenuBar() -> None: ...
def BeginMainMenuBar() -> bool: ...
def EndMainMenuBar() -> None: ...
def BeginMenu(label: str, enabled: bool = True) -> bool: ...
def EndMenu() -> None: ...


def MenuItem(
    label: str, shortcut: Optional[str], selected: bool = False, enabled: bool = False
) -> Tuple[bool, bool]: ...

# Tooltips


def BeginTooltip() -> None: ...
def EndTooltip() -> None: ...
def SetTooltip(value: str) -> None: ...

# Popups, Modals


def OpenPopup(str_id: str) -> None: ...


def BeginPopUp(
    str_id: str, flags: ImGuiWindowFlags = ImGuiWindowFlags(0)) -> bool: ...


def BeginPopupContextItem(
    str_id: Optional[str], mouse_button: ImGuiMouseButton = ImGuiMouseButton(1)
) -> bool: ...


def BeginPopupContextWindow(
    str_id: Optional[str],
    mouse_button: ImGuiMouseButton = ImGuiMouseButton(1),
    also_over_items: bool = True,
) -> bool: ...


def BeginPopupContextVoid(
    str_id: Optional[str], mouse_button: ImGuiMouseButton = ImGuiMouseButton(1)
) -> bool: ...


def BeginPopupModal(
    name: str, open: bool, flags: ImGuiWindowFlags = ImGuiWindowFlags(0)
) -> Tuple[bool, bool]: ...
def EndPopup() -> None: ...


def OpenPopupOnItemClick(
    str_id: Optional[str], mouse_button: ImGuiMouseButton = ImGuiMouseButton(1)
) -> bool: ...
def IsPopupOpen(str_id: str) -> bool: ...
def CloseCurrentPopup() -> None: ...

# Columns


def Columns(count: int = 1, id: Optional[str]
            = None, border: bool = True) -> None: ...


def NextColumn() -> None: ...
def GetColumnIndex() -> int: ...
def GetColumnWidth(column_index: int = -1) -> float: ...
def SetColumnWidth(column_index: int, width: float) -> None: ...
def GetColumnOffset(column_index: int = -1) -> float: ...
def SetColumnOffset(column_index: int, offset_x: float) -> None: ...
def GetColumnsCount() -> int: ...

# Tab Bars, Tabs


def BeginTabBar(
    str_id: str, flags: ImGuiTabBarFlags = ImGuiTabBarFlags(0)) -> bool: ...


def EndTabBar() -> None: ...


def BeginTabItem(
    label: str, open: bool, flags: ImGuiTabItemFlags = ImGuiTabItemFlags(0)
) -> Tuple[bool, bool]: ...
def EndTabItem() -> None: ...
def SetTabItemClosed(tab_or_docked_window_label: str) -> None: ...

# Logging/Capture


def LogToTTY(auto_open_depth: int = -1) -> None: ...
def LogToFile(auto_open_depth: int = -1,
              filename: Optional[str] = None) -> None: ...


def LogToClipboard(auto_open_depth: int = -1) -> None: ...
def LogFinish() -> None: ...
def LogButtons() -> None: ...

# Clipping


def PushClipRect(
    clip_rect_min: ImVec2, clip_rect_max: ImVec2, intersect_with_current_clip_rect: bool
) -> None: ...
def PopClipRect() -> None: ...

# Focus, Activation


def SetItemDefaultFocus() -> None: ...
def SetKeyboardFocusHere(offset: int = 0) -> None: ...

# Item/Widgets Utilities


def IsItemHovered(flags: ImGuiHoveredFlags = ImGuiHoveredFlags(0)) -> bool: ...
def IsItemActive() -> bool: ...
def IsItemFocused() -> bool: ...
def IsItemClicked(
    mouse_button: ImGuiMouseButton = ImGuiMouseButton(0)) -> bool: ...


def IsItemVisible() -> bool: ...
def IsItemEdited() -> bool: ...
def IsItemActivated() -> bool: ...
def IsItemDeactivated() -> bool: ...
def IsItemDeactivatedAfterEdit() -> bool: ...
def IsItemToggledOpen() -> bool: ...
def IsAnyItemHovered() -> bool: ...
def IsAnyItemActive() -> bool: ...
def IsAnyItemFocused() -> bool: ...
def GetItemRectMin() -> ImVec2: ...
def GetItemRectMax() -> ImVec2: ...
def GetItemRectSize() -> ImVec2: ...
def SetItemAllowOverlap() -> None: ...

# Miscellaneous Utilities


@overload
def IsRectVisible(size: ImVec2) -> bool: ...
@overload
def IsRectVisible(rect_min: ImVec2, rect_max: ImVec2) -> bool: ...

def GetTime() -> float: ...
def GetFrameCount() -> int: ...
def GetStyleColorName(idx: ImGuiCol) -> str: ...


def CalcListClipping(
    items_count: int, items_height: float) -> Tuple[int, int]: ...
def BeginChildFrame(id: ImGuiID, size: ImVec2,
                    flags: ImGuiWindowFlags = ImGuiWindowFlags(0)) -> bool: ...


def EndChildFrame() -> None: ...

# Text Utilities


def CalcTextSize(
    text: str,
    text_end: Optional[str] = None,
    hide_text_after_double_hash: bool = False,
    wrap_width: float = -1.0,
) -> ImVec2: ...

# Inputs Utilities: Keyboard


def GetKeyIndex(imgui_key: ImGuiKey) -> int: ...
def IsKeyDown(user_key_index: int) -> bool: ...
def IsKeyPressed(user_key_index: int, repeat: bool = True) -> bool: ...
def IsKeyReleased(user_key_index: int) -> bool: ...


def GetKeyPressedAmount(
    key_index: int, repeat_delay: float, rate: float) -> int: ...
def CaptureKeyboardFromApp(
    want_capture_keyboard_value: bool = True) -> None: ...

# Inputs Utilities: Mouse


def IsMouseDown(button: ImGuiMouseButton) -> bool: ...
def IsMouseClicked(button: ImGuiMouseButton, repeat: bool = False) -> bool: ...
def IsMouseReleased(button: ImGuiMouseButton) -> bool: ...
def IsMouseDoubleClicked(button: ImGuiMouseButton) -> bool: ...
def IsMouseHoveringRect(r_min: ImVec2, r_max: ImVec2,
                        clip: bool = True) -> bool: ...


def IsMousePosValid(mouse_pos: Optional[ImVec2]) -> bool: ...
def IsAnyMouseDown() -> bool: ...
def GetMousePos() -> ImVec2: ...
def GetMousePosOnOpeningCurrentPopup() -> ImVec2: ...


def IsMouseDragging(button: ImGuiMouseButton,
                    lock_threshold: float = -1.0) -> bool: ...


def GetMouseDragDelta(
    button: ImGuiMouseButton, lock_threshold: float = -1.0
) -> bool: ...
def ResetMouseDragDelta(button: ImGuiMouseButton) -> None: ...
def GetMouseCursor() -> ImGuiMouseCursor: ...
def SetMouseCursor(cursor_type: ImGuiMouseCursor) -> None: ...
def CaptureMouseFromApp(want_capture_mouse_value: bool = True) -> None: ...

# Clipboard Utilities


def GetClipboardText() -> str: ...
def SetClipboardText(text: str) -> None: ...

# Settings/.Ini Utilities


def LoadIniSettingsFromDisk(ini_filename: str) -> None: ...
def LoadIniSettingsFromMemory(ini_data: str) -> None: ...
def SaveIniSettingsToDisk(ini_filename: str) -> None: ...
def SaveIniSettingsToMemory() -> str: ...


# Draw Commands

def AddLine(p1: ImVec2, p2: ImVec2, col: ImU32, thickness: float = 1.) -> None: ...
def AddRect(p_min: ImVec2, p_max: ImVec2, col: ImU32, rounding: float = 0., flags: ImDrawFlags = 0, thickness: float = 1.) -> None: ...
def AddRectFilled(p_min: ImVec2, p_max: ImVec2, col: ImU32, rounding: float = 0., flags: ImDrawFlags = 0) -> None: ...
def AddAddRectFilledMultiColor(p_min: ImVec2, p_max: ImVec2, col_upr_left: ImU32, col_upr_right: ImU32, col_bot_right: ImU32, col_bot_left: ImU32) -> None: ...
def AddQuad(p1: ImVec2, p2: ImVec2, p3: ImVec2, p4: ImVec2, col: ImU32, thickness: float = 1.) -> None: ...
def AddQuadFilled(p1: ImVec2, p2: ImVec2, p3: ImVec2, p4: ImVec2, col: ImU32) -> None: ...
def AddTriangle(p1: ImVec2, p2: ImVec2, p3: ImVec2, col: ImU32, thickness: float = 1.) -> None: ...
def AddTriangleFilled(p1: ImVec2, p2: ImVec2, p3: ImVec2, col: ImU32) -> None: ...
def AddCircle(center: ImVec2, radius: float, col: ImU32, num_segments: int = 0, thickness: float = 1.) -> None: ...
def AddCircleFilled(center: ImVec2, radius: float, col: ImU32, num_segments: int = 0) -> None: ...
def AddNgon(center: ImVec2, radius: float, col: ImU32, num_segments: int, thickness: float = 1.) -> None: ...
def AddNgonFilled(center: ImVec2, radius: float, col: ImU32, num_segments: int) -> None: ...
def AddText(pos: ImVec2, col: ImU32, text: str, text_end: Optional[str] = None) -> None: ...
def AddPolyline(points: List[ImVec2], num_points: int, col: ImU32, flags: ImDrawFlags, thickness) -> None: ...
def AddConvexPolyFilled(points: List[ImVec2], num_points: int, col: ImU32) -> None: ...
def AddBezierCubic(p1: ImVec2, p2: ImVec2, p3: ImVec2, p4: ImVec2, col: ImU32, thickness: float, num_segments: int = 0) -> None: ...
def AddBezierQuadratic(p1: ImVec2, p2: ImVec2, p3: ImVec2, col: ImU32, thickness: float, num_segments: int = 0) -> None: ...


ImGuiWindowFlags_None: int
ImGuiWindowFlags_NoTitleBar: int
ImGuiWindowFlags_NoResize: int
ImGuiWindowFlags_NoMove: int
ImGuiWindowFlags_NoScrollbar: int
ImGuiWindowFlags_NoScrollWithMouse: int
ImGuiWindowFlags_NoCollapse: int
ImGuiWindowFlags_AlwaysAutoResize: int
ImGuiWindowFlags_NoBackground: int
ImGuiWindowFlags_NoSavedSettings: int
ImGuiWindowFlags_NoMouseInputs: int
ImGuiWindowFlags_MenuBar: int
ImGuiWindowFlags_HorizontalScrollbar: int
ImGuiWindowFlags_NoFocusOnAppearing: int
ImGuiWindowFlags_NoBringToFrontOnFocus: int
ImGuiWindowFlags_AlwaysVerticalScrollbar: int
ImGuiWindowFlags_AlwaysHorizontalScrollbar: int
ImGuiWindowFlags_AlwaysUseWindowPadding: int
ImGuiWindowFlags_NoNavInputs: int
ImGuiWindowFlags_NoNavFocus: int
ImGuiWindowFlags_UnsavedDocument: int
ImGuiWindowFlags_NoNav: int
ImGuiWindowFlags_NoDecoration: int
ImGuiWindowFlags_NoInputs: int
ImGuiWindowFlags_NavFlattened: int
ImGuiWindowFlags_ChildWindow: int
ImGuiWindowFlags_Tooltip: int
ImGuiWindowFlags_Popup: int
ImGuiWindowFlags_Modal: int
ImGuiWindowFlags_ChildMenu: int
ImGuiInputTextFlags_None: int
ImGuiInputTextFlags_CharsDecimal: int
ImGuiInputTextFlags_CharsHexadecimal: int
ImGuiInputTextFlags_CharsUppercase: int
ImGuiInputTextFlags_CharsNoBlank: int
ImGuiInputTextFlags_AutoSelectAll: int
ImGuiInputTextFlags_EnterReturnsTrue: int
ImGuiInputTextFlags_CallbackCompletion: int
ImGuiInputTextFlags_CallbackHistory: int
ImGuiInputTextFlags_CallbackAlways: int
ImGuiInputTextFlags_CallbackCharFilter: int
ImGuiInputTextFlags_AllowTabInput: int
ImGuiInputTextFlags_CtrlEnterForNewLine: int
ImGuiInputTextFlags_NoHorizontalScroll: int
ImGuiInputTextFlags_AlwaysInsertMode: int
ImGuiInputTextFlags_ReadOnly: int
ImGuiInputTextFlags_Password: int
ImGuiInputTextFlags_NoUndoRedo: int
ImGuiInputTextFlags_CharsScientific: int
ImGuiInputTextFlags_CallbackResize: int
ImGuiInputTextFlags_Multiline: int
ImGuiInputTextFlags_NoMarkEdited: int
ImGuiTreeNodeFlags_None: int
ImGuiTreeNodeFlags_Selected: int
ImGuiTreeNodeFlags_Framed: int
ImGuiTreeNodeFlags_AllowItemOverlap: int
ImGuiTreeNodeFlags_NoTreePushOnOpen: int
ImGuiTreeNodeFlags_NoAutoOpenOnLog: int
ImGuiTreeNodeFlags_DefaultOpen: int
ImGuiTreeNodeFlags_OpenOnDoubleClick: int
ImGuiTreeNodeFlags_OpenOnArrow: int
ImGuiTreeNodeFlags_Leaf: int
ImGuiTreeNodeFlags_Bullet: int
ImGuiTreeNodeFlags_FramePadding: int
ImGuiTreeNodeFlags_SpanAvailWidth: int
ImGuiTreeNodeFlags_SpanFullWidth: int
ImGuiTreeNodeFlags_NavLeftJumpsBackHere: int
ImGuiTreeNodeFlags_CollapsingHeader: int
ImGuiSelectableFlags_None: int
ImGuiSelectableFlags_DontClosePopups: int
ImGuiSelectableFlags_SpanAllColumns: int
ImGuiSelectableFlags_AllowDoubleClick: int
ImGuiSelectableFlags_Disabled: int
ImGuiSelectableFlags_AllowItemOverlap: int
ImGuiComboFlags_None: int
ImGuiComboFlags_PopupAlignLeft: int
ImGuiComboFlags_HeightSmall: int
ImGuiComboFlags_HeightRegular: int
ImGuiComboFlags_HeightLarge: int
ImGuiComboFlags_HeightLargest: int
ImGuiComboFlags_NoArrowButton: int
ImGuiComboFlags_NoPreview: int
ImGuiComboFlags_HeightMask_: int
ImGuiTabBarFlags_None: int
ImGuiTabBarFlags_Reorderable: int
ImGuiTabBarFlags_AutoSelectNewTabs: int
ImGuiTabBarFlags_TabListPopupButton: int
ImGuiTabBarFlags_NoCloseWithMiddleMouseButton: int
ImGuiTabBarFlags_NoTabListScrollingButtons: int
ImGuiTabBarFlags_NoTooltip: int
ImGuiTabBarFlags_FittingPolicyResizeDown: int
ImGuiTabBarFlags_FittingPolicyScroll: int
ImGuiTabBarFlags_FittingPolicyMask_: int
ImGuiTabBarFlags_FittingPolicyDefault_: int
ImGuiTabItemFlags_None: int
ImGuiTabItemFlags_UnsavedDocument: int
ImGuiTabItemFlags_SetSelected: int
ImGuiTabItemFlags_NoCloseWithMiddleMouseButton: int
ImGuiTabItemFlags_NoPushId: int
ImGuiFocusedFlags_None: int
ImGuiFocusedFlags_ChildWindows: int
ImGuiFocusedFlags_RootWindow: int
ImGuiFocusedFlags_AnyWindow: int
ImGuiFocusedFlags_RootAndChildWindows: int
ImGuiHoveredFlags_None: int
ImGuiHoveredFlags_ChildWindows: int
ImGuiHoveredFlags_RootWindow: int
ImGuiHoveredFlags_AnyWindow: int
ImGuiHoveredFlags_AllowWhenBlockedByPopup: int
ImGuiHoveredFlags_AllowWhenBlockedByActiveItem: int
ImGuiHoveredFlags_AllowWhenOverlapped: int
ImGuiHoveredFlags_AllowWhenDisabled: int
ImGuiHoveredFlags_RectOnly: int
ImGuiHoveredFlags_RootAndChildWindows: int
ImGuiDragDropFlags_None: int
ImGuiDragDropFlags_SourceNoPreviewTooltip: int
ImGuiDragDropFlags_SourceNoDisableHover: int
ImGuiDragDropFlags_SourceNoHoldToOpenOthers: int
ImGuiDragDropFlags_SourceAllowNullID: int
ImGuiDragDropFlags_SourceExtern: int
ImGuiDragDropFlags_SourceAutoExpirePayload: int
ImGuiDragDropFlags_AcceptBeforeDelivery: int
ImGuiDragDropFlags_AcceptNoDrawDefaultRect: int
ImGuiDragDropFlags_AcceptNoPreviewTooltip: int
ImGuiDragDropFlags_AcceptPeekOnly: int
ImGuiDataType_S8: int
ImGuiDataType_U8: int
ImGuiDataType_S16: int
ImGuiDataType_U16: int
ImGuiDataType_S32: int
ImGuiDataType_U32: int
ImGuiDataType_S64: int
ImGuiDataType_U64: int
ImGuiDataType_Float: int
ImGuiDataType_Double: int
ImGuiDataType_COUN: int
ImGuiDir_None: int
ImGuiDir_Left: int
ImGuiDir_Right: int
ImGuiDir_Up: int
ImGuiDir_Down: int
ImGuiDir_COUNT: int
ImGuiKey_Tab: int
ImGuiKey_LeftArrow: int
ImGuiKey_RightArrow: int
ImGuiKey_UpArrow: int
ImGuiKey_DownArrow: int
ImGuiKey_PageUp: int
ImGuiKey_PageDown: int
ImGuiKey_Home: int
ImGuiKey_End: int
ImGuiKey_Insert: int
ImGuiKey_Delete: int
ImGuiKey_Backspace: int
ImGuiKey_Space: int
ImGuiKey_Enter: int
ImGuiKey_Escape: int
ImGuiKey_KeyPadEnter: int
ImGuiKey_A: int
ImGuiKey_C: int
ImGuiKey_V: int
ImGuiKey_X: int
ImGuiKey_Y: int
ImGuiKey_Z: int
ImGuiKey_COUNT: int
ImGuiKeyModFlags_None: int
ImGuiKeyModFlags_Ctrl: int
ImGuiKeyModFlags_Shift: int
ImGuiKeyModFlags_Alt: int
ImGuiKeyModFlags_Super: int
ImGuiNavInput_Activate: int
ImGuiNavInput_Cancel: int
ImGuiNavInput_Input: int
ImGuiNavInput_Menu: int
ImGuiNavInput_DpadLeft: int
ImGuiNavInput_DpadRight: int
ImGuiNavInput_DpadUp: int
ImGuiNavInput_DpadDown: int
ImGuiNavInput_LStickLeft: int
ImGuiNavInput_LStickRight: int
ImGuiNavInput_LStickUp: int
ImGuiNavInput_LStickDown: int
ImGuiNavInput_FocusPrev: int
ImGuiNavInput_FocusNext: int
ImGuiNavInput_TweakSlow: int
ImGuiNavInput_TweakFast: int
ImGuiNavInput_KeyMenu_: int
ImGuiNavInput_KeyLeft_: int
ImGuiNavInput_KeyRight_: int
ImGuiNavInput_KeyUp_: int
ImGuiNavInput_KeyDown_: int
ImGuiNavInput_COUNT: int
ImGuiNavInput_InternalStart_: int
ImGuiConfigFlags_None: int
ImGuiConfigFlags_NavEnableKeyboard: int
ImGuiConfigFlags_NavEnableGamepad: int
ImGuiConfigFlags_NavEnableSetMousePos: int
ImGuiConfigFlags_NavNoCaptureKeyboard: int
ImGuiConfigFlags_NoMouse: int
ImGuiConfigFlags_NoMouseCursorChange: int
ImGuiConfigFlags_IsSRGB: int
ImGuiConfigFlags_IsTouchScreen: int
ImGuiBackendFlags_None: int
ImGuiBackendFlags_HasGamepad: int
ImGuiBackendFlags_HasMouseCursors: int
ImGuiBackendFlags_HasSetMousePos: int
ImGuiBackendFlags_RendererHasVtxOffset: int
ImGuiCol_Text: int
ImGuiCol_TextDisabled: int
ImGuiCol_WindowBg: int
ImGuiCol_ChildBg: int
ImGuiCol_PopupBg: int
ImGuiCol_Border: int
ImGuiCol_BorderShadow: int
ImGuiCol_FrameBg: int
ImGuiCol_FrameBgHovered: int
ImGuiCol_FrameBgActive: int
ImGuiCol_TitleBg: int
ImGuiCol_TitleBgActive: int
ImGuiCol_TitleBgCollapsed: int
ImGuiCol_MenuBarBg: int
ImGuiCol_ScrollbarBg: int
ImGuiCol_ScrollbarGrab: int
ImGuiCol_ScrollbarGrabHovered: int
ImGuiCol_ScrollbarGrabActive: int
ImGuiCol_CheckMark: int
ImGuiCol_SliderGrab: int
ImGuiCol_SliderGrabActive: int
ImGuiCol_Button: int
ImGuiCol_ButtonHovered: int
ImGuiCol_ButtonActive: int
ImGuiCol_Header: int
ImGuiCol_HeaderHovered: int
ImGuiCol_HeaderActive: int
ImGuiCol_Separator: int
ImGuiCol_SeparatorHovered: int
ImGuiCol_SeparatorActive: int
ImGuiCol_ResizeGrip: int
ImGuiCol_ResizeGripHovered: int
ImGuiCol_ResizeGripActive: int
ImGuiCol_Tab: int
ImGuiCol_TabHovered: int
ImGuiCol_TabActive: int
ImGuiCol_TabUnfocused: int
ImGuiCol_TabUnfocusedActive: int
ImGuiCol_PlotLines: int
ImGuiCol_PlotLinesHovered: int
ImGuiCol_PlotHistogram: int
ImGuiCol_PlotHistogramHovered: int
ImGuiCol_TextSelectedBg: int
ImGuiCol_DragDropTarget: int
ImGuiCol_NavHighlight: int
ImGuiCol_NavWindowingHighlight: int
ImGuiCol_NavWindowingDimBg: int
ImGuiCol_ModalWindowDimBg: int
ImGuiCol_COUNT: int
ImGuiStyleVar_Alpha: int
ImGuiStyleVar_WindowPadding: int
ImGuiStyleVar_WindowRounding: int
ImGuiStyleVar_WindowBorderSize: int
ImGuiStyleVar_WindowMinSize: int
ImGuiStyleVar_WindowTitleAlign: int
ImGuiStyleVar_ChildRounding: int
ImGuiStyleVar_ChildBorderSize: int
ImGuiStyleVar_PopupRounding: int
ImGuiStyleVar_PopupBorderSize: int
ImGuiStyleVar_FramePadding: int
ImGuiStyleVar_FrameRounding: int
ImGuiStyleVar_FrameBorderSize: int
ImGuiStyleVar_ItemSpacing: int
ImGuiStyleVar_ItemInnerSpacing: int
ImGuiStyleVar_IndentSpacing: int
ImGuiStyleVar_ScrollbarSize: int
ImGuiStyleVar_ScrollbarRounding: int
ImGuiStyleVar_GrabMinSize: int
ImGuiStyleVar_GrabRounding: int
ImGuiStyleVar_TabRounding: int
ImGuiStyleVar_ButtonTextAlign: int
ImGuiStyleVar_SelectableTextAlign: int
ImGuiStyleVar_COUNT: int
ImGuiColorEditFlags_None: int
ImGuiColorEditFlags_NoAlpha: int
ImGuiColorEditFlags_NoPicker: int
ImGuiColorEditFlags_NoOptions: int
ImGuiColorEditFlags_NoSmallPreview: int
ImGuiColorEditFlags_NoInputs: int
ImGuiColorEditFlags_NoTooltip: int
ImGuiColorEditFlags_NoLabel: int
ImGuiColorEditFlags_NoSidePreview: int
ImGuiColorEditFlags_NoDragDrop: int
ImGuiColorEditFlags_NoBorder: int
ImGuiColorEditFlags_AlphaBar: int
ImGuiColorEditFlags_AlphaPreview: int
ImGuiColorEditFlags_AlphaPreviewHalf: int
ImGuiColorEditFlags_HDR: int
ImGuiColorEditFlags_DisplayRGB: int
ImGuiColorEditFlags_DisplayHSV: int
ImGuiColorEditFlags_DisplayHex: int
ImGuiColorEditFlags_Uint8: int
ImGuiColorEditFlags_Float: int
ImGuiColorEditFlags_PickerHueBar: int
ImGuiColorEditFlags_PickerHueWheel: int
ImGuiColorEditFlags_InputRGB: int
ImGuiColorEditFlags_InputHSV: int
ImGuiColorEditFlags__OptionsDefault: int
ImGuiColorEditFlags__DisplayMask: int
ImGuiColorEditFlags__DataTypeMask: int
ImGuiColorEditFlags__PickerMask: int
ImGuiColorEditFlags__InputMask: int
ImGuiMouseButton_Left: int
ImGuiMouseButton_Right: int
ImGuiMouseButton_Middle: int
ImGuiMouseButton_COUNT: int
ImGuiMouseCursor_None: int
ImGuiMouseCursor_Arrow: int
ImGuiMouseCursor_TextInput: int
ImGuiMouseCursor_ResizeAll: int
ImGuiMouseCursor_ResizeNS: int
ImGuiMouseCursor_ResizeEW: int
ImGuiMouseCursor_ResizeNESW: int
ImGuiMouseCursor_ResizeNWSE: int
ImGuiMouseCursor_Hand: int
ImGuiMouseCursor_NotAllowed: int
ImGuiMouseCursor_COUNT: int
ImGuiCond_Always: int
ImGuiCond_Once: int
ImGuiCond_FirstUseEver: int
ImGuiCond_Appearing: int
