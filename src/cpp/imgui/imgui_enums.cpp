// AUTO-GENERATED FILE - DO NOT EDIT
// Generated: 2026-02-01 11:01:19
// imgui version: 1.92.6 WIP
// Generator: python3 scripts/generate_imgui_enums.py

#include "imgui.h"

#include "../utils.h"
#include "imgui_utils.h"

void bind_imgui_enums(nb::module_& m) {

  { // ImGuiWindowFlags_
  auto e = nb::enum_<ImGuiWindowFlags_>(m, "ImGuiWindowFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiWindowFlags_None",                        ImGuiWindowFlags_None);                        m.attr("ImGuiWindowFlags_None")                        = ImGuiWindowFlags_::ImGuiWindowFlags_None;
    e.value("ImGuiWindowFlags_NoTitleBar",                  ImGuiWindowFlags_NoTitleBar);                  m.attr("ImGuiWindowFlags_NoTitleBar")                  = ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar;
    e.value("ImGuiWindowFlags_NoResize",                    ImGuiWindowFlags_NoResize);                    m.attr("ImGuiWindowFlags_NoResize")                    = ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;
    e.value("ImGuiWindowFlags_NoMove",                      ImGuiWindowFlags_NoMove);                      m.attr("ImGuiWindowFlags_NoMove")                      = ImGuiWindowFlags_::ImGuiWindowFlags_NoMove;
    e.value("ImGuiWindowFlags_NoScrollbar",                 ImGuiWindowFlags_NoScrollbar);                 m.attr("ImGuiWindowFlags_NoScrollbar")                 = ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
    e.value("ImGuiWindowFlags_NoScrollWithMouse",           ImGuiWindowFlags_NoScrollWithMouse);           m.attr("ImGuiWindowFlags_NoScrollWithMouse")           = ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse;
    e.value("ImGuiWindowFlags_NoCollapse",                  ImGuiWindowFlags_NoCollapse);                  m.attr("ImGuiWindowFlags_NoCollapse")                  = ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse;
    e.value("ImGuiWindowFlags_AlwaysAutoResize",            ImGuiWindowFlags_AlwaysAutoResize);            m.attr("ImGuiWindowFlags_AlwaysAutoResize")            = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
    e.value("ImGuiWindowFlags_NoBackground",                ImGuiWindowFlags_NoBackground);                m.attr("ImGuiWindowFlags_NoBackground")                = ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground;
    e.value("ImGuiWindowFlags_NoSavedSettings",             ImGuiWindowFlags_NoSavedSettings);             m.attr("ImGuiWindowFlags_NoSavedSettings")             = ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings;
    e.value("ImGuiWindowFlags_NoMouseInputs",               ImGuiWindowFlags_NoMouseInputs);               m.attr("ImGuiWindowFlags_NoMouseInputs")               = ImGuiWindowFlags_::ImGuiWindowFlags_NoMouseInputs;
    e.value("ImGuiWindowFlags_MenuBar",                     ImGuiWindowFlags_MenuBar);                     m.attr("ImGuiWindowFlags_MenuBar")                     = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;
    e.value("ImGuiWindowFlags_HorizontalScrollbar",         ImGuiWindowFlags_HorizontalScrollbar);         m.attr("ImGuiWindowFlags_HorizontalScrollbar")         = ImGuiWindowFlags_::ImGuiWindowFlags_HorizontalScrollbar;
    e.value("ImGuiWindowFlags_NoFocusOnAppearing",          ImGuiWindowFlags_NoFocusOnAppearing);          m.attr("ImGuiWindowFlags_NoFocusOnAppearing")          = ImGuiWindowFlags_::ImGuiWindowFlags_NoFocusOnAppearing;
    e.value("ImGuiWindowFlags_NoBringToFrontOnFocus",       ImGuiWindowFlags_NoBringToFrontOnFocus);       m.attr("ImGuiWindowFlags_NoBringToFrontOnFocus")       = ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus;
    e.value("ImGuiWindowFlags_AlwaysVerticalScrollbar",     ImGuiWindowFlags_AlwaysVerticalScrollbar);     m.attr("ImGuiWindowFlags_AlwaysVerticalScrollbar")     = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar;
    e.value("ImGuiWindowFlags_AlwaysHorizontalScrollbar",   ImGuiWindowFlags_AlwaysHorizontalScrollbar);   m.attr("ImGuiWindowFlags_AlwaysHorizontalScrollbar")   = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysHorizontalScrollbar;
    e.value("ImGuiWindowFlags_NoNavInputs",                 ImGuiWindowFlags_NoNavInputs);                 m.attr("ImGuiWindowFlags_NoNavInputs")                 = ImGuiWindowFlags_::ImGuiWindowFlags_NoNavInputs;
    e.value("ImGuiWindowFlags_NoNavFocus",                  ImGuiWindowFlags_NoNavFocus);                  m.attr("ImGuiWindowFlags_NoNavFocus")                  = ImGuiWindowFlags_::ImGuiWindowFlags_NoNavFocus;
    e.value("ImGuiWindowFlags_UnsavedDocument",             ImGuiWindowFlags_UnsavedDocument);             m.attr("ImGuiWindowFlags_UnsavedDocument")             = ImGuiWindowFlags_::ImGuiWindowFlags_UnsavedDocument;
    e.value("ImGuiWindowFlags_NoNav",                       ImGuiWindowFlags_NoNav);                       m.attr("ImGuiWindowFlags_NoNav")                       = ImGuiWindowFlags_::ImGuiWindowFlags_NoNav;
    e.value("ImGuiWindowFlags_NoDecoration",                ImGuiWindowFlags_NoDecoration);                m.attr("ImGuiWindowFlags_NoDecoration")                = ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration;
    e.value("ImGuiWindowFlags_NoInputs",                    ImGuiWindowFlags_NoInputs);                    m.attr("ImGuiWindowFlags_NoInputs")                    = ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs;
    e.value("ImGuiWindowFlags_ChildWindow",                 ImGuiWindowFlags_ChildWindow);                 m.attr("ImGuiWindowFlags_ChildWindow")                 = ImGuiWindowFlags_::ImGuiWindowFlags_ChildWindow;
    e.value("ImGuiWindowFlags_Tooltip",                     ImGuiWindowFlags_Tooltip);                     m.attr("ImGuiWindowFlags_Tooltip")                     = ImGuiWindowFlags_::ImGuiWindowFlags_Tooltip;
    e.value("ImGuiWindowFlags_Popup",                       ImGuiWindowFlags_Popup);                       m.attr("ImGuiWindowFlags_Popup")                       = ImGuiWindowFlags_::ImGuiWindowFlags_Popup;
    e.value("ImGuiWindowFlags_Modal",                       ImGuiWindowFlags_Modal);                       m.attr("ImGuiWindowFlags_Modal")                       = ImGuiWindowFlags_::ImGuiWindowFlags_Modal;
    e.value("ImGuiWindowFlags_ChildMenu",                   ImGuiWindowFlags_ChildMenu);                   m.attr("ImGuiWindowFlags_ChildMenu")                   = ImGuiWindowFlags_::ImGuiWindowFlags_ChildMenu;
  ;
  }

  { // ImGuiChildFlags_
  auto e = nb::enum_<ImGuiChildFlags_>(m, "ImGuiChildFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiChildFlags_None",                         ImGuiChildFlags_None);                         m.attr("ImGuiChildFlags_None")                         = ImGuiChildFlags_::ImGuiChildFlags_None;
    e.value("ImGuiChildFlags_Borders",                      ImGuiChildFlags_Borders);                      m.attr("ImGuiChildFlags_Borders")                      = ImGuiChildFlags_::ImGuiChildFlags_Borders;
    e.value("ImGuiChildFlags_AlwaysUseWindowPadding",       ImGuiChildFlags_AlwaysUseWindowPadding);       m.attr("ImGuiChildFlags_AlwaysUseWindowPadding")       = ImGuiChildFlags_::ImGuiChildFlags_AlwaysUseWindowPadding;
    e.value("ImGuiChildFlags_ResizeX",                      ImGuiChildFlags_ResizeX);                      m.attr("ImGuiChildFlags_ResizeX")                      = ImGuiChildFlags_::ImGuiChildFlags_ResizeX;
    e.value("ImGuiChildFlags_ResizeY",                      ImGuiChildFlags_ResizeY);                      m.attr("ImGuiChildFlags_ResizeY")                      = ImGuiChildFlags_::ImGuiChildFlags_ResizeY;
    e.value("ImGuiChildFlags_AutoResizeX",                  ImGuiChildFlags_AutoResizeX);                  m.attr("ImGuiChildFlags_AutoResizeX")                  = ImGuiChildFlags_::ImGuiChildFlags_AutoResizeX;
    e.value("ImGuiChildFlags_AutoResizeY",                  ImGuiChildFlags_AutoResizeY);                  m.attr("ImGuiChildFlags_AutoResizeY")                  = ImGuiChildFlags_::ImGuiChildFlags_AutoResizeY;
    e.value("ImGuiChildFlags_AlwaysAutoResize",             ImGuiChildFlags_AlwaysAutoResize);             m.attr("ImGuiChildFlags_AlwaysAutoResize")             = ImGuiChildFlags_::ImGuiChildFlags_AlwaysAutoResize;
    e.value("ImGuiChildFlags_FrameStyle",                   ImGuiChildFlags_FrameStyle);                   m.attr("ImGuiChildFlags_FrameStyle")                   = ImGuiChildFlags_::ImGuiChildFlags_FrameStyle;
    e.value("ImGuiChildFlags_NavFlattened",                 ImGuiChildFlags_NavFlattened);                 m.attr("ImGuiChildFlags_NavFlattened")                 = ImGuiChildFlags_::ImGuiChildFlags_NavFlattened;
  ;
  }

  { // ImGuiItemFlags_
  auto e = nb::enum_<ImGuiItemFlags_>(m, "ImGuiItemFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiItemFlags_None",                          ImGuiItemFlags_None);                          m.attr("ImGuiItemFlags_None")                          = ImGuiItemFlags_::ImGuiItemFlags_None;
    e.value("ImGuiItemFlags_NoTabStop",                     ImGuiItemFlags_NoTabStop);                     m.attr("ImGuiItemFlags_NoTabStop")                     = ImGuiItemFlags_::ImGuiItemFlags_NoTabStop;
    e.value("ImGuiItemFlags_NoNav",                         ImGuiItemFlags_NoNav);                         m.attr("ImGuiItemFlags_NoNav")                         = ImGuiItemFlags_::ImGuiItemFlags_NoNav;
    e.value("ImGuiItemFlags_NoNavDefaultFocus",             ImGuiItemFlags_NoNavDefaultFocus);             m.attr("ImGuiItemFlags_NoNavDefaultFocus")             = ImGuiItemFlags_::ImGuiItemFlags_NoNavDefaultFocus;
    e.value("ImGuiItemFlags_ButtonRepeat",                  ImGuiItemFlags_ButtonRepeat);                  m.attr("ImGuiItemFlags_ButtonRepeat")                  = ImGuiItemFlags_::ImGuiItemFlags_ButtonRepeat;
    e.value("ImGuiItemFlags_AutoClosePopups",               ImGuiItemFlags_AutoClosePopups);               m.attr("ImGuiItemFlags_AutoClosePopups")               = ImGuiItemFlags_::ImGuiItemFlags_AutoClosePopups;
    e.value("ImGuiItemFlags_AllowDuplicateId",              ImGuiItemFlags_AllowDuplicateId);              m.attr("ImGuiItemFlags_AllowDuplicateId")              = ImGuiItemFlags_::ImGuiItemFlags_AllowDuplicateId;
    e.value("ImGuiItemFlags_Disabled",                      ImGuiItemFlags_Disabled);                      m.attr("ImGuiItemFlags_Disabled")                      = ImGuiItemFlags_::ImGuiItemFlags_Disabled;
  ;
  }

  { // ImGuiInputTextFlags_
  auto e = nb::enum_<ImGuiInputTextFlags_>(m, "ImGuiInputTextFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiInputTextFlags_None",                     ImGuiInputTextFlags_None);                     m.attr("ImGuiInputTextFlags_None")                     = ImGuiInputTextFlags_::ImGuiInputTextFlags_None;
    e.value("ImGuiInputTextFlags_CharsDecimal",             ImGuiInputTextFlags_CharsDecimal);             m.attr("ImGuiInputTextFlags_CharsDecimal")             = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsDecimal;
    e.value("ImGuiInputTextFlags_CharsHexadecimal",         ImGuiInputTextFlags_CharsHexadecimal);         m.attr("ImGuiInputTextFlags_CharsHexadecimal")         = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsHexadecimal;
    e.value("ImGuiInputTextFlags_CharsScientific",          ImGuiInputTextFlags_CharsScientific);          m.attr("ImGuiInputTextFlags_CharsScientific")          = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsScientific;
    e.value("ImGuiInputTextFlags_CharsUppercase",           ImGuiInputTextFlags_CharsUppercase);           m.attr("ImGuiInputTextFlags_CharsUppercase")           = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsUppercase;
    e.value("ImGuiInputTextFlags_CharsNoBlank",             ImGuiInputTextFlags_CharsNoBlank);             m.attr("ImGuiInputTextFlags_CharsNoBlank")             = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsNoBlank;
    e.value("ImGuiInputTextFlags_AllowTabInput",            ImGuiInputTextFlags_AllowTabInput);            m.attr("ImGuiInputTextFlags_AllowTabInput")            = ImGuiInputTextFlags_::ImGuiInputTextFlags_AllowTabInput;
    e.value("ImGuiInputTextFlags_EnterReturnsTrue",         ImGuiInputTextFlags_EnterReturnsTrue);         m.attr("ImGuiInputTextFlags_EnterReturnsTrue")         = ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue;
    e.value("ImGuiInputTextFlags_EscapeClearsAll",          ImGuiInputTextFlags_EscapeClearsAll);          m.attr("ImGuiInputTextFlags_EscapeClearsAll")          = ImGuiInputTextFlags_::ImGuiInputTextFlags_EscapeClearsAll;
    e.value("ImGuiInputTextFlags_CtrlEnterForNewLine",      ImGuiInputTextFlags_CtrlEnterForNewLine);      m.attr("ImGuiInputTextFlags_CtrlEnterForNewLine")      = ImGuiInputTextFlags_::ImGuiInputTextFlags_CtrlEnterForNewLine;
    e.value("ImGuiInputTextFlags_ReadOnly",                 ImGuiInputTextFlags_ReadOnly);                 m.attr("ImGuiInputTextFlags_ReadOnly")                 = ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly;
    e.value("ImGuiInputTextFlags_Password",                 ImGuiInputTextFlags_Password);                 m.attr("ImGuiInputTextFlags_Password")                 = ImGuiInputTextFlags_::ImGuiInputTextFlags_Password;
    e.value("ImGuiInputTextFlags_AlwaysOverwrite",          ImGuiInputTextFlags_AlwaysOverwrite);          m.attr("ImGuiInputTextFlags_AlwaysOverwrite")          = ImGuiInputTextFlags_::ImGuiInputTextFlags_AlwaysOverwrite;
    e.value("ImGuiInputTextFlags_AutoSelectAll",            ImGuiInputTextFlags_AutoSelectAll);            m.attr("ImGuiInputTextFlags_AutoSelectAll")            = ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll;
    e.value("ImGuiInputTextFlags_ParseEmptyRefVal",         ImGuiInputTextFlags_ParseEmptyRefVal);         m.attr("ImGuiInputTextFlags_ParseEmptyRefVal")         = ImGuiInputTextFlags_::ImGuiInputTextFlags_ParseEmptyRefVal;
    e.value("ImGuiInputTextFlags_DisplayEmptyRefVal",       ImGuiInputTextFlags_DisplayEmptyRefVal);       m.attr("ImGuiInputTextFlags_DisplayEmptyRefVal")       = ImGuiInputTextFlags_::ImGuiInputTextFlags_DisplayEmptyRefVal;
    e.value("ImGuiInputTextFlags_NoHorizontalScroll",       ImGuiInputTextFlags_NoHorizontalScroll);       m.attr("ImGuiInputTextFlags_NoHorizontalScroll")       = ImGuiInputTextFlags_::ImGuiInputTextFlags_NoHorizontalScroll;
    e.value("ImGuiInputTextFlags_NoUndoRedo",               ImGuiInputTextFlags_NoUndoRedo);               m.attr("ImGuiInputTextFlags_NoUndoRedo")               = ImGuiInputTextFlags_::ImGuiInputTextFlags_NoUndoRedo;
    e.value("ImGuiInputTextFlags_ElideLeft",                ImGuiInputTextFlags_ElideLeft);                m.attr("ImGuiInputTextFlags_ElideLeft")                = ImGuiInputTextFlags_::ImGuiInputTextFlags_ElideLeft;
    e.value("ImGuiInputTextFlags_CallbackCompletion",       ImGuiInputTextFlags_CallbackCompletion);       m.attr("ImGuiInputTextFlags_CallbackCompletion")       = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCompletion;
    e.value("ImGuiInputTextFlags_CallbackHistory",          ImGuiInputTextFlags_CallbackHistory);          m.attr("ImGuiInputTextFlags_CallbackHistory")          = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackHistory;
    e.value("ImGuiInputTextFlags_CallbackAlways",           ImGuiInputTextFlags_CallbackAlways);           m.attr("ImGuiInputTextFlags_CallbackAlways")           = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackAlways;
    e.value("ImGuiInputTextFlags_CallbackCharFilter",       ImGuiInputTextFlags_CallbackCharFilter);       m.attr("ImGuiInputTextFlags_CallbackCharFilter")       = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCharFilter;
    e.value("ImGuiInputTextFlags_CallbackResize",           ImGuiInputTextFlags_CallbackResize);           m.attr("ImGuiInputTextFlags_CallbackResize")           = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackResize;
    e.value("ImGuiInputTextFlags_CallbackEdit",             ImGuiInputTextFlags_CallbackEdit);             m.attr("ImGuiInputTextFlags_CallbackEdit")             = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackEdit;
    e.value("ImGuiInputTextFlags_WordWrap",                 ImGuiInputTextFlags_WordWrap);                 m.attr("ImGuiInputTextFlags_WordWrap")                 = ImGuiInputTextFlags_::ImGuiInputTextFlags_WordWrap;
  ;
  }

  { // ImGuiTreeNodeFlags_
  auto e = nb::enum_<ImGuiTreeNodeFlags_>(m, "ImGuiTreeNodeFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTreeNodeFlags_None",                      ImGuiTreeNodeFlags_None);                      m.attr("ImGuiTreeNodeFlags_None")                      = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_None;
    e.value("ImGuiTreeNodeFlags_Selected",                  ImGuiTreeNodeFlags_Selected);                  m.attr("ImGuiTreeNodeFlags_Selected")                  = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Selected;
    e.value("ImGuiTreeNodeFlags_Framed",                    ImGuiTreeNodeFlags_Framed);                    m.attr("ImGuiTreeNodeFlags_Framed")                    = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Framed;
    e.value("ImGuiTreeNodeFlags_AllowOverlap",              ImGuiTreeNodeFlags_AllowOverlap);              m.attr("ImGuiTreeNodeFlags_AllowOverlap")              = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_AllowOverlap;
    e.value("ImGuiTreeNodeFlags_NoTreePushOnOpen",          ImGuiTreeNodeFlags_NoTreePushOnOpen);          m.attr("ImGuiTreeNodeFlags_NoTreePushOnOpen")          = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoTreePushOnOpen;
    e.value("ImGuiTreeNodeFlags_NoAutoOpenOnLog",           ImGuiTreeNodeFlags_NoAutoOpenOnLog);           m.attr("ImGuiTreeNodeFlags_NoAutoOpenOnLog")           = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoAutoOpenOnLog;
    e.value("ImGuiTreeNodeFlags_DefaultOpen",               ImGuiTreeNodeFlags_DefaultOpen);               m.attr("ImGuiTreeNodeFlags_DefaultOpen")               = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen;
    e.value("ImGuiTreeNodeFlags_OpenOnDoubleClick",         ImGuiTreeNodeFlags_OpenOnDoubleClick);         m.attr("ImGuiTreeNodeFlags_OpenOnDoubleClick")         = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnDoubleClick;
    e.value("ImGuiTreeNodeFlags_OpenOnArrow",               ImGuiTreeNodeFlags_OpenOnArrow);               m.attr("ImGuiTreeNodeFlags_OpenOnArrow")               = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow;
    e.value("ImGuiTreeNodeFlags_Leaf",                      ImGuiTreeNodeFlags_Leaf);                      m.attr("ImGuiTreeNodeFlags_Leaf")                      = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf;
    e.value("ImGuiTreeNodeFlags_Bullet",                    ImGuiTreeNodeFlags_Bullet);                    m.attr("ImGuiTreeNodeFlags_Bullet")                    = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Bullet;
    e.value("ImGuiTreeNodeFlags_FramePadding",              ImGuiTreeNodeFlags_FramePadding);              m.attr("ImGuiTreeNodeFlags_FramePadding")              = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_FramePadding;
    e.value("ImGuiTreeNodeFlags_SpanAvailWidth",            ImGuiTreeNodeFlags_SpanAvailWidth);            m.attr("ImGuiTreeNodeFlags_SpanAvailWidth")            = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth;
    e.value("ImGuiTreeNodeFlags_SpanFullWidth",             ImGuiTreeNodeFlags_SpanFullWidth);             m.attr("ImGuiTreeNodeFlags_SpanFullWidth")             = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanFullWidth;
    e.value("ImGuiTreeNodeFlags_SpanLabelWidth",            ImGuiTreeNodeFlags_SpanLabelWidth);            m.attr("ImGuiTreeNodeFlags_SpanLabelWidth")            = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanLabelWidth;
    e.value("ImGuiTreeNodeFlags_SpanAllColumns",            ImGuiTreeNodeFlags_SpanAllColumns);            m.attr("ImGuiTreeNodeFlags_SpanAllColumns")            = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAllColumns;
    e.value("ImGuiTreeNodeFlags_LabelSpanAllColumns",       ImGuiTreeNodeFlags_LabelSpanAllColumns);       m.attr("ImGuiTreeNodeFlags_LabelSpanAllColumns")       = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_LabelSpanAllColumns;
    e.value("ImGuiTreeNodeFlags_NavLeftJumpsToParent",      ImGuiTreeNodeFlags_NavLeftJumpsToParent);      m.attr("ImGuiTreeNodeFlags_NavLeftJumpsToParent")      = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NavLeftJumpsToParent;
    e.value("ImGuiTreeNodeFlags_CollapsingHeader",          ImGuiTreeNodeFlags_CollapsingHeader);          m.attr("ImGuiTreeNodeFlags_CollapsingHeader")          = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_CollapsingHeader;
    e.value("ImGuiTreeNodeFlags_DrawLinesNone",             ImGuiTreeNodeFlags_DrawLinesNone);             m.attr("ImGuiTreeNodeFlags_DrawLinesNone")             = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DrawLinesNone;
    e.value("ImGuiTreeNodeFlags_DrawLinesFull",             ImGuiTreeNodeFlags_DrawLinesFull);             m.attr("ImGuiTreeNodeFlags_DrawLinesFull")             = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DrawLinesFull;
    e.value("ImGuiTreeNodeFlags_DrawLinesToNodes",          ImGuiTreeNodeFlags_DrawLinesToNodes);          m.attr("ImGuiTreeNodeFlags_DrawLinesToNodes")          = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DrawLinesToNodes;
    e.value("ImGuiTreeNodeFlags_NavLeftJumpsBackHere",      ImGuiTreeNodeFlags_NavLeftJumpsBackHere);      m.attr("ImGuiTreeNodeFlags_NavLeftJumpsBackHere")      = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NavLeftJumpsBackHere;
    e.value("ImGuiTreeNodeFlags_SpanTextWidth",             ImGuiTreeNodeFlags_SpanTextWidth);             m.attr("ImGuiTreeNodeFlags_SpanTextWidth")             = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanTextWidth;
  ;
  }

  { // ImGuiPopupFlags_
  auto e = nb::enum_<ImGuiPopupFlags_>(m, "ImGuiPopupFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiPopupFlags_None",                         ImGuiPopupFlags_None);                         m.attr("ImGuiPopupFlags_None")                         = ImGuiPopupFlags_::ImGuiPopupFlags_None;
    e.value("ImGuiPopupFlags_MouseButtonLeft",              ImGuiPopupFlags_MouseButtonLeft);              m.attr("ImGuiPopupFlags_MouseButtonLeft")              = ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonLeft;
    e.value("ImGuiPopupFlags_MouseButtonRight",             ImGuiPopupFlags_MouseButtonRight);             m.attr("ImGuiPopupFlags_MouseButtonRight")             = ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonRight;
    e.value("ImGuiPopupFlags_MouseButtonMiddle",            ImGuiPopupFlags_MouseButtonMiddle);            m.attr("ImGuiPopupFlags_MouseButtonMiddle")            = ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonMiddle;
    e.value("ImGuiPopupFlags_MouseButtonMask_",             ImGuiPopupFlags_MouseButtonMask_);             m.attr("ImGuiPopupFlags_MouseButtonMask_")             = ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonMask_;
    e.value("ImGuiPopupFlags_MouseButtonDefault_",          ImGuiPopupFlags_MouseButtonDefault_);          m.attr("ImGuiPopupFlags_MouseButtonDefault_")          = ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonDefault_;
    e.value("ImGuiPopupFlags_NoReopen",                     ImGuiPopupFlags_NoReopen);                     m.attr("ImGuiPopupFlags_NoReopen")                     = ImGuiPopupFlags_::ImGuiPopupFlags_NoReopen;
    e.value("ImGuiPopupFlags_NoOpenOverExistingPopup",      ImGuiPopupFlags_NoOpenOverExistingPopup);      m.attr("ImGuiPopupFlags_NoOpenOverExistingPopup")      = ImGuiPopupFlags_::ImGuiPopupFlags_NoOpenOverExistingPopup;
    e.value("ImGuiPopupFlags_NoOpenOverItems",              ImGuiPopupFlags_NoOpenOverItems);              m.attr("ImGuiPopupFlags_NoOpenOverItems")              = ImGuiPopupFlags_::ImGuiPopupFlags_NoOpenOverItems;
    e.value("ImGuiPopupFlags_AnyPopupId",                   ImGuiPopupFlags_AnyPopupId);                   m.attr("ImGuiPopupFlags_AnyPopupId")                   = ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopupId;
    e.value("ImGuiPopupFlags_AnyPopupLevel",                ImGuiPopupFlags_AnyPopupLevel);                m.attr("ImGuiPopupFlags_AnyPopupLevel")                = ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopupLevel;
    e.value("ImGuiPopupFlags_AnyPopup",                     ImGuiPopupFlags_AnyPopup);                     m.attr("ImGuiPopupFlags_AnyPopup")                     = ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopup;
  ;
  }

  { // ImGuiSelectableFlags_
  auto e = nb::enum_<ImGuiSelectableFlags_>(m, "ImGuiSelectableFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiSelectableFlags_None",                    ImGuiSelectableFlags_None);                    m.attr("ImGuiSelectableFlags_None")                    = ImGuiSelectableFlags_::ImGuiSelectableFlags_None;
    e.value("ImGuiSelectableFlags_NoAutoClosePopups",       ImGuiSelectableFlags_NoAutoClosePopups);       m.attr("ImGuiSelectableFlags_NoAutoClosePopups")       = ImGuiSelectableFlags_::ImGuiSelectableFlags_NoAutoClosePopups;
    e.value("ImGuiSelectableFlags_SpanAllColumns",          ImGuiSelectableFlags_SpanAllColumns);          m.attr("ImGuiSelectableFlags_SpanAllColumns")          = ImGuiSelectableFlags_::ImGuiSelectableFlags_SpanAllColumns;
    e.value("ImGuiSelectableFlags_AllowDoubleClick",        ImGuiSelectableFlags_AllowDoubleClick);        m.attr("ImGuiSelectableFlags_AllowDoubleClick")        = ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick;
    e.value("ImGuiSelectableFlags_Disabled",                ImGuiSelectableFlags_Disabled);                m.attr("ImGuiSelectableFlags_Disabled")                = ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled;
    e.value("ImGuiSelectableFlags_AllowOverlap",            ImGuiSelectableFlags_AllowOverlap);            m.attr("ImGuiSelectableFlags_AllowOverlap")            = ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowOverlap;
    e.value("ImGuiSelectableFlags_Highlight",               ImGuiSelectableFlags_Highlight);               m.attr("ImGuiSelectableFlags_Highlight")               = ImGuiSelectableFlags_::ImGuiSelectableFlags_Highlight;
    e.value("ImGuiSelectableFlags_SelectOnNav",             ImGuiSelectableFlags_SelectOnNav);             m.attr("ImGuiSelectableFlags_SelectOnNav")             = ImGuiSelectableFlags_::ImGuiSelectableFlags_SelectOnNav;
    e.value("ImGuiSelectableFlags_DontClosePopups",         ImGuiSelectableFlags_DontClosePopups);         m.attr("ImGuiSelectableFlags_DontClosePopups")         = ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups;
  ;
  }

  { // ImGuiComboFlags_
  auto e = nb::enum_<ImGuiComboFlags_>(m, "ImGuiComboFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiComboFlags_None",                         ImGuiComboFlags_None);                         m.attr("ImGuiComboFlags_None")                         = ImGuiComboFlags_::ImGuiComboFlags_None;
    e.value("ImGuiComboFlags_PopupAlignLeft",               ImGuiComboFlags_PopupAlignLeft);               m.attr("ImGuiComboFlags_PopupAlignLeft")               = ImGuiComboFlags_::ImGuiComboFlags_PopupAlignLeft;
    e.value("ImGuiComboFlags_HeightSmall",                  ImGuiComboFlags_HeightSmall);                  m.attr("ImGuiComboFlags_HeightSmall")                  = ImGuiComboFlags_::ImGuiComboFlags_HeightSmall;
    e.value("ImGuiComboFlags_HeightRegular",                ImGuiComboFlags_HeightRegular);                m.attr("ImGuiComboFlags_HeightRegular")                = ImGuiComboFlags_::ImGuiComboFlags_HeightRegular;
    e.value("ImGuiComboFlags_HeightLarge",                  ImGuiComboFlags_HeightLarge);                  m.attr("ImGuiComboFlags_HeightLarge")                  = ImGuiComboFlags_::ImGuiComboFlags_HeightLarge;
    e.value("ImGuiComboFlags_HeightLargest",                ImGuiComboFlags_HeightLargest);                m.attr("ImGuiComboFlags_HeightLargest")                = ImGuiComboFlags_::ImGuiComboFlags_HeightLargest;
    e.value("ImGuiComboFlags_NoArrowButton",                ImGuiComboFlags_NoArrowButton);                m.attr("ImGuiComboFlags_NoArrowButton")                = ImGuiComboFlags_::ImGuiComboFlags_NoArrowButton;
    e.value("ImGuiComboFlags_NoPreview",                    ImGuiComboFlags_NoPreview);                    m.attr("ImGuiComboFlags_NoPreview")                    = ImGuiComboFlags_::ImGuiComboFlags_NoPreview;
    e.value("ImGuiComboFlags_WidthFitPreview",              ImGuiComboFlags_WidthFitPreview);              m.attr("ImGuiComboFlags_WidthFitPreview")              = ImGuiComboFlags_::ImGuiComboFlags_WidthFitPreview;
    e.value("ImGuiComboFlags_HeightMask_",                  ImGuiComboFlags_HeightMask_);                  m.attr("ImGuiComboFlags_HeightMask_")                  = ImGuiComboFlags_::ImGuiComboFlags_HeightMask_;
  ;
  }

  { // ImGuiTabBarFlags_
  auto e = nb::enum_<ImGuiTabBarFlags_>(m, "ImGuiTabBarFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTabBarFlags_None",                        ImGuiTabBarFlags_None);                        m.attr("ImGuiTabBarFlags_None")                        = ImGuiTabBarFlags_::ImGuiTabBarFlags_None;
    e.value("ImGuiTabBarFlags_Reorderable",                 ImGuiTabBarFlags_Reorderable);                 m.attr("ImGuiTabBarFlags_Reorderable")                 = ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable;
    e.value("ImGuiTabBarFlags_AutoSelectNewTabs",           ImGuiTabBarFlags_AutoSelectNewTabs);           m.attr("ImGuiTabBarFlags_AutoSelectNewTabs")           = ImGuiTabBarFlags_::ImGuiTabBarFlags_AutoSelectNewTabs;
    e.value("ImGuiTabBarFlags_TabListPopupButton",          ImGuiTabBarFlags_TabListPopupButton);          m.attr("ImGuiTabBarFlags_TabListPopupButton")          = ImGuiTabBarFlags_::ImGuiTabBarFlags_TabListPopupButton;
    e.value("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton); m.attr("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton") = ImGuiTabBarFlags_::ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;
    e.value("ImGuiTabBarFlags_NoTabListScrollingButtons",   ImGuiTabBarFlags_NoTabListScrollingButtons);   m.attr("ImGuiTabBarFlags_NoTabListScrollingButtons")   = ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTabListScrollingButtons;
    e.value("ImGuiTabBarFlags_NoTooltip",                   ImGuiTabBarFlags_NoTooltip);                   m.attr("ImGuiTabBarFlags_NoTooltip")                   = ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTooltip;
    e.value("ImGuiTabBarFlags_DrawSelectedOverline",        ImGuiTabBarFlags_DrawSelectedOverline);        m.attr("ImGuiTabBarFlags_DrawSelectedOverline")        = ImGuiTabBarFlags_::ImGuiTabBarFlags_DrawSelectedOverline;
    e.value("ImGuiTabBarFlags_FittingPolicyMixed",          ImGuiTabBarFlags_FittingPolicyMixed);          m.attr("ImGuiTabBarFlags_FittingPolicyMixed")          = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyMixed;
    e.value("ImGuiTabBarFlags_FittingPolicyShrink",         ImGuiTabBarFlags_FittingPolicyShrink);         m.attr("ImGuiTabBarFlags_FittingPolicyShrink")         = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyShrink;
    e.value("ImGuiTabBarFlags_FittingPolicyScroll",         ImGuiTabBarFlags_FittingPolicyScroll);         m.attr("ImGuiTabBarFlags_FittingPolicyScroll")         = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyScroll;
    e.value("ImGuiTabBarFlags_FittingPolicyMask_",          ImGuiTabBarFlags_FittingPolicyMask_);          m.attr("ImGuiTabBarFlags_FittingPolicyMask_")          = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyMask_;
    e.value("ImGuiTabBarFlags_FittingPolicyDefault_",       ImGuiTabBarFlags_FittingPolicyDefault_);       m.attr("ImGuiTabBarFlags_FittingPolicyDefault_")       = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyDefault_;
    e.value("ImGuiTabBarFlags_FittingPolicyResizeDown",     ImGuiTabBarFlags_FittingPolicyResizeDown);     m.attr("ImGuiTabBarFlags_FittingPolicyResizeDown")     = ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyResizeDown;
  ;
  }

  { // ImGuiTabItemFlags_
  auto e = nb::enum_<ImGuiTabItemFlags_>(m, "ImGuiTabItemFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTabItemFlags_None",                       ImGuiTabItemFlags_None);                       m.attr("ImGuiTabItemFlags_None")                       = ImGuiTabItemFlags_::ImGuiTabItemFlags_None;
    e.value("ImGuiTabItemFlags_UnsavedDocument",            ImGuiTabItemFlags_UnsavedDocument);            m.attr("ImGuiTabItemFlags_UnsavedDocument")            = ImGuiTabItemFlags_::ImGuiTabItemFlags_UnsavedDocument;
    e.value("ImGuiTabItemFlags_SetSelected",                ImGuiTabItemFlags_SetSelected);                m.attr("ImGuiTabItemFlags_SetSelected")                = ImGuiTabItemFlags_::ImGuiTabItemFlags_SetSelected;
    e.value("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton); m.attr("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton") = ImGuiTabItemFlags_::ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
    e.value("ImGuiTabItemFlags_NoPushId",                   ImGuiTabItemFlags_NoPushId);                   m.attr("ImGuiTabItemFlags_NoPushId")                   = ImGuiTabItemFlags_::ImGuiTabItemFlags_NoPushId;
    e.value("ImGuiTabItemFlags_NoTooltip",                  ImGuiTabItemFlags_NoTooltip);                  m.attr("ImGuiTabItemFlags_NoTooltip")                  = ImGuiTabItemFlags_::ImGuiTabItemFlags_NoTooltip;
    e.value("ImGuiTabItemFlags_NoReorder",                  ImGuiTabItemFlags_NoReorder);                  m.attr("ImGuiTabItemFlags_NoReorder")                  = ImGuiTabItemFlags_::ImGuiTabItemFlags_NoReorder;
    e.value("ImGuiTabItemFlags_Leading",                    ImGuiTabItemFlags_Leading);                    m.attr("ImGuiTabItemFlags_Leading")                    = ImGuiTabItemFlags_::ImGuiTabItemFlags_Leading;
    e.value("ImGuiTabItemFlags_Trailing",                   ImGuiTabItemFlags_Trailing);                   m.attr("ImGuiTabItemFlags_Trailing")                   = ImGuiTabItemFlags_::ImGuiTabItemFlags_Trailing;
    e.value("ImGuiTabItemFlags_NoAssumedClosure",           ImGuiTabItemFlags_NoAssumedClosure);           m.attr("ImGuiTabItemFlags_NoAssumedClosure")           = ImGuiTabItemFlags_::ImGuiTabItemFlags_NoAssumedClosure;
  ;
  }

  { // ImGuiFocusedFlags_
  auto e = nb::enum_<ImGuiFocusedFlags_>(m, "ImGuiFocusedFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiFocusedFlags_None",                       ImGuiFocusedFlags_None);                       m.attr("ImGuiFocusedFlags_None")                       = ImGuiFocusedFlags_::ImGuiFocusedFlags_None;
    e.value("ImGuiFocusedFlags_ChildWindows",               ImGuiFocusedFlags_ChildWindows);               m.attr("ImGuiFocusedFlags_ChildWindows")               = ImGuiFocusedFlags_::ImGuiFocusedFlags_ChildWindows;
    e.value("ImGuiFocusedFlags_RootWindow",                 ImGuiFocusedFlags_RootWindow);                 m.attr("ImGuiFocusedFlags_RootWindow")                 = ImGuiFocusedFlags_::ImGuiFocusedFlags_RootWindow;
    e.value("ImGuiFocusedFlags_AnyWindow",                  ImGuiFocusedFlags_AnyWindow);                  m.attr("ImGuiFocusedFlags_AnyWindow")                  = ImGuiFocusedFlags_::ImGuiFocusedFlags_AnyWindow;
    e.value("ImGuiFocusedFlags_NoPopupHierarchy",           ImGuiFocusedFlags_NoPopupHierarchy);           m.attr("ImGuiFocusedFlags_NoPopupHierarchy")           = ImGuiFocusedFlags_::ImGuiFocusedFlags_NoPopupHierarchy;
    e.value("ImGuiFocusedFlags_RootAndChildWindows",        ImGuiFocusedFlags_RootAndChildWindows);        m.attr("ImGuiFocusedFlags_RootAndChildWindows")        = ImGuiFocusedFlags_::ImGuiFocusedFlags_RootAndChildWindows;
  ;
  }

  { // ImGuiHoveredFlags_
  auto e = nb::enum_<ImGuiHoveredFlags_>(m, "ImGuiHoveredFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiHoveredFlags_None",                       ImGuiHoveredFlags_None);                       m.attr("ImGuiHoveredFlags_None")                       = ImGuiHoveredFlags_::ImGuiHoveredFlags_None;
    e.value("ImGuiHoveredFlags_ChildWindows",               ImGuiHoveredFlags_ChildWindows);               m.attr("ImGuiHoveredFlags_ChildWindows")               = ImGuiHoveredFlags_::ImGuiHoveredFlags_ChildWindows;
    e.value("ImGuiHoveredFlags_RootWindow",                 ImGuiHoveredFlags_RootWindow);                 m.attr("ImGuiHoveredFlags_RootWindow")                 = ImGuiHoveredFlags_::ImGuiHoveredFlags_RootWindow;
    e.value("ImGuiHoveredFlags_AnyWindow",                  ImGuiHoveredFlags_AnyWindow);                  m.attr("ImGuiHoveredFlags_AnyWindow")                  = ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow;
    e.value("ImGuiHoveredFlags_NoPopupHierarchy",           ImGuiHoveredFlags_NoPopupHierarchy);           m.attr("ImGuiHoveredFlags_NoPopupHierarchy")           = ImGuiHoveredFlags_::ImGuiHoveredFlags_NoPopupHierarchy;
    e.value("ImGuiHoveredFlags_AllowWhenBlockedByPopup",    ImGuiHoveredFlags_AllowWhenBlockedByPopup);    m.attr("ImGuiHoveredFlags_AllowWhenBlockedByPopup")    = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenBlockedByPopup;
    e.value("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem", ImGuiHoveredFlags_AllowWhenBlockedByActiveItem); m.attr("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem") = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenBlockedByActiveItem;
    e.value("ImGuiHoveredFlags_AllowWhenOverlappedByItem",  ImGuiHoveredFlags_AllowWhenOverlappedByItem);  m.attr("ImGuiHoveredFlags_AllowWhenOverlappedByItem")  = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlappedByItem;
    e.value("ImGuiHoveredFlags_AllowWhenOverlappedByWindow", ImGuiHoveredFlags_AllowWhenOverlappedByWindow); m.attr("ImGuiHoveredFlags_AllowWhenOverlappedByWindow") = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlappedByWindow;
    e.value("ImGuiHoveredFlags_AllowWhenDisabled",          ImGuiHoveredFlags_AllowWhenDisabled);          m.attr("ImGuiHoveredFlags_AllowWhenDisabled")          = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenDisabled;
    e.value("ImGuiHoveredFlags_NoNavOverride",              ImGuiHoveredFlags_NoNavOverride);              m.attr("ImGuiHoveredFlags_NoNavOverride")              = ImGuiHoveredFlags_::ImGuiHoveredFlags_NoNavOverride;
    e.value("ImGuiHoveredFlags_AllowWhenOverlapped",        ImGuiHoveredFlags_AllowWhenOverlapped);        m.attr("ImGuiHoveredFlags_AllowWhenOverlapped")        = ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlapped;
    e.value("ImGuiHoveredFlags_RectOnly",                   ImGuiHoveredFlags_RectOnly);                   m.attr("ImGuiHoveredFlags_RectOnly")                   = ImGuiHoveredFlags_::ImGuiHoveredFlags_RectOnly;
    e.value("ImGuiHoveredFlags_RootAndChildWindows",        ImGuiHoveredFlags_RootAndChildWindows);        m.attr("ImGuiHoveredFlags_RootAndChildWindows")        = ImGuiHoveredFlags_::ImGuiHoveredFlags_RootAndChildWindows;
    e.value("ImGuiHoveredFlags_ForTooltip",                 ImGuiHoveredFlags_ForTooltip);                 m.attr("ImGuiHoveredFlags_ForTooltip")                 = ImGuiHoveredFlags_::ImGuiHoveredFlags_ForTooltip;
    e.value("ImGuiHoveredFlags_Stationary",                 ImGuiHoveredFlags_Stationary);                 m.attr("ImGuiHoveredFlags_Stationary")                 = ImGuiHoveredFlags_::ImGuiHoveredFlags_Stationary;
    e.value("ImGuiHoveredFlags_DelayNone",                  ImGuiHoveredFlags_DelayNone);                  m.attr("ImGuiHoveredFlags_DelayNone")                  = ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayNone;
    e.value("ImGuiHoveredFlags_DelayShort",                 ImGuiHoveredFlags_DelayShort);                 m.attr("ImGuiHoveredFlags_DelayShort")                 = ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayShort;
    e.value("ImGuiHoveredFlags_DelayNormal",                ImGuiHoveredFlags_DelayNormal);                m.attr("ImGuiHoveredFlags_DelayNormal")                = ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayNormal;
    e.value("ImGuiHoveredFlags_NoSharedDelay",              ImGuiHoveredFlags_NoSharedDelay);              m.attr("ImGuiHoveredFlags_NoSharedDelay")              = ImGuiHoveredFlags_::ImGuiHoveredFlags_NoSharedDelay;
  ;
  }

  { // ImGuiDragDropFlags_
  auto e = nb::enum_<ImGuiDragDropFlags_>(m, "ImGuiDragDropFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiDragDropFlags_None",                      ImGuiDragDropFlags_None);                      m.attr("ImGuiDragDropFlags_None")                      = ImGuiDragDropFlags_::ImGuiDragDropFlags_None;
    e.value("ImGuiDragDropFlags_SourceNoPreviewTooltip",    ImGuiDragDropFlags_SourceNoPreviewTooltip);    m.attr("ImGuiDragDropFlags_SourceNoPreviewTooltip")    = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoPreviewTooltip;
    e.value("ImGuiDragDropFlags_SourceNoDisableHover",      ImGuiDragDropFlags_SourceNoDisableHover);      m.attr("ImGuiDragDropFlags_SourceNoDisableHover")      = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoDisableHover;
    e.value("ImGuiDragDropFlags_SourceNoHoldToOpenOthers",  ImGuiDragDropFlags_SourceNoHoldToOpenOthers);  m.attr("ImGuiDragDropFlags_SourceNoHoldToOpenOthers")  = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
    e.value("ImGuiDragDropFlags_SourceAllowNullID",         ImGuiDragDropFlags_SourceAllowNullID);         m.attr("ImGuiDragDropFlags_SourceAllowNullID")         = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceAllowNullID;
    e.value("ImGuiDragDropFlags_SourceExtern",              ImGuiDragDropFlags_SourceExtern);              m.attr("ImGuiDragDropFlags_SourceExtern")              = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceExtern;
    e.value("ImGuiDragDropFlags_PayloadAutoExpire",         ImGuiDragDropFlags_PayloadAutoExpire);         m.attr("ImGuiDragDropFlags_PayloadAutoExpire")         = ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadAutoExpire;
    e.value("ImGuiDragDropFlags_PayloadNoCrossContext",     ImGuiDragDropFlags_PayloadNoCrossContext);     m.attr("ImGuiDragDropFlags_PayloadNoCrossContext")     = ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadNoCrossContext;
    e.value("ImGuiDragDropFlags_PayloadNoCrossProcess",     ImGuiDragDropFlags_PayloadNoCrossProcess);     m.attr("ImGuiDragDropFlags_PayloadNoCrossProcess")     = ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadNoCrossProcess;
    e.value("ImGuiDragDropFlags_AcceptBeforeDelivery",      ImGuiDragDropFlags_AcceptBeforeDelivery);      m.attr("ImGuiDragDropFlags_AcceptBeforeDelivery")      = ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptBeforeDelivery;
    e.value("ImGuiDragDropFlags_AcceptNoDrawDefaultRect",   ImGuiDragDropFlags_AcceptNoDrawDefaultRect);   m.attr("ImGuiDragDropFlags_AcceptNoDrawDefaultRect")   = ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
    e.value("ImGuiDragDropFlags_AcceptNoPreviewTooltip",    ImGuiDragDropFlags_AcceptNoPreviewTooltip);    m.attr("ImGuiDragDropFlags_AcceptNoPreviewTooltip")    = ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptNoPreviewTooltip;
    e.value("ImGuiDragDropFlags_AcceptDrawAsHovered",       ImGuiDragDropFlags_AcceptDrawAsHovered);       m.attr("ImGuiDragDropFlags_AcceptDrawAsHovered")       = ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptDrawAsHovered;
    e.value("ImGuiDragDropFlags_AcceptPeekOnly",            ImGuiDragDropFlags_AcceptPeekOnly);            m.attr("ImGuiDragDropFlags_AcceptPeekOnly")            = ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptPeekOnly;
    e.value("ImGuiDragDropFlags_SourceAutoExpirePayload",   ImGuiDragDropFlags_SourceAutoExpirePayload);   m.attr("ImGuiDragDropFlags_SourceAutoExpirePayload")   = ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceAutoExpirePayload;
  ;
  }

  { // ImGuiDataType_
  auto e = nb::enum_<ImGuiDataType_>(m, "ImGuiDataType_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiDataType_S8",                             ImGuiDataType_S8);                             m.attr("ImGuiDataType_S8")                             = ImGuiDataType_::ImGuiDataType_S8;
    e.value("ImGuiDataType_U8",                             ImGuiDataType_U8);                             m.attr("ImGuiDataType_U8")                             = ImGuiDataType_::ImGuiDataType_U8;
    e.value("ImGuiDataType_S16",                            ImGuiDataType_S16);                            m.attr("ImGuiDataType_S16")                            = ImGuiDataType_::ImGuiDataType_S16;
    e.value("ImGuiDataType_U16",                            ImGuiDataType_U16);                            m.attr("ImGuiDataType_U16")                            = ImGuiDataType_::ImGuiDataType_U16;
    e.value("ImGuiDataType_S32",                            ImGuiDataType_S32);                            m.attr("ImGuiDataType_S32")                            = ImGuiDataType_::ImGuiDataType_S32;
    e.value("ImGuiDataType_U32",                            ImGuiDataType_U32);                            m.attr("ImGuiDataType_U32")                            = ImGuiDataType_::ImGuiDataType_U32;
    e.value("ImGuiDataType_S64",                            ImGuiDataType_S64);                            m.attr("ImGuiDataType_S64")                            = ImGuiDataType_::ImGuiDataType_S64;
    e.value("ImGuiDataType_U64",                            ImGuiDataType_U64);                            m.attr("ImGuiDataType_U64")                            = ImGuiDataType_::ImGuiDataType_U64;
    e.value("ImGuiDataType_Float",                          ImGuiDataType_Float);                          m.attr("ImGuiDataType_Float")                          = ImGuiDataType_::ImGuiDataType_Float;
    e.value("ImGuiDataType_Double",                         ImGuiDataType_Double);                         m.attr("ImGuiDataType_Double")                         = ImGuiDataType_::ImGuiDataType_Double;
    e.value("ImGuiDataType_Bool",                           ImGuiDataType_Bool);                           m.attr("ImGuiDataType_Bool")                           = ImGuiDataType_::ImGuiDataType_Bool;
    e.value("ImGuiDataType_String",                         ImGuiDataType_String);                         m.attr("ImGuiDataType_String")                         = ImGuiDataType_::ImGuiDataType_String;
    e.value("ImGuiDataType_COUNT",                          ImGuiDataType_COUNT);                          m.attr("ImGuiDataType_COUNT")                          = ImGuiDataType_::ImGuiDataType_COUNT;
  ;
  }

  { // ImGuiDir
  auto e = nb::enum_<ImGuiDir>(m, "ImGuiDir", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiDir_None",                                ImGuiDir_None);                                m.attr("ImGuiDir_None")                                = ImGuiDir::ImGuiDir_None;
    e.value("ImGuiDir_Left",                                ImGuiDir_Left);                                m.attr("ImGuiDir_Left")                                = ImGuiDir::ImGuiDir_Left;
    e.value("ImGuiDir_Right",                               ImGuiDir_Right);                               m.attr("ImGuiDir_Right")                               = ImGuiDir::ImGuiDir_Right;
    e.value("ImGuiDir_Up",                                  ImGuiDir_Up);                                  m.attr("ImGuiDir_Up")                                  = ImGuiDir::ImGuiDir_Up;
    e.value("ImGuiDir_Down",                                ImGuiDir_Down);                                m.attr("ImGuiDir_Down")                                = ImGuiDir::ImGuiDir_Down;
    e.value("ImGuiDir_COUNT",                               ImGuiDir_COUNT);                               m.attr("ImGuiDir_COUNT")                               = ImGuiDir::ImGuiDir_COUNT;
  ;
  }

  { // ImGuiSortDirection
  auto e = nb::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiSortDirection_None",                      ImGuiSortDirection_None);                      m.attr("ImGuiSortDirection_None")                      = ImGuiSortDirection::ImGuiSortDirection_None;
    e.value("ImGuiSortDirection_Ascending",                 ImGuiSortDirection_Ascending);                 m.attr("ImGuiSortDirection_Ascending")                 = ImGuiSortDirection::ImGuiSortDirection_Ascending;
    e.value("ImGuiSortDirection_Descending",                ImGuiSortDirection_Descending);                m.attr("ImGuiSortDirection_Descending")                = ImGuiSortDirection::ImGuiSortDirection_Descending;
  ;
  }

  { // ImGuiKey
  auto e = nb::enum_<ImGuiKey>(m, "ImGuiKey", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiKey_None",                                ImGuiKey_None);                                m.attr("ImGuiKey_None")                                = ImGuiKey::ImGuiKey_None;
    e.value("ImGuiKey_NamedKey_BEGIN",                      ImGuiKey_NamedKey_BEGIN);                      m.attr("ImGuiKey_NamedKey_BEGIN")                      = ImGuiKey::ImGuiKey_NamedKey_BEGIN;
    e.value("ImGuiKey_Tab",                                 ImGuiKey_Tab);                                 m.attr("ImGuiKey_Tab")                                 = ImGuiKey::ImGuiKey_Tab;
    e.value("ImGuiKey_LeftArrow",                           ImGuiKey_LeftArrow);                           m.attr("ImGuiKey_LeftArrow")                           = ImGuiKey::ImGuiKey_LeftArrow;
    e.value("ImGuiKey_RightArrow",                          ImGuiKey_RightArrow);                          m.attr("ImGuiKey_RightArrow")                          = ImGuiKey::ImGuiKey_RightArrow;
    e.value("ImGuiKey_UpArrow",                             ImGuiKey_UpArrow);                             m.attr("ImGuiKey_UpArrow")                             = ImGuiKey::ImGuiKey_UpArrow;
    e.value("ImGuiKey_DownArrow",                           ImGuiKey_DownArrow);                           m.attr("ImGuiKey_DownArrow")                           = ImGuiKey::ImGuiKey_DownArrow;
    e.value("ImGuiKey_PageUp",                              ImGuiKey_PageUp);                              m.attr("ImGuiKey_PageUp")                              = ImGuiKey::ImGuiKey_PageUp;
    e.value("ImGuiKey_PageDown",                            ImGuiKey_PageDown);                            m.attr("ImGuiKey_PageDown")                            = ImGuiKey::ImGuiKey_PageDown;
    e.value("ImGuiKey_Home",                                ImGuiKey_Home);                                m.attr("ImGuiKey_Home")                                = ImGuiKey::ImGuiKey_Home;
    e.value("ImGuiKey_End",                                 ImGuiKey_End);                                 m.attr("ImGuiKey_End")                                 = ImGuiKey::ImGuiKey_End;
    e.value("ImGuiKey_Insert",                              ImGuiKey_Insert);                              m.attr("ImGuiKey_Insert")                              = ImGuiKey::ImGuiKey_Insert;
    e.value("ImGuiKey_Delete",                              ImGuiKey_Delete);                              m.attr("ImGuiKey_Delete")                              = ImGuiKey::ImGuiKey_Delete;
    e.value("ImGuiKey_Backspace",                           ImGuiKey_Backspace);                           m.attr("ImGuiKey_Backspace")                           = ImGuiKey::ImGuiKey_Backspace;
    e.value("ImGuiKey_Space",                               ImGuiKey_Space);                               m.attr("ImGuiKey_Space")                               = ImGuiKey::ImGuiKey_Space;
    e.value("ImGuiKey_Enter",                               ImGuiKey_Enter);                               m.attr("ImGuiKey_Enter")                               = ImGuiKey::ImGuiKey_Enter;
    e.value("ImGuiKey_Escape",                              ImGuiKey_Escape);                              m.attr("ImGuiKey_Escape")                              = ImGuiKey::ImGuiKey_Escape;
    e.value("ImGuiKey_LeftCtrl",                            ImGuiKey_LeftCtrl);                            m.attr("ImGuiKey_LeftCtrl")                            = ImGuiKey::ImGuiKey_LeftCtrl;
    e.value("ImGuiKey_LeftShift",                           ImGuiKey_LeftShift);                           m.attr("ImGuiKey_LeftShift")                           = ImGuiKey::ImGuiKey_LeftShift;
    e.value("ImGuiKey_LeftAlt",                             ImGuiKey_LeftAlt);                             m.attr("ImGuiKey_LeftAlt")                             = ImGuiKey::ImGuiKey_LeftAlt;
    e.value("ImGuiKey_LeftSuper",                           ImGuiKey_LeftSuper);                           m.attr("ImGuiKey_LeftSuper")                           = ImGuiKey::ImGuiKey_LeftSuper;
    e.value("ImGuiKey_RightCtrl",                           ImGuiKey_RightCtrl);                           m.attr("ImGuiKey_RightCtrl")                           = ImGuiKey::ImGuiKey_RightCtrl;
    e.value("ImGuiKey_RightShift",                          ImGuiKey_RightShift);                          m.attr("ImGuiKey_RightShift")                          = ImGuiKey::ImGuiKey_RightShift;
    e.value("ImGuiKey_RightAlt",                            ImGuiKey_RightAlt);                            m.attr("ImGuiKey_RightAlt")                            = ImGuiKey::ImGuiKey_RightAlt;
    e.value("ImGuiKey_RightSuper",                          ImGuiKey_RightSuper);                          m.attr("ImGuiKey_RightSuper")                          = ImGuiKey::ImGuiKey_RightSuper;
    e.value("ImGuiKey_Menu",                                ImGuiKey_Menu);                                m.attr("ImGuiKey_Menu")                                = ImGuiKey::ImGuiKey_Menu;
    e.value("ImGuiKey_0",                                   ImGuiKey_0);                                   m.attr("ImGuiKey_0")                                   = ImGuiKey::ImGuiKey_0;
    e.value("ImGuiKey_1",                                   ImGuiKey_1);                                   m.attr("ImGuiKey_1")                                   = ImGuiKey::ImGuiKey_1;
    e.value("ImGuiKey_2",                                   ImGuiKey_2);                                   m.attr("ImGuiKey_2")                                   = ImGuiKey::ImGuiKey_2;
    e.value("ImGuiKey_3",                                   ImGuiKey_3);                                   m.attr("ImGuiKey_3")                                   = ImGuiKey::ImGuiKey_3;
    e.value("ImGuiKey_4",                                   ImGuiKey_4);                                   m.attr("ImGuiKey_4")                                   = ImGuiKey::ImGuiKey_4;
    e.value("ImGuiKey_5",                                   ImGuiKey_5);                                   m.attr("ImGuiKey_5")                                   = ImGuiKey::ImGuiKey_5;
    e.value("ImGuiKey_6",                                   ImGuiKey_6);                                   m.attr("ImGuiKey_6")                                   = ImGuiKey::ImGuiKey_6;
    e.value("ImGuiKey_7",                                   ImGuiKey_7);                                   m.attr("ImGuiKey_7")                                   = ImGuiKey::ImGuiKey_7;
    e.value("ImGuiKey_8",                                   ImGuiKey_8);                                   m.attr("ImGuiKey_8")                                   = ImGuiKey::ImGuiKey_8;
    e.value("ImGuiKey_9",                                   ImGuiKey_9);                                   m.attr("ImGuiKey_9")                                   = ImGuiKey::ImGuiKey_9;
    e.value("ImGuiKey_A",                                   ImGuiKey_A);                                   m.attr("ImGuiKey_A")                                   = ImGuiKey::ImGuiKey_A;
    e.value("ImGuiKey_B",                                   ImGuiKey_B);                                   m.attr("ImGuiKey_B")                                   = ImGuiKey::ImGuiKey_B;
    e.value("ImGuiKey_C",                                   ImGuiKey_C);                                   m.attr("ImGuiKey_C")                                   = ImGuiKey::ImGuiKey_C;
    e.value("ImGuiKey_D",                                   ImGuiKey_D);                                   m.attr("ImGuiKey_D")                                   = ImGuiKey::ImGuiKey_D;
    e.value("ImGuiKey_E",                                   ImGuiKey_E);                                   m.attr("ImGuiKey_E")                                   = ImGuiKey::ImGuiKey_E;
    e.value("ImGuiKey_F",                                   ImGuiKey_F);                                   m.attr("ImGuiKey_F")                                   = ImGuiKey::ImGuiKey_F;
    e.value("ImGuiKey_G",                                   ImGuiKey_G);                                   m.attr("ImGuiKey_G")                                   = ImGuiKey::ImGuiKey_G;
    e.value("ImGuiKey_H",                                   ImGuiKey_H);                                   m.attr("ImGuiKey_H")                                   = ImGuiKey::ImGuiKey_H;
    e.value("ImGuiKey_I",                                   ImGuiKey_I);                                   m.attr("ImGuiKey_I")                                   = ImGuiKey::ImGuiKey_I;
    e.value("ImGuiKey_J",                                   ImGuiKey_J);                                   m.attr("ImGuiKey_J")                                   = ImGuiKey::ImGuiKey_J;
    e.value("ImGuiKey_K",                                   ImGuiKey_K);                                   m.attr("ImGuiKey_K")                                   = ImGuiKey::ImGuiKey_K;
    e.value("ImGuiKey_L",                                   ImGuiKey_L);                                   m.attr("ImGuiKey_L")                                   = ImGuiKey::ImGuiKey_L;
    e.value("ImGuiKey_M",                                   ImGuiKey_M);                                   m.attr("ImGuiKey_M")                                   = ImGuiKey::ImGuiKey_M;
    e.value("ImGuiKey_N",                                   ImGuiKey_N);                                   m.attr("ImGuiKey_N")                                   = ImGuiKey::ImGuiKey_N;
    e.value("ImGuiKey_O",                                   ImGuiKey_O);                                   m.attr("ImGuiKey_O")                                   = ImGuiKey::ImGuiKey_O;
    e.value("ImGuiKey_P",                                   ImGuiKey_P);                                   m.attr("ImGuiKey_P")                                   = ImGuiKey::ImGuiKey_P;
    e.value("ImGuiKey_Q",                                   ImGuiKey_Q);                                   m.attr("ImGuiKey_Q")                                   = ImGuiKey::ImGuiKey_Q;
    e.value("ImGuiKey_R",                                   ImGuiKey_R);                                   m.attr("ImGuiKey_R")                                   = ImGuiKey::ImGuiKey_R;
    e.value("ImGuiKey_S",                                   ImGuiKey_S);                                   m.attr("ImGuiKey_S")                                   = ImGuiKey::ImGuiKey_S;
    e.value("ImGuiKey_T",                                   ImGuiKey_T);                                   m.attr("ImGuiKey_T")                                   = ImGuiKey::ImGuiKey_T;
    e.value("ImGuiKey_U",                                   ImGuiKey_U);                                   m.attr("ImGuiKey_U")                                   = ImGuiKey::ImGuiKey_U;
    e.value("ImGuiKey_V",                                   ImGuiKey_V);                                   m.attr("ImGuiKey_V")                                   = ImGuiKey::ImGuiKey_V;
    e.value("ImGuiKey_W",                                   ImGuiKey_W);                                   m.attr("ImGuiKey_W")                                   = ImGuiKey::ImGuiKey_W;
    e.value("ImGuiKey_X",                                   ImGuiKey_X);                                   m.attr("ImGuiKey_X")                                   = ImGuiKey::ImGuiKey_X;
    e.value("ImGuiKey_Y",                                   ImGuiKey_Y);                                   m.attr("ImGuiKey_Y")                                   = ImGuiKey::ImGuiKey_Y;
    e.value("ImGuiKey_Z",                                   ImGuiKey_Z);                                   m.attr("ImGuiKey_Z")                                   = ImGuiKey::ImGuiKey_Z;
    e.value("ImGuiKey_F1",                                  ImGuiKey_F1);                                  m.attr("ImGuiKey_F1")                                  = ImGuiKey::ImGuiKey_F1;
    e.value("ImGuiKey_F2",                                  ImGuiKey_F2);                                  m.attr("ImGuiKey_F2")                                  = ImGuiKey::ImGuiKey_F2;
    e.value("ImGuiKey_F3",                                  ImGuiKey_F3);                                  m.attr("ImGuiKey_F3")                                  = ImGuiKey::ImGuiKey_F3;
    e.value("ImGuiKey_F4",                                  ImGuiKey_F4);                                  m.attr("ImGuiKey_F4")                                  = ImGuiKey::ImGuiKey_F4;
    e.value("ImGuiKey_F5",                                  ImGuiKey_F5);                                  m.attr("ImGuiKey_F5")                                  = ImGuiKey::ImGuiKey_F5;
    e.value("ImGuiKey_F6",                                  ImGuiKey_F6);                                  m.attr("ImGuiKey_F6")                                  = ImGuiKey::ImGuiKey_F6;
    e.value("ImGuiKey_F7",                                  ImGuiKey_F7);                                  m.attr("ImGuiKey_F7")                                  = ImGuiKey::ImGuiKey_F7;
    e.value("ImGuiKey_F8",                                  ImGuiKey_F8);                                  m.attr("ImGuiKey_F8")                                  = ImGuiKey::ImGuiKey_F8;
    e.value("ImGuiKey_F9",                                  ImGuiKey_F9);                                  m.attr("ImGuiKey_F9")                                  = ImGuiKey::ImGuiKey_F9;
    e.value("ImGuiKey_F10",                                 ImGuiKey_F10);                                 m.attr("ImGuiKey_F10")                                 = ImGuiKey::ImGuiKey_F10;
    e.value("ImGuiKey_F11",                                 ImGuiKey_F11);                                 m.attr("ImGuiKey_F11")                                 = ImGuiKey::ImGuiKey_F11;
    e.value("ImGuiKey_F12",                                 ImGuiKey_F12);                                 m.attr("ImGuiKey_F12")                                 = ImGuiKey::ImGuiKey_F12;
    e.value("ImGuiKey_F13",                                 ImGuiKey_F13);                                 m.attr("ImGuiKey_F13")                                 = ImGuiKey::ImGuiKey_F13;
    e.value("ImGuiKey_F14",                                 ImGuiKey_F14);                                 m.attr("ImGuiKey_F14")                                 = ImGuiKey::ImGuiKey_F14;
    e.value("ImGuiKey_F15",                                 ImGuiKey_F15);                                 m.attr("ImGuiKey_F15")                                 = ImGuiKey::ImGuiKey_F15;
    e.value("ImGuiKey_F16",                                 ImGuiKey_F16);                                 m.attr("ImGuiKey_F16")                                 = ImGuiKey::ImGuiKey_F16;
    e.value("ImGuiKey_F17",                                 ImGuiKey_F17);                                 m.attr("ImGuiKey_F17")                                 = ImGuiKey::ImGuiKey_F17;
    e.value("ImGuiKey_F18",                                 ImGuiKey_F18);                                 m.attr("ImGuiKey_F18")                                 = ImGuiKey::ImGuiKey_F18;
    e.value("ImGuiKey_F19",                                 ImGuiKey_F19);                                 m.attr("ImGuiKey_F19")                                 = ImGuiKey::ImGuiKey_F19;
    e.value("ImGuiKey_F20",                                 ImGuiKey_F20);                                 m.attr("ImGuiKey_F20")                                 = ImGuiKey::ImGuiKey_F20;
    e.value("ImGuiKey_F21",                                 ImGuiKey_F21);                                 m.attr("ImGuiKey_F21")                                 = ImGuiKey::ImGuiKey_F21;
    e.value("ImGuiKey_F22",                                 ImGuiKey_F22);                                 m.attr("ImGuiKey_F22")                                 = ImGuiKey::ImGuiKey_F22;
    e.value("ImGuiKey_F23",                                 ImGuiKey_F23);                                 m.attr("ImGuiKey_F23")                                 = ImGuiKey::ImGuiKey_F23;
    e.value("ImGuiKey_F24",                                 ImGuiKey_F24);                                 m.attr("ImGuiKey_F24")                                 = ImGuiKey::ImGuiKey_F24;
    e.value("ImGuiKey_Apostrophe",                          ImGuiKey_Apostrophe);                          m.attr("ImGuiKey_Apostrophe")                          = ImGuiKey::ImGuiKey_Apostrophe;
    e.value("ImGuiKey_Comma",                               ImGuiKey_Comma);                               m.attr("ImGuiKey_Comma")                               = ImGuiKey::ImGuiKey_Comma;
    e.value("ImGuiKey_Minus",                               ImGuiKey_Minus);                               m.attr("ImGuiKey_Minus")                               = ImGuiKey::ImGuiKey_Minus;
    e.value("ImGuiKey_Period",                              ImGuiKey_Period);                              m.attr("ImGuiKey_Period")                              = ImGuiKey::ImGuiKey_Period;
    e.value("ImGuiKey_Slash",                               ImGuiKey_Slash);                               m.attr("ImGuiKey_Slash")                               = ImGuiKey::ImGuiKey_Slash;
    e.value("ImGuiKey_Semicolon",                           ImGuiKey_Semicolon);                           m.attr("ImGuiKey_Semicolon")                           = ImGuiKey::ImGuiKey_Semicolon;
    e.value("ImGuiKey_Equal",                               ImGuiKey_Equal);                               m.attr("ImGuiKey_Equal")                               = ImGuiKey::ImGuiKey_Equal;
    e.value("ImGuiKey_LeftBracket",                         ImGuiKey_LeftBracket);                         m.attr("ImGuiKey_LeftBracket")                         = ImGuiKey::ImGuiKey_LeftBracket;
    e.value("ImGuiKey_Backslash",                           ImGuiKey_Backslash);                           m.attr("ImGuiKey_Backslash")                           = ImGuiKey::ImGuiKey_Backslash;
    e.value("ImGuiKey_RightBracket",                        ImGuiKey_RightBracket);                        m.attr("ImGuiKey_RightBracket")                        = ImGuiKey::ImGuiKey_RightBracket;
    e.value("ImGuiKey_GraveAccent",                         ImGuiKey_GraveAccent);                         m.attr("ImGuiKey_GraveAccent")                         = ImGuiKey::ImGuiKey_GraveAccent;
    e.value("ImGuiKey_CapsLock",                            ImGuiKey_CapsLock);                            m.attr("ImGuiKey_CapsLock")                            = ImGuiKey::ImGuiKey_CapsLock;
    e.value("ImGuiKey_ScrollLock",                          ImGuiKey_ScrollLock);                          m.attr("ImGuiKey_ScrollLock")                          = ImGuiKey::ImGuiKey_ScrollLock;
    e.value("ImGuiKey_NumLock",                             ImGuiKey_NumLock);                             m.attr("ImGuiKey_NumLock")                             = ImGuiKey::ImGuiKey_NumLock;
    e.value("ImGuiKey_PrintScreen",                         ImGuiKey_PrintScreen);                         m.attr("ImGuiKey_PrintScreen")                         = ImGuiKey::ImGuiKey_PrintScreen;
    e.value("ImGuiKey_Pause",                               ImGuiKey_Pause);                               m.attr("ImGuiKey_Pause")                               = ImGuiKey::ImGuiKey_Pause;
    e.value("ImGuiKey_Keypad0",                             ImGuiKey_Keypad0);                             m.attr("ImGuiKey_Keypad0")                             = ImGuiKey::ImGuiKey_Keypad0;
    e.value("ImGuiKey_Keypad1",                             ImGuiKey_Keypad1);                             m.attr("ImGuiKey_Keypad1")                             = ImGuiKey::ImGuiKey_Keypad1;
    e.value("ImGuiKey_Keypad2",                             ImGuiKey_Keypad2);                             m.attr("ImGuiKey_Keypad2")                             = ImGuiKey::ImGuiKey_Keypad2;
    e.value("ImGuiKey_Keypad3",                             ImGuiKey_Keypad3);                             m.attr("ImGuiKey_Keypad3")                             = ImGuiKey::ImGuiKey_Keypad3;
    e.value("ImGuiKey_Keypad4",                             ImGuiKey_Keypad4);                             m.attr("ImGuiKey_Keypad4")                             = ImGuiKey::ImGuiKey_Keypad4;
    e.value("ImGuiKey_Keypad5",                             ImGuiKey_Keypad5);                             m.attr("ImGuiKey_Keypad5")                             = ImGuiKey::ImGuiKey_Keypad5;
    e.value("ImGuiKey_Keypad6",                             ImGuiKey_Keypad6);                             m.attr("ImGuiKey_Keypad6")                             = ImGuiKey::ImGuiKey_Keypad6;
    e.value("ImGuiKey_Keypad7",                             ImGuiKey_Keypad7);                             m.attr("ImGuiKey_Keypad7")                             = ImGuiKey::ImGuiKey_Keypad7;
    e.value("ImGuiKey_Keypad8",                             ImGuiKey_Keypad8);                             m.attr("ImGuiKey_Keypad8")                             = ImGuiKey::ImGuiKey_Keypad8;
    e.value("ImGuiKey_Keypad9",                             ImGuiKey_Keypad9);                             m.attr("ImGuiKey_Keypad9")                             = ImGuiKey::ImGuiKey_Keypad9;
    e.value("ImGuiKey_KeypadDecimal",                       ImGuiKey_KeypadDecimal);                       m.attr("ImGuiKey_KeypadDecimal")                       = ImGuiKey::ImGuiKey_KeypadDecimal;
    e.value("ImGuiKey_KeypadDivide",                        ImGuiKey_KeypadDivide);                        m.attr("ImGuiKey_KeypadDivide")                        = ImGuiKey::ImGuiKey_KeypadDivide;
    e.value("ImGuiKey_KeypadMultiply",                      ImGuiKey_KeypadMultiply);                      m.attr("ImGuiKey_KeypadMultiply")                      = ImGuiKey::ImGuiKey_KeypadMultiply;
    e.value("ImGuiKey_KeypadSubtract",                      ImGuiKey_KeypadSubtract);                      m.attr("ImGuiKey_KeypadSubtract")                      = ImGuiKey::ImGuiKey_KeypadSubtract;
    e.value("ImGuiKey_KeypadAdd",                           ImGuiKey_KeypadAdd);                           m.attr("ImGuiKey_KeypadAdd")                           = ImGuiKey::ImGuiKey_KeypadAdd;
    e.value("ImGuiKey_KeypadEnter",                         ImGuiKey_KeypadEnter);                         m.attr("ImGuiKey_KeypadEnter")                         = ImGuiKey::ImGuiKey_KeypadEnter;
    e.value("ImGuiKey_KeypadEqual",                         ImGuiKey_KeypadEqual);                         m.attr("ImGuiKey_KeypadEqual")                         = ImGuiKey::ImGuiKey_KeypadEqual;
    e.value("ImGuiKey_AppBack",                             ImGuiKey_AppBack);                             m.attr("ImGuiKey_AppBack")                             = ImGuiKey::ImGuiKey_AppBack;
    e.value("ImGuiKey_AppForward",                          ImGuiKey_AppForward);                          m.attr("ImGuiKey_AppForward")                          = ImGuiKey::ImGuiKey_AppForward;
    e.value("ImGuiKey_Oem102",                              ImGuiKey_Oem102);                              m.attr("ImGuiKey_Oem102")                              = ImGuiKey::ImGuiKey_Oem102;
    e.value("ImGuiKey_GamepadStart",                        ImGuiKey_GamepadStart);                        m.attr("ImGuiKey_GamepadStart")                        = ImGuiKey::ImGuiKey_GamepadStart;
    e.value("ImGuiKey_GamepadBack",                         ImGuiKey_GamepadBack);                         m.attr("ImGuiKey_GamepadBack")                         = ImGuiKey::ImGuiKey_GamepadBack;
    e.value("ImGuiKey_GamepadFaceLeft",                     ImGuiKey_GamepadFaceLeft);                     m.attr("ImGuiKey_GamepadFaceLeft")                     = ImGuiKey::ImGuiKey_GamepadFaceLeft;
    e.value("ImGuiKey_GamepadFaceRight",                    ImGuiKey_GamepadFaceRight);                    m.attr("ImGuiKey_GamepadFaceRight")                    = ImGuiKey::ImGuiKey_GamepadFaceRight;
    e.value("ImGuiKey_GamepadFaceUp",                       ImGuiKey_GamepadFaceUp);                       m.attr("ImGuiKey_GamepadFaceUp")                       = ImGuiKey::ImGuiKey_GamepadFaceUp;
    e.value("ImGuiKey_GamepadFaceDown",                     ImGuiKey_GamepadFaceDown);                     m.attr("ImGuiKey_GamepadFaceDown")                     = ImGuiKey::ImGuiKey_GamepadFaceDown;
    e.value("ImGuiKey_GamepadDpadLeft",                     ImGuiKey_GamepadDpadLeft);                     m.attr("ImGuiKey_GamepadDpadLeft")                     = ImGuiKey::ImGuiKey_GamepadDpadLeft;
    e.value("ImGuiKey_GamepadDpadRight",                    ImGuiKey_GamepadDpadRight);                    m.attr("ImGuiKey_GamepadDpadRight")                    = ImGuiKey::ImGuiKey_GamepadDpadRight;
    e.value("ImGuiKey_GamepadDpadUp",                       ImGuiKey_GamepadDpadUp);                       m.attr("ImGuiKey_GamepadDpadUp")                       = ImGuiKey::ImGuiKey_GamepadDpadUp;
    e.value("ImGuiKey_GamepadDpadDown",                     ImGuiKey_GamepadDpadDown);                     m.attr("ImGuiKey_GamepadDpadDown")                     = ImGuiKey::ImGuiKey_GamepadDpadDown;
    e.value("ImGuiKey_GamepadL1",                           ImGuiKey_GamepadL1);                           m.attr("ImGuiKey_GamepadL1")                           = ImGuiKey::ImGuiKey_GamepadL1;
    e.value("ImGuiKey_GamepadR1",                           ImGuiKey_GamepadR1);                           m.attr("ImGuiKey_GamepadR1")                           = ImGuiKey::ImGuiKey_GamepadR1;
    e.value("ImGuiKey_GamepadL2",                           ImGuiKey_GamepadL2);                           m.attr("ImGuiKey_GamepadL2")                           = ImGuiKey::ImGuiKey_GamepadL2;
    e.value("ImGuiKey_GamepadR2",                           ImGuiKey_GamepadR2);                           m.attr("ImGuiKey_GamepadR2")                           = ImGuiKey::ImGuiKey_GamepadR2;
    e.value("ImGuiKey_GamepadL3",                           ImGuiKey_GamepadL3);                           m.attr("ImGuiKey_GamepadL3")                           = ImGuiKey::ImGuiKey_GamepadL3;
    e.value("ImGuiKey_GamepadR3",                           ImGuiKey_GamepadR3);                           m.attr("ImGuiKey_GamepadR3")                           = ImGuiKey::ImGuiKey_GamepadR3;
    e.value("ImGuiKey_GamepadLStickLeft",                   ImGuiKey_GamepadLStickLeft);                   m.attr("ImGuiKey_GamepadLStickLeft")                   = ImGuiKey::ImGuiKey_GamepadLStickLeft;
    e.value("ImGuiKey_GamepadLStickRight",                  ImGuiKey_GamepadLStickRight);                  m.attr("ImGuiKey_GamepadLStickRight")                  = ImGuiKey::ImGuiKey_GamepadLStickRight;
    e.value("ImGuiKey_GamepadLStickUp",                     ImGuiKey_GamepadLStickUp);                     m.attr("ImGuiKey_GamepadLStickUp")                     = ImGuiKey::ImGuiKey_GamepadLStickUp;
    e.value("ImGuiKey_GamepadLStickDown",                   ImGuiKey_GamepadLStickDown);                   m.attr("ImGuiKey_GamepadLStickDown")                   = ImGuiKey::ImGuiKey_GamepadLStickDown;
    e.value("ImGuiKey_GamepadRStickLeft",                   ImGuiKey_GamepadRStickLeft);                   m.attr("ImGuiKey_GamepadRStickLeft")                   = ImGuiKey::ImGuiKey_GamepadRStickLeft;
    e.value("ImGuiKey_GamepadRStickRight",                  ImGuiKey_GamepadRStickRight);                  m.attr("ImGuiKey_GamepadRStickRight")                  = ImGuiKey::ImGuiKey_GamepadRStickRight;
    e.value("ImGuiKey_GamepadRStickUp",                     ImGuiKey_GamepadRStickUp);                     m.attr("ImGuiKey_GamepadRStickUp")                     = ImGuiKey::ImGuiKey_GamepadRStickUp;
    e.value("ImGuiKey_GamepadRStickDown",                   ImGuiKey_GamepadRStickDown);                   m.attr("ImGuiKey_GamepadRStickDown")                   = ImGuiKey::ImGuiKey_GamepadRStickDown;
    e.value("ImGuiKey_MouseLeft",                           ImGuiKey_MouseLeft);                           m.attr("ImGuiKey_MouseLeft")                           = ImGuiKey::ImGuiKey_MouseLeft;
    e.value("ImGuiKey_MouseRight",                          ImGuiKey_MouseRight);                          m.attr("ImGuiKey_MouseRight")                          = ImGuiKey::ImGuiKey_MouseRight;
    e.value("ImGuiKey_MouseMiddle",                         ImGuiKey_MouseMiddle);                         m.attr("ImGuiKey_MouseMiddle")                         = ImGuiKey::ImGuiKey_MouseMiddle;
    e.value("ImGuiKey_MouseX1",                             ImGuiKey_MouseX1);                             m.attr("ImGuiKey_MouseX1")                             = ImGuiKey::ImGuiKey_MouseX1;
    e.value("ImGuiKey_MouseX2",                             ImGuiKey_MouseX2);                             m.attr("ImGuiKey_MouseX2")                             = ImGuiKey::ImGuiKey_MouseX2;
    e.value("ImGuiKey_MouseWheelX",                         ImGuiKey_MouseWheelX);                         m.attr("ImGuiKey_MouseWheelX")                         = ImGuiKey::ImGuiKey_MouseWheelX;
    e.value("ImGuiKey_MouseWheelY",                         ImGuiKey_MouseWheelY);                         m.attr("ImGuiKey_MouseWheelY")                         = ImGuiKey::ImGuiKey_MouseWheelY;
    e.value("ImGuiKey_ReservedForModCtrl",                  ImGuiKey_ReservedForModCtrl);                  m.attr("ImGuiKey_ReservedForModCtrl")                  = ImGuiKey::ImGuiKey_ReservedForModCtrl;
    e.value("ImGuiKey_ReservedForModShift",                 ImGuiKey_ReservedForModShift);                 m.attr("ImGuiKey_ReservedForModShift")                 = ImGuiKey::ImGuiKey_ReservedForModShift;
    e.value("ImGuiKey_ReservedForModAlt",                   ImGuiKey_ReservedForModAlt);                   m.attr("ImGuiKey_ReservedForModAlt")                   = ImGuiKey::ImGuiKey_ReservedForModAlt;
    e.value("ImGuiKey_ReservedForModSuper",                 ImGuiKey_ReservedForModSuper);                 m.attr("ImGuiKey_ReservedForModSuper")                 = ImGuiKey::ImGuiKey_ReservedForModSuper;
    e.value("ImGuiKey_NamedKey_END",                        ImGuiKey_NamedKey_END);                        m.attr("ImGuiKey_NamedKey_END")                        = ImGuiKey::ImGuiKey_NamedKey_END;
    e.value("ImGuiKey_NamedKey_COUNT",                      ImGuiKey_NamedKey_COUNT);                      m.attr("ImGuiKey_NamedKey_COUNT")                      = ImGuiKey::ImGuiKey_NamedKey_COUNT;
    e.value("ImGuiMod_None",                                ImGuiMod_None);                                m.attr("ImGuiMod_None")                                = ImGuiKey::ImGuiMod_None;
    e.value("ImGuiMod_Ctrl",                                ImGuiMod_Ctrl);                                m.attr("ImGuiMod_Ctrl")                                = ImGuiKey::ImGuiMod_Ctrl;
    e.value("ImGuiMod_Shift",                               ImGuiMod_Shift);                               m.attr("ImGuiMod_Shift")                               = ImGuiKey::ImGuiMod_Shift;
    e.value("ImGuiMod_Alt",                                 ImGuiMod_Alt);                                 m.attr("ImGuiMod_Alt")                                 = ImGuiKey::ImGuiMod_Alt;
    e.value("ImGuiMod_Super",                               ImGuiMod_Super);                               m.attr("ImGuiMod_Super")                               = ImGuiKey::ImGuiMod_Super;
    e.value("ImGuiMod_Mask_",                               ImGuiMod_Mask_);                               m.attr("ImGuiMod_Mask_")                               = ImGuiKey::ImGuiMod_Mask_;
    e.value("ImGuiKey_COUNT",                               ImGuiKey_COUNT);                               m.attr("ImGuiKey_COUNT")                               = ImGuiKey::ImGuiKey_COUNT;
    e.value("ImGuiMod_Shortcut",                            ImGuiMod_Shortcut);                            m.attr("ImGuiMod_Shortcut")                            = ImGuiKey::ImGuiMod_Shortcut;
  ;
  }

  { // ImGuiInputFlags_
  auto e = nb::enum_<ImGuiInputFlags_>(m, "ImGuiInputFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiInputFlags_None",                         ImGuiInputFlags_None);                         m.attr("ImGuiInputFlags_None")                         = ImGuiInputFlags_::ImGuiInputFlags_None;
    e.value("ImGuiInputFlags_Repeat",                       ImGuiInputFlags_Repeat);                       m.attr("ImGuiInputFlags_Repeat")                       = ImGuiInputFlags_::ImGuiInputFlags_Repeat;
    e.value("ImGuiInputFlags_RouteActive",                  ImGuiInputFlags_RouteActive);                  m.attr("ImGuiInputFlags_RouteActive")                  = ImGuiInputFlags_::ImGuiInputFlags_RouteActive;
    e.value("ImGuiInputFlags_RouteFocused",                 ImGuiInputFlags_RouteFocused);                 m.attr("ImGuiInputFlags_RouteFocused")                 = ImGuiInputFlags_::ImGuiInputFlags_RouteFocused;
    e.value("ImGuiInputFlags_RouteGlobal",                  ImGuiInputFlags_RouteGlobal);                  m.attr("ImGuiInputFlags_RouteGlobal")                  = ImGuiInputFlags_::ImGuiInputFlags_RouteGlobal;
    e.value("ImGuiInputFlags_RouteAlways",                  ImGuiInputFlags_RouteAlways);                  m.attr("ImGuiInputFlags_RouteAlways")                  = ImGuiInputFlags_::ImGuiInputFlags_RouteAlways;
    e.value("ImGuiInputFlags_RouteOverFocused",             ImGuiInputFlags_RouteOverFocused);             m.attr("ImGuiInputFlags_RouteOverFocused")             = ImGuiInputFlags_::ImGuiInputFlags_RouteOverFocused;
    e.value("ImGuiInputFlags_RouteOverActive",              ImGuiInputFlags_RouteOverActive);              m.attr("ImGuiInputFlags_RouteOverActive")              = ImGuiInputFlags_::ImGuiInputFlags_RouteOverActive;
    e.value("ImGuiInputFlags_RouteUnlessBgFocused",         ImGuiInputFlags_RouteUnlessBgFocused);         m.attr("ImGuiInputFlags_RouteUnlessBgFocused")         = ImGuiInputFlags_::ImGuiInputFlags_RouteUnlessBgFocused;
    e.value("ImGuiInputFlags_RouteFromRootWindow",          ImGuiInputFlags_RouteFromRootWindow);          m.attr("ImGuiInputFlags_RouteFromRootWindow")          = ImGuiInputFlags_::ImGuiInputFlags_RouteFromRootWindow;
    e.value("ImGuiInputFlags_Tooltip",                      ImGuiInputFlags_Tooltip);                      m.attr("ImGuiInputFlags_Tooltip")                      = ImGuiInputFlags_::ImGuiInputFlags_Tooltip;
  ;
  }

  { // ImGuiConfigFlags_
  auto e = nb::enum_<ImGuiConfigFlags_>(m, "ImGuiConfigFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiConfigFlags_None",                        ImGuiConfigFlags_None);                        m.attr("ImGuiConfigFlags_None")                        = ImGuiConfigFlags_::ImGuiConfigFlags_None;
    e.value("ImGuiConfigFlags_NavEnableKeyboard",           ImGuiConfigFlags_NavEnableKeyboard);           m.attr("ImGuiConfigFlags_NavEnableKeyboard")           = ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableKeyboard;
    e.value("ImGuiConfigFlags_NavEnableGamepad",            ImGuiConfigFlags_NavEnableGamepad);            m.attr("ImGuiConfigFlags_NavEnableGamepad")            = ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableGamepad;
    e.value("ImGuiConfigFlags_NoMouse",                     ImGuiConfigFlags_NoMouse);                     m.attr("ImGuiConfigFlags_NoMouse")                     = ImGuiConfigFlags_::ImGuiConfigFlags_NoMouse;
    e.value("ImGuiConfigFlags_NoMouseCursorChange",         ImGuiConfigFlags_NoMouseCursorChange);         m.attr("ImGuiConfigFlags_NoMouseCursorChange")         = ImGuiConfigFlags_::ImGuiConfigFlags_NoMouseCursorChange;
    e.value("ImGuiConfigFlags_NoKeyboard",                  ImGuiConfigFlags_NoKeyboard);                  m.attr("ImGuiConfigFlags_NoKeyboard")                  = ImGuiConfigFlags_::ImGuiConfigFlags_NoKeyboard;
    e.value("ImGuiConfigFlags_IsSRGB",                      ImGuiConfigFlags_IsSRGB);                      m.attr("ImGuiConfigFlags_IsSRGB")                      = ImGuiConfigFlags_::ImGuiConfigFlags_IsSRGB;
    e.value("ImGuiConfigFlags_IsTouchScreen",               ImGuiConfigFlags_IsTouchScreen);               m.attr("ImGuiConfigFlags_IsTouchScreen")               = ImGuiConfigFlags_::ImGuiConfigFlags_IsTouchScreen;
    e.value("ImGuiConfigFlags_NavEnableSetMousePos",        ImGuiConfigFlags_NavEnableSetMousePos);        m.attr("ImGuiConfigFlags_NavEnableSetMousePos")        = ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableSetMousePos;
    e.value("ImGuiConfigFlags_NavNoCaptureKeyboard",        ImGuiConfigFlags_NavNoCaptureKeyboard);        m.attr("ImGuiConfigFlags_NavNoCaptureKeyboard")        = ImGuiConfigFlags_::ImGuiConfigFlags_NavNoCaptureKeyboard;
  ;
  }

  { // ImGuiBackendFlags_
  auto e = nb::enum_<ImGuiBackendFlags_>(m, "ImGuiBackendFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiBackendFlags_None",                       ImGuiBackendFlags_None);                       m.attr("ImGuiBackendFlags_None")                       = ImGuiBackendFlags_::ImGuiBackendFlags_None;
    e.value("ImGuiBackendFlags_HasGamepad",                 ImGuiBackendFlags_HasGamepad);                 m.attr("ImGuiBackendFlags_HasGamepad")                 = ImGuiBackendFlags_::ImGuiBackendFlags_HasGamepad;
    e.value("ImGuiBackendFlags_HasMouseCursors",            ImGuiBackendFlags_HasMouseCursors);            m.attr("ImGuiBackendFlags_HasMouseCursors")            = ImGuiBackendFlags_::ImGuiBackendFlags_HasMouseCursors;
    e.value("ImGuiBackendFlags_HasSetMousePos",             ImGuiBackendFlags_HasSetMousePos);             m.attr("ImGuiBackendFlags_HasSetMousePos")             = ImGuiBackendFlags_::ImGuiBackendFlags_HasSetMousePos;
    e.value("ImGuiBackendFlags_RendererHasVtxOffset",       ImGuiBackendFlags_RendererHasVtxOffset);       m.attr("ImGuiBackendFlags_RendererHasVtxOffset")       = ImGuiBackendFlags_::ImGuiBackendFlags_RendererHasVtxOffset;
    e.value("ImGuiBackendFlags_RendererHasTextures",        ImGuiBackendFlags_RendererHasTextures);        m.attr("ImGuiBackendFlags_RendererHasTextures")        = ImGuiBackendFlags_::ImGuiBackendFlags_RendererHasTextures;
  ;
  }

  { // ImGuiCol_
  auto e = nb::enum_<ImGuiCol_>(m, "ImGuiCol_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiCol_Text",                                ImGuiCol_Text);                                m.attr("ImGuiCol_Text")                                = ImGuiCol_::ImGuiCol_Text;
    e.value("ImGuiCol_TextDisabled",                        ImGuiCol_TextDisabled);                        m.attr("ImGuiCol_TextDisabled")                        = ImGuiCol_::ImGuiCol_TextDisabled;
    e.value("ImGuiCol_WindowBg",                            ImGuiCol_WindowBg);                            m.attr("ImGuiCol_WindowBg")                            = ImGuiCol_::ImGuiCol_WindowBg;
    e.value("ImGuiCol_ChildBg",                             ImGuiCol_ChildBg);                             m.attr("ImGuiCol_ChildBg")                             = ImGuiCol_::ImGuiCol_ChildBg;
    e.value("ImGuiCol_PopupBg",                             ImGuiCol_PopupBg);                             m.attr("ImGuiCol_PopupBg")                             = ImGuiCol_::ImGuiCol_PopupBg;
    e.value("ImGuiCol_Border",                              ImGuiCol_Border);                              m.attr("ImGuiCol_Border")                              = ImGuiCol_::ImGuiCol_Border;
    e.value("ImGuiCol_BorderShadow",                        ImGuiCol_BorderShadow);                        m.attr("ImGuiCol_BorderShadow")                        = ImGuiCol_::ImGuiCol_BorderShadow;
    e.value("ImGuiCol_FrameBg",                             ImGuiCol_FrameBg);                             m.attr("ImGuiCol_FrameBg")                             = ImGuiCol_::ImGuiCol_FrameBg;
    e.value("ImGuiCol_FrameBgHovered",                      ImGuiCol_FrameBgHovered);                      m.attr("ImGuiCol_FrameBgHovered")                      = ImGuiCol_::ImGuiCol_FrameBgHovered;
    e.value("ImGuiCol_FrameBgActive",                       ImGuiCol_FrameBgActive);                       m.attr("ImGuiCol_FrameBgActive")                       = ImGuiCol_::ImGuiCol_FrameBgActive;
    e.value("ImGuiCol_TitleBg",                             ImGuiCol_TitleBg);                             m.attr("ImGuiCol_TitleBg")                             = ImGuiCol_::ImGuiCol_TitleBg;
    e.value("ImGuiCol_TitleBgActive",                       ImGuiCol_TitleBgActive);                       m.attr("ImGuiCol_TitleBgActive")                       = ImGuiCol_::ImGuiCol_TitleBgActive;
    e.value("ImGuiCol_TitleBgCollapsed",                    ImGuiCol_TitleBgCollapsed);                    m.attr("ImGuiCol_TitleBgCollapsed")                    = ImGuiCol_::ImGuiCol_TitleBgCollapsed;
    e.value("ImGuiCol_MenuBarBg",                           ImGuiCol_MenuBarBg);                           m.attr("ImGuiCol_MenuBarBg")                           = ImGuiCol_::ImGuiCol_MenuBarBg;
    e.value("ImGuiCol_ScrollbarBg",                         ImGuiCol_ScrollbarBg);                         m.attr("ImGuiCol_ScrollbarBg")                         = ImGuiCol_::ImGuiCol_ScrollbarBg;
    e.value("ImGuiCol_ScrollbarGrab",                       ImGuiCol_ScrollbarGrab);                       m.attr("ImGuiCol_ScrollbarGrab")                       = ImGuiCol_::ImGuiCol_ScrollbarGrab;
    e.value("ImGuiCol_ScrollbarGrabHovered",                ImGuiCol_ScrollbarGrabHovered);                m.attr("ImGuiCol_ScrollbarGrabHovered")                = ImGuiCol_::ImGuiCol_ScrollbarGrabHovered;
    e.value("ImGuiCol_ScrollbarGrabActive",                 ImGuiCol_ScrollbarGrabActive);                 m.attr("ImGuiCol_ScrollbarGrabActive")                 = ImGuiCol_::ImGuiCol_ScrollbarGrabActive;
    e.value("ImGuiCol_CheckMark",                           ImGuiCol_CheckMark);                           m.attr("ImGuiCol_CheckMark")                           = ImGuiCol_::ImGuiCol_CheckMark;
    e.value("ImGuiCol_SliderGrab",                          ImGuiCol_SliderGrab);                          m.attr("ImGuiCol_SliderGrab")                          = ImGuiCol_::ImGuiCol_SliderGrab;
    e.value("ImGuiCol_SliderGrabActive",                    ImGuiCol_SliderGrabActive);                    m.attr("ImGuiCol_SliderGrabActive")                    = ImGuiCol_::ImGuiCol_SliderGrabActive;
    e.value("ImGuiCol_Button",                              ImGuiCol_Button);                              m.attr("ImGuiCol_Button")                              = ImGuiCol_::ImGuiCol_Button;
    e.value("ImGuiCol_ButtonHovered",                       ImGuiCol_ButtonHovered);                       m.attr("ImGuiCol_ButtonHovered")                       = ImGuiCol_::ImGuiCol_ButtonHovered;
    e.value("ImGuiCol_ButtonActive",                        ImGuiCol_ButtonActive);                        m.attr("ImGuiCol_ButtonActive")                        = ImGuiCol_::ImGuiCol_ButtonActive;
    e.value("ImGuiCol_Header",                              ImGuiCol_Header);                              m.attr("ImGuiCol_Header")                              = ImGuiCol_::ImGuiCol_Header;
    e.value("ImGuiCol_HeaderHovered",                       ImGuiCol_HeaderHovered);                       m.attr("ImGuiCol_HeaderHovered")                       = ImGuiCol_::ImGuiCol_HeaderHovered;
    e.value("ImGuiCol_HeaderActive",                        ImGuiCol_HeaderActive);                        m.attr("ImGuiCol_HeaderActive")                        = ImGuiCol_::ImGuiCol_HeaderActive;
    e.value("ImGuiCol_Separator",                           ImGuiCol_Separator);                           m.attr("ImGuiCol_Separator")                           = ImGuiCol_::ImGuiCol_Separator;
    e.value("ImGuiCol_SeparatorHovered",                    ImGuiCol_SeparatorHovered);                    m.attr("ImGuiCol_SeparatorHovered")                    = ImGuiCol_::ImGuiCol_SeparatorHovered;
    e.value("ImGuiCol_SeparatorActive",                     ImGuiCol_SeparatorActive);                     m.attr("ImGuiCol_SeparatorActive")                     = ImGuiCol_::ImGuiCol_SeparatorActive;
    e.value("ImGuiCol_ResizeGrip",                          ImGuiCol_ResizeGrip);                          m.attr("ImGuiCol_ResizeGrip")                          = ImGuiCol_::ImGuiCol_ResizeGrip;
    e.value("ImGuiCol_ResizeGripHovered",                   ImGuiCol_ResizeGripHovered);                   m.attr("ImGuiCol_ResizeGripHovered")                   = ImGuiCol_::ImGuiCol_ResizeGripHovered;
    e.value("ImGuiCol_ResizeGripActive",                    ImGuiCol_ResizeGripActive);                    m.attr("ImGuiCol_ResizeGripActive")                    = ImGuiCol_::ImGuiCol_ResizeGripActive;
    e.value("ImGuiCol_InputTextCursor",                     ImGuiCol_InputTextCursor);                     m.attr("ImGuiCol_InputTextCursor")                     = ImGuiCol_::ImGuiCol_InputTextCursor;
    e.value("ImGuiCol_TabHovered",                          ImGuiCol_TabHovered);                          m.attr("ImGuiCol_TabHovered")                          = ImGuiCol_::ImGuiCol_TabHovered;
    e.value("ImGuiCol_Tab",                                 ImGuiCol_Tab);                                 m.attr("ImGuiCol_Tab")                                 = ImGuiCol_::ImGuiCol_Tab;
    e.value("ImGuiCol_TabSelected",                         ImGuiCol_TabSelected);                         m.attr("ImGuiCol_TabSelected")                         = ImGuiCol_::ImGuiCol_TabSelected;
    e.value("ImGuiCol_TabSelectedOverline",                 ImGuiCol_TabSelectedOverline);                 m.attr("ImGuiCol_TabSelectedOverline")                 = ImGuiCol_::ImGuiCol_TabSelectedOverline;
    e.value("ImGuiCol_TabDimmed",                           ImGuiCol_TabDimmed);                           m.attr("ImGuiCol_TabDimmed")                           = ImGuiCol_::ImGuiCol_TabDimmed;
    e.value("ImGuiCol_TabDimmedSelected",                   ImGuiCol_TabDimmedSelected);                   m.attr("ImGuiCol_TabDimmedSelected")                   = ImGuiCol_::ImGuiCol_TabDimmedSelected;
    e.value("ImGuiCol_TabDimmedSelectedOverline",           ImGuiCol_TabDimmedSelectedOverline);           m.attr("ImGuiCol_TabDimmedSelectedOverline")           = ImGuiCol_::ImGuiCol_TabDimmedSelectedOverline;
    e.value("ImGuiCol_PlotLines",                           ImGuiCol_PlotLines);                           m.attr("ImGuiCol_PlotLines")                           = ImGuiCol_::ImGuiCol_PlotLines;
    e.value("ImGuiCol_PlotLinesHovered",                    ImGuiCol_PlotLinesHovered);                    m.attr("ImGuiCol_PlotLinesHovered")                    = ImGuiCol_::ImGuiCol_PlotLinesHovered;
    e.value("ImGuiCol_PlotHistogram",                       ImGuiCol_PlotHistogram);                       m.attr("ImGuiCol_PlotHistogram")                       = ImGuiCol_::ImGuiCol_PlotHistogram;
    e.value("ImGuiCol_PlotHistogramHovered",                ImGuiCol_PlotHistogramHovered);                m.attr("ImGuiCol_PlotHistogramHovered")                = ImGuiCol_::ImGuiCol_PlotHistogramHovered;
    e.value("ImGuiCol_TableHeaderBg",                       ImGuiCol_TableHeaderBg);                       m.attr("ImGuiCol_TableHeaderBg")                       = ImGuiCol_::ImGuiCol_TableHeaderBg;
    e.value("ImGuiCol_TableBorderStrong",                   ImGuiCol_TableBorderStrong);                   m.attr("ImGuiCol_TableBorderStrong")                   = ImGuiCol_::ImGuiCol_TableBorderStrong;
    e.value("ImGuiCol_TableBorderLight",                    ImGuiCol_TableBorderLight);                    m.attr("ImGuiCol_TableBorderLight")                    = ImGuiCol_::ImGuiCol_TableBorderLight;
    e.value("ImGuiCol_TableRowBg",                          ImGuiCol_TableRowBg);                          m.attr("ImGuiCol_TableRowBg")                          = ImGuiCol_::ImGuiCol_TableRowBg;
    e.value("ImGuiCol_TableRowBgAlt",                       ImGuiCol_TableRowBgAlt);                       m.attr("ImGuiCol_TableRowBgAlt")                       = ImGuiCol_::ImGuiCol_TableRowBgAlt;
    e.value("ImGuiCol_TextLink",                            ImGuiCol_TextLink);                            m.attr("ImGuiCol_TextLink")                            = ImGuiCol_::ImGuiCol_TextLink;
    e.value("ImGuiCol_TextSelectedBg",                      ImGuiCol_TextSelectedBg);                      m.attr("ImGuiCol_TextSelectedBg")                      = ImGuiCol_::ImGuiCol_TextSelectedBg;
    e.value("ImGuiCol_TreeLines",                           ImGuiCol_TreeLines);                           m.attr("ImGuiCol_TreeLines")                           = ImGuiCol_::ImGuiCol_TreeLines;
    e.value("ImGuiCol_DragDropTarget",                      ImGuiCol_DragDropTarget);                      m.attr("ImGuiCol_DragDropTarget")                      = ImGuiCol_::ImGuiCol_DragDropTarget;
    e.value("ImGuiCol_DragDropTargetBg",                    ImGuiCol_DragDropTargetBg);                    m.attr("ImGuiCol_DragDropTargetBg")                    = ImGuiCol_::ImGuiCol_DragDropTargetBg;
    e.value("ImGuiCol_UnsavedMarker",                       ImGuiCol_UnsavedMarker);                       m.attr("ImGuiCol_UnsavedMarker")                       = ImGuiCol_::ImGuiCol_UnsavedMarker;
    e.value("ImGuiCol_NavCursor",                           ImGuiCol_NavCursor);                           m.attr("ImGuiCol_NavCursor")                           = ImGuiCol_::ImGuiCol_NavCursor;
    e.value("ImGuiCol_NavWindowingHighlight",               ImGuiCol_NavWindowingHighlight);               m.attr("ImGuiCol_NavWindowingHighlight")               = ImGuiCol_::ImGuiCol_NavWindowingHighlight;
    e.value("ImGuiCol_NavWindowingDimBg",                   ImGuiCol_NavWindowingDimBg);                   m.attr("ImGuiCol_NavWindowingDimBg")                   = ImGuiCol_::ImGuiCol_NavWindowingDimBg;
    e.value("ImGuiCol_ModalWindowDimBg",                    ImGuiCol_ModalWindowDimBg);                    m.attr("ImGuiCol_ModalWindowDimBg")                    = ImGuiCol_::ImGuiCol_ModalWindowDimBg;
    e.value("ImGuiCol_COUNT",                               ImGuiCol_COUNT);                               m.attr("ImGuiCol_COUNT")                               = ImGuiCol_::ImGuiCol_COUNT;
    e.value("ImGuiCol_TabActive",                           ImGuiCol_TabActive);                           m.attr("ImGuiCol_TabActive")                           = ImGuiCol_::ImGuiCol_TabActive;
    e.value("ImGuiCol_TabUnfocused",                        ImGuiCol_TabUnfocused);                        m.attr("ImGuiCol_TabUnfocused")                        = ImGuiCol_::ImGuiCol_TabUnfocused;
    e.value("ImGuiCol_TabUnfocusedActive",                  ImGuiCol_TabUnfocusedActive);                  m.attr("ImGuiCol_TabUnfocusedActive")                  = ImGuiCol_::ImGuiCol_TabUnfocusedActive;
    e.value("ImGuiCol_NavHighlight",                        ImGuiCol_NavHighlight);                        m.attr("ImGuiCol_NavHighlight")                        = ImGuiCol_::ImGuiCol_NavHighlight;
  ;
  }

  { // ImGuiStyleVar_
  auto e = nb::enum_<ImGuiStyleVar_>(m, "ImGuiStyleVar_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiStyleVar_Alpha",                          ImGuiStyleVar_Alpha);                          m.attr("ImGuiStyleVar_Alpha")                          = ImGuiStyleVar_::ImGuiStyleVar_Alpha;
    e.value("ImGuiStyleVar_DisabledAlpha",                  ImGuiStyleVar_DisabledAlpha);                  m.attr("ImGuiStyleVar_DisabledAlpha")                  = ImGuiStyleVar_::ImGuiStyleVar_DisabledAlpha;
    e.value("ImGuiStyleVar_WindowPadding",                  ImGuiStyleVar_WindowPadding);                  m.attr("ImGuiStyleVar_WindowPadding")                  = ImGuiStyleVar_::ImGuiStyleVar_WindowPadding;
    e.value("ImGuiStyleVar_WindowRounding",                 ImGuiStyleVar_WindowRounding);                 m.attr("ImGuiStyleVar_WindowRounding")                 = ImGuiStyleVar_::ImGuiStyleVar_WindowRounding;
    e.value("ImGuiStyleVar_WindowBorderSize",               ImGuiStyleVar_WindowBorderSize);               m.attr("ImGuiStyleVar_WindowBorderSize")               = ImGuiStyleVar_::ImGuiStyleVar_WindowBorderSize;
    e.value("ImGuiStyleVar_WindowMinSize",                  ImGuiStyleVar_WindowMinSize);                  m.attr("ImGuiStyleVar_WindowMinSize")                  = ImGuiStyleVar_::ImGuiStyleVar_WindowMinSize;
    e.value("ImGuiStyleVar_WindowTitleAlign",               ImGuiStyleVar_WindowTitleAlign);               m.attr("ImGuiStyleVar_WindowTitleAlign")               = ImGuiStyleVar_::ImGuiStyleVar_WindowTitleAlign;
    e.value("ImGuiStyleVar_ChildRounding",                  ImGuiStyleVar_ChildRounding);                  m.attr("ImGuiStyleVar_ChildRounding")                  = ImGuiStyleVar_::ImGuiStyleVar_ChildRounding;
    e.value("ImGuiStyleVar_ChildBorderSize",                ImGuiStyleVar_ChildBorderSize);                m.attr("ImGuiStyleVar_ChildBorderSize")                = ImGuiStyleVar_::ImGuiStyleVar_ChildBorderSize;
    e.value("ImGuiStyleVar_PopupRounding",                  ImGuiStyleVar_PopupRounding);                  m.attr("ImGuiStyleVar_PopupRounding")                  = ImGuiStyleVar_::ImGuiStyleVar_PopupRounding;
    e.value("ImGuiStyleVar_PopupBorderSize",                ImGuiStyleVar_PopupBorderSize);                m.attr("ImGuiStyleVar_PopupBorderSize")                = ImGuiStyleVar_::ImGuiStyleVar_PopupBorderSize;
    e.value("ImGuiStyleVar_FramePadding",                   ImGuiStyleVar_FramePadding);                   m.attr("ImGuiStyleVar_FramePadding")                   = ImGuiStyleVar_::ImGuiStyleVar_FramePadding;
    e.value("ImGuiStyleVar_FrameRounding",                  ImGuiStyleVar_FrameRounding);                  m.attr("ImGuiStyleVar_FrameRounding")                  = ImGuiStyleVar_::ImGuiStyleVar_FrameRounding;
    e.value("ImGuiStyleVar_FrameBorderSize",                ImGuiStyleVar_FrameBorderSize);                m.attr("ImGuiStyleVar_FrameBorderSize")                = ImGuiStyleVar_::ImGuiStyleVar_FrameBorderSize;
    e.value("ImGuiStyleVar_ItemSpacing",                    ImGuiStyleVar_ItemSpacing);                    m.attr("ImGuiStyleVar_ItemSpacing")                    = ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing;
    e.value("ImGuiStyleVar_ItemInnerSpacing",               ImGuiStyleVar_ItemInnerSpacing);               m.attr("ImGuiStyleVar_ItemInnerSpacing")               = ImGuiStyleVar_::ImGuiStyleVar_ItemInnerSpacing;
    e.value("ImGuiStyleVar_IndentSpacing",                  ImGuiStyleVar_IndentSpacing);                  m.attr("ImGuiStyleVar_IndentSpacing")                  = ImGuiStyleVar_::ImGuiStyleVar_IndentSpacing;
    e.value("ImGuiStyleVar_CellPadding",                    ImGuiStyleVar_CellPadding);                    m.attr("ImGuiStyleVar_CellPadding")                    = ImGuiStyleVar_::ImGuiStyleVar_CellPadding;
    e.value("ImGuiStyleVar_ScrollbarSize",                  ImGuiStyleVar_ScrollbarSize);                  m.attr("ImGuiStyleVar_ScrollbarSize")                  = ImGuiStyleVar_::ImGuiStyleVar_ScrollbarSize;
    e.value("ImGuiStyleVar_ScrollbarRounding",              ImGuiStyleVar_ScrollbarRounding);              m.attr("ImGuiStyleVar_ScrollbarRounding")              = ImGuiStyleVar_::ImGuiStyleVar_ScrollbarRounding;
    e.value("ImGuiStyleVar_ScrollbarPadding",               ImGuiStyleVar_ScrollbarPadding);               m.attr("ImGuiStyleVar_ScrollbarPadding")               = ImGuiStyleVar_::ImGuiStyleVar_ScrollbarPadding;
    e.value("ImGuiStyleVar_GrabMinSize",                    ImGuiStyleVar_GrabMinSize);                    m.attr("ImGuiStyleVar_GrabMinSize")                    = ImGuiStyleVar_::ImGuiStyleVar_GrabMinSize;
    e.value("ImGuiStyleVar_GrabRounding",                   ImGuiStyleVar_GrabRounding);                   m.attr("ImGuiStyleVar_GrabRounding")                   = ImGuiStyleVar_::ImGuiStyleVar_GrabRounding;
    e.value("ImGuiStyleVar_ImageBorderSize",                ImGuiStyleVar_ImageBorderSize);                m.attr("ImGuiStyleVar_ImageBorderSize")                = ImGuiStyleVar_::ImGuiStyleVar_ImageBorderSize;
    e.value("ImGuiStyleVar_TabRounding",                    ImGuiStyleVar_TabRounding);                    m.attr("ImGuiStyleVar_TabRounding")                    = ImGuiStyleVar_::ImGuiStyleVar_TabRounding;
    e.value("ImGuiStyleVar_TabBorderSize",                  ImGuiStyleVar_TabBorderSize);                  m.attr("ImGuiStyleVar_TabBorderSize")                  = ImGuiStyleVar_::ImGuiStyleVar_TabBorderSize;
    e.value("ImGuiStyleVar_TabMinWidthBase",                ImGuiStyleVar_TabMinWidthBase);                m.attr("ImGuiStyleVar_TabMinWidthBase")                = ImGuiStyleVar_::ImGuiStyleVar_TabMinWidthBase;
    e.value("ImGuiStyleVar_TabMinWidthShrink",              ImGuiStyleVar_TabMinWidthShrink);              m.attr("ImGuiStyleVar_TabMinWidthShrink")              = ImGuiStyleVar_::ImGuiStyleVar_TabMinWidthShrink;
    e.value("ImGuiStyleVar_TabBarBorderSize",               ImGuiStyleVar_TabBarBorderSize);               m.attr("ImGuiStyleVar_TabBarBorderSize")               = ImGuiStyleVar_::ImGuiStyleVar_TabBarBorderSize;
    e.value("ImGuiStyleVar_TabBarOverlineSize",             ImGuiStyleVar_TabBarOverlineSize);             m.attr("ImGuiStyleVar_TabBarOverlineSize")             = ImGuiStyleVar_::ImGuiStyleVar_TabBarOverlineSize;
    e.value("ImGuiStyleVar_TableAngledHeadersAngle",        ImGuiStyleVar_TableAngledHeadersAngle);        m.attr("ImGuiStyleVar_TableAngledHeadersAngle")        = ImGuiStyleVar_::ImGuiStyleVar_TableAngledHeadersAngle;
    e.value("ImGuiStyleVar_TableAngledHeadersTextAlign",    ImGuiStyleVar_TableAngledHeadersTextAlign);    m.attr("ImGuiStyleVar_TableAngledHeadersTextAlign")    = ImGuiStyleVar_::ImGuiStyleVar_TableAngledHeadersTextAlign;
    e.value("ImGuiStyleVar_TreeLinesSize",                  ImGuiStyleVar_TreeLinesSize);                  m.attr("ImGuiStyleVar_TreeLinesSize")                  = ImGuiStyleVar_::ImGuiStyleVar_TreeLinesSize;
    e.value("ImGuiStyleVar_TreeLinesRounding",              ImGuiStyleVar_TreeLinesRounding);              m.attr("ImGuiStyleVar_TreeLinesRounding")              = ImGuiStyleVar_::ImGuiStyleVar_TreeLinesRounding;
    e.value("ImGuiStyleVar_ButtonTextAlign",                ImGuiStyleVar_ButtonTextAlign);                m.attr("ImGuiStyleVar_ButtonTextAlign")                = ImGuiStyleVar_::ImGuiStyleVar_ButtonTextAlign;
    e.value("ImGuiStyleVar_SelectableTextAlign",            ImGuiStyleVar_SelectableTextAlign);            m.attr("ImGuiStyleVar_SelectableTextAlign")            = ImGuiStyleVar_::ImGuiStyleVar_SelectableTextAlign;
    e.value("ImGuiStyleVar_SeparatorTextBorderSize",        ImGuiStyleVar_SeparatorTextBorderSize);        m.attr("ImGuiStyleVar_SeparatorTextBorderSize")        = ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextBorderSize;
    e.value("ImGuiStyleVar_SeparatorTextAlign",             ImGuiStyleVar_SeparatorTextAlign);             m.attr("ImGuiStyleVar_SeparatorTextAlign")             = ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextAlign;
    e.value("ImGuiStyleVar_SeparatorTextPadding",           ImGuiStyleVar_SeparatorTextPadding);           m.attr("ImGuiStyleVar_SeparatorTextPadding")           = ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextPadding;
    e.value("ImGuiStyleVar_COUNT",                          ImGuiStyleVar_COUNT);                          m.attr("ImGuiStyleVar_COUNT")                          = ImGuiStyleVar_::ImGuiStyleVar_COUNT;
  ;
  }

  { // ImGuiButtonFlags_
  auto e = nb::enum_<ImGuiButtonFlags_>(m, "ImGuiButtonFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiButtonFlags_None",                        ImGuiButtonFlags_None);                        m.attr("ImGuiButtonFlags_None")                        = ImGuiButtonFlags_::ImGuiButtonFlags_None;
    e.value("ImGuiButtonFlags_MouseButtonLeft",             ImGuiButtonFlags_MouseButtonLeft);             m.attr("ImGuiButtonFlags_MouseButtonLeft")             = ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonLeft;
    e.value("ImGuiButtonFlags_MouseButtonRight",            ImGuiButtonFlags_MouseButtonRight);            m.attr("ImGuiButtonFlags_MouseButtonRight")            = ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonRight;
    e.value("ImGuiButtonFlags_MouseButtonMiddle",           ImGuiButtonFlags_MouseButtonMiddle);           m.attr("ImGuiButtonFlags_MouseButtonMiddle")           = ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonMiddle;
    e.value("ImGuiButtonFlags_MouseButtonMask_",            ImGuiButtonFlags_MouseButtonMask_);            m.attr("ImGuiButtonFlags_MouseButtonMask_")            = ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonMask_;
    e.value("ImGuiButtonFlags_EnableNav",                   ImGuiButtonFlags_EnableNav);                   m.attr("ImGuiButtonFlags_EnableNav")                   = ImGuiButtonFlags_::ImGuiButtonFlags_EnableNav;
  ;
  }

  { // ImGuiColorEditFlags_
  auto e = nb::enum_<ImGuiColorEditFlags_>(m, "ImGuiColorEditFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiColorEditFlags_None",                     ImGuiColorEditFlags_None);                     m.attr("ImGuiColorEditFlags_None")                     = ImGuiColorEditFlags_::ImGuiColorEditFlags_None;
    e.value("ImGuiColorEditFlags_NoAlpha",                  ImGuiColorEditFlags_NoAlpha);                  m.attr("ImGuiColorEditFlags_NoAlpha")                  = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoAlpha;
    e.value("ImGuiColorEditFlags_NoPicker",                 ImGuiColorEditFlags_NoPicker);                 m.attr("ImGuiColorEditFlags_NoPicker")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoPicker;
    e.value("ImGuiColorEditFlags_NoOptions",                ImGuiColorEditFlags_NoOptions);                m.attr("ImGuiColorEditFlags_NoOptions")                = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoOptions;
    e.value("ImGuiColorEditFlags_NoSmallPreview",           ImGuiColorEditFlags_NoSmallPreview);           m.attr("ImGuiColorEditFlags_NoSmallPreview")           = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoSmallPreview;
    e.value("ImGuiColorEditFlags_NoInputs",                 ImGuiColorEditFlags_NoInputs);                 m.attr("ImGuiColorEditFlags_NoInputs")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs;
    e.value("ImGuiColorEditFlags_NoTooltip",                ImGuiColorEditFlags_NoTooltip);                m.attr("ImGuiColorEditFlags_NoTooltip")                = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoTooltip;
    e.value("ImGuiColorEditFlags_NoLabel",                  ImGuiColorEditFlags_NoLabel);                  m.attr("ImGuiColorEditFlags_NoLabel")                  = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoLabel;
    e.value("ImGuiColorEditFlags_NoSidePreview",            ImGuiColorEditFlags_NoSidePreview);            m.attr("ImGuiColorEditFlags_NoSidePreview")            = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoSidePreview;
    e.value("ImGuiColorEditFlags_NoDragDrop",               ImGuiColorEditFlags_NoDragDrop);               m.attr("ImGuiColorEditFlags_NoDragDrop")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoDragDrop;
    e.value("ImGuiColorEditFlags_NoBorder",                 ImGuiColorEditFlags_NoBorder);                 m.attr("ImGuiColorEditFlags_NoBorder")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoBorder;
    e.value("ImGuiColorEditFlags_NoColorMarkers",           ImGuiColorEditFlags_NoColorMarkers);           m.attr("ImGuiColorEditFlags_NoColorMarkers")           = ImGuiColorEditFlags_::ImGuiColorEditFlags_NoColorMarkers;
    e.value("ImGuiColorEditFlags_AlphaOpaque",              ImGuiColorEditFlags_AlphaOpaque);              m.attr("ImGuiColorEditFlags_AlphaOpaque")              = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaOpaque;
    e.value("ImGuiColorEditFlags_AlphaNoBg",                ImGuiColorEditFlags_AlphaNoBg);                m.attr("ImGuiColorEditFlags_AlphaNoBg")                = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaNoBg;
    e.value("ImGuiColorEditFlags_AlphaPreviewHalf",         ImGuiColorEditFlags_AlphaPreviewHalf);         m.attr("ImGuiColorEditFlags_AlphaPreviewHalf")         = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf;
    e.value("ImGuiColorEditFlags_AlphaBar",                 ImGuiColorEditFlags_AlphaBar);                 m.attr("ImGuiColorEditFlags_AlphaBar")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar;
    e.value("ImGuiColorEditFlags_HDR",                      ImGuiColorEditFlags_HDR);                      m.attr("ImGuiColorEditFlags_HDR")                      = ImGuiColorEditFlags_::ImGuiColorEditFlags_HDR;
    e.value("ImGuiColorEditFlags_DisplayRGB",               ImGuiColorEditFlags_DisplayRGB);               m.attr("ImGuiColorEditFlags_DisplayRGB")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayRGB;
    e.value("ImGuiColorEditFlags_DisplayHSV",               ImGuiColorEditFlags_DisplayHSV);               m.attr("ImGuiColorEditFlags_DisplayHSV")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayHSV;
    e.value("ImGuiColorEditFlags_DisplayHex",               ImGuiColorEditFlags_DisplayHex);               m.attr("ImGuiColorEditFlags_DisplayHex")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayHex;
    e.value("ImGuiColorEditFlags_Uint8",                    ImGuiColorEditFlags_Uint8);                    m.attr("ImGuiColorEditFlags_Uint8")                    = ImGuiColorEditFlags_::ImGuiColorEditFlags_Uint8;
    e.value("ImGuiColorEditFlags_Float",                    ImGuiColorEditFlags_Float);                    m.attr("ImGuiColorEditFlags_Float")                    = ImGuiColorEditFlags_::ImGuiColorEditFlags_Float;
    e.value("ImGuiColorEditFlags_PickerHueBar",             ImGuiColorEditFlags_PickerHueBar);             m.attr("ImGuiColorEditFlags_PickerHueBar")             = ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueBar;
    e.value("ImGuiColorEditFlags_PickerHueWheel",           ImGuiColorEditFlags_PickerHueWheel);           m.attr("ImGuiColorEditFlags_PickerHueWheel")           = ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueWheel;
    e.value("ImGuiColorEditFlags_InputRGB",                 ImGuiColorEditFlags_InputRGB);                 m.attr("ImGuiColorEditFlags_InputRGB")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_InputRGB;
    e.value("ImGuiColorEditFlags_InputHSV",                 ImGuiColorEditFlags_InputHSV);                 m.attr("ImGuiColorEditFlags_InputHSV")                 = ImGuiColorEditFlags_::ImGuiColorEditFlags_InputHSV;
    e.value("ImGuiColorEditFlags_DefaultOptions_",          ImGuiColorEditFlags_DefaultOptions_);          m.attr("ImGuiColorEditFlags_DefaultOptions_")          = ImGuiColorEditFlags_::ImGuiColorEditFlags_DefaultOptions_;
    e.value("ImGuiColorEditFlags_AlphaMask_",               ImGuiColorEditFlags_AlphaMask_);               m.attr("ImGuiColorEditFlags_AlphaMask_")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaMask_;
    e.value("ImGuiColorEditFlags_DisplayMask_",             ImGuiColorEditFlags_DisplayMask_);             m.attr("ImGuiColorEditFlags_DisplayMask_")             = ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayMask_;
    e.value("ImGuiColorEditFlags_DataTypeMask_",            ImGuiColorEditFlags_DataTypeMask_);            m.attr("ImGuiColorEditFlags_DataTypeMask_")            = ImGuiColorEditFlags_::ImGuiColorEditFlags_DataTypeMask_;
    e.value("ImGuiColorEditFlags_PickerMask_",              ImGuiColorEditFlags_PickerMask_);              m.attr("ImGuiColorEditFlags_PickerMask_")              = ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerMask_;
    e.value("ImGuiColorEditFlags_InputMask_",               ImGuiColorEditFlags_InputMask_);               m.attr("ImGuiColorEditFlags_InputMask_")               = ImGuiColorEditFlags_::ImGuiColorEditFlags_InputMask_;
    e.value("ImGuiColorEditFlags_AlphaPreview",             ImGuiColorEditFlags_AlphaPreview);             m.attr("ImGuiColorEditFlags_AlphaPreview")             = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreview;
  ;
  }

  { // ImGuiSliderFlags_
  auto e = nb::enum_<ImGuiSliderFlags_>(m, "ImGuiSliderFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiSliderFlags_None",                        ImGuiSliderFlags_None);                        m.attr("ImGuiSliderFlags_None")                        = ImGuiSliderFlags_::ImGuiSliderFlags_None;
    e.value("ImGuiSliderFlags_Logarithmic",                 ImGuiSliderFlags_Logarithmic);                 m.attr("ImGuiSliderFlags_Logarithmic")                 = ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic;
    e.value("ImGuiSliderFlags_NoRoundToFormat",             ImGuiSliderFlags_NoRoundToFormat);             m.attr("ImGuiSliderFlags_NoRoundToFormat")             = ImGuiSliderFlags_::ImGuiSliderFlags_NoRoundToFormat;
    e.value("ImGuiSliderFlags_NoInput",                     ImGuiSliderFlags_NoInput);                     m.attr("ImGuiSliderFlags_NoInput")                     = ImGuiSliderFlags_::ImGuiSliderFlags_NoInput;
    e.value("ImGuiSliderFlags_WrapAround",                  ImGuiSliderFlags_WrapAround);                  m.attr("ImGuiSliderFlags_WrapAround")                  = ImGuiSliderFlags_::ImGuiSliderFlags_WrapAround;
    e.value("ImGuiSliderFlags_ClampOnInput",                ImGuiSliderFlags_ClampOnInput);                m.attr("ImGuiSliderFlags_ClampOnInput")                = ImGuiSliderFlags_::ImGuiSliderFlags_ClampOnInput;
    e.value("ImGuiSliderFlags_ClampZeroRange",              ImGuiSliderFlags_ClampZeroRange);              m.attr("ImGuiSliderFlags_ClampZeroRange")              = ImGuiSliderFlags_::ImGuiSliderFlags_ClampZeroRange;
    e.value("ImGuiSliderFlags_NoSpeedTweaks",               ImGuiSliderFlags_NoSpeedTweaks);               m.attr("ImGuiSliderFlags_NoSpeedTweaks")               = ImGuiSliderFlags_::ImGuiSliderFlags_NoSpeedTweaks;
    e.value("ImGuiSliderFlags_ColorMarkers",                ImGuiSliderFlags_ColorMarkers);                m.attr("ImGuiSliderFlags_ColorMarkers")                = ImGuiSliderFlags_::ImGuiSliderFlags_ColorMarkers;
    e.value("ImGuiSliderFlags_AlwaysClamp",                 ImGuiSliderFlags_AlwaysClamp);                 m.attr("ImGuiSliderFlags_AlwaysClamp")                 = ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp;
    e.value("ImGuiSliderFlags_InvalidMask_",                ImGuiSliderFlags_InvalidMask_);                m.attr("ImGuiSliderFlags_InvalidMask_")                = ImGuiSliderFlags_::ImGuiSliderFlags_InvalidMask_;
  ;
  }

  { // ImGuiMouseButton_
  auto e = nb::enum_<ImGuiMouseButton_>(m, "ImGuiMouseButton_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiMouseButton_Left",                        ImGuiMouseButton_Left);                        m.attr("ImGuiMouseButton_Left")                        = ImGuiMouseButton_::ImGuiMouseButton_Left;
    e.value("ImGuiMouseButton_Right",                       ImGuiMouseButton_Right);                       m.attr("ImGuiMouseButton_Right")                       = ImGuiMouseButton_::ImGuiMouseButton_Right;
    e.value("ImGuiMouseButton_Middle",                      ImGuiMouseButton_Middle);                      m.attr("ImGuiMouseButton_Middle")                      = ImGuiMouseButton_::ImGuiMouseButton_Middle;
    e.value("ImGuiMouseButton_COUNT",                       ImGuiMouseButton_COUNT);                       m.attr("ImGuiMouseButton_COUNT")                       = ImGuiMouseButton_::ImGuiMouseButton_COUNT;
  ;
  }

  { // ImGuiMouseCursor_
  auto e = nb::enum_<ImGuiMouseCursor_>(m, "ImGuiMouseCursor_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiMouseCursor_None",                        ImGuiMouseCursor_None);                        m.attr("ImGuiMouseCursor_None")                        = ImGuiMouseCursor_::ImGuiMouseCursor_None;
    e.value("ImGuiMouseCursor_Arrow",                       ImGuiMouseCursor_Arrow);                       m.attr("ImGuiMouseCursor_Arrow")                       = ImGuiMouseCursor_::ImGuiMouseCursor_Arrow;
    e.value("ImGuiMouseCursor_TextInput",                   ImGuiMouseCursor_TextInput);                   m.attr("ImGuiMouseCursor_TextInput")                   = ImGuiMouseCursor_::ImGuiMouseCursor_TextInput;
    e.value("ImGuiMouseCursor_ResizeAll",                   ImGuiMouseCursor_ResizeAll);                   m.attr("ImGuiMouseCursor_ResizeAll")                   = ImGuiMouseCursor_::ImGuiMouseCursor_ResizeAll;
    e.value("ImGuiMouseCursor_ResizeNS",                    ImGuiMouseCursor_ResizeNS);                    m.attr("ImGuiMouseCursor_ResizeNS")                    = ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNS;
    e.value("ImGuiMouseCursor_ResizeEW",                    ImGuiMouseCursor_ResizeEW);                    m.attr("ImGuiMouseCursor_ResizeEW")                    = ImGuiMouseCursor_::ImGuiMouseCursor_ResizeEW;
    e.value("ImGuiMouseCursor_ResizeNESW",                  ImGuiMouseCursor_ResizeNESW);                  m.attr("ImGuiMouseCursor_ResizeNESW")                  = ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNESW;
    e.value("ImGuiMouseCursor_ResizeNWSE",                  ImGuiMouseCursor_ResizeNWSE);                  m.attr("ImGuiMouseCursor_ResizeNWSE")                  = ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNWSE;
    e.value("ImGuiMouseCursor_Hand",                        ImGuiMouseCursor_Hand);                        m.attr("ImGuiMouseCursor_Hand")                        = ImGuiMouseCursor_::ImGuiMouseCursor_Hand;
    e.value("ImGuiMouseCursor_Wait",                        ImGuiMouseCursor_Wait);                        m.attr("ImGuiMouseCursor_Wait")                        = ImGuiMouseCursor_::ImGuiMouseCursor_Wait;
    e.value("ImGuiMouseCursor_Progress",                    ImGuiMouseCursor_Progress);                    m.attr("ImGuiMouseCursor_Progress")                    = ImGuiMouseCursor_::ImGuiMouseCursor_Progress;
    e.value("ImGuiMouseCursor_NotAllowed",                  ImGuiMouseCursor_NotAllowed);                  m.attr("ImGuiMouseCursor_NotAllowed")                  = ImGuiMouseCursor_::ImGuiMouseCursor_NotAllowed;
    e.value("ImGuiMouseCursor_COUNT",                       ImGuiMouseCursor_COUNT);                       m.attr("ImGuiMouseCursor_COUNT")                       = ImGuiMouseCursor_::ImGuiMouseCursor_COUNT;
  ;
  }

  { // ImGuiMouseSource
  auto e = nb::enum_<ImGuiMouseSource>(m, "ImGuiMouseSource", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiMouseSource_Mouse",                       ImGuiMouseSource_Mouse);                       m.attr("ImGuiMouseSource_Mouse")                       = ImGuiMouseSource::ImGuiMouseSource_Mouse;
    e.value("ImGuiMouseSource_TouchScreen",                 ImGuiMouseSource_TouchScreen);                 m.attr("ImGuiMouseSource_TouchScreen")                 = ImGuiMouseSource::ImGuiMouseSource_TouchScreen;
    e.value("ImGuiMouseSource_Pen",                         ImGuiMouseSource_Pen);                         m.attr("ImGuiMouseSource_Pen")                         = ImGuiMouseSource::ImGuiMouseSource_Pen;
    e.value("ImGuiMouseSource_COUNT",                       ImGuiMouseSource_COUNT);                       m.attr("ImGuiMouseSource_COUNT")                       = ImGuiMouseSource::ImGuiMouseSource_COUNT;
  ;
  }

  { // ImGuiCond_
  auto e = nb::enum_<ImGuiCond_>(m, "ImGuiCond_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiCond_None",                               ImGuiCond_None);                               m.attr("ImGuiCond_None")                               = ImGuiCond_::ImGuiCond_None;
    e.value("ImGuiCond_Always",                             ImGuiCond_Always);                             m.attr("ImGuiCond_Always")                             = ImGuiCond_::ImGuiCond_Always;
    e.value("ImGuiCond_Once",                               ImGuiCond_Once);                               m.attr("ImGuiCond_Once")                               = ImGuiCond_::ImGuiCond_Once;
    e.value("ImGuiCond_FirstUseEver",                       ImGuiCond_FirstUseEver);                       m.attr("ImGuiCond_FirstUseEver")                       = ImGuiCond_::ImGuiCond_FirstUseEver;
    e.value("ImGuiCond_Appearing",                          ImGuiCond_Appearing);                          m.attr("ImGuiCond_Appearing")                          = ImGuiCond_::ImGuiCond_Appearing;
  ;
  }

  { // ImGuiTableFlags_
  auto e = nb::enum_<ImGuiTableFlags_>(m, "ImGuiTableFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTableFlags_None",                         ImGuiTableFlags_None);                         m.attr("ImGuiTableFlags_None")                         = ImGuiTableFlags_::ImGuiTableFlags_None;
    e.value("ImGuiTableFlags_Resizable",                    ImGuiTableFlags_Resizable);                    m.attr("ImGuiTableFlags_Resizable")                    = ImGuiTableFlags_::ImGuiTableFlags_Resizable;
    e.value("ImGuiTableFlags_Reorderable",                  ImGuiTableFlags_Reorderable);                  m.attr("ImGuiTableFlags_Reorderable")                  = ImGuiTableFlags_::ImGuiTableFlags_Reorderable;
    e.value("ImGuiTableFlags_Hideable",                     ImGuiTableFlags_Hideable);                     m.attr("ImGuiTableFlags_Hideable")                     = ImGuiTableFlags_::ImGuiTableFlags_Hideable;
    e.value("ImGuiTableFlags_Sortable",                     ImGuiTableFlags_Sortable);                     m.attr("ImGuiTableFlags_Sortable")                     = ImGuiTableFlags_::ImGuiTableFlags_Sortable;
    e.value("ImGuiTableFlags_NoSavedSettings",              ImGuiTableFlags_NoSavedSettings);              m.attr("ImGuiTableFlags_NoSavedSettings")              = ImGuiTableFlags_::ImGuiTableFlags_NoSavedSettings;
    e.value("ImGuiTableFlags_ContextMenuInBody",            ImGuiTableFlags_ContextMenuInBody);            m.attr("ImGuiTableFlags_ContextMenuInBody")            = ImGuiTableFlags_::ImGuiTableFlags_ContextMenuInBody;
    e.value("ImGuiTableFlags_RowBg",                        ImGuiTableFlags_RowBg);                        m.attr("ImGuiTableFlags_RowBg")                        = ImGuiTableFlags_::ImGuiTableFlags_RowBg;
    e.value("ImGuiTableFlags_BordersInnerH",                ImGuiTableFlags_BordersInnerH);                m.attr("ImGuiTableFlags_BordersInnerH")                = ImGuiTableFlags_::ImGuiTableFlags_BordersInnerH;
    e.value("ImGuiTableFlags_BordersOuterH",                ImGuiTableFlags_BordersOuterH);                m.attr("ImGuiTableFlags_BordersOuterH")                = ImGuiTableFlags_::ImGuiTableFlags_BordersOuterH;
    e.value("ImGuiTableFlags_BordersInnerV",                ImGuiTableFlags_BordersInnerV);                m.attr("ImGuiTableFlags_BordersInnerV")                = ImGuiTableFlags_::ImGuiTableFlags_BordersInnerV;
    e.value("ImGuiTableFlags_BordersOuterV",                ImGuiTableFlags_BordersOuterV);                m.attr("ImGuiTableFlags_BordersOuterV")                = ImGuiTableFlags_::ImGuiTableFlags_BordersOuterV;
    e.value("ImGuiTableFlags_BordersH",                     ImGuiTableFlags_BordersH);                     m.attr("ImGuiTableFlags_BordersH")                     = ImGuiTableFlags_::ImGuiTableFlags_BordersH;
    e.value("ImGuiTableFlags_BordersV",                     ImGuiTableFlags_BordersV);                     m.attr("ImGuiTableFlags_BordersV")                     = ImGuiTableFlags_::ImGuiTableFlags_BordersV;
    e.value("ImGuiTableFlags_BordersInner",                 ImGuiTableFlags_BordersInner);                 m.attr("ImGuiTableFlags_BordersInner")                 = ImGuiTableFlags_::ImGuiTableFlags_BordersInner;
    e.value("ImGuiTableFlags_BordersOuter",                 ImGuiTableFlags_BordersOuter);                 m.attr("ImGuiTableFlags_BordersOuter")                 = ImGuiTableFlags_::ImGuiTableFlags_BordersOuter;
    e.value("ImGuiTableFlags_Borders",                      ImGuiTableFlags_Borders);                      m.attr("ImGuiTableFlags_Borders")                      = ImGuiTableFlags_::ImGuiTableFlags_Borders;
    e.value("ImGuiTableFlags_NoBordersInBody",              ImGuiTableFlags_NoBordersInBody);              m.attr("ImGuiTableFlags_NoBordersInBody")              = ImGuiTableFlags_::ImGuiTableFlags_NoBordersInBody;
    e.value("ImGuiTableFlags_NoBordersInBodyUntilResize",   ImGuiTableFlags_NoBordersInBodyUntilResize);   m.attr("ImGuiTableFlags_NoBordersInBodyUntilResize")   = ImGuiTableFlags_::ImGuiTableFlags_NoBordersInBodyUntilResize;
    e.value("ImGuiTableFlags_SizingFixedFit",               ImGuiTableFlags_SizingFixedFit);               m.attr("ImGuiTableFlags_SizingFixedFit")               = ImGuiTableFlags_::ImGuiTableFlags_SizingFixedFit;
    e.value("ImGuiTableFlags_SizingFixedSame",              ImGuiTableFlags_SizingFixedSame);              m.attr("ImGuiTableFlags_SizingFixedSame")              = ImGuiTableFlags_::ImGuiTableFlags_SizingFixedSame;
    e.value("ImGuiTableFlags_SizingStretchProp",            ImGuiTableFlags_SizingStretchProp);            m.attr("ImGuiTableFlags_SizingStretchProp")            = ImGuiTableFlags_::ImGuiTableFlags_SizingStretchProp;
    e.value("ImGuiTableFlags_SizingStretchSame",            ImGuiTableFlags_SizingStretchSame);            m.attr("ImGuiTableFlags_SizingStretchSame")            = ImGuiTableFlags_::ImGuiTableFlags_SizingStretchSame;
    e.value("ImGuiTableFlags_NoHostExtendX",                ImGuiTableFlags_NoHostExtendX);                m.attr("ImGuiTableFlags_NoHostExtendX")                = ImGuiTableFlags_::ImGuiTableFlags_NoHostExtendX;
    e.value("ImGuiTableFlags_NoHostExtendY",                ImGuiTableFlags_NoHostExtendY);                m.attr("ImGuiTableFlags_NoHostExtendY")                = ImGuiTableFlags_::ImGuiTableFlags_NoHostExtendY;
    e.value("ImGuiTableFlags_NoKeepColumnsVisible",         ImGuiTableFlags_NoKeepColumnsVisible);         m.attr("ImGuiTableFlags_NoKeepColumnsVisible")         = ImGuiTableFlags_::ImGuiTableFlags_NoKeepColumnsVisible;
    e.value("ImGuiTableFlags_PreciseWidths",                ImGuiTableFlags_PreciseWidths);                m.attr("ImGuiTableFlags_PreciseWidths")                = ImGuiTableFlags_::ImGuiTableFlags_PreciseWidths;
    e.value("ImGuiTableFlags_NoClip",                       ImGuiTableFlags_NoClip);                       m.attr("ImGuiTableFlags_NoClip")                       = ImGuiTableFlags_::ImGuiTableFlags_NoClip;
    e.value("ImGuiTableFlags_PadOuterX",                    ImGuiTableFlags_PadOuterX);                    m.attr("ImGuiTableFlags_PadOuterX")                    = ImGuiTableFlags_::ImGuiTableFlags_PadOuterX;
    e.value("ImGuiTableFlags_NoPadOuterX",                  ImGuiTableFlags_NoPadOuterX);                  m.attr("ImGuiTableFlags_NoPadOuterX")                  = ImGuiTableFlags_::ImGuiTableFlags_NoPadOuterX;
    e.value("ImGuiTableFlags_NoPadInnerX",                  ImGuiTableFlags_NoPadInnerX);                  m.attr("ImGuiTableFlags_NoPadInnerX")                  = ImGuiTableFlags_::ImGuiTableFlags_NoPadInnerX;
    e.value("ImGuiTableFlags_ScrollX",                      ImGuiTableFlags_ScrollX);                      m.attr("ImGuiTableFlags_ScrollX")                      = ImGuiTableFlags_::ImGuiTableFlags_ScrollX;
    e.value("ImGuiTableFlags_ScrollY",                      ImGuiTableFlags_ScrollY);                      m.attr("ImGuiTableFlags_ScrollY")                      = ImGuiTableFlags_::ImGuiTableFlags_ScrollY;
    e.value("ImGuiTableFlags_SortMulti",                    ImGuiTableFlags_SortMulti);                    m.attr("ImGuiTableFlags_SortMulti")                    = ImGuiTableFlags_::ImGuiTableFlags_SortMulti;
    e.value("ImGuiTableFlags_SortTristate",                 ImGuiTableFlags_SortTristate);                 m.attr("ImGuiTableFlags_SortTristate")                 = ImGuiTableFlags_::ImGuiTableFlags_SortTristate;
    e.value("ImGuiTableFlags_HighlightHoveredColumn",       ImGuiTableFlags_HighlightHoveredColumn);       m.attr("ImGuiTableFlags_HighlightHoveredColumn")       = ImGuiTableFlags_::ImGuiTableFlags_HighlightHoveredColumn;
    e.value("ImGuiTableFlags_SizingMask_",                  ImGuiTableFlags_SizingMask_);                  m.attr("ImGuiTableFlags_SizingMask_")                  = ImGuiTableFlags_::ImGuiTableFlags_SizingMask_;
  ;
  }

  { // ImGuiTableColumnFlags_
  auto e = nb::enum_<ImGuiTableColumnFlags_>(m, "ImGuiTableColumnFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTableColumnFlags_None",                   ImGuiTableColumnFlags_None);                   m.attr("ImGuiTableColumnFlags_None")                   = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_None;
    e.value("ImGuiTableColumnFlags_Disabled",               ImGuiTableColumnFlags_Disabled);               m.attr("ImGuiTableColumnFlags_Disabled")               = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_Disabled;
    e.value("ImGuiTableColumnFlags_DefaultHide",            ImGuiTableColumnFlags_DefaultHide);            m.attr("ImGuiTableColumnFlags_DefaultHide")            = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_DefaultHide;
    e.value("ImGuiTableColumnFlags_DefaultSort",            ImGuiTableColumnFlags_DefaultSort);            m.attr("ImGuiTableColumnFlags_DefaultSort")            = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_DefaultSort;
    e.value("ImGuiTableColumnFlags_WidthStretch",           ImGuiTableColumnFlags_WidthStretch);           m.attr("ImGuiTableColumnFlags_WidthStretch")           = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthStretch;
    e.value("ImGuiTableColumnFlags_WidthFixed",             ImGuiTableColumnFlags_WidthFixed);             m.attr("ImGuiTableColumnFlags_WidthFixed")             = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthFixed;
    e.value("ImGuiTableColumnFlags_NoResize",               ImGuiTableColumnFlags_NoResize);               m.attr("ImGuiTableColumnFlags_NoResize")               = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoResize;
    e.value("ImGuiTableColumnFlags_NoReorder",              ImGuiTableColumnFlags_NoReorder);              m.attr("ImGuiTableColumnFlags_NoReorder")              = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoReorder;
    e.value("ImGuiTableColumnFlags_NoHide",                 ImGuiTableColumnFlags_NoHide);                 m.attr("ImGuiTableColumnFlags_NoHide")                 = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHide;
    e.value("ImGuiTableColumnFlags_NoClip",                 ImGuiTableColumnFlags_NoClip);                 m.attr("ImGuiTableColumnFlags_NoClip")                 = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoClip;
    e.value("ImGuiTableColumnFlags_NoSort",                 ImGuiTableColumnFlags_NoSort);                 m.attr("ImGuiTableColumnFlags_NoSort")                 = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSort;
    e.value("ImGuiTableColumnFlags_NoSortAscending",        ImGuiTableColumnFlags_NoSortAscending);        m.attr("ImGuiTableColumnFlags_NoSortAscending")        = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSortAscending;
    e.value("ImGuiTableColumnFlags_NoSortDescending",       ImGuiTableColumnFlags_NoSortDescending);       m.attr("ImGuiTableColumnFlags_NoSortDescending")       = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSortDescending;
    e.value("ImGuiTableColumnFlags_NoHeaderLabel",          ImGuiTableColumnFlags_NoHeaderLabel);          m.attr("ImGuiTableColumnFlags_NoHeaderLabel")          = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHeaderLabel;
    e.value("ImGuiTableColumnFlags_NoHeaderWidth",          ImGuiTableColumnFlags_NoHeaderWidth);          m.attr("ImGuiTableColumnFlags_NoHeaderWidth")          = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHeaderWidth;
    e.value("ImGuiTableColumnFlags_PreferSortAscending",    ImGuiTableColumnFlags_PreferSortAscending);    m.attr("ImGuiTableColumnFlags_PreferSortAscending")    = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_PreferSortAscending;
    e.value("ImGuiTableColumnFlags_PreferSortDescending",   ImGuiTableColumnFlags_PreferSortDescending);   m.attr("ImGuiTableColumnFlags_PreferSortDescending")   = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_PreferSortDescending;
    e.value("ImGuiTableColumnFlags_IndentEnable",           ImGuiTableColumnFlags_IndentEnable);           m.attr("ImGuiTableColumnFlags_IndentEnable")           = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentEnable;
    e.value("ImGuiTableColumnFlags_IndentDisable",          ImGuiTableColumnFlags_IndentDisable);          m.attr("ImGuiTableColumnFlags_IndentDisable")          = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentDisable;
    e.value("ImGuiTableColumnFlags_AngledHeader",           ImGuiTableColumnFlags_AngledHeader);           m.attr("ImGuiTableColumnFlags_AngledHeader")           = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_AngledHeader;
    e.value("ImGuiTableColumnFlags_IsEnabled",              ImGuiTableColumnFlags_IsEnabled);              m.attr("ImGuiTableColumnFlags_IsEnabled")              = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsEnabled;
    e.value("ImGuiTableColumnFlags_IsVisible",              ImGuiTableColumnFlags_IsVisible);              m.attr("ImGuiTableColumnFlags_IsVisible")              = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsVisible;
    e.value("ImGuiTableColumnFlags_IsSorted",               ImGuiTableColumnFlags_IsSorted);               m.attr("ImGuiTableColumnFlags_IsSorted")               = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsSorted;
    e.value("ImGuiTableColumnFlags_IsHovered",              ImGuiTableColumnFlags_IsHovered);              m.attr("ImGuiTableColumnFlags_IsHovered")              = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsHovered;
    e.value("ImGuiTableColumnFlags_WidthMask_",             ImGuiTableColumnFlags_WidthMask_);             m.attr("ImGuiTableColumnFlags_WidthMask_")             = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthMask_;
    e.value("ImGuiTableColumnFlags_IndentMask_",            ImGuiTableColumnFlags_IndentMask_);            m.attr("ImGuiTableColumnFlags_IndentMask_")            = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentMask_;
    e.value("ImGuiTableColumnFlags_StatusMask_",            ImGuiTableColumnFlags_StatusMask_);            m.attr("ImGuiTableColumnFlags_StatusMask_")            = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_StatusMask_;
    e.value("ImGuiTableColumnFlags_NoDirectResize_",        ImGuiTableColumnFlags_NoDirectResize_);        m.attr("ImGuiTableColumnFlags_NoDirectResize_")        = ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoDirectResize_;
  ;
  }

  { // ImGuiTableRowFlags_
  auto e = nb::enum_<ImGuiTableRowFlags_>(m, "ImGuiTableRowFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTableRowFlags_None",                      ImGuiTableRowFlags_None);                      m.attr("ImGuiTableRowFlags_None")                      = ImGuiTableRowFlags_::ImGuiTableRowFlags_None;
    e.value("ImGuiTableRowFlags_Headers",                   ImGuiTableRowFlags_Headers);                   m.attr("ImGuiTableRowFlags_Headers")                   = ImGuiTableRowFlags_::ImGuiTableRowFlags_Headers;
  ;
  }

  { // ImGuiTableBgTarget_
  auto e = nb::enum_<ImGuiTableBgTarget_>(m, "ImGuiTableBgTarget_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiTableBgTarget_None",                      ImGuiTableBgTarget_None);                      m.attr("ImGuiTableBgTarget_None")                      = ImGuiTableBgTarget_::ImGuiTableBgTarget_None;
    e.value("ImGuiTableBgTarget_RowBg0",                    ImGuiTableBgTarget_RowBg0);                    m.attr("ImGuiTableBgTarget_RowBg0")                    = ImGuiTableBgTarget_::ImGuiTableBgTarget_RowBg0;
    e.value("ImGuiTableBgTarget_RowBg1",                    ImGuiTableBgTarget_RowBg1);                    m.attr("ImGuiTableBgTarget_RowBg1")                    = ImGuiTableBgTarget_::ImGuiTableBgTarget_RowBg1;
    e.value("ImGuiTableBgTarget_CellBg",                    ImGuiTableBgTarget_CellBg);                    m.attr("ImGuiTableBgTarget_CellBg")                    = ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg;
  ;
  }

  { // ImGuiListClipperFlags_
  auto e = nb::enum_<ImGuiListClipperFlags_>(m, "ImGuiListClipperFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiListClipperFlags_None",                   ImGuiListClipperFlags_None);                   m.attr("ImGuiListClipperFlags_None")                   = ImGuiListClipperFlags_::ImGuiListClipperFlags_None;
    e.value("ImGuiListClipperFlags_NoSetTableRowCounters",  ImGuiListClipperFlags_NoSetTableRowCounters);  m.attr("ImGuiListClipperFlags_NoSetTableRowCounters")  = ImGuiListClipperFlags_::ImGuiListClipperFlags_NoSetTableRowCounters;
  ;
  }

  { // ImGuiMultiSelectFlags_
  auto e = nb::enum_<ImGuiMultiSelectFlags_>(m, "ImGuiMultiSelectFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiMultiSelectFlags_None",                   ImGuiMultiSelectFlags_None);                   m.attr("ImGuiMultiSelectFlags_None")                   = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_None;
    e.value("ImGuiMultiSelectFlags_SingleSelect",           ImGuiMultiSelectFlags_SingleSelect);           m.attr("ImGuiMultiSelectFlags_SingleSelect")           = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SingleSelect;
    e.value("ImGuiMultiSelectFlags_NoSelectAll",            ImGuiMultiSelectFlags_NoSelectAll);            m.attr("ImGuiMultiSelectFlags_NoSelectAll")            = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoSelectAll;
    e.value("ImGuiMultiSelectFlags_NoRangeSelect",          ImGuiMultiSelectFlags_NoRangeSelect);          m.attr("ImGuiMultiSelectFlags_NoRangeSelect")          = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoRangeSelect;
    e.value("ImGuiMultiSelectFlags_NoAutoSelect",           ImGuiMultiSelectFlags_NoAutoSelect);           m.attr("ImGuiMultiSelectFlags_NoAutoSelect")           = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoSelect;
    e.value("ImGuiMultiSelectFlags_NoAutoClear",            ImGuiMultiSelectFlags_NoAutoClear);            m.attr("ImGuiMultiSelectFlags_NoAutoClear")            = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoClear;
    e.value("ImGuiMultiSelectFlags_NoAutoClearOnReselect",  ImGuiMultiSelectFlags_NoAutoClearOnReselect);  m.attr("ImGuiMultiSelectFlags_NoAutoClearOnReselect")  = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoClearOnReselect;
    e.value("ImGuiMultiSelectFlags_BoxSelect1d",            ImGuiMultiSelectFlags_BoxSelect1d);            m.attr("ImGuiMultiSelectFlags_BoxSelect1d")            = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelect1d;
    e.value("ImGuiMultiSelectFlags_BoxSelect2d",            ImGuiMultiSelectFlags_BoxSelect2d);            m.attr("ImGuiMultiSelectFlags_BoxSelect2d")            = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelect2d;
    e.value("ImGuiMultiSelectFlags_BoxSelectNoScroll",      ImGuiMultiSelectFlags_BoxSelectNoScroll);      m.attr("ImGuiMultiSelectFlags_BoxSelectNoScroll")      = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelectNoScroll;
    e.value("ImGuiMultiSelectFlags_ClearOnEscape",          ImGuiMultiSelectFlags_ClearOnEscape);          m.attr("ImGuiMultiSelectFlags_ClearOnEscape")          = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ClearOnEscape;
    e.value("ImGuiMultiSelectFlags_ClearOnClickVoid",       ImGuiMultiSelectFlags_ClearOnClickVoid);       m.attr("ImGuiMultiSelectFlags_ClearOnClickVoid")       = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ClearOnClickVoid;
    e.value("ImGuiMultiSelectFlags_ScopeWindow",            ImGuiMultiSelectFlags_ScopeWindow);            m.attr("ImGuiMultiSelectFlags_ScopeWindow")            = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ScopeWindow;
    e.value("ImGuiMultiSelectFlags_ScopeRect",              ImGuiMultiSelectFlags_ScopeRect);              m.attr("ImGuiMultiSelectFlags_ScopeRect")              = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ScopeRect;
    e.value("ImGuiMultiSelectFlags_SelectOnClick",          ImGuiMultiSelectFlags_SelectOnClick);          m.attr("ImGuiMultiSelectFlags_SelectOnClick")          = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SelectOnClick;
    e.value("ImGuiMultiSelectFlags_SelectOnClickRelease",   ImGuiMultiSelectFlags_SelectOnClickRelease);   m.attr("ImGuiMultiSelectFlags_SelectOnClickRelease")   = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SelectOnClickRelease;
    e.value("ImGuiMultiSelectFlags_NavWrapX",               ImGuiMultiSelectFlags_NavWrapX);               m.attr("ImGuiMultiSelectFlags_NavWrapX")               = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NavWrapX;
    e.value("ImGuiMultiSelectFlags_NoSelectOnRightClick",   ImGuiMultiSelectFlags_NoSelectOnRightClick);   m.attr("ImGuiMultiSelectFlags_NoSelectOnRightClick")   = ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoSelectOnRightClick;
  ;
  }

  { // ImGuiSelectionRequestType
  auto e = nb::enum_<ImGuiSelectionRequestType>(m, "ImGuiSelectionRequestType", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiSelectionRequestType_None",               ImGuiSelectionRequestType_None);               m.attr("ImGuiSelectionRequestType_None")               = ImGuiSelectionRequestType::ImGuiSelectionRequestType_None;
    e.value("ImGuiSelectionRequestType_SetAll",             ImGuiSelectionRequestType_SetAll);             m.attr("ImGuiSelectionRequestType_SetAll")             = ImGuiSelectionRequestType::ImGuiSelectionRequestType_SetAll;
    e.value("ImGuiSelectionRequestType_SetRange",           ImGuiSelectionRequestType_SetRange);           m.attr("ImGuiSelectionRequestType_SetRange")           = ImGuiSelectionRequestType::ImGuiSelectionRequestType_SetRange;
  ;
  }

  { // ImDrawFlags_
  auto e = nb::enum_<ImDrawFlags_>(m, "ImDrawFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImDrawFlags_None",                             ImDrawFlags_None);                             m.attr("ImDrawFlags_None")                             = ImDrawFlags_::ImDrawFlags_None;
    e.value("ImDrawFlags_Closed",                           ImDrawFlags_Closed);                           m.attr("ImDrawFlags_Closed")                           = ImDrawFlags_::ImDrawFlags_Closed;
    e.value("ImDrawFlags_RoundCornersTopLeft",              ImDrawFlags_RoundCornersTopLeft);              m.attr("ImDrawFlags_RoundCornersTopLeft")              = ImDrawFlags_::ImDrawFlags_RoundCornersTopLeft;
    e.value("ImDrawFlags_RoundCornersTopRight",             ImDrawFlags_RoundCornersTopRight);             m.attr("ImDrawFlags_RoundCornersTopRight")             = ImDrawFlags_::ImDrawFlags_RoundCornersTopRight;
    e.value("ImDrawFlags_RoundCornersBottomLeft",           ImDrawFlags_RoundCornersBottomLeft);           m.attr("ImDrawFlags_RoundCornersBottomLeft")           = ImDrawFlags_::ImDrawFlags_RoundCornersBottomLeft;
    e.value("ImDrawFlags_RoundCornersBottomRight",          ImDrawFlags_RoundCornersBottomRight);          m.attr("ImDrawFlags_RoundCornersBottomRight")          = ImDrawFlags_::ImDrawFlags_RoundCornersBottomRight;
    e.value("ImDrawFlags_RoundCornersNone",                 ImDrawFlags_RoundCornersNone);                 m.attr("ImDrawFlags_RoundCornersNone")                 = ImDrawFlags_::ImDrawFlags_RoundCornersNone;
    e.value("ImDrawFlags_RoundCornersTop",                  ImDrawFlags_RoundCornersTop);                  m.attr("ImDrawFlags_RoundCornersTop")                  = ImDrawFlags_::ImDrawFlags_RoundCornersTop;
    e.value("ImDrawFlags_RoundCornersBottom",               ImDrawFlags_RoundCornersBottom);               m.attr("ImDrawFlags_RoundCornersBottom")               = ImDrawFlags_::ImDrawFlags_RoundCornersBottom;
    e.value("ImDrawFlags_RoundCornersLeft",                 ImDrawFlags_RoundCornersLeft);                 m.attr("ImDrawFlags_RoundCornersLeft")                 = ImDrawFlags_::ImDrawFlags_RoundCornersLeft;
    e.value("ImDrawFlags_RoundCornersRight",                ImDrawFlags_RoundCornersRight);                m.attr("ImDrawFlags_RoundCornersRight")                = ImDrawFlags_::ImDrawFlags_RoundCornersRight;
    e.value("ImDrawFlags_RoundCornersAll",                  ImDrawFlags_RoundCornersAll);                  m.attr("ImDrawFlags_RoundCornersAll")                  = ImDrawFlags_::ImDrawFlags_RoundCornersAll;
    e.value("ImDrawFlags_RoundCornersDefault_",             ImDrawFlags_RoundCornersDefault_);             m.attr("ImDrawFlags_RoundCornersDefault_")             = ImDrawFlags_::ImDrawFlags_RoundCornersDefault_;
    e.value("ImDrawFlags_RoundCornersMask_",                ImDrawFlags_RoundCornersMask_);                m.attr("ImDrawFlags_RoundCornersMask_")                = ImDrawFlags_::ImDrawFlags_RoundCornersMask_;
  ;
  }

  { // ImDrawListFlags_
  auto e = nb::enum_<ImDrawListFlags_>(m, "ImDrawListFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImDrawListFlags_None",                         ImDrawListFlags_None);                         m.attr("ImDrawListFlags_None")                         = ImDrawListFlags_::ImDrawListFlags_None;
    e.value("ImDrawListFlags_AntiAliasedLines",             ImDrawListFlags_AntiAliasedLines);             m.attr("ImDrawListFlags_AntiAliasedLines")             = ImDrawListFlags_::ImDrawListFlags_AntiAliasedLines;
    e.value("ImDrawListFlags_AntiAliasedLinesUseTex",       ImDrawListFlags_AntiAliasedLinesUseTex);       m.attr("ImDrawListFlags_AntiAliasedLinesUseTex")       = ImDrawListFlags_::ImDrawListFlags_AntiAliasedLinesUseTex;
    e.value("ImDrawListFlags_AntiAliasedFill",              ImDrawListFlags_AntiAliasedFill);              m.attr("ImDrawListFlags_AntiAliasedFill")              = ImDrawListFlags_::ImDrawListFlags_AntiAliasedFill;
    e.value("ImDrawListFlags_AllowVtxOffset",               ImDrawListFlags_AllowVtxOffset);               m.attr("ImDrawListFlags_AllowVtxOffset")               = ImDrawListFlags_::ImDrawListFlags_AllowVtxOffset;
  ;
  }

  { // ImTextureFormat
  auto e = nb::enum_<ImTextureFormat>(m, "ImTextureFormat", nb::is_arithmetic(), nb::is_flag());
    e.value("ImTextureFormat_RGBA32",                       ImTextureFormat_RGBA32);                       m.attr("ImTextureFormat_RGBA32")                       = ImTextureFormat::ImTextureFormat_RGBA32;
    e.value("ImTextureFormat_Alpha8",                       ImTextureFormat_Alpha8);                       m.attr("ImTextureFormat_Alpha8")                       = ImTextureFormat::ImTextureFormat_Alpha8;
  ;
  }

  { // ImTextureStatus
  auto e = nb::enum_<ImTextureStatus>(m, "ImTextureStatus", nb::is_arithmetic(), nb::is_flag());
    e.value("ImTextureStatus_OK",                           ImTextureStatus_OK);                           m.attr("ImTextureStatus_OK")                           = ImTextureStatus::ImTextureStatus_OK;
    e.value("ImTextureStatus_Destroyed",                    ImTextureStatus_Destroyed);                    m.attr("ImTextureStatus_Destroyed")                    = ImTextureStatus::ImTextureStatus_Destroyed;
    e.value("ImTextureStatus_WantCreate",                   ImTextureStatus_WantCreate);                   m.attr("ImTextureStatus_WantCreate")                   = ImTextureStatus::ImTextureStatus_WantCreate;
    e.value("ImTextureStatus_WantUpdates",                  ImTextureStatus_WantUpdates);                  m.attr("ImTextureStatus_WantUpdates")                  = ImTextureStatus::ImTextureStatus_WantUpdates;
    e.value("ImTextureStatus_WantDestroy",                  ImTextureStatus_WantDestroy);                  m.attr("ImTextureStatus_WantDestroy")                  = ImTextureStatus::ImTextureStatus_WantDestroy;
  ;
  }

  { // ImFontAtlasFlags_
  auto e = nb::enum_<ImFontAtlasFlags_>(m, "ImFontAtlasFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImFontAtlasFlags_None",                        ImFontAtlasFlags_None);                        m.attr("ImFontAtlasFlags_None")                        = ImFontAtlasFlags_::ImFontAtlasFlags_None;
    e.value("ImFontAtlasFlags_NoPowerOfTwoHeight",          ImFontAtlasFlags_NoPowerOfTwoHeight);          m.attr("ImFontAtlasFlags_NoPowerOfTwoHeight")          = ImFontAtlasFlags_::ImFontAtlasFlags_NoPowerOfTwoHeight;
    e.value("ImFontAtlasFlags_NoMouseCursors",              ImFontAtlasFlags_NoMouseCursors);              m.attr("ImFontAtlasFlags_NoMouseCursors")              = ImFontAtlasFlags_::ImFontAtlasFlags_NoMouseCursors;
    e.value("ImFontAtlasFlags_NoBakedLines",                ImFontAtlasFlags_NoBakedLines);                m.attr("ImFontAtlasFlags_NoBakedLines")                = ImFontAtlasFlags_::ImFontAtlasFlags_NoBakedLines;
  ;
  }

  { // ImFontFlags_
  auto e = nb::enum_<ImFontFlags_>(m, "ImFontFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImFontFlags_None",                             ImFontFlags_None);                             m.attr("ImFontFlags_None")                             = ImFontFlags_::ImFontFlags_None;
    e.value("ImFontFlags_NoLoadError",                      ImFontFlags_NoLoadError);                      m.attr("ImFontFlags_NoLoadError")                      = ImFontFlags_::ImFontFlags_NoLoadError;
    e.value("ImFontFlags_NoLoadGlyphs",                     ImFontFlags_NoLoadGlyphs);                     m.attr("ImFontFlags_NoLoadGlyphs")                     = ImFontFlags_::ImFontFlags_NoLoadGlyphs;
    e.value("ImFontFlags_LockBakedSizes",                   ImFontFlags_LockBakedSizes);                   m.attr("ImFontFlags_LockBakedSizes")                   = ImFontFlags_::ImFontFlags_LockBakedSizes;
  ;
  }

  { // ImGuiViewportFlags_
  auto e = nb::enum_<ImGuiViewportFlags_>(m, "ImGuiViewportFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImGuiViewportFlags_None",                      ImGuiViewportFlags_None);                      m.attr("ImGuiViewportFlags_None")                      = ImGuiViewportFlags_::ImGuiViewportFlags_None;
    e.value("ImGuiViewportFlags_IsPlatformWindow",          ImGuiViewportFlags_IsPlatformWindow);          m.attr("ImGuiViewportFlags_IsPlatformWindow")          = ImGuiViewportFlags_::ImGuiViewportFlags_IsPlatformWindow;
    e.value("ImGuiViewportFlags_IsPlatformMonitor",         ImGuiViewportFlags_IsPlatformMonitor);         m.attr("ImGuiViewportFlags_IsPlatformMonitor")         = ImGuiViewportFlags_::ImGuiViewportFlags_IsPlatformMonitor;
    e.value("ImGuiViewportFlags_OwnedByApp",                ImGuiViewportFlags_OwnedByApp);                m.attr("ImGuiViewportFlags_OwnedByApp")                = ImGuiViewportFlags_::ImGuiViewportFlags_OwnedByApp;
  ;
  }

}
