#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

void bind_imgui_enums(nb::module_& m) {

  // Enum bindings standardized like ImGuiKey
  nb::enum_<ImGuiDir>(m, "ImGuiDir")
    .value("ImGuiDir_None", ImGuiDir_None)
    .value("ImGuiDir_Left", ImGuiDir_Left)
    .value("ImGuiDir_Right", ImGuiDir_Right)
    .value("ImGuiDir_Up", ImGuiDir_Up)
    .value("ImGuiDir_Down", ImGuiDir_Down)
    .value("ImGuiDir_COUNT", ImGuiDir_COUNT)
  ;
  m.attr("ImGuiDir_None") = static_cast<int>(ImGuiDir_None);
  m.attr("ImGuiDir_Left") = static_cast<int>(ImGuiDir_Left);
  m.attr("ImGuiDir_Right") = static_cast<int>(ImGuiDir_Right);
  m.attr("ImGuiDir_Up") = static_cast<int>(ImGuiDir_Up);
  m.attr("ImGuiDir_Down") = static_cast<int>(ImGuiDir_Down);
  m.attr("ImGuiDir_COUNT") = static_cast<int>(ImGuiDir_COUNT);


  nb::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection")
    .value("ImGuiSortDirection_None", ImGuiSortDirection_None)
    .value("ImGuiSortDirection_Ascending", ImGuiSortDirection_Ascending)
    .value("ImGuiSortDirection_Descending", ImGuiSortDirection_Descending)
  ;
  m.attr("ImGuiSortDirection_None") = static_cast<int>(ImGuiSortDirection_None);
  m.attr("ImGuiSortDirection_Ascending") = static_cast<int>(ImGuiSortDirection_Ascending);
  m.attr("ImGuiSortDirection_Descending") = static_cast<int>(ImGuiSortDirection_Descending);

  nb::enum_<ImGuiWindowFlags_>(m, "ImGuiWindowFlags")
    .value("ImGuiWindowFlags_None", ImGuiWindowFlags_None)
    .value("ImGuiWindowFlags_NoTitleBar", ImGuiWindowFlags_NoTitleBar)
    .value("ImGuiWindowFlags_NoResize", ImGuiWindowFlags_NoResize)
    .value("ImGuiWindowFlags_NoMove", ImGuiWindowFlags_NoMove)
    .value("ImGuiWindowFlags_NoScrollbar", ImGuiWindowFlags_NoScrollbar)
    .value("ImGuiWindowFlags_NoScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse)
    .value("ImGuiWindowFlags_NoCollapse", ImGuiWindowFlags_NoCollapse)
    .value("ImGuiWindowFlags_AlwaysAutoResize", ImGuiWindowFlags_AlwaysAutoResize)
    .value("ImGuiWindowFlags_NoBackground", ImGuiWindowFlags_NoBackground)
    .value("ImGuiWindowFlags_NoSavedSettings", ImGuiWindowFlags_NoSavedSettings)
    .value("ImGuiWindowFlags_NoMouseInputs", ImGuiWindowFlags_NoMouseInputs)
    .value("ImGuiWindowFlags_MenuBar", ImGuiWindowFlags_MenuBar)
    .value("ImGuiWindowFlags_HorizontalScrollbar", ImGuiWindowFlags_HorizontalScrollbar)
    .value("ImGuiWindowFlags_NoFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing)
    .value("ImGuiWindowFlags_NoBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus)
    .value("ImGuiWindowFlags_AlwaysVerticalScrollbar", ImGuiWindowFlags_AlwaysVerticalScrollbar)
    .value("ImGuiWindowFlags_AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar)
    .value("ImGuiWindowFlags_AlwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding)
    .value("ImGuiWindowFlags_NoNavInputs", ImGuiWindowFlags_NoNavInputs)
    .value("ImGuiWindowFlags_NoNavFocus", ImGuiWindowFlags_NoNavFocus)
    .value("ImGuiWindowFlags_UnsavedDocument", ImGuiWindowFlags_UnsavedDocument)
    .value("ImGuiWindowFlags_NoNav", ImGuiWindowFlags_NoNav)
    .value("ImGuiWindowFlags_NoDecoration", ImGuiWindowFlags_NoDecoration)
    .value("ImGuiWindowFlags_NoInputs", ImGuiWindowFlags_NoInputs)
    .value("ImGuiWindowFlags_NavFlattened", ImGuiWindowFlags_NavFlattened)
    .value("ImGuiWindowFlags_ChildWindow", ImGuiWindowFlags_ChildWindow)
    .value("ImGuiWindowFlags_Tooltip", ImGuiWindowFlags_Tooltip)
    .value("ImGuiWindowFlags_Popup", ImGuiWindowFlags_Popup)
    .value("ImGuiWindowFlags_Modal", ImGuiWindowFlags_Modal)
    .value("ImGuiWindowFlags_ChildMenu", ImGuiWindowFlags_ChildMenu)
  ;
  m.attr("ImGuiWindowFlags_None") = static_cast<int>(ImGuiWindowFlags_None);
  m.attr("ImGuiWindowFlags_NoTitleBar") = static_cast<int>(ImGuiWindowFlags_NoTitleBar);
  m.attr("ImGuiWindowFlags_NoResize") = static_cast<int>(ImGuiWindowFlags_NoResize);
  m.attr("ImGuiWindowFlags_NoMove") = static_cast<int>(ImGuiWindowFlags_NoMove);
  m.attr("ImGuiWindowFlags_NoScrollbar") = static_cast<int>(ImGuiWindowFlags_NoScrollbar);
  m.attr("ImGuiWindowFlags_NoScrollWithMouse") = static_cast<int>(ImGuiWindowFlags_NoScrollWithMouse);
  m.attr("ImGuiWindowFlags_NoCollapse") = static_cast<int>(ImGuiWindowFlags_NoCollapse);
  m.attr("ImGuiWindowFlags_AlwaysAutoResize") = static_cast<int>(ImGuiWindowFlags_AlwaysAutoResize);
  m.attr("ImGuiWindowFlags_NoBackground") = static_cast<int>(ImGuiWindowFlags_NoBackground);
  m.attr("ImGuiWindowFlags_NoSavedSettings") = static_cast<int>(ImGuiWindowFlags_NoSavedSettings);
  m.attr("ImGuiWindowFlags_NoMouseInputs") = static_cast<int>(ImGuiWindowFlags_NoMouseInputs);
  m.attr("ImGuiWindowFlags_MenuBar") = static_cast<int>(ImGuiWindowFlags_MenuBar);
  m.attr("ImGuiWindowFlags_HorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_HorizontalScrollbar);
  m.attr("ImGuiWindowFlags_NoFocusOnAppearing") = static_cast<int>(ImGuiWindowFlags_NoFocusOnAppearing);
  m.attr("ImGuiWindowFlags_NoBringToFrontOnFocus") = static_cast<int>(ImGuiWindowFlags_NoBringToFrontOnFocus);
  m.attr("ImGuiWindowFlags_AlwaysVerticalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysVerticalScrollbar);
  m.attr("ImGuiWindowFlags_AlwaysHorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysHorizontalScrollbar);
  m.attr("ImGuiWindowFlags_AlwaysUseWindowPadding") = static_cast<int>(ImGuiWindowFlags_AlwaysUseWindowPadding);
  m.attr("ImGuiWindowFlags_NoNavInputs") = static_cast<int>(ImGuiWindowFlags_NoNavInputs);
  m.attr("ImGuiWindowFlags_NoNavFocus") = static_cast<int>(ImGuiWindowFlags_NoNavFocus);
  m.attr("ImGuiWindowFlags_UnsavedDocument") = static_cast<int>(ImGuiWindowFlags_UnsavedDocument);
  m.attr("ImGuiWindowFlags_NoNav") = static_cast<int>(ImGuiWindowFlags_NoNav);
  m.attr("ImGuiWindowFlags_NoDecoration") = static_cast<int>(ImGuiWindowFlags_NoDecoration);
  m.attr("ImGuiWindowFlags_NoInputs") = static_cast<int>(ImGuiWindowFlags_NoInputs);
  m.attr("ImGuiWindowFlags_NavFlattened") = static_cast<int>(ImGuiWindowFlags_NavFlattened);
  m.attr("ImGuiWindowFlags_ChildWindow") = static_cast<int>(ImGuiWindowFlags_ChildWindow);
  m.attr("ImGuiWindowFlags_Tooltip") = static_cast<int>(ImGuiWindowFlags_Tooltip);
  m.attr("ImGuiWindowFlags_Popup") = static_cast<int>(ImGuiWindowFlags_Popup);
  m.attr("ImGuiWindowFlags_Modal") = static_cast<int>(ImGuiWindowFlags_Modal);
  m.attr("ImGuiWindowFlags_ChildMenu") = static_cast<int>(ImGuiWindowFlags_ChildMenu);

  { // ImGuiInputTextFlags_
  auto e = nb::enum_<ImGuiInputTextFlags_>(m, "ImGuiInputTextFlags");
    e.value("ImGuiInputTextFlags_None", ImGuiInputTextFlags_::ImGuiInputTextFlags_None); m.attr("ImGuiInputTextFlags_None") = ImGuiInputTextFlags_::ImGuiInputTextFlags_None;
    // .value("ImGuiInputTextFlags_CharsDecimal", ImGuiInputTextFlags_CharsDecimal)
    // .value("ImGuiInputTextFlags_CharsHexadecimal", ImGuiInputTextFlags_CharsHexadecimal)
    // .value("ImGuiInputTextFlags_CharsUppercase", ImGuiInputTextFlags_CharsUppercase)
    // .value("ImGuiInputTextFlags_CharsNoBlank", ImGuiInputTextFlags_CharsNoBlank)
    // .value("ImGuiInputTextFlags_AutoSelectAll", ImGuiInputTextFlags_AutoSelectAll)
    // .value("ImGuiInputTextFlags_EnterReturnsTrue", ImGuiInputTextFlags_EnterReturnsTrue)
    // .value("ImGuiInputTextFlags_CallbackCompletion", ImGuiInputTextFlags_CallbackCompletion)
    // .value("ImGuiInputTextFlags_CallbackHistory", ImGuiInputTextFlags_CallbackHistory)
    // .value("ImGuiInputTextFlags_CallbackAlways", ImGuiInputTextFlags_CallbackAlways)
    // .value("ImGuiInputTextFlags_CallbackCharFilter", ImGuiInputTextFlags_CallbackCharFilter)
    // .value("ImGuiInputTextFlags_AllowTabInput", ImGuiInputTextFlags_AllowTabInput)
    // .value("ImGuiInputTextFlags_CtrlEnterForNewLine", ImGuiInputTextFlags_CtrlEnterForNewLine)
    // .value("ImGuiInputTextFlags_NoHorizontalScroll", ImGuiInputTextFlags_NoHorizontalScroll)
    // .value("ImGuiInputTextFlags_AlwaysOverwrite", ImGuiInputTextFlags_AlwaysOverwrite)
    // .value("ImGuiInputTextFlags_ReadOnly", ImGuiInputTextFlags_ReadOnly)
    // .value("ImGuiInputTextFlags_Password", ImGuiInputTextFlags_Password)
    // .value("ImGuiInputTextFlags_NoUndoRedo", ImGuiInputTextFlags_NoUndoRedo)
    // .value("ImGuiInputTextFlags_CharsScientific", ImGuiInputTextFlags_CharsScientific)
    // .value("ImGuiInputTextFlags_CallbackResize", ImGuiInputTextFlags_CallbackResize)
  ;
  }
  m.attr("ImGuiInputTextFlags_None") = static_cast<int>(ImGuiInputTextFlags_None);
  m.attr("ImGuiInputTextFlags_CharsDecimal") = static_cast<int>(ImGuiInputTextFlags_CharsDecimal);
  m.attr("ImGuiInputTextFlags_CharsHexadecimal") = static_cast<int>(ImGuiInputTextFlags_CharsHexadecimal);
  m.attr("ImGuiInputTextFlags_CharsUppercase") = static_cast<int>(ImGuiInputTextFlags_CharsUppercase);
  m.attr("ImGuiInputTextFlags_CharsNoBlank") = static_cast<int>(ImGuiInputTextFlags_CharsNoBlank);
  m.attr("ImGuiInputTextFlags_AutoSelectAll") = static_cast<int>(ImGuiInputTextFlags_AutoSelectAll);
  m.attr("ImGuiInputTextFlags_EnterReturnsTrue") = static_cast<int>(ImGuiInputTextFlags_EnterReturnsTrue);
  m.attr("ImGuiInputTextFlags_CallbackCompletion") = static_cast<int>(ImGuiInputTextFlags_CallbackCompletion);
  m.attr("ImGuiInputTextFlags_CallbackHistory") = static_cast<int>(ImGuiInputTextFlags_CallbackHistory);
  m.attr("ImGuiInputTextFlags_CallbackAlways") = static_cast<int>(ImGuiInputTextFlags_CallbackAlways);
  m.attr("ImGuiInputTextFlags_CallbackCharFilter") = static_cast<int>(ImGuiInputTextFlags_CallbackCharFilter);
  m.attr("ImGuiInputTextFlags_AllowTabInput") = static_cast<int>(ImGuiInputTextFlags_AllowTabInput);
  m.attr("ImGuiInputTextFlags_CtrlEnterForNewLine") = static_cast<int>(ImGuiInputTextFlags_CtrlEnterForNewLine);
  m.attr("ImGuiInputTextFlags_NoHorizontalScroll") = static_cast<int>(ImGuiInputTextFlags_NoHorizontalScroll);
  m.attr("ImGuiInputTextFlags_AlwaysOverwrite") = static_cast<int>(ImGuiInputTextFlags_AlwaysOverwrite);
  m.attr("ImGuiInputTextFlags_ReadOnly") = static_cast<int>(ImGuiInputTextFlags_ReadOnly);
  m.attr("ImGuiInputTextFlags_Password") = static_cast<int>(ImGuiInputTextFlags_Password);
  m.attr("ImGuiInputTextFlags_NoUndoRedo") = static_cast<int>(ImGuiInputTextFlags_NoUndoRedo);
  m.attr("ImGuiInputTextFlags_CharsScientific") = static_cast<int>(ImGuiInputTextFlags_CharsScientific);
  m.attr("ImGuiInputTextFlags_CallbackResize") = static_cast<int>(ImGuiInputTextFlags_CallbackResize);

  nb::enum_<ImGuiTreeNodeFlags_>(m, "ImGuiTreeNodeFlags")
    .value("ImGuiTreeNodeFlags_None", ImGuiTreeNodeFlags_None)
    .value("ImGuiTreeNodeFlags_Selected", ImGuiTreeNodeFlags_Selected)
    .value("ImGuiTreeNodeFlags_Framed", ImGuiTreeNodeFlags_Framed)
    .value("ImGuiTreeNodeFlags_AllowItemOverlap", ImGuiTreeNodeFlags_AllowItemOverlap)
    .value("ImGuiTreeNodeFlags_NoTreePushOnOpen", ImGuiTreeNodeFlags_NoTreePushOnOpen)
    .value("ImGuiTreeNodeFlags_NoAutoOpenOnLog", ImGuiTreeNodeFlags_NoAutoOpenOnLog)
    .value("ImGuiTreeNodeFlags_DefaultOpen", ImGuiTreeNodeFlags_DefaultOpen)
    .value("ImGuiTreeNodeFlags_OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick)
    .value("ImGuiTreeNodeFlags_OpenOnArrow", ImGuiTreeNodeFlags_OpenOnArrow)
    .value("ImGuiTreeNodeFlags_Leaf", ImGuiTreeNodeFlags_Leaf)
    .value("ImGuiTreeNodeFlags_Bullet", ImGuiTreeNodeFlags_Bullet)
    .value("ImGuiTreeNodeFlags_FramePadding", ImGuiTreeNodeFlags_FramePadding)
    .value("ImGuiTreeNodeFlags_SpanAvailWidth", ImGuiTreeNodeFlags_SpanAvailWidth)
    .value("ImGuiTreeNodeFlags_SpanFullWidth", ImGuiTreeNodeFlags_SpanFullWidth)
    .value("ImGuiTreeNodeFlags_NavLeftJumpsBackHere", ImGuiTreeNodeFlags_NavLeftJumpsBackHere)
    .value("ImGuiTreeNodeFlags_CollapsingHeader", ImGuiTreeNodeFlags_CollapsingHeader)
  ;
  nb::enum_<ImGuiSelectableFlags_>(m, "ImGuiSelectableFlags")
    .value("ImGuiSelectableFlags_None", ImGuiSelectableFlags_None)
    .value("ImGuiSelectableFlags_DontClosePopups", ImGuiSelectableFlags_DontClosePopups)
    .value("ImGuiSelectableFlags_SpanAllColumns", ImGuiSelectableFlags_SpanAllColumns)
    .value("ImGuiSelectableFlags_AllowDoubleClick", ImGuiSelectableFlags_AllowDoubleClick)
    .value("ImGuiSelectableFlags_Disabled", ImGuiSelectableFlags_Disabled)
    .value("ImGuiSelectableFlags_AllowItemOverlap", ImGuiSelectableFlags_AllowItemOverlap)
  ;
  nb::enum_<ImGuiComboFlags_>(m, "ImGuiComboFlags")
    .value("ImGuiComboFlags_None", ImGuiComboFlags_None)
    .value("ImGuiComboFlags_PopupAlignLeft", ImGuiComboFlags_PopupAlignLeft)
    .value("ImGuiComboFlags_HeightSmall", ImGuiComboFlags_HeightSmall)
    .value("ImGuiComboFlags_HeightRegular", ImGuiComboFlags_HeightRegular)
    .value("ImGuiComboFlags_HeightLarge", ImGuiComboFlags_HeightLarge)
    .value("ImGuiComboFlags_HeightLargest", ImGuiComboFlags_HeightLargest)
    .value("ImGuiComboFlags_NoArrowButton", ImGuiComboFlags_NoArrowButton)
    .value("ImGuiComboFlags_NoPreview", ImGuiComboFlags_NoPreview)
    .value("ImGuiComboFlags_HeightMask_", ImGuiComboFlags_HeightMask_)
  ;
  nb::enum_<ImGuiTabBarFlags_>(m, "ImGuiTabBarFlags")
    .value("ImGuiTabBarFlags_None", ImGuiTabBarFlags_None)
    .value("ImGuiTabBarFlags_Reorderable", ImGuiTabBarFlags_Reorderable)
    .value("ImGuiTabBarFlags_AutoSelectNewTabs", ImGuiTabBarFlags_AutoSelectNewTabs)
    .value("ImGuiTabBarFlags_TabListPopupButton", ImGuiTabBarFlags_TabListPopupButton)
    .value("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)
    .value("ImGuiTabBarFlags_NoTabListScrollingButtons", ImGuiTabBarFlags_NoTabListScrollingButtons)
    .value("ImGuiTabBarFlags_NoTooltip", ImGuiTabBarFlags_NoTooltip)
    .value("ImGuiTabBarFlags_FittingPolicyResizeDown", ImGuiTabBarFlags_FittingPolicyResizeDown)
    .value("ImGuiTabBarFlags_FittingPolicyScroll", ImGuiTabBarFlags_FittingPolicyScroll)
    .value("ImGuiTabBarFlags_FittingPolicyMask_", ImGuiTabBarFlags_FittingPolicyMask_)
    .value("ImGuiTabBarFlags_FittingPolicyDefault_", ImGuiTabBarFlags_FittingPolicyDefault_)
  ;
  nb::enum_<ImGuiTabItemFlags_>(m, "ImGuiTabItemFlags")
    .value("ImGuiTabItemFlags_None", ImGuiTabItemFlags_None)
    .value("ImGuiTabItemFlags_UnsavedDocument", ImGuiTabItemFlags_UnsavedDocument)
    .value("ImGuiTabItemFlags_SetSelected", ImGuiTabItemFlags_SetSelected)
    .value("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton)
    .value("ImGuiTabItemFlags_NoPushId", ImGuiTabItemFlags_NoPushId)
  ;
  nb::enum_<ImGuiTableFlags_>(m, "ImGuiTableFlags")
    .value("ImGuiTableFlags_None", ImGuiTableFlags_None)
    .value("ImGuiTableFlags_Resizable", ImGuiTableFlags_Resizable)
    .value("ImGuiTableFlags_Reorderable", ImGuiTableFlags_Reorderable)
    .value("ImGuiTableFlags_Hideable", ImGuiTableFlags_Hideable)
    .value("ImGuiTableFlags_Sortable", ImGuiTableFlags_Sortable)
    .value("ImGuiTableFlags_NoSavedSettings", ImGuiTableFlags_NoSavedSettings)
    .value("ImGuiTableFlags_ContextMenuInBody", ImGuiTableFlags_ContextMenuInBody)
    .value("ImGuiTableFlags_RowBg", ImGuiTableFlags_RowBg)
    .value("ImGuiTableFlags_BordersInnerH", ImGuiTableFlags_BordersInnerH)
    .value("ImGuiTableFlags_BordersOuterH", ImGuiTableFlags_BordersOuterH)
    .value("ImGuiTableFlags_BordersInnerV", ImGuiTableFlags_BordersInnerV)
    .value("ImGuiTableFlags_BordersOuterV", ImGuiTableFlags_BordersOuterV)
    .value("ImGuiTableFlags_BordersH", ImGuiTableFlags_BordersH)
    .value("ImGuiTableFlags_BordersV", ImGuiTableFlags_BordersV)
    .value("ImGuiTableFlags_BordersInner", ImGuiTableFlags_BordersInner)
    .value("ImGuiTableFlags_BordersOuter", ImGuiTableFlags_BordersOuter)
    .value("ImGuiTableFlags_Borders", ImGuiTableFlags_Borders)
    .value("ImGuiTableFlags_NoBordersInBody", ImGuiTableFlags_NoBordersInBody)
    .value("ImGuiTableFlags_NoBordersInBodyUntilResize", ImGuiTableFlags_NoBordersInBodyUntilResize)
    .value("ImGuiTableFlags_SizingFixedFit", ImGuiTableFlags_SizingFixedFit)
    .value("ImGuiTableFlags_SizingFixedSame", ImGuiTableFlags_SizingFixedSame)
    .value("ImGuiTableFlags_SizingStretchProp", ImGuiTableFlags_SizingStretchProp)
    .value("ImGuiTableFlags_SizingStretchSame", ImGuiTableFlags_SizingStretchSame)
    .value("ImGuiTableFlags_NoHostExtendX", ImGuiTableFlags_NoHostExtendX)
    .value("ImGuiTableFlags_NoHostExtendY", ImGuiTableFlags_NoHostExtendY)
    .value("ImGuiTableFlags_NoKeepColumnsVisible", ImGuiTableFlags_NoKeepColumnsVisible)
    .value("ImGuiTableFlags_PreciseWidths", ImGuiTableFlags_PreciseWidths)
    .value("ImGuiTableFlags_NoClip", ImGuiTableFlags_NoClip)
    .value("ImGuiTableFlags_PadOuterX", ImGuiTableFlags_PadOuterX)
    .value("ImGuiTableFlags_NoPadOuterX", ImGuiTableFlags_NoPadOuterX)
    .value("ImGuiTableFlags_NoPadInnerX", ImGuiTableFlags_NoPadInnerX)
    .value("ImGuiTableFlags_ScrollX", ImGuiTableFlags_ScrollX)
    .value("ImGuiTableFlags_ScrollY", ImGuiTableFlags_ScrollY)
    .value("ImGuiTableFlags_SortMulti", ImGuiTableFlags_SortMulti)
    .value("ImGuiTableFlags_SortTristate", ImGuiTableFlags_SortTristate)
    .value("ImGuiTableFlags_HighlightHoveredColumn", ImGuiTableFlags_HighlightHoveredColumn)
  ;
  nb::enum_<ImGuiTableColumnFlags_>(m, "ImGuiTableColumnFlags")
    .value("ImGuiTableColumnFlags_None", ImGuiTableColumnFlags_None)
    .value("ImGuiTableColumnFlags_Disabled", ImGuiTableColumnFlags_Disabled)
    .value("ImGuiTableColumnFlags_DefaultHide", ImGuiTableColumnFlags_DefaultHide)
    .value("ImGuiTableColumnFlags_DefaultSort", ImGuiTableColumnFlags_DefaultSort)
    .value("ImGuiTableColumnFlags_WidthStretch", ImGuiTableColumnFlags_WidthStretch)
    .value("ImGuiTableColumnFlags_WidthFixed", ImGuiTableColumnFlags_WidthFixed)
    .value("ImGuiTableColumnFlags_NoResize", ImGuiTableColumnFlags_NoResize)
    .value("ImGuiTableColumnFlags_NoReorder", ImGuiTableColumnFlags_NoReorder)
    .value("ImGuiTableColumnFlags_NoHide", ImGuiTableColumnFlags_NoHide)
    .value("ImGuiTableColumnFlags_NoClip", ImGuiTableColumnFlags_NoClip)
    .value("ImGuiTableColumnFlags_NoSort", ImGuiTableColumnFlags_NoSort)
    .value("ImGuiTableColumnFlags_NoSortAscending", ImGuiTableColumnFlags_NoSortAscending)
    .value("ImGuiTableColumnFlags_NoSortDescending", ImGuiTableColumnFlags_NoSortDescending)
    .value("ImGuiTableColumnFlags_NoHeaderLabel", ImGuiTableColumnFlags_NoHeaderLabel)
    .value("ImGuiTableColumnFlags_NoHeaderWidth", ImGuiTableColumnFlags_NoHeaderWidth)
    .value("ImGuiTableColumnFlags_PreferSortAscending", ImGuiTableColumnFlags_PreferSortAscending)
    .value("ImGuiTableColumnFlags_PreferSortDescending", ImGuiTableColumnFlags_PreferSortDescending)
    .value("ImGuiTableColumnFlags_IndentEnable", ImGuiTableColumnFlags_IndentEnable)
    .value("ImGuiTableColumnFlags_IndentDisable", ImGuiTableColumnFlags_IndentDisable)
    .value("ImGuiTableColumnFlags_AngledHeader", ImGuiTableColumnFlags_AngledHeader)
    .value("ImGuiTableColumnFlags_IsEnabled", ImGuiTableColumnFlags_IsEnabled)
    .value("ImGuiTableColumnFlags_IsVisible", ImGuiTableColumnFlags_IsVisible)
    .value("ImGuiTableColumnFlags_IsSorted", ImGuiTableColumnFlags_IsSorted)
    .value("ImGuiTableColumnFlags_IsHovered", ImGuiTableColumnFlags_IsHovered)
  ;
  nb::enum_<ImGuiTableRowFlags_>(m, "ImGuiTableRowFlags")
    .value("ImGuiTableRowFlags_None", ImGuiTableRowFlags_None)
    .value("ImGuiTableRowFlags_Headers", ImGuiTableRowFlags_Headers)
  ;
  nb::enum_<ImGuiTableBgTarget_>(m, "ImGuiTableBgTarget")
    .value("ImGuiTableBgTarget_None", ImGuiTableBgTarget_None)
    .value("ImGuiTableBgTarget_RowBg0", ImGuiTableBgTarget_RowBg0)
    .value("ImGuiTableBgTarget_RowBg1", ImGuiTableBgTarget_RowBg1)
    .value("ImGuiTableBgTarget_CellBg", ImGuiTableBgTarget_CellBg)
  ;
  nb::enum_<ImGuiFocusedFlags_>(m, "ImGuiFocusedFlags")
    .value("ImGuiFocusedFlags_None", ImGuiFocusedFlags_None)
    .value("ImGuiFocusedFlags_ChildWindows", ImGuiFocusedFlags_ChildWindows)
    .value("ImGuiFocusedFlags_RootWindow", ImGuiFocusedFlags_RootWindow)
    .value("ImGuiFocusedFlags_AnyWindow", ImGuiFocusedFlags_AnyWindow)
    .value("ImGuiFocusedFlags_RootAndChildWindows", ImGuiFocusedFlags_RootAndChildWindows)
  ;
  nb::enum_<ImGuiHoveredFlags_>(m, "ImGuiHoveredFlags")
    .value("ImGuiHoveredFlags_None", ImGuiHoveredFlags_None)
    .value("ImGuiHoveredFlags_ChildWindows", ImGuiHoveredFlags_ChildWindows)
    .value("ImGuiHoveredFlags_RootWindow", ImGuiHoveredFlags_RootWindow)
    .value("ImGuiHoveredFlags_AnyWindow", ImGuiHoveredFlags_AnyWindow)
    .value("ImGuiHoveredFlags_AllowWhenBlockedByPopup", ImGuiHoveredFlags_AllowWhenBlockedByPopup)
    .value("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem", ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
    .value("ImGuiHoveredFlags_AllowWhenOverlapped", ImGuiHoveredFlags_AllowWhenOverlapped)
    .value("ImGuiHoveredFlags_AllowWhenDisabled", ImGuiHoveredFlags_AllowWhenDisabled)
    .value("ImGuiHoveredFlags_RectOnly", ImGuiHoveredFlags_RectOnly)
    .value("ImGuiHoveredFlags_RootAndChildWindows", ImGuiHoveredFlags_RootAndChildWindows)
  ;
  nb::enum_<ImGuiDragDropFlags_>(m, "ImGuiDragDropFlags")
    .value("ImGuiDragDropFlags_None", ImGuiDragDropFlags_None)
    .value("ImGuiDragDropFlags_SourceNoPreviewTooltip", ImGuiDragDropFlags_SourceNoPreviewTooltip)
    .value("ImGuiDragDropFlags_SourceNoDisableHover", ImGuiDragDropFlags_SourceNoDisableHover)
    .value("ImGuiDragDropFlags_SourceNoHoldToOpenOthers", ImGuiDragDropFlags_SourceNoHoldToOpenOthers)
    .value("ImGuiDragDropFlags_SourceAllowNullID", ImGuiDragDropFlags_SourceAllowNullID)
    .value("ImGuiDragDropFlags_SourceExtern", ImGuiDragDropFlags_SourceExtern)
    .value("ImGuiDragDropFlags_SourceAutoExpirePayload", ImGuiDragDropFlags_SourceAutoExpirePayload)
    .value("ImGuiDragDropFlags_AcceptBeforeDelivery", ImGuiDragDropFlags_AcceptBeforeDelivery)
    .value("ImGuiDragDropFlags_AcceptNoDrawDefaultRect", ImGuiDragDropFlags_AcceptNoDrawDefaultRect)
    .value("ImGuiDragDropFlags_AcceptNoPreviewTooltip", ImGuiDragDropFlags_AcceptNoPreviewTooltip)
    .value("ImGuiDragDropFlags_AcceptPeekOnly", ImGuiDragDropFlags_AcceptPeekOnly)
  ;
  nb::enum_<ImGuiDataType_>(m, "ImGuiDataType")
    .value("ImGuiDataType_S8", ImGuiDataType_S8)
    .value("ImGuiDataType_U8", ImGuiDataType_U8)
    .value("ImGuiDataType_S16", ImGuiDataType_S16)
    .value("ImGuiDataType_U16", ImGuiDataType_U16)
    .value("ImGuiDataType_S32", ImGuiDataType_S32)
    .value("ImGuiDataType_U32", ImGuiDataType_U32)
    .value("ImGuiDataType_S64", ImGuiDataType_S64)
    .value("ImGuiDataType_U64", ImGuiDataType_U64)
    .value("ImGuiDataType_Float", ImGuiDataType_Float)
    .value("ImGuiDataType_Double", ImGuiDataType_Double)
    .value("ImGuiDataType_COUNT", ImGuiDataType_COUNT)
  ;



  m.attr("ImGuiTreeNodeFlags_None") = static_cast<int>(ImGuiTreeNodeFlags_None);
  m.attr("ImGuiTreeNodeFlags_Selected") = static_cast<int>(ImGuiTreeNodeFlags_Selected);
  m.attr("ImGuiTreeNodeFlags_Framed") = static_cast<int>(ImGuiTreeNodeFlags_Framed);
  m.attr("ImGuiTreeNodeFlags_AllowItemOverlap") = static_cast<int>(ImGuiTreeNodeFlags_AllowItemOverlap);
  m.attr("ImGuiTreeNodeFlags_NoTreePushOnOpen") = static_cast<int>(ImGuiTreeNodeFlags_NoTreePushOnOpen);
  m.attr("ImGuiTreeNodeFlags_NoAutoOpenOnLog") = static_cast<int>(ImGuiTreeNodeFlags_NoAutoOpenOnLog);
  m.attr("ImGuiTreeNodeFlags_DefaultOpen") = static_cast<int>(ImGuiTreeNodeFlags_DefaultOpen);
  m.attr("ImGuiTreeNodeFlags_OpenOnDoubleClick") = static_cast<int>(ImGuiTreeNodeFlags_OpenOnDoubleClick);
  m.attr("ImGuiTreeNodeFlags_OpenOnArrow") = static_cast<int>(ImGuiTreeNodeFlags_OpenOnArrow);
  m.attr("ImGuiTreeNodeFlags_Leaf") = static_cast<int>(ImGuiTreeNodeFlags_Leaf);
  m.attr("ImGuiTreeNodeFlags_Bullet") = static_cast<int>(ImGuiTreeNodeFlags_Bullet);
  m.attr("ImGuiTreeNodeFlags_FramePadding") = static_cast<int>(ImGuiTreeNodeFlags_FramePadding);
  m.attr("ImGuiTreeNodeFlags_SpanAvailWidth") = static_cast<int>(ImGuiTreeNodeFlags_SpanAvailWidth);
  m.attr("ImGuiTreeNodeFlags_SpanFullWidth") = static_cast<int>(ImGuiTreeNodeFlags_SpanFullWidth);
  m.attr("ImGuiTreeNodeFlags_NavLeftJumpsBackHere") = static_cast<int>(ImGuiTreeNodeFlags_NavLeftJumpsBackHere);
  m.attr("ImGuiTreeNodeFlags_CollapsingHeader") = static_cast<int>(ImGuiTreeNodeFlags_CollapsingHeader);

  m.attr("ImGuiSelectableFlags_None") = static_cast<int>(ImGuiSelectableFlags_None);
  m.attr("ImGuiSelectableFlags_DontClosePopups") = static_cast<int>(ImGuiSelectableFlags_DontClosePopups);
  m.attr("ImGuiSelectableFlags_SpanAllColumns") = static_cast<int>(ImGuiSelectableFlags_SpanAllColumns);
  m.attr("ImGuiSelectableFlags_AllowDoubleClick") = static_cast<int>(ImGuiSelectableFlags_AllowDoubleClick);
  m.attr("ImGuiSelectableFlags_Disabled") = static_cast<int>(ImGuiSelectableFlags_Disabled);
  m.attr("ImGuiSelectableFlags_AllowItemOverlap") = static_cast<int>(ImGuiSelectableFlags_AllowItemOverlap);

  m.attr("ImGuiComboFlags_None") = static_cast<int>(ImGuiComboFlags_None);
  m.attr("ImGuiComboFlags_PopupAlignLeft") = static_cast<int>(ImGuiComboFlags_PopupAlignLeft);
  m.attr("ImGuiComboFlags_HeightSmall") = static_cast<int>(ImGuiComboFlags_HeightSmall);
  m.attr("ImGuiComboFlags_HeightRegular") = static_cast<int>(ImGuiComboFlags_HeightRegular);
  m.attr("ImGuiComboFlags_HeightLarge") = static_cast<int>(ImGuiComboFlags_HeightLarge);
  m.attr("ImGuiComboFlags_HeightLargest") = static_cast<int>(ImGuiComboFlags_HeightLargest);
  m.attr("ImGuiComboFlags_NoArrowButton") = static_cast<int>(ImGuiComboFlags_NoArrowButton);
  m.attr("ImGuiComboFlags_NoPreview") = static_cast<int>(ImGuiComboFlags_NoPreview);
  m.attr("ImGuiComboFlags_HeightMask_") = static_cast<int>(ImGuiComboFlags_HeightMask_);

  m.attr("ImGuiTabBarFlags_None") = static_cast<int>(ImGuiTabBarFlags_None);
  m.attr("ImGuiTabBarFlags_Reorderable") = static_cast<int>(ImGuiTabBarFlags_Reorderable);
  m.attr("ImGuiTabBarFlags_AutoSelectNewTabs") = static_cast<int>(ImGuiTabBarFlags_AutoSelectNewTabs);
  m.attr("ImGuiTabBarFlags_TabListPopupButton") = static_cast<int>(ImGuiTabBarFlags_TabListPopupButton);
  m.attr("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton") =
      static_cast<int>(ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
  m.attr("ImGuiTabBarFlags_NoTabListScrollingButtons") = static_cast<int>(ImGuiTabBarFlags_NoTabListScrollingButtons);
  m.attr("ImGuiTabBarFlags_NoTooltip") = static_cast<int>(ImGuiTabBarFlags_NoTooltip);
  m.attr("ImGuiTabBarFlags_FittingPolicyResizeDown") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyResizeDown);
  m.attr("ImGuiTabBarFlags_FittingPolicyScroll") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyScroll);
  m.attr("ImGuiTabBarFlags_FittingPolicyMask_") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyMask_);
  m.attr("ImGuiTabBarFlags_FittingPolicyDefault_") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyDefault_);

  m.attr("ImGuiTabItemFlags_None") = static_cast<int>(ImGuiTabItemFlags_None);
  m.attr("ImGuiTabItemFlags_UnsavedDocument") = static_cast<int>(ImGuiTabItemFlags_UnsavedDocument);
  m.attr("ImGuiTabItemFlags_SetSelected") = static_cast<int>(ImGuiTabItemFlags_SetSelected);
  m.attr("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton") =
      static_cast<int>(ImGuiTabItemFlags_NoCloseWithMiddleMouseButton);
  m.attr("ImGuiTabItemFlags_NoPushId") = static_cast<int>(ImGuiTabItemFlags_NoPushId);

  m.attr("ImGuiTableFlags_None") = static_cast<int>(ImGuiTableFlags_None);
  m.attr("ImGuiTableFlags_Resizable") = static_cast<int>(ImGuiTableFlags_Resizable);
  m.attr("ImGuiTableFlags_Reorderable") = static_cast<int>(ImGuiTableFlags_Reorderable);
  m.attr("ImGuiTableFlags_Hideable") = static_cast<int>(ImGuiTableFlags_Hideable);
  m.attr("ImGuiTableFlags_Sortable") = static_cast<int>(ImGuiTableFlags_Sortable);
  m.attr("ImGuiTableFlags_NoSavedSettings") = static_cast<int>(ImGuiTableFlags_NoSavedSettings);
  m.attr("ImGuiTableFlags_ContextMenuInBody") = static_cast<int>(ImGuiTableFlags_ContextMenuInBody);
  m.attr("ImGuiTableFlags_RowBg") = static_cast<int>(ImGuiTableFlags_RowBg);
  m.attr("ImGuiTableFlags_BordersInnerH") = static_cast<int>(ImGuiTableFlags_BordersInnerH);
  m.attr("ImGuiTableFlags_BordersOuterH") = static_cast<int>(ImGuiTableFlags_BordersOuterH);
  m.attr("ImGuiTableFlags_BordersInnerV") = static_cast<int>(ImGuiTableFlags_BordersInnerV);
  m.attr("ImGuiTableFlags_BordersOuterV") = static_cast<int>(ImGuiTableFlags_BordersOuterV);
  m.attr("ImGuiTableFlags_BordersH") = static_cast<int>(ImGuiTableFlags_BordersH);
  m.attr("ImGuiTableFlags_BordersV") = static_cast<int>(ImGuiTableFlags_BordersV);
  m.attr("ImGuiTableFlags_BordersInner") = static_cast<int>(ImGuiTableFlags_BordersInner);
  m.attr("ImGuiTableFlags_BordersOuter") = static_cast<int>(ImGuiTableFlags_BordersOuter);
  m.attr("ImGuiTableFlags_Borders") = static_cast<int>(ImGuiTableFlags_Borders);
  m.attr("ImGuiTableFlags_NoBordersInBody") = static_cast<int>(ImGuiTableFlags_NoBordersInBody);
  m.attr("ImGuiTableFlags_NoBordersInBodyUntilResize") = static_cast<int>(ImGuiTableFlags_NoBordersInBodyUntilResize);
  m.attr("ImGuiTableFlags_SizingFixedFit") = static_cast<int>(ImGuiTableFlags_SizingFixedFit);
  m.attr("ImGuiTableFlags_SizingFixedSame") = static_cast<int>(ImGuiTableFlags_SizingFixedSame);
  m.attr("ImGuiTableFlags_SizingStretchProp") = static_cast<int>(ImGuiTableFlags_SizingStretchProp);
  m.attr("ImGuiTableFlags_SizingStretchSame") = static_cast<int>(ImGuiTableFlags_SizingStretchSame);
  m.attr("ImGuiTableFlags_NoHostExtendX") = static_cast<int>(ImGuiTableFlags_NoHostExtendX);
  m.attr("ImGuiTableFlags_NoHostExtendY") = static_cast<int>(ImGuiTableFlags_NoHostExtendY);
  m.attr("ImGuiTableFlags_NoKeepColumnsVisible") = static_cast<int>(ImGuiTableFlags_NoKeepColumnsVisible);
  m.attr("ImGuiTableFlags_PreciseWidths") = static_cast<int>(ImGuiTableFlags_PreciseWidths);
  m.attr("ImGuiTableFlags_NoClip") = static_cast<int>(ImGuiTableFlags_NoClip);
  m.attr("ImGuiTableFlags_PadOuterX") = static_cast<int>(ImGuiTableFlags_PadOuterX);
  m.attr("ImGuiTableFlags_NoPadOuterX") = static_cast<int>(ImGuiTableFlags_NoPadOuterX);
  m.attr("ImGuiTableFlags_NoPadInnerX") = static_cast<int>(ImGuiTableFlags_NoPadInnerX);
  m.attr("ImGuiTableFlags_ScrollX") = static_cast<int>(ImGuiTableFlags_ScrollX);
  m.attr("ImGuiTableFlags_ScrollY") = static_cast<int>(ImGuiTableFlags_ScrollY);
  m.attr("ImGuiTableFlags_SortMulti") = static_cast<int>(ImGuiTableFlags_SortMulti);
  m.attr("ImGuiTableFlags_SortTristate") = static_cast<int>(ImGuiTableFlags_SortTristate);
  m.attr("ImGuiTableFlags_HighlightHoveredColumn") = static_cast<int>(ImGuiTableFlags_HighlightHoveredColumn);

  m.attr("ImGuiTableColumnFlags_None") = static_cast<int>(ImGuiTableColumnFlags_None);
  m.attr("ImGuiTableColumnFlags_Disabled") = static_cast<int>(ImGuiTableColumnFlags_Disabled);
  m.attr("ImGuiTableColumnFlags_DefaultHide") = static_cast<int>(ImGuiTableColumnFlags_DefaultHide);
  m.attr("ImGuiTableColumnFlags_DefaultSort") = static_cast<int>(ImGuiTableColumnFlags_DefaultSort);
  m.attr("ImGuiTableColumnFlags_WidthStretch") = static_cast<int>(ImGuiTableColumnFlags_WidthStretch);
  m.attr("ImGuiTableColumnFlags_WidthFixed") = static_cast<int>(ImGuiTableColumnFlags_WidthFixed);
  m.attr("ImGuiTableColumnFlags_NoResize") = static_cast<int>(ImGuiTableColumnFlags_NoResize);
  m.attr("ImGuiTableColumnFlags_NoReorder") = static_cast<int>(ImGuiTableColumnFlags_NoReorder);
  m.attr("ImGuiTableColumnFlags_NoHide") = static_cast<int>(ImGuiTableColumnFlags_NoHide);
  m.attr("ImGuiTableColumnFlags_NoClip") = static_cast<int>(ImGuiTableColumnFlags_NoClip);
  m.attr("ImGuiTableColumnFlags_NoSort") = static_cast<int>(ImGuiTableColumnFlags_NoSort);
  m.attr("ImGuiTableColumnFlags_NoSortAscending") = static_cast<int>(ImGuiTableColumnFlags_NoSortAscending);
  m.attr("ImGuiTableColumnFlags_NoSortDescending") = static_cast<int>(ImGuiTableColumnFlags_NoSortDescending);
  m.attr("ImGuiTableColumnFlags_NoHeaderLabel") = static_cast<int>(ImGuiTableColumnFlags_NoHeaderLabel);
  m.attr("ImGuiTableColumnFlags_NoHeaderWidth") = static_cast<int>(ImGuiTableColumnFlags_NoHeaderWidth);
  m.attr("ImGuiTableColumnFlags_PreferSortAscending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortAscending);
  m.attr("ImGuiTableColumnFlags_PreferSortDescending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortDescending);
  m.attr("ImGuiTableColumnFlags_IndentEnable") = static_cast<int>(ImGuiTableColumnFlags_IndentEnable);
  m.attr("ImGuiTableColumnFlags_IndentDisable") = static_cast<int>(ImGuiTableColumnFlags_IndentDisable);
  m.attr("ImGuiTableColumnFlags_AngledHeader") = static_cast<int>(ImGuiTableColumnFlags_AngledHeader);
  m.attr("ImGuiTableColumnFlags_IsEnabled") = static_cast<int>(ImGuiTableColumnFlags_IsEnabled);
  m.attr("ImGuiTableColumnFlags_IsVisible") = static_cast<int>(ImGuiTableColumnFlags_IsVisible);
  m.attr("ImGuiTableColumnFlags_IsSorted") = static_cast<int>(ImGuiTableColumnFlags_IsSorted);
  m.attr("ImGuiTableColumnFlags_IsHovered") = static_cast<int>(ImGuiTableColumnFlags_IsHovered);
  
  m.attr("ImGuiTableRowFlags_None") = static_cast<int>(ImGuiTableRowFlags_None);
  m.attr("ImGuiTableRowFlags_Headers") = static_cast<int>(ImGuiTableRowFlags_Headers);
  
  m.attr("ImGuiTableBgTarget_None") = static_cast<int>(ImGuiTableBgTarget_None);
  m.attr("ImGuiTableBgTarget_RowBg0") = static_cast<int>(ImGuiTableBgTarget_RowBg0);
  m.attr("ImGuiTableBgTarget_RowBg1") = static_cast<int>(ImGuiTableBgTarget_RowBg1);
  m.attr("ImGuiTableBgTarget_CellBg") = static_cast<int>(ImGuiTableBgTarget_CellBg);

  m.attr("ImGuiFocusedFlags_None") = static_cast<int>(ImGuiFocusedFlags_None);
  m.attr("ImGuiFocusedFlags_ChildWindows") = static_cast<int>(ImGuiFocusedFlags_ChildWindows);
  m.attr("ImGuiFocusedFlags_RootWindow") = static_cast<int>(ImGuiFocusedFlags_RootWindow);
  m.attr("ImGuiFocusedFlags_AnyWindow") = static_cast<int>(ImGuiFocusedFlags_AnyWindow);
  m.attr("ImGuiFocusedFlags_RootAndChildWindows") = static_cast<int>(ImGuiFocusedFlags_RootAndChildWindows);

  m.attr("ImGuiHoveredFlags_None") = static_cast<int>(ImGuiHoveredFlags_None);
  m.attr("ImGuiHoveredFlags_ChildWindows") = static_cast<int>(ImGuiHoveredFlags_ChildWindows);
  m.attr("ImGuiHoveredFlags_RootWindow") = static_cast<int>(ImGuiHoveredFlags_RootWindow);
  m.attr("ImGuiHoveredFlags_AnyWindow") = static_cast<int>(ImGuiHoveredFlags_AnyWindow);
  m.attr("ImGuiHoveredFlags_AllowWhenBlockedByPopup") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
  m.attr("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
  m.attr("ImGuiHoveredFlags_AllowWhenOverlapped") = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlapped);
  m.attr("ImGuiHoveredFlags_AllowWhenDisabled") = static_cast<int>(ImGuiHoveredFlags_AllowWhenDisabled);
  m.attr("ImGuiHoveredFlags_RectOnly") = static_cast<int>(ImGuiHoveredFlags_RectOnly);
  m.attr("ImGuiHoveredFlags_RootAndChildWindows") = static_cast<int>(ImGuiHoveredFlags_RootAndChildWindows);

  m.attr("ImGuiDragDropFlags_None") = static_cast<int>(ImGuiDragDropFlags_None);
  m.attr("ImGuiDragDropFlags_SourceNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_SourceNoPreviewTooltip);
  m.attr("ImGuiDragDropFlags_SourceNoDisableHover") = static_cast<int>(ImGuiDragDropFlags_SourceNoDisableHover);
  m.attr("ImGuiDragDropFlags_SourceNoHoldToOpenOthers") = static_cast<int>(ImGuiDragDropFlags_SourceNoHoldToOpenOthers);
  m.attr("ImGuiDragDropFlags_SourceAllowNullID") = static_cast<int>(ImGuiDragDropFlags_SourceAllowNullID);
  m.attr("ImGuiDragDropFlags_SourceExtern") = static_cast<int>(ImGuiDragDropFlags_SourceExtern);
  m.attr("ImGuiDragDropFlags_SourceAutoExpirePayload") = static_cast<int>(ImGuiDragDropFlags_SourceAutoExpirePayload);
  m.attr("ImGuiDragDropFlags_AcceptBeforeDelivery") = static_cast<int>(ImGuiDragDropFlags_AcceptBeforeDelivery);
  m.attr("ImGuiDragDropFlags_AcceptNoDrawDefaultRect") = static_cast<int>(ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
  m.attr("ImGuiDragDropFlags_AcceptNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_AcceptNoPreviewTooltip);
  m.attr("ImGuiDragDropFlags_AcceptPeekOnly") = static_cast<int>(ImGuiDragDropFlags_AcceptPeekOnly);

  m.attr("ImGuiDataType_S8") = static_cast<int>(ImGuiDataType_S8);
  m.attr("ImGuiDataType_U8") = static_cast<int>(ImGuiDataType_U8);
  m.attr("ImGuiDataType_S16") = static_cast<int>(ImGuiDataType_S16);
  m.attr("ImGuiDataType_U16") = static_cast<int>(ImGuiDataType_U16);
  m.attr("ImGuiDataType_S32") = static_cast<int>(ImGuiDataType_S32);
  m.attr("ImGuiDataType_U32") = static_cast<int>(ImGuiDataType_U32);
  m.attr("ImGuiDataType_S64") = static_cast<int>(ImGuiDataType_S64);
  m.attr("ImGuiDataType_U64") = static_cast<int>(ImGuiDataType_U64);
  m.attr("ImGuiDataType_Float") = static_cast<int>(ImGuiDataType_Float);
  m.attr("ImGuiDataType_Double") = static_cast<int>(ImGuiDataType_Double);
  m.attr("ImGuiDataType_COUNT") = static_cast<int>(ImGuiDataType_COUNT);

  nb::enum_<ImGuiConfigFlags_>(m, "ImGuiConfigFlags")
    .value("ImGuiConfigFlags_None", ImGuiConfigFlags_None)
    .value("ImGuiConfigFlags_NavEnableKeyboard", ImGuiConfigFlags_NavEnableKeyboard)
    .value("ImGuiConfigFlags_NavEnableGamepad", ImGuiConfigFlags_NavEnableGamepad)
    .value("ImGuiConfigFlags_NavEnableSetMousePos", ImGuiConfigFlags_NavEnableSetMousePos)
    .value("ImGuiConfigFlags_NavNoCaptureKeyboard", ImGuiConfigFlags_NavNoCaptureKeyboard)
    .value("ImGuiConfigFlags_NoMouse", ImGuiConfigFlags_NoMouse)
    .value("ImGuiConfigFlags_NoMouseCursorChange", ImGuiConfigFlags_NoMouseCursorChange)
    .value("ImGuiConfigFlags_IsSRGB", ImGuiConfigFlags_IsSRGB)
    .value("ImGuiConfigFlags_IsTouchScreen", ImGuiConfigFlags_IsTouchScreen)
  ;
  m.attr("ImGuiConfigFlags_None") = static_cast<int>(ImGuiConfigFlags_None);
  m.attr("ImGuiConfigFlags_NavEnableKeyboard") = static_cast<int>(ImGuiConfigFlags_NavEnableKeyboard);
  m.attr("ImGuiConfigFlags_NavEnableGamepad") = static_cast<int>(ImGuiConfigFlags_NavEnableGamepad);
  m.attr("ImGuiConfigFlags_NavEnableSetMousePos") = static_cast<int>(ImGuiConfigFlags_NavEnableSetMousePos);
  m.attr("ImGuiConfigFlags_NavNoCaptureKeyboard") = static_cast<int>(ImGuiConfigFlags_NavNoCaptureKeyboard);
  m.attr("ImGuiConfigFlags_NoMouse") = static_cast<int>(ImGuiConfigFlags_NoMouse);
  m.attr("ImGuiConfigFlags_NoMouseCursorChange") = static_cast<int>(ImGuiConfigFlags_NoMouseCursorChange);
  m.attr("ImGuiConfigFlags_IsSRGB") = static_cast<int>(ImGuiConfigFlags_IsSRGB);
  m.attr("ImGuiConfigFlags_IsTouchScreen") = static_cast<int>(ImGuiConfigFlags_IsTouchScreen);

  nb::enum_<ImGuiBackendFlags_>(m, "ImGuiBackendFlags")
    .value("ImGuiBackendFlags_None", ImGuiBackendFlags_None)
    .value("ImGuiBackendFlags_HasGamepad", ImGuiBackendFlags_HasGamepad)
    .value("ImGuiBackendFlags_HasMouseCursors", ImGuiBackendFlags_HasMouseCursors)
    .value("ImGuiBackendFlags_HasSetMousePos", ImGuiBackendFlags_HasSetMousePos)
    .value("ImGuiBackendFlags_RendererHasVtxOffset", ImGuiBackendFlags_RendererHasVtxOffset)
  ;
  m.attr("ImGuiBackendFlags_None") = static_cast<int>(ImGuiBackendFlags_None);
  m.attr("ImGuiBackendFlags_HasGamepad") = static_cast<int>(ImGuiBackendFlags_HasGamepad);
  m.attr("ImGuiBackendFlags_HasMouseCursors") = static_cast<int>(ImGuiBackendFlags_HasMouseCursors);
  m.attr("ImGuiBackendFlags_HasSetMousePos") = static_cast<int>(ImGuiBackendFlags_HasSetMousePos);
  m.attr("ImGuiBackendFlags_RendererHasVtxOffset") = static_cast<int>(ImGuiBackendFlags_RendererHasVtxOffset);

  nb::enum_<ImGuiCol_>(m, "ImGuiCol")
    .value("ImGuiCol_Text", ImGuiCol_Text)
    .value("ImGuiCol_TextDisabled", ImGuiCol_TextDisabled)
    .value("ImGuiCol_WindowBg", ImGuiCol_WindowBg)
    .value("ImGuiCol_ChildBg", ImGuiCol_ChildBg)
    .value("ImGuiCol_PopupBg", ImGuiCol_PopupBg)
    .value("ImGuiCol_Border", ImGuiCol_Border)
    .value("ImGuiCol_BorderShadow", ImGuiCol_BorderShadow)
    .value("ImGuiCol_FrameBg", ImGuiCol_FrameBg)
    .value("ImGuiCol_FrameBgHovered", ImGuiCol_FrameBgHovered)
    .value("ImGuiCol_FrameBgActive", ImGuiCol_FrameBgActive)
    .value("ImGuiCol_TitleBg", ImGuiCol_TitleBg)
    .value("ImGuiCol_TitleBgActive", ImGuiCol_TitleBgActive)
    .value("ImGuiCol_TitleBgCollapsed", ImGuiCol_TitleBgCollapsed)
    .value("ImGuiCol_MenuBarBg", ImGuiCol_MenuBarBg)
    .value("ImGuiCol_ScrollbarBg", ImGuiCol_ScrollbarBg)
    .value("ImGuiCol_ScrollbarGrab", ImGuiCol_ScrollbarGrab)
    .value("ImGuiCol_ScrollbarGrabHovered", ImGuiCol_ScrollbarGrabHovered)
    .value("ImGuiCol_ScrollbarGrabActive", ImGuiCol_ScrollbarGrabActive)
    .value("ImGuiCol_CheckMark", ImGuiCol_CheckMark)
    .value("ImGuiCol_SliderGrab", ImGuiCol_SliderGrab)
    .value("ImGuiCol_SliderGrabActive", ImGuiCol_SliderGrabActive)
    .value("ImGuiCol_Button", ImGuiCol_Button)
    .value("ImGuiCol_ButtonHovered", ImGuiCol_ButtonHovered)
    .value("ImGuiCol_ButtonActive", ImGuiCol_ButtonActive)
    .value("ImGuiCol_Header", ImGuiCol_Header)
    .value("ImGuiCol_HeaderHovered", ImGuiCol_HeaderHovered)
    .value("ImGuiCol_HeaderActive", ImGuiCol_HeaderActive)
    .value("ImGuiCol_Separator", ImGuiCol_Separator)
    .value("ImGuiCol_SeparatorHovered", ImGuiCol_SeparatorHovered)
    .value("ImGuiCol_SeparatorActive", ImGuiCol_SeparatorActive)
    .value("ImGuiCol_ResizeGrip", ImGuiCol_ResizeGrip)
    .value("ImGuiCol_ResizeGripHovered", ImGuiCol_ResizeGripHovered)
    .value("ImGuiCol_ResizeGripActive", ImGuiCol_ResizeGripActive)
    .value("ImGuiCol_TabHovered", ImGuiCol_TabHovered)
    .value("ImGuiCol_Tab", ImGuiCol_Tab)
    .value("ImGuiCol_TabSelected", ImGuiCol_TabSelected)
    .value("ImGuiCol_TabSelectedOverline", ImGuiCol_TabSelectedOverline)
    .value("ImGuiCol_TabDimmed", ImGuiCol_TabDimmed)
    .value("ImGuiCol_TabDimmedSelected", ImGuiCol_TabDimmedSelected)
    .value("ImGuiCol_TabDimmedSelectedOverline", ImGuiCol_TabDimmedSelectedOverline)
    .value("ImGuiCol_TabUnfocused", ImGuiCol_TabUnfocused)
    .value("ImGuiCol_TabUnfocusedActive", ImGuiCol_TabUnfocusedActive)
    .value("ImGuiCol_PlotLines", ImGuiCol_PlotLines)
    .value("ImGuiCol_PlotLinesHovered", ImGuiCol_PlotLinesHovered)
    .value("ImGuiCol_PlotHistogram", ImGuiCol_PlotHistogram)
    .value("ImGuiCol_PlotHistogramHovered", ImGuiCol_PlotHistogramHovered)
    .value("ImGuiCol_TableHeaderBg", ImGuiCol_TableHeaderBg)
    .value("ImGuiCol_TableBorderStrong", ImGuiCol_TableBorderStrong)
    .value("ImGuiCol_TableBorderLight", ImGuiCol_TableBorderLight)
    .value("ImGuiCol_TableRowBg", ImGuiCol_TableRowBg)
    .value("ImGuiCol_TableRowBgAlt", ImGuiCol_TableRowBgAlt)
    .value("ImGuiCol_TextLink", ImGuiCol_TextLink)
    .value("ImGuiCol_TextSelectedBg", ImGuiCol_TextSelectedBg)
    .value("ImGuiCol_DragDropTarget", ImGuiCol_DragDropTarget)
    .value("ImGuiCol_NavCursor", ImGuiCol_NavCursor)
    .value("ImGuiCol_NavWindowingHighlight", ImGuiCol_NavWindowingHighlight)
    .value("ImGuiCol_NavWindowingDimBg", ImGuiCol_NavWindowingDimBg)
    .value("ImGuiCol_ModalWindowDimBg", ImGuiCol_ModalWindowDimBg)
    .value("ImGuiCol_COUNT", ImGuiCol_COUNT)
  ;
  m.attr("ImGuiCol_Text") = static_cast<int>(ImGuiCol_Text);
  m.attr("ImGuiCol_TextDisabled") = static_cast<int>(ImGuiCol_TextDisabled);
  m.attr("ImGuiCol_WindowBg") = static_cast<int>(ImGuiCol_WindowBg);
  m.attr("ImGuiCol_ChildBg") = static_cast<int>(ImGuiCol_ChildBg);
  m.attr("ImGuiCol_PopupBg") = static_cast<int>(ImGuiCol_PopupBg);
  m.attr("ImGuiCol_Border") = static_cast<int>(ImGuiCol_Border);
  m.attr("ImGuiCol_BorderShadow") = static_cast<int>(ImGuiCol_BorderShadow);
  m.attr("ImGuiCol_FrameBg") = static_cast<int>(ImGuiCol_FrameBg);
  m.attr("ImGuiCol_FrameBgHovered") = static_cast<int>(ImGuiCol_FrameBgHovered);
  m.attr("ImGuiCol_FrameBgActive") = static_cast<int>(ImGuiCol_FrameBgActive);
  m.attr("ImGuiCol_TitleBg") = static_cast<int>(ImGuiCol_TitleBg);
  m.attr("ImGuiCol_TitleBgActive") = static_cast<int>(ImGuiCol_TitleBgActive);
  m.attr("ImGuiCol_TitleBgCollapsed") = static_cast<int>(ImGuiCol_TitleBgCollapsed);
  m.attr("ImGuiCol_MenuBarBg") = static_cast<int>(ImGuiCol_MenuBarBg);
  m.attr("ImGuiCol_ScrollbarBg") = static_cast<int>(ImGuiCol_ScrollbarBg);
  m.attr("ImGuiCol_ScrollbarGrab") = static_cast<int>(ImGuiCol_ScrollbarGrab);
  m.attr("ImGuiCol_ScrollbarGrabHovered") = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
  m.attr("ImGuiCol_ScrollbarGrabActive") = static_cast<int>(ImGuiCol_ScrollbarGrabActive);
  m.attr("ImGuiCol_CheckMark") = static_cast<int>(ImGuiCol_CheckMark);
  m.attr("ImGuiCol_SliderGrab") = static_cast<int>(ImGuiCol_SliderGrab);
  m.attr("ImGuiCol_ScrollbarGrabHovered") = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
  m.attr("ImGuiCol_SliderGrabActive") = static_cast<int>(ImGuiCol_SliderGrabActive);
  m.attr("ImGuiCol_Button") = static_cast<int>(ImGuiCol_Button);
  m.attr("ImGuiCol_ButtonHovered") = static_cast<int>(ImGuiCol_ButtonHovered);
  m.attr("ImGuiCol_ButtonActive") = static_cast<int>(ImGuiCol_ButtonActive);
  m.attr("ImGuiCol_Header") = static_cast<int>(ImGuiCol_Header);
  m.attr("ImGuiCol_HeaderHovered") = static_cast<int>(ImGuiCol_HeaderHovered);
  m.attr("ImGuiCol_HeaderActive") = static_cast<int>(ImGuiCol_HeaderActive);
  m.attr("ImGuiCol_Separator") = static_cast<int>(ImGuiCol_Separator);
  m.attr("ImGuiCol_SeparatorHovered") = static_cast<int>(ImGuiCol_SeparatorHovered);
  m.attr("ImGuiCol_SeparatorActive") = static_cast<int>(ImGuiCol_SeparatorActive);
  m.attr("ImGuiCol_ResizeGrip") = static_cast<int>(ImGuiCol_ResizeGrip);
  m.attr("ImGuiCol_ResizeGripHovered") = static_cast<int>(ImGuiCol_ResizeGripHovered);
  m.attr("ImGuiCol_ResizeGripActive") = static_cast<int>(ImGuiCol_ResizeGripActive);
  m.attr("ImGuiCol_TabHovered") = static_cast<int>(ImGuiCol_TabHovered);
  m.attr("ImGuiCol_Tab") = static_cast<int>(ImGuiCol_Tab);
  m.attr("ImGuiCol_TabSelected") = static_cast<int>(ImGuiCol_TabSelected);
  m.attr("ImGuiCol_TabSelectedOverline") = static_cast<int>(ImGuiCol_TabSelectedOverline);
  m.attr("ImGuiCol_TabDimmed") = static_cast<int>(ImGuiCol_TabDimmed);
  m.attr("ImGuiCol_TabDimmedSelected") = static_cast<int>(ImGuiCol_TabDimmedSelected);
  m.attr("ImGuiCol_TabDimmedSelectedOverline") = static_cast<int>(ImGuiCol_TabDimmedSelectedOverline);
  m.attr("ImGuiCol_TabActive") = static_cast<int>(ImGuiCol_TabSelected);  // Deprecated
  m.attr("ImGuiCol_TabUnfocused") = static_cast<int>(ImGuiCol_TabUnfocused);
  m.attr("ImGuiCol_TabUnfocusedActive") = static_cast<int>(ImGuiCol_TabUnfocusedActive);
  m.attr("ImGuiCol_PlotLines") = static_cast<int>(ImGuiCol_PlotLines);
  m.attr("ImGuiCol_PlotLinesHovered") = static_cast<int>(ImGuiCol_PlotLinesHovered);
  m.attr("ImGuiCol_PlotHistogram") = static_cast<int>(ImGuiCol_PlotHistogram);
  m.attr("ImGuiCol_PlotHistogramHovered") = static_cast<int>(ImGuiCol_PlotHistogramHovered);
  m.attr("ImGuiCol_TableHeaderBg") = static_cast<int>(ImGuiCol_TableHeaderBg);
  m.attr("ImGuiCol_TableBorderStrong") = static_cast<int>(ImGuiCol_TableBorderStrong);
  m.attr("ImGuiCol_TableBorderLight") = static_cast<int>(ImGuiCol_TableBorderLight);
  m.attr("ImGuiCol_TableRowBg") = static_cast<int>(ImGuiCol_TableRowBg);
  m.attr("ImGuiCol_TableRowBgAlt") = static_cast<int>(ImGuiCol_TableRowBgAlt);
  m.attr("ImGuiCol_TextLink") = static_cast<int>(ImGuiCol_TextLink);
  m.attr("ImGuiCol_TextSelectedBg") = static_cast<int>(ImGuiCol_TextSelectedBg);
  m.attr("ImGuiCol_DragDropTarget") = static_cast<int>(ImGuiCol_DragDropTarget);
  m.attr("ImGuiCol_NavCursor") = static_cast<int>(ImGuiCol_NavCursor);
  m.attr("ImGuiCol_NavWindowingHighlight") = static_cast<int>(ImGuiCol_NavWindowingHighlight);
  m.attr("ImGuiCol_NavHighlight") = static_cast<int>(ImGuiCol_NavCursor);  // Deprecated
  m.attr("ImGuiCol_NavWindowingDimBg") = static_cast<int>(ImGuiCol_NavWindowingDimBg);
  m.attr("ImGuiCol_ModalWindowDimBg") = static_cast<int>(ImGuiCol_ModalWindowDimBg);
  m.attr("ImGuiCol_COUNT") = static_cast<int>(ImGuiCol_COUNT);


  nb::enum_<ImGuiStyleVar_>(m, "ImGuiStyleVar")
    .value("ImGuiStyleVar_Alpha", ImGuiStyleVar_Alpha)
    .value("ImGuiStyleVar_WindowPadding", ImGuiStyleVar_WindowPadding)
    .value("ImGuiStyleVar_WindowRounding", ImGuiStyleVar_WindowRounding)
    .value("ImGuiStyleVar_WindowBorderSize", ImGuiStyleVar_WindowBorderSize)
    .value("ImGuiStyleVar_WindowMinSize", ImGuiStyleVar_WindowMinSize)
    .value("ImGuiStyleVar_WindowTitleAlign", ImGuiStyleVar_WindowTitleAlign)
    .value("ImGuiStyleVar_ChildRounding", ImGuiStyleVar_ChildRounding)
    .value("ImGuiStyleVar_ChildBorderSize", ImGuiStyleVar_ChildBorderSize)
    .value("ImGuiStyleVar_PopupRounding", ImGuiStyleVar_PopupRounding)
    .value("ImGuiStyleVar_PopupBorderSize", ImGuiStyleVar_PopupBorderSize)
    .value("ImGuiStyleVar_FramePadding", ImGuiStyleVar_FramePadding)
    .value("ImGuiStyleVar_FrameRounding", ImGuiStyleVar_FrameRounding)
    .value("ImGuiStyleVar_FrameBorderSize", ImGuiStyleVar_FrameBorderSize)
    .value("ImGuiStyleVar_ItemSpacing", ImGuiStyleVar_ItemSpacing)
    .value("ImGuiStyleVar_ItemInnerSpacing", ImGuiStyleVar_ItemInnerSpacing)
    .value("ImGuiStyleVar_IndentSpacing", ImGuiStyleVar_IndentSpacing)
    .value("ImGuiStyleVar_ScrollbarSize", ImGuiStyleVar_ScrollbarSize)
    .value("ImGuiStyleVar_ScrollbarRounding", ImGuiStyleVar_ScrollbarRounding)
    .value("ImGuiStyleVar_GrabMinSize", ImGuiStyleVar_GrabMinSize)
    .value("ImGuiStyleVar_GrabRounding", ImGuiStyleVar_GrabRounding)
    .value("ImGuiStyleVar_TabRounding", ImGuiStyleVar_TabRounding)
    .value("ImGuiStyleVar_ButtonTextAlign", ImGuiStyleVar_ButtonTextAlign)
    .value("ImGuiStyleVar_SelectableTextAlign", ImGuiStyleVar_SelectableTextAlign)
    .value("ImGuiStyleVar_COUNT", ImGuiStyleVar_COUNT)
  ;
  m.attr("ImGuiStyleVar_Alpha") = static_cast<int>(ImGuiStyleVar_Alpha);
  m.attr("ImGuiStyleVar_WindowPadding") = static_cast<int>(ImGuiStyleVar_WindowPadding);
  m.attr("ImGuiStyleVar_WindowRounding") = static_cast<int>(ImGuiStyleVar_WindowRounding);
  m.attr("ImGuiStyleVar_WindowBorderSize") = static_cast<int>(ImGuiStyleVar_WindowBorderSize);
  m.attr("ImGuiStyleVar_WindowMinSize") = static_cast<int>(ImGuiStyleVar_WindowMinSize);
  m.attr("ImGuiStyleVar_WindowTitleAlign") = static_cast<int>(ImGuiStyleVar_WindowTitleAlign);
  m.attr("ImGuiStyleVar_ChildRounding") = static_cast<int>(ImGuiStyleVar_ChildRounding);
  m.attr("ImGuiStyleVar_ChildBorderSize") = static_cast<int>(ImGuiStyleVar_ChildBorderSize);
  m.attr("ImGuiStyleVar_PopupRounding") = static_cast<int>(ImGuiStyleVar_PopupRounding);
  m.attr("ImGuiStyleVar_PopupBorderSize") = static_cast<int>(ImGuiStyleVar_PopupBorderSize);
  m.attr("ImGuiStyleVar_FramePadding") = static_cast<int>(ImGuiStyleVar_FramePadding);
  m.attr("ImGuiStyleVar_FrameRounding") = static_cast<int>(ImGuiStyleVar_FrameRounding);
  m.attr("ImGuiStyleVar_FrameBorderSize") = static_cast<int>(ImGuiStyleVar_FrameBorderSize);
  m.attr("ImGuiStyleVar_ItemSpacing") = static_cast<int>(ImGuiStyleVar_ItemSpacing);
  m.attr("ImGuiStyleVar_ItemInnerSpacing") = static_cast<int>(ImGuiStyleVar_ItemInnerSpacing);
  m.attr("ImGuiStyleVar_IndentSpacing") = static_cast<int>(ImGuiStyleVar_IndentSpacing);
  m.attr("ImGuiStyleVar_ScrollbarSize") = static_cast<int>(ImGuiStyleVar_ScrollbarSize);
  m.attr("ImGuiStyleVar_ScrollbarRounding") = static_cast<int>(ImGuiStyleVar_ScrollbarRounding);
  m.attr("ImGuiStyleVar_GrabMinSize") = static_cast<int>(ImGuiStyleVar_GrabMinSize);
  m.attr("ImGuiStyleVar_GrabRounding") = static_cast<int>(ImGuiStyleVar_GrabRounding);
  m.attr("ImGuiStyleVar_TabRounding") = static_cast<int>(ImGuiStyleVar_TabRounding);
  m.attr("ImGuiStyleVar_ButtonTextAlign") = static_cast<int>(ImGuiStyleVar_ButtonTextAlign);
  m.attr("ImGuiStyleVar_SelectableTextAlign") = static_cast<int>(ImGuiStyleVar_SelectableTextAlign);
  m.attr("ImGuiStyleVar_COUNT") = static_cast<int>(ImGuiStyleVar_COUNT);


  nb::enum_<ImGuiColorEditFlags_>(m, "ImGuiColorEditFlags")
    .value("ImGuiColorEditFlags_None", ImGuiColorEditFlags_None)
    .value("ImGuiColorEditFlags_NoAlpha", ImGuiColorEditFlags_NoAlpha)
    .value("ImGuiColorEditFlags_NoPicker", ImGuiColorEditFlags_NoPicker)
    .value("ImGuiColorEditFlags_NoOptions", ImGuiColorEditFlags_NoOptions)
    .value("ImGuiColorEditFlags_NoSmallPreview", ImGuiColorEditFlags_NoSmallPreview)
    .value("ImGuiColorEditFlags_NoInputs", ImGuiColorEditFlags_NoInputs)
    .value("ImGuiColorEditFlags_NoTooltip", ImGuiColorEditFlags_NoTooltip)
    .value("ImGuiColorEditFlags_NoLabel", ImGuiColorEditFlags_NoLabel)
    .value("ImGuiColorEditFlags_NoSidePreview", ImGuiColorEditFlags_NoSidePreview)
    .value("ImGuiColorEditFlags_NoDragDrop", ImGuiColorEditFlags_NoDragDrop)
    .value("ImGuiColorEditFlags_NoBorder", ImGuiColorEditFlags_NoBorder)
    .value("ImGuiColorEditFlags_AlphaBar", ImGuiColorEditFlags_AlphaBar)
    .value("ImGuiColorEditFlags_AlphaPreview", ImGuiColorEditFlags_AlphaPreview)
    .value("ImGuiColorEditFlags_AlphaPreviewHalf", ImGuiColorEditFlags_AlphaPreviewHalf)
    .value("ImGuiColorEditFlags_HDR", ImGuiColorEditFlags_HDR)
    .value("ImGuiColorEditFlags_DisplayRGB", ImGuiColorEditFlags_DisplayRGB)
    .value("ImGuiColorEditFlags_DisplayHSV", ImGuiColorEditFlags_DisplayHSV)
    .value("ImGuiColorEditFlags_DisplayHex", ImGuiColorEditFlags_DisplayHex)
    .value("ImGuiColorEditFlags_Uint8", ImGuiColorEditFlags_Uint8)
    .value("ImGuiColorEditFlags_Float", ImGuiColorEditFlags_Float)
    .value("ImGuiColorEditFlags_PickerHueBar", ImGuiColorEditFlags_PickerHueBar)
    .value("ImGuiColorEditFlags_PickerHueWheel", ImGuiColorEditFlags_PickerHueWheel)
    .value("ImGuiColorEditFlags_InputRGB", ImGuiColorEditFlags_InputRGB)
    .value("ImGuiColorEditFlags_InputHSV", ImGuiColorEditFlags_InputHSV)
  ;
  m.attr("ImGuiColorEditFlags_None") = static_cast<int>(ImGuiColorEditFlags_None);
  m.attr("ImGuiColorEditFlags_NoAlpha") = static_cast<int>(ImGuiColorEditFlags_NoAlpha);
  m.attr("ImGuiColorEditFlags_NoPicker") = static_cast<int>(ImGuiColorEditFlags_NoPicker);
  m.attr("ImGuiColorEditFlags_NoOptions") = static_cast<int>(ImGuiColorEditFlags_NoOptions);
  m.attr("ImGuiColorEditFlags_NoSmallPreview") = static_cast<int>(ImGuiColorEditFlags_NoSmallPreview);
  m.attr("ImGuiColorEditFlags_NoInputs") = static_cast<int>(ImGuiColorEditFlags_NoInputs);
  m.attr("ImGuiColorEditFlags_NoTooltip") = static_cast<int>(ImGuiColorEditFlags_NoTooltip);
  m.attr("ImGuiColorEditFlags_NoLabel") = static_cast<int>(ImGuiColorEditFlags_NoLabel);
  m.attr("ImGuiColorEditFlags_NoSidePreview") = static_cast<int>(ImGuiColorEditFlags_NoSidePreview);
  m.attr("ImGuiColorEditFlags_NoDragDrop") = static_cast<int>(ImGuiColorEditFlags_NoDragDrop);
  m.attr("ImGuiColorEditFlags_NoBorder") = static_cast<int>(ImGuiColorEditFlags_NoBorder);
  m.attr("ImGuiColorEditFlags_AlphaBar") = static_cast<int>(ImGuiColorEditFlags_AlphaBar);
  m.attr("ImGuiColorEditFlags_AlphaPreview") = static_cast<int>(ImGuiColorEditFlags_AlphaPreview);
  m.attr("ImGuiColorEditFlags_AlphaPreviewHalf") = static_cast<int>(ImGuiColorEditFlags_AlphaPreviewHalf);
  m.attr("ImGuiColorEditFlags_HDR") = static_cast<int>(ImGuiColorEditFlags_HDR);
  m.attr("ImGuiColorEditFlags_DisplayRGB") = static_cast<int>(ImGuiColorEditFlags_DisplayRGB);
  m.attr("ImGuiColorEditFlags_DisplayHSV") = static_cast<int>(ImGuiColorEditFlags_DisplayHSV);
  m.attr("ImGuiColorEditFlags_DisplayHex") = static_cast<int>(ImGuiColorEditFlags_DisplayHex);
  m.attr("ImGuiColorEditFlags_Uint8") = static_cast<int>(ImGuiColorEditFlags_Uint8);
  m.attr("ImGuiColorEditFlags_Float") = static_cast<int>(ImGuiColorEditFlags_Float);
  m.attr("ImGuiColorEditFlags_PickerHueBar") = static_cast<int>(ImGuiColorEditFlags_PickerHueBar);
  m.attr("ImGuiColorEditFlags_PickerHueWheel") = static_cast<int>(ImGuiColorEditFlags_PickerHueWheel);
  m.attr("ImGuiColorEditFlags_InputRGB") = static_cast<int>(ImGuiColorEditFlags_InputRGB);
  m.attr("ImGuiColorEditFlags_InputHSV") = static_cast<int>(ImGuiColorEditFlags_InputHSV);


  nb::enum_<ImGuiMouseButton_>(m, "ImGuiMouseButton")
    .value("ImGuiMouseButton_Left", ImGuiMouseButton_Left)
    .value("ImGuiMouseButton_Right", ImGuiMouseButton_Right)
    .value("ImGuiMouseButton_Middle", ImGuiMouseButton_Middle)
    .value("ImGuiMouseButton_COUNT", ImGuiMouseButton_COUNT)
  ;
  m.attr("ImGuiMouseButton_Left") = static_cast<int>(ImGuiMouseButton_Left);
  m.attr("ImGuiMouseButton_Right") = static_cast<int>(ImGuiMouseButton_Right);
  m.attr("ImGuiMouseButton_Middle") = static_cast<int>(ImGuiMouseButton_Middle);
  m.attr("ImGuiMouseButton_COUNT") = static_cast<int>(ImGuiMouseButton_COUNT);


  nb::enum_<ImGuiMouseCursor_>(m, "ImGuiMouseCursor")
    .value("ImGuiMouseCursor_None", ImGuiMouseCursor_None)
    .value("ImGuiMouseCursor_Arrow", ImGuiMouseCursor_Arrow)
    .value("ImGuiMouseCursor_TextInput", ImGuiMouseCursor_TextInput)
    .value("ImGuiMouseCursor_ResizeAll", ImGuiMouseCursor_ResizeAll)
    .value("ImGuiMouseCursor_ResizeNS", ImGuiMouseCursor_ResizeNS)
    .value("ImGuiMouseCursor_ResizeEW", ImGuiMouseCursor_ResizeEW)
    .value("ImGuiMouseCursor_ResizeNESW", ImGuiMouseCursor_ResizeNESW)
    .value("ImGuiMouseCursor_ResizeNWSE", ImGuiMouseCursor_ResizeNWSE)
    .value("ImGuiMouseCursor_Hand", ImGuiMouseCursor_Hand)
    .value("ImGuiMouseCursor_NotAllowed", ImGuiMouseCursor_NotAllowed)
    .value("ImGuiMouseCursor_COUNT", ImGuiMouseCursor_COUNT)
  ;
  m.attr("ImGuiMouseCursor_None") = static_cast<int>(ImGuiMouseCursor_None);
  m.attr("ImGuiMouseCursor_Arrow") = static_cast<int>(ImGuiMouseCursor_Arrow);
  m.attr("ImGuiMouseCursor_TextInput") = static_cast<int>(ImGuiMouseCursor_TextInput);
  m.attr("ImGuiMouseCursor_ResizeAll") = static_cast<int>(ImGuiMouseCursor_ResizeAll);
  m.attr("ImGuiMouseCursor_ResizeNS") = static_cast<int>(ImGuiMouseCursor_ResizeNS);
  m.attr("ImGuiMouseCursor_ResizeEW") = static_cast<int>(ImGuiMouseCursor_ResizeEW);
  m.attr("ImGuiMouseCursor_ResizeNESW") = static_cast<int>(ImGuiMouseCursor_ResizeNESW);
  m.attr("ImGuiMouseCursor_ResizeNWSE") = static_cast<int>(ImGuiMouseCursor_ResizeNWSE);
  m.attr("ImGuiMouseCursor_Hand") = static_cast<int>(ImGuiMouseCursor_Hand);
  m.attr("ImGuiMouseCursor_NotAllowed") = static_cast<int>(ImGuiMouseCursor_NotAllowed);
  m.attr("ImGuiMouseCursor_COUNT") = static_cast<int>(ImGuiMouseCursor_COUNT);

  { // ImGuiCond ImGuiCond_
    auto e = nb::enum_<ImGuiCond_>(m, "ImGuiCond");
        e.value("ImGuiCond_Always",         ImGuiCond_Always);          m.attr("ImGuiCond_Always")          = ImGuiCond_::ImGuiCond_Always;
        e.value("ImGuiCond_Once",           ImGuiCond_Once);            m.attr("ImGuiCond_Once")            = ImGuiCond_::ImGuiCond_Once;
        e.value("ImGuiCond_FirstUseEver",   ImGuiCond_FirstUseEver);    m.attr("ImGuiCond_FirstUseEver")    = ImGuiCond_::ImGuiCond_FirstUseEver;
        e.value("ImGuiCond_Appearing",      ImGuiCond_Appearing);       m.attr("ImGuiCond_Appearing")       = ImGuiCond_::ImGuiCond_Appearing;
    ;
  }


  nb::enum_<ImDrawFlags_>(m, "ImDrawFlags")
    .value("ImDrawFlags_None", ImDrawFlags_None)
    .value("ImDrawFlags_Closed", ImDrawFlags_Closed)
    .value("ImDrawFlags_RoundCornersTopLeft", ImDrawFlags_RoundCornersTopLeft)
    .value("ImDrawFlags_RoundCornersTopRight", ImDrawFlags_RoundCornersTopRight)
    .value("ImDrawFlags_RoundCornersBottomLeft", ImDrawFlags_RoundCornersBottomLeft)
    .value("ImDrawFlags_RoundCornersBottomRight", ImDrawFlags_RoundCornersBottomRight)
    .value("ImDrawFlags_RoundCornersNone", ImDrawFlags_RoundCornersNone)
    .value("ImDrawFlags_RoundCornersTop", ImDrawFlags_RoundCornersTop)
    .value("ImDrawFlags_RoundCornersBottom", ImDrawFlags_RoundCornersBottom)
    .value("ImDrawFlags_RoundCornersLeft", ImDrawFlags_RoundCornersLeft)
    .value("ImDrawFlags_RoundCornersRight", ImDrawFlags_RoundCornersRight)
    .value("ImDrawFlags_RoundCornersAll", ImDrawFlags_RoundCornersAll)
  ;
  m.attr("ImDrawFlags_None") = static_cast<int>(ImDrawFlags_None);
  m.attr("ImDrawFlags_Closed") = static_cast<int>(ImDrawFlags_Closed);
  m.attr("ImDrawFlags_RoundCornersTopLeft") = static_cast<int>(ImDrawFlags_RoundCornersTopLeft);
  m.attr("ImDrawFlags_RoundCornersTopRight") = static_cast<int>(ImDrawFlags_RoundCornersTopRight);
  m.attr("ImDrawFlags_RoundCornersBottomLeft") = static_cast<int>(ImDrawFlags_RoundCornersBottomLeft);
  m.attr("ImDrawFlags_RoundCornersBottomRight") = static_cast<int>(ImDrawFlags_RoundCornersBottomRight);
  m.attr("ImDrawFlags_RoundCornersNone") = static_cast<int>(ImDrawFlags_RoundCornersNone);
  m.attr("ImDrawFlags_RoundCornersTop") = static_cast<int>(ImDrawFlags_RoundCornersTop);
  m.attr("ImDrawFlags_RoundCornersBottom") = static_cast<int>(ImDrawFlags_RoundCornersBottom);
  m.attr("ImDrawFlags_RoundCornersLeft") = static_cast<int>(ImDrawFlags_RoundCornersLeft);
  m.attr("ImDrawFlags_RoundCornersRight") = static_cast<int>(ImDrawFlags_RoundCornersRight);
  m.attr("ImDrawFlags_RoundCornersAll") = static_cast<int>(ImDrawFlags_RoundCornersAll);

  nb::enum_<ImGuiKey>(m, "ImGuiKey")
    .value("ImGuiKey_None", ImGuiKey::ImGuiKey_None)
    .value("ImGuiKey_Tab", ImGuiKey::ImGuiKey_Tab)
    .value("ImGuiKey_LeftArrow", ImGuiKey::ImGuiKey_LeftArrow)
    .value("ImGuiKey_RightArrow", ImGuiKey::ImGuiKey_RightArrow)
    .value("ImGuiKey_UpArrow", ImGuiKey::ImGuiKey_UpArrow)
    .value("ImGuiKey_DownArrow", ImGuiKey::ImGuiKey_DownArrow)
    .value("ImGuiKey_PageUp", ImGuiKey::ImGuiKey_PageUp)
    .value("ImGuiKey_PageDown", ImGuiKey::ImGuiKey_PageDown)
    .value("ImGuiKey_Home", ImGuiKey::ImGuiKey_Home)
    .value("ImGuiKey_End", ImGuiKey::ImGuiKey_End)
    .value("ImGuiKey_Insert", ImGuiKey::ImGuiKey_Insert)
    .value("ImGuiKey_Delete", ImGuiKey::ImGuiKey_Delete)
    .value("ImGuiKey_Backspace", ImGuiKey::ImGuiKey_Backspace)
    .value("ImGuiKey_Space", ImGuiKey::ImGuiKey_Space)
    .value("ImGuiKey_Enter", ImGuiKey::ImGuiKey_Enter)
    .value("ImGuiKey_Escape", ImGuiKey::ImGuiKey_Escape)
    .value("ImGuiKey_LeftCtrl", ImGuiKey::ImGuiKey_LeftCtrl)
    .value("ImGuiKey_LeftShift", ImGuiKey::ImGuiKey_LeftShift)
    .value("ImGuiKey_LeftAlt", ImGuiKey::ImGuiKey_LeftAlt)
    .value("ImGuiKey_LeftSuper", ImGuiKey::ImGuiKey_LeftSuper)
    .value("ImGuiKey_RightCtrl", ImGuiKey::ImGuiKey_RightCtrl)
    .value("ImGuiKey_RightShift", ImGuiKey::ImGuiKey_RightShift)
    .value("ImGuiKey_RightAlt", ImGuiKey::ImGuiKey_RightAlt)
    .value("ImGuiKey_RightSuper", ImGuiKey::ImGuiKey_RightSuper)
    .value("ImGuiKey_Menu", ImGuiKey::ImGuiKey_Menu)
    .value("ImGuiKey_0", ImGuiKey::ImGuiKey_0)
    .value("ImGuiKey_1", ImGuiKey::ImGuiKey_1)
    .value("ImGuiKey_2", ImGuiKey::ImGuiKey_2)
    .value("ImGuiKey_3", ImGuiKey::ImGuiKey_3)
    .value("ImGuiKey_4", ImGuiKey::ImGuiKey_4)
    .value("ImGuiKey_5", ImGuiKey::ImGuiKey_5)
    .value("ImGuiKey_6", ImGuiKey::ImGuiKey_6)
    .value("ImGuiKey_7", ImGuiKey::ImGuiKey_7)
    .value("ImGuiKey_8", ImGuiKey::ImGuiKey_8)
    .value("ImGuiKey_9", ImGuiKey::ImGuiKey_9)
    .value("ImGuiKey_A", ImGuiKey::ImGuiKey_A)
    .value("ImGuiKey_B", ImGuiKey::ImGuiKey_B)
    .value("ImGuiKey_C", ImGuiKey::ImGuiKey_C)
    .value("ImGuiKey_D", ImGuiKey::ImGuiKey_D)
    .value("ImGuiKey_E", ImGuiKey::ImGuiKey_E)
    .value("ImGuiKey_F", ImGuiKey::ImGuiKey_F)
    .value("ImGuiKey_G", ImGuiKey::ImGuiKey_G)
    .value("ImGuiKey_H", ImGuiKey::ImGuiKey_H)
    .value("ImGuiKey_I", ImGuiKey::ImGuiKey_I)
    .value("ImGuiKey_J", ImGuiKey::ImGuiKey_J)
    .value("ImGuiKey_K", ImGuiKey::ImGuiKey_K)
    .value("ImGuiKey_L", ImGuiKey::ImGuiKey_L)
    .value("ImGuiKey_M", ImGuiKey::ImGuiKey_M)
    .value("ImGuiKey_N", ImGuiKey::ImGuiKey_N)
    .value("ImGuiKey_O", ImGuiKey::ImGuiKey_O)
    .value("ImGuiKey_P", ImGuiKey::ImGuiKey_P)
    .value("ImGuiKey_Q", ImGuiKey::ImGuiKey_Q)
    .value("ImGuiKey_R", ImGuiKey::ImGuiKey_R)
    .value("ImGuiKey_S", ImGuiKey::ImGuiKey_S)
    .value("ImGuiKey_T", ImGuiKey::ImGuiKey_T)
    .value("ImGuiKey_U", ImGuiKey::ImGuiKey_U)
    .value("ImGuiKey_V", ImGuiKey::ImGuiKey_V)
    .value("ImGuiKey_W", ImGuiKey::ImGuiKey_W)
    .value("ImGuiKey_X", ImGuiKey::ImGuiKey_X)
    .value("ImGuiKey_Y", ImGuiKey::ImGuiKey_Y)
    .value("ImGuiKey_Z", ImGuiKey::ImGuiKey_Z)
    .value("ImGuiKey_F1", ImGuiKey::ImGuiKey_F1)
    .value("ImGuiKey_F2", ImGuiKey::ImGuiKey_F2)
    .value("ImGuiKey_F3", ImGuiKey::ImGuiKey_F3)
    .value("ImGuiKey_F4", ImGuiKey::ImGuiKey_F4)
    .value("ImGuiKey_F5", ImGuiKey::ImGuiKey_F5)
    .value("ImGuiKey_F6", ImGuiKey::ImGuiKey_F6)
    .value("ImGuiKey_F7", ImGuiKey::ImGuiKey_F7)
    .value("ImGuiKey_F8", ImGuiKey::ImGuiKey_F8)
    .value("ImGuiKey_F9", ImGuiKey::ImGuiKey_F9)
    .value("ImGuiKey_F10", ImGuiKey::ImGuiKey_F10)
    .value("ImGuiKey_F11", ImGuiKey::ImGuiKey_F11)
    .value("ImGuiKey_F12", ImGuiKey::ImGuiKey_F12)
    .value("ImGuiKey_F13", ImGuiKey::ImGuiKey_F13)
    .value("ImGuiKey_F14", ImGuiKey::ImGuiKey_F14)
    .value("ImGuiKey_F15", ImGuiKey::ImGuiKey_F15)
    .value("ImGuiKey_F16", ImGuiKey::ImGuiKey_F16)
    .value("ImGuiKey_F17", ImGuiKey::ImGuiKey_F17)
    .value("ImGuiKey_F18", ImGuiKey::ImGuiKey_F18)
    .value("ImGuiKey_F19", ImGuiKey::ImGuiKey_F19)
    .value("ImGuiKey_F20", ImGuiKey::ImGuiKey_F20)
    .value("ImGuiKey_F21", ImGuiKey::ImGuiKey_F21)
    .value("ImGuiKey_F22", ImGuiKey::ImGuiKey_F22)
    .value("ImGuiKey_F23", ImGuiKey::ImGuiKey_F23)
    .value("ImGuiKey_F24", ImGuiKey::ImGuiKey_F24)
    .value("ImGuiKey_Apostrophe", ImGuiKey::ImGuiKey_Apostrophe)
    .value("ImGuiKey_Comma", ImGuiKey::ImGuiKey_Comma)
    .value("ImGuiKey_Minus", ImGuiKey::ImGuiKey_Minus)
    .value("ImGuiKey_Period", ImGuiKey::ImGuiKey_Period)
    .value("ImGuiKey_Slash", ImGuiKey::ImGuiKey_Slash)
    .value("ImGuiKey_Semicolon", ImGuiKey::ImGuiKey_Semicolon)
    .value("ImGuiKey_Equal", ImGuiKey::ImGuiKey_Equal)
    .value("ImGuiKey_LeftBracket", ImGuiKey::ImGuiKey_LeftBracket)
    .value("ImGuiKey_Backslash", ImGuiKey::ImGuiKey_Backslash)
    .value("ImGuiKey_RightBracket", ImGuiKey::ImGuiKey_RightBracket)
    .value("ImGuiKey_GraveAccent", ImGuiKey::ImGuiKey_GraveAccent)
    .value("ImGuiKey_CapsLock", ImGuiKey::ImGuiKey_CapsLock)
    .value("ImGuiKey_ScrollLock", ImGuiKey::ImGuiKey_ScrollLock)
    .value("ImGuiKey_NumLock", ImGuiKey::ImGuiKey_NumLock)
    .value("ImGuiKey_PrintScreen", ImGuiKey::ImGuiKey_PrintScreen)
    .value("ImGuiKey_Pause", ImGuiKey::ImGuiKey_Pause)
    .value("ImGuiKey_Keypad0", ImGuiKey::ImGuiKey_Keypad0)
    .value("ImGuiKey_Keypad1", ImGuiKey::ImGuiKey_Keypad1)
    .value("ImGuiKey_Keypad2", ImGuiKey::ImGuiKey_Keypad2)
    .value("ImGuiKey_Keypad3", ImGuiKey::ImGuiKey_Keypad3)
    .value("ImGuiKey_Keypad4", ImGuiKey::ImGuiKey_Keypad4)
    .value("ImGuiKey_Keypad5", ImGuiKey::ImGuiKey_Keypad5)
    .value("ImGuiKey_Keypad6", ImGuiKey::ImGuiKey_Keypad6)
    .value("ImGuiKey_Keypad7", ImGuiKey::ImGuiKey_Keypad7)
    .value("ImGuiKey_Keypad8", ImGuiKey::ImGuiKey_Keypad8)
    .value("ImGuiKey_Keypad9", ImGuiKey::ImGuiKey_Keypad9)
    .value("ImGuiKey_KeypadDecimal", ImGuiKey::ImGuiKey_KeypadDecimal)
    .value("ImGuiKey_KeypadDivide", ImGuiKey::ImGuiKey_KeypadDivide)
    .value("ImGuiKey_KeypadMultiply", ImGuiKey::ImGuiKey_KeypadMultiply)
    .value("ImGuiKey_KeypadSubtract", ImGuiKey::ImGuiKey_KeypadSubtract)
    .value("ImGuiKey_KeypadAdd", ImGuiKey::ImGuiKey_KeypadAdd)
    .value("ImGuiKey_KeypadEnter", ImGuiKey::ImGuiKey_KeypadEnter)
    .value("ImGuiKey_KeypadEqual", ImGuiKey::ImGuiKey_KeypadEqual)
    .value("ImGuiKey_AppBack", ImGuiKey::ImGuiKey_AppBack)
    .value("ImGuiKey_AppForward", ImGuiKey::ImGuiKey_AppForward)
    .value("ImGuiKey_GamepadStart", ImGuiKey::ImGuiKey_GamepadStart)
    .value("ImGuiKey_GamepadBack", ImGuiKey::ImGuiKey_GamepadBack)
    .value("ImGuiKey_GamepadFaceUp", ImGuiKey::ImGuiKey_GamepadFaceUp)
    .value("ImGuiKey_GamepadFaceDown", ImGuiKey::ImGuiKey_GamepadFaceDown)
    .value("ImGuiKey_GamepadFaceLeft", ImGuiKey::ImGuiKey_GamepadFaceLeft)
    .value("ImGuiKey_GamepadFaceRight", ImGuiKey::ImGuiKey_GamepadFaceRight)
    .value("ImGuiKey_GamepadDpadUp", ImGuiKey::ImGuiKey_GamepadDpadUp)
    .value("ImGuiKey_GamepadDpadDown", ImGuiKey::ImGuiKey_GamepadDpadDown)
    .value("ImGuiKey_GamepadDpadLeft", ImGuiKey::ImGuiKey_GamepadDpadLeft)
    .value("ImGuiKey_GamepadDpadRight", ImGuiKey::ImGuiKey_GamepadDpadRight)
    .value("ImGuiKey_GamepadL1", ImGuiKey::ImGuiKey_GamepadL1)
    .value("ImGuiKey_GamepadR1", ImGuiKey::ImGuiKey_GamepadR1)
    .value("ImGuiKey_GamepadL2", ImGuiKey::ImGuiKey_GamepadL2)
    .value("ImGuiKey_GamepadR2", ImGuiKey::ImGuiKey_GamepadR2)
    .value("ImGuiKey_GamepadL3", ImGuiKey::ImGuiKey_GamepadL3)
    .value("ImGuiKey_GamepadR3", ImGuiKey::ImGuiKey_GamepadR3)
    .value("ImGuiKey_GamepadLStickUp", ImGuiKey::ImGuiKey_GamepadLStickUp)
    .value("ImGuiKey_GamepadLStickDown", ImGuiKey::ImGuiKey_GamepadLStickDown)
    .value("ImGuiKey_GamepadLStickLeft", ImGuiKey::ImGuiKey_GamepadLStickLeft)
    .value("ImGuiKey_GamepadLStickRight", ImGuiKey::ImGuiKey_GamepadLStickRight)
    .value("ImGuiKey_GamepadRStickUp", ImGuiKey::ImGuiKey_GamepadRStickUp)
    .value("ImGuiKey_GamepadRStickDown", ImGuiKey::ImGuiKey_GamepadRStickDown)
    .value("ImGuiKey_GamepadRStickLeft", ImGuiKey::ImGuiKey_GamepadRStickLeft)
    .value("ImGuiKey_GamepadRStickRight", ImGuiKey::ImGuiKey_GamepadRStickRight)
    .value("ImGuiKey_ModCtrl", ImGuiKey::ImGuiKey_ModCtrl)
    .value("ImGuiKey_ModShift", ImGuiKey::ImGuiKey_ModShift)
    .value("ImGuiKey_ModAlt", ImGuiKey::ImGuiKey_ModAlt)
    .value("ImGuiKey_ModSuper", ImGuiKey::ImGuiKey_ModSuper)
    .value("ImGuiMod_None", ImGuiKey::ImGuiMod_None)
    .value("ImGuiMod_Ctrl", ImGuiKey::ImGuiMod_Ctrl)
    .value("ImGuiMod_Shift", ImGuiKey::ImGuiMod_Shift)
    .value("ImGuiMod_Alt", ImGuiKey::ImGuiMod_Alt)
    .value("ImGuiMod_Super", ImGuiKey::ImGuiMod_Super)
    .value("ImGuiMod_Mask_", ImGuiKey::ImGuiMod_Mask_)
  ;
  m.attr("ImGuiKey_None") = ImGuiKey::ImGuiKey_None;
  m.attr("ImGuiKey_Tab") = ImGuiKey::ImGuiKey_Tab;
  m.attr("ImGuiKey_LeftArrow") = ImGuiKey::ImGuiKey_LeftArrow;
  m.attr("ImGuiKey_RightArrow") = ImGuiKey::ImGuiKey_RightArrow;
  m.attr("ImGuiKey_UpArrow") = ImGuiKey::ImGuiKey_UpArrow;
  m.attr("ImGuiKey_DownArrow") = ImGuiKey::ImGuiKey_DownArrow;
  m.attr("ImGuiKey_PageUp") = ImGuiKey::ImGuiKey_PageUp;
  m.attr("ImGuiKey_PageDown") = ImGuiKey::ImGuiKey_PageDown;
  m.attr("ImGuiKey_Home") = ImGuiKey::ImGuiKey_Home;
  m.attr("ImGuiKey_End") = ImGuiKey::ImGuiKey_End;
  m.attr("ImGuiKey_Insert") = ImGuiKey::ImGuiKey_Insert;
  m.attr("ImGuiKey_Delete") = ImGuiKey::ImGuiKey_Delete;
  m.attr("ImGuiKey_Backspace") = ImGuiKey::ImGuiKey_Backspace;
  m.attr("ImGuiKey_Space") = ImGuiKey::ImGuiKey_Space;
  m.attr("ImGuiKey_Enter") = ImGuiKey::ImGuiKey_Enter;
  m.attr("ImGuiKey_Escape") = ImGuiKey::ImGuiKey_Escape;
  m.attr("ImGuiKey_LeftCtrl") = ImGuiKey::ImGuiKey_LeftCtrl;
  m.attr("ImGuiKey_LeftShift") = ImGuiKey::ImGuiKey_LeftShift;
  m.attr("ImGuiKey_LeftAlt") = ImGuiKey::ImGuiKey_LeftAlt;
  m.attr("ImGuiKey_LeftSuper") = ImGuiKey::ImGuiKey_LeftSuper;
  m.attr("ImGuiKey_RightCtrl") = ImGuiKey::ImGuiKey_RightCtrl;
  m.attr("ImGuiKey_RightShift") = ImGuiKey::ImGuiKey_RightShift;
  m.attr("ImGuiKey_RightAlt") = ImGuiKey::ImGuiKey_RightAlt;
  m.attr("ImGuiKey_RightSuper") = ImGuiKey::ImGuiKey_RightSuper;
  m.attr("ImGuiKey_Menu") = ImGuiKey::ImGuiKey_Menu;
  m.attr("ImGuiKey_0") = ImGuiKey::ImGuiKey_0;
  m.attr("ImGuiKey_1") = ImGuiKey::ImGuiKey_1;
  m.attr("ImGuiKey_2") = ImGuiKey::ImGuiKey_2;
  m.attr("ImGuiKey_3") = ImGuiKey::ImGuiKey_3;
  m.attr("ImGuiKey_4") = ImGuiKey::ImGuiKey_4;
  m.attr("ImGuiKey_5") = ImGuiKey::ImGuiKey_5;
  m.attr("ImGuiKey_6") = ImGuiKey::ImGuiKey_6;
  m.attr("ImGuiKey_7") = ImGuiKey::ImGuiKey_7;
  m.attr("ImGuiKey_8") = ImGuiKey::ImGuiKey_8;
  m.attr("ImGuiKey_9") = ImGuiKey::ImGuiKey_9;
  m.attr("ImGuiKey_A") = ImGuiKey::ImGuiKey_A;
  m.attr("ImGuiKey_B") = ImGuiKey::ImGuiKey_B;
  m.attr("ImGuiKey_C") = ImGuiKey::ImGuiKey_C;
  m.attr("ImGuiKey_D") = ImGuiKey::ImGuiKey_D;
  m.attr("ImGuiKey_E") = ImGuiKey::ImGuiKey_E;
  m.attr("ImGuiKey_F") = ImGuiKey::ImGuiKey_F;
  m.attr("ImGuiKey_G") = ImGuiKey::ImGuiKey_G;
  m.attr("ImGuiKey_H") = ImGuiKey::ImGuiKey_H;
  m.attr("ImGuiKey_I") = ImGuiKey::ImGuiKey_I;
  m.attr("ImGuiKey_J") = ImGuiKey::ImGuiKey_J;
  m.attr("ImGuiKey_K") = ImGuiKey::ImGuiKey_K;
  m.attr("ImGuiKey_L") = ImGuiKey::ImGuiKey_L;
  m.attr("ImGuiKey_M") = ImGuiKey::ImGuiKey_M;
  m.attr("ImGuiKey_N") = ImGuiKey::ImGuiKey_N;
  m.attr("ImGuiKey_O") = ImGuiKey::ImGuiKey_O;
  m.attr("ImGuiKey_P") = ImGuiKey::ImGuiKey_P;
  m.attr("ImGuiKey_Q") = ImGuiKey::ImGuiKey_Q;
  m.attr("ImGuiKey_R") = ImGuiKey::ImGuiKey_R;
  m.attr("ImGuiKey_S") = ImGuiKey::ImGuiKey_S;
  m.attr("ImGuiKey_T") = ImGuiKey::ImGuiKey_T;
  m.attr("ImGuiKey_U") = ImGuiKey::ImGuiKey_U;
  m.attr("ImGuiKey_V") = ImGuiKey::ImGuiKey_V;
  m.attr("ImGuiKey_W") = ImGuiKey::ImGuiKey_W;
  m.attr("ImGuiKey_X") = ImGuiKey::ImGuiKey_X;
  m.attr("ImGuiKey_Y") = ImGuiKey::ImGuiKey_Y;
  m.attr("ImGuiKey_Z") = ImGuiKey::ImGuiKey_Z;
  m.attr("ImGuiKey_F1") = ImGuiKey::ImGuiKey_F1;
  m.attr("ImGuiKey_F2") = ImGuiKey::ImGuiKey_F2;
  m.attr("ImGuiKey_F3") = ImGuiKey::ImGuiKey_F3;
  m.attr("ImGuiKey_F4") = ImGuiKey::ImGuiKey_F4;
  m.attr("ImGuiKey_F5") = ImGuiKey::ImGuiKey_F5;
  m.attr("ImGuiKey_F6") = ImGuiKey::ImGuiKey_F6;
  m.attr("ImGuiKey_F7") = ImGuiKey::ImGuiKey_F7;
  m.attr("ImGuiKey_F8") = ImGuiKey::ImGuiKey_F8;
  m.attr("ImGuiKey_F9") = ImGuiKey::ImGuiKey_F9;
  m.attr("ImGuiKey_F10") = ImGuiKey::ImGuiKey_F10;
  m.attr("ImGuiKey_F11") = ImGuiKey::ImGuiKey_F11;
  m.attr("ImGuiKey_F12") = ImGuiKey::ImGuiKey_F12;
  m.attr("ImGuiKey_F13") = ImGuiKey::ImGuiKey_F13;
  m.attr("ImGuiKey_F14") = ImGuiKey::ImGuiKey_F14;
  m.attr("ImGuiKey_F15") = ImGuiKey::ImGuiKey_F15;
  m.attr("ImGuiKey_F16") = ImGuiKey::ImGuiKey_F16;
  m.attr("ImGuiKey_F17") = ImGuiKey::ImGuiKey_F17;
  m.attr("ImGuiKey_F18") = ImGuiKey::ImGuiKey_F18;
  m.attr("ImGuiKey_F19") = ImGuiKey::ImGuiKey_F19;
  m.attr("ImGuiKey_F20") = ImGuiKey::ImGuiKey_F20;
  m.attr("ImGuiKey_F21") = ImGuiKey::ImGuiKey_F21;
  m.attr("ImGuiKey_F22") = ImGuiKey::ImGuiKey_F22;
  m.attr("ImGuiKey_F23") = ImGuiKey::ImGuiKey_F23;
  m.attr("ImGuiKey_F24") = ImGuiKey::ImGuiKey_F24;
  m.attr("ImGuiKey_Apostrophe") = ImGuiKey::ImGuiKey_Apostrophe;
  m.attr("ImGuiKey_Comma") = ImGuiKey::ImGuiKey_Comma;
  m.attr("ImGuiKey_Minus") = ImGuiKey::ImGuiKey_Minus;
  m.attr("ImGuiKey_Period") = ImGuiKey::ImGuiKey_Period;
  m.attr("ImGuiKey_Slash") = ImGuiKey::ImGuiKey_Slash;
  m.attr("ImGuiKey_Semicolon") = ImGuiKey::ImGuiKey_Semicolon;
  m.attr("ImGuiKey_Equal") = ImGuiKey::ImGuiKey_Equal;
  m.attr("ImGuiKey_LeftBracket") = ImGuiKey::ImGuiKey_LeftBracket;
  m.attr("ImGuiKey_Backslash") = ImGuiKey::ImGuiKey_Backslash;
  m.attr("ImGuiKey_RightBracket") = ImGuiKey::ImGuiKey_RightBracket;
  m.attr("ImGuiKey_GraveAccent") = ImGuiKey::ImGuiKey_GraveAccent;
  m.attr("ImGuiKey_CapsLock") = ImGuiKey::ImGuiKey_CapsLock;
  m.attr("ImGuiKey_ScrollLock") = ImGuiKey::ImGuiKey_ScrollLock;
  m.attr("ImGuiKey_NumLock") = ImGuiKey::ImGuiKey_NumLock;
  m.attr("ImGuiKey_PrintScreen") = ImGuiKey::ImGuiKey_PrintScreen;
  m.attr("ImGuiKey_Pause") = ImGuiKey::ImGuiKey_Pause;
  m.attr("ImGuiKey_Keypad0") = ImGuiKey::ImGuiKey_Keypad0;
  m.attr("ImGuiKey_Keypad1") = ImGuiKey::ImGuiKey_Keypad1;
  m.attr("ImGuiKey_Keypad2") = ImGuiKey::ImGuiKey_Keypad2;
  m.attr("ImGuiKey_Keypad3") = ImGuiKey::ImGuiKey_Keypad3;
  m.attr("ImGuiKey_Keypad4") = ImGuiKey::ImGuiKey_Keypad4;
  m.attr("ImGuiKey_Keypad5") = ImGuiKey::ImGuiKey_Keypad5;
  m.attr("ImGuiKey_Keypad6") = ImGuiKey::ImGuiKey_Keypad6;
  m.attr("ImGuiKey_Keypad7") = ImGuiKey::ImGuiKey_Keypad7;
  m.attr("ImGuiKey_Keypad8") = ImGuiKey::ImGuiKey_Keypad8;
  m.attr("ImGuiKey_Keypad9") = ImGuiKey::ImGuiKey_Keypad9;
  m.attr("ImGuiKey_KeypadDecimal") = ImGuiKey::ImGuiKey_KeypadDecimal;
  m.attr("ImGuiKey_KeypadDivide") = ImGuiKey::ImGuiKey_KeypadDivide;
  m.attr("ImGuiKey_KeypadMultiply") = ImGuiKey::ImGuiKey_KeypadMultiply;
  m.attr("ImGuiKey_KeypadSubtract") = ImGuiKey::ImGuiKey_KeypadSubtract;
  m.attr("ImGuiKey_KeypadAdd") = ImGuiKey::ImGuiKey_KeypadAdd;
  m.attr("ImGuiKey_KeypadEnter") = ImGuiKey::ImGuiKey_KeypadEnter;
  m.attr("ImGuiKey_KeypadEqual") = ImGuiKey::ImGuiKey_KeypadEqual;
  m.attr("ImGuiKey_AppBack") = ImGuiKey::ImGuiKey_AppBack;
  m.attr("ImGuiKey_AppForward") = ImGuiKey::ImGuiKey_AppForward;
  m.attr("ImGuiKey_GamepadStart") = ImGuiKey::ImGuiKey_GamepadStart;
  m.attr("ImGuiKey_GamepadBack") = ImGuiKey::ImGuiKey_GamepadBack;
  m.attr("ImGuiKey_GamepadFaceUp") = ImGuiKey::ImGuiKey_GamepadFaceUp;
  m.attr("ImGuiKey_GamepadFaceDown") = ImGuiKey::ImGuiKey_GamepadFaceDown;
  m.attr("ImGuiKey_GamepadFaceLeft") = ImGuiKey::ImGuiKey_GamepadFaceLeft;
  m.attr("ImGuiKey_GamepadFaceRight") = ImGuiKey::ImGuiKey_GamepadFaceRight;
  m.attr("ImGuiKey_GamepadDpadUp") = ImGuiKey::ImGuiKey_GamepadDpadUp;
  m.attr("ImGuiKey_GamepadDpadDown") = ImGuiKey::ImGuiKey_GamepadDpadDown;
  m.attr("ImGuiKey_GamepadDpadLeft") = ImGuiKey::ImGuiKey_GamepadDpadLeft;
  m.attr("ImGuiKey_GamepadDpadRight") = ImGuiKey::ImGuiKey_GamepadDpadRight;
  m.attr("ImGuiKey_GamepadL1") = ImGuiKey::ImGuiKey_GamepadL1;
  m.attr("ImGuiKey_GamepadR1") = ImGuiKey::ImGuiKey_GamepadR1;
  m.attr("ImGuiKey_GamepadL2") = ImGuiKey::ImGuiKey_GamepadL2;
  m.attr("ImGuiKey_GamepadR2") = ImGuiKey::ImGuiKey_GamepadR2;
  m.attr("ImGuiKey_GamepadL3") = ImGuiKey::ImGuiKey_GamepadL3;
  m.attr("ImGuiKey_GamepadR3") = ImGuiKey::ImGuiKey_GamepadR3;
  m.attr("ImGuiKey_GamepadLStickUp") = ImGuiKey::ImGuiKey_GamepadLStickUp;
  m.attr("ImGuiKey_GamepadLStickDown") = ImGuiKey::ImGuiKey_GamepadLStickDown;
  m.attr("ImGuiKey_GamepadLStickLeft") = ImGuiKey::ImGuiKey_GamepadLStickLeft;
  m.attr("ImGuiKey_GamepadLStickRight") = ImGuiKey::ImGuiKey_GamepadLStickRight;
  m.attr("ImGuiKey_GamepadRStickUp") = ImGuiKey::ImGuiKey_GamepadRStickUp;
  m.attr("ImGuiKey_GamepadRStickDown") = ImGuiKey::ImGuiKey_GamepadRStickDown;
  m.attr("ImGuiKey_GamepadRStickLeft") = ImGuiKey::ImGuiKey_GamepadRStickLeft;
  m.attr("ImGuiKey_GamepadRStickRight") = ImGuiKey::ImGuiKey_GamepadRStickRight;
  m.attr("ImGuiKey_ModCtrl") = ImGuiKey::ImGuiKey_ModCtrl;
  m.attr("ImGuiKey_ModShift") = ImGuiKey::ImGuiKey_ModShift;
  m.attr("ImGuiKey_ModAlt") = ImGuiKey::ImGuiKey_ModAlt;
  m.attr("ImGuiKey_ModSuper") = ImGuiKey::ImGuiKey_ModSuper;
  m.attr("ImGuiMod_None") = ImGuiKey::ImGuiMod_None;
  m.attr("ImGuiMod_Ctrl") = ImGuiKey::ImGuiMod_Ctrl;
  m.attr("ImGuiMod_Shift") = ImGuiKey::ImGuiMod_Shift;
  m.attr("ImGuiMod_Alt") = ImGuiKey::ImGuiMod_Alt;
  m.attr("ImGuiMod_Super") = ImGuiKey::ImGuiMod_Super;
  m.attr("ImGuiMod_Mask_") = ImGuiKey::ImGuiMod_Mask_;



  // ImDrawFlags

}
