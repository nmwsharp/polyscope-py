#include "imgui.h"
#include "implot.h"

#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "utils.h"
#include "imgui_utils.h"

namespace py = pybind11;

void bind_implot_structs(py::module& m);
void bind_implot_methods(py::module& m);
void bind_implot_enums(py::module& m);

void bind_implot(py::module& m) {
  auto implot_module = m.def_submodule("implot", "ImPlot bindings");

  bind_implot_structs(implot_module);
  bind_implot_methods(implot_module);
  bind_implot_enums(implot_module);
}

// clang-format off

void bind_implot_structs(py::module& m) {



}

void bind_implot_methods(py::module& m) {
    
    //-----------------------------------------------------------------------------
    // [SECTION] Begin/End Plot
    //-----------------------------------------------------------------------------

    m.def(
        "BeginPlot",
        [](const char* title_id, const Vec2T& size, ImPlotFlags flags) {
            return ImPlot::BeginPlot(title_id, to_vec2(size), flags);
        },
        py::arg("title_id"),
        py::arg("size") = std::make_tuple(-1.f, 0.f),
        py::arg("flags") = 0
    );

    m.def("EndPlot", []() { ImPlot::EndPlot(); });

    m.def(
        "BeginSubplots",
        [](const char* title_id, int rows, int cols, const Vec2T& size, ImPlotSubplotFlags flags, std::vector<float> row_ratios, std::vector<float> col_ratios) {

            float* row_ratios_ptr = nullptr;
            float* col_ratios_ptr = nullptr;
            if(row_ratios.size() > 0) {
                if((int)row_ratios.size() != rows) throw std::runtime_error("invalid row_ratios size");
                row_ratios_ptr = row_ratios.data();
            }
            if(col_ratios.size() > 0) {
                if((int)col_ratios.size() != cols) throw std::runtime_error("invalid col_ratios size");
                col_ratios_ptr = col_ratios.data();
            }

            return ImPlot::BeginSubplots(title_id, rows, cols, to_vec2(size), flags, row_ratios_ptr, col_ratios_ptr);
        },
        py::arg("title_id"),
        py::arg("rows"),
        py::arg("cols"),
        py::arg("size") = std::make_tuple(-1.f, 0.f),
        py::arg("flags") = 0,
        py::arg("row_ratios") = std::vector<float>(),
        py::arg("col_ratios") = std::vector<float>()
    );

    m.def("EndSubplots", []() { ImPlot::EndSubplots(); });


    //-----------------------------------------------------------------------------
    // [SECTION] Setup
    //-----------------------------------------------------------------------------
    
    m.def(
        "SetupAxis",
        [](ImAxis axis, const char* label, ImPlotAxisFlags flags) {
            ImPlot::SetupAxis(axis, label, flags);
        },
        py::arg("axis"),
        py::arg("label") = "",
        py::arg("flags") = 0
    );

    m.def(
        "SetupAxisLimits",
        [](ImAxis axis, double v_min, double v_max, ImPlotCond cond) {
            ImPlot::SetupAxisLimits(axis, v_min, v_max, cond);
        },
        py::arg("axis"),
        py::arg("vmin"),
        py::arg("vmax"),
        py::arg("cond") = (int)ImPlotCond_Once
    );

    m.def(
        "SetupAxisFormat",
        [](ImAxis axis, const char* fmt) {
            ImPlot::SetupAxisFormat(axis, fmt);
        },
        py::arg("axis"),
        py::arg("fmt")
    );

    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, const Eigen::VectorXd& values, const std::vector<std::string>& labels, bool keep_default) {
            if(labels.size() > 0 && (labels.size() != values.size())) throw std::runtime_error("input sizes don't match");
            const auto _labels = convert_string_items(labels);
            ImPlot::SetupAxisTicks(axis, values.data(), values.size(), labels.size() == 0 ? nullptr : _labels.data(), keep_default);
        },
        py::arg("axis"),
        py::arg("values"),
        py::arg("labels") = std::vector<std::string>(),
        py::arg("keep_default") = false
    );

    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, double v_min, double v_max, int n_ticks, const std::vector<std::string>& labels, bool keep_default) {
            if(labels.size() > 0 && (labels.size() != n_ticks)) throw std::runtime_error("input sizes don't match");
            const auto _labels = convert_string_items(labels);
            ImPlot::SetupAxisTicks(axis, v_min, v_max, n_ticks, labels.size() == 0 ? nullptr : _labels.data(), keep_default);
        },
        py::arg("axis"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("n_ticks"),
        py::arg("labels") = std::vector<std::string>(),
        py::arg("keep_default") = false
    );

    m.def(
        "SetupAxisScale",
        [](ImAxis axis, ImPlotScale scale) {
            ImPlot::SetupAxisScale(axis, scale);
        },
        py::arg("axis"),
        py::arg("scale")
    );

    m.def(
        "SetupAxisLimitsConstraints",
        [](ImAxis axis, double v_min, double v_max) {
            ImPlot::SetupAxisLimitsConstraints(axis, v_min, v_max);
        },
        py::arg("axis"),
        py::arg("v_min"),
        py::arg("v_max")
    );

    m.def(
        "SetupAxisZoomConstraints",
        [](ImAxis axis, double z_min, double z_max) {
            ImPlot::SetupAxisZoomConstraints(axis, z_min, z_max);
        },
        py::arg("axis"),
        py::arg("z_min"),
        py::arg("z_max")
    );

    m.def(
        "SetupAxes",
        [](const char* x_label, const char* y_label, ImPlotAxisFlags x_flags, ImPlotAxisFlags y_flags) {
            ImPlot::SetupAxes(x_label, y_label, x_flags, y_flags);
        },
        py::arg("x_label"),
        py::arg("y_label"),
        py::arg("x_flags") = 0,
        py::arg("y_flags") = 0
    );

    m.def(
        "SetupAxesLimits",
        [](double x_min, double x_max, double y_min, double y_max, ImPlotCond cond) {
            ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max, cond);
        },
        py::arg("x_min"),
        py::arg("x_max"),
        py::arg("y_min"),
        py::arg("y_max"),
        py::arg("cond") = (int)ImPlotCond_Once
    );

    m.def(
        "SetupLegend",
        [](ImPlotLocation location, ImPlotLegendFlags flags) {
            ImPlot::SetupLegend(location, flags);
        },
        py::arg("location"),
        py::arg("flags") = 0
    );

    m.def(
        "SetupMouseText",
        [](ImPlotLocation location, ImPlotMouseTextFlags flags) {
            ImPlot::SetupMouseText(location, flags);
        },
        py::arg("location"),
        py::arg("flags") = 0
    );


    m.def(
        "SetupFinish",
        []() {
            ImPlot::SetupFinish();
        }
    );


    //-----------------------------------------------------------------------------
    // [SECTION] Plot Items
    //-----------------------------------------------------------------------------

    // PlotLine

    m.def(
        "PlotLine",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotLineFlags flags) {
            ImPlot::PlotLine(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("xscale")=1.,
        py::arg("xstart")=0.,
        py::arg("flags")=0
    );
    
    m.def(
        "PlotLine",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotLineFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotLine(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        py::arg("label_id"),
        py::arg("xs"),
        py::arg("ys"),
        py::arg("flags") = 0
    );
    
    // PlotScatter

    m.def(
        "PlotScatter",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotScatterFlags flags) {
            ImPlot::PlotScatter(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("xscale")=1.,
        py::arg("xstart")=0.,
        py::arg("flags")=0
    );
    
    m.def(
        "PlotScatter",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotScatterFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotScatter(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        py::arg("label_id"),
        py::arg("xs"),
        py::arg("ys"),
        py::arg("flags") = 0
    );

    // PlotStairs

    m.def(
        "PlotStairs",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotStairsFlags flags) {
            ImPlot::PlotStairs(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("xscale")=1.,
        py::arg("xstart")=0.,
        py::arg("flags")=0
    );
    
    m.def(
        "PlotStairs",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotStairsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotStairs(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        py::arg("label_id"),
        py::arg("xs"),
        py::arg("ys"),
        py::arg("flags") = 0
    );

    // PlotShaded TODO
    
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& values, double yref, double xscale, double xstart, ImPlotShadedFlags flags) {
            ImPlot::PlotShaded(label_id, values.data(), values.size(), yref, xscale, xstart, flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("yref")=0.,
        py::arg("xscale")=1.,
        py::arg("xstart")=0.,
        py::arg("flags")=0
    );
    
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, double yref, ImPlotShadedFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotShaded(label_id, xs.data(), ys.data(), xs.size(), yref, flags);
        },
        py::arg("label_id"),
        py::arg("xs"),
        py::arg("ys"),
        py::arg("yref")=0.,
        py::arg("flags") = 0
    );
    
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys1, const Eigen::VectorXd& ys2, ImPlotShadedFlags flags) {
            if(xs.size() != ys1.size()) throw std::runtime_error("invalid input sizes");
            if(xs.size() != ys2.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotShaded(label_id, xs.data(), ys1.data(), ys2.data(), xs.size(), flags);
        },
        py::arg("label_id"),
        py::arg("xs"),
        py::arg("ys1"),
        py::arg("ys2"),
        py::arg("flags") = 0
    );

    // PlotBars TODO
    
    // PlotBarGroups TODO
    
    // PlotErrorBars TODO
    
    // PlotStems TODO
    
    // PlotInfLines
    
    m.def(
        "PlotInfLines",
        [](const char* label_id, const Eigen::VectorXd& values, ImPlotInfLinesFlags flags) {
            ImPlot::PlotInfLines(label_id, values.data(), values.size(), flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("flags")=0
    );
    
    // PlotPieChart
    m.def(
        "PlotPieChart",
        [](const std::vector<std::string>& label_ids, const Eigen::VectorXd& values, double x, double y, double radius, const char* label_fmt, double angle0, ImPlotPieChartFlags flags) {
            if(label_ids.size() != values.size()) throw std::runtime_error("input sizes don't match");
            const auto _label_ids = convert_string_items(label_ids);
            ImPlot::PlotPieChart(_label_ids.data(), values.data(), values.size(), x, y, radius, label_fmt, angle0, flags);
        },
        py::arg("label_ids"),
        py::arg("values"),
        py::arg("x"),
        py::arg("y"),
        py::arg("radius"),
        py::arg("label_fmt") = "%.1f",
        py::arg("angle0") = 90,
        py::arg("flags") = 0
    );
    

    // PlotHeatMap TODO
    
    // PlotHistogram
    
    m.def(
        "PlotHistogram",
        [](const char* label_id, const Eigen::VectorXd& values, int bins, double bar_scale, const Vec2T& range, ImPlotHistogramFlags flags) {
            ImPlotRange imrange(std::get<0>(range), std::get<1>(range));
            ImPlot::PlotHistogram(label_id, values.data(), values.size(), bins, bar_scale, imrange, flags);
        },
        py::arg("label_id"),
        py::arg("values"),
        py::arg("bins") = (int)ImPlotBin_Sturges,
        py::arg("bar_scale") = 1.0,
        py::arg("range") = std::make_tuple(0.f, 0.f),
        py::arg("flags") = 0
    );
    
    // PlotHistogram2D TODO
    
    // PlotDigital TODO
    
    // PlotImage TODO
    
    // PlotText TODO
    
    // PlotDummy TODO


    //-----------------------------------------------------------------------------
    // [SECTION] Plot Tools
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Plot Utils
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Legend Utils
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Drag and Drop
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Styling
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Colormaps
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Miscellaneous
    //-----------------------------------------------------------------------------
}

void bind_implot_enums(py::module& m) {

    // ImAxis
    m.attr("ImAxis_X1") = static_cast<int>(ImAxis_X1);
    m.attr("ImAxis_X2") = static_cast<int>(ImAxis_X2);
    m.attr("ImAxis_X3") = static_cast<int>(ImAxis_X3);
    m.attr("ImAxis_Y1") = static_cast<int>(ImAxis_Y1);
    m.attr("ImAxis_Y2") = static_cast<int>(ImAxis_Y2);
    m.attr("ImAxis_Y3") = static_cast<int>(ImAxis_Y3);
    m.attr("ImAxis_COUNT") = static_cast<int>(ImAxis_COUNT);

    // ImPlotFlags
    m.attr("ImPlotLineFlags_None") = static_cast<int>(ImPlotLineFlags_None);
    m.attr("ImPlotFlags_None") = static_cast<int>(ImPlotFlags_None);
    m.attr("ImPlotFlags_NoTitle") = static_cast<int>(ImPlotFlags_NoTitle);
    m.attr("ImPlotFlags_NoLegend") = static_cast<int>(ImPlotFlags_NoLegend);
    m.attr("ImPlotFlags_NoMouseText") = static_cast<int>(ImPlotFlags_NoMouseText);
    m.attr("ImPlotFlags_NoInputs") = static_cast<int>(ImPlotFlags_NoInputs);
    m.attr("ImPlotFlags_NoMenus") = static_cast<int>(ImPlotFlags_NoMenus);
    m.attr("ImPlotFlags_NoBoxSelect") = static_cast<int>(ImPlotFlags_NoBoxSelect);
    m.attr("ImPlotFlags_NoFrame") = static_cast<int>(ImPlotFlags_NoFrame);
    m.attr("ImPlotFlags_Equal") = static_cast<int>(ImPlotFlags_Equal);
    m.attr("ImPlotFlags_Crosshairs") = static_cast<int>(ImPlotFlags_Crosshairs);
    m.attr("ImPlotFlags_CanvasOnly") = static_cast<int>(ImPlotFlags_CanvasOnly);

    // ImPlotAxisFlags
    m.attr("ImPlotAxisFlags_None") = static_cast<int>(ImPlotAxisFlags_None);
    m.attr("ImPlotAxisFlags_NoLabel") = static_cast<int>(ImPlotAxisFlags_NoLabel);
    m.attr("ImPlotAxisFlags_NoGridLines") = static_cast<int>(ImPlotAxisFlags_NoGridLines);
    m.attr("ImPlotAxisFlags_NoTickMarks") = static_cast<int>(ImPlotAxisFlags_NoTickMarks);
    m.attr("ImPlotAxisFlags_NoTickLabels") = static_cast<int>(ImPlotAxisFlags_NoTickLabels);
    m.attr("ImPlotAxisFlags_NoInitialFit") = static_cast<int>(ImPlotAxisFlags_NoInitialFit);
    m.attr("ImPlotAxisFlags_NoMenus") = static_cast<int>(ImPlotAxisFlags_NoMenus);
    m.attr("ImPlotAxisFlags_NoSideSwitch") = static_cast<int>(ImPlotAxisFlags_NoSideSwitch);
    m.attr("ImPlotAxisFlags_NoHighlight") = static_cast<int>(ImPlotAxisFlags_NoHighlight);
    m.attr("ImPlotAxisFlags_Opposite") = static_cast<int>(ImPlotAxisFlags_Opposite);
    m.attr("ImPlotAxisFlags_Foreground") = static_cast<int>(ImPlotAxisFlags_Foreground);
    m.attr("ImPlotAxisFlags_Invert") = static_cast<int>(ImPlotAxisFlags_Invert);
    m.attr("ImPlotAxisFlags_AutoFit") = static_cast<int>(ImPlotAxisFlags_AutoFit);
    m.attr("ImPlotAxisFlags_RangeFit") = static_cast<int>(ImPlotAxisFlags_RangeFit);
    m.attr("ImPlotAxisFlags_PanStretch") = static_cast<int>(ImPlotAxisFlags_PanStretch);
    m.attr("ImPlotAxisFlags_LockMin") = static_cast<int>(ImPlotAxisFlags_LockMin);
    m.attr("ImPlotAxisFlags_LockMax") = static_cast<int>(ImPlotAxisFlags_LockMax);
    m.attr("ImPlotAxisFlags_Lock") = static_cast<int>(ImPlotAxisFlags_Lock);
    m.attr("ImPlotAxisFlags_NoDecorations") = static_cast<int>(ImPlotAxisFlags_NoDecorations);
    m.attr("ImPlotAxisFlags_AuxDefault") = static_cast<int>(ImPlotAxisFlags_AuxDefault);

    // ImPlotSubplotFlags
    m.attr("ImPlotSubplotFlags_None") = static_cast<int>(ImPlotSubplotFlags_None);
    m.attr("ImPlotSubplotFlags_NoTitle") = static_cast<int>(ImPlotSubplotFlags_NoTitle);
    m.attr("ImPlotSubplotFlags_NoLegend") = static_cast<int>(ImPlotSubplotFlags_NoLegend);
    m.attr("ImPlotSubplotFlags_NoMenus") = static_cast<int>(ImPlotSubplotFlags_NoMenus);
    m.attr("ImPlotSubplotFlags_NoResize") = static_cast<int>(ImPlotSubplotFlags_NoResize);
    m.attr("ImPlotSubplotFlags_NoAlign") = static_cast<int>(ImPlotSubplotFlags_NoAlign);
    m.attr("ImPlotSubplotFlags_ShareItems") = static_cast<int>(ImPlotSubplotFlags_ShareItems);
    m.attr("ImPlotSubplotFlags_LinkRows") = static_cast<int>(ImPlotSubplotFlags_LinkRows);
    m.attr("ImPlotSubplotFlags_LinkCols") = static_cast<int>(ImPlotSubplotFlags_LinkCols);
    m.attr("ImPlotSubplotFlags_LinkAllX") = static_cast<int>(ImPlotSubplotFlags_LinkAllX);
    m.attr("ImPlotSubplotFlags_LinkAllY") = static_cast<int>(ImPlotSubplotFlags_LinkAllY);
    m.attr("ImPlotSubplotFlags_ColMajor") = static_cast<int>(ImPlotSubplotFlags_ColMajor);

    // ImPlotLegendFlags
    m.attr("ImPlotLegendFlags_None") = static_cast<int>(ImPlotLegendFlags_None);
    m.attr("ImPlotLegendFlags_NoButtons") = static_cast<int>(ImPlotLegendFlags_NoButtons);
    m.attr("ImPlotLegendFlags_NoHighlightItem") = static_cast<int>(ImPlotLegendFlags_NoHighlightItem);
    m.attr("ImPlotLegendFlags_NoHighlightAxis") = static_cast<int>(ImPlotLegendFlags_NoHighlightAxis);
    m.attr("ImPlotLegendFlags_NoMenus") = static_cast<int>(ImPlotLegendFlags_NoMenus);
    m.attr("ImPlotLegendFlags_Outside") = static_cast<int>(ImPlotLegendFlags_Outside);
    m.attr("ImPlotLegendFlags_Horizontal") = static_cast<int>(ImPlotLegendFlags_Horizontal);
    m.attr("ImPlotLegendFlags_Sort") = static_cast<int>(ImPlotLegendFlags_Sort);

    // ImPlotMouseTextFlags
    m.attr("ImPlotMouseTextFlags_None") = static_cast<int>(ImPlotMouseTextFlags_None);
    m.attr("ImPlotMouseTextFlags_NoAuxAxes") = static_cast<int>(ImPlotMouseTextFlags_NoAuxAxes);
    m.attr("ImPlotMouseTextFlags_NoFormat") = static_cast<int>(ImPlotMouseTextFlags_NoFormat);
    m.attr("ImPlotMouseTextFlags_ShowAlways") = static_cast<int>(ImPlotMouseTextFlags_ShowAlways);

    // ImPlotDragToolFlags
    m.attr("ImPlotDragToolFlags_None") = static_cast<int>(ImPlotDragToolFlags_None);
    m.attr("ImPlotDragToolFlags_NoCursors") = static_cast<int>(ImPlotDragToolFlags_NoCursors);
    m.attr("ImPlotDragToolFlags_NoFit") = static_cast<int>(ImPlotDragToolFlags_NoFit);
    m.attr("ImPlotDragToolFlags_NoInputs") = static_cast<int>(ImPlotDragToolFlags_NoInputs);
    m.attr("ImPlotDragToolFlags_Delayed") = static_cast<int>(ImPlotDragToolFlags_Delayed);

    // ImPlotColormapScaleFlags
    m.attr("ImPlotColormapScaleFlags_None") = static_cast<int>(ImPlotColormapScaleFlags_None);
    m.attr("ImPlotColormapScaleFlags_NoLabel") = static_cast<int>(ImPlotColormapScaleFlags_NoLabel);
    m.attr("ImPlotColormapScaleFlags_Opposite") = static_cast<int>(ImPlotColormapScaleFlags_Opposite);
    m.attr("ImPlotColormapScaleFlags_Invert") = static_cast<int>(ImPlotColormapScaleFlags_Invert);

    // ImPlotItemFlags
    m.attr("ImPlotItemFlags_None") = static_cast<int>(ImPlotItemFlags_None);
    m.attr("ImPlotItemFlags_NoLegend") = static_cast<int>(ImPlotItemFlags_NoLegend);
    m.attr("ImPlotItemFlags_NoFit") = static_cast<int>(ImPlotItemFlags_NoFit);
 
    // ImPlotLineFlags
    m.attr("ImPlotLineFlags_None") = static_cast<int>(ImPlotLineFlags_None);
    m.attr("ImPlotLineFlags_Segments") = static_cast<int>(ImPlotLineFlags_Segments);
    m.attr("ImPlotLineFlags_Loop") = static_cast<int>(ImPlotLineFlags_Loop);
    m.attr("ImPlotLineFlags_SkipNaN") = static_cast<int>(ImPlotLineFlags_SkipNaN);
    m.attr("ImPlotLineFlags_NoClip") = static_cast<int>(ImPlotLineFlags_NoClip);
    m.attr("ImPlotLineFlags_Shaded") = static_cast<int>(ImPlotLineFlags_Shaded);

    // ImPlotScatterFlags
    m.attr("ImPlotScatterFlags_None") = static_cast<int>(ImPlotScatterFlags_None);
    m.attr("ImPlotScatterFlags_NoClip") = static_cast<int>(ImPlotScatterFlags_NoClip);

    // ImPlotStairsFlags
    m.attr("ImPlotStairsFlags_None") = static_cast<int>(ImPlotStairsFlags_None);
    m.attr("ImPlotStairsFlags_PreStep") = static_cast<int>(ImPlotStairsFlags_PreStep);
    m.attr("ImPlotStairsFlags_Shaded") = static_cast<int>(ImPlotStairsFlags_Shaded);

    // ImPlotShadedFlags
    m.attr("ImPlotShadedFlags_None") = static_cast<int>(ImPlotShadedFlags_None);

    // ImPlotBarsFlags
    m.attr("ImPlotBarsFlags_None") = static_cast<int>(ImPlotBarsFlags_None);
    m.attr("ImPlotBarsFlags_Horizontal") = static_cast<int>(ImPlotBarsFlags_Horizontal);

    // ImPlotBarGroupsFlags
    m.attr("ImPlotBarGroupsFlags_None") = static_cast<int>(ImPlotBarGroupsFlags_None);
    m.attr("ImPlotBarGroupsFlags_Horizontal") = static_cast<int>(ImPlotBarGroupsFlags_Horizontal);
    m.attr("ImPlotBarGroupsFlags_Stacked") = static_cast<int>(ImPlotBarGroupsFlags_Stacked);

    // ImPlotErrorBarsFlags
    m.attr("ImPlotErrorBarsFlags_None") = static_cast<int>(ImPlotErrorBarsFlags_None);
    m.attr("ImPlotErrorBarsFlags_Horizontal") = static_cast<int>(ImPlotErrorBarsFlags_Horizontal);

    // ImPlotStemsFlags
    m.attr("ImPlotStemsFlags_None") = static_cast<int>(ImPlotStemsFlags_None);
    m.attr("ImPlotStemsFlags_Horizontal") = static_cast<int>(ImPlotStemsFlags_Horizontal);
   
    // ImPlotInfLinesFlags
    m.attr("ImPlotInfLinesFlags_None") = static_cast<int>(ImPlotInfLinesFlags_None);
    m.attr("ImPlotInfLinesFlags_Horizontal") = static_cast<int>(ImPlotInfLinesFlags_Horizontal);

    // ImPlotPieChartFlags
    m.attr("ImPlotPieChartFlags_None") = static_cast<int>(ImPlotPieChartFlags_None);
    m.attr("ImPlotPieChartFlags_Normalize") = static_cast<int>(ImPlotPieChartFlags_Normalize);
    m.attr("ImPlotPieChartFlags_IgnoreHidden") = static_cast<int>(ImPlotPieChartFlags_IgnoreHidden);
    m.attr("ImPlotPieChartFlags_Exploding") = static_cast<int>(ImPlotPieChartFlags_Exploding);

    // ImPlotHeatmapFlags
    m.attr("ImPlotHeatmapFlags_None") = static_cast<int>(ImPlotHeatmapFlags_None);
    m.attr("ImPlotHeatmapFlags_ColMajor") = static_cast<int>(ImPlotHeatmapFlags_ColMajor);

    // ImPlotHistogramFlags
    m.attr("ImPlotHistogramFlags_None") = static_cast<int>(ImPlotHistogramFlags_None);
    m.attr("ImPlotHistogramFlags_Horizontal") = static_cast<int>(ImPlotHistogramFlags_Horizontal);
    m.attr("ImPlotHistogramFlags_Cumulative") = static_cast<int>(ImPlotHistogramFlags_Cumulative);
    m.attr("ImPlotHistogramFlags_Density") = static_cast<int>(ImPlotHistogramFlags_Density);
    m.attr("ImPlotHistogramFlags_NoOutliers") = static_cast<int>(ImPlotHistogramFlags_NoOutliers);
    m.attr("ImPlotHistogramFlags_ColMajor") = static_cast<int>(ImPlotHistogramFlags_ColMajor);

    // ImPlotDigitalFlags
    m.attr("ImPlotDigitalFlags_None") = static_cast<int>(ImPlotDigitalFlags_None);

    // ImPlotImageFlags
    m.attr("ImPlotImageFlags_None") = static_cast<int>(ImPlotImageFlags_None);

    // ImPlotTextFlags
    m.attr("ImPlotTextFlags_None") = static_cast<int>(ImPlotTextFlags_None);
    m.attr("ImPlotTextFlags_Vertical") = static_cast<int>(ImPlotTextFlags_Vertical);

    // ImPlotDummyFlags
    m.attr("ImPlotDummyFlags_None") = static_cast<int>(ImPlotDummyFlags_None);

    // ImPlotCond
    m.attr("ImPlotCond_None") = static_cast<int>(ImPlotCond_None);
    m.attr("ImPlotCond_Always") = static_cast<int>(ImPlotCond_Always);
    m.attr("ImPlotCond_Once") = static_cast<int>(ImPlotCond_Once);

    // ImPlotCol
    m.attr("ImPlotCol_Line") = static_cast<int>(ImPlotCol_Line);
    m.attr("ImPlotCol_Fill") = static_cast<int>(ImPlotCol_Fill);
    m.attr("ImPlotCol_MarkerOutline") = static_cast<int>(ImPlotCol_MarkerOutline);
    m.attr("ImPlotCol_MarkerFill") = static_cast<int>(ImPlotCol_MarkerFill);
    m.attr("ImPlotCol_ErrorBar") = static_cast<int>(ImPlotCol_ErrorBar);
    m.attr("ImPlotCol_FrameBg") = static_cast<int>(ImPlotCol_FrameBg);
    m.attr("ImPlotCol_PlotBg") = static_cast<int>(ImPlotCol_PlotBg);
    m.attr("ImPlotCol_PlotBorder") = static_cast<int>(ImPlotCol_PlotBorder);
    m.attr("ImPlotCol_LegendBg") = static_cast<int>(ImPlotCol_LegendBg);
    m.attr("ImPlotCol_LegendBorder") = static_cast<int>(ImPlotCol_LegendBorder);
    m.attr("ImPlotCol_LegendText") = static_cast<int>(ImPlotCol_LegendText);
    m.attr("ImPlotCol_TitleText") = static_cast<int>(ImPlotCol_TitleText);
    m.attr("ImPlotCol_InlayText") = static_cast<int>(ImPlotCol_InlayText);
    m.attr("ImPlotCol_AxisText") = static_cast<int>(ImPlotCol_AxisText);
    m.attr("ImPlotCol_AxisGrid") = static_cast<int>(ImPlotCol_AxisGrid);
    m.attr("ImPlotCol_AxisTick") = static_cast<int>(ImPlotCol_AxisTick);
    m.attr("ImPlotCol_AxisBg") = static_cast<int>(ImPlotCol_AxisBg);
    m.attr("ImPlotCol_AxisBgHovered") = static_cast<int>(ImPlotCol_AxisBgHovered);
    m.attr("ImPlotCol_AxisBgActive") = static_cast<int>(ImPlotCol_AxisBgActive);
    m.attr("ImPlotCol_Selection") = static_cast<int>(ImPlotCol_Selection);
    m.attr("ImPlotCol_Crosshairs") = static_cast<int>(ImPlotCol_Crosshairs);
    m.attr("ImPlotCol_COUNT") = static_cast<int>(ImPlotCol_COUNT);

    // ImPlotStyleVar
    m.attr("ImPlotStyleVar_LineWeight") = static_cast<int>(ImPlotStyleVar_LineWeight);
    m.attr("ImPlotStyleVar_Marker") = static_cast<int>(ImPlotStyleVar_Marker);
    m.attr("ImPlotStyleVar_MarkerSize") = static_cast<int>(ImPlotStyleVar_MarkerSize);
    m.attr("ImPlotStyleVar_MarkerWeight") = static_cast<int>(ImPlotStyleVar_MarkerWeight);
    m.attr("ImPlotStyleVar_FillAlpha") = static_cast<int>(ImPlotStyleVar_FillAlpha);
    m.attr("ImPlotStyleVar_ErrorBarSize") = static_cast<int>(ImPlotStyleVar_ErrorBarSize);
    m.attr("ImPlotStyleVar_ErrorBarWeight") = static_cast<int>(ImPlotStyleVar_ErrorBarWeight);
    m.attr("ImPlotStyleVar_DigitalBitHeight") = static_cast<int>(ImPlotStyleVar_DigitalBitHeight);
    m.attr("ImPlotStyleVar_DigitalBitGap") = static_cast<int>(ImPlotStyleVar_DigitalBitGap);
    m.attr("ImPlotStyleVar_PlotBorderSize") = static_cast<int>(ImPlotStyleVar_PlotBorderSize);
    m.attr("ImPlotStyleVar_MinorAlpha") = static_cast<int>(ImPlotStyleVar_MinorAlpha);
    m.attr("ImPlotStyleVar_MajorTickLen") = static_cast<int>(ImPlotStyleVar_MajorTickLen);
    m.attr("ImPlotStyleVar_MinorTickLen") = static_cast<int>(ImPlotStyleVar_MinorTickLen);
    m.attr("ImPlotStyleVar_MajorTickSize") = static_cast<int>(ImPlotStyleVar_MajorTickSize);
    m.attr("ImPlotStyleVar_MinorTickSize") = static_cast<int>(ImPlotStyleVar_MinorTickSize);
    m.attr("ImPlotStyleVar_MajorGridSize") = static_cast<int>(ImPlotStyleVar_MajorGridSize);
    m.attr("ImPlotStyleVar_MinorGridSize") = static_cast<int>(ImPlotStyleVar_MinorGridSize);
    m.attr("ImPlotStyleVar_PlotPadding") = static_cast<int>(ImPlotStyleVar_PlotPadding);
    m.attr("ImPlotStyleVar_LabelPadding") = static_cast<int>(ImPlotStyleVar_LabelPadding);
    m.attr("ImPlotStyleVar_LegendPadding") = static_cast<int>(ImPlotStyleVar_LegendPadding);
    m.attr("ImPlotStyleVar_LegendInnerPadding") = static_cast<int>(ImPlotStyleVar_LegendInnerPadding);
    m.attr("ImPlotStyleVar_LegendSpacing") = static_cast<int>(ImPlotStyleVar_LegendSpacing);
    m.attr("ImPlotStyleVar_MousePosPadding") = static_cast<int>(ImPlotStyleVar_MousePosPadding);
    m.attr("ImPlotStyleVar_AnnotationPadding") = static_cast<int>(ImPlotStyleVar_AnnotationPadding);
    m.attr("ImPlotStyleVar_FitPadding") = static_cast<int>(ImPlotStyleVar_FitPadding);
    m.attr("ImPlotStyleVar_PlotDefaultSize") = static_cast<int>(ImPlotStyleVar_PlotDefaultSize);
    m.attr("ImPlotStyleVar_PlotMinSize") = static_cast<int>(ImPlotStyleVar_PlotMinSize);
    m.attr("ImPlotStyleVar_COUNT") = static_cast<int>(ImPlotStyleVar_COUNT);

    // ImPlotScale
    m.attr("ImPlotScale_Linear") = static_cast<int>(ImPlotScale_Linear);
    m.attr("ImPlotScale_Time") = static_cast<int>(ImPlotScale_Time);
    m.attr("ImPlotScale_Log10") = static_cast<int>(ImPlotScale_Log10);
    m.attr("ImPlotScale_SymLog") = static_cast<int>(ImPlotScale_SymLog);

    // ImPlotMarker
    m.attr("ImPlotMarker_None") = static_cast<int>(ImPlotMarker_None);
    m.attr("ImPlotMarker_Circle") = static_cast<int>(ImPlotMarker_Circle);
    m.attr("ImPlotMarker_Square") = static_cast<int>(ImPlotMarker_Square);
    m.attr("ImPlotMarker_Diamond") = static_cast<int>(ImPlotMarker_Diamond);
    m.attr("ImPlotMarker_Up") = static_cast<int>(ImPlotMarker_Up);
    m.attr("ImPlotMarker_Down") = static_cast<int>(ImPlotMarker_Down);
    m.attr("ImPlotMarker_Left") = static_cast<int>(ImPlotMarker_Left);
    m.attr("ImPlotMarker_Right") = static_cast<int>(ImPlotMarker_Right);
    m.attr("ImPlotMarker_Cross") = static_cast<int>(ImPlotMarker_Cross);
    m.attr("ImPlotMarker_Plus") = static_cast<int>(ImPlotMarker_Plus);
    m.attr("ImPlotMarker_Asterisk") = static_cast<int>(ImPlotMarker_Asterisk);
    m.attr("ImPlotMarker_COUNT") = static_cast<int>(ImPlotMarker_COUNT);


    // ImPlotColormap
    m.attr("ImPlotColormap_Deep") = static_cast<int>(ImPlotColormap_Deep);
    m.attr("ImPlotColormap_Dark") = static_cast<int>(ImPlotColormap_Dark);
    m.attr("ImPlotColormap_Pastel") = static_cast<int>(ImPlotColormap_Pastel);
    m.attr("ImPlotColormap_Paired") = static_cast<int>(ImPlotColormap_Paired);
    m.attr("ImPlotColormap_Viridis") = static_cast<int>(ImPlotColormap_Viridis);
    m.attr("ImPlotColormap_Plasma") = static_cast<int>(ImPlotColormap_Plasma);
    m.attr("ImPlotColormap_Hot") = static_cast<int>(ImPlotColormap_Hot);
    m.attr("ImPlotColormap_Cool") = static_cast<int>(ImPlotColormap_Cool);
    m.attr("ImPlotColormap_Pink") = static_cast<int>(ImPlotColormap_Pink);
    m.attr("ImPlotColormap_Jet") = static_cast<int>(ImPlotColormap_Jet);
    m.attr("ImPlotColormap_Twilight") = static_cast<int>(ImPlotColormap_Twilight);
    m.attr("ImPlotColormap_RdBu") = static_cast<int>(ImPlotColormap_RdBu);
    m.attr("ImPlotColormap_BrBG") = static_cast<int>(ImPlotColormap_BrBG);
    m.attr("ImPlotColormap_PiYG") = static_cast<int>(ImPlotColormap_PiYG);
    m.attr("ImPlotColormap_Spectral") = static_cast<int>(ImPlotColormap_Spectral);
    m.attr("ImPlotColormap_Greys") = static_cast<int>(ImPlotColormap_Greys);

    // ImPlotLocation
    m.attr("ImPlotLocation_Center") = static_cast<int>(ImPlotLocation_Center);
    m.attr("ImPlotLocation_North") = static_cast<int>(ImPlotLocation_North);
    m.attr("ImPlotLocation_South") = static_cast<int>(ImPlotLocation_South);
    m.attr("ImPlotLocation_West") = static_cast<int>(ImPlotLocation_West);
    m.attr("ImPlotLocation_East") = static_cast<int>(ImPlotLocation_East);
    m.attr("ImPlotLocation_NorthWest") = static_cast<int>(ImPlotLocation_NorthWest);
    m.attr("ImPlotLocation_NorthEast") = static_cast<int>(ImPlotLocation_NorthEast);
    m.attr("ImPlotLocation_SouthWest") = static_cast<int>(ImPlotLocation_SouthWest);
    m.attr("ImPlotLocation_SouthEast") = static_cast<int>(ImPlotLocation_SouthEast);

    // ImPlotBin
    m.attr("ImPlotBin_Sqrt") = static_cast<int>(ImPlotBin_Sqrt);
    m.attr("ImPlotBin_Sturges") = static_cast<int>(ImPlotBin_Sturges);
    m.attr("ImPlotBin_Rice") = static_cast<int>(ImPlotBin_Rice);
    m.attr("ImPlotBin_Scott") = static_cast<int>(ImPlotBin_Scott);

}

// clang-format on
