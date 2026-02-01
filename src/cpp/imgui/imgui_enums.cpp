#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

void bind_imgui_enums(nb::module_& m) {

  // For most of these, we simply bind the int constants

  // A few enums are bound differently, currently: ImGuiDir ImGuiKey ImGuiMouseSource ImGuiSortDirection
  // These are defined as actual enums rather than ints, because they are different in imgui.h, and otherwise we lose implicit conversions.

  { // ImGuiDir ImGuiDir
  auto e = nb::enum_<ImGuiDir>(m, "ImGuiDir");
    e.value("ImGuiDir_None",                           ImGuiDir_None);                           m.attr("ImGuiDir_None")                           = ImGuiDir::ImGuiDir_None;
    e.value("ImGuiDir_Left",                           ImGuiDir_Left);                           m.attr("ImGuiDir_Left")                           = ImGuiDir::ImGuiDir_Left;
    e.value("ImGuiDir_Right",                          ImGuiDir_Right);                          m.attr("ImGuiDir_Right")                          = ImGuiDir::ImGuiDir_Right;
    e.value("ImGuiDir_Up",                             ImGuiDir_Up);                             m.attr("ImGuiDir_Up")                             = ImGuiDir::ImGuiDir_Up;
    e.value("ImGuiDir_Down",                           ImGuiDir_Down);                           m.attr("ImGuiDir_Down")                           = ImGuiDir::ImGuiDir_Down;
    e.value("ImGuiDir_COUNT",                          ImGuiDir_COUNT);                          m.attr("ImGuiDir_COUNT")                          = ImGuiDir::ImGuiDir_COUNT;
  ;
  }

  { // ImGuiSortDirection ImGuiSortDirection
  auto e = nb::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection");
    e.value("ImGuiSortDirection_None",                 ImGuiSortDirection_None);                 m.attr("ImGuiSortDirection_None")                 = ImGuiSortDirection::ImGuiSortDirection_None;
    e.value("ImGuiSortDirection_Ascending",            ImGuiSortDirection_Ascending);            m.attr("ImGuiSortDirection_Ascending")            = ImGuiSortDirection::ImGuiSortDirection_Ascending;
    e.value("ImGuiSortDirection_Descending",           ImGuiSortDirection_Descending);           m.attr("ImGuiSortDirection_Descending")           = ImGuiSortDirection::ImGuiSortDirection_Descending;
  ;
  }

  { // ImGuiWindowFlags ImGuiWindowFlags_
    m.attr("ImGuiWindowFlags_NoSavedSettings")        = static_cast<int>(ImGuiWindowFlags_NoSavedSettings);
    m.attr("ImGuiWindowFlags_NoMouseInputs")          = static_cast<int>(ImGuiWindowFlags_NoMouseInputs);
    m.attr("ImGuiWindowFlags_MenuBar")                = static_cast<int>(ImGuiWindowFlags_MenuBar);
    m.attr("ImGuiWindowFlags_HorizontalScrollbar")    = static_cast<int>(ImGuiWindowFlags_HorizontalScrollbar);
    m.attr("ImGuiWindowFlags_NoFocusOnAppearing")     = static_cast<int>(ImGuiWindowFlags_NoFocusOnAppearing);
    m.attr("ImGuiWindowFlags_NoBringToFrontOnFocus")  = static_cast<int>(ImGuiWindowFlags_NoBringToFrontOnFocus);
    m.attr("ImGuiWindowFlags_AlwaysVerticalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysVerticalScrollbar);
    m.attr("ImGuiWindowFlags_AlwaysHorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysHorizontalScrollbar);
    m.attr("ImGuiWindowFlags_NoNavInputs")            = static_cast<int>(ImGuiWindowFlags_NoNavInputs);
    m.attr("ImGuiWindowFlags_NoNavFocus")             = static_cast<int>(ImGuiWindowFlags_NoNavFocus);
    m.attr("ImGuiWindowFlags_UnsavedDocument")        = static_cast<int>(ImGuiWindowFlags_UnsavedDocument);
    m.attr("ImGuiWindowFlags_NoNav")                  = static_cast<int>(ImGuiWindowFlags_NoNav);
    m.attr("ImGuiWindowFlags_NoDecoration")           = static_cast<int>(ImGuiWindowFlags_NoDecoration);
    m.attr("ImGuiWindowFlags_NoInputs")               = static_cast<int>(ImGuiWindowFlags_NoInputs);
    m.attr("ImGuiWindowFlags_ChildWindow")            = static_cast<int>(ImGuiWindowFlags_ChildWindow);
    m.attr("ImGuiWindowFlags_Tooltip")                = static_cast<int>(ImGuiWindowFlags_Tooltip);
    m.attr("ImGuiWindowFlags_Popup")                  = static_cast<int>(ImGuiWindowFlags_Popup);
    m.attr("ImGuiWindowFlags_Modal")                  = static_cast<int>(ImGuiWindowFlags_Modal);
    m.attr("ImGuiWindowFlags_ChildMenu")              = static_cast<int>(ImGuiWindowFlags_ChildMenu);
  ;
  }

  { // ImGuiChildFlags ImGuiChildFlags_
    m.attr("ImGuiChildFlags_None")                    = static_cast<int>(ImGuiChildFlags_None);
    m.attr("ImGuiChildFlags_Borders")                 = static_cast<int>(ImGuiChildFlags_Borders);
    m.attr("ImGuiChildFlags_AlwaysUseWindowPadding")  = static_cast<int>(ImGuiChildFlags_AlwaysUseWindowPadding);
    m.attr("ImGuiChildFlags_ResizeX")                 = static_cast<int>(ImGuiChildFlags_ResizeX);
    m.attr("ImGuiChildFlags_ResizeY")                 = static_cast<int>(ImGuiChildFlags_ResizeY);
    m.attr("ImGuiChildFlags_AutoResizeX")             = static_cast<int>(ImGuiChildFlags_AutoResizeX);
    m.attr("ImGuiChildFlags_AutoResizeY")             = static_cast<int>(ImGuiChildFlags_AutoResizeY);
    m.attr("ImGuiChildFlags_AlwaysAutoResize")        = static_cast<int>(ImGuiChildFlags_AlwaysAutoResize);
    m.attr("ImGuiChildFlags_FrameStyle")               = static_cast<int>(ImGuiChildFlags_FrameStyle);
    m.attr("ImGuiChildFlags_NavFlattened")            = static_cast<int>(ImGuiChildFlags_NavFlattened);
  ;
  }

  { // ImGuiItemFlags ImGuiItemFlags_
    m.attr("ImGuiItemFlags_None")                     = static_cast<int>(ImGuiItemFlags_None);
    m.attr("ImGuiItemFlags_NoTabStop")                = static_cast<int>(ImGuiItemFlags_NoTabStop);
    m.attr("ImGuiItemFlags_NoNav")                    = static_cast<int>(ImGuiItemFlags_NoNav);
    m.attr("ImGuiItemFlags_NoNavDefaultFocus")        = static_cast<int>(ImGuiItemFlags_NoNavDefaultFocus);
    m.attr("ImGuiItemFlags_ButtonRepeat")             = static_cast<int>(ImGuiItemFlags_ButtonRepeat);
    m.attr("ImGuiItemFlags_AutoClosePopups")          = static_cast<int>(ImGuiItemFlags_AutoClosePopups);
    m.attr("ImGuiItemFlags_AllowDuplicateId")         = static_cast<int>(ImGuiItemFlags_AllowDuplicateId);
    m.attr("ImGuiItemFlags_Disabled")                  = static_cast<int>(ImGuiItemFlags_Disabled);
  ;
  }

  { // ImGuiInputTextFlags ImGuiInputTextFlags_
    m.attr("ImGuiInputTextFlags_None")                = static_cast<int>(ImGuiInputTextFlags_None);
    m.attr("ImGuiInputTextFlags_CharsDecimal")        = static_cast<int>(ImGuiInputTextFlags_CharsDecimal);
    m.attr("ImGuiInputTextFlags_CharsHexadecimal")    = static_cast<int>(ImGuiInputTextFlags_CharsHexadecimal);
    m.attr("ImGuiInputTextFlags_CharsScientific")     = static_cast<int>(ImGuiInputTextFlags_CharsScientific);
    m.attr("ImGuiInputTextFlags_CharsUppercase")      = static_cast<int>(ImGuiInputTextFlags_CharsUppercase);
    m.attr("ImGuiInputTextFlags_CharsNoBlank")        = static_cast<int>(ImGuiInputTextFlags_CharsNoBlank);
    m.attr("ImGuiInputTextFlags_AllowTabInput")       = static_cast<int>(ImGuiInputTextFlags_AllowTabInput);
    m.attr("ImGuiInputTextFlags_EnterReturnsTrue")    = static_cast<int>(ImGuiInputTextFlags_EnterReturnsTrue);
    m.attr("ImGuiInputTextFlags_EscapeClearsAll")     = static_cast<int>(ImGuiInputTextFlags_EscapeClearsAll);
    m.attr("ImGuiInputTextFlags_CtrlEnterForNewLine") = static_cast<int>(ImGuiInputTextFlags_CtrlEnterForNewLine);
    m.attr("ImGuiInputTextFlags_ReadOnly")            = static_cast<int>(ImGuiInputTextFlags_ReadOnly);
    m.attr("ImGuiInputTextFlags_Password")            = static_cast<int>(ImGuiInputTextFlags_Password);
    m.attr("ImGuiInputTextFlags_AlwaysOverwrite")     = static_cast<int>(ImGuiInputTextFlags_AlwaysOverwrite);
    m.attr("ImGuiInputTextFlags_AutoSelectAll")       = static_cast<int>(ImGuiInputTextFlags_AutoSelectAll);
    m.attr("ImGuiInputTextFlags_ParseEmptyRefVal")    = static_cast<int>(ImGuiInputTextFlags_ParseEmptyRefVal);
    m.attr("ImGuiInputTextFlags_DisplayEmptyRefVal")  = static_cast<int>(ImGuiInputTextFlags_DisplayEmptyRefVal);
    m.attr("ImGuiInputTextFlags_NoHorizontalScroll")  = static_cast<int>(ImGuiInputTextFlags_NoHorizontalScroll);
    m.attr("ImGuiInputTextFlags_NoUndoRedo")          = static_cast<int>(ImGuiInputTextFlags_NoUndoRedo);
    m.attr("ImGuiInputTextFlags_ElideLeft")           = static_cast<int>(ImGuiInputTextFlags_ElideLeft);
    m.attr("ImGuiInputTextFlags_CallbackCompletion")  = static_cast<int>(ImGuiInputTextFlags_CallbackCompletion);
    m.attr("ImGuiInputTextFlags_CallbackHistory")     = static_cast<int>(ImGuiInputTextFlags_CallbackHistory);
    m.attr("ImGuiInputTextFlags_CallbackAlways")      = static_cast<int>(ImGuiInputTextFlags_CallbackAlways);
    m.attr("ImGuiInputTextFlags_CallbackCharFilter")  = static_cast<int>(ImGuiInputTextFlags_CallbackCharFilter);
    m.attr("ImGuiInputTextFlags_CallbackResize")      = static_cast<int>(ImGuiInputTextFlags_CallbackResize);
    m.attr("ImGuiInputTextFlags_CallbackEdit")        = static_cast<int>(ImGuiInputTextFlags_CallbackEdit);
    m.attr("ImGuiInputTextFlags_WordWrap")            = static_cast<int>(ImGuiInputTextFlags_WordWrap);
  ;
  }

  { // ImGuiTreeNodeFlags ImGuiTreeNodeFlags_
    m.attr("ImGuiTreeNodeFlags_None")                 = static_cast<int>(ImGuiTreeNodeFlags_None);
    m.attr("ImGuiTreeNodeFlags_Selected")             = static_cast<int>(ImGuiTreeNodeFlags_Selected);
    m.attr("ImGuiTreeNodeFlags_Framed")               = static_cast<int>(ImGuiTreeNodeFlags_Framed);
    m.attr("ImGuiTreeNodeFlags_AllowOverlap")         = static_cast<int>(ImGuiTreeNodeFlags_AllowOverlap);
    m.attr("ImGuiTreeNodeFlags_NoTreePushOnOpen")     = static_cast<int>(ImGuiTreeNodeFlags_NoTreePushOnOpen);
    m.attr("ImGuiTreeNodeFlags_NoAutoOpenOnLog")      = static_cast<int>(ImGuiTreeNodeFlags_NoAutoOpenOnLog);
    m.attr("ImGuiTreeNodeFlags_DefaultOpen")          = static_cast<int>(ImGuiTreeNodeFlags_DefaultOpen);
    m.attr("ImGuiTreeNodeFlags_OpenOnDoubleClick")    = static_cast<int>(ImGuiTreeNodeFlags_OpenOnDoubleClick);
    m.attr("ImGuiTreeNodeFlags_OpenOnArrow")          = static_cast<int>(ImGuiTreeNodeFlags_OpenOnArrow);
    m.attr("ImGuiTreeNodeFlags_Leaf")                 = static_cast<int>(ImGuiTreeNodeFlags_Leaf);
    m.attr("ImGuiTreeNodeFlags_Bullet")               = static_cast<int>(ImGuiTreeNodeFlags_Bullet);
    m.attr("ImGuiTreeNodeFlags_FramePadding")         = static_cast<int>(ImGuiTreeNodeFlags_FramePadding);
    m.attr("ImGuiTreeNodeFlags_SpanAvailWidth")       = static_cast<int>(ImGuiTreeNodeFlags_SpanAvailWidth);
    m.attr("ImGuiTreeNodeFlags_SpanFullWidth")        = static_cast<int>(ImGuiTreeNodeFlags_SpanFullWidth);
    m.attr("ImGuiTreeNodeFlags_SpanLabelWidth")       = static_cast<int>(ImGuiTreeNodeFlags_SpanLabelWidth);
    m.attr("ImGuiTreeNodeFlags_SpanAllColumns")       = static_cast<int>(ImGuiTreeNodeFlags_SpanAllColumns);
    m.attr("ImGuiTreeNodeFlags_LabelSpanAllColumns")  = static_cast<int>(ImGuiTreeNodeFlags_LabelSpanAllColumns);
    m.attr("ImGuiTreeNodeFlags_NavLeftJumpsToParent") = static_cast<int>(ImGuiTreeNodeFlags_NavLeftJumpsToParent);
    m.attr("ImGuiTreeNodeFlags_CollapsingHeader")     = static_cast<int>(ImGuiTreeNodeFlags_CollapsingHeader);
    m.attr("ImGuiTreeNodeFlags_DrawLinesNone")        = static_cast<int>(ImGuiTreeNodeFlags_DrawLinesNone);
    m.attr("ImGuiTreeNodeFlags_DrawLinesFull")        = static_cast<int>(ImGuiTreeNodeFlags_DrawLinesFull);
    m.attr("ImGuiTreeNodeFlags_DrawLinesToNodes")     = static_cast<int>(ImGuiTreeNodeFlags_DrawLinesToNodes);
  ;
  }

  { // ImGuiListClipperFlags ImGuiListClipperFlags_
    m.attr("ImGuiListClipperFlags_None")                  = static_cast<int>(ImGuiListClipperFlags_None);
    m.attr("ImGuiListClipperFlags_NoSetTableRowCounters") = static_cast<int>(ImGuiListClipperFlags_NoSetTableRowCounters);
  ;
  }

  { // ImGuiPopupFlags ImGuiPopupFlags_
    m.attr("ImGuiPopupFlags_None" )                   = static_cast<int>(ImGuiPopupFlags_None);
    m.attr("ImGuiPopupFlags_MouseButtonLeft")        = static_cast<int>(ImGuiPopupFlags_MouseButtonLeft);
    m.attr("ImGuiPopupFlags_MouseButtonRight")       = static_cast<int>(ImGuiPopupFlags_MouseButtonRight);
    m.attr("ImGuiPopupFlags_MouseButtonMiddle")       = static_cast<int>(ImGuiPopupFlags_MouseButtonMiddle);
    m.attr("ImGuiPopupFlags_MouseButtonMask_")        = static_cast<int>(ImGuiPopupFlags_MouseButtonMask_);
    m.attr("ImGuiPopupFlags_MouseButtonDefault_")     = static_cast<int>(ImGuiPopupFlags_MouseButtonDefault_);
    m.attr("ImGuiPopupFlags_NoReopen")                 = static_cast<int>(ImGuiPopupFlags_NoReopen);
    m.attr("ImGuiPopupFlags_NoOpenOverExistingPopup") = static_cast<int>(ImGuiPopupFlags_NoOpenOverExistingPopup);
    m.attr("ImGuiPopupFlags_NoOpenOverItems")          = static_cast<int>(ImGuiPopupFlags_NoOpenOverItems);
    m.attr("ImGuiPopupFlags_AnyPopupId")              = static_cast<int>(ImGuiPopupFlags_AnyPopupId);
    m.attr("ImGuiPopupFlags_AnyPopupLevel")           = static_cast<int>(ImGuiPopupFlags_AnyPopupLevel);
    m.attr("ImGuiPopupFlags_AnyPopup")                = static_cast<int>(ImGuiPopupFlags_AnyPopup);
  ;
  }

  { // ImGuiMultiSelectFlags ImGuiMultiSelectFlags_
    m.attr("ImGuiMultiSelectFlags_None")                  = static_cast<int>(ImGuiMultiSelectFlags_None);
    m.attr("ImGuiMultiSelectFlags_SingleSelect")          = static_cast<int>(ImGuiMultiSelectFlags_SingleSelect);
    m.attr("ImGuiMultiSelectFlags_NoSelectAll")           = static_cast<int>(ImGuiMultiSelectFlags_NoSelectAll);
    m.attr("ImGuiMultiSelectFlags_NoRangeSelect")         = static_cast<int>(ImGuiMultiSelectFlags_NoRangeSelect);
    m.attr("ImGuiMultiSelectFlags_NoAutoSelect")          = static_cast<int>(ImGuiMultiSelectFlags_NoAutoSelect);
    m.attr("ImGuiMultiSelectFlags_NoAutoClear")           = static_cast<int>(ImGuiMultiSelectFlags_NoAutoClear);
    m.attr("ImGuiMultiSelectFlags_NoAutoClearOnReselect") = static_cast<int>(ImGuiMultiSelectFlags_NoAutoClearOnReselect);
    m.attr("ImGuiMultiSelectFlags_BoxSelect1d")           = static_cast<int>(ImGuiMultiSelectFlags_BoxSelect1d);
    m.attr("ImGuiMultiSelectFlags_BoxSelect2d")           = static_cast<int>(ImGuiMultiSelectFlags_BoxSelect2d);
    m.attr("ImGuiMultiSelectFlags_BoxSelectNoScroll")     = static_cast<int>(ImGuiMultiSelectFlags_BoxSelectNoScroll);
    m.attr("ImGuiMultiSelectFlags_ClearOnEscape")         = static_cast<int>(ImGuiMultiSelectFlags_ClearOnEscape);
    m.attr("ImGuiMultiSelectFlags_ClearOnClickVoid")      = static_cast<int>(ImGuiMultiSelectFlags_ClearOnClickVoid);
    m.attr("ImGuiMultiSelectFlags_ScopeWindow")           = static_cast<int>(ImGuiMultiSelectFlags_ScopeWindow);
    m.attr("ImGuiMultiSelectFlags_ScopeRect")             = static_cast<int>(ImGuiMultiSelectFlags_ScopeRect);
    m.attr("ImGuiMultiSelectFlags_SelectOnClick")         = static_cast<int>(ImGuiMultiSelectFlags_SelectOnClick);
    m.attr("ImGuiMultiSelectFlags_SelectOnClickRelease")  = static_cast<int>(ImGuiMultiSelectFlags_SelectOnClickRelease);
    m.attr("ImGuiMultiSelectFlags_NavWrapX")              = static_cast<int>(ImGuiMultiSelectFlags_NavWrapX);
    m.attr("ImGuiMultiSelectFlags_NoSelectOnRightClick")  = static_cast<int>(ImGuiMultiSelectFlags_NoSelectOnRightClick);
  ;
  }

  { // ImGuiSelectableFlags ImGuiSelectableFlags_
    m.attr("ImGuiSelectableFlags_None")               = static_cast<int>(ImGuiSelectableFlags_None);
    m.attr("ImGuiSelectableFlags_DontClosePopups")    = static_cast<int>(ImGuiSelectableFlags_DontClosePopups);
    m.attr("ImGuiSelectableFlags_SpanAllColumns")     = static_cast<int>(ImGuiSelectableFlags_SpanAllColumns);
    m.attr("ImGuiSelectableFlags_AllowDoubleClick")   = static_cast<int>(ImGuiSelectableFlags_AllowDoubleClick);
    m.attr("ImGuiSelectableFlags_Disabled")           = static_cast<int>(ImGuiSelectableFlags_Disabled);
    m.attr("ImGuiSelectableFlags_AllowOverlap")       = static_cast<int>(ImGuiSelectableFlags_AllowOverlap);
    m.attr("ImGuiSelectableFlags_Highlight")          = static_cast<int>(ImGuiSelectableFlags_Highlight);
    m.attr("ImGuiSelectableFlags_SelectOnNav")        = static_cast<int>(ImGuiSelectableFlags_SelectOnNav);
  ;
  }

  { // ImGuiComboFlags ImGuiComboFlags_
    m.attr("ImGuiComboFlags_None")                    = static_cast<int>(ImGuiComboFlags_None);
    m.attr("ImGuiComboFlags_PopupAlignLeft")          = static_cast<int>(ImGuiComboFlags_PopupAlignLeft);
    m.attr("ImGuiComboFlags_HeightSmall")             = static_cast<int>(ImGuiComboFlags_HeightSmall);
    m.attr("ImGuiComboFlags_HeightRegular")           = static_cast<int>(ImGuiComboFlags_HeightRegular);
    m.attr("ImGuiComboFlags_HeightLarge")             = static_cast<int>(ImGuiComboFlags_HeightLarge);
    m.attr("ImGuiComboFlags_HeightLargest")           = static_cast<int>(ImGuiComboFlags_HeightLargest);
    m.attr("ImGuiComboFlags_NoArrowButton")           = static_cast<int>(ImGuiComboFlags_NoArrowButton);
    m.attr("ImGuiComboFlags_NoPreview")               = static_cast<int>(ImGuiComboFlags_NoPreview);
    m.attr("ImGuiComboFlags_WidthFitPreview")         = static_cast<int>(ImGuiComboFlags_WidthFitPreview);
    m.attr("ImGuiComboFlags_HeightMask_")             = static_cast<int>(ImGuiComboFlags_HeightMask_);
  ;
  }

  { // ImGuiTabBarFlags ImGuiTabBarFlags_
    m.attr("ImGuiTabBarFlags_None")                   = static_cast<int>(ImGuiTabBarFlags_None);
    m.attr("ImGuiTabBarFlags_Reorderable")            = static_cast<int>(ImGuiTabBarFlags_Reorderable);
    m.attr("ImGuiTabBarFlags_AutoSelectNewTabs")      = static_cast<int>(ImGuiTabBarFlags_AutoSelectNewTabs);
    m.attr("ImGuiTabBarFlags_TabListPopupButton")     = static_cast<int>(ImGuiTabBarFlags_TabListPopupButton);
    m.attr("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton") = static_cast<int>(ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
    m.attr("ImGuiTabBarFlags_NoTabListScrollingButtons") = static_cast<int>(ImGuiTabBarFlags_NoTabListScrollingButtons);
    m.attr("ImGuiTabBarFlags_NoTooltip")              = static_cast<int>(ImGuiTabBarFlags_NoTooltip);
    m.attr("ImGuiTabBarFlags_DrawSelectedOverline")   = static_cast<int>(ImGuiTabBarFlags_DrawSelectedOverline);
    m.attr("ImGuiTabBarFlags_FittingPolicyMixed")     = static_cast<int>(ImGuiTabBarFlags_FittingPolicyMixed);
    m.attr("ImGuiTabBarFlags_FittingPolicyShrink")    = static_cast<int>(ImGuiTabBarFlags_FittingPolicyShrink);
    m.attr("ImGuiTabBarFlags_FittingPolicyScroll")    = static_cast<int>(ImGuiTabBarFlags_FittingPolicyScroll);
    m.attr("ImGuiTabBarFlags_FittingPolicyScroll")    = static_cast<int>(ImGuiTabBarFlags_FittingPolicyScroll);
    m.attr("ImGuiTabBarFlags_FittingPolicyMask_")     = static_cast<int>(ImGuiTabBarFlags_FittingPolicyMask_);
    m.attr("ImGuiTabBarFlags_FittingPolicyDefault_")  = static_cast<int>(ImGuiTabBarFlags_FittingPolicyDefault_);
  ;
  }

  { // ImGuiTabItemFlags ImGuiTabItemFlags_
    m.attr("ImGuiTabItemFlags_None")                  = static_cast<int>(ImGuiTabItemFlags_None);
    m.attr("ImGuiTabItemFlags_UnsavedDocument")       = static_cast<int>(ImGuiTabItemFlags_UnsavedDocument);
    m.attr("ImGuiTabItemFlags_SetSelected")           = static_cast<int>(ImGuiTabItemFlags_SetSelected);
    m.attr("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton") = static_cast<int>(ImGuiTabItemFlags_NoCloseWithMiddleMouseButton);
    m.attr("ImGuiTabItemFlags_NoPushId")              = static_cast<int>(ImGuiTabItemFlags_NoPushId);
    m.attr("ImGuiTabItemFlags_NoTooltip")             = static_cast<int>(ImGuiTabItemFlags_NoTooltip);
    m.attr("ImGuiTabItemFlags_NoReorder")             = static_cast<int>(ImGuiTabItemFlags_NoReorder);
    m.attr("ImGuiTabItemFlags_Leading")               = static_cast<int>(ImGuiTabItemFlags_Leading);
    m.attr("ImGuiTabItemFlags_Trailing")              = static_cast<int>(ImGuiTabItemFlags_Trailing);
    m.attr("ImGuiTabItemFlags_NoAssumedClosure")      = static_cast<int>(ImGuiTabItemFlags_NoAssumedClosure);
  ;
  }

  { // ImGuiFocusedFlags ImGuiFocusedFlags_
    m.attr("ImGuiFocusedFlags_None")                  = static_cast<int>(ImGuiFocusedFlags_None);
    m.attr("ImGuiFocusedFlags_ChildWindows")          = static_cast<int>(ImGuiFocusedFlags_ChildWindows);
    m.attr("ImGuiFocusedFlags_RootWindow")            = static_cast<int>(ImGuiFocusedFlags_RootWindow);
    m.attr("ImGuiFocusedFlags_AnyWindow")             = static_cast<int>(ImGuiFocusedFlags_AnyWindow);
    m.attr("ImGuiFocusedFlags_NoPopupHierarchy")      = static_cast<int>(ImGuiFocusedFlags_NoPopupHierarchy);
    m.attr("ImGuiFocusedFlags_RootAndChildWindows")   = static_cast<int>(ImGuiFocusedFlags_RootAndChildWindows);
  ;
  }

  { // ImGuiHoveredFlags ImGuiHoveredFlags_
    m.attr("ImGuiHoveredFlags_None")                  = static_cast<int>(ImGuiHoveredFlags_None);
    m.attr("ImGuiHoveredFlags_ChildWindows")          = static_cast<int>(ImGuiHoveredFlags_ChildWindows);
    m.attr("ImGuiHoveredFlags_RootWindow")            = static_cast<int>(ImGuiHoveredFlags_RootWindow);
    m.attr("ImGuiHoveredFlags_AnyWindow")             = static_cast<int>(ImGuiHoveredFlags_AnyWindow);
    m.attr("ImGuiHoveredFlags_NoPopupHierarchy")      = static_cast<int>(ImGuiHoveredFlags_NoPopupHierarchy);
    m.attr("ImGuiHoveredFlags_AllowWhenBlockedByPopup") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
    m.attr("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
    m.attr("ImGuiHoveredFlags_AllowWhenOverlappedByItem") = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlappedByItem);
    m.attr("ImGuiHoveredFlags_AllowWhenOverlappedByWindow") = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlappedByWindow);
    m.attr("ImGuiHoveredFlags_AllowWhenDisabled")     = static_cast<int>(ImGuiHoveredFlags_AllowWhenDisabled);
    m.attr("ImGuiHoveredFlags_NoNavOverride")         = static_cast<int>(ImGuiHoveredFlags_NoNavOverride);
    m.attr("ImGuiHoveredFlags_AllowWhenOverlapped")   = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlapped);
    m.attr("ImGuiHoveredFlags_RectOnly")              = static_cast<int>(ImGuiHoveredFlags_RectOnly);
    m.attr("ImGuiHoveredFlags_RootAndChildWindows")   = static_cast<int>(ImGuiHoveredFlags_RootAndChildWindows);
    m.attr("ImGuiHoveredFlags_ForTooltip")            = static_cast<int>(ImGuiHoveredFlags_ForTooltip);
    m.attr("ImGuiHoveredFlags_Stationary")            = static_cast<int>(ImGuiHoveredFlags_Stationary);
    m.attr("ImGuiHoveredFlags_DelayNone")             = static_cast<int>(ImGuiHoveredFlags_DelayNone);
    m.attr("ImGuiHoveredFlags_DelayShort")            = static_cast<int>(ImGuiHoveredFlags_DelayShort);
    m.attr("ImGuiHoveredFlags_DelayNormal")           = static_cast<int>(ImGuiHoveredFlags_DelayNormal);
    m.attr("ImGuiHoveredFlags_NoSharedDelay")         = static_cast<int>(ImGuiHoveredFlags_NoSharedDelay);
  ;
  }


  { // ImGuiDragDropFlags ImGuiDragDropFlags_
    m.attr("ImGuiDragDropFlags_None")                       = static_cast<int>(ImGuiDragDropFlags_None);
    m.attr("ImGuiDragDropFlags_SourceNoPreviewTooltip")     = static_cast<int>(ImGuiDragDropFlags_SourceNoPreviewTooltip);
    m.attr("ImGuiDragDropFlags_SourceNoDisableHover")       = static_cast<int>(ImGuiDragDropFlags_SourceNoDisableHover);
    m.attr("ImGuiDragDropFlags_SourceNoHoldToOpenOthers")   = static_cast<int>(ImGuiDragDropFlags_SourceNoHoldToOpenOthers);
    m.attr("ImGuiDragDropFlags_SourceAllowNullID")          = static_cast<int>(ImGuiDragDropFlags_SourceAllowNullID);
    m.attr("ImGuiDragDropFlags_SourceExtern")               = static_cast<int>(ImGuiDragDropFlags_SourceExtern);
    m.attr("ImGuiDragDropFlags_PayloadAutoExpire")          = static_cast<int>(ImGuiDragDropFlags_PayloadAutoExpire);
    m.attr("ImGuiDragDropFlags_PayloadNoCrossContext")      = static_cast<int>(ImGuiDragDropFlags_PayloadNoCrossContext);
    m.attr("ImGuiDragDropFlags_PayloadNoCrossProcess")      = static_cast<int>(ImGuiDragDropFlags_PayloadNoCrossProcess);
    m.attr("ImGuiDragDropFlags_AcceptBeforeDelivery")       = static_cast<int>(ImGuiDragDropFlags_AcceptBeforeDelivery);
    m.attr("ImGuiDragDropFlags_AcceptNoDrawDefaultRect")    = static_cast<int>(ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
    m.attr("ImGuiDragDropFlags_AcceptNoPreviewTooltip")     = static_cast<int>(ImGuiDragDropFlags_AcceptNoPreviewTooltip);
    m.attr("ImGuiDragDropFlags_AcceptDrawAsHovered")        = static_cast<int>(ImGuiDragDropFlags_AcceptDrawAsHovered);
    m.attr("ImGuiDragDropFlags_AcceptPeekOnly")             = static_cast<int>(ImGuiDragDropFlags_AcceptPeekOnly);
  ;
  }

  { // ImGuiDataType ImGuiDataType_
    m.attr("ImGuiDataType_S8")                        = static_cast<int>(ImGuiDataType_S8);
    m.attr("ImGuiDataType_U8")                        = static_cast<int>(ImGuiDataType_U8);
    m.attr("ImGuiDataType_S16")                       = static_cast<int>(ImGuiDataType_S16);
    m.attr("ImGuiDataType_U16")                       = static_cast<int>(ImGuiDataType_U16);
    m.attr("ImGuiDataType_S32")                       = static_cast<int>(ImGuiDataType_S32);
    m.attr("ImGuiDataType_U32")                       = static_cast<int>(ImGuiDataType_U32);
    m.attr("ImGuiDataType_S64")                       = static_cast<int>(ImGuiDataType_S64);
    m.attr("ImGuiDataType_U64")                       = static_cast<int>(ImGuiDataType_U64);
    m.attr("ImGuiDataType_Float")                     = static_cast<int>(ImGuiDataType_Float);
    m.attr("ImGuiDataType_Double")                    = static_cast<int>(ImGuiDataType_Double);
    m.attr("ImGuiDataType_Bool")                      = static_cast<int>(ImGuiDataType_Bool);
    m.attr("ImGuiDataType_String")                    = static_cast<int>(ImGuiDataType_String);
    m.attr("ImGuiDataType_COUNT")                     = static_cast<int>(ImGuiDataType_COUNT);
  ;
  }

  // TODO resume here

  { // ImGuiInputFlags ImGuiInputFlags_
    m.attr("ImGuiInputFlags_None")                    = static_cast<int>(ImGuiInputFlags_None);
    m.attr("ImGuiInputFlags_Repeat")                  = static_cast<int>(ImGuiInputFlags_Repeat);
    m.attr("ImGuiInputFlags_RouteActive")             = static_cast<int>(ImGuiInputFlags_RouteActive);
    m.attr("ImGuiInputFlags_RouteFocused")            = static_cast<int>(ImGuiInputFlags_RouteFocused);
    m.attr("ImGuiInputFlags_RouteGlobal")             = static_cast<int>(ImGuiInputFlags_RouteGlobal);
  ;
  }

  { // ImGuiInputFlags ImGuiInputFlags_
    m.attr("ImGuiInputFlags_RouteFromRootWindow")     = static_cast<int>(ImGuiInputFlags_RouteFromRootWindow);
    m.attr("ImGuiInputFlags_Tooltip")                 = static_cast<int>(ImGuiInputFlags_Tooltip);
  ;
  }

  { // ImGuiConfigFlags ImGuiConfigFlags_
    m.attr("ImGuiConfigFlags_None")                   = static_cast<int>(ImGuiConfigFlags_None);
    m.attr("ImGuiConfigFlags_NavEnableKeyboard")      = static_cast<int>(ImGuiConfigFlags_NavEnableKeyboard);
    m.attr("ImGuiConfigFlags_NavEnableGamepad")       = static_cast<int>(ImGuiConfigFlags_NavEnableGamepad);
    m.attr("ImGuiConfigFlags_NavEnableSetMousePos")   = static_cast<int>(ImGuiConfigFlags_NavEnableSetMousePos);
    m.attr("ImGuiConfigFlags_NavNoCaptureKeyboard")   = static_cast<int>(ImGuiConfigFlags_NavNoCaptureKeyboard);
  ;
  }

  { // ImGuiConfigFlags ImGuiConfigFlags_
  ;
  }

  { // ImGuiBackendFlags ImGuiBackendFlags_
    m.attr("ImGuiBackendFlags_None")                  = static_cast<int>(ImGuiBackendFlags_None);
    m.attr("ImGuiBackendFlags_HasGamepad")            = static_cast<int>(ImGuiBackendFlags_HasGamepad);
    m.attr("ImGuiBackendFlags_HasMouseCursors")       = static_cast<int>(ImGuiBackendFlags_HasMouseCursors);
    m.attr("ImGuiBackendFlags_HasSetMousePos")        = static_cast<int>(ImGuiBackendFlags_HasSetMousePos);
    m.attr("ImGuiBackendFlags_RendererHasVtxOffset")  = static_cast<int>(ImGuiBackendFlags_RendererHasVtxOffset);
  ;
  }

  { // ImGuiBackendFlags ImGuiBackendFlags_
    m.attr("ImGuiCol_Text")                           = static_cast<int>(ImGuiCol_Text);
    m.attr("ImGuiCol_TextDisabled")                   = static_cast<int>(ImGuiCol_TextDisabled);
    m.attr("ImGuiCol_WindowBg")                       = static_cast<int>(ImGuiCol_WindowBg);
    m.attr("ImGuiCol_ChildBg")                        = static_cast<int>(ImGuiCol_ChildBg);
    m.attr("ImGuiCol_PopupBg")                        = static_cast<int>(ImGuiCol_PopupBg);
  ;
  }

  { // ImGuiCol ImGuiCol_
    m.attr("ImGuiCol_FrameBgActive")                  = static_cast<int>(ImGuiCol_FrameBgActive);
    m.attr("ImGuiCol_TitleBg")                        = static_cast<int>(ImGuiCol_TitleBg);
    m.attr("ImGuiCol_TitleBgActive")                  = static_cast<int>(ImGuiCol_TitleBgActive);
    m.attr("ImGuiCol_TitleBgCollapsed")               = static_cast<int>(ImGuiCol_TitleBgCollapsed);
    m.attr("ImGuiCol_MenuBarBg")                      = static_cast<int>(ImGuiCol_MenuBarBg);
    m.attr("ImGuiCol_ScrollbarBg")                    = static_cast<int>(ImGuiCol_ScrollbarBg);
    m.attr("ImGuiCol_ScrollbarGrab")                  = static_cast<int>(ImGuiCol_ScrollbarGrab);
    m.attr("ImGuiCol_ScrollbarGrabHovered")           = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
    m.attr("ImGuiCol_ScrollbarGrabActive")            = static_cast<int>(ImGuiCol_ScrollbarGrabActive);
    m.attr("ImGuiCol_CheckMark")                      = static_cast<int>(ImGuiCol_CheckMark);
    m.attr("ImGuiCol_SliderGrab")                     = static_cast<int>(ImGuiCol_SliderGrab);
    m.attr("ImGuiCol_SliderGrabActive")               = static_cast<int>(ImGuiCol_SliderGrabActive);
    m.attr("ImGuiCol_Button")                         = static_cast<int>(ImGuiCol_Button);
    m.attr("ImGuiCol_ButtonHovered")                  = static_cast<int>(ImGuiCol_ButtonHovered);
    m.attr("ImGuiCol_ButtonActive")                   = static_cast<int>(ImGuiCol_ButtonActive);
    m.attr("ImGuiCol_Header")                         = static_cast<int>(ImGuiCol_Header);
    m.attr("ImGuiCol_HeaderHovered")                  = static_cast<int>(ImGuiCol_HeaderHovered);
    m.attr("ImGuiCol_HeaderActive")                   = static_cast<int>(ImGuiCol_HeaderActive);
    m.attr("ImGuiCol_Separator")                      = static_cast<int>(ImGuiCol_Separator);
    m.attr("ImGuiCol_SeparatorHovered")               = static_cast<int>(ImGuiCol_SeparatorHovered);
    m.attr("ImGuiCol_SeparatorActive")                = static_cast<int>(ImGuiCol_SeparatorActive);
    m.attr("ImGuiCol_ResizeGrip")                     = static_cast<int>(ImGuiCol_ResizeGrip);
    m.attr("ImGuiCol_ResizeGripHovered")              = static_cast<int>(ImGuiCol_ResizeGripHovered);
    m.attr("ImGuiCol_ResizeGripActive")               = static_cast<int>(ImGuiCol_ResizeGripActive);
    m.attr("ImGuiCol_InputTextCursor")                = static_cast<int>(ImGuiCol_InputTextCursor);
    m.attr("ImGuiCol_TabHovered")                     = static_cast<int>(ImGuiCol_TabHovered);
    m.attr("ImGuiCol_Tab")                            = static_cast<int>(ImGuiCol_Tab);
    m.attr("ImGuiCol_TabSelected")                    = static_cast<int>(ImGuiCol_TabSelected);
    m.attr("ImGuiCol_TabSelectedOverline")            = static_cast<int>(ImGuiCol_TabSelectedOverline);
    m.attr("ImGuiCol_TabDimmed")                      = static_cast<int>(ImGuiCol_TabDimmed);
    m.attr("ImGuiCol_TabDimmedSelected")              = static_cast<int>(ImGuiCol_TabDimmedSelected);
    m.attr("ImGuiCol_TabDimmedSelectedOverline")      = static_cast<int>(ImGuiCol_TabDimmedSelectedOverline);
    m.attr("ImGuiCol_TabUnfocused")                   = static_cast<int>(ImGuiCol_TabUnfocused);
    m.attr("ImGuiCol_TabUnfocusedActive")             = static_cast<int>(ImGuiCol_TabUnfocusedActive);
    m.attr("ImGuiCol_PlotLines")                      = static_cast<int>(ImGuiCol_PlotLines);
    m.attr("ImGuiCol_PlotLinesHovered")               = static_cast<int>(ImGuiCol_PlotLinesHovered);
    m.attr("ImGuiCol_PlotHistogram")                  = static_cast<int>(ImGuiCol_PlotHistogram);
    m.attr("ImGuiCol_PlotHistogramHovered")           = static_cast<int>(ImGuiCol_PlotHistogramHovered);
    m.attr("ImGuiCol_TableHeaderBg")                  = static_cast<int>(ImGuiCol_TableHeaderBg);
    m.attr("ImGuiCol_TableBorderStrong")              = static_cast<int>(ImGuiCol_TableBorderStrong);
    m.attr("ImGuiCol_TableBorderLight")               = static_cast<int>(ImGuiCol_TableBorderLight);
    m.attr("ImGuiCol_TableRowBg")                     = static_cast<int>(ImGuiCol_TableRowBg);
    m.attr("ImGuiCol_TableRowBgAlt")                  = static_cast<int>(ImGuiCol_TableRowBgAlt);
    m.attr("ImGuiCol_TextLink")                       = static_cast<int>(ImGuiCol_TextLink);
    m.attr("ImGuiCol_TextSelectedBg")                 = static_cast<int>(ImGuiCol_TextSelectedBg);
    m.attr("ImGuiCol_DragDropTarget")                 = static_cast<int>(ImGuiCol_DragDropTarget);
    m.attr("ImGuiCol_NavCursor")                      = static_cast<int>(ImGuiCol_NavCursor);
    m.attr("ImGuiCol_NavWindowingHighlight")          = static_cast<int>(ImGuiCol_NavWindowingHighlight);
    m.attr("ImGuiCol_NavWindowingDimBg")              = static_cast<int>(ImGuiCol_NavWindowingDimBg);
    m.attr("ImGuiCol_ModalWindowDimBg")               = static_cast<int>(ImGuiCol_ModalWindowDimBg);
    m.attr("ImGuiCol_COUNT")                          = static_cast<int>(ImGuiCol_COUNT);
  ;
  }

  { // ImGuiStyleVar ImGuiStyleVar_
    m.attr("ImGuiStyleVar_Alpha")                         = static_cast<int>(ImGuiStyleVar_Alpha);
    m.attr("ImGuiStyleVar_DisabledAlpha")                 = static_cast<int>(ImGuiStyleVar_DisabledAlpha);
    m.attr("ImGuiStyleVar_WindowPadding")                 = static_cast<int>(ImGuiStyleVar_WindowPadding);
    m.attr("ImGuiStyleVar_WindowRounding")                = static_cast<int>(ImGuiStyleVar_WindowRounding);
    m.attr("ImGuiStyleVar_WindowBorderSize")              = static_cast<int>(ImGuiStyleVar_WindowBorderSize);
  ;
  }

  { // ImGuiStyleVar ImGuiStyleVar_
    m.attr("ImGuiStyleVar_PopupRounding")                 = static_cast<int>(ImGuiStyleVar_PopupRounding);
    m.attr("ImGuiStyleVar_PopupBorderSize")               = static_cast<int>(ImGuiStyleVar_PopupBorderSize);
    m.attr("ImGuiStyleVar_FramePadding")                  = static_cast<int>(ImGuiStyleVar_FramePadding);
    m.attr("ImGuiStyleVar_FrameRounding")                 = static_cast<int>(ImGuiStyleVar_FrameRounding);
    m.attr("ImGuiStyleVar_FrameBorderSize")               = static_cast<int>(ImGuiStyleVar_FrameBorderSize);
    m.attr("ImGuiStyleVar_ItemSpacing")                   = static_cast<int>(ImGuiStyleVar_ItemSpacing);
    m.attr("ImGuiStyleVar_ItemInnerSpacing")              = static_cast<int>(ImGuiStyleVar_ItemInnerSpacing);
    m.attr("ImGuiStyleVar_IndentSpacing")                 = static_cast<int>(ImGuiStyleVar_IndentSpacing);
    m.attr("ImGuiStyleVar_CellPadding")                   = static_cast<int>(ImGuiStyleVar_CellPadding);
    m.attr("ImGuiStyleVar_ScrollbarSize")                 = static_cast<int>(ImGuiStyleVar_ScrollbarSize);
    m.attr("ImGuiStyleVar_ScrollbarRounding")             = static_cast<int>(ImGuiStyleVar_ScrollbarRounding);
    m.attr("ImGuiStyleVar_ScrollbarPadding")              = static_cast<int>(ImGuiStyleVar_ScrollbarPadding);
    m.attr("ImGuiStyleVar_GrabMinSize")                   = static_cast<int>(ImGuiStyleVar_GrabMinSize);
    m.attr("ImGuiStyleVar_GrabRounding")                  = static_cast<int>(ImGuiStyleVar_GrabRounding);
    m.attr("ImGuiStyleVar_ImageBorderSize")               = static_cast<int>(ImGuiStyleVar_ImageBorderSize);
    m.attr("ImGuiStyleVar_TabRounding")                   = static_cast<int>(ImGuiStyleVar_TabRounding);
    m.attr("ImGuiStyleVar_TabBorderSize")                 = static_cast<int>(ImGuiStyleVar_TabBorderSize);
    m.attr("ImGuiStyleVar_TabMinWidthBase")               = static_cast<int>(ImGuiStyleVar_TabMinWidthBase);
    m.attr("ImGuiStyleVar_TabMinWidthShrink")             = static_cast<int>(ImGuiStyleVar_TabMinWidthShrink);
    m.attr("ImGuiStyleVar_TabBarBorderSize")              = static_cast<int>(ImGuiStyleVar_TabBarBorderSize);
    m.attr("ImGuiStyleVar_TabBarOverlineSize")            = static_cast<int>(ImGuiStyleVar_TabBarOverlineSize);
    m.attr("ImGuiStyleVar_TableAngledHeadersAngle")       = static_cast<int>(ImGuiStyleVar_TableAngledHeadersAngle);
    m.attr("ImGuiStyleVar_TableAngledHeadersTextAlign")   = static_cast<int>(ImGuiStyleVar_TableAngledHeadersTextAlign);
    m.attr("ImGuiStyleVar_TreeLinesSize")                 = static_cast<int>(ImGuiStyleVar_TreeLinesSize);
    m.attr("ImGuiStyleVar_TreeLinesRounding")             = static_cast<int>(ImGuiStyleVar_TreeLinesRounding);
    m.attr("ImGuiStyleVar_ButtonTextAlign")               = static_cast<int>(ImGuiStyleVar_ButtonTextAlign);
    m.attr("ImGuiStyleVar_SelectableTextAlign")           = static_cast<int>(ImGuiStyleVar_SelectableTextAlign);
    m.attr("ImGuiStyleVar_SeparatorTextBorderSize")       = static_cast<int>(ImGuiStyleVar_SeparatorTextBorderSize);
    m.attr("ImGuiStyleVar_SeparatorTextAlign")            = static_cast<int>(ImGuiStyleVar_SeparatorTextAlign);
    m.attr("ImGuiStyleVar_SeparatorTextPadding")          = static_cast<int>(ImGuiStyleVar_SeparatorTextPadding);
  ;
  }

  { // ImGuiButtonFlags ImGuiButtonFlags_
    m.attr("ImGuiButtonFlags_None")                   = static_cast<int>(ImGuiButtonFlags_None);
    m.attr("ImGuiButtonFlags_MouseButtonLeft")        = static_cast<int>(ImGuiButtonFlags_MouseButtonLeft);
    m.attr("ImGuiButtonFlags_MouseButtonRight")       = static_cast<int>(ImGuiButtonFlags_MouseButtonRight);
    m.attr("ImGuiButtonFlags_MouseButtonMiddle")      = static_cast<int>(ImGuiButtonFlags_MouseButtonMiddle);
    m.attr("ImGuiButtonFlags_MouseButtonMask_")       = static_cast<int>(ImGuiButtonFlags_MouseButtonMask_);
  ;
  }

  { // ImGuiButtonFlags ImGuiButtonFlags_
  { // ImGuiColorEditFlags ImGuiColorEditFlags_
    m.attr("ImGuiColorEditFlags_None")                = static_cast<int>(ImGuiColorEditFlags_None);
    m.attr("ImGuiColorEditFlags_NoAlpha")             = static_cast<int>(ImGuiColorEditFlags_NoAlpha);
    m.attr("ImGuiColorEditFlags_NoPicker")            = static_cast<int>(ImGuiColorEditFlags_NoPicker);
    m.attr("ImGuiColorEditFlags_NoOptions")           = static_cast<int>(ImGuiColorEditFlags_NoOptions);
    m.attr("ImGuiColorEditFlags_NoSmallPreview")      = static_cast<int>(ImGuiColorEditFlags_NoSmallPreview);
  ;
  }

  { // ImGuiColorEditFlags ImGuiColorEditFlags_
    m.attr("ImGuiColorEditFlags_NoDragDrop")          = static_cast<int>(ImGuiColorEditFlags_NoDragDrop);
    m.attr("ImGuiColorEditFlags_NoBorder")            = static_cast<int>(ImGuiColorEditFlags_NoBorder);
    m.attr("ImGuiColorEditFlags_AlphaBar")            = static_cast<int>(ImGuiColorEditFlags_AlphaBar);
    m.attr("ImGuiColorEditFlags_AlphaPreview")        = static_cast<int>(ImGuiColorEditFlags_AlphaPreview);
    m.attr("ImGuiColorEditFlags_AlphaPreviewHalf")    = static_cast<int>(ImGuiColorEditFlags_AlphaPreviewHalf);
    m.attr("ImGuiColorEditFlags_HDR")                 = static_cast<int>(ImGuiColorEditFlags_HDR);
    m.attr("ImGuiColorEditFlags_DisplayRGB")          = static_cast<int>(ImGuiColorEditFlags_DisplayRGB);
    m.attr("ImGuiColorEditFlags_DisplayHSV")          = static_cast<int>(ImGuiColorEditFlags_DisplayHSV);
    m.attr("ImGuiColorEditFlags_DisplayHex")          = static_cast<int>(ImGuiColorEditFlags_DisplayHex);
    m.attr("ImGuiColorEditFlags_Uint8")               = static_cast<int>(ImGuiColorEditFlags_Uint8);
    m.attr("ImGuiColorEditFlags_Float")               = static_cast<int>(ImGuiColorEditFlags_Float);
    m.attr("ImGuiColorEditFlags_PickerHueBar")        = static_cast<int>(ImGuiColorEditFlags_PickerHueBar);
    m.attr("ImGuiColorEditFlags_PickerHueWheel")      = static_cast<int>(ImGuiColorEditFlags_PickerHueWheel);
    m.attr("ImGuiColorEditFlags_InputRGB")            = static_cast<int>(ImGuiColorEditFlags_InputRGB);
    m.attr("ImGuiColorEditFlags_InputHSV")            = static_cast<int>(ImGuiColorEditFlags_InputHSV);
  ;
  }

  { // ImGuiSliderFlags ImGuiSliderFlags_
    m.attr("ImGuiSliderFlags_None")                   = static_cast<int>(ImGuiSliderFlags_None);
    m.attr("ImGuiSliderFlags_Logarithmic")            = static_cast<int>(ImGuiSliderFlags_Logarithmic);
    m.attr("ImGuiSliderFlags_NoRoundToFormat")        = static_cast<int>(ImGuiSliderFlags_NoRoundToFormat);
    m.attr("ImGuiSliderFlags_NoInput")                = static_cast<int>(ImGuiSliderFlags_NoInput);
    m.attr("ImGuiSliderFlags_WrapAround")             = static_cast<int>(ImGuiSliderFlags_WrapAround);
  ;
  }

  { // ImGuiSliderFlags ImGuiSliderFlags_
    m.attr("ImGuiSliderFlags_InvalidMask_")           = static_cast<int>(ImGuiSliderFlags_InvalidMask_);
  ;
  }

  { // ImGuiMouseButton ImGuiMouseButton_
    m.attr("ImGuiMouseButton_Left")                   = static_cast<int>(ImGuiMouseButton_Left);
    m.attr("ImGuiMouseButton_Right")                  = static_cast<int>(ImGuiMouseButton_Right);
    m.attr("ImGuiMouseButton_Middle")                 = static_cast<int>(ImGuiMouseButton_Middle);
    m.attr("ImGuiMouseButton_COUNT")                  = static_cast<int>(ImGuiMouseButton_COUNT);
  ;
  ;
  }

  { // ImGuiMouseButton ImGuiMouseButton_
    m.attr("ImGuiMouseCursor_Arrow")                  = static_cast<int>(ImGuiMouseCursor_Arrow);
    m.attr("ImGuiMouseCursor_TextInput")              = static_cast<int>(ImGuiMouseCursor_TextInput);
    m.attr("ImGuiMouseCursor_ResizeAll")              = static_cast<int>(ImGuiMouseCursor_ResizeAll);
    m.attr("ImGuiMouseCursor_ResizeNS")               = static_cast<int>(ImGuiMouseCursor_ResizeNS);
  ;
  }

  { // ImGuiMouseCursor ImGuiMouseCursor_
    m.attr("ImGuiMouseCursor_NotAllowed")             = static_cast<int>(ImGuiMouseCursor_NotAllowed);
    m.attr("ImGuiMouseCursor_COUNT")                  = static_cast<int>(ImGuiMouseCursor_COUNT);
  ;
  }

  { // ImGuiMouseSource ImGuiMouseSource
  auto e = nb::enum_<ImGuiMouseSource>(m, "ImGuiMouseSource");
    e.value("ImGuiMouseSource_Mouse",                  ImGuiMouseSource_Mouse);                  m.attr("ImGuiMouseSource_Mouse")                  = ImGuiMouseSource_::ImGuiMouseSource_Mouse;
    e.value("ImGuiMouseSource_TouchScreen",            ImGuiMouseSource_TouchScreen);            m.attr("ImGuiMouseSource_TouchScreen")            = ImGuiMouseSource_::ImGuiMouseSource_TouchScreen;
    e.value("ImGuiMouseSource_Pen",                    ImGuiMouseSource_Pen);                    m.attr("ImGuiMouseSource_Pen")                    = ImGuiMouseSource_::ImGuiMouseSource_Pen;
    e.value("ImGuiMouseSource_COUNT",                  ImGuiMouseSource_COUNT);                  m.attr("ImGuiMouseSource_COUNT")                  = ImGuiMouseSource_::ImGuiMouseSource_COUNT;
  ;
  }

  { // ImGuiMouseSource ImGuiMouseSource
    m.attr("ImGuiCond_Once")                          = static_cast<int>(ImGuiCond_Once);
    m.attr("ImGuiCond_FirstUseEver")                  = static_cast<int>(ImGuiCond_FirstUseEver);
    m.attr("ImGuiCond_Appearing")                     = static_cast<int>(ImGuiCond_Appearing);
  ;
  ;
  }

  { // ImGuiCond ImGuiCond_
    m.attr("ImGuiTableFlags_Resizable")               = static_cast<int>(ImGuiTableFlags_Resizable);
    m.attr("ImGuiTableFlags_Reorderable")             = static_cast<int>(ImGuiTableFlags_Reorderable);
    m.attr("ImGuiTableFlags_Hideable")                = static_cast<int>(ImGuiTableFlags_Hideable);
    m.attr("ImGuiTableFlags_Sortable")                = static_cast<int>(ImGuiTableFlags_Sortable);
  ;
  }

  { // ImGuiTableFlags ImGuiTableFlags_
    m.attr("ImGuiTableFlags_BordersOuterH")           = static_cast<int>(ImGuiTableFlags_BordersOuterH);
    m.attr("ImGuiTableFlags_BordersInnerV")           = static_cast<int>(ImGuiTableFlags_BordersInnerV);
    m.attr("ImGuiTableFlags_BordersOuterV")           = static_cast<int>(ImGuiTableFlags_BordersOuterV);
    m.attr("ImGuiTableFlags_BordersH")                = static_cast<int>(ImGuiTableFlags_BordersH);
    m.attr("ImGuiTableFlags_BordersV")                = static_cast<int>(ImGuiTableFlags_BordersV);
    m.attr("ImGuiTableFlags_BordersInner")            = static_cast<int>(ImGuiTableFlags_BordersInner);
    m.attr("ImGuiTableFlags_BordersOuter")            = static_cast<int>(ImGuiTableFlags_BordersOuter);
    m.attr("ImGuiTableFlags_Borders")                 = static_cast<int>(ImGuiTableFlags_Borders);
    m.attr("ImGuiTableFlags_NoBordersInBody")         = static_cast<int>(ImGuiTableFlags_NoBordersInBody);
    m.attr("ImGuiTableFlags_NoBordersInBodyUntilResize") = static_cast<int>(ImGuiTableFlags_NoBordersInBodyUntilResize);
    m.attr("ImGuiTableFlags_SizingFixedFit")          = static_cast<int>(ImGuiTableFlags_SizingFixedFit);
    m.attr("ImGuiTableFlags_SizingFixedSame")         = static_cast<int>(ImGuiTableFlags_SizingFixedSame);
    m.attr("ImGuiTableFlags_SizingStretchProp")       = static_cast<int>(ImGuiTableFlags_SizingStretchProp);
    m.attr("ImGuiTableFlags_SizingStretchSame")       = static_cast<int>(ImGuiTableFlags_SizingStretchSame);
    m.attr("ImGuiTableFlags_NoHostExtendX")           = static_cast<int>(ImGuiTableFlags_NoHostExtendX);
    m.attr("ImGuiTableFlags_NoHostExtendY")           = static_cast<int>(ImGuiTableFlags_NoHostExtendY);
    m.attr("ImGuiTableFlags_NoKeepColumnsVisible")    = static_cast<int>(ImGuiTableFlags_NoKeepColumnsVisible);
    m.attr("ImGuiTableFlags_PreciseWidths")           = static_cast<int>(ImGuiTableFlags_PreciseWidths);
    m.attr("ImGuiTableFlags_NoClip")                  = static_cast<int>(ImGuiTableFlags_NoClip);
    m.attr("ImGuiTableFlags_PadOuterX")               = static_cast<int>(ImGuiTableFlags_PadOuterX);
    m.attr("ImGuiTableFlags_NoPadOuterX")             = static_cast<int>(ImGuiTableFlags_NoPadOuterX);
    m.attr("ImGuiTableFlags_NoPadInnerX")             = static_cast<int>(ImGuiTableFlags_NoPadInnerX);
    m.attr("ImGuiTableFlags_ScrollX")                 = static_cast<int>(ImGuiTableFlags_ScrollX);
    m.attr("ImGuiTableFlags_ScrollY")                 = static_cast<int>(ImGuiTableFlags_ScrollY);
    m.attr("ImGuiTableFlags_SortMulti")               = static_cast<int>(ImGuiTableFlags_SortMulti);
    m.attr("ImGuiTableFlags_SortTristate")            = static_cast<int>(ImGuiTableFlags_SortTristate);
    m.attr("ImGuiTableFlags_HighlightHoveredColumn")  = static_cast<int>(ImGuiTableFlags_HighlightHoveredColumn);
  ;
  }

  { // ImGuiTableColumnFlags ImGuiTableColumnFlags_
    m.attr("ImGuiTableColumnFlags_None")              = static_cast<int>(ImGuiTableColumnFlags_None);
    m.attr("ImGuiTableColumnFlags_Disabled")          = static_cast<int>(ImGuiTableColumnFlags_Disabled);
    m.attr("ImGuiTableColumnFlags_DefaultHide")       = static_cast<int>(ImGuiTableColumnFlags_DefaultHide);
    m.attr("ImGuiTableColumnFlags_DefaultSort")       = static_cast<int>(ImGuiTableColumnFlags_DefaultSort);
    m.attr("ImGuiTableColumnFlags_WidthStretch")      = static_cast<int>(ImGuiTableColumnFlags_WidthStretch);
  ;
  }

  { // ImGuiTableColumnFlags ImGuiTableColumnFlags_
    m.attr("ImGuiTableColumnFlags_NoClip")            = static_cast<int>(ImGuiTableColumnFlags_NoClip);
    m.attr("ImGuiTableColumnFlags_NoSort")            = static_cast<int>(ImGuiTableColumnFlags_NoSort);
    m.attr("ImGuiTableColumnFlags_NoSortAscending")   = static_cast<int>(ImGuiTableColumnFlags_NoSortAscending);
    m.attr("ImGuiTableColumnFlags_NoSortDescending")  = static_cast<int>(ImGuiTableColumnFlags_NoSortDescending);
    m.attr("ImGuiTableColumnFlags_NoHeaderLabel")     = static_cast<int>(ImGuiTableColumnFlags_NoHeaderLabel);
    m.attr("ImGuiTableColumnFlags_NoHeaderWidth")     = static_cast<int>(ImGuiTableColumnFlags_NoHeaderWidth);
    m.attr("ImGuiTableColumnFlags_PreferSortAscending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortAscending);
    m.attr("ImGuiTableColumnFlags_PreferSortDescending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortDescending);
    m.attr("ImGuiTableColumnFlags_IndentEnable")      = static_cast<int>(ImGuiTableColumnFlags_IndentEnable);
    m.attr("ImGuiTableColumnFlags_IndentDisable")     = static_cast<int>(ImGuiTableColumnFlags_IndentDisable);
    m.attr("ImGuiTableColumnFlags_AngledHeader")      = static_cast<int>(ImGuiTableColumnFlags_AngledHeader);
    m.attr("ImGuiTableColumnFlags_IsEnabled")         = static_cast<int>(ImGuiTableColumnFlags_IsEnabled);
    m.attr("ImGuiTableColumnFlags_IsVisible")         = static_cast<int>(ImGuiTableColumnFlags_IsVisible);
    m.attr("ImGuiTableColumnFlags_IsSorted")          = static_cast<int>(ImGuiTableColumnFlags_IsSorted);
    m.attr("ImGuiTableColumnFlags_IsHovered")         = static_cast<int>(ImGuiTableColumnFlags_IsHovered);
  ;
  }

  { // ImGuiTableRowFlags ImGuiTableRowFlags_
    m.attr("ImGuiTableRowFlags_None")                 = static_cast<int>(ImGuiTableRowFlags_None);
    m.attr("ImGuiTableRowFlags_Headers")              = static_cast<int>(ImGuiTableRowFlags_Headers);
  ;
  }

  ;
  }

  { // ImGuiTableRowFlags ImGuiTableRowFlags_
    m.attr("ImGuiTableBgTarget_CellBg")               = static_cast<int>(ImGuiTableBgTarget_CellBg);
  ;
  }

  { // ImGuiTableBgTarget ImGuiTableBgTarget_
    m.attr("ImDrawFlags_Closed")                      = static_cast<int>(ImDrawFlags_Closed);
    m.attr("ImDrawFlags_RoundCornersTopLeft")         = static_cast<int>(ImDrawFlags_RoundCornersTopLeft);
    m.attr("ImDrawFlags_RoundCornersTopRight")        = static_cast<int>(ImDrawFlags_RoundCornersTopRight);
    m.attr("ImDrawFlags_RoundCornersBottomLeft")      = static_cast<int>(ImDrawFlags_RoundCornersBottomLeft);
  ;
  }

  { // ImDrawFlags ImDrawFlags_
    m.attr("ImDrawFlags_RoundCornersLeft")            = static_cast<int>(ImDrawFlags_RoundCornersLeft);
    m.attr("ImDrawFlags_RoundCornersRight")           = static_cast<int>(ImDrawFlags_RoundCornersRight);
    m.attr("ImDrawFlags_RoundCornersAll")             = static_cast<int>(ImDrawFlags_RoundCornersAll);
  ;
  }

  { // ImGuiKey ImGuiKey
  auto e = nb::enum_<ImGuiKey>(m, "ImGuiKey");
    e.value("ImGuiKey_None",                           ImGuiKey_None);                           m.attr("ImGuiKey_None")                           = ImGuiKey::ImGuiKey_None;
    e.value("ImGuiKey_Tab",                            ImGuiKey_Tab);                            m.attr("ImGuiKey_Tab")                            = ImGuiKey::ImGuiKey_Tab;
    e.value("ImGuiKey_LeftArrow",                      ImGuiKey_LeftArrow);                      m.attr("ImGuiKey_LeftArrow")                      = ImGuiKey::ImGuiKey_LeftArrow;
    e.value("ImGuiKey_RightArrow",                     ImGuiKey_RightArrow);                     m.attr("ImGuiKey_RightArrow")                     = ImGuiKey::ImGuiKey_RightArrow;
    e.value("ImGuiKey_UpArrow",                        ImGuiKey_UpArrow);                        m.attr("ImGuiKey_UpArrow")                        = ImGuiKey::ImGuiKey_UpArrow;
    e.value("ImGuiKey_DownArrow",                      ImGuiKey_DownArrow);                      m.attr("ImGuiKey_DownArrow")                      = ImGuiKey::ImGuiKey_DownArrow;
    e.value("ImGuiKey_PageUp",                         ImGuiKey_PageUp);                         m.attr("ImGuiKey_PageUp")                         = ImGuiKey::ImGuiKey_PageUp;
    e.value("ImGuiKey_PageDown",                       ImGuiKey_PageDown);                       m.attr("ImGuiKey_PageDown")                       = ImGuiKey::ImGuiKey_PageDown;
    e.value("ImGuiKey_Home",                           ImGuiKey_Home);                           m.attr("ImGuiKey_Home")                           = ImGuiKey::ImGuiKey_Home;
    e.value("ImGuiKey_End",                            ImGuiKey_End);                            m.attr("ImGuiKey_End")                            = ImGuiKey::ImGuiKey_End;
    e.value("ImGuiKey_Insert",                         ImGuiKey_Insert);                         m.attr("ImGuiKey_Insert")                         = ImGuiKey::ImGuiKey_Insert;
    e.value("ImGuiKey_Delete",                         ImGuiKey_Delete);                         m.attr("ImGuiKey_Delete")                         = ImGuiKey::ImGuiKey_Delete;
    e.value("ImGuiKey_Backspace",                      ImGuiKey_Backspace);                      m.attr("ImGuiKey_Backspace")                      = ImGuiKey::ImGuiKey_Backspace;
    e.value("ImGuiKey_Space",                          ImGuiKey_Space);                          m.attr("ImGuiKey_Space")                          = ImGuiKey::ImGuiKey_Space;
    e.value("ImGuiKey_Enter",                          ImGuiKey_Enter);                          m.attr("ImGuiKey_Enter")                          = ImGuiKey::ImGuiKey_Enter;
    e.value("ImGuiKey_Escape",                         ImGuiKey_Escape);                         m.attr("ImGuiKey_Escape")                         = ImGuiKey::ImGuiKey_Escape;
    e.value("ImGuiKey_LeftCtrl",                       ImGuiKey_LeftCtrl);                       m.attr("ImGuiKey_LeftCtrl")                       = ImGuiKey::ImGuiKey_LeftCtrl;
    e.value("ImGuiKey_LeftShift",                      ImGuiKey_LeftShift);                      m.attr("ImGuiKey_LeftShift")                      = ImGuiKey::ImGuiKey_LeftShift;
    e.value("ImGuiKey_LeftAlt",                        ImGuiKey_LeftAlt);                        m.attr("ImGuiKey_LeftAlt")                        = ImGuiKey::ImGuiKey_LeftAlt;
    e.value("ImGuiKey_LeftSuper",                      ImGuiKey_LeftSuper);                      m.attr("ImGuiKey_LeftSuper")                      = ImGuiKey::ImGuiKey_LeftSuper;
    e.value("ImGuiKey_RightCtrl",                      ImGuiKey_RightCtrl);                      m.attr("ImGuiKey_RightCtrl")                      = ImGuiKey::ImGuiKey_RightCtrl;
    e.value("ImGuiKey_RightShift",                     ImGuiKey_RightShift);                     m.attr("ImGuiKey_RightShift")                     = ImGuiKey::ImGuiKey_RightShift;
    e.value("ImGuiKey_RightAlt",                       ImGuiKey_RightAlt);                       m.attr("ImGuiKey_RightAlt")                       = ImGuiKey::ImGuiKey_RightAlt;
    e.value("ImGuiKey_RightSuper",                     ImGuiKey_RightSuper);                     m.attr("ImGuiKey_RightSuper")                     = ImGuiKey::ImGuiKey_RightSuper;
    e.value("ImGuiKey_Menu",                           ImGuiKey_Menu);                           m.attr("ImGuiKey_Menu")                           = ImGuiKey::ImGuiKey_Menu;
    e.value("ImGuiKey_0",                              ImGuiKey_0);                              m.attr("ImGuiKey_0")                              = ImGuiKey::ImGuiKey_0;
    e.value("ImGuiKey_1",                              ImGuiKey_1);                              m.attr("ImGuiKey_1")                              = ImGuiKey::ImGuiKey_1;
    e.value("ImGuiKey_2",                              ImGuiKey_2);                              m.attr("ImGuiKey_2")                              = ImGuiKey::ImGuiKey_2;
    e.value("ImGuiKey_3",                              ImGuiKey_3);                              m.attr("ImGuiKey_3")                              = ImGuiKey::ImGuiKey_3;
    e.value("ImGuiKey_4",                              ImGuiKey_4);                              m.attr("ImGuiKey_4")                              = ImGuiKey::ImGuiKey_4;
    e.value("ImGuiKey_5",                              ImGuiKey_5);                              m.attr("ImGuiKey_5")                              = ImGuiKey::ImGuiKey_5;
    e.value("ImGuiKey_6",                              ImGuiKey_6);                              m.attr("ImGuiKey_6")                              = ImGuiKey::ImGuiKey_6;
    e.value("ImGuiKey_7",                              ImGuiKey_7);                              m.attr("ImGuiKey_7")                              = ImGuiKey::ImGuiKey_7;
    e.value("ImGuiKey_8",                              ImGuiKey_8);                              m.attr("ImGuiKey_8")                              = ImGuiKey::ImGuiKey_8;
    e.value("ImGuiKey_9",                              ImGuiKey_9);                              m.attr("ImGuiKey_9")                              = ImGuiKey::ImGuiKey_9;
    e.value("ImGuiKey_A",                              ImGuiKey_A);                              m.attr("ImGuiKey_A")                              = ImGuiKey::ImGuiKey_A;
    e.value("ImGuiKey_B",                              ImGuiKey_B);                              m.attr("ImGuiKey_B")                              = ImGuiKey::ImGuiKey_B;
    e.value("ImGuiKey_C",                              ImGuiKey_C);                              m.attr("ImGuiKey_C")                              = ImGuiKey::ImGuiKey_C;
    e.value("ImGuiKey_D",                              ImGuiKey_D);                              m.attr("ImGuiKey_D")                              = ImGuiKey::ImGuiKey_D;
    e.value("ImGuiKey_E",                              ImGuiKey_E);                              m.attr("ImGuiKey_E")                              = ImGuiKey::ImGuiKey_E;
    e.value("ImGuiKey_F",                              ImGuiKey_F);                              m.attr("ImGuiKey_F")                              = ImGuiKey::ImGuiKey_F;
    e.value("ImGuiKey_G",                              ImGuiKey_G);                              m.attr("ImGuiKey_G")                              = ImGuiKey::ImGuiKey_G;
    e.value("ImGuiKey_H",                              ImGuiKey_H);                              m.attr("ImGuiKey_H")                              = ImGuiKey::ImGuiKey_H;
    e.value("ImGuiKey_I",                              ImGuiKey_I);                              m.attr("ImGuiKey_I")                              = ImGuiKey::ImGuiKey_I;
    e.value("ImGuiKey_J",                              ImGuiKey_J);                              m.attr("ImGuiKey_J")                              = ImGuiKey::ImGuiKey_J;
    e.value("ImGuiKey_K",                              ImGuiKey_K);                              m.attr("ImGuiKey_K")                              = ImGuiKey::ImGuiKey_K;
    e.value("ImGuiKey_L",                              ImGuiKey_L);                              m.attr("ImGuiKey_L")                              = ImGuiKey::ImGuiKey_L;
    e.value("ImGuiKey_M",                              ImGuiKey_M);                              m.attr("ImGuiKey_M")                              = ImGuiKey::ImGuiKey_M;
    e.value("ImGuiKey_N",                              ImGuiKey_N);                              m.attr("ImGuiKey_N")                              = ImGuiKey::ImGuiKey_N;
    e.value("ImGuiKey_O",                              ImGuiKey_O);                              m.attr("ImGuiKey_O")                              = ImGuiKey::ImGuiKey_O;
    e.value("ImGuiKey_P",                              ImGuiKey_P);                              m.attr("ImGuiKey_P")                              = ImGuiKey::ImGuiKey_P;
    e.value("ImGuiKey_Q",                              ImGuiKey_Q);                              m.attr("ImGuiKey_Q")                              = ImGuiKey::ImGuiKey_Q;
    e.value("ImGuiKey_R",                              ImGuiKey_R);                              m.attr("ImGuiKey_R")                              = ImGuiKey::ImGuiKey_R;
    e.value("ImGuiKey_S",                              ImGuiKey_S);                              m.attr("ImGuiKey_S")                              = ImGuiKey::ImGuiKey_S;
    e.value("ImGuiKey_T",                              ImGuiKey_T);                              m.attr("ImGuiKey_T")                              = ImGuiKey::ImGuiKey_T;
    e.value("ImGuiKey_U",                              ImGuiKey_U);                              m.attr("ImGuiKey_U")                              = ImGuiKey::ImGuiKey_U;
    e.value("ImGuiKey_V",                              ImGuiKey_V);                              m.attr("ImGuiKey_V")                              = ImGuiKey::ImGuiKey_V;
    e.value("ImGuiKey_W",                              ImGuiKey_W);                              m.attr("ImGuiKey_W")                              = ImGuiKey::ImGuiKey_W;
    e.value("ImGuiKey_X",                              ImGuiKey_X);                              m.attr("ImGuiKey_X")                              = ImGuiKey::ImGuiKey_X;
    e.value("ImGuiKey_Y",                              ImGuiKey_Y);                              m.attr("ImGuiKey_Y")                              = ImGuiKey::ImGuiKey_Y;
    e.value("ImGuiKey_Z",                              ImGuiKey_Z);                              m.attr("ImGuiKey_Z")                              = ImGuiKey::ImGuiKey_Z;
    e.value("ImGuiKey_F1",                             ImGuiKey_F1);                             m.attr("ImGuiKey_F1")                             = ImGuiKey::ImGuiKey_F1;
    e.value("ImGuiKey_F2",                             ImGuiKey_F2);                             m.attr("ImGuiKey_F2")                             = ImGuiKey::ImGuiKey_F2;
    e.value("ImGuiKey_F3",                             ImGuiKey_F3);                             m.attr("ImGuiKey_F3")                             = ImGuiKey::ImGuiKey_F3;
    e.value("ImGuiKey_F4",                             ImGuiKey_F4);                             m.attr("ImGuiKey_F4")                             = ImGuiKey::ImGuiKey_F4;
    e.value("ImGuiKey_F5",                             ImGuiKey_F5);                             m.attr("ImGuiKey_F5")                             = ImGuiKey::ImGuiKey_F5;
    e.value("ImGuiKey_F6",                             ImGuiKey_F6);                             m.attr("ImGuiKey_F6")                             = ImGuiKey::ImGuiKey_F6;
    e.value("ImGuiKey_F7",                             ImGuiKey_F7);                             m.attr("ImGuiKey_F7")                             = ImGuiKey::ImGuiKey_F7;
    e.value("ImGuiKey_F8",                             ImGuiKey_F8);                             m.attr("ImGuiKey_F8")                             = ImGuiKey::ImGuiKey_F8;
    e.value("ImGuiKey_F9",                             ImGuiKey_F9);                             m.attr("ImGuiKey_F9")                             = ImGuiKey::ImGuiKey_F9;
    e.value("ImGuiKey_F10",                            ImGuiKey_F10);                            m.attr("ImGuiKey_F10")                            = ImGuiKey::ImGuiKey_F10;
    e.value("ImGuiKey_F11",                            ImGuiKey_F11);                            m.attr("ImGuiKey_F11")                            = ImGuiKey::ImGuiKey_F11;
    e.value("ImGuiKey_F12",                            ImGuiKey_F12);                            m.attr("ImGuiKey_F12")                            = ImGuiKey::ImGuiKey_F12;
    e.value("ImGuiKey_F13",                            ImGuiKey_F13);                            m.attr("ImGuiKey_F13")                            = ImGuiKey::ImGuiKey_F13;
    e.value("ImGuiKey_F14",                            ImGuiKey_F14);                            m.attr("ImGuiKey_F14")                            = ImGuiKey::ImGuiKey_F14;
    e.value("ImGuiKey_F15",                            ImGuiKey_F15);                            m.attr("ImGuiKey_F15")                            = ImGuiKey::ImGuiKey_F15;
    e.value("ImGuiKey_F16",                            ImGuiKey_F16);                            m.attr("ImGuiKey_F16")                            = ImGuiKey::ImGuiKey_F16;
    e.value("ImGuiKey_F17",                            ImGuiKey_F17);                            m.attr("ImGuiKey_F17")                            = ImGuiKey::ImGuiKey_F17;
    e.value("ImGuiKey_F18",                            ImGuiKey_F18);                            m.attr("ImGuiKey_F18")                            = ImGuiKey::ImGuiKey_F18;
    e.value("ImGuiKey_F19",                            ImGuiKey_F19);                            m.attr("ImGuiKey_F19")                            = ImGuiKey::ImGuiKey_F19;
    e.value("ImGuiKey_F20",                            ImGuiKey_F20);                            m.attr("ImGuiKey_F20")                            = ImGuiKey::ImGuiKey_F20;
    e.value("ImGuiKey_F21",                            ImGuiKey_F21);                            m.attr("ImGuiKey_F21")                            = ImGuiKey::ImGuiKey_F21;
    e.value("ImGuiKey_F22",                            ImGuiKey_F22);                            m.attr("ImGuiKey_F22")                            = ImGuiKey::ImGuiKey_F22;
    e.value("ImGuiKey_F23",                            ImGuiKey_F23);                            m.attr("ImGuiKey_F23")                            = ImGuiKey::ImGuiKey_F23;
    e.value("ImGuiKey_F24",                            ImGuiKey_F24);                            m.attr("ImGuiKey_F24")                            = ImGuiKey::ImGuiKey_F24;
    e.value("ImGuiKey_Apostrophe",                     ImGuiKey_Apostrophe);                     m.attr("ImGuiKey_Apostrophe")                     = ImGuiKey::ImGuiKey_Apostrophe;
    e.value("ImGuiKey_Comma",                          ImGuiKey_Comma);                          m.attr("ImGuiKey_Comma")                          = ImGuiKey::ImGuiKey_Comma;
    e.value("ImGuiKey_Minus",                          ImGuiKey_Minus);                          m.attr("ImGuiKey_Minus")                          = ImGuiKey::ImGuiKey_Minus;
    e.value("ImGuiKey_Period",                         ImGuiKey_Period);                         m.attr("ImGuiKey_Period")                         = ImGuiKey::ImGuiKey_Period;
    e.value("ImGuiKey_Slash",                          ImGuiKey_Slash);                          m.attr("ImGuiKey_Slash")                          = ImGuiKey::ImGuiKey_Slash;
    e.value("ImGuiKey_Semicolon",                      ImGuiKey_Semicolon);                      m.attr("ImGuiKey_Semicolon")                      = ImGuiKey::ImGuiKey_Semicolon;
    e.value("ImGuiKey_Equal",                          ImGuiKey_Equal);                          m.attr("ImGuiKey_Equal")                          = ImGuiKey::ImGuiKey_Equal;
    e.value("ImGuiKey_LeftBracket",                    ImGuiKey_LeftBracket);                    m.attr("ImGuiKey_LeftBracket")                    = ImGuiKey::ImGuiKey_LeftBracket;
    e.value("ImGuiKey_Backslash",                      ImGuiKey_Backslash);                      m.attr("ImGuiKey_Backslash")                      = ImGuiKey::ImGuiKey_Backslash;
    e.value("ImGuiKey_RightBracket",                   ImGuiKey_RightBracket);                   m.attr("ImGuiKey_RightBracket")                   = ImGuiKey::ImGuiKey_RightBracket;
    e.value("ImGuiKey_GraveAccent",                    ImGuiKey_GraveAccent);                    m.attr("ImGuiKey_GraveAccent")                    = ImGuiKey::ImGuiKey_GraveAccent;
    e.value("ImGuiKey_CapsLock",                       ImGuiKey_CapsLock);                       m.attr("ImGuiKey_CapsLock")                       = ImGuiKey::ImGuiKey_CapsLock;
    e.value("ImGuiKey_ScrollLock",                     ImGuiKey_ScrollLock);                     m.attr("ImGuiKey_ScrollLock")                     = ImGuiKey::ImGuiKey_ScrollLock;
    e.value("ImGuiKey_NumLock",                        ImGuiKey_NumLock);                        m.attr("ImGuiKey_NumLock")                        = ImGuiKey::ImGuiKey_NumLock;
    e.value("ImGuiKey_PrintScreen",                    ImGuiKey_PrintScreen);                    m.attr("ImGuiKey_PrintScreen")                    = ImGuiKey::ImGuiKey_PrintScreen;
    e.value("ImGuiKey_Pause",                          ImGuiKey_Pause);                          m.attr("ImGuiKey_Pause")                          = ImGuiKey::ImGuiKey_Pause;
    e.value("ImGuiKey_Keypad0",                        ImGuiKey_Keypad0);                        m.attr("ImGuiKey_Keypad0")                        = ImGuiKey::ImGuiKey_Keypad0;
    e.value("ImGuiKey_Keypad1",                        ImGuiKey_Keypad1);                        m.attr("ImGuiKey_Keypad1")                        = ImGuiKey::ImGuiKey_Keypad1;
    e.value("ImGuiKey_Keypad2",                        ImGuiKey_Keypad2);                        m.attr("ImGuiKey_Keypad2")                        = ImGuiKey::ImGuiKey_Keypad2;
    e.value("ImGuiKey_Keypad3",                        ImGuiKey_Keypad3);                        m.attr("ImGuiKey_Keypad3")                        = ImGuiKey::ImGuiKey_Keypad3;
    e.value("ImGuiKey_Keypad4",                        ImGuiKey_Keypad4);                        m.attr("ImGuiKey_Keypad4")                        = ImGuiKey::ImGuiKey_Keypad4;
    e.value("ImGuiKey_Keypad5",                        ImGuiKey_Keypad5);                        m.attr("ImGuiKey_Keypad5")                        = ImGuiKey::ImGuiKey_Keypad5;
    e.value("ImGuiKey_Keypad6",                        ImGuiKey_Keypad6);                        m.attr("ImGuiKey_Keypad6")                        = ImGuiKey::ImGuiKey_Keypad6;
    e.value("ImGuiKey_Keypad7",                        ImGuiKey_Keypad7);                        m.attr("ImGuiKey_Keypad7")                        = ImGuiKey::ImGuiKey_Keypad7;
    e.value("ImGuiKey_Keypad8",                        ImGuiKey_Keypad8);                        m.attr("ImGuiKey_Keypad8")                        = ImGuiKey::ImGuiKey_Keypad8;
    e.value("ImGuiKey_Keypad9",                        ImGuiKey_Keypad9);                        m.attr("ImGuiKey_Keypad9")                        = ImGuiKey::ImGuiKey_Keypad9;
    e.value("ImGuiKey_KeypadDecimal",                  ImGuiKey_KeypadDecimal);                  m.attr("ImGuiKey_KeypadDecimal")                  = ImGuiKey::ImGuiKey_KeypadDecimal;
    e.value("ImGuiKey_KeypadDivide",                   ImGuiKey_KeypadDivide);                   m.attr("ImGuiKey_KeypadDivide")                   = ImGuiKey::ImGuiKey_KeypadDivide;
    e.value("ImGuiKey_KeypadMultiply",                 ImGuiKey_KeypadMultiply);                 m.attr("ImGuiKey_KeypadMultiply")                 = ImGuiKey::ImGuiKey_KeypadMultiply;
    e.value("ImGuiKey_KeypadSubtract",                 ImGuiKey_KeypadSubtract);                 m.attr("ImGuiKey_KeypadSubtract")                 = ImGuiKey::ImGuiKey_KeypadSubtract;
    e.value("ImGuiKey_KeypadAdd",                      ImGuiKey_KeypadAdd);                      m.attr("ImGuiKey_KeypadAdd")                      = ImGuiKey::ImGuiKey_KeypadAdd;
    e.value("ImGuiKey_KeypadEnter",                    ImGuiKey_KeypadEnter);                    m.attr("ImGuiKey_KeypadEnter")                    = ImGuiKey::ImGuiKey_KeypadEnter;
    e.value("ImGuiKey_KeypadEqual",                    ImGuiKey_KeypadEqual);                    m.attr("ImGuiKey_KeypadEqual")                    = ImGuiKey::ImGuiKey_KeypadEqual;
    e.value("ImGuiKey_AppBack",                        ImGuiKey_AppBack);                        m.attr("ImGuiKey_AppBack")                        = ImGuiKey::ImGuiKey_AppBack;
    e.value("ImGuiKey_AppForward",                     ImGuiKey_AppForward);                     m.attr("ImGuiKey_AppForward")                     = ImGuiKey::ImGuiKey_AppForward;
    e.value("ImGuiKey_GamepadStart",                   ImGuiKey_GamepadStart);                   m.attr("ImGuiKey_GamepadStart")                   = ImGuiKey::ImGuiKey_GamepadStart;
    e.value("ImGuiKey_GamepadBack",                    ImGuiKey_GamepadBack);                    m.attr("ImGuiKey_GamepadBack")                    = ImGuiKey::ImGuiKey_GamepadBack;
    e.value("ImGuiKey_GamepadFaceUp",                  ImGuiKey_GamepadFaceUp);                  m.attr("ImGuiKey_GamepadFaceUp")                  = ImGuiKey::ImGuiKey_GamepadFaceUp;
    e.value("ImGuiKey_GamepadFaceDown",                ImGuiKey_GamepadFaceDown);                m.attr("ImGuiKey_GamepadFaceDown")                = ImGuiKey::ImGuiKey_GamepadFaceDown;
    e.value("ImGuiKey_GamepadFaceLeft",                ImGuiKey_GamepadFaceLeft);                m.attr("ImGuiKey_GamepadFaceLeft")                = ImGuiKey::ImGuiKey_GamepadFaceLeft;
    e.value("ImGuiKey_GamepadFaceRight",               ImGuiKey_GamepadFaceRight);               m.attr("ImGuiKey_GamepadFaceRight")               = ImGuiKey::ImGuiKey_GamepadFaceRight;
    e.value("ImGuiKey_GamepadDpadUp",                  ImGuiKey_GamepadDpadUp);                  m.attr("ImGuiKey_GamepadDpadUp")                  = ImGuiKey::ImGuiKey_GamepadDpadUp;
    e.value("ImGuiKey_GamepadDpadDown",                ImGuiKey_GamepadDpadDown);                m.attr("ImGuiKey_GamepadDpadDown")                = ImGuiKey::ImGuiKey_GamepadDpadDown;
    e.value("ImGuiKey_GamepadDpadLeft",                ImGuiKey_GamepadDpadLeft);                m.attr("ImGuiKey_GamepadDpadLeft")                = ImGuiKey::ImGuiKey_GamepadDpadLeft;
    e.value("ImGuiKey_GamepadDpadRight",               ImGuiKey_GamepadDpadRight);               m.attr("ImGuiKey_GamepadDpadRight")               = ImGuiKey::ImGuiKey_GamepadDpadRight;
    e.value("ImGuiKey_GamepadL1",                      ImGuiKey_GamepadL1);                      m.attr("ImGuiKey_GamepadL1")                      = ImGuiKey::ImGuiKey_GamepadL1;
    e.value("ImGuiKey_GamepadR1",                      ImGuiKey_GamepadR1);                      m.attr("ImGuiKey_GamepadR1")                      = ImGuiKey::ImGuiKey_GamepadR1;
    e.value("ImGuiKey_GamepadL2",                      ImGuiKey_GamepadL2);                      m.attr("ImGuiKey_GamepadL2")                      = ImGuiKey::ImGuiKey_GamepadL2;
    e.value("ImGuiKey_GamepadR2",                      ImGuiKey_GamepadR2);                      m.attr("ImGuiKey_GamepadR2")                      = ImGuiKey::ImGuiKey_GamepadR2;
    e.value("ImGuiKey_GamepadL3",                      ImGuiKey_GamepadL3);                      m.attr("ImGuiKey_GamepadL3")                      = ImGuiKey::ImGuiKey_GamepadL3;
    e.value("ImGuiKey_GamepadR3",                      ImGuiKey_GamepadR3);                      m.attr("ImGuiKey_GamepadR3")                      = ImGuiKey::ImGuiKey_GamepadR3;
    e.value("ImGuiKey_GamepadLStickUp",                ImGuiKey_GamepadLStickUp);                m.attr("ImGuiKey_GamepadLStickUp")                = ImGuiKey::ImGuiKey_GamepadLStickUp;
    e.value("ImGuiKey_GamepadLStickDown",              ImGuiKey_GamepadLStickDown);              m.attr("ImGuiKey_GamepadLStickDown")              = ImGuiKey::ImGuiKey_GamepadLStickDown;
    e.value("ImGuiKey_GamepadLStickLeft",              ImGuiKey_GamepadLStickLeft);              m.attr("ImGuiKey_GamepadLStickLeft")              = ImGuiKey::ImGuiKey_GamepadLStickLeft;
    e.value("ImGuiKey_GamepadLStickRight",             ImGuiKey_GamepadLStickRight);             m.attr("ImGuiKey_GamepadLStickRight")             = ImGuiKey::ImGuiKey_GamepadLStickRight;
    e.value("ImGuiKey_GamepadRStickUp",                ImGuiKey_GamepadRStickUp);                m.attr("ImGuiKey_GamepadRStickUp")                = ImGuiKey::ImGuiKey_GamepadRStickUp;
    e.value("ImGuiKey_GamepadRStickDown",              ImGuiKey_GamepadRStickDown);              m.attr("ImGuiKey_GamepadRStickDown")              = ImGuiKey::ImGuiKey_GamepadRStickDown;
    e.value("ImGuiKey_GamepadRStickLeft",              ImGuiKey_GamepadRStickLeft);              m.attr("ImGuiKey_GamepadRStickLeft")              = ImGuiKey::ImGuiKey_GamepadRStickLeft;
    e.value("ImGuiKey_GamepadRStickRight",             ImGuiKey_GamepadRStickRight);             m.attr("ImGuiKey_GamepadRStickRight")             = ImGuiKey::ImGuiKey_GamepadRStickRight;
    e.value("ImGuiMod_None",                           ImGuiMod_None);                           m.attr("ImGuiMod_None")                           = ImGuiKey::ImGuiMod_None;
    e.value("ImGuiMod_Ctrl",                           ImGuiMod_Ctrl);                           m.attr("ImGuiMod_Ctrl")                           = ImGuiKey::ImGuiMod_Ctrl;
    e.value("ImGuiMod_Shift",                          ImGuiMod_Shift);                          m.attr("ImGuiMod_Shift")                          = ImGuiKey::ImGuiMod_Shift;
    e.value("ImGuiMod_Alt",                            ImGuiMod_Alt);                            m.attr("ImGuiMod_Alt")                            = ImGuiKey::ImGuiMod_Alt;
    e.value("ImGuiMod_Super",                          ImGuiMod_Super);                          m.attr("ImGuiMod_Super")                          = ImGuiKey::ImGuiMod_Super;
    e.value("ImGuiMod_Mask_",                          ImGuiMod_Mask_);                          m.attr("ImGuiMod_Mask_")                          = ImGuiKey::ImGuiMod_Mask_;
  ;
  }

  { // ImTextureFormat
    m.attr("ImTextureStatus_WantUpdates") = static_cast<int>(ImTextureStatus_WantUpdates);
    m.attr("ImTextureStatus_WantDestroy") = static_cast<int>(ImTextureStatus_WantDestroy);
  ;
  }

  { // ImTextureStatus
    m.attr("ImFontAtlasFlags_None")               = static_cast<int>(ImFontAtlasFlags_None);
    m.attr("ImFontAtlasFlags_NoPowerOfTwoHeight") = static_cast<int>(ImFontAtlasFlags_NoPowerOfTwoHeight);
    m.attr("ImFontAtlasFlags_NoMouseCursors")     = static_cast<int>(ImFontAtlasFlags_NoMouseCursors);
    m.attr("ImFontAtlasFlags_NoBakedLines")       = static_cast<int>(ImFontAtlasFlags_NoBakedLines);
  ;
  ;
  }

  { // ImFontAtlasFlags ImFontAtlasFlags_
    m.attr("ImFontFlags_NoLoadError")     = static_cast<int>(ImFontFlags_NoLoadError);
    m.attr("ImFontFlags_NoLoadGlyphs")    = static_cast<int>(ImFontFlags_NoLoadGlyphs);
    m.attr("ImFontFlags_LockBakedSizes")  = static_cast<int>(ImFontFlags_LockBakedSizes);
  ;
  ;
  }

  { // ImFontFlags ImFontFlags_
    m.attr("ImGuiViewportFlags_IsPlatformWindow")  = static_cast<int>(ImGuiViewportFlags_IsPlatformWindow);
    m.attr("ImGuiViewportFlags_IsPlatformMonitor") = static_cast<int>(ImGuiViewportFlags_IsPlatformMonitor);
    m.attr("ImGuiViewportFlags_OwnedByApp")        = static_cast<int>(ImGuiViewportFlags_OwnedByApp);
  ;
  ;
  }

  { // ImGuiViewportFlags ImGuiViewportFlags_
  ;
  }
}
