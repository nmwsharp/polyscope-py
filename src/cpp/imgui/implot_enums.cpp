// AUTO-GENERATED FILE - DO NOT EDIT
// Generated: 2026-02-01 17:13:16
// implot version: 0.17
// Generator: python3 scripts/generate_imgui_enums.py

#include "implot.h"

#include "../utils.h"
#include "imgui_utils.h"

void bind_implot_enums(nb::module_& m) {

  { // ImAxis_
  auto e = nb::enum_<ImAxis_>(m, "ImAxis_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImAxis_X1",                                    ImAxis_X1);                                    m.attr("ImAxis_X1")                                    = ImAxis_::ImAxis_X1;
    e.value("ImAxis_X2",                                    ImAxis_X2);                                    m.attr("ImAxis_X2")                                    = ImAxis_::ImAxis_X2;
    e.value("ImAxis_X3",                                    ImAxis_X3);                                    m.attr("ImAxis_X3")                                    = ImAxis_::ImAxis_X3;
    e.value("ImAxis_Y1",                                    ImAxis_Y1);                                    m.attr("ImAxis_Y1")                                    = ImAxis_::ImAxis_Y1;
    e.value("ImAxis_Y2",                                    ImAxis_Y2);                                    m.attr("ImAxis_Y2")                                    = ImAxis_::ImAxis_Y2;
    e.value("ImAxis_Y3",                                    ImAxis_Y3);                                    m.attr("ImAxis_Y3")                                    = ImAxis_::ImAxis_Y3;
    e.value("ImAxis_COUNT",                                 ImAxis_COUNT);                                 m.attr("ImAxis_COUNT")                                 = ImAxis_::ImAxis_COUNT;
  ;
  }

  { // ImPlotFlags_
  auto e = nb::enum_<ImPlotFlags_>(m, "ImPlotFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotFlags_None",                             ImPlotFlags_None);                             m.attr("ImPlotFlags_None")                             = ImPlotFlags_::ImPlotFlags_None;
    e.value("ImPlotFlags_NoTitle",                          ImPlotFlags_NoTitle);                          m.attr("ImPlotFlags_NoTitle")                          = ImPlotFlags_::ImPlotFlags_NoTitle;
    e.value("ImPlotFlags_NoLegend",                         ImPlotFlags_NoLegend);                         m.attr("ImPlotFlags_NoLegend")                         = ImPlotFlags_::ImPlotFlags_NoLegend;
    e.value("ImPlotFlags_NoMouseText",                      ImPlotFlags_NoMouseText);                      m.attr("ImPlotFlags_NoMouseText")                      = ImPlotFlags_::ImPlotFlags_NoMouseText;
    e.value("ImPlotFlags_NoInputs",                         ImPlotFlags_NoInputs);                         m.attr("ImPlotFlags_NoInputs")                         = ImPlotFlags_::ImPlotFlags_NoInputs;
    e.value("ImPlotFlags_NoMenus",                          ImPlotFlags_NoMenus);                          m.attr("ImPlotFlags_NoMenus")                          = ImPlotFlags_::ImPlotFlags_NoMenus;
    e.value("ImPlotFlags_NoBoxSelect",                      ImPlotFlags_NoBoxSelect);                      m.attr("ImPlotFlags_NoBoxSelect")                      = ImPlotFlags_::ImPlotFlags_NoBoxSelect;
    e.value("ImPlotFlags_NoFrame",                          ImPlotFlags_NoFrame);                          m.attr("ImPlotFlags_NoFrame")                          = ImPlotFlags_::ImPlotFlags_NoFrame;
    e.value("ImPlotFlags_Equal",                            ImPlotFlags_Equal);                            m.attr("ImPlotFlags_Equal")                            = ImPlotFlags_::ImPlotFlags_Equal;
    e.value("ImPlotFlags_Crosshairs",                       ImPlotFlags_Crosshairs);                       m.attr("ImPlotFlags_Crosshairs")                       = ImPlotFlags_::ImPlotFlags_Crosshairs;
    e.value("ImPlotFlags_CanvasOnly",                       ImPlotFlags_CanvasOnly);                       m.attr("ImPlotFlags_CanvasOnly")                       = ImPlotFlags_::ImPlotFlags_CanvasOnly;
  ;
  }

  { // ImPlotAxisFlags_
  auto e = nb::enum_<ImPlotAxisFlags_>(m, "ImPlotAxisFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotAxisFlags_None",                         ImPlotAxisFlags_None);                         m.attr("ImPlotAxisFlags_None")                         = ImPlotAxisFlags_::ImPlotAxisFlags_None;
    e.value("ImPlotAxisFlags_NoLabel",                      ImPlotAxisFlags_NoLabel);                      m.attr("ImPlotAxisFlags_NoLabel")                      = ImPlotAxisFlags_::ImPlotAxisFlags_NoLabel;
    e.value("ImPlotAxisFlags_NoGridLines",                  ImPlotAxisFlags_NoGridLines);                  m.attr("ImPlotAxisFlags_NoGridLines")                  = ImPlotAxisFlags_::ImPlotAxisFlags_NoGridLines;
    e.value("ImPlotAxisFlags_NoTickMarks",                  ImPlotAxisFlags_NoTickMarks);                  m.attr("ImPlotAxisFlags_NoTickMarks")                  = ImPlotAxisFlags_::ImPlotAxisFlags_NoTickMarks;
    e.value("ImPlotAxisFlags_NoTickLabels",                 ImPlotAxisFlags_NoTickLabels);                 m.attr("ImPlotAxisFlags_NoTickLabels")                 = ImPlotAxisFlags_::ImPlotAxisFlags_NoTickLabels;
    e.value("ImPlotAxisFlags_NoInitialFit",                 ImPlotAxisFlags_NoInitialFit);                 m.attr("ImPlotAxisFlags_NoInitialFit")                 = ImPlotAxisFlags_::ImPlotAxisFlags_NoInitialFit;
    e.value("ImPlotAxisFlags_NoMenus",                      ImPlotAxisFlags_NoMenus);                      m.attr("ImPlotAxisFlags_NoMenus")                      = ImPlotAxisFlags_::ImPlotAxisFlags_NoMenus;
    e.value("ImPlotAxisFlags_NoSideSwitch",                 ImPlotAxisFlags_NoSideSwitch);                 m.attr("ImPlotAxisFlags_NoSideSwitch")                 = ImPlotAxisFlags_::ImPlotAxisFlags_NoSideSwitch;
    e.value("ImPlotAxisFlags_NoHighlight",                  ImPlotAxisFlags_NoHighlight);                  m.attr("ImPlotAxisFlags_NoHighlight")                  = ImPlotAxisFlags_::ImPlotAxisFlags_NoHighlight;
    e.value("ImPlotAxisFlags_Opposite",                     ImPlotAxisFlags_Opposite);                     m.attr("ImPlotAxisFlags_Opposite")                     = ImPlotAxisFlags_::ImPlotAxisFlags_Opposite;
    e.value("ImPlotAxisFlags_Foreground",                   ImPlotAxisFlags_Foreground);                   m.attr("ImPlotAxisFlags_Foreground")                   = ImPlotAxisFlags_::ImPlotAxisFlags_Foreground;
    e.value("ImPlotAxisFlags_Invert",                       ImPlotAxisFlags_Invert);                       m.attr("ImPlotAxisFlags_Invert")                       = ImPlotAxisFlags_::ImPlotAxisFlags_Invert;
    e.value("ImPlotAxisFlags_AutoFit",                      ImPlotAxisFlags_AutoFit);                      m.attr("ImPlotAxisFlags_AutoFit")                      = ImPlotAxisFlags_::ImPlotAxisFlags_AutoFit;
    e.value("ImPlotAxisFlags_RangeFit",                     ImPlotAxisFlags_RangeFit);                     m.attr("ImPlotAxisFlags_RangeFit")                     = ImPlotAxisFlags_::ImPlotAxisFlags_RangeFit;
    e.value("ImPlotAxisFlags_PanStretch",                   ImPlotAxisFlags_PanStretch);                   m.attr("ImPlotAxisFlags_PanStretch")                   = ImPlotAxisFlags_::ImPlotAxisFlags_PanStretch;
    e.value("ImPlotAxisFlags_LockMin",                      ImPlotAxisFlags_LockMin);                      m.attr("ImPlotAxisFlags_LockMin")                      = ImPlotAxisFlags_::ImPlotAxisFlags_LockMin;
    e.value("ImPlotAxisFlags_LockMax",                      ImPlotAxisFlags_LockMax);                      m.attr("ImPlotAxisFlags_LockMax")                      = ImPlotAxisFlags_::ImPlotAxisFlags_LockMax;
    e.value("ImPlotAxisFlags_Lock",                         ImPlotAxisFlags_Lock);                         m.attr("ImPlotAxisFlags_Lock")                         = ImPlotAxisFlags_::ImPlotAxisFlags_Lock;
    e.value("ImPlotAxisFlags_NoDecorations",                ImPlotAxisFlags_NoDecorations);                m.attr("ImPlotAxisFlags_NoDecorations")                = ImPlotAxisFlags_::ImPlotAxisFlags_NoDecorations;
    e.value("ImPlotAxisFlags_AuxDefault",                   ImPlotAxisFlags_AuxDefault);                   m.attr("ImPlotAxisFlags_AuxDefault")                   = ImPlotAxisFlags_::ImPlotAxisFlags_AuxDefault;
  ;
  }

  { // ImPlotSubplotFlags_
  auto e = nb::enum_<ImPlotSubplotFlags_>(m, "ImPlotSubplotFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotSubplotFlags_None",                      ImPlotSubplotFlags_None);                      m.attr("ImPlotSubplotFlags_None")                      = ImPlotSubplotFlags_::ImPlotSubplotFlags_None;
    e.value("ImPlotSubplotFlags_NoTitle",                   ImPlotSubplotFlags_NoTitle);                   m.attr("ImPlotSubplotFlags_NoTitle")                   = ImPlotSubplotFlags_::ImPlotSubplotFlags_NoTitle;
    e.value("ImPlotSubplotFlags_NoLegend",                  ImPlotSubplotFlags_NoLegend);                  m.attr("ImPlotSubplotFlags_NoLegend")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_NoLegend;
    e.value("ImPlotSubplotFlags_NoMenus",                   ImPlotSubplotFlags_NoMenus);                   m.attr("ImPlotSubplotFlags_NoMenus")                   = ImPlotSubplotFlags_::ImPlotSubplotFlags_NoMenus;
    e.value("ImPlotSubplotFlags_NoResize",                  ImPlotSubplotFlags_NoResize);                  m.attr("ImPlotSubplotFlags_NoResize")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_NoResize;
    e.value("ImPlotSubplotFlags_NoAlign",                   ImPlotSubplotFlags_NoAlign);                   m.attr("ImPlotSubplotFlags_NoAlign")                   = ImPlotSubplotFlags_::ImPlotSubplotFlags_NoAlign;
    e.value("ImPlotSubplotFlags_ShareItems",                ImPlotSubplotFlags_ShareItems);                m.attr("ImPlotSubplotFlags_ShareItems")                = ImPlotSubplotFlags_::ImPlotSubplotFlags_ShareItems;
    e.value("ImPlotSubplotFlags_LinkRows",                  ImPlotSubplotFlags_LinkRows);                  m.attr("ImPlotSubplotFlags_LinkRows")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_LinkRows;
    e.value("ImPlotSubplotFlags_LinkCols",                  ImPlotSubplotFlags_LinkCols);                  m.attr("ImPlotSubplotFlags_LinkCols")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_LinkCols;
    e.value("ImPlotSubplotFlags_LinkAllX",                  ImPlotSubplotFlags_LinkAllX);                  m.attr("ImPlotSubplotFlags_LinkAllX")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_LinkAllX;
    e.value("ImPlotSubplotFlags_LinkAllY",                  ImPlotSubplotFlags_LinkAllY);                  m.attr("ImPlotSubplotFlags_LinkAllY")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_LinkAllY;
    e.value("ImPlotSubplotFlags_ColMajor",                  ImPlotSubplotFlags_ColMajor);                  m.attr("ImPlotSubplotFlags_ColMajor")                  = ImPlotSubplotFlags_::ImPlotSubplotFlags_ColMajor;
  ;
  }

  { // ImPlotLegendFlags_
  auto e = nb::enum_<ImPlotLegendFlags_>(m, "ImPlotLegendFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotLegendFlags_None",                       ImPlotLegendFlags_None);                       m.attr("ImPlotLegendFlags_None")                       = ImPlotLegendFlags_::ImPlotLegendFlags_None;
    e.value("ImPlotLegendFlags_NoButtons",                  ImPlotLegendFlags_NoButtons);                  m.attr("ImPlotLegendFlags_NoButtons")                  = ImPlotLegendFlags_::ImPlotLegendFlags_NoButtons;
    e.value("ImPlotLegendFlags_NoHighlightItem",            ImPlotLegendFlags_NoHighlightItem);            m.attr("ImPlotLegendFlags_NoHighlightItem")            = ImPlotLegendFlags_::ImPlotLegendFlags_NoHighlightItem;
    e.value("ImPlotLegendFlags_NoHighlightAxis",            ImPlotLegendFlags_NoHighlightAxis);            m.attr("ImPlotLegendFlags_NoHighlightAxis")            = ImPlotLegendFlags_::ImPlotLegendFlags_NoHighlightAxis;
    e.value("ImPlotLegendFlags_NoMenus",                    ImPlotLegendFlags_NoMenus);                    m.attr("ImPlotLegendFlags_NoMenus")                    = ImPlotLegendFlags_::ImPlotLegendFlags_NoMenus;
    e.value("ImPlotLegendFlags_Outside",                    ImPlotLegendFlags_Outside);                    m.attr("ImPlotLegendFlags_Outside")                    = ImPlotLegendFlags_::ImPlotLegendFlags_Outside;
    e.value("ImPlotLegendFlags_Horizontal",                 ImPlotLegendFlags_Horizontal);                 m.attr("ImPlotLegendFlags_Horizontal")                 = ImPlotLegendFlags_::ImPlotLegendFlags_Horizontal;
    e.value("ImPlotLegendFlags_Sort",                       ImPlotLegendFlags_Sort);                       m.attr("ImPlotLegendFlags_Sort")                       = ImPlotLegendFlags_::ImPlotLegendFlags_Sort;
  ;
  }

  { // ImPlotMouseTextFlags_
  auto e = nb::enum_<ImPlotMouseTextFlags_>(m, "ImPlotMouseTextFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotMouseTextFlags_None",                    ImPlotMouseTextFlags_None);                    m.attr("ImPlotMouseTextFlags_None")                    = ImPlotMouseTextFlags_::ImPlotMouseTextFlags_None;
    e.value("ImPlotMouseTextFlags_NoAuxAxes",               ImPlotMouseTextFlags_NoAuxAxes);               m.attr("ImPlotMouseTextFlags_NoAuxAxes")               = ImPlotMouseTextFlags_::ImPlotMouseTextFlags_NoAuxAxes;
    e.value("ImPlotMouseTextFlags_NoFormat",                ImPlotMouseTextFlags_NoFormat);                m.attr("ImPlotMouseTextFlags_NoFormat")                = ImPlotMouseTextFlags_::ImPlotMouseTextFlags_NoFormat;
    e.value("ImPlotMouseTextFlags_ShowAlways",              ImPlotMouseTextFlags_ShowAlways);              m.attr("ImPlotMouseTextFlags_ShowAlways")              = ImPlotMouseTextFlags_::ImPlotMouseTextFlags_ShowAlways;
  ;
  }

  { // ImPlotDragToolFlags_
  auto e = nb::enum_<ImPlotDragToolFlags_>(m, "ImPlotDragToolFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotDragToolFlags_None",                     ImPlotDragToolFlags_None);                     m.attr("ImPlotDragToolFlags_None")                     = ImPlotDragToolFlags_::ImPlotDragToolFlags_None;
    e.value("ImPlotDragToolFlags_NoCursors",                ImPlotDragToolFlags_NoCursors);                m.attr("ImPlotDragToolFlags_NoCursors")                = ImPlotDragToolFlags_::ImPlotDragToolFlags_NoCursors;
    e.value("ImPlotDragToolFlags_NoFit",                    ImPlotDragToolFlags_NoFit);                    m.attr("ImPlotDragToolFlags_NoFit")                    = ImPlotDragToolFlags_::ImPlotDragToolFlags_NoFit;
    e.value("ImPlotDragToolFlags_NoInputs",                 ImPlotDragToolFlags_NoInputs);                 m.attr("ImPlotDragToolFlags_NoInputs")                 = ImPlotDragToolFlags_::ImPlotDragToolFlags_NoInputs;
    e.value("ImPlotDragToolFlags_Delayed",                  ImPlotDragToolFlags_Delayed);                  m.attr("ImPlotDragToolFlags_Delayed")                  = ImPlotDragToolFlags_::ImPlotDragToolFlags_Delayed;
  ;
  }

  { // ImPlotColormapScaleFlags_
  auto e = nb::enum_<ImPlotColormapScaleFlags_>(m, "ImPlotColormapScaleFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotColormapScaleFlags_None",                ImPlotColormapScaleFlags_None);                m.attr("ImPlotColormapScaleFlags_None")                = ImPlotColormapScaleFlags_::ImPlotColormapScaleFlags_None;
    e.value("ImPlotColormapScaleFlags_NoLabel",             ImPlotColormapScaleFlags_NoLabel);             m.attr("ImPlotColormapScaleFlags_NoLabel")             = ImPlotColormapScaleFlags_::ImPlotColormapScaleFlags_NoLabel;
    e.value("ImPlotColormapScaleFlags_Opposite",            ImPlotColormapScaleFlags_Opposite);            m.attr("ImPlotColormapScaleFlags_Opposite")            = ImPlotColormapScaleFlags_::ImPlotColormapScaleFlags_Opposite;
    e.value("ImPlotColormapScaleFlags_Invert",              ImPlotColormapScaleFlags_Invert);              m.attr("ImPlotColormapScaleFlags_Invert")              = ImPlotColormapScaleFlags_::ImPlotColormapScaleFlags_Invert;
  ;
  }

  { // ImPlotItemFlags_
  auto e = nb::enum_<ImPlotItemFlags_>(m, "ImPlotItemFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotItemFlags_None",                         ImPlotItemFlags_None);                         m.attr("ImPlotItemFlags_None")                         = ImPlotItemFlags_::ImPlotItemFlags_None;
    e.value("ImPlotItemFlags_NoLegend",                     ImPlotItemFlags_NoLegend);                     m.attr("ImPlotItemFlags_NoLegend")                     = ImPlotItemFlags_::ImPlotItemFlags_NoLegend;
    e.value("ImPlotItemFlags_NoFit",                        ImPlotItemFlags_NoFit);                        m.attr("ImPlotItemFlags_NoFit")                        = ImPlotItemFlags_::ImPlotItemFlags_NoFit;
  ;
  }

  { // ImPlotLineFlags_
  auto e = nb::enum_<ImPlotLineFlags_>(m, "ImPlotLineFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotLineFlags_None",                         ImPlotLineFlags_None);                         m.attr("ImPlotLineFlags_None")                         = ImPlotLineFlags_::ImPlotLineFlags_None;
    e.value("ImPlotLineFlags_Segments",                     ImPlotLineFlags_Segments);                     m.attr("ImPlotLineFlags_Segments")                     = ImPlotLineFlags_::ImPlotLineFlags_Segments;
    e.value("ImPlotLineFlags_Loop",                         ImPlotLineFlags_Loop);                         m.attr("ImPlotLineFlags_Loop")                         = ImPlotLineFlags_::ImPlotLineFlags_Loop;
    e.value("ImPlotLineFlags_SkipNaN",                      ImPlotLineFlags_SkipNaN);                      m.attr("ImPlotLineFlags_SkipNaN")                      = ImPlotLineFlags_::ImPlotLineFlags_SkipNaN;
    e.value("ImPlotLineFlags_NoClip",                       ImPlotLineFlags_NoClip);                       m.attr("ImPlotLineFlags_NoClip")                       = ImPlotLineFlags_::ImPlotLineFlags_NoClip;
    e.value("ImPlotLineFlags_Shaded",                       ImPlotLineFlags_Shaded);                       m.attr("ImPlotLineFlags_Shaded")                       = ImPlotLineFlags_::ImPlotLineFlags_Shaded;
  ;
  }

  { // ImPlotScatterFlags_
  auto e = nb::enum_<ImPlotScatterFlags_>(m, "ImPlotScatterFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotScatterFlags_None",                      ImPlotScatterFlags_None);                      m.attr("ImPlotScatterFlags_None")                      = ImPlotScatterFlags_::ImPlotScatterFlags_None;
    e.value("ImPlotScatterFlags_NoClip",                    ImPlotScatterFlags_NoClip);                    m.attr("ImPlotScatterFlags_NoClip")                    = ImPlotScatterFlags_::ImPlotScatterFlags_NoClip;
  ;
  }

  { // ImPlotStairsFlags_
  auto e = nb::enum_<ImPlotStairsFlags_>(m, "ImPlotStairsFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotStairsFlags_None",                       ImPlotStairsFlags_None);                       m.attr("ImPlotStairsFlags_None")                       = ImPlotStairsFlags_::ImPlotStairsFlags_None;
    e.value("ImPlotStairsFlags_PreStep",                    ImPlotStairsFlags_PreStep);                    m.attr("ImPlotStairsFlags_PreStep")                    = ImPlotStairsFlags_::ImPlotStairsFlags_PreStep;
    e.value("ImPlotStairsFlags_Shaded",                     ImPlotStairsFlags_Shaded);                     m.attr("ImPlotStairsFlags_Shaded")                     = ImPlotStairsFlags_::ImPlotStairsFlags_Shaded;
  ;
  }

  { // ImPlotShadedFlags_
  auto e = nb::enum_<ImPlotShadedFlags_>(m, "ImPlotShadedFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotShadedFlags_None",                       ImPlotShadedFlags_None);                       m.attr("ImPlotShadedFlags_None")                       = ImPlotShadedFlags_::ImPlotShadedFlags_None;
  ;
  }

  { // ImPlotBarsFlags_
  auto e = nb::enum_<ImPlotBarsFlags_>(m, "ImPlotBarsFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotBarsFlags_None",                         ImPlotBarsFlags_None);                         m.attr("ImPlotBarsFlags_None")                         = ImPlotBarsFlags_::ImPlotBarsFlags_None;
    e.value("ImPlotBarsFlags_Horizontal",                   ImPlotBarsFlags_Horizontal);                   m.attr("ImPlotBarsFlags_Horizontal")                   = ImPlotBarsFlags_::ImPlotBarsFlags_Horizontal;
  ;
  }

  { // ImPlotBarGroupsFlags_
  auto e = nb::enum_<ImPlotBarGroupsFlags_>(m, "ImPlotBarGroupsFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotBarGroupsFlags_None",                    ImPlotBarGroupsFlags_None);                    m.attr("ImPlotBarGroupsFlags_None")                    = ImPlotBarGroupsFlags_::ImPlotBarGroupsFlags_None;
    e.value("ImPlotBarGroupsFlags_Horizontal",              ImPlotBarGroupsFlags_Horizontal);              m.attr("ImPlotBarGroupsFlags_Horizontal")              = ImPlotBarGroupsFlags_::ImPlotBarGroupsFlags_Horizontal;
    e.value("ImPlotBarGroupsFlags_Stacked",                 ImPlotBarGroupsFlags_Stacked);                 m.attr("ImPlotBarGroupsFlags_Stacked")                 = ImPlotBarGroupsFlags_::ImPlotBarGroupsFlags_Stacked;
  ;
  }

  { // ImPlotErrorBarsFlags_
  auto e = nb::enum_<ImPlotErrorBarsFlags_>(m, "ImPlotErrorBarsFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotErrorBarsFlags_None",                    ImPlotErrorBarsFlags_None);                    m.attr("ImPlotErrorBarsFlags_None")                    = ImPlotErrorBarsFlags_::ImPlotErrorBarsFlags_None;
    e.value("ImPlotErrorBarsFlags_Horizontal",              ImPlotErrorBarsFlags_Horizontal);              m.attr("ImPlotErrorBarsFlags_Horizontal")              = ImPlotErrorBarsFlags_::ImPlotErrorBarsFlags_Horizontal;
  ;
  }

  { // ImPlotStemsFlags_
  auto e = nb::enum_<ImPlotStemsFlags_>(m, "ImPlotStemsFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotStemsFlags_None",                        ImPlotStemsFlags_None);                        m.attr("ImPlotStemsFlags_None")                        = ImPlotStemsFlags_::ImPlotStemsFlags_None;
    e.value("ImPlotStemsFlags_Horizontal",                  ImPlotStemsFlags_Horizontal);                  m.attr("ImPlotStemsFlags_Horizontal")                  = ImPlotStemsFlags_::ImPlotStemsFlags_Horizontal;
  ;
  }

  { // ImPlotInfLinesFlags_
  auto e = nb::enum_<ImPlotInfLinesFlags_>(m, "ImPlotInfLinesFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotInfLinesFlags_None",                     ImPlotInfLinesFlags_None);                     m.attr("ImPlotInfLinesFlags_None")                     = ImPlotInfLinesFlags_::ImPlotInfLinesFlags_None;
    e.value("ImPlotInfLinesFlags_Horizontal",               ImPlotInfLinesFlags_Horizontal);               m.attr("ImPlotInfLinesFlags_Horizontal")               = ImPlotInfLinesFlags_::ImPlotInfLinesFlags_Horizontal;
  ;
  }

  { // ImPlotPieChartFlags_
  auto e = nb::enum_<ImPlotPieChartFlags_>(m, "ImPlotPieChartFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotPieChartFlags_None",                     ImPlotPieChartFlags_None);                     m.attr("ImPlotPieChartFlags_None")                     = ImPlotPieChartFlags_::ImPlotPieChartFlags_None;
    e.value("ImPlotPieChartFlags_Normalize",                ImPlotPieChartFlags_Normalize);                m.attr("ImPlotPieChartFlags_Normalize")                = ImPlotPieChartFlags_::ImPlotPieChartFlags_Normalize;
    e.value("ImPlotPieChartFlags_IgnoreHidden",             ImPlotPieChartFlags_IgnoreHidden);             m.attr("ImPlotPieChartFlags_IgnoreHidden")             = ImPlotPieChartFlags_::ImPlotPieChartFlags_IgnoreHidden;
    e.value("ImPlotPieChartFlags_Exploding",                ImPlotPieChartFlags_Exploding);                m.attr("ImPlotPieChartFlags_Exploding")                = ImPlotPieChartFlags_::ImPlotPieChartFlags_Exploding;
  ;
  }

  { // ImPlotHeatmapFlags_
  auto e = nb::enum_<ImPlotHeatmapFlags_>(m, "ImPlotHeatmapFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotHeatmapFlags_None",                      ImPlotHeatmapFlags_None);                      m.attr("ImPlotHeatmapFlags_None")                      = ImPlotHeatmapFlags_::ImPlotHeatmapFlags_None;
    e.value("ImPlotHeatmapFlags_ColMajor",                  ImPlotHeatmapFlags_ColMajor);                  m.attr("ImPlotHeatmapFlags_ColMajor")                  = ImPlotHeatmapFlags_::ImPlotHeatmapFlags_ColMajor;
  ;
  }

  { // ImPlotHistogramFlags_
  auto e = nb::enum_<ImPlotHistogramFlags_>(m, "ImPlotHistogramFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotHistogramFlags_None",                    ImPlotHistogramFlags_None);                    m.attr("ImPlotHistogramFlags_None")                    = ImPlotHistogramFlags_::ImPlotHistogramFlags_None;
    e.value("ImPlotHistogramFlags_Horizontal",              ImPlotHistogramFlags_Horizontal);              m.attr("ImPlotHistogramFlags_Horizontal")              = ImPlotHistogramFlags_::ImPlotHistogramFlags_Horizontal;
    e.value("ImPlotHistogramFlags_Cumulative",              ImPlotHistogramFlags_Cumulative);              m.attr("ImPlotHistogramFlags_Cumulative")              = ImPlotHistogramFlags_::ImPlotHistogramFlags_Cumulative;
    e.value("ImPlotHistogramFlags_Density",                 ImPlotHistogramFlags_Density);                 m.attr("ImPlotHistogramFlags_Density")                 = ImPlotHistogramFlags_::ImPlotHistogramFlags_Density;
    e.value("ImPlotHistogramFlags_NoOutliers",              ImPlotHistogramFlags_NoOutliers);              m.attr("ImPlotHistogramFlags_NoOutliers")              = ImPlotHistogramFlags_::ImPlotHistogramFlags_NoOutliers;
    e.value("ImPlotHistogramFlags_ColMajor",                ImPlotHistogramFlags_ColMajor);                m.attr("ImPlotHistogramFlags_ColMajor")                = ImPlotHistogramFlags_::ImPlotHistogramFlags_ColMajor;
  ;
  }

  { // ImPlotDigitalFlags_
  auto e = nb::enum_<ImPlotDigitalFlags_>(m, "ImPlotDigitalFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotDigitalFlags_None",                      ImPlotDigitalFlags_None);                      m.attr("ImPlotDigitalFlags_None")                      = ImPlotDigitalFlags_::ImPlotDigitalFlags_None;
  ;
  }

  { // ImPlotImageFlags_
  auto e = nb::enum_<ImPlotImageFlags_>(m, "ImPlotImageFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotImageFlags_None",                        ImPlotImageFlags_None);                        m.attr("ImPlotImageFlags_None")                        = ImPlotImageFlags_::ImPlotImageFlags_None;
  ;
  }

  { // ImPlotTextFlags_
  auto e = nb::enum_<ImPlotTextFlags_>(m, "ImPlotTextFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotTextFlags_None",                         ImPlotTextFlags_None);                         m.attr("ImPlotTextFlags_None")                         = ImPlotTextFlags_::ImPlotTextFlags_None;
    e.value("ImPlotTextFlags_Vertical",                     ImPlotTextFlags_Vertical);                     m.attr("ImPlotTextFlags_Vertical")                     = ImPlotTextFlags_::ImPlotTextFlags_Vertical;
  ;
  }

  { // ImPlotDummyFlags_
  auto e = nb::enum_<ImPlotDummyFlags_>(m, "ImPlotDummyFlags_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotDummyFlags_None",                        ImPlotDummyFlags_None);                        m.attr("ImPlotDummyFlags_None")                        = ImPlotDummyFlags_::ImPlotDummyFlags_None;
  ;
  }

  { // ImPlotCond_
  auto e = nb::enum_<ImPlotCond_>(m, "ImPlotCond_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotCond_None",                              ImPlotCond_None);                              m.attr("ImPlotCond_None")                              = ImPlotCond_::ImPlotCond_None;
    e.value("ImPlotCond_Always",                            ImPlotCond_Always);                            m.attr("ImPlotCond_Always")                            = ImPlotCond_::ImPlotCond_Always;
    e.value("ImPlotCond_Once",                              ImPlotCond_Once);                              m.attr("ImPlotCond_Once")                              = ImPlotCond_::ImPlotCond_Once;
  ;
  }

  { // ImPlotCol_
  auto e = nb::enum_<ImPlotCol_>(m, "ImPlotCol_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotCol_Line",                               ImPlotCol_Line);                               m.attr("ImPlotCol_Line")                               = ImPlotCol_::ImPlotCol_Line;
    e.value("ImPlotCol_Fill",                               ImPlotCol_Fill);                               m.attr("ImPlotCol_Fill")                               = ImPlotCol_::ImPlotCol_Fill;
    e.value("ImPlotCol_MarkerOutline",                      ImPlotCol_MarkerOutline);                      m.attr("ImPlotCol_MarkerOutline")                      = ImPlotCol_::ImPlotCol_MarkerOutline;
    e.value("ImPlotCol_MarkerFill",                         ImPlotCol_MarkerFill);                         m.attr("ImPlotCol_MarkerFill")                         = ImPlotCol_::ImPlotCol_MarkerFill;
    e.value("ImPlotCol_ErrorBar",                           ImPlotCol_ErrorBar);                           m.attr("ImPlotCol_ErrorBar")                           = ImPlotCol_::ImPlotCol_ErrorBar;
    e.value("ImPlotCol_FrameBg",                            ImPlotCol_FrameBg);                            m.attr("ImPlotCol_FrameBg")                            = ImPlotCol_::ImPlotCol_FrameBg;
    e.value("ImPlotCol_PlotBg",                             ImPlotCol_PlotBg);                             m.attr("ImPlotCol_PlotBg")                             = ImPlotCol_::ImPlotCol_PlotBg;
    e.value("ImPlotCol_PlotBorder",                         ImPlotCol_PlotBorder);                         m.attr("ImPlotCol_PlotBorder")                         = ImPlotCol_::ImPlotCol_PlotBorder;
    e.value("ImPlotCol_LegendBg",                           ImPlotCol_LegendBg);                           m.attr("ImPlotCol_LegendBg")                           = ImPlotCol_::ImPlotCol_LegendBg;
    e.value("ImPlotCol_LegendBorder",                       ImPlotCol_LegendBorder);                       m.attr("ImPlotCol_LegendBorder")                       = ImPlotCol_::ImPlotCol_LegendBorder;
    e.value("ImPlotCol_LegendText",                         ImPlotCol_LegendText);                         m.attr("ImPlotCol_LegendText")                         = ImPlotCol_::ImPlotCol_LegendText;
    e.value("ImPlotCol_TitleText",                          ImPlotCol_TitleText);                          m.attr("ImPlotCol_TitleText")                          = ImPlotCol_::ImPlotCol_TitleText;
    e.value("ImPlotCol_InlayText",                          ImPlotCol_InlayText);                          m.attr("ImPlotCol_InlayText")                          = ImPlotCol_::ImPlotCol_InlayText;
    e.value("ImPlotCol_AxisText",                           ImPlotCol_AxisText);                           m.attr("ImPlotCol_AxisText")                           = ImPlotCol_::ImPlotCol_AxisText;
    e.value("ImPlotCol_AxisGrid",                           ImPlotCol_AxisGrid);                           m.attr("ImPlotCol_AxisGrid")                           = ImPlotCol_::ImPlotCol_AxisGrid;
    e.value("ImPlotCol_AxisTick",                           ImPlotCol_AxisTick);                           m.attr("ImPlotCol_AxisTick")                           = ImPlotCol_::ImPlotCol_AxisTick;
    e.value("ImPlotCol_AxisBg",                             ImPlotCol_AxisBg);                             m.attr("ImPlotCol_AxisBg")                             = ImPlotCol_::ImPlotCol_AxisBg;
    e.value("ImPlotCol_AxisBgHovered",                      ImPlotCol_AxisBgHovered);                      m.attr("ImPlotCol_AxisBgHovered")                      = ImPlotCol_::ImPlotCol_AxisBgHovered;
    e.value("ImPlotCol_AxisBgActive",                       ImPlotCol_AxisBgActive);                       m.attr("ImPlotCol_AxisBgActive")                       = ImPlotCol_::ImPlotCol_AxisBgActive;
    e.value("ImPlotCol_Selection",                          ImPlotCol_Selection);                          m.attr("ImPlotCol_Selection")                          = ImPlotCol_::ImPlotCol_Selection;
    e.value("ImPlotCol_Crosshairs",                         ImPlotCol_Crosshairs);                         m.attr("ImPlotCol_Crosshairs")                         = ImPlotCol_::ImPlotCol_Crosshairs;
    e.value("ImPlotCol_COUNT",                              ImPlotCol_COUNT);                              m.attr("ImPlotCol_COUNT")                              = ImPlotCol_::ImPlotCol_COUNT;
  ;
  }

  { // ImPlotStyleVar_
  auto e = nb::enum_<ImPlotStyleVar_>(m, "ImPlotStyleVar_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotStyleVar_LineWeight",                    ImPlotStyleVar_LineWeight);                    m.attr("ImPlotStyleVar_LineWeight")                    = ImPlotStyleVar_::ImPlotStyleVar_LineWeight;
    e.value("ImPlotStyleVar_Marker",                        ImPlotStyleVar_Marker);                        m.attr("ImPlotStyleVar_Marker")                        = ImPlotStyleVar_::ImPlotStyleVar_Marker;
    e.value("ImPlotStyleVar_MarkerSize",                    ImPlotStyleVar_MarkerSize);                    m.attr("ImPlotStyleVar_MarkerSize")                    = ImPlotStyleVar_::ImPlotStyleVar_MarkerSize;
    e.value("ImPlotStyleVar_MarkerWeight",                  ImPlotStyleVar_MarkerWeight);                  m.attr("ImPlotStyleVar_MarkerWeight")                  = ImPlotStyleVar_::ImPlotStyleVar_MarkerWeight;
    e.value("ImPlotStyleVar_FillAlpha",                     ImPlotStyleVar_FillAlpha);                     m.attr("ImPlotStyleVar_FillAlpha")                     = ImPlotStyleVar_::ImPlotStyleVar_FillAlpha;
    e.value("ImPlotStyleVar_ErrorBarSize",                  ImPlotStyleVar_ErrorBarSize);                  m.attr("ImPlotStyleVar_ErrorBarSize")                  = ImPlotStyleVar_::ImPlotStyleVar_ErrorBarSize;
    e.value("ImPlotStyleVar_ErrorBarWeight",                ImPlotStyleVar_ErrorBarWeight);                m.attr("ImPlotStyleVar_ErrorBarWeight")                = ImPlotStyleVar_::ImPlotStyleVar_ErrorBarWeight;
    e.value("ImPlotStyleVar_DigitalBitHeight",              ImPlotStyleVar_DigitalBitHeight);              m.attr("ImPlotStyleVar_DigitalBitHeight")              = ImPlotStyleVar_::ImPlotStyleVar_DigitalBitHeight;
    e.value("ImPlotStyleVar_DigitalBitGap",                 ImPlotStyleVar_DigitalBitGap);                 m.attr("ImPlotStyleVar_DigitalBitGap")                 = ImPlotStyleVar_::ImPlotStyleVar_DigitalBitGap;
    e.value("ImPlotStyleVar_PlotBorderSize",                ImPlotStyleVar_PlotBorderSize);                m.attr("ImPlotStyleVar_PlotBorderSize")                = ImPlotStyleVar_::ImPlotStyleVar_PlotBorderSize;
    e.value("ImPlotStyleVar_MinorAlpha",                    ImPlotStyleVar_MinorAlpha);                    m.attr("ImPlotStyleVar_MinorAlpha")                    = ImPlotStyleVar_::ImPlotStyleVar_MinorAlpha;
    e.value("ImPlotStyleVar_MajorTickLen",                  ImPlotStyleVar_MajorTickLen);                  m.attr("ImPlotStyleVar_MajorTickLen")                  = ImPlotStyleVar_::ImPlotStyleVar_MajorTickLen;
    e.value("ImPlotStyleVar_MinorTickLen",                  ImPlotStyleVar_MinorTickLen);                  m.attr("ImPlotStyleVar_MinorTickLen")                  = ImPlotStyleVar_::ImPlotStyleVar_MinorTickLen;
    e.value("ImPlotStyleVar_MajorTickSize",                 ImPlotStyleVar_MajorTickSize);                 m.attr("ImPlotStyleVar_MajorTickSize")                 = ImPlotStyleVar_::ImPlotStyleVar_MajorTickSize;
    e.value("ImPlotStyleVar_MinorTickSize",                 ImPlotStyleVar_MinorTickSize);                 m.attr("ImPlotStyleVar_MinorTickSize")                 = ImPlotStyleVar_::ImPlotStyleVar_MinorTickSize;
    e.value("ImPlotStyleVar_MajorGridSize",                 ImPlotStyleVar_MajorGridSize);                 m.attr("ImPlotStyleVar_MajorGridSize")                 = ImPlotStyleVar_::ImPlotStyleVar_MajorGridSize;
    e.value("ImPlotStyleVar_MinorGridSize",                 ImPlotStyleVar_MinorGridSize);                 m.attr("ImPlotStyleVar_MinorGridSize")                 = ImPlotStyleVar_::ImPlotStyleVar_MinorGridSize;
    e.value("ImPlotStyleVar_PlotPadding",                   ImPlotStyleVar_PlotPadding);                   m.attr("ImPlotStyleVar_PlotPadding")                   = ImPlotStyleVar_::ImPlotStyleVar_PlotPadding;
    e.value("ImPlotStyleVar_LabelPadding",                  ImPlotStyleVar_LabelPadding);                  m.attr("ImPlotStyleVar_LabelPadding")                  = ImPlotStyleVar_::ImPlotStyleVar_LabelPadding;
    e.value("ImPlotStyleVar_LegendPadding",                 ImPlotStyleVar_LegendPadding);                 m.attr("ImPlotStyleVar_LegendPadding")                 = ImPlotStyleVar_::ImPlotStyleVar_LegendPadding;
    e.value("ImPlotStyleVar_LegendInnerPadding",            ImPlotStyleVar_LegendInnerPadding);            m.attr("ImPlotStyleVar_LegendInnerPadding")            = ImPlotStyleVar_::ImPlotStyleVar_LegendInnerPadding;
    e.value("ImPlotStyleVar_LegendSpacing",                 ImPlotStyleVar_LegendSpacing);                 m.attr("ImPlotStyleVar_LegendSpacing")                 = ImPlotStyleVar_::ImPlotStyleVar_LegendSpacing;
    e.value("ImPlotStyleVar_MousePosPadding",               ImPlotStyleVar_MousePosPadding);               m.attr("ImPlotStyleVar_MousePosPadding")               = ImPlotStyleVar_::ImPlotStyleVar_MousePosPadding;
    e.value("ImPlotStyleVar_AnnotationPadding",             ImPlotStyleVar_AnnotationPadding);             m.attr("ImPlotStyleVar_AnnotationPadding")             = ImPlotStyleVar_::ImPlotStyleVar_AnnotationPadding;
    e.value("ImPlotStyleVar_FitPadding",                    ImPlotStyleVar_FitPadding);                    m.attr("ImPlotStyleVar_FitPadding")                    = ImPlotStyleVar_::ImPlotStyleVar_FitPadding;
    e.value("ImPlotStyleVar_PlotDefaultSize",               ImPlotStyleVar_PlotDefaultSize);               m.attr("ImPlotStyleVar_PlotDefaultSize")               = ImPlotStyleVar_::ImPlotStyleVar_PlotDefaultSize;
    e.value("ImPlotStyleVar_PlotMinSize",                   ImPlotStyleVar_PlotMinSize);                   m.attr("ImPlotStyleVar_PlotMinSize")                   = ImPlotStyleVar_::ImPlotStyleVar_PlotMinSize;
    e.value("ImPlotStyleVar_COUNT",                         ImPlotStyleVar_COUNT);                         m.attr("ImPlotStyleVar_COUNT")                         = ImPlotStyleVar_::ImPlotStyleVar_COUNT;
  ;
  }

  { // ImPlotScale_
  auto e = nb::enum_<ImPlotScale_>(m, "ImPlotScale_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotScale_Linear",                           ImPlotScale_Linear);                           m.attr("ImPlotScale_Linear")                           = ImPlotScale_::ImPlotScale_Linear;
    e.value("ImPlotScale_Time",                             ImPlotScale_Time);                             m.attr("ImPlotScale_Time")                             = ImPlotScale_::ImPlotScale_Time;
    e.value("ImPlotScale_Log10",                            ImPlotScale_Log10);                            m.attr("ImPlotScale_Log10")                            = ImPlotScale_::ImPlotScale_Log10;
    e.value("ImPlotScale_SymLog",                           ImPlotScale_SymLog);                           m.attr("ImPlotScale_SymLog")                           = ImPlotScale_::ImPlotScale_SymLog;
  ;
  }

  { // ImPlotMarker_
  auto e = nb::enum_<ImPlotMarker_>(m, "ImPlotMarker_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotMarker_None",                            ImPlotMarker_None);                            m.attr("ImPlotMarker_None")                            = ImPlotMarker_::ImPlotMarker_None;
    e.value("ImPlotMarker_Circle",                          ImPlotMarker_Circle);                          m.attr("ImPlotMarker_Circle")                          = ImPlotMarker_::ImPlotMarker_Circle;
    e.value("ImPlotMarker_Square",                          ImPlotMarker_Square);                          m.attr("ImPlotMarker_Square")                          = ImPlotMarker_::ImPlotMarker_Square;
    e.value("ImPlotMarker_Diamond",                         ImPlotMarker_Diamond);                         m.attr("ImPlotMarker_Diamond")                         = ImPlotMarker_::ImPlotMarker_Diamond;
    e.value("ImPlotMarker_Up",                              ImPlotMarker_Up);                              m.attr("ImPlotMarker_Up")                              = ImPlotMarker_::ImPlotMarker_Up;
    e.value("ImPlotMarker_Down",                            ImPlotMarker_Down);                            m.attr("ImPlotMarker_Down")                            = ImPlotMarker_::ImPlotMarker_Down;
    e.value("ImPlotMarker_Left",                            ImPlotMarker_Left);                            m.attr("ImPlotMarker_Left")                            = ImPlotMarker_::ImPlotMarker_Left;
    e.value("ImPlotMarker_Right",                           ImPlotMarker_Right);                           m.attr("ImPlotMarker_Right")                           = ImPlotMarker_::ImPlotMarker_Right;
    e.value("ImPlotMarker_Cross",                           ImPlotMarker_Cross);                           m.attr("ImPlotMarker_Cross")                           = ImPlotMarker_::ImPlotMarker_Cross;
    e.value("ImPlotMarker_Plus",                            ImPlotMarker_Plus);                            m.attr("ImPlotMarker_Plus")                            = ImPlotMarker_::ImPlotMarker_Plus;
    e.value("ImPlotMarker_Asterisk",                        ImPlotMarker_Asterisk);                        m.attr("ImPlotMarker_Asterisk")                        = ImPlotMarker_::ImPlotMarker_Asterisk;
    e.value("ImPlotMarker_COUNT",                           ImPlotMarker_COUNT);                           m.attr("ImPlotMarker_COUNT")                           = ImPlotMarker_::ImPlotMarker_COUNT;
  ;
  }

  { // ImPlotColormap_
  auto e = nb::enum_<ImPlotColormap_>(m, "ImPlotColormap_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotColormap_Deep",                          ImPlotColormap_Deep);                          m.attr("ImPlotColormap_Deep")                          = ImPlotColormap_::ImPlotColormap_Deep;
    e.value("ImPlotColormap_Dark",                          ImPlotColormap_Dark);                          m.attr("ImPlotColormap_Dark")                          = ImPlotColormap_::ImPlotColormap_Dark;
    e.value("ImPlotColormap_Pastel",                        ImPlotColormap_Pastel);                        m.attr("ImPlotColormap_Pastel")                        = ImPlotColormap_::ImPlotColormap_Pastel;
    e.value("ImPlotColormap_Paired",                        ImPlotColormap_Paired);                        m.attr("ImPlotColormap_Paired")                        = ImPlotColormap_::ImPlotColormap_Paired;
    e.value("ImPlotColormap_Viridis",                       ImPlotColormap_Viridis);                       m.attr("ImPlotColormap_Viridis")                       = ImPlotColormap_::ImPlotColormap_Viridis;
    e.value("ImPlotColormap_Plasma",                        ImPlotColormap_Plasma);                        m.attr("ImPlotColormap_Plasma")                        = ImPlotColormap_::ImPlotColormap_Plasma;
    e.value("ImPlotColormap_Hot",                           ImPlotColormap_Hot);                           m.attr("ImPlotColormap_Hot")                           = ImPlotColormap_::ImPlotColormap_Hot;
    e.value("ImPlotColormap_Cool",                          ImPlotColormap_Cool);                          m.attr("ImPlotColormap_Cool")                          = ImPlotColormap_::ImPlotColormap_Cool;
    e.value("ImPlotColormap_Pink",                          ImPlotColormap_Pink);                          m.attr("ImPlotColormap_Pink")                          = ImPlotColormap_::ImPlotColormap_Pink;
    e.value("ImPlotColormap_Jet",                           ImPlotColormap_Jet);                           m.attr("ImPlotColormap_Jet")                           = ImPlotColormap_::ImPlotColormap_Jet;
    e.value("ImPlotColormap_Twilight",                      ImPlotColormap_Twilight);                      m.attr("ImPlotColormap_Twilight")                      = ImPlotColormap_::ImPlotColormap_Twilight;
    e.value("ImPlotColormap_RdBu",                          ImPlotColormap_RdBu);                          m.attr("ImPlotColormap_RdBu")                          = ImPlotColormap_::ImPlotColormap_RdBu;
    e.value("ImPlotColormap_BrBG",                          ImPlotColormap_BrBG);                          m.attr("ImPlotColormap_BrBG")                          = ImPlotColormap_::ImPlotColormap_BrBG;
    e.value("ImPlotColormap_PiYG",                          ImPlotColormap_PiYG);                          m.attr("ImPlotColormap_PiYG")                          = ImPlotColormap_::ImPlotColormap_PiYG;
    e.value("ImPlotColormap_Spectral",                      ImPlotColormap_Spectral);                      m.attr("ImPlotColormap_Spectral")                      = ImPlotColormap_::ImPlotColormap_Spectral;
    e.value("ImPlotColormap_Greys",                         ImPlotColormap_Greys);                         m.attr("ImPlotColormap_Greys")                         = ImPlotColormap_::ImPlotColormap_Greys;
  ;
  }

  { // ImPlotLocation_
  auto e = nb::enum_<ImPlotLocation_>(m, "ImPlotLocation_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotLocation_Center",                        ImPlotLocation_Center);                        m.attr("ImPlotLocation_Center")                        = ImPlotLocation_::ImPlotLocation_Center;
    e.value("ImPlotLocation_North",                         ImPlotLocation_North);                         m.attr("ImPlotLocation_North")                         = ImPlotLocation_::ImPlotLocation_North;
    e.value("ImPlotLocation_South",                         ImPlotLocation_South);                         m.attr("ImPlotLocation_South")                         = ImPlotLocation_::ImPlotLocation_South;
    e.value("ImPlotLocation_West",                          ImPlotLocation_West);                          m.attr("ImPlotLocation_West")                          = ImPlotLocation_::ImPlotLocation_West;
    e.value("ImPlotLocation_East",                          ImPlotLocation_East);                          m.attr("ImPlotLocation_East")                          = ImPlotLocation_::ImPlotLocation_East;
    e.value("ImPlotLocation_NorthWest",                     ImPlotLocation_NorthWest);                     m.attr("ImPlotLocation_NorthWest")                     = ImPlotLocation_::ImPlotLocation_NorthWest;
    e.value("ImPlotLocation_NorthEast",                     ImPlotLocation_NorthEast);                     m.attr("ImPlotLocation_NorthEast")                     = ImPlotLocation_::ImPlotLocation_NorthEast;
    e.value("ImPlotLocation_SouthWest",                     ImPlotLocation_SouthWest);                     m.attr("ImPlotLocation_SouthWest")                     = ImPlotLocation_::ImPlotLocation_SouthWest;
    e.value("ImPlotLocation_SouthEast",                     ImPlotLocation_SouthEast);                     m.attr("ImPlotLocation_SouthEast")                     = ImPlotLocation_::ImPlotLocation_SouthEast;
  ;
  }

  { // ImPlotBin_
  auto e = nb::enum_<ImPlotBin_>(m, "ImPlotBin_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotBin_Sqrt",                               ImPlotBin_Sqrt);                               m.attr("ImPlotBin_Sqrt")                               = ImPlotBin_::ImPlotBin_Sqrt;
    e.value("ImPlotBin_Sturges",                            ImPlotBin_Sturges);                            m.attr("ImPlotBin_Sturges")                            = ImPlotBin_::ImPlotBin_Sturges;
    e.value("ImPlotBin_Rice",                               ImPlotBin_Rice);                               m.attr("ImPlotBin_Rice")                               = ImPlotBin_::ImPlotBin_Rice;
    e.value("ImPlotBin_Scott",                              ImPlotBin_Scott);                              m.attr("ImPlotBin_Scott")                              = ImPlotBin_::ImPlotBin_Scott;
  ;
  }

  { // ImPlotFlagsObsolete_
  auto e = nb::enum_<ImPlotFlagsObsolete_>(m, "ImPlotFlagsObsolete_", nb::is_arithmetic(), nb::is_flag());
    e.value("ImPlotFlags_YAxis2",                           ImPlotFlags_YAxis2);                           m.attr("ImPlotFlags_YAxis2")                           = ImPlotFlagsObsolete_::ImPlotFlags_YAxis2;
    e.value("ImPlotFlags_YAxis3",                           ImPlotFlags_YAxis3);                           m.attr("ImPlotFlags_YAxis3")                           = ImPlotFlagsObsolete_::ImPlotFlags_YAxis3;
  ;
  }

}
