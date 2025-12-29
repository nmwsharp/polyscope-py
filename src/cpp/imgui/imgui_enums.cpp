#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

void bind_imgui_enums(nb::module_& m) {

  { // ImGuiDir ImGuiDir
  auto e = nb::enum_<ImGuiDir>(m, "ImGuiDir");
    e.value("ImGuiDir_None",                           ImGuiDir_None);                           m.attr("ImGuiDir_None")                           = static_cast<int>(ImGuiDir_None);
    e.value("ImGuiDir_Left",                           ImGuiDir_Left);                           m.attr("ImGuiDir_Left")                           = static_cast<int>(ImGuiDir_Left);
    e.value("ImGuiDir_Right",                          ImGuiDir_Right);                          m.attr("ImGuiDir_Right")                          = static_cast<int>(ImGuiDir_Right);
    e.value("ImGuiDir_Up",                             ImGuiDir_Up);                             m.attr("ImGuiDir_Up")                             = static_cast<int>(ImGuiDir_Up);
    e.value("ImGuiDir_Down",                           ImGuiDir_Down);                           m.attr("ImGuiDir_Down")                           = static_cast<int>(ImGuiDir_Down);
    e.value("ImGuiDir_COUNT",                          ImGuiDir_COUNT);                          m.attr("ImGuiDir_COUNT")                          = static_cast<int>(ImGuiDir_COUNT);
  ;
  }

  { // ImGuiSortDirection ImGuiSortDirection
  auto e = nb::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection");
    e.value("ImGuiSortDirection_None",                 ImGuiSortDirection_None);                 m.attr("ImGuiSortDirection_None")                 = static_cast<int>(ImGuiSortDirection_None);
    e.value("ImGuiSortDirection_Ascending",            ImGuiSortDirection_Ascending);            m.attr("ImGuiSortDirection_Ascending")            = static_cast<int>(ImGuiSortDirection_Ascending);
    e.value("ImGuiSortDirection_Descending",           ImGuiSortDirection_Descending);           m.attr("ImGuiSortDirection_Descending")           = static_cast<int>(ImGuiSortDirection_Descending);
  ;
  }

  { // ImGuiWindowFlags ImGuiWindowFlags_
  auto e = nb::enum_<ImGuiWindowFlags_>(m, "ImGuiWindowFlags");
    e.value("ImGuiWindowFlags_None",                   ImGuiWindowFlags_None);                   m.attr("ImGuiWindowFlags_None")                   = static_cast<int>(ImGuiWindowFlags_None);
    e.value("ImGuiWindowFlags_NoTitleBar",             ImGuiWindowFlags_NoTitleBar);             m.attr("ImGuiWindowFlags_NoTitleBar")             = static_cast<int>(ImGuiWindowFlags_NoTitleBar);
    e.value("ImGuiWindowFlags_NoResize",               ImGuiWindowFlags_NoResize);               m.attr("ImGuiWindowFlags_NoResize")               = static_cast<int>(ImGuiWindowFlags_NoResize);
    e.value("ImGuiWindowFlags_NoMove",                 ImGuiWindowFlags_NoMove);                 m.attr("ImGuiWindowFlags_NoMove")                 = static_cast<int>(ImGuiWindowFlags_NoMove);
    e.value("ImGuiWindowFlags_NoScrollbar",            ImGuiWindowFlags_NoScrollbar);            m.attr("ImGuiWindowFlags_NoScrollbar")            = static_cast<int>(ImGuiWindowFlags_NoScrollbar);
    e.value("ImGuiWindowFlags_NoScrollWithMouse",      ImGuiWindowFlags_NoScrollWithMouse);      m.attr("ImGuiWindowFlags_NoScrollWithMouse")      = static_cast<int>(ImGuiWindowFlags_NoScrollWithMouse);
    e.value("ImGuiWindowFlags_NoCollapse",             ImGuiWindowFlags_NoCollapse);             m.attr("ImGuiWindowFlags_NoCollapse")             = static_cast<int>(ImGuiWindowFlags_NoCollapse);
    e.value("ImGuiWindowFlags_AlwaysAutoResize",       ImGuiWindowFlags_AlwaysAutoResize);       m.attr("ImGuiWindowFlags_AlwaysAutoResize")       = static_cast<int>(ImGuiWindowFlags_AlwaysAutoResize);
    e.value("ImGuiWindowFlags_NoBackground",           ImGuiWindowFlags_NoBackground);           m.attr("ImGuiWindowFlags_NoBackground")           = static_cast<int>(ImGuiWindowFlags_NoBackground);
    e.value("ImGuiWindowFlags_NoSavedSettings",        ImGuiWindowFlags_NoSavedSettings);        m.attr("ImGuiWindowFlags_NoSavedSettings")        = static_cast<int>(ImGuiWindowFlags_NoSavedSettings);
    e.value("ImGuiWindowFlags_NoMouseInputs",          ImGuiWindowFlags_NoMouseInputs);          m.attr("ImGuiWindowFlags_NoMouseInputs")          = static_cast<int>(ImGuiWindowFlags_NoMouseInputs);
    e.value("ImGuiWindowFlags_MenuBar",                ImGuiWindowFlags_MenuBar);                m.attr("ImGuiWindowFlags_MenuBar")                = static_cast<int>(ImGuiWindowFlags_MenuBar);
    e.value("ImGuiWindowFlags_HorizontalScrollbar",    ImGuiWindowFlags_HorizontalScrollbar);    m.attr("ImGuiWindowFlags_HorizontalScrollbar")    = static_cast<int>(ImGuiWindowFlags_HorizontalScrollbar);
    e.value("ImGuiWindowFlags_NoFocusOnAppearing",     ImGuiWindowFlags_NoFocusOnAppearing);     m.attr("ImGuiWindowFlags_NoFocusOnAppearing")     = static_cast<int>(ImGuiWindowFlags_NoFocusOnAppearing);
    e.value("ImGuiWindowFlags_NoBringToFrontOnFocus",  ImGuiWindowFlags_NoBringToFrontOnFocus);  m.attr("ImGuiWindowFlags_NoBringToFrontOnFocus")  = static_cast<int>(ImGuiWindowFlags_NoBringToFrontOnFocus);
    e.value("ImGuiWindowFlags_AlwaysVerticalScrollbar", ImGuiWindowFlags_AlwaysVerticalScrollbar); m.attr("ImGuiWindowFlags_AlwaysVerticalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysVerticalScrollbar);
    e.value("ImGuiWindowFlags_AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar); m.attr("ImGuiWindowFlags_AlwaysHorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysHorizontalScrollbar);
    e.value("ImGuiWindowFlags_AlwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding); m.attr("ImGuiWindowFlags_AlwaysUseWindowPadding") = static_cast<int>(ImGuiWindowFlags_AlwaysUseWindowPadding);
    e.value("ImGuiWindowFlags_NoNavInputs",            ImGuiWindowFlags_NoNavInputs);            m.attr("ImGuiWindowFlags_NoNavInputs")            = static_cast<int>(ImGuiWindowFlags_NoNavInputs);
    e.value("ImGuiWindowFlags_NoNavFocus",             ImGuiWindowFlags_NoNavFocus);             m.attr("ImGuiWindowFlags_NoNavFocus")             = static_cast<int>(ImGuiWindowFlags_NoNavFocus);
    e.value("ImGuiWindowFlags_UnsavedDocument",        ImGuiWindowFlags_UnsavedDocument);        m.attr("ImGuiWindowFlags_UnsavedDocument")        = static_cast<int>(ImGuiWindowFlags_UnsavedDocument);
    e.value("ImGuiWindowFlags_NoNav",                  ImGuiWindowFlags_NoNav);                  m.attr("ImGuiWindowFlags_NoNav")                  = static_cast<int>(ImGuiWindowFlags_NoNav);
    e.value("ImGuiWindowFlags_NoDecoration",           ImGuiWindowFlags_NoDecoration);           m.attr("ImGuiWindowFlags_NoDecoration")           = static_cast<int>(ImGuiWindowFlags_NoDecoration);
    e.value("ImGuiWindowFlags_NoInputs",               ImGuiWindowFlags_NoInputs);               m.attr("ImGuiWindowFlags_NoInputs")               = static_cast<int>(ImGuiWindowFlags_NoInputs);
    e.value("ImGuiWindowFlags_NavFlattened",           ImGuiWindowFlags_NavFlattened);           m.attr("ImGuiWindowFlags_NavFlattened")           = static_cast<int>(ImGuiWindowFlags_NavFlattened);
    e.value("ImGuiWindowFlags_ChildWindow",            ImGuiWindowFlags_ChildWindow);            m.attr("ImGuiWindowFlags_ChildWindow")            = static_cast<int>(ImGuiWindowFlags_ChildWindow);
    e.value("ImGuiWindowFlags_Tooltip",                ImGuiWindowFlags_Tooltip);                m.attr("ImGuiWindowFlags_Tooltip")                = static_cast<int>(ImGuiWindowFlags_Tooltip);
    e.value("ImGuiWindowFlags_Popup",                  ImGuiWindowFlags_Popup);                  m.attr("ImGuiWindowFlags_Popup")                  = static_cast<int>(ImGuiWindowFlags_Popup);
    e.value("ImGuiWindowFlags_Modal",                  ImGuiWindowFlags_Modal);                  m.attr("ImGuiWindowFlags_Modal")                  = static_cast<int>(ImGuiWindowFlags_Modal);
    e.value("ImGuiWindowFlags_ChildMenu",              ImGuiWindowFlags_ChildMenu);              m.attr("ImGuiWindowFlags_ChildMenu")              = static_cast<int>(ImGuiWindowFlags_ChildMenu);
  ;
  }

  { // ImGuiChildFlags ImGuiChildFlags_
  auto e = nb::enum_<ImGuiChildFlags_>(m, "ImGuiChildFlags");
    e.value("ImGuiChildFlags_None",                    ImGuiChildFlags_None);                    m.attr("ImGuiChildFlags_None")                    = static_cast<int>(ImGuiChildFlags_None);
    e.value("ImGuiChildFlags_Borders",                 ImGuiChildFlags_Borders);                 m.attr("ImGuiChildFlags_Borders")                 = static_cast<int>(ImGuiChildFlags_Borders);
    e.value("ImGuiChildFlags_AlwaysUseWindowPadding",  ImGuiChildFlags_AlwaysUseWindowPadding);  m.attr("ImGuiChildFlags_AlwaysUseWindowPadding")  = static_cast<int>(ImGuiChildFlags_AlwaysUseWindowPadding);
    e.value("ImGuiChildFlags_ResizeX",                 ImGuiChildFlags_ResizeX);                 m.attr("ImGuiChildFlags_ResizeX")                 = static_cast<int>(ImGuiChildFlags_ResizeX);
    e.value("ImGuiChildFlags_ResizeY",                 ImGuiChildFlags_ResizeY);                 m.attr("ImGuiChildFlags_ResizeY")                 = static_cast<int>(ImGuiChildFlags_ResizeY);
    e.value("ImGuiChildFlags_AutoResizeX",             ImGuiChildFlags_AutoResizeX);             m.attr("ImGuiChildFlags_AutoResizeX")             = static_cast<int>(ImGuiChildFlags_AutoResizeX);
    e.value("ImGuiChildFlags_AutoResizeY",             ImGuiChildFlags_AutoResizeY);             m.attr("ImGuiChildFlags_AutoResizeY")             = static_cast<int>(ImGuiChildFlags_AutoResizeY);
    e.value("ImGuiChildFlags_AlwaysAutoResize",        ImGuiChildFlags_AlwaysAutoResize);        m.attr("ImGuiChildFlags_AlwaysAutoResize")        = static_cast<int>(ImGuiChildFlags_AlwaysAutoResize);
    e.value("ImGuiChildFlags_FrameStyle",              ImGuiChildFlags_FrameStyle);              m.attr("ImGuiChildFlags_FrameStyle")              = static_cast<int>(ImGuiChildFlags_FrameStyle);
    e.value("ImGuiChildFlags_NavFlattened",            ImGuiChildFlags_NavFlattened);            m.attr("ImGuiChildFlags_NavFlattened")            = static_cast<int>(ImGuiChildFlags_NavFlattened);
  ;
  }

  { // ImGuiItemFlags ImGuiItemFlags_
  auto e = nb::enum_<ImGuiItemFlags_>(m, "ImGuiItemFlags");
    e.value("ImGuiItemFlags_None",                     ImGuiItemFlags_None);                     m.attr("ImGuiItemFlags_None")                     = static_cast<int>(ImGuiItemFlags_None);
    e.value("ImGuiItemFlags_NoTabStop",                ImGuiItemFlags_NoTabStop);                m.attr("ImGuiItemFlags_NoTabStop")                = static_cast<int>(ImGuiItemFlags_NoTabStop);
    e.value("ImGuiItemFlags_NoNav",                    ImGuiItemFlags_NoNav);                    m.attr("ImGuiItemFlags_NoNav")                    = static_cast<int>(ImGuiItemFlags_NoNav);
    e.value("ImGuiItemFlags_NoNavDefaultFocus",        ImGuiItemFlags_NoNavDefaultFocus);        m.attr("ImGuiItemFlags_NoNavDefaultFocus")        = static_cast<int>(ImGuiItemFlags_NoNavDefaultFocus);
    e.value("ImGuiItemFlags_ButtonRepeat",             ImGuiItemFlags_ButtonRepeat);             m.attr("ImGuiItemFlags_ButtonRepeat")             = static_cast<int>(ImGuiItemFlags_ButtonRepeat);
    e.value("ImGuiItemFlags_AutoClosePopups",          ImGuiItemFlags_AutoClosePopups);          m.attr("ImGuiItemFlags_AutoClosePopups")          = static_cast<int>(ImGuiItemFlags_AutoClosePopups);
    e.value("ImGuiItemFlags_AllowDuplicateId",         ImGuiItemFlags_AllowDuplicateId);         m.attr("ImGuiItemFlags_AllowDuplicateId")         = static_cast<int>(ImGuiItemFlags_AllowDuplicateId);
  ;
  }

  { // ImGuiInputTextFlags ImGuiInputTextFlags_
  auto e = nb::enum_<ImGuiInputTextFlags_>(m, "ImGuiInputTextFlags");
    e.value("ImGuiInputTextFlags_None",                ImGuiInputTextFlags_None);                m.attr("ImGuiInputTextFlags_None")                = static_cast<int>(ImGuiInputTextFlags_None);
    e.value("ImGuiInputTextFlags_CharsDecimal",        ImGuiInputTextFlags_CharsDecimal);        m.attr("ImGuiInputTextFlags_CharsDecimal")        = static_cast<int>(ImGuiInputTextFlags_CharsDecimal);
    e.value("ImGuiInputTextFlags_CharsHexadecimal",    ImGuiInputTextFlags_CharsHexadecimal);    m.attr("ImGuiInputTextFlags_CharsHexadecimal")    = static_cast<int>(ImGuiInputTextFlags_CharsHexadecimal);
    e.value("ImGuiInputTextFlags_CharsScientific",     ImGuiInputTextFlags_CharsScientific);     m.attr("ImGuiInputTextFlags_CharsScientific")     = static_cast<int>(ImGuiInputTextFlags_CharsScientific);
    e.value("ImGuiInputTextFlags_CharsUppercase",      ImGuiInputTextFlags_CharsUppercase);      m.attr("ImGuiInputTextFlags_CharsUppercase")      = static_cast<int>(ImGuiInputTextFlags_CharsUppercase);
    e.value("ImGuiInputTextFlags_CharsNoBlank",        ImGuiInputTextFlags_CharsNoBlank);        m.attr("ImGuiInputTextFlags_CharsNoBlank")        = static_cast<int>(ImGuiInputTextFlags_CharsNoBlank);
    e.value("ImGuiInputTextFlags_AllowTabInput",       ImGuiInputTextFlags_AllowTabInput);       m.attr("ImGuiInputTextFlags_AllowTabInput")       = static_cast<int>(ImGuiInputTextFlags_AllowTabInput);
    e.value("ImGuiInputTextFlags_EnterReturnsTrue",    ImGuiInputTextFlags_EnterReturnsTrue);    m.attr("ImGuiInputTextFlags_EnterReturnsTrue")    = static_cast<int>(ImGuiInputTextFlags_EnterReturnsTrue);
    e.value("ImGuiInputTextFlags_EscapeClearsAll",     ImGuiInputTextFlags_EscapeClearsAll);     m.attr("ImGuiInputTextFlags_EscapeClearsAll")     = static_cast<int>(ImGuiInputTextFlags_EscapeClearsAll);
    e.value("ImGuiInputTextFlags_CtrlEnterForNewLine", ImGuiInputTextFlags_CtrlEnterForNewLine); m.attr("ImGuiInputTextFlags_CtrlEnterForNewLine") = static_cast<int>(ImGuiInputTextFlags_CtrlEnterForNewLine);
    e.value("ImGuiInputTextFlags_ReadOnly",            ImGuiInputTextFlags_ReadOnly);            m.attr("ImGuiInputTextFlags_ReadOnly")            = static_cast<int>(ImGuiInputTextFlags_ReadOnly);
    e.value("ImGuiInputTextFlags_Password",            ImGuiInputTextFlags_Password);            m.attr("ImGuiInputTextFlags_Password")            = static_cast<int>(ImGuiInputTextFlags_Password);
    e.value("ImGuiInputTextFlags_AlwaysOverwrite",     ImGuiInputTextFlags_AlwaysOverwrite);     m.attr("ImGuiInputTextFlags_AlwaysOverwrite")     = static_cast<int>(ImGuiInputTextFlags_AlwaysOverwrite);
    e.value("ImGuiInputTextFlags_AutoSelectAll",       ImGuiInputTextFlags_AutoSelectAll);       m.attr("ImGuiInputTextFlags_AutoSelectAll")       = static_cast<int>(ImGuiInputTextFlags_AutoSelectAll);
    e.value("ImGuiInputTextFlags_ParseEmptyRefVal",    ImGuiInputTextFlags_ParseEmptyRefVal);    m.attr("ImGuiInputTextFlags_ParseEmptyRefVal")    = static_cast<int>(ImGuiInputTextFlags_ParseEmptyRefVal);
    e.value("ImGuiInputTextFlags_DisplayEmptyRefVal",  ImGuiInputTextFlags_DisplayEmptyRefVal);  m.attr("ImGuiInputTextFlags_DisplayEmptyRefVal")  = static_cast<int>(ImGuiInputTextFlags_DisplayEmptyRefVal);
    e.value("ImGuiInputTextFlags_NoHorizontalScroll",  ImGuiInputTextFlags_NoHorizontalScroll);  m.attr("ImGuiInputTextFlags_NoHorizontalScroll")  = static_cast<int>(ImGuiInputTextFlags_NoHorizontalScroll);
    e.value("ImGuiInputTextFlags_NoUndoRedo",          ImGuiInputTextFlags_NoUndoRedo);          m.attr("ImGuiInputTextFlags_NoUndoRedo")          = static_cast<int>(ImGuiInputTextFlags_NoUndoRedo);
    e.value("ImGuiInputTextFlags_ElideLeft",           ImGuiInputTextFlags_ElideLeft);           m.attr("ImGuiInputTextFlags_ElideLeft")           = static_cast<int>(ImGuiInputTextFlags_ElideLeft);
    e.value("ImGuiInputTextFlags_CallbackCompletion",  ImGuiInputTextFlags_CallbackCompletion);  m.attr("ImGuiInputTextFlags_CallbackCompletion")  = static_cast<int>(ImGuiInputTextFlags_CallbackCompletion);
    e.value("ImGuiInputTextFlags_CallbackHistory",     ImGuiInputTextFlags_CallbackHistory);     m.attr("ImGuiInputTextFlags_CallbackHistory")     = static_cast<int>(ImGuiInputTextFlags_CallbackHistory);
    e.value("ImGuiInputTextFlags_CallbackAlways",      ImGuiInputTextFlags_CallbackAlways);      m.attr("ImGuiInputTextFlags_CallbackAlways")      = static_cast<int>(ImGuiInputTextFlags_CallbackAlways);
    e.value("ImGuiInputTextFlags_CallbackCharFilter",  ImGuiInputTextFlags_CallbackCharFilter);  m.attr("ImGuiInputTextFlags_CallbackCharFilter")  = static_cast<int>(ImGuiInputTextFlags_CallbackCharFilter);
    e.value("ImGuiInputTextFlags_CallbackResize",      ImGuiInputTextFlags_CallbackResize);      m.attr("ImGuiInputTextFlags_CallbackResize")      = static_cast<int>(ImGuiInputTextFlags_CallbackResize);
    e.value("ImGuiInputTextFlags_CallbackEdit",        ImGuiInputTextFlags_CallbackEdit);        m.attr("ImGuiInputTextFlags_CallbackEdit")        = static_cast<int>(ImGuiInputTextFlags_CallbackEdit);
  ;
  }

  { // ImGuiTreeNodeFlags ImGuiTreeNodeFlags_
  auto e = nb::enum_<ImGuiTreeNodeFlags_>(m, "ImGuiTreeNodeFlags");
    e.value("ImGuiTreeNodeFlags_None",                 ImGuiTreeNodeFlags_None);                 m.attr("ImGuiTreeNodeFlags_None")                 = static_cast<int>(ImGuiTreeNodeFlags_None);
    e.value("ImGuiTreeNodeFlags_Selected",             ImGuiTreeNodeFlags_Selected);             m.attr("ImGuiTreeNodeFlags_Selected")             = static_cast<int>(ImGuiTreeNodeFlags_Selected);
    e.value("ImGuiTreeNodeFlags_Framed",               ImGuiTreeNodeFlags_Framed);               m.attr("ImGuiTreeNodeFlags_Framed")               = static_cast<int>(ImGuiTreeNodeFlags_Framed);
    e.value("ImGuiTreeNodeFlags_AllowItemOverlap",     ImGuiTreeNodeFlags_AllowItemOverlap);     m.attr("ImGuiTreeNodeFlags_AllowItemOverlap")     = static_cast<int>(ImGuiTreeNodeFlags_AllowItemOverlap);
    e.value("ImGuiTreeNodeFlags_NoTreePushOnOpen",     ImGuiTreeNodeFlags_NoTreePushOnOpen);     m.attr("ImGuiTreeNodeFlags_NoTreePushOnOpen")     = static_cast<int>(ImGuiTreeNodeFlags_NoTreePushOnOpen);
    e.value("ImGuiTreeNodeFlags_NoAutoOpenOnLog",      ImGuiTreeNodeFlags_NoAutoOpenOnLog);      m.attr("ImGuiTreeNodeFlags_NoAutoOpenOnLog")      = static_cast<int>(ImGuiTreeNodeFlags_NoAutoOpenOnLog);
    e.value("ImGuiTreeNodeFlags_DefaultOpen",          ImGuiTreeNodeFlags_DefaultOpen);          m.attr("ImGuiTreeNodeFlags_DefaultOpen")          = static_cast<int>(ImGuiTreeNodeFlags_DefaultOpen);
    e.value("ImGuiTreeNodeFlags_OpenOnDoubleClick",    ImGuiTreeNodeFlags_OpenOnDoubleClick);    m.attr("ImGuiTreeNodeFlags_OpenOnDoubleClick")    = static_cast<int>(ImGuiTreeNodeFlags_OpenOnDoubleClick);
    e.value("ImGuiTreeNodeFlags_OpenOnArrow",          ImGuiTreeNodeFlags_OpenOnArrow);          m.attr("ImGuiTreeNodeFlags_OpenOnArrow")          = static_cast<int>(ImGuiTreeNodeFlags_OpenOnArrow);
    e.value("ImGuiTreeNodeFlags_Leaf",                 ImGuiTreeNodeFlags_Leaf);                 m.attr("ImGuiTreeNodeFlags_Leaf")                 = static_cast<int>(ImGuiTreeNodeFlags_Leaf);
    e.value("ImGuiTreeNodeFlags_Bullet",               ImGuiTreeNodeFlags_Bullet);               m.attr("ImGuiTreeNodeFlags_Bullet")               = static_cast<int>(ImGuiTreeNodeFlags_Bullet);
    e.value("ImGuiTreeNodeFlags_FramePadding",         ImGuiTreeNodeFlags_FramePadding);         m.attr("ImGuiTreeNodeFlags_FramePadding")         = static_cast<int>(ImGuiTreeNodeFlags_FramePadding);
    e.value("ImGuiTreeNodeFlags_SpanAvailWidth",       ImGuiTreeNodeFlags_SpanAvailWidth);       m.attr("ImGuiTreeNodeFlags_SpanAvailWidth")       = static_cast<int>(ImGuiTreeNodeFlags_SpanAvailWidth);
    e.value("ImGuiTreeNodeFlags_SpanFullWidth",        ImGuiTreeNodeFlags_SpanFullWidth);        m.attr("ImGuiTreeNodeFlags_SpanFullWidth")        = static_cast<int>(ImGuiTreeNodeFlags_SpanFullWidth);
    e.value("ImGuiTreeNodeFlags_NavLeftJumpsBackHere", ImGuiTreeNodeFlags_NavLeftJumpsBackHere); m.attr("ImGuiTreeNodeFlags_NavLeftJumpsBackHere") = static_cast<int>(ImGuiTreeNodeFlags_NavLeftJumpsBackHere);
    e.value("ImGuiTreeNodeFlags_CollapsingHeader",     ImGuiTreeNodeFlags_CollapsingHeader);     m.attr("ImGuiTreeNodeFlags_CollapsingHeader")     = static_cast<int>(ImGuiTreeNodeFlags_CollapsingHeader);
  ;
  }

  { // ImGuiPopupFlags ImGuiPopupFlags_
  auto e = nb::enum_<ImGuiPopupFlags_>(m, "ImGuiPopupFlags");
    e.value("ImGuiPopupFlags_None",                    ImGuiPopupFlags_None);                    m.attr("ImGuiPopupFlags_None")                    = static_cast<int>(ImGuiPopupFlags_None);
    e.value("ImGuiPopupFlags_MouseButtonLeft",         ImGuiPopupFlags_MouseButtonLeft);         m.attr("ImGuiPopupFlags_MouseButtonLeft")         = static_cast<int>(ImGuiPopupFlags_MouseButtonLeft);
    e.value("ImGuiPopupFlags_MouseButtonRight",        ImGuiPopupFlags_MouseButtonRight);        m.attr("ImGuiPopupFlags_MouseButtonRight")        = static_cast<int>(ImGuiPopupFlags_MouseButtonRight);
    e.value("ImGuiPopupFlags_MouseButtonMiddle",       ImGuiPopupFlags_MouseButtonMiddle);       m.attr("ImGuiPopupFlags_MouseButtonMiddle")       = static_cast<int>(ImGuiPopupFlags_MouseButtonMiddle);
    e.value("ImGuiPopupFlags_MouseButtonMask_",        ImGuiPopupFlags_MouseButtonMask_);        m.attr("ImGuiPopupFlags_MouseButtonMask_")        = static_cast<int>(ImGuiPopupFlags_MouseButtonMask_);
    e.value("ImGuiPopupFlags_MouseButtonDefault_",     ImGuiPopupFlags_MouseButtonDefault_);     m.attr("ImGuiPopupFlags_MouseButtonDefault_")     = static_cast<int>(ImGuiPopupFlags_MouseButtonDefault_);
    e.value("ImGuiPopupFlags_NoReopen",                ImGuiPopupFlags_NoReopen);                m.attr("ImGuiPopupFlags_NoReopen")                = static_cast<int>(ImGuiPopupFlags_NoReopen);
    e.value("ImGuiPopupFlags_NoOpenOverExistingPopup", ImGuiPopupFlags_NoOpenOverExistingPopup); m.attr("ImGuiPopupFlags_NoOpenOverExistingPopup") = static_cast<int>(ImGuiPopupFlags_NoOpenOverExistingPopup);
    e.value("ImGuiPopupFlags_NoOpenOverItems",         ImGuiPopupFlags_NoOpenOverItems);         m.attr("ImGuiPopupFlags_NoOpenOverItems")         = static_cast<int>(ImGuiPopupFlags_NoOpenOverItems);
    e.value("ImGuiPopupFlags_AnyPopupId",              ImGuiPopupFlags_AnyPopupId);              m.attr("ImGuiPopupFlags_AnyPopupId")              = static_cast<int>(ImGuiPopupFlags_AnyPopupId);
    e.value("ImGuiPopupFlags_AnyPopupLevel",           ImGuiPopupFlags_AnyPopupLevel);           m.attr("ImGuiPopupFlags_AnyPopupLevel")           = static_cast<int>(ImGuiPopupFlags_AnyPopupLevel);
    e.value("ImGuiPopupFlags_AnyPopup",                ImGuiPopupFlags_AnyPopup);                m.attr("ImGuiPopupFlags_AnyPopup")                = static_cast<int>(ImGuiPopupFlags_AnyPopup);
  ;
  }

  { // ImGuiSelectableFlags ImGuiSelectableFlags_
  auto e = nb::enum_<ImGuiSelectableFlags_>(m, "ImGuiSelectableFlags");
    e.value("ImGuiSelectableFlags_None",               ImGuiSelectableFlags_None);               m.attr("ImGuiSelectableFlags_None")               = static_cast<int>(ImGuiSelectableFlags_None);
    e.value("ImGuiSelectableFlags_DontClosePopups",    ImGuiSelectableFlags_DontClosePopups);    m.attr("ImGuiSelectableFlags_DontClosePopups")    = static_cast<int>(ImGuiSelectableFlags_DontClosePopups);
    e.value("ImGuiSelectableFlags_SpanAllColumns",     ImGuiSelectableFlags_SpanAllColumns);     m.attr("ImGuiSelectableFlags_SpanAllColumns")     = static_cast<int>(ImGuiSelectableFlags_SpanAllColumns);
    e.value("ImGuiSelectableFlags_AllowDoubleClick",   ImGuiSelectableFlags_AllowDoubleClick);   m.attr("ImGuiSelectableFlags_AllowDoubleClick")   = static_cast<int>(ImGuiSelectableFlags_AllowDoubleClick);
    e.value("ImGuiSelectableFlags_Disabled",           ImGuiSelectableFlags_Disabled);           m.attr("ImGuiSelectableFlags_Disabled")           = static_cast<int>(ImGuiSelectableFlags_Disabled);
    e.value("ImGuiSelectableFlags_AllowItemOverlap",   ImGuiSelectableFlags_AllowItemOverlap);   m.attr("ImGuiSelectableFlags_AllowItemOverlap")   = static_cast<int>(ImGuiSelectableFlags_AllowItemOverlap);
  ;
  }

  { // ImGuiComboFlags ImGuiComboFlags_
  auto e = nb::enum_<ImGuiComboFlags_>(m, "ImGuiComboFlags");
    e.value("ImGuiComboFlags_None",                    ImGuiComboFlags_None);                    m.attr("ImGuiComboFlags_None")                    = static_cast<int>(ImGuiComboFlags_None);
    e.value("ImGuiComboFlags_PopupAlignLeft",          ImGuiComboFlags_PopupAlignLeft);          m.attr("ImGuiComboFlags_PopupAlignLeft")          = static_cast<int>(ImGuiComboFlags_PopupAlignLeft);
    e.value("ImGuiComboFlags_HeightSmall",             ImGuiComboFlags_HeightSmall);             m.attr("ImGuiComboFlags_HeightSmall")             = static_cast<int>(ImGuiComboFlags_HeightSmall);
    e.value("ImGuiComboFlags_HeightRegular",           ImGuiComboFlags_HeightRegular);           m.attr("ImGuiComboFlags_HeightRegular")           = static_cast<int>(ImGuiComboFlags_HeightRegular);
    e.value("ImGuiComboFlags_HeightLarge",             ImGuiComboFlags_HeightLarge);             m.attr("ImGuiComboFlags_HeightLarge")             = static_cast<int>(ImGuiComboFlags_HeightLarge);
    e.value("ImGuiComboFlags_HeightLargest",           ImGuiComboFlags_HeightLargest);           m.attr("ImGuiComboFlags_HeightLargest")           = static_cast<int>(ImGuiComboFlags_HeightLargest);
    e.value("ImGuiComboFlags_NoArrowButton",           ImGuiComboFlags_NoArrowButton);           m.attr("ImGuiComboFlags_NoArrowButton")           = static_cast<int>(ImGuiComboFlags_NoArrowButton);
    e.value("ImGuiComboFlags_NoPreview",               ImGuiComboFlags_NoPreview);               m.attr("ImGuiComboFlags_NoPreview")               = static_cast<int>(ImGuiComboFlags_NoPreview);
    e.value("ImGuiComboFlags_HeightMask_",             ImGuiComboFlags_HeightMask_);             m.attr("ImGuiComboFlags_HeightMask_")             = static_cast<int>(ImGuiComboFlags_HeightMask_);
  ;
  }

  { // ImGuiTabBarFlags ImGuiTabBarFlags_
  auto e = nb::enum_<ImGuiTabBarFlags_>(m, "ImGuiTabBarFlags");
    e.value("ImGuiTabBarFlags_None",                   ImGuiTabBarFlags_None);                   m.attr("ImGuiTabBarFlags_None")                   = static_cast<int>(ImGuiTabBarFlags_None);
    e.value("ImGuiTabBarFlags_Reorderable",            ImGuiTabBarFlags_Reorderable);            m.attr("ImGuiTabBarFlags_Reorderable")            = static_cast<int>(ImGuiTabBarFlags_Reorderable);
    e.value("ImGuiTabBarFlags_AutoSelectNewTabs",      ImGuiTabBarFlags_AutoSelectNewTabs);      m.attr("ImGuiTabBarFlags_AutoSelectNewTabs")      = static_cast<int>(ImGuiTabBarFlags_AutoSelectNewTabs);
    e.value("ImGuiTabBarFlags_TabListPopupButton",     ImGuiTabBarFlags_TabListPopupButton);     m.attr("ImGuiTabBarFlags_TabListPopupButton")     = static_cast<int>(ImGuiTabBarFlags_TabListPopupButton);
    e.value("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton); m.attr("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton") = static_cast<int>(ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
    e.value("ImGuiTabBarFlags_NoTabListScrollingButtons", ImGuiTabBarFlags_NoTabListScrollingButtons); m.attr("ImGuiTabBarFlags_NoTabListScrollingButtons") = static_cast<int>(ImGuiTabBarFlags_NoTabListScrollingButtons);
    e.value("ImGuiTabBarFlags_NoTooltip",              ImGuiTabBarFlags_NoTooltip);              m.attr("ImGuiTabBarFlags_NoTooltip")              = static_cast<int>(ImGuiTabBarFlags_NoTooltip);
    e.value("ImGuiTabBarFlags_FittingPolicyResizeDown", ImGuiTabBarFlags_FittingPolicyResizeDown); m.attr("ImGuiTabBarFlags_FittingPolicyResizeDown") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyResizeDown);
    e.value("ImGuiTabBarFlags_FittingPolicyScroll",    ImGuiTabBarFlags_FittingPolicyScroll);    m.attr("ImGuiTabBarFlags_FittingPolicyScroll")    = static_cast<int>(ImGuiTabBarFlags_FittingPolicyScroll);
    e.value("ImGuiTabBarFlags_FittingPolicyMask_",     ImGuiTabBarFlags_FittingPolicyMask_);     m.attr("ImGuiTabBarFlags_FittingPolicyMask_")     = static_cast<int>(ImGuiTabBarFlags_FittingPolicyMask_);
    e.value("ImGuiTabBarFlags_FittingPolicyDefault_",  ImGuiTabBarFlags_FittingPolicyDefault_);  m.attr("ImGuiTabBarFlags_FittingPolicyDefault_")  = static_cast<int>(ImGuiTabBarFlags_FittingPolicyDefault_);
  ;
  }

  { // ImGuiTabItemFlags ImGuiTabItemFlags_
  auto e = nb::enum_<ImGuiTabItemFlags_>(m, "ImGuiTabItemFlags");
    e.value("ImGuiTabItemFlags_None",                  ImGuiTabItemFlags_None);                  m.attr("ImGuiTabItemFlags_None")                  = static_cast<int>(ImGuiTabItemFlags_None);
    e.value("ImGuiTabItemFlags_UnsavedDocument",       ImGuiTabItemFlags_UnsavedDocument);       m.attr("ImGuiTabItemFlags_UnsavedDocument")       = static_cast<int>(ImGuiTabItemFlags_UnsavedDocument);
    e.value("ImGuiTabItemFlags_SetSelected",           ImGuiTabItemFlags_SetSelected);           m.attr("ImGuiTabItemFlags_SetSelected")           = static_cast<int>(ImGuiTabItemFlags_SetSelected);
    e.value("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton); m.attr("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton") = static_cast<int>(ImGuiTabItemFlags_NoCloseWithMiddleMouseButton);
    e.value("ImGuiTabItemFlags_NoPushId",              ImGuiTabItemFlags_NoPushId);              m.attr("ImGuiTabItemFlags_NoPushId")              = static_cast<int>(ImGuiTabItemFlags_NoPushId);
  ;
  }

  { // ImGuiFocusedFlags ImGuiFocusedFlags_
  auto e = nb::enum_<ImGuiFocusedFlags_>(m, "ImGuiFocusedFlags");
    e.value("ImGuiFocusedFlags_None",                  ImGuiFocusedFlags_None);                  m.attr("ImGuiFocusedFlags_None")                  = static_cast<int>(ImGuiFocusedFlags_None);
    e.value("ImGuiFocusedFlags_ChildWindows",          ImGuiFocusedFlags_ChildWindows);          m.attr("ImGuiFocusedFlags_ChildWindows")          = static_cast<int>(ImGuiFocusedFlags_ChildWindows);
    e.value("ImGuiFocusedFlags_RootWindow",            ImGuiFocusedFlags_RootWindow);            m.attr("ImGuiFocusedFlags_RootWindow")            = static_cast<int>(ImGuiFocusedFlags_RootWindow);
    e.value("ImGuiFocusedFlags_AnyWindow",             ImGuiFocusedFlags_AnyWindow);             m.attr("ImGuiFocusedFlags_AnyWindow")             = static_cast<int>(ImGuiFocusedFlags_AnyWindow);
    e.value("ImGuiFocusedFlags_RootAndChildWindows",   ImGuiFocusedFlags_RootAndChildWindows);   m.attr("ImGuiFocusedFlags_RootAndChildWindows")   = static_cast<int>(ImGuiFocusedFlags_RootAndChildWindows);
  ;
  }

  { // ImGuiHoveredFlags ImGuiHoveredFlags_
  auto e = nb::enum_<ImGuiHoveredFlags_>(m, "ImGuiHoveredFlags");
    e.value("ImGuiHoveredFlags_None",                  ImGuiHoveredFlags_None);                  m.attr("ImGuiHoveredFlags_None")                  = static_cast<int>(ImGuiHoveredFlags_None);
    e.value("ImGuiHoveredFlags_ChildWindows",          ImGuiHoveredFlags_ChildWindows);          m.attr("ImGuiHoveredFlags_ChildWindows")          = static_cast<int>(ImGuiHoveredFlags_ChildWindows);
    e.value("ImGuiHoveredFlags_RootWindow",            ImGuiHoveredFlags_RootWindow);            m.attr("ImGuiHoveredFlags_RootWindow")            = static_cast<int>(ImGuiHoveredFlags_RootWindow);
    e.value("ImGuiHoveredFlags_AnyWindow",             ImGuiHoveredFlags_AnyWindow);             m.attr("ImGuiHoveredFlags_AnyWindow")             = static_cast<int>(ImGuiHoveredFlags_AnyWindow);
    e.value("ImGuiHoveredFlags_AllowWhenBlockedByPopup", ImGuiHoveredFlags_AllowWhenBlockedByPopup); m.attr("ImGuiHoveredFlags_AllowWhenBlockedByPopup") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
    e.value("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem", ImGuiHoveredFlags_AllowWhenBlockedByActiveItem); m.attr("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
    e.value("ImGuiHoveredFlags_AllowWhenOverlapped",   ImGuiHoveredFlags_AllowWhenOverlapped);   m.attr("ImGuiHoveredFlags_AllowWhenOverlapped")   = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlapped);
    e.value("ImGuiHoveredFlags_AllowWhenDisabled",     ImGuiHoveredFlags_AllowWhenDisabled);     m.attr("ImGuiHoveredFlags_AllowWhenDisabled")     = static_cast<int>(ImGuiHoveredFlags_AllowWhenDisabled);
    e.value("ImGuiHoveredFlags_RectOnly",              ImGuiHoveredFlags_RectOnly);              m.attr("ImGuiHoveredFlags_RectOnly")              = static_cast<int>(ImGuiHoveredFlags_RectOnly);
    e.value("ImGuiHoveredFlags_RootAndChildWindows",   ImGuiHoveredFlags_RootAndChildWindows);   m.attr("ImGuiHoveredFlags_RootAndChildWindows")   = static_cast<int>(ImGuiHoveredFlags_RootAndChildWindows);
  ;
  }

  { // ImGuiDragDropFlags ImGuiDragDropFlags_
  auto e = nb::enum_<ImGuiDragDropFlags_>(m, "ImGuiDragDropFlags");
    e.value("ImGuiDragDropFlags_None",                 ImGuiDragDropFlags_None);                 m.attr("ImGuiDragDropFlags_None")                 = static_cast<int>(ImGuiDragDropFlags_None);
    e.value("ImGuiDragDropFlags_SourceNoPreviewTooltip", ImGuiDragDropFlags_SourceNoPreviewTooltip); m.attr("ImGuiDragDropFlags_SourceNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_SourceNoPreviewTooltip);
    e.value("ImGuiDragDropFlags_SourceNoDisableHover", ImGuiDragDropFlags_SourceNoDisableHover); m.attr("ImGuiDragDropFlags_SourceNoDisableHover") = static_cast<int>(ImGuiDragDropFlags_SourceNoDisableHover);
    e.value("ImGuiDragDropFlags_SourceNoHoldToOpenOthers", ImGuiDragDropFlags_SourceNoHoldToOpenOthers); m.attr("ImGuiDragDropFlags_SourceNoHoldToOpenOthers") = static_cast<int>(ImGuiDragDropFlags_SourceNoHoldToOpenOthers);
    e.value("ImGuiDragDropFlags_SourceAllowNullID",    ImGuiDragDropFlags_SourceAllowNullID);    m.attr("ImGuiDragDropFlags_SourceAllowNullID")    = static_cast<int>(ImGuiDragDropFlags_SourceAllowNullID);
    e.value("ImGuiDragDropFlags_SourceExtern",         ImGuiDragDropFlags_SourceExtern);         m.attr("ImGuiDragDropFlags_SourceExtern")         = static_cast<int>(ImGuiDragDropFlags_SourceExtern);
    e.value("ImGuiDragDropFlags_SourceAutoExpirePayload", ImGuiDragDropFlags_SourceAutoExpirePayload); m.attr("ImGuiDragDropFlags_SourceAutoExpirePayload") = static_cast<int>(ImGuiDragDropFlags_SourceAutoExpirePayload);
    e.value("ImGuiDragDropFlags_AcceptBeforeDelivery", ImGuiDragDropFlags_AcceptBeforeDelivery); m.attr("ImGuiDragDropFlags_AcceptBeforeDelivery") = static_cast<int>(ImGuiDragDropFlags_AcceptBeforeDelivery);
    e.value("ImGuiDragDropFlags_AcceptNoDrawDefaultRect", ImGuiDragDropFlags_AcceptNoDrawDefaultRect); m.attr("ImGuiDragDropFlags_AcceptNoDrawDefaultRect") = static_cast<int>(ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
    e.value("ImGuiDragDropFlags_AcceptNoPreviewTooltip", ImGuiDragDropFlags_AcceptNoPreviewTooltip); m.attr("ImGuiDragDropFlags_AcceptNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_AcceptNoPreviewTooltip);
    e.value("ImGuiDragDropFlags_AcceptPeekOnly",       ImGuiDragDropFlags_AcceptPeekOnly);       m.attr("ImGuiDragDropFlags_AcceptPeekOnly")       = static_cast<int>(ImGuiDragDropFlags_AcceptPeekOnly);
  ;
  }

  { // ImGuiDataType ImGuiDataType_
  auto e = nb::enum_<ImGuiDataType_>(m, "ImGuiDataType");
    e.value("ImGuiDataType_S8",                        ImGuiDataType_S8);                        m.attr("ImGuiDataType_S8")                        = static_cast<int>(ImGuiDataType_S8);
    e.value("ImGuiDataType_U8",                        ImGuiDataType_U8);                        m.attr("ImGuiDataType_U8")                        = static_cast<int>(ImGuiDataType_U8);
    e.value("ImGuiDataType_S16",                       ImGuiDataType_S16);                       m.attr("ImGuiDataType_S16")                       = static_cast<int>(ImGuiDataType_S16);
    e.value("ImGuiDataType_U16",                       ImGuiDataType_U16);                       m.attr("ImGuiDataType_U16")                       = static_cast<int>(ImGuiDataType_U16);
    e.value("ImGuiDataType_S32",                       ImGuiDataType_S32);                       m.attr("ImGuiDataType_S32")                       = static_cast<int>(ImGuiDataType_S32);
    e.value("ImGuiDataType_U32",                       ImGuiDataType_U32);                       m.attr("ImGuiDataType_U32")                       = static_cast<int>(ImGuiDataType_U32);
    e.value("ImGuiDataType_S64",                       ImGuiDataType_S64);                       m.attr("ImGuiDataType_S64")                       = static_cast<int>(ImGuiDataType_S64);
    e.value("ImGuiDataType_U64",                       ImGuiDataType_U64);                       m.attr("ImGuiDataType_U64")                       = static_cast<int>(ImGuiDataType_U64);
    e.value("ImGuiDataType_Float",                     ImGuiDataType_Float);                     m.attr("ImGuiDataType_Float")                     = static_cast<int>(ImGuiDataType_Float);
    e.value("ImGuiDataType_Double",                    ImGuiDataType_Double);                    m.attr("ImGuiDataType_Double")                    = static_cast<int>(ImGuiDataType_Double);
    e.value("ImGuiDataType_COUNT",                     ImGuiDataType_COUNT);                     m.attr("ImGuiDataType_COUNT")                     = static_cast<int>(ImGuiDataType_COUNT);
  ;
  }

  { // ImGuiInputFlags ImGuiInputFlags_
  auto e = nb::enum_<ImGuiInputFlags_>(m, "ImGuiInputFlags");
    e.value("ImGuiInputFlags_None",                    ImGuiInputFlags_None);                    m.attr("ImGuiInputFlags_None")                    = static_cast<int>(ImGuiInputFlags_None);
    e.value("ImGuiInputFlags_Repeat",                  ImGuiInputFlags_Repeat);                  m.attr("ImGuiInputFlags_Repeat")                  = static_cast<int>(ImGuiInputFlags_Repeat);
    e.value("ImGuiInputFlags_RouteActive",             ImGuiInputFlags_RouteActive);             m.attr("ImGuiInputFlags_RouteActive")             = static_cast<int>(ImGuiInputFlags_RouteActive);
    e.value("ImGuiInputFlags_RouteFocused",            ImGuiInputFlags_RouteFocused);            m.attr("ImGuiInputFlags_RouteFocused")            = static_cast<int>(ImGuiInputFlags_RouteFocused);
    e.value("ImGuiInputFlags_RouteGlobal",             ImGuiInputFlags_RouteGlobal);             m.attr("ImGuiInputFlags_RouteGlobal")             = static_cast<int>(ImGuiInputFlags_RouteGlobal);
    e.value("ImGuiInputFlags_RouteAlways",             ImGuiInputFlags_RouteAlways);             m.attr("ImGuiInputFlags_RouteAlways")             = static_cast<int>(ImGuiInputFlags_RouteAlways);
    e.value("ImGuiInputFlags_RouteOverFocused",        ImGuiInputFlags_RouteOverFocused);        m.attr("ImGuiInputFlags_RouteOverFocused")        = static_cast<int>(ImGuiInputFlags_RouteOverFocused);
    e.value("ImGuiInputFlags_RouteOverActive",         ImGuiInputFlags_RouteOverActive);         m.attr("ImGuiInputFlags_RouteOverActive")         = static_cast<int>(ImGuiInputFlags_RouteOverActive);
    e.value("ImGuiInputFlags_RouteUnlessBgFocused",    ImGuiInputFlags_RouteUnlessBgFocused);    m.attr("ImGuiInputFlags_RouteUnlessBgFocused")    = static_cast<int>(ImGuiInputFlags_RouteUnlessBgFocused);
    e.value("ImGuiInputFlags_RouteFromRootWindow",     ImGuiInputFlags_RouteFromRootWindow);     m.attr("ImGuiInputFlags_RouteFromRootWindow")     = static_cast<int>(ImGuiInputFlags_RouteFromRootWindow);
    e.value("ImGuiInputFlags_Tooltip",                 ImGuiInputFlags_Tooltip);                 m.attr("ImGuiInputFlags_Tooltip")                 = static_cast<int>(ImGuiInputFlags_Tooltip);
  ;
  }

  { // ImGuiConfigFlags ImGuiConfigFlags_
  auto e = nb::enum_<ImGuiConfigFlags_>(m, "ImGuiConfigFlags");
    e.value("ImGuiConfigFlags_None",                   ImGuiConfigFlags_None);                   m.attr("ImGuiConfigFlags_None")                   = static_cast<int>(ImGuiConfigFlags_None);
    e.value("ImGuiConfigFlags_NavEnableKeyboard",      ImGuiConfigFlags_NavEnableKeyboard);      m.attr("ImGuiConfigFlags_NavEnableKeyboard")      = static_cast<int>(ImGuiConfigFlags_NavEnableKeyboard);
    e.value("ImGuiConfigFlags_NavEnableGamepad",       ImGuiConfigFlags_NavEnableGamepad);       m.attr("ImGuiConfigFlags_NavEnableGamepad")       = static_cast<int>(ImGuiConfigFlags_NavEnableGamepad);
    e.value("ImGuiConfigFlags_NavEnableSetMousePos",   ImGuiConfigFlags_NavEnableSetMousePos);   m.attr("ImGuiConfigFlags_NavEnableSetMousePos")   = static_cast<int>(ImGuiConfigFlags_NavEnableSetMousePos);
    e.value("ImGuiConfigFlags_NavNoCaptureKeyboard",   ImGuiConfigFlags_NavNoCaptureKeyboard);   m.attr("ImGuiConfigFlags_NavNoCaptureKeyboard")   = static_cast<int>(ImGuiConfigFlags_NavNoCaptureKeyboard);
    e.value("ImGuiConfigFlags_NoMouse",                ImGuiConfigFlags_NoMouse);                m.attr("ImGuiConfigFlags_NoMouse")                = static_cast<int>(ImGuiConfigFlags_NoMouse);
    e.value("ImGuiConfigFlags_NoMouseCursorChange",    ImGuiConfigFlags_NoMouseCursorChange);    m.attr("ImGuiConfigFlags_NoMouseCursorChange")    = static_cast<int>(ImGuiConfigFlags_NoMouseCursorChange);
    e.value("ImGuiConfigFlags_IsSRGB",                 ImGuiConfigFlags_IsSRGB);                 m.attr("ImGuiConfigFlags_IsSRGB")                 = static_cast<int>(ImGuiConfigFlags_IsSRGB);
    e.value("ImGuiConfigFlags_IsTouchScreen",          ImGuiConfigFlags_IsTouchScreen);          m.attr("ImGuiConfigFlags_IsTouchScreen")          = static_cast<int>(ImGuiConfigFlags_IsTouchScreen);
  ;
  }

  { // ImGuiBackendFlags ImGuiBackendFlags_
  auto e = nb::enum_<ImGuiBackendFlags_>(m, "ImGuiBackendFlags");
    e.value("ImGuiBackendFlags_None",                  ImGuiBackendFlags_None);                  m.attr("ImGuiBackendFlags_None")                  = static_cast<int>(ImGuiBackendFlags_None);
    e.value("ImGuiBackendFlags_HasGamepad",            ImGuiBackendFlags_HasGamepad);            m.attr("ImGuiBackendFlags_HasGamepad")            = static_cast<int>(ImGuiBackendFlags_HasGamepad);
    e.value("ImGuiBackendFlags_HasMouseCursors",       ImGuiBackendFlags_HasMouseCursors);       m.attr("ImGuiBackendFlags_HasMouseCursors")       = static_cast<int>(ImGuiBackendFlags_HasMouseCursors);
    e.value("ImGuiBackendFlags_HasSetMousePos",        ImGuiBackendFlags_HasSetMousePos);        m.attr("ImGuiBackendFlags_HasSetMousePos")        = static_cast<int>(ImGuiBackendFlags_HasSetMousePos);
    e.value("ImGuiBackendFlags_RendererHasVtxOffset",  ImGuiBackendFlags_RendererHasVtxOffset);  m.attr("ImGuiBackendFlags_RendererHasVtxOffset")  = static_cast<int>(ImGuiBackendFlags_RendererHasVtxOffset);
  ;
  }

  { // ImGuiCol ImGuiCol_
  auto e = nb::enum_<ImGuiCol_>(m, "ImGuiCol");
    e.value("ImGuiCol_Text",                           ImGuiCol_Text);                           m.attr("ImGuiCol_Text")                           = static_cast<int>(ImGuiCol_Text);
    e.value("ImGuiCol_TextDisabled",                   ImGuiCol_TextDisabled);                   m.attr("ImGuiCol_TextDisabled")                   = static_cast<int>(ImGuiCol_TextDisabled);
    e.value("ImGuiCol_WindowBg",                       ImGuiCol_WindowBg);                       m.attr("ImGuiCol_WindowBg")                       = static_cast<int>(ImGuiCol_WindowBg);
    e.value("ImGuiCol_ChildBg",                        ImGuiCol_ChildBg);                        m.attr("ImGuiCol_ChildBg")                        = static_cast<int>(ImGuiCol_ChildBg);
    e.value("ImGuiCol_PopupBg",                        ImGuiCol_PopupBg);                        m.attr("ImGuiCol_PopupBg")                        = static_cast<int>(ImGuiCol_PopupBg);
    e.value("ImGuiCol_Border",                         ImGuiCol_Border);                         m.attr("ImGuiCol_Border")                         = static_cast<int>(ImGuiCol_Border);
    e.value("ImGuiCol_BorderShadow",                   ImGuiCol_BorderShadow);                   m.attr("ImGuiCol_BorderShadow")                   = static_cast<int>(ImGuiCol_BorderShadow);
    e.value("ImGuiCol_FrameBg",                        ImGuiCol_FrameBg);                        m.attr("ImGuiCol_FrameBg")                        = static_cast<int>(ImGuiCol_FrameBg);
    e.value("ImGuiCol_FrameBgHovered",                 ImGuiCol_FrameBgHovered);                 m.attr("ImGuiCol_FrameBgHovered")                 = static_cast<int>(ImGuiCol_FrameBgHovered);
    e.value("ImGuiCol_FrameBgActive",                  ImGuiCol_FrameBgActive);                  m.attr("ImGuiCol_FrameBgActive")                  = static_cast<int>(ImGuiCol_FrameBgActive);
    e.value("ImGuiCol_TitleBg",                        ImGuiCol_TitleBg);                        m.attr("ImGuiCol_TitleBg")                        = static_cast<int>(ImGuiCol_TitleBg);
    e.value("ImGuiCol_TitleBgActive",                  ImGuiCol_TitleBgActive);                  m.attr("ImGuiCol_TitleBgActive")                  = static_cast<int>(ImGuiCol_TitleBgActive);
    e.value("ImGuiCol_TitleBgCollapsed",               ImGuiCol_TitleBgCollapsed);               m.attr("ImGuiCol_TitleBgCollapsed")               = static_cast<int>(ImGuiCol_TitleBgCollapsed);
    e.value("ImGuiCol_MenuBarBg",                      ImGuiCol_MenuBarBg);                      m.attr("ImGuiCol_MenuBarBg")                      = static_cast<int>(ImGuiCol_MenuBarBg);
    e.value("ImGuiCol_ScrollbarBg",                    ImGuiCol_ScrollbarBg);                    m.attr("ImGuiCol_ScrollbarBg")                    = static_cast<int>(ImGuiCol_ScrollbarBg);
    e.value("ImGuiCol_ScrollbarGrab",                  ImGuiCol_ScrollbarGrab);                  m.attr("ImGuiCol_ScrollbarGrab")                  = static_cast<int>(ImGuiCol_ScrollbarGrab);
    e.value("ImGuiCol_ScrollbarGrabHovered",           ImGuiCol_ScrollbarGrabHovered);           m.attr("ImGuiCol_ScrollbarGrabHovered")           = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
    e.value("ImGuiCol_ScrollbarGrabActive",            ImGuiCol_ScrollbarGrabActive);            m.attr("ImGuiCol_ScrollbarGrabActive")            = static_cast<int>(ImGuiCol_ScrollbarGrabActive);
    e.value("ImGuiCol_CheckMark",                      ImGuiCol_CheckMark);                      m.attr("ImGuiCol_CheckMark")                      = static_cast<int>(ImGuiCol_CheckMark);
    e.value("ImGuiCol_SliderGrab",                     ImGuiCol_SliderGrab);                     m.attr("ImGuiCol_SliderGrab")                     = static_cast<int>(ImGuiCol_SliderGrab);
    e.value("ImGuiCol_SliderGrabActive",               ImGuiCol_SliderGrabActive);               m.attr("ImGuiCol_SliderGrabActive")               = static_cast<int>(ImGuiCol_SliderGrabActive);
    e.value("ImGuiCol_Button",                         ImGuiCol_Button);                         m.attr("ImGuiCol_Button")                         = static_cast<int>(ImGuiCol_Button);
    e.value("ImGuiCol_ButtonHovered",                  ImGuiCol_ButtonHovered);                  m.attr("ImGuiCol_ButtonHovered")                  = static_cast<int>(ImGuiCol_ButtonHovered);
    e.value("ImGuiCol_ButtonActive",                   ImGuiCol_ButtonActive);                   m.attr("ImGuiCol_ButtonActive")                   = static_cast<int>(ImGuiCol_ButtonActive);
    e.value("ImGuiCol_Header",                         ImGuiCol_Header);                         m.attr("ImGuiCol_Header")                         = static_cast<int>(ImGuiCol_Header);
    e.value("ImGuiCol_HeaderHovered",                  ImGuiCol_HeaderHovered);                  m.attr("ImGuiCol_HeaderHovered")                  = static_cast<int>(ImGuiCol_HeaderHovered);
    e.value("ImGuiCol_HeaderActive",                   ImGuiCol_HeaderActive);                   m.attr("ImGuiCol_HeaderActive")                   = static_cast<int>(ImGuiCol_HeaderActive);
    e.value("ImGuiCol_Separator",                      ImGuiCol_Separator);                      m.attr("ImGuiCol_Separator")                      = static_cast<int>(ImGuiCol_Separator);
    e.value("ImGuiCol_SeparatorHovered",               ImGuiCol_SeparatorHovered);               m.attr("ImGuiCol_SeparatorHovered")               = static_cast<int>(ImGuiCol_SeparatorHovered);
    e.value("ImGuiCol_SeparatorActive",                ImGuiCol_SeparatorActive);                m.attr("ImGuiCol_SeparatorActive")                = static_cast<int>(ImGuiCol_SeparatorActive);
    e.value("ImGuiCol_ResizeGrip",                     ImGuiCol_ResizeGrip);                     m.attr("ImGuiCol_ResizeGrip")                     = static_cast<int>(ImGuiCol_ResizeGrip);
    e.value("ImGuiCol_ResizeGripHovered",              ImGuiCol_ResizeGripHovered);              m.attr("ImGuiCol_ResizeGripHovered")              = static_cast<int>(ImGuiCol_ResizeGripHovered);
    e.value("ImGuiCol_ResizeGripActive",               ImGuiCol_ResizeGripActive);               m.attr("ImGuiCol_ResizeGripActive")               = static_cast<int>(ImGuiCol_ResizeGripActive);
    e.value("ImGuiCol_Tab",                            ImGuiCol_Tab);                            m.attr("ImGuiCol_Tab")                            = static_cast<int>(ImGuiCol_Tab);
    e.value("ImGuiCol_TabHovered",                     ImGuiCol_TabHovered);                     m.attr("ImGuiCol_TabHovered")                     = static_cast<int>(ImGuiCol_TabHovered);
    e.value("ImGuiCol_TabSelected",                    ImGuiCol_TabSelected);                    m.attr("ImGuiCol_TabSelected")                    = static_cast<int>(ImGuiCol_TabSelected);
    e.value("ImGuiCol_TabSelectedOverline",            ImGuiCol_TabSelectedOverline);            m.attr("ImGuiCol_TabSelectedOverline")            = static_cast<int>(ImGuiCol_TabSelectedOverline);
    e.value("ImGuiCol_TabDimmed",                      ImGuiCol_TabDimmed);                      m.attr("ImGuiCol_TabDimmed")                      = static_cast<int>(ImGuiCol_TabDimmed);
    e.value("ImGuiCol_TabDimmedSelected",              ImGuiCol_TabDimmedSelected);              m.attr("ImGuiCol_TabDimmedSelected")              = static_cast<int>(ImGuiCol_TabDimmedSelected);
    e.value("ImGuiCol_TabDimmedSelectedOverline",      ImGuiCol_TabDimmedSelectedOverline);      m.attr("ImGuiCol_TabDimmedSelectedOverline")      = static_cast<int>(ImGuiCol_TabDimmedSelectedOverline);
    e.value("ImGuiCol_TabUnfocused",                   ImGuiCol_TabUnfocused);                   m.attr("ImGuiCol_TabUnfocused")                   = static_cast<int>(ImGuiCol_TabUnfocused);
    e.value("ImGuiCol_TabUnfocusedActive",             ImGuiCol_TabUnfocusedActive);             m.attr("ImGuiCol_TabUnfocusedActive")             = static_cast<int>(ImGuiCol_TabUnfocusedActive);
    e.value("ImGuiCol_PlotLines",                      ImGuiCol_PlotLines);                      m.attr("ImGuiCol_PlotLines")                      = static_cast<int>(ImGuiCol_PlotLines);
    e.value("ImGuiCol_PlotLinesHovered",               ImGuiCol_PlotLinesHovered);               m.attr("ImGuiCol_PlotLinesHovered")               = static_cast<int>(ImGuiCol_PlotLinesHovered);
    e.value("ImGuiCol_PlotHistogram",                  ImGuiCol_PlotHistogram);                  m.attr("ImGuiCol_PlotHistogram")                  = static_cast<int>(ImGuiCol_PlotHistogram);
    e.value("ImGuiCol_PlotHistogramHovered",           ImGuiCol_PlotHistogramHovered);           m.attr("ImGuiCol_PlotHistogramHovered")           = static_cast<int>(ImGuiCol_PlotHistogramHovered);
    e.value("ImGuiCol_TableHeaderBg",                  ImGuiCol_TableHeaderBg);                  m.attr("ImGuiCol_TableHeaderBg")                  = static_cast<int>(ImGuiCol_TableHeaderBg);
    e.value("ImGuiCol_TableBorderStrong",              ImGuiCol_TableBorderStrong);              m.attr("ImGuiCol_TableBorderStrong")              = static_cast<int>(ImGuiCol_TableBorderStrong);
    e.value("ImGuiCol_TableBorderLight",               ImGuiCol_TableBorderLight);               m.attr("ImGuiCol_TableBorderLight")               = static_cast<int>(ImGuiCol_TableBorderLight);
    e.value("ImGuiCol_TableRowBg",                     ImGuiCol_TableRowBg);                     m.attr("ImGuiCol_TableRowBg")                     = static_cast<int>(ImGuiCol_TableRowBg);
    e.value("ImGuiCol_TableRowBgAlt",                  ImGuiCol_TableRowBgAlt);                  m.attr("ImGuiCol_TableRowBgAlt")                  = static_cast<int>(ImGuiCol_TableRowBgAlt);
    e.value("ImGuiCol_TextLink",                       ImGuiCol_TextLink);                       m.attr("ImGuiCol_TextLink")                       = static_cast<int>(ImGuiCol_TextLink);
    e.value("ImGuiCol_TextSelectedBg",                 ImGuiCol_TextSelectedBg);                 m.attr("ImGuiCol_TextSelectedBg")                 = static_cast<int>(ImGuiCol_TextSelectedBg);
    e.value("ImGuiCol_DragDropTarget",                 ImGuiCol_DragDropTarget);                 m.attr("ImGuiCol_DragDropTarget")                 = static_cast<int>(ImGuiCol_DragDropTarget);
    e.value("ImGuiCol_NavCursor",                      ImGuiCol_NavCursor);                      m.attr("ImGuiCol_NavCursor")                      = static_cast<int>(ImGuiCol_NavCursor);
    e.value("ImGuiCol_NavWindowingHighlight",          ImGuiCol_NavWindowingHighlight);          m.attr("ImGuiCol_NavWindowingHighlight")          = static_cast<int>(ImGuiCol_NavWindowingHighlight);
    e.value("ImGuiCol_NavWindowingDimBg",              ImGuiCol_NavWindowingDimBg);              m.attr("ImGuiCol_NavWindowingDimBg")              = static_cast<int>(ImGuiCol_NavWindowingDimBg);
    e.value("ImGuiCol_ModalWindowDimBg",               ImGuiCol_ModalWindowDimBg);               m.attr("ImGuiCol_ModalWindowDimBg")               = static_cast<int>(ImGuiCol_ModalWindowDimBg);
    e.value("ImGuiCol_COUNT",                          ImGuiCol_COUNT);                          m.attr("ImGuiCol_COUNT")                          = static_cast<int>(ImGuiCol_COUNT);
  ;
  }

  { // ImGuiStyleVar ImGuiStyleVar_
  auto e = nb::enum_<ImGuiStyleVar_>(m, "ImGuiStyleVar");
    e.value("ImGuiStyleVar_Alpha",                     ImGuiStyleVar_Alpha);                     m.attr("ImGuiStyleVar_Alpha")                     = static_cast<int>(ImGuiStyleVar_Alpha);
    e.value("ImGuiStyleVar_WindowPadding",             ImGuiStyleVar_WindowPadding);             m.attr("ImGuiStyleVar_WindowPadding")             = static_cast<int>(ImGuiStyleVar_WindowPadding);
    e.value("ImGuiStyleVar_WindowRounding",            ImGuiStyleVar_WindowRounding);            m.attr("ImGuiStyleVar_WindowRounding")            = static_cast<int>(ImGuiStyleVar_WindowRounding);
    e.value("ImGuiStyleVar_WindowBorderSize",          ImGuiStyleVar_WindowBorderSize);          m.attr("ImGuiStyleVar_WindowBorderSize")          = static_cast<int>(ImGuiStyleVar_WindowBorderSize);
    e.value("ImGuiStyleVar_WindowMinSize",             ImGuiStyleVar_WindowMinSize);             m.attr("ImGuiStyleVar_WindowMinSize")             = static_cast<int>(ImGuiStyleVar_WindowMinSize);
    e.value("ImGuiStyleVar_WindowTitleAlign",          ImGuiStyleVar_WindowTitleAlign);          m.attr("ImGuiStyleVar_WindowTitleAlign")          = static_cast<int>(ImGuiStyleVar_WindowTitleAlign);
    e.value("ImGuiStyleVar_ChildRounding",             ImGuiStyleVar_ChildRounding);             m.attr("ImGuiStyleVar_ChildRounding")             = static_cast<int>(ImGuiStyleVar_ChildRounding);
    e.value("ImGuiStyleVar_ChildBorderSize",           ImGuiStyleVar_ChildBorderSize);           m.attr("ImGuiStyleVar_ChildBorderSize")           = static_cast<int>(ImGuiStyleVar_ChildBorderSize);
    e.value("ImGuiStyleVar_PopupRounding",             ImGuiStyleVar_PopupRounding);             m.attr("ImGuiStyleVar_PopupRounding")             = static_cast<int>(ImGuiStyleVar_PopupRounding);
    e.value("ImGuiStyleVar_PopupBorderSize",           ImGuiStyleVar_PopupBorderSize);           m.attr("ImGuiStyleVar_PopupBorderSize")           = static_cast<int>(ImGuiStyleVar_PopupBorderSize);
    e.value("ImGuiStyleVar_FramePadding",              ImGuiStyleVar_FramePadding);              m.attr("ImGuiStyleVar_FramePadding")              = static_cast<int>(ImGuiStyleVar_FramePadding);
    e.value("ImGuiStyleVar_FrameRounding",             ImGuiStyleVar_FrameRounding);             m.attr("ImGuiStyleVar_FrameRounding")             = static_cast<int>(ImGuiStyleVar_FrameRounding);
    e.value("ImGuiStyleVar_FrameBorderSize",           ImGuiStyleVar_FrameBorderSize);           m.attr("ImGuiStyleVar_FrameBorderSize")           = static_cast<int>(ImGuiStyleVar_FrameBorderSize);
    e.value("ImGuiStyleVar_ItemSpacing",               ImGuiStyleVar_ItemSpacing);               m.attr("ImGuiStyleVar_ItemSpacing")               = static_cast<int>(ImGuiStyleVar_ItemSpacing);
    e.value("ImGuiStyleVar_ItemInnerSpacing",          ImGuiStyleVar_ItemInnerSpacing);          m.attr("ImGuiStyleVar_ItemInnerSpacing")          = static_cast<int>(ImGuiStyleVar_ItemInnerSpacing);
    e.value("ImGuiStyleVar_IndentSpacing",             ImGuiStyleVar_IndentSpacing);             m.attr("ImGuiStyleVar_IndentSpacing")             = static_cast<int>(ImGuiStyleVar_IndentSpacing);
    e.value("ImGuiStyleVar_ScrollbarSize",             ImGuiStyleVar_ScrollbarSize);             m.attr("ImGuiStyleVar_ScrollbarSize")             = static_cast<int>(ImGuiStyleVar_ScrollbarSize);
    e.value("ImGuiStyleVar_ScrollbarRounding",         ImGuiStyleVar_ScrollbarRounding);         m.attr("ImGuiStyleVar_ScrollbarRounding")         = static_cast<int>(ImGuiStyleVar_ScrollbarRounding);
    e.value("ImGuiStyleVar_GrabMinSize",               ImGuiStyleVar_GrabMinSize);               m.attr("ImGuiStyleVar_GrabMinSize")               = static_cast<int>(ImGuiStyleVar_GrabMinSize);
    e.value("ImGuiStyleVar_GrabRounding",              ImGuiStyleVar_GrabRounding);              m.attr("ImGuiStyleVar_GrabRounding")              = static_cast<int>(ImGuiStyleVar_GrabRounding);
    e.value("ImGuiStyleVar_TabRounding",               ImGuiStyleVar_TabRounding);               m.attr("ImGuiStyleVar_TabRounding")               = static_cast<int>(ImGuiStyleVar_TabRounding);
    e.value("ImGuiStyleVar_ButtonTextAlign",           ImGuiStyleVar_ButtonTextAlign);           m.attr("ImGuiStyleVar_ButtonTextAlign")           = static_cast<int>(ImGuiStyleVar_ButtonTextAlign);
    e.value("ImGuiStyleVar_SelectableTextAlign",       ImGuiStyleVar_SelectableTextAlign);       m.attr("ImGuiStyleVar_SelectableTextAlign")       = static_cast<int>(ImGuiStyleVar_SelectableTextAlign);
    e.value("ImGuiStyleVar_COUNT",                     ImGuiStyleVar_COUNT);                     m.attr("ImGuiStyleVar_COUNT")                     = static_cast<int>(ImGuiStyleVar_COUNT);
  ;
  }

  { // ImGuiButtonFlags ImGuiButtonFlags_
  auto e = nb::enum_<ImGuiButtonFlags_>(m, "ImGuiButtonFlags");
    e.value("ImGuiButtonFlags_None",                   ImGuiButtonFlags_None);                   m.attr("ImGuiButtonFlags_None")                   = static_cast<int>(ImGuiButtonFlags_None);
    e.value("ImGuiButtonFlags_MouseButtonLeft",        ImGuiButtonFlags_MouseButtonLeft);        m.attr("ImGuiButtonFlags_MouseButtonLeft")        = static_cast<int>(ImGuiButtonFlags_MouseButtonLeft);
    e.value("ImGuiButtonFlags_MouseButtonRight",       ImGuiButtonFlags_MouseButtonRight);       m.attr("ImGuiButtonFlags_MouseButtonRight")       = static_cast<int>(ImGuiButtonFlags_MouseButtonRight);
    e.value("ImGuiButtonFlags_MouseButtonMiddle",      ImGuiButtonFlags_MouseButtonMiddle);      m.attr("ImGuiButtonFlags_MouseButtonMiddle")      = static_cast<int>(ImGuiButtonFlags_MouseButtonMiddle);
    e.value("ImGuiButtonFlags_MouseButtonMask_",       ImGuiButtonFlags_MouseButtonMask_);       m.attr("ImGuiButtonFlags_MouseButtonMask_")       = static_cast<int>(ImGuiButtonFlags_MouseButtonMask_);
    e.value("ImGuiButtonFlags_EnableNav",              ImGuiButtonFlags_EnableNav);              m.attr("ImGuiButtonFlags_EnableNav")              = static_cast<int>(ImGuiButtonFlags_EnableNav);
  ;
  }

  { // ImGuiColorEditFlags ImGuiColorEditFlags_
  auto e = nb::enum_<ImGuiColorEditFlags_>(m, "ImGuiColorEditFlags");
    e.value("ImGuiColorEditFlags_None",                ImGuiColorEditFlags_None);                m.attr("ImGuiColorEditFlags_None")                = static_cast<int>(ImGuiColorEditFlags_None);
    e.value("ImGuiColorEditFlags_NoAlpha",             ImGuiColorEditFlags_NoAlpha);             m.attr("ImGuiColorEditFlags_NoAlpha")             = static_cast<int>(ImGuiColorEditFlags_NoAlpha);
    e.value("ImGuiColorEditFlags_NoPicker",            ImGuiColorEditFlags_NoPicker);            m.attr("ImGuiColorEditFlags_NoPicker")            = static_cast<int>(ImGuiColorEditFlags_NoPicker);
    e.value("ImGuiColorEditFlags_NoOptions",           ImGuiColorEditFlags_NoOptions);           m.attr("ImGuiColorEditFlags_NoOptions")           = static_cast<int>(ImGuiColorEditFlags_NoOptions);
    e.value("ImGuiColorEditFlags_NoSmallPreview",      ImGuiColorEditFlags_NoSmallPreview);      m.attr("ImGuiColorEditFlags_NoSmallPreview")      = static_cast<int>(ImGuiColorEditFlags_NoSmallPreview);
    e.value("ImGuiColorEditFlags_NoInputs",            ImGuiColorEditFlags_NoInputs);            m.attr("ImGuiColorEditFlags_NoInputs")            = static_cast<int>(ImGuiColorEditFlags_NoInputs);
    e.value("ImGuiColorEditFlags_NoTooltip",           ImGuiColorEditFlags_NoTooltip);           m.attr("ImGuiColorEditFlags_NoTooltip")           = static_cast<int>(ImGuiColorEditFlags_NoTooltip);
    e.value("ImGuiColorEditFlags_NoLabel",             ImGuiColorEditFlags_NoLabel);             m.attr("ImGuiColorEditFlags_NoLabel")             = static_cast<int>(ImGuiColorEditFlags_NoLabel);
    e.value("ImGuiColorEditFlags_NoSidePreview",       ImGuiColorEditFlags_NoSidePreview);       m.attr("ImGuiColorEditFlags_NoSidePreview")       = static_cast<int>(ImGuiColorEditFlags_NoSidePreview);
    e.value("ImGuiColorEditFlags_NoDragDrop",          ImGuiColorEditFlags_NoDragDrop);          m.attr("ImGuiColorEditFlags_NoDragDrop")          = static_cast<int>(ImGuiColorEditFlags_NoDragDrop);
    e.value("ImGuiColorEditFlags_NoBorder",            ImGuiColorEditFlags_NoBorder);            m.attr("ImGuiColorEditFlags_NoBorder")            = static_cast<int>(ImGuiColorEditFlags_NoBorder);
    e.value("ImGuiColorEditFlags_AlphaBar",            ImGuiColorEditFlags_AlphaBar);            m.attr("ImGuiColorEditFlags_AlphaBar")            = static_cast<int>(ImGuiColorEditFlags_AlphaBar);
    e.value("ImGuiColorEditFlags_AlphaPreview",        ImGuiColorEditFlags_AlphaPreview);        m.attr("ImGuiColorEditFlags_AlphaPreview")        = static_cast<int>(ImGuiColorEditFlags_AlphaPreview);
    e.value("ImGuiColorEditFlags_AlphaPreviewHalf",    ImGuiColorEditFlags_AlphaPreviewHalf);    m.attr("ImGuiColorEditFlags_AlphaPreviewHalf")    = static_cast<int>(ImGuiColorEditFlags_AlphaPreviewHalf);
    e.value("ImGuiColorEditFlags_HDR",                 ImGuiColorEditFlags_HDR);                 m.attr("ImGuiColorEditFlags_HDR")                 = static_cast<int>(ImGuiColorEditFlags_HDR);
    e.value("ImGuiColorEditFlags_DisplayRGB",          ImGuiColorEditFlags_DisplayRGB);          m.attr("ImGuiColorEditFlags_DisplayRGB")          = static_cast<int>(ImGuiColorEditFlags_DisplayRGB);
    e.value("ImGuiColorEditFlags_DisplayHSV",          ImGuiColorEditFlags_DisplayHSV);          m.attr("ImGuiColorEditFlags_DisplayHSV")          = static_cast<int>(ImGuiColorEditFlags_DisplayHSV);
    e.value("ImGuiColorEditFlags_DisplayHex",          ImGuiColorEditFlags_DisplayHex);          m.attr("ImGuiColorEditFlags_DisplayHex")          = static_cast<int>(ImGuiColorEditFlags_DisplayHex);
    e.value("ImGuiColorEditFlags_Uint8",               ImGuiColorEditFlags_Uint8);               m.attr("ImGuiColorEditFlags_Uint8")               = static_cast<int>(ImGuiColorEditFlags_Uint8);
    e.value("ImGuiColorEditFlags_Float",               ImGuiColorEditFlags_Float);               m.attr("ImGuiColorEditFlags_Float")               = static_cast<int>(ImGuiColorEditFlags_Float);
    e.value("ImGuiColorEditFlags_PickerHueBar",        ImGuiColorEditFlags_PickerHueBar);        m.attr("ImGuiColorEditFlags_PickerHueBar")        = static_cast<int>(ImGuiColorEditFlags_PickerHueBar);
    e.value("ImGuiColorEditFlags_PickerHueWheel",      ImGuiColorEditFlags_PickerHueWheel);      m.attr("ImGuiColorEditFlags_PickerHueWheel")      = static_cast<int>(ImGuiColorEditFlags_PickerHueWheel);
    e.value("ImGuiColorEditFlags_InputRGB",            ImGuiColorEditFlags_InputRGB);            m.attr("ImGuiColorEditFlags_InputRGB")            = static_cast<int>(ImGuiColorEditFlags_InputRGB);
    e.value("ImGuiColorEditFlags_InputHSV",            ImGuiColorEditFlags_InputHSV);            m.attr("ImGuiColorEditFlags_InputHSV")            = static_cast<int>(ImGuiColorEditFlags_InputHSV);
  ;
  }

  { // ImGuiSliderFlags ImGuiSliderFlags_
  auto e = nb::enum_<ImGuiSliderFlags_>(m, "ImGuiSliderFlags");
    e.value("ImGuiSliderFlags_None",                   ImGuiSliderFlags_None);                   m.attr("ImGuiSliderFlags_None")                   = static_cast<int>(ImGuiSliderFlags_None);
    e.value("ImGuiSliderFlags_Logarithmic",            ImGuiSliderFlags_Logarithmic);            m.attr("ImGuiSliderFlags_Logarithmic")            = static_cast<int>(ImGuiSliderFlags_Logarithmic);
    e.value("ImGuiSliderFlags_NoRoundToFormat",        ImGuiSliderFlags_NoRoundToFormat);        m.attr("ImGuiSliderFlags_NoRoundToFormat")        = static_cast<int>(ImGuiSliderFlags_NoRoundToFormat);
    e.value("ImGuiSliderFlags_NoInput",                ImGuiSliderFlags_NoInput);                m.attr("ImGuiSliderFlags_NoInput")                = static_cast<int>(ImGuiSliderFlags_NoInput);
    e.value("ImGuiSliderFlags_WrapAround",             ImGuiSliderFlags_WrapAround);             m.attr("ImGuiSliderFlags_WrapAround")             = static_cast<int>(ImGuiSliderFlags_WrapAround);
    e.value("ImGuiSliderFlags_ClampOnInput",           ImGuiSliderFlags_ClampOnInput);           m.attr("ImGuiSliderFlags_ClampOnInput")           = static_cast<int>(ImGuiSliderFlags_ClampOnInput);
    e.value("ImGuiSliderFlags_ClampZeroRange",         ImGuiSliderFlags_ClampZeroRange);         m.attr("ImGuiSliderFlags_ClampZeroRange")         = static_cast<int>(ImGuiSliderFlags_ClampZeroRange);
    e.value("ImGuiSliderFlags_NoSpeedTweaks",          ImGuiSliderFlags_NoSpeedTweaks);          m.attr("ImGuiSliderFlags_NoSpeedTweaks")          = static_cast<int>(ImGuiSliderFlags_NoSpeedTweaks);
    e.value("ImGuiSliderFlags_AlwaysClamp",            ImGuiSliderFlags_AlwaysClamp);            m.attr("ImGuiSliderFlags_AlwaysClamp")            = static_cast<int>(ImGuiSliderFlags_AlwaysClamp);
    e.value("ImGuiSliderFlags_InvalidMask_",           ImGuiSliderFlags_InvalidMask_);           m.attr("ImGuiSliderFlags_InvalidMask_")           = static_cast<int>(ImGuiSliderFlags_InvalidMask_);
  ;
  }

  { // ImGuiMouseButton ImGuiMouseButton_
  auto e = nb::enum_<ImGuiMouseButton_>(m, "ImGuiMouseButton");
    e.value("ImGuiMouseButton_Left",                   ImGuiMouseButton_Left);                   m.attr("ImGuiMouseButton_Left")                   = static_cast<int>(ImGuiMouseButton_Left);
    e.value("ImGuiMouseButton_Right",                  ImGuiMouseButton_Right);                  m.attr("ImGuiMouseButton_Right")                  = static_cast<int>(ImGuiMouseButton_Right);
    e.value("ImGuiMouseButton_Middle",                 ImGuiMouseButton_Middle);                 m.attr("ImGuiMouseButton_Middle")                 = static_cast<int>(ImGuiMouseButton_Middle);
    e.value("ImGuiMouseButton_COUNT",                  ImGuiMouseButton_COUNT);                  m.attr("ImGuiMouseButton_COUNT")                  = static_cast<int>(ImGuiMouseButton_COUNT);
  ;
  }

  { // ImGuiMouseCursor ImGuiMouseCursor_
  auto e = nb::enum_<ImGuiMouseCursor_>(m, "ImGuiMouseCursor");
    e.value("ImGuiMouseCursor_None",                   ImGuiMouseCursor_None);                   m.attr("ImGuiMouseCursor_None")                   = static_cast<int>(ImGuiMouseCursor_None);
    e.value("ImGuiMouseCursor_Arrow",                  ImGuiMouseCursor_Arrow);                  m.attr("ImGuiMouseCursor_Arrow")                  = static_cast<int>(ImGuiMouseCursor_Arrow);
    e.value("ImGuiMouseCursor_TextInput",              ImGuiMouseCursor_TextInput);              m.attr("ImGuiMouseCursor_TextInput")              = static_cast<int>(ImGuiMouseCursor_TextInput);
    e.value("ImGuiMouseCursor_ResizeAll",              ImGuiMouseCursor_ResizeAll);              m.attr("ImGuiMouseCursor_ResizeAll")              = static_cast<int>(ImGuiMouseCursor_ResizeAll);
    e.value("ImGuiMouseCursor_ResizeNS",               ImGuiMouseCursor_ResizeNS);               m.attr("ImGuiMouseCursor_ResizeNS")               = static_cast<int>(ImGuiMouseCursor_ResizeNS);
    e.value("ImGuiMouseCursor_ResizeEW",               ImGuiMouseCursor_ResizeEW);               m.attr("ImGuiMouseCursor_ResizeEW")               = static_cast<int>(ImGuiMouseCursor_ResizeEW);
    e.value("ImGuiMouseCursor_ResizeNESW",             ImGuiMouseCursor_ResizeNESW);             m.attr("ImGuiMouseCursor_ResizeNESW")             = static_cast<int>(ImGuiMouseCursor_ResizeNESW);
    e.value("ImGuiMouseCursor_ResizeNWSE",             ImGuiMouseCursor_ResizeNWSE);             m.attr("ImGuiMouseCursor_ResizeNWSE")             = static_cast<int>(ImGuiMouseCursor_ResizeNWSE);
    e.value("ImGuiMouseCursor_Hand",                   ImGuiMouseCursor_Hand);                   m.attr("ImGuiMouseCursor_Hand")                   = static_cast<int>(ImGuiMouseCursor_Hand);
    e.value("ImGuiMouseCursor_NotAllowed",             ImGuiMouseCursor_NotAllowed);             m.attr("ImGuiMouseCursor_NotAllowed")             = static_cast<int>(ImGuiMouseCursor_NotAllowed);
    e.value("ImGuiMouseCursor_COUNT",                  ImGuiMouseCursor_COUNT);                  m.attr("ImGuiMouseCursor_COUNT")                  = static_cast<int>(ImGuiMouseCursor_COUNT);
  ;
  }

  { // ImGuiMouseSource ImGuiMouseSource
  auto e = nb::enum_<ImGuiMouseSource>(m, "ImGuiMouseSource");
    e.value("ImGuiMouseSource_Mouse",                  ImGuiMouseSource_Mouse);                  m.attr("ImGuiMouseSource_Mouse")                  = static_cast<int>(ImGuiMouseSource_Mouse);
    e.value("ImGuiMouseSource_TouchScreen",            ImGuiMouseSource_TouchScreen);            m.attr("ImGuiMouseSource_TouchScreen")            = static_cast<int>(ImGuiMouseSource_TouchScreen);
    e.value("ImGuiMouseSource_Pen",                    ImGuiMouseSource_Pen);                    m.attr("ImGuiMouseSource_Pen")                    = static_cast<int>(ImGuiMouseSource_Pen);
    e.value("ImGuiMouseSource_COUNT",                  ImGuiMouseSource_COUNT);                  m.attr("ImGuiMouseSource_COUNT")                  = static_cast<int>(ImGuiMouseSource_COUNT);
  ;
  }

  { // ImGuiCond ImGuiCond_
  auto e = nb::enum_<ImGuiCond_>(m, "ImGuiCond");
    e.value("ImGuiCond_Always",                        ImGuiCond_Always);                        m.attr("ImGuiCond_Always")                        = static_cast<int>(ImGuiCond_Always);
    e.value("ImGuiCond_Once",                          ImGuiCond_Once);                          m.attr("ImGuiCond_Once")                          = static_cast<int>(ImGuiCond_Once);
    e.value("ImGuiCond_FirstUseEver",                  ImGuiCond_FirstUseEver);                  m.attr("ImGuiCond_FirstUseEver")                  = static_cast<int>(ImGuiCond_FirstUseEver);
    e.value("ImGuiCond_Appearing",                     ImGuiCond_Appearing);                     m.attr("ImGuiCond_Appearing")                     = static_cast<int>(ImGuiCond_Appearing);
  ;
  }

  { // ImGuiTableFlags ImGuiTableFlags_
  auto e = nb::enum_<ImGuiTableFlags_>(m, "ImGuiTableFlags");
    e.value("ImGuiTableFlags_None",                    ImGuiTableFlags_None);                    m.attr("ImGuiTableFlags_None")                    = static_cast<int>(ImGuiTableFlags_None);
    e.value("ImGuiTableFlags_Resizable",               ImGuiTableFlags_Resizable);               m.attr("ImGuiTableFlags_Resizable")               = static_cast<int>(ImGuiTableFlags_Resizable);
    e.value("ImGuiTableFlags_Reorderable",             ImGuiTableFlags_Reorderable);             m.attr("ImGuiTableFlags_Reorderable")             = static_cast<int>(ImGuiTableFlags_Reorderable);
    e.value("ImGuiTableFlags_Hideable",                ImGuiTableFlags_Hideable);                m.attr("ImGuiTableFlags_Hideable")                = static_cast<int>(ImGuiTableFlags_Hideable);
    e.value("ImGuiTableFlags_Sortable",                ImGuiTableFlags_Sortable);                m.attr("ImGuiTableFlags_Sortable")                = static_cast<int>(ImGuiTableFlags_Sortable);
    e.value("ImGuiTableFlags_NoSavedSettings",         ImGuiTableFlags_NoSavedSettings);         m.attr("ImGuiTableFlags_NoSavedSettings")         = static_cast<int>(ImGuiTableFlags_NoSavedSettings);
    e.value("ImGuiTableFlags_ContextMenuInBody",       ImGuiTableFlags_ContextMenuInBody);       m.attr("ImGuiTableFlags_ContextMenuInBody")       = static_cast<int>(ImGuiTableFlags_ContextMenuInBody);
    e.value("ImGuiTableFlags_RowBg",                   ImGuiTableFlags_RowBg);                   m.attr("ImGuiTableFlags_RowBg")                   = static_cast<int>(ImGuiTableFlags_RowBg);
    e.value("ImGuiTableFlags_BordersInnerH",           ImGuiTableFlags_BordersInnerH);           m.attr("ImGuiTableFlags_BordersInnerH")           = static_cast<int>(ImGuiTableFlags_BordersInnerH);
    e.value("ImGuiTableFlags_BordersOuterH",           ImGuiTableFlags_BordersOuterH);           m.attr("ImGuiTableFlags_BordersOuterH")           = static_cast<int>(ImGuiTableFlags_BordersOuterH);
    e.value("ImGuiTableFlags_BordersInnerV",           ImGuiTableFlags_BordersInnerV);           m.attr("ImGuiTableFlags_BordersInnerV")           = static_cast<int>(ImGuiTableFlags_BordersInnerV);
    e.value("ImGuiTableFlags_BordersOuterV",           ImGuiTableFlags_BordersOuterV);           m.attr("ImGuiTableFlags_BordersOuterV")           = static_cast<int>(ImGuiTableFlags_BordersOuterV);
    e.value("ImGuiTableFlags_BordersH",                ImGuiTableFlags_BordersH);                m.attr("ImGuiTableFlags_BordersH")                = static_cast<int>(ImGuiTableFlags_BordersH);
    e.value("ImGuiTableFlags_BordersV",                ImGuiTableFlags_BordersV);                m.attr("ImGuiTableFlags_BordersV")                = static_cast<int>(ImGuiTableFlags_BordersV);
    e.value("ImGuiTableFlags_BordersInner",            ImGuiTableFlags_BordersInner);            m.attr("ImGuiTableFlags_BordersInner")            = static_cast<int>(ImGuiTableFlags_BordersInner);
    e.value("ImGuiTableFlags_BordersOuter",            ImGuiTableFlags_BordersOuter);            m.attr("ImGuiTableFlags_BordersOuter")            = static_cast<int>(ImGuiTableFlags_BordersOuter);
    e.value("ImGuiTableFlags_Borders",                 ImGuiTableFlags_Borders);                 m.attr("ImGuiTableFlags_Borders")                 = static_cast<int>(ImGuiTableFlags_Borders);
    e.value("ImGuiTableFlags_NoBordersInBody",         ImGuiTableFlags_NoBordersInBody);         m.attr("ImGuiTableFlags_NoBordersInBody")         = static_cast<int>(ImGuiTableFlags_NoBordersInBody);
    e.value("ImGuiTableFlags_NoBordersInBodyUntilResize", ImGuiTableFlags_NoBordersInBodyUntilResize); m.attr("ImGuiTableFlags_NoBordersInBodyUntilResize") = static_cast<int>(ImGuiTableFlags_NoBordersInBodyUntilResize);
    e.value("ImGuiTableFlags_SizingFixedFit",          ImGuiTableFlags_SizingFixedFit);          m.attr("ImGuiTableFlags_SizingFixedFit")          = static_cast<int>(ImGuiTableFlags_SizingFixedFit);
    e.value("ImGuiTableFlags_SizingFixedSame",         ImGuiTableFlags_SizingFixedSame);         m.attr("ImGuiTableFlags_SizingFixedSame")         = static_cast<int>(ImGuiTableFlags_SizingFixedSame);
    e.value("ImGuiTableFlags_SizingStretchProp",       ImGuiTableFlags_SizingStretchProp);       m.attr("ImGuiTableFlags_SizingStretchProp")       = static_cast<int>(ImGuiTableFlags_SizingStretchProp);
    e.value("ImGuiTableFlags_SizingStretchSame",       ImGuiTableFlags_SizingStretchSame);       m.attr("ImGuiTableFlags_SizingStretchSame")       = static_cast<int>(ImGuiTableFlags_SizingStretchSame);
    e.value("ImGuiTableFlags_NoHostExtendX",           ImGuiTableFlags_NoHostExtendX);           m.attr("ImGuiTableFlags_NoHostExtendX")           = static_cast<int>(ImGuiTableFlags_NoHostExtendX);
    e.value("ImGuiTableFlags_NoHostExtendY",           ImGuiTableFlags_NoHostExtendY);           m.attr("ImGuiTableFlags_NoHostExtendY")           = static_cast<int>(ImGuiTableFlags_NoHostExtendY);
    e.value("ImGuiTableFlags_NoKeepColumnsVisible",    ImGuiTableFlags_NoKeepColumnsVisible);    m.attr("ImGuiTableFlags_NoKeepColumnsVisible")    = static_cast<int>(ImGuiTableFlags_NoKeepColumnsVisible);
    e.value("ImGuiTableFlags_PreciseWidths",           ImGuiTableFlags_PreciseWidths);           m.attr("ImGuiTableFlags_PreciseWidths")           = static_cast<int>(ImGuiTableFlags_PreciseWidths);
    e.value("ImGuiTableFlags_NoClip",                  ImGuiTableFlags_NoClip);                  m.attr("ImGuiTableFlags_NoClip")                  = static_cast<int>(ImGuiTableFlags_NoClip);
    e.value("ImGuiTableFlags_PadOuterX",               ImGuiTableFlags_PadOuterX);               m.attr("ImGuiTableFlags_PadOuterX")               = static_cast<int>(ImGuiTableFlags_PadOuterX);
    e.value("ImGuiTableFlags_NoPadOuterX",             ImGuiTableFlags_NoPadOuterX);             m.attr("ImGuiTableFlags_NoPadOuterX")             = static_cast<int>(ImGuiTableFlags_NoPadOuterX);
    e.value("ImGuiTableFlags_NoPadInnerX",             ImGuiTableFlags_NoPadInnerX);             m.attr("ImGuiTableFlags_NoPadInnerX")             = static_cast<int>(ImGuiTableFlags_NoPadInnerX);
    e.value("ImGuiTableFlags_ScrollX",                 ImGuiTableFlags_ScrollX);                 m.attr("ImGuiTableFlags_ScrollX")                 = static_cast<int>(ImGuiTableFlags_ScrollX);
    e.value("ImGuiTableFlags_ScrollY",                 ImGuiTableFlags_ScrollY);                 m.attr("ImGuiTableFlags_ScrollY")                 = static_cast<int>(ImGuiTableFlags_ScrollY);
    e.value("ImGuiTableFlags_SortMulti",               ImGuiTableFlags_SortMulti);               m.attr("ImGuiTableFlags_SortMulti")               = static_cast<int>(ImGuiTableFlags_SortMulti);
    e.value("ImGuiTableFlags_SortTristate",            ImGuiTableFlags_SortTristate);            m.attr("ImGuiTableFlags_SortTristate")            = static_cast<int>(ImGuiTableFlags_SortTristate);
    e.value("ImGuiTableFlags_HighlightHoveredColumn",  ImGuiTableFlags_HighlightHoveredColumn);  m.attr("ImGuiTableFlags_HighlightHoveredColumn")  = static_cast<int>(ImGuiTableFlags_HighlightHoveredColumn);
  ;
  }

  { // ImGuiTableColumnFlags ImGuiTableColumnFlags_
  auto e = nb::enum_<ImGuiTableColumnFlags_>(m, "ImGuiTableColumnFlags");
    e.value("ImGuiTableColumnFlags_None",              ImGuiTableColumnFlags_None);              m.attr("ImGuiTableColumnFlags_None")              = static_cast<int>(ImGuiTableColumnFlags_None);
    e.value("ImGuiTableColumnFlags_Disabled",          ImGuiTableColumnFlags_Disabled);          m.attr("ImGuiTableColumnFlags_Disabled")          = static_cast<int>(ImGuiTableColumnFlags_Disabled);
    e.value("ImGuiTableColumnFlags_DefaultHide",       ImGuiTableColumnFlags_DefaultHide);       m.attr("ImGuiTableColumnFlags_DefaultHide")       = static_cast<int>(ImGuiTableColumnFlags_DefaultHide);
    e.value("ImGuiTableColumnFlags_DefaultSort",       ImGuiTableColumnFlags_DefaultSort);       m.attr("ImGuiTableColumnFlags_DefaultSort")       = static_cast<int>(ImGuiTableColumnFlags_DefaultSort);
    e.value("ImGuiTableColumnFlags_WidthStretch",      ImGuiTableColumnFlags_WidthStretch);      m.attr("ImGuiTableColumnFlags_WidthStretch")      = static_cast<int>(ImGuiTableColumnFlags_WidthStretch);
    e.value("ImGuiTableColumnFlags_WidthFixed",        ImGuiTableColumnFlags_WidthFixed);        m.attr("ImGuiTableColumnFlags_WidthFixed")        = static_cast<int>(ImGuiTableColumnFlags_WidthFixed);
    e.value("ImGuiTableColumnFlags_NoResize",          ImGuiTableColumnFlags_NoResize);          m.attr("ImGuiTableColumnFlags_NoResize")          = static_cast<int>(ImGuiTableColumnFlags_NoResize);
    e.value("ImGuiTableColumnFlags_NoReorder",         ImGuiTableColumnFlags_NoReorder);         m.attr("ImGuiTableColumnFlags_NoReorder")         = static_cast<int>(ImGuiTableColumnFlags_NoReorder);
    e.value("ImGuiTableColumnFlags_NoHide",            ImGuiTableColumnFlags_NoHide);            m.attr("ImGuiTableColumnFlags_NoHide")            = static_cast<int>(ImGuiTableColumnFlags_NoHide);
    e.value("ImGuiTableColumnFlags_NoClip",            ImGuiTableColumnFlags_NoClip);            m.attr("ImGuiTableColumnFlags_NoClip")            = static_cast<int>(ImGuiTableColumnFlags_NoClip);
    e.value("ImGuiTableColumnFlags_NoSort",            ImGuiTableColumnFlags_NoSort);            m.attr("ImGuiTableColumnFlags_NoSort")            = static_cast<int>(ImGuiTableColumnFlags_NoSort);
    e.value("ImGuiTableColumnFlags_NoSortAscending",   ImGuiTableColumnFlags_NoSortAscending);   m.attr("ImGuiTableColumnFlags_NoSortAscending")   = static_cast<int>(ImGuiTableColumnFlags_NoSortAscending);
    e.value("ImGuiTableColumnFlags_NoSortDescending",  ImGuiTableColumnFlags_NoSortDescending);  m.attr("ImGuiTableColumnFlags_NoSortDescending")  = static_cast<int>(ImGuiTableColumnFlags_NoSortDescending);
    e.value("ImGuiTableColumnFlags_NoHeaderLabel",     ImGuiTableColumnFlags_NoHeaderLabel);     m.attr("ImGuiTableColumnFlags_NoHeaderLabel")     = static_cast<int>(ImGuiTableColumnFlags_NoHeaderLabel);
    e.value("ImGuiTableColumnFlags_NoHeaderWidth",     ImGuiTableColumnFlags_NoHeaderWidth);     m.attr("ImGuiTableColumnFlags_NoHeaderWidth")     = static_cast<int>(ImGuiTableColumnFlags_NoHeaderWidth);
    e.value("ImGuiTableColumnFlags_PreferSortAscending", ImGuiTableColumnFlags_PreferSortAscending); m.attr("ImGuiTableColumnFlags_PreferSortAscending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortAscending);
    e.value("ImGuiTableColumnFlags_PreferSortDescending", ImGuiTableColumnFlags_PreferSortDescending); m.attr("ImGuiTableColumnFlags_PreferSortDescending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortDescending);
    e.value("ImGuiTableColumnFlags_IndentEnable",      ImGuiTableColumnFlags_IndentEnable);      m.attr("ImGuiTableColumnFlags_IndentEnable")      = static_cast<int>(ImGuiTableColumnFlags_IndentEnable);
    e.value("ImGuiTableColumnFlags_IndentDisable",     ImGuiTableColumnFlags_IndentDisable);     m.attr("ImGuiTableColumnFlags_IndentDisable")     = static_cast<int>(ImGuiTableColumnFlags_IndentDisable);
    e.value("ImGuiTableColumnFlags_AngledHeader",      ImGuiTableColumnFlags_AngledHeader);      m.attr("ImGuiTableColumnFlags_AngledHeader")      = static_cast<int>(ImGuiTableColumnFlags_AngledHeader);
    e.value("ImGuiTableColumnFlags_IsEnabled",         ImGuiTableColumnFlags_IsEnabled);         m.attr("ImGuiTableColumnFlags_IsEnabled")         = static_cast<int>(ImGuiTableColumnFlags_IsEnabled);
    e.value("ImGuiTableColumnFlags_IsVisible",         ImGuiTableColumnFlags_IsVisible);         m.attr("ImGuiTableColumnFlags_IsVisible")         = static_cast<int>(ImGuiTableColumnFlags_IsVisible);
    e.value("ImGuiTableColumnFlags_IsSorted",          ImGuiTableColumnFlags_IsSorted);          m.attr("ImGuiTableColumnFlags_IsSorted")          = static_cast<int>(ImGuiTableColumnFlags_IsSorted);
    e.value("ImGuiTableColumnFlags_IsHovered",         ImGuiTableColumnFlags_IsHovered);         m.attr("ImGuiTableColumnFlags_IsHovered")         = static_cast<int>(ImGuiTableColumnFlags_IsHovered);
  ;
  }

  { // ImGuiTableRowFlags ImGuiTableRowFlags_
  auto e = nb::enum_<ImGuiTableRowFlags_>(m, "ImGuiTableRowFlags");
    e.value("ImGuiTableRowFlags_None",                 ImGuiTableRowFlags_None);                 m.attr("ImGuiTableRowFlags_None")                 = static_cast<int>(ImGuiTableRowFlags_None);
    e.value("ImGuiTableRowFlags_Headers",              ImGuiTableRowFlags_Headers);              m.attr("ImGuiTableRowFlags_Headers")              = static_cast<int>(ImGuiTableRowFlags_Headers);
  ;
  }

  { // ImGuiTableBgTarget ImGuiTableBgTarget_
  auto e = nb::enum_<ImGuiTableBgTarget_>(m, "ImGuiTableBgTarget");
    e.value("ImGuiTableBgTarget_None",                 ImGuiTableBgTarget_None);                 m.attr("ImGuiTableBgTarget_None")                 = static_cast<int>(ImGuiTableBgTarget_None);
    e.value("ImGuiTableBgTarget_RowBg0",               ImGuiTableBgTarget_RowBg0);               m.attr("ImGuiTableBgTarget_RowBg0")               = static_cast<int>(ImGuiTableBgTarget_RowBg0);
    e.value("ImGuiTableBgTarget_RowBg1",               ImGuiTableBgTarget_RowBg1);               m.attr("ImGuiTableBgTarget_RowBg1")               = static_cast<int>(ImGuiTableBgTarget_RowBg1);
    e.value("ImGuiTableBgTarget_CellBg",               ImGuiTableBgTarget_CellBg);               m.attr("ImGuiTableBgTarget_CellBg")               = static_cast<int>(ImGuiTableBgTarget_CellBg);
  ;
  }

  { // ImDrawFlags ImDrawFlags_
  auto e = nb::enum_<ImDrawFlags_>(m, "ImDrawFlags");
    e.value("ImDrawFlags_None",                        ImDrawFlags_None);                        m.attr("ImDrawFlags_None")                        = static_cast<int>(ImDrawFlags_None);
    e.value("ImDrawFlags_Closed",                      ImDrawFlags_Closed);                      m.attr("ImDrawFlags_Closed")                      = static_cast<int>(ImDrawFlags_Closed);
    e.value("ImDrawFlags_RoundCornersTopLeft",         ImDrawFlags_RoundCornersTopLeft);         m.attr("ImDrawFlags_RoundCornersTopLeft")         = static_cast<int>(ImDrawFlags_RoundCornersTopLeft);
    e.value("ImDrawFlags_RoundCornersTopRight",        ImDrawFlags_RoundCornersTopRight);        m.attr("ImDrawFlags_RoundCornersTopRight")        = static_cast<int>(ImDrawFlags_RoundCornersTopRight);
    e.value("ImDrawFlags_RoundCornersBottomLeft",      ImDrawFlags_RoundCornersBottomLeft);      m.attr("ImDrawFlags_RoundCornersBottomLeft")      = static_cast<int>(ImDrawFlags_RoundCornersBottomLeft);
    e.value("ImDrawFlags_RoundCornersBottomRight",     ImDrawFlags_RoundCornersBottomRight);     m.attr("ImDrawFlags_RoundCornersBottomRight")     = static_cast<int>(ImDrawFlags_RoundCornersBottomRight);
    e.value("ImDrawFlags_RoundCornersNone",            ImDrawFlags_RoundCornersNone);            m.attr("ImDrawFlags_RoundCornersNone")            = static_cast<int>(ImDrawFlags_RoundCornersNone);
    e.value("ImDrawFlags_RoundCornersTop",             ImDrawFlags_RoundCornersTop);             m.attr("ImDrawFlags_RoundCornersTop")             = static_cast<int>(ImDrawFlags_RoundCornersTop);
    e.value("ImDrawFlags_RoundCornersBottom",          ImDrawFlags_RoundCornersBottom);          m.attr("ImDrawFlags_RoundCornersBottom")          = static_cast<int>(ImDrawFlags_RoundCornersBottom);
    e.value("ImDrawFlags_RoundCornersLeft",            ImDrawFlags_RoundCornersLeft);            m.attr("ImDrawFlags_RoundCornersLeft")            = static_cast<int>(ImDrawFlags_RoundCornersLeft);
    e.value("ImDrawFlags_RoundCornersRight",           ImDrawFlags_RoundCornersRight);           m.attr("ImDrawFlags_RoundCornersRight")           = static_cast<int>(ImDrawFlags_RoundCornersRight);
    e.value("ImDrawFlags_RoundCornersAll",             ImDrawFlags_RoundCornersAll);             m.attr("ImDrawFlags_RoundCornersAll")             = static_cast<int>(ImDrawFlags_RoundCornersAll);
  ;
  }

  { // ImGuiKey ImGuiKey
  auto e = nb::enum_<ImGuiKey>(m, "ImGuiKey");
    e.value("ImGuiKey_None",                           ImGuiKey_None);                           m.attr("ImGuiKey_None")                           = static_cast<int>(ImGuiKey_None);
    e.value("ImGuiKey_Tab",                            ImGuiKey_Tab);                            m.attr("ImGuiKey_Tab")                            = static_cast<int>(ImGuiKey_Tab);
    e.value("ImGuiKey_LeftArrow",                      ImGuiKey_LeftArrow);                      m.attr("ImGuiKey_LeftArrow")                      = static_cast<int>(ImGuiKey_LeftArrow);
    e.value("ImGuiKey_RightArrow",                     ImGuiKey_RightArrow);                     m.attr("ImGuiKey_RightArrow")                     = static_cast<int>(ImGuiKey_RightArrow);
    e.value("ImGuiKey_UpArrow",                        ImGuiKey_UpArrow);                        m.attr("ImGuiKey_UpArrow")                        = static_cast<int>(ImGuiKey_UpArrow);
    e.value("ImGuiKey_DownArrow",                      ImGuiKey_DownArrow);                      m.attr("ImGuiKey_DownArrow")                      = static_cast<int>(ImGuiKey_DownArrow);
    e.value("ImGuiKey_PageUp",                         ImGuiKey_PageUp);                         m.attr("ImGuiKey_PageUp")                         = static_cast<int>(ImGuiKey_PageUp);
    e.value("ImGuiKey_PageDown",                       ImGuiKey_PageDown);                       m.attr("ImGuiKey_PageDown")                       = static_cast<int>(ImGuiKey_PageDown);
    e.value("ImGuiKey_Home",                           ImGuiKey_Home);                           m.attr("ImGuiKey_Home")                           = static_cast<int>(ImGuiKey_Home);
    e.value("ImGuiKey_End",                            ImGuiKey_End);                            m.attr("ImGuiKey_End")                            = static_cast<int>(ImGuiKey_End);
    e.value("ImGuiKey_Insert",                         ImGuiKey_Insert);                         m.attr("ImGuiKey_Insert")                         = static_cast<int>(ImGuiKey_Insert);
    e.value("ImGuiKey_Delete",                         ImGuiKey_Delete);                         m.attr("ImGuiKey_Delete")                         = static_cast<int>(ImGuiKey_Delete);
    e.value("ImGuiKey_Backspace",                      ImGuiKey_Backspace);                      m.attr("ImGuiKey_Backspace")                      = static_cast<int>(ImGuiKey_Backspace);
    e.value("ImGuiKey_Space",                          ImGuiKey_Space);                          m.attr("ImGuiKey_Space")                          = static_cast<int>(ImGuiKey_Space);
    e.value("ImGuiKey_Enter",                          ImGuiKey_Enter);                          m.attr("ImGuiKey_Enter")                          = static_cast<int>(ImGuiKey_Enter);
    e.value("ImGuiKey_Escape",                         ImGuiKey_Escape);                         m.attr("ImGuiKey_Escape")                         = static_cast<int>(ImGuiKey_Escape);
    e.value("ImGuiKey_LeftCtrl",                       ImGuiKey_LeftCtrl);                       m.attr("ImGuiKey_LeftCtrl")                       = static_cast<int>(ImGuiKey_LeftCtrl);
    e.value("ImGuiKey_LeftShift",                      ImGuiKey_LeftShift);                      m.attr("ImGuiKey_LeftShift")                      = static_cast<int>(ImGuiKey_LeftShift);
    e.value("ImGuiKey_LeftAlt",                        ImGuiKey_LeftAlt);                        m.attr("ImGuiKey_LeftAlt")                        = static_cast<int>(ImGuiKey_LeftAlt);
    e.value("ImGuiKey_LeftSuper",                      ImGuiKey_LeftSuper);                      m.attr("ImGuiKey_LeftSuper")                      = static_cast<int>(ImGuiKey_LeftSuper);
    e.value("ImGuiKey_RightCtrl",                      ImGuiKey_RightCtrl);                      m.attr("ImGuiKey_RightCtrl")                      = static_cast<int>(ImGuiKey_RightCtrl);
    e.value("ImGuiKey_RightShift",                     ImGuiKey_RightShift);                     m.attr("ImGuiKey_RightShift")                     = static_cast<int>(ImGuiKey_RightShift);
    e.value("ImGuiKey_RightAlt",                       ImGuiKey_RightAlt);                       m.attr("ImGuiKey_RightAlt")                       = static_cast<int>(ImGuiKey_RightAlt);
    e.value("ImGuiKey_RightSuper",                     ImGuiKey_RightSuper);                     m.attr("ImGuiKey_RightSuper")                     = static_cast<int>(ImGuiKey_RightSuper);
    e.value("ImGuiKey_Menu",                           ImGuiKey_Menu);                           m.attr("ImGuiKey_Menu")                           = static_cast<int>(ImGuiKey_Menu);
    e.value("ImGuiKey_0",                              ImGuiKey_0);                              m.attr("ImGuiKey_0")                              = static_cast<int>(ImGuiKey_0);
    e.value("ImGuiKey_1",                              ImGuiKey_1);                              m.attr("ImGuiKey_1")                              = static_cast<int>(ImGuiKey_1);
    e.value("ImGuiKey_2",                              ImGuiKey_2);                              m.attr("ImGuiKey_2")                              = static_cast<int>(ImGuiKey_2);
    e.value("ImGuiKey_3",                              ImGuiKey_3);                              m.attr("ImGuiKey_3")                              = static_cast<int>(ImGuiKey_3);
    e.value("ImGuiKey_4",                              ImGuiKey_4);                              m.attr("ImGuiKey_4")                              = static_cast<int>(ImGuiKey_4);
    e.value("ImGuiKey_5",                              ImGuiKey_5);                              m.attr("ImGuiKey_5")                              = static_cast<int>(ImGuiKey_5);
    e.value("ImGuiKey_6",                              ImGuiKey_6);                              m.attr("ImGuiKey_6")                              = static_cast<int>(ImGuiKey_6);
    e.value("ImGuiKey_7",                              ImGuiKey_7);                              m.attr("ImGuiKey_7")                              = static_cast<int>(ImGuiKey_7);
    e.value("ImGuiKey_8",                              ImGuiKey_8);                              m.attr("ImGuiKey_8")                              = static_cast<int>(ImGuiKey_8);
    e.value("ImGuiKey_9",                              ImGuiKey_9);                              m.attr("ImGuiKey_9")                              = static_cast<int>(ImGuiKey_9);
    e.value("ImGuiKey_A",                              ImGuiKey_A);                              m.attr("ImGuiKey_A")                              = static_cast<int>(ImGuiKey_A);
    e.value("ImGuiKey_B",                              ImGuiKey_B);                              m.attr("ImGuiKey_B")                              = static_cast<int>(ImGuiKey_B);
    e.value("ImGuiKey_C",                              ImGuiKey_C);                              m.attr("ImGuiKey_C")                              = static_cast<int>(ImGuiKey_C);
    e.value("ImGuiKey_D",                              ImGuiKey_D);                              m.attr("ImGuiKey_D")                              = static_cast<int>(ImGuiKey_D);
    e.value("ImGuiKey_E",                              ImGuiKey_E);                              m.attr("ImGuiKey_E")                              = static_cast<int>(ImGuiKey_E);
    e.value("ImGuiKey_F",                              ImGuiKey_F);                              m.attr("ImGuiKey_F")                              = static_cast<int>(ImGuiKey_F);
    e.value("ImGuiKey_G",                              ImGuiKey_G);                              m.attr("ImGuiKey_G")                              = static_cast<int>(ImGuiKey_G);
    e.value("ImGuiKey_H",                              ImGuiKey_H);                              m.attr("ImGuiKey_H")                              = static_cast<int>(ImGuiKey_H);
    e.value("ImGuiKey_I",                              ImGuiKey_I);                              m.attr("ImGuiKey_I")                              = static_cast<int>(ImGuiKey_I);
    e.value("ImGuiKey_J",                              ImGuiKey_J);                              m.attr("ImGuiKey_J")                              = static_cast<int>(ImGuiKey_J);
    e.value("ImGuiKey_K",                              ImGuiKey_K);                              m.attr("ImGuiKey_K")                              = static_cast<int>(ImGuiKey_K);
    e.value("ImGuiKey_L",                              ImGuiKey_L);                              m.attr("ImGuiKey_L")                              = static_cast<int>(ImGuiKey_L);
    e.value("ImGuiKey_M",                              ImGuiKey_M);                              m.attr("ImGuiKey_M")                              = static_cast<int>(ImGuiKey_M);
    e.value("ImGuiKey_N",                              ImGuiKey_N);                              m.attr("ImGuiKey_N")                              = static_cast<int>(ImGuiKey_N);
    e.value("ImGuiKey_O",                              ImGuiKey_O);                              m.attr("ImGuiKey_O")                              = static_cast<int>(ImGuiKey_O);
    e.value("ImGuiKey_P",                              ImGuiKey_P);                              m.attr("ImGuiKey_P")                              = static_cast<int>(ImGuiKey_P);
    e.value("ImGuiKey_Q",                              ImGuiKey_Q);                              m.attr("ImGuiKey_Q")                              = static_cast<int>(ImGuiKey_Q);
    e.value("ImGuiKey_R",                              ImGuiKey_R);                              m.attr("ImGuiKey_R")                              = static_cast<int>(ImGuiKey_R);
    e.value("ImGuiKey_S",                              ImGuiKey_S);                              m.attr("ImGuiKey_S")                              = static_cast<int>(ImGuiKey_S);
    e.value("ImGuiKey_T",                              ImGuiKey_T);                              m.attr("ImGuiKey_T")                              = static_cast<int>(ImGuiKey_T);
    e.value("ImGuiKey_U",                              ImGuiKey_U);                              m.attr("ImGuiKey_U")                              = static_cast<int>(ImGuiKey_U);
    e.value("ImGuiKey_V",                              ImGuiKey_V);                              m.attr("ImGuiKey_V")                              = static_cast<int>(ImGuiKey_V);
    e.value("ImGuiKey_W",                              ImGuiKey_W);                              m.attr("ImGuiKey_W")                              = static_cast<int>(ImGuiKey_W);
    e.value("ImGuiKey_X",                              ImGuiKey_X);                              m.attr("ImGuiKey_X")                              = static_cast<int>(ImGuiKey_X);
    e.value("ImGuiKey_Y",                              ImGuiKey_Y);                              m.attr("ImGuiKey_Y")                              = static_cast<int>(ImGuiKey_Y);
    e.value("ImGuiKey_Z",                              ImGuiKey_Z);                              m.attr("ImGuiKey_Z")                              = static_cast<int>(ImGuiKey_Z);
    e.value("ImGuiKey_F1",                             ImGuiKey_F1);                             m.attr("ImGuiKey_F1")                             = static_cast<int>(ImGuiKey_F1);
    e.value("ImGuiKey_F2",                             ImGuiKey_F2);                             m.attr("ImGuiKey_F2")                             = static_cast<int>(ImGuiKey_F2);
    e.value("ImGuiKey_F3",                             ImGuiKey_F3);                             m.attr("ImGuiKey_F3")                             = static_cast<int>(ImGuiKey_F3);
    e.value("ImGuiKey_F4",                             ImGuiKey_F4);                             m.attr("ImGuiKey_F4")                             = static_cast<int>(ImGuiKey_F4);
    e.value("ImGuiKey_F5",                             ImGuiKey_F5);                             m.attr("ImGuiKey_F5")                             = static_cast<int>(ImGuiKey_F5);
    e.value("ImGuiKey_F6",                             ImGuiKey_F6);                             m.attr("ImGuiKey_F6")                             = static_cast<int>(ImGuiKey_F6);
    e.value("ImGuiKey_F7",                             ImGuiKey_F7);                             m.attr("ImGuiKey_F7")                             = static_cast<int>(ImGuiKey_F7);
    e.value("ImGuiKey_F8",                             ImGuiKey_F8);                             m.attr("ImGuiKey_F8")                             = static_cast<int>(ImGuiKey_F8);
    e.value("ImGuiKey_F9",                             ImGuiKey_F9);                             m.attr("ImGuiKey_F9")                             = static_cast<int>(ImGuiKey_F9);
    e.value("ImGuiKey_F10",                            ImGuiKey_F10);                            m.attr("ImGuiKey_F10")                            = static_cast<int>(ImGuiKey_F10);
    e.value("ImGuiKey_F11",                            ImGuiKey_F11);                            m.attr("ImGuiKey_F11")                            = static_cast<int>(ImGuiKey_F11);
    e.value("ImGuiKey_F12",                            ImGuiKey_F12);                            m.attr("ImGuiKey_F12")                            = static_cast<int>(ImGuiKey_F12);
    e.value("ImGuiKey_F13",                            ImGuiKey_F13);                            m.attr("ImGuiKey_F13")                            = static_cast<int>(ImGuiKey_F13);
    e.value("ImGuiKey_F14",                            ImGuiKey_F14);                            m.attr("ImGuiKey_F14")                            = static_cast<int>(ImGuiKey_F14);
    e.value("ImGuiKey_F15",                            ImGuiKey_F15);                            m.attr("ImGuiKey_F15")                            = static_cast<int>(ImGuiKey_F15);
    e.value("ImGuiKey_F16",                            ImGuiKey_F16);                            m.attr("ImGuiKey_F16")                            = static_cast<int>(ImGuiKey_F16);
    e.value("ImGuiKey_F17",                            ImGuiKey_F17);                            m.attr("ImGuiKey_F17")                            = static_cast<int>(ImGuiKey_F17);
    e.value("ImGuiKey_F18",                            ImGuiKey_F18);                            m.attr("ImGuiKey_F18")                            = static_cast<int>(ImGuiKey_F18);
    e.value("ImGuiKey_F19",                            ImGuiKey_F19);                            m.attr("ImGuiKey_F19")                            = static_cast<int>(ImGuiKey_F19);
    e.value("ImGuiKey_F20",                            ImGuiKey_F20);                            m.attr("ImGuiKey_F20")                            = static_cast<int>(ImGuiKey_F20);
    e.value("ImGuiKey_F21",                            ImGuiKey_F21);                            m.attr("ImGuiKey_F21")                            = static_cast<int>(ImGuiKey_F21);
    e.value("ImGuiKey_F22",                            ImGuiKey_F22);                            m.attr("ImGuiKey_F22")                            = static_cast<int>(ImGuiKey_F22);
    e.value("ImGuiKey_F23",                            ImGuiKey_F23);                            m.attr("ImGuiKey_F23")                            = static_cast<int>(ImGuiKey_F23);
    e.value("ImGuiKey_F24",                            ImGuiKey_F24);                            m.attr("ImGuiKey_F24")                            = static_cast<int>(ImGuiKey_F24);
    e.value("ImGuiKey_Apostrophe",                     ImGuiKey_Apostrophe);                     m.attr("ImGuiKey_Apostrophe")                     = static_cast<int>(ImGuiKey_Apostrophe);
    e.value("ImGuiKey_Comma",                          ImGuiKey_Comma);                          m.attr("ImGuiKey_Comma")                          = static_cast<int>(ImGuiKey_Comma);
    e.value("ImGuiKey_Minus",                          ImGuiKey_Minus);                          m.attr("ImGuiKey_Minus")                          = static_cast<int>(ImGuiKey_Minus);
    e.value("ImGuiKey_Period",                         ImGuiKey_Period);                         m.attr("ImGuiKey_Period")                         = static_cast<int>(ImGuiKey_Period);
    e.value("ImGuiKey_Slash",                          ImGuiKey_Slash);                          m.attr("ImGuiKey_Slash")                          = static_cast<int>(ImGuiKey_Slash);
    e.value("ImGuiKey_Semicolon",                      ImGuiKey_Semicolon);                      m.attr("ImGuiKey_Semicolon")                      = static_cast<int>(ImGuiKey_Semicolon);
    e.value("ImGuiKey_Equal",                          ImGuiKey_Equal);                          m.attr("ImGuiKey_Equal")                          = static_cast<int>(ImGuiKey_Equal);
    e.value("ImGuiKey_LeftBracket",                    ImGuiKey_LeftBracket);                    m.attr("ImGuiKey_LeftBracket")                    = static_cast<int>(ImGuiKey_LeftBracket);
    e.value("ImGuiKey_Backslash",                      ImGuiKey_Backslash);                      m.attr("ImGuiKey_Backslash")                      = static_cast<int>(ImGuiKey_Backslash);
    e.value("ImGuiKey_RightBracket",                   ImGuiKey_RightBracket);                   m.attr("ImGuiKey_RightBracket")                   = static_cast<int>(ImGuiKey_RightBracket);
    e.value("ImGuiKey_GraveAccent",                    ImGuiKey_GraveAccent);                    m.attr("ImGuiKey_GraveAccent")                    = static_cast<int>(ImGuiKey_GraveAccent);
    e.value("ImGuiKey_CapsLock",                       ImGuiKey_CapsLock);                       m.attr("ImGuiKey_CapsLock")                       = static_cast<int>(ImGuiKey_CapsLock);
    e.value("ImGuiKey_ScrollLock",                     ImGuiKey_ScrollLock);                     m.attr("ImGuiKey_ScrollLock")                     = static_cast<int>(ImGuiKey_ScrollLock);
    e.value("ImGuiKey_NumLock",                        ImGuiKey_NumLock);                        m.attr("ImGuiKey_NumLock")                        = static_cast<int>(ImGuiKey_NumLock);
    e.value("ImGuiKey_PrintScreen",                    ImGuiKey_PrintScreen);                    m.attr("ImGuiKey_PrintScreen")                    = static_cast<int>(ImGuiKey_PrintScreen);
    e.value("ImGuiKey_Pause",                          ImGuiKey_Pause);                          m.attr("ImGuiKey_Pause")                          = static_cast<int>(ImGuiKey_Pause);
    e.value("ImGuiKey_Keypad0",                        ImGuiKey_Keypad0);                        m.attr("ImGuiKey_Keypad0")                        = static_cast<int>(ImGuiKey_Keypad0);
    e.value("ImGuiKey_Keypad1",                        ImGuiKey_Keypad1);                        m.attr("ImGuiKey_Keypad1")                        = static_cast<int>(ImGuiKey_Keypad1);
    e.value("ImGuiKey_Keypad2",                        ImGuiKey_Keypad2);                        m.attr("ImGuiKey_Keypad2")                        = static_cast<int>(ImGuiKey_Keypad2);
    e.value("ImGuiKey_Keypad3",                        ImGuiKey_Keypad3);                        m.attr("ImGuiKey_Keypad3")                        = static_cast<int>(ImGuiKey_Keypad3);
    e.value("ImGuiKey_Keypad4",                        ImGuiKey_Keypad4);                        m.attr("ImGuiKey_Keypad4")                        = static_cast<int>(ImGuiKey_Keypad4);
    e.value("ImGuiKey_Keypad5",                        ImGuiKey_Keypad5);                        m.attr("ImGuiKey_Keypad5")                        = static_cast<int>(ImGuiKey_Keypad5);
    e.value("ImGuiKey_Keypad6",                        ImGuiKey_Keypad6);                        m.attr("ImGuiKey_Keypad6")                        = static_cast<int>(ImGuiKey_Keypad6);
    e.value("ImGuiKey_Keypad7",                        ImGuiKey_Keypad7);                        m.attr("ImGuiKey_Keypad7")                        = static_cast<int>(ImGuiKey_Keypad7);
    e.value("ImGuiKey_Keypad8",                        ImGuiKey_Keypad8);                        m.attr("ImGuiKey_Keypad8")                        = static_cast<int>(ImGuiKey_Keypad8);
    e.value("ImGuiKey_Keypad9",                        ImGuiKey_Keypad9);                        m.attr("ImGuiKey_Keypad9")                        = static_cast<int>(ImGuiKey_Keypad9);
    e.value("ImGuiKey_KeypadDecimal",                  ImGuiKey_KeypadDecimal);                  m.attr("ImGuiKey_KeypadDecimal")                  = static_cast<int>(ImGuiKey_KeypadDecimal);
    e.value("ImGuiKey_KeypadDivide",                   ImGuiKey_KeypadDivide);                   m.attr("ImGuiKey_KeypadDivide")                   = static_cast<int>(ImGuiKey_KeypadDivide);
    e.value("ImGuiKey_KeypadMultiply",                 ImGuiKey_KeypadMultiply);                 m.attr("ImGuiKey_KeypadMultiply")                 = static_cast<int>(ImGuiKey_KeypadMultiply);
    e.value("ImGuiKey_KeypadSubtract",                 ImGuiKey_KeypadSubtract);                 m.attr("ImGuiKey_KeypadSubtract")                 = static_cast<int>(ImGuiKey_KeypadSubtract);
    e.value("ImGuiKey_KeypadAdd",                      ImGuiKey_KeypadAdd);                      m.attr("ImGuiKey_KeypadAdd")                      = static_cast<int>(ImGuiKey_KeypadAdd);
    e.value("ImGuiKey_KeypadEnter",                    ImGuiKey_KeypadEnter);                    m.attr("ImGuiKey_KeypadEnter")                    = static_cast<int>(ImGuiKey_KeypadEnter);
    e.value("ImGuiKey_KeypadEqual",                    ImGuiKey_KeypadEqual);                    m.attr("ImGuiKey_KeypadEqual")                    = static_cast<int>(ImGuiKey_KeypadEqual);
    e.value("ImGuiKey_AppBack",                        ImGuiKey_AppBack);                        m.attr("ImGuiKey_AppBack")                        = static_cast<int>(ImGuiKey_AppBack);
    e.value("ImGuiKey_AppForward",                     ImGuiKey_AppForward);                     m.attr("ImGuiKey_AppForward")                     = static_cast<int>(ImGuiKey_AppForward);
    e.value("ImGuiKey_GamepadStart",                   ImGuiKey_GamepadStart);                   m.attr("ImGuiKey_GamepadStart")                   = static_cast<int>(ImGuiKey_GamepadStart);
    e.value("ImGuiKey_GamepadBack",                    ImGuiKey_GamepadBack);                    m.attr("ImGuiKey_GamepadBack")                    = static_cast<int>(ImGuiKey_GamepadBack);
    e.value("ImGuiKey_GamepadFaceUp",                  ImGuiKey_GamepadFaceUp);                  m.attr("ImGuiKey_GamepadFaceUp")                  = static_cast<int>(ImGuiKey_GamepadFaceUp);
    e.value("ImGuiKey_GamepadFaceDown",                ImGuiKey_GamepadFaceDown);                m.attr("ImGuiKey_GamepadFaceDown")                = static_cast<int>(ImGuiKey_GamepadFaceDown);
    e.value("ImGuiKey_GamepadFaceLeft",                ImGuiKey_GamepadFaceLeft);                m.attr("ImGuiKey_GamepadFaceLeft")                = static_cast<int>(ImGuiKey_GamepadFaceLeft);
    e.value("ImGuiKey_GamepadFaceRight",               ImGuiKey_GamepadFaceRight);               m.attr("ImGuiKey_GamepadFaceRight")               = static_cast<int>(ImGuiKey_GamepadFaceRight);
    e.value("ImGuiKey_GamepadDpadUp",                  ImGuiKey_GamepadDpadUp);                  m.attr("ImGuiKey_GamepadDpadUp")                  = static_cast<int>(ImGuiKey_GamepadDpadUp);
    e.value("ImGuiKey_GamepadDpadDown",                ImGuiKey_GamepadDpadDown);                m.attr("ImGuiKey_GamepadDpadDown")                = static_cast<int>(ImGuiKey_GamepadDpadDown);
    e.value("ImGuiKey_GamepadDpadLeft",                ImGuiKey_GamepadDpadLeft);                m.attr("ImGuiKey_GamepadDpadLeft")                = static_cast<int>(ImGuiKey_GamepadDpadLeft);
    e.value("ImGuiKey_GamepadDpadRight",               ImGuiKey_GamepadDpadRight);               m.attr("ImGuiKey_GamepadDpadRight")               = static_cast<int>(ImGuiKey_GamepadDpadRight);
    e.value("ImGuiKey_GamepadL1",                      ImGuiKey_GamepadL1);                      m.attr("ImGuiKey_GamepadL1")                      = static_cast<int>(ImGuiKey_GamepadL1);
    e.value("ImGuiKey_GamepadR1",                      ImGuiKey_GamepadR1);                      m.attr("ImGuiKey_GamepadR1")                      = static_cast<int>(ImGuiKey_GamepadR1);
    e.value("ImGuiKey_GamepadL2",                      ImGuiKey_GamepadL2);                      m.attr("ImGuiKey_GamepadL2")                      = static_cast<int>(ImGuiKey_GamepadL2);
    e.value("ImGuiKey_GamepadR2",                      ImGuiKey_GamepadR2);                      m.attr("ImGuiKey_GamepadR2")                      = static_cast<int>(ImGuiKey_GamepadR2);
    e.value("ImGuiKey_GamepadL3",                      ImGuiKey_GamepadL3);                      m.attr("ImGuiKey_GamepadL3")                      = static_cast<int>(ImGuiKey_GamepadL3);
    e.value("ImGuiKey_GamepadR3",                      ImGuiKey_GamepadR3);                      m.attr("ImGuiKey_GamepadR3")                      = static_cast<int>(ImGuiKey_GamepadR3);
    e.value("ImGuiKey_GamepadLStickUp",                ImGuiKey_GamepadLStickUp);                m.attr("ImGuiKey_GamepadLStickUp")                = static_cast<int>(ImGuiKey_GamepadLStickUp);
    e.value("ImGuiKey_GamepadLStickDown",              ImGuiKey_GamepadLStickDown);              m.attr("ImGuiKey_GamepadLStickDown")              = static_cast<int>(ImGuiKey_GamepadLStickDown);
    e.value("ImGuiKey_GamepadLStickLeft",              ImGuiKey_GamepadLStickLeft);              m.attr("ImGuiKey_GamepadLStickLeft")              = static_cast<int>(ImGuiKey_GamepadLStickLeft);
    e.value("ImGuiKey_GamepadLStickRight",             ImGuiKey_GamepadLStickRight);             m.attr("ImGuiKey_GamepadLStickRight")             = static_cast<int>(ImGuiKey_GamepadLStickRight);
    e.value("ImGuiKey_GamepadRStickUp",                ImGuiKey_GamepadRStickUp);                m.attr("ImGuiKey_GamepadRStickUp")                = static_cast<int>(ImGuiKey_GamepadRStickUp);
    e.value("ImGuiKey_GamepadRStickDown",              ImGuiKey_GamepadRStickDown);              m.attr("ImGuiKey_GamepadRStickDown")              = static_cast<int>(ImGuiKey_GamepadRStickDown);
    e.value("ImGuiKey_GamepadRStickLeft",              ImGuiKey_GamepadRStickLeft);              m.attr("ImGuiKey_GamepadRStickLeft")              = static_cast<int>(ImGuiKey_GamepadRStickLeft);
    e.value("ImGuiKey_GamepadRStickRight",             ImGuiKey_GamepadRStickRight);             m.attr("ImGuiKey_GamepadRStickRight")             = static_cast<int>(ImGuiKey_GamepadRStickRight);
    e.value("ImGuiKey_ModCtrl",                        ImGuiKey_ModCtrl);                        m.attr("ImGuiKey_ModCtrl")                        = static_cast<int>(ImGuiKey_ModCtrl);
    e.value("ImGuiKey_ModShift",                       ImGuiKey_ModShift);                       m.attr("ImGuiKey_ModShift")                       = static_cast<int>(ImGuiKey_ModShift);
    e.value("ImGuiKey_ModAlt",                         ImGuiKey_ModAlt);                         m.attr("ImGuiKey_ModAlt")                         = static_cast<int>(ImGuiKey_ModAlt);
    e.value("ImGuiKey_ModSuper",                       ImGuiKey_ModSuper);                       m.attr("ImGuiKey_ModSuper")                       = static_cast<int>(ImGuiKey_ModSuper);
    e.value("ImGuiMod_None",                           ImGuiMod_None);                           m.attr("ImGuiMod_None")                           = static_cast<int>(ImGuiMod_None);
    e.value("ImGuiMod_Ctrl",                           ImGuiMod_Ctrl);                           m.attr("ImGuiMod_Ctrl")                           = static_cast<int>(ImGuiMod_Ctrl);
    e.value("ImGuiMod_Shift",                          ImGuiMod_Shift);                          m.attr("ImGuiMod_Shift")                          = static_cast<int>(ImGuiMod_Shift);
    e.value("ImGuiMod_Alt",                            ImGuiMod_Alt);                            m.attr("ImGuiMod_Alt")                            = static_cast<int>(ImGuiMod_Alt);
    e.value("ImGuiMod_Super",                          ImGuiMod_Super);                          m.attr("ImGuiMod_Super")                          = static_cast<int>(ImGuiMod_Super);
    e.value("ImGuiMod_Mask_",                          ImGuiMod_Mask_);                          m.attr("ImGuiMod_Mask_")                          = static_cast<int>(ImGuiMod_Mask_);
  ;
  }

}
