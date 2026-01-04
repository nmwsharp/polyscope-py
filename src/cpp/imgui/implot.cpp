#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

void bind_implot_structs(nb::module_& m);
void bind_implot_methods(nb::module_& m);
void bind_implot_enums(nb::module_& m);

void bind_implot(nb::module_& m) {
  auto implot_module = m.def_submodule("implot", "ImPlot bindings");

  bind_implot_structs(implot_module);
  bind_implot_methods(implot_module);
  bind_implot_enums(implot_module);
}

// clang-format off

void bind_implot_structs(nb::module_& m) {

    #define VEC2_PROPERTY(name)                              \
        def_prop_rw(#name, [](const ImPlotStyle& style) {   \
            return from_vec2(style.name);                    \
        }, [](ImPlotStyle& style, const Vec2T& value) {      \
            style.name = to_vec2(value);                     \
        })

    nb::class_<ImPlotStyle>(m, "ImPlotStyle")
        // Item styling variables
        .def_rw("LineWeight", &ImPlotStyle::LineWeight)
        .def_rw("Marker", &ImPlotStyle::Marker)
        .def_rw("MarkerSize", &ImPlotStyle::MarkerSize)
        .def_rw("MarkerWeight", &ImPlotStyle::MarkerWeight)
        .def_rw("FillAlpha", &ImPlotStyle::FillAlpha)
        .def_rw("ErrorBarSize", &ImPlotStyle::ErrorBarSize)
        .def_rw("ErrorBarWeight", &ImPlotStyle::ErrorBarWeight)
        .def_rw("DigitalBitHeight", &ImPlotStyle::DigitalBitHeight)
        .def_rw("DigitalBitGap", &ImPlotStyle::DigitalBitGap)

        // Plot styling variables
        .def_rw("PlotBorderSize", &ImPlotStyle::PlotBorderSize)
        .def_rw("MinorAlpha", &ImPlotStyle::MinorAlpha)
        .VEC2_PROPERTY(MajorTickLen)
        .VEC2_PROPERTY(MinorTickLen)
        .VEC2_PROPERTY(MajorTickSize)
        .VEC2_PROPERTY(MinorTickSize)
        .VEC2_PROPERTY(MajorGridSize)
        .VEC2_PROPERTY(MinorGridSize)
        .VEC2_PROPERTY(PlotPadding)
        .VEC2_PROPERTY(LabelPadding)
        .VEC2_PROPERTY(LegendPadding)
        .VEC2_PROPERTY(LegendInnerPadding)
        .VEC2_PROPERTY(LegendSpacing)
        .VEC2_PROPERTY(MousePosPadding)
        .VEC2_PROPERTY(AnnotationPadding)
        .VEC2_PROPERTY(FitPadding)
        .VEC2_PROPERTY(PlotDefaultSize)
        .VEC2_PROPERTY(PlotMinSize)

        // Style colors
        .def("GetColor", [](const ImPlotStyle& style, int idx) {
            if (idx < 0 || idx >= ImPlotCol_COUNT) {
                throw std::out_of_range("Color index out of range: " + std::to_string(idx));
            }
            return from_vec4(style.Colors[idx]);
        }, nb::arg("idx"), "Get color by index")

        .def("SetColor", [](ImPlotStyle& style, int idx, const Vec4T& color) {
            if (idx < 0 || idx >= ImPlotCol_COUNT) {
                throw std::out_of_range("Color index out of range: " + std::to_string(idx));
            }
            style.Colors[idx] = to_vec4(color);
        }, nb::arg("idx"), nb::arg("color"), "Set color by index")

        .def("GetColorCount", [](ImPlotStyle& style) {
            return static_cast<uint32_t>(ImPlotCol_COUNT);
        }, "Get total number of colors")

        // Colormap
        .def_rw("Colormap", &ImPlotStyle::Colormap)

        // Settings/flags
        .def_rw("UseLocalTime", &ImPlotStyle::UseLocalTime)
        .def_rw("UseISO8601", &ImPlotStyle::UseISO8601)
        .def_rw("Use24HourClock", &ImPlotStyle::Use24HourClock)
    ;

    #undef VEC2_PROPERTY

    nb::class_<ImPlotInputMap>(m, "ImPlotInputMap")
        .def_rw("Pan", &ImPlotInputMap::Pan)
        .def_rw("PanMod", &ImPlotInputMap::PanMod)
        .def_rw("Fit", &ImPlotInputMap::Fit)
        .def_rw("Select", &ImPlotInputMap::Select)
        .def_rw("SelectCancel", &ImPlotInputMap::SelectCancel)
        .def_rw("SelectMod", &ImPlotInputMap::SelectMod)
        .def_rw("SelectHorzMod", &ImPlotInputMap::SelectHorzMod)
        .def_rw("SelectVertMod", &ImPlotInputMap::SelectVertMod)
        .def_rw("Menu", &ImPlotInputMap::Menu)
        .def_rw("OverrideMod", &ImPlotInputMap::OverrideMod)
        .def_rw("ZoomMod", &ImPlotInputMap::ZoomMod)
        .def_rw("ZoomRate", &ImPlotInputMap::ZoomRate)
    ;

}

void bind_implot_methods(nb::module_& m) {
    
    //-----------------------------------------------------------------------------
    // [SECTION] Begin/End Plot
    //-----------------------------------------------------------------------------

    // IMPLOT_API bool BeginPlot(const char* title_id, const ImVec2& size=ImVec2(-1,0), ImPlotFlags flags=0);
    m.def(
        "BeginPlot",
        [](const char* title_id, const Vec2T& size, ImPlotFlags flags) {
            return ImPlot::BeginPlot(title_id, to_vec2(size), flags);
        },
        nb::arg("title_id"),
        nb::arg("size") = std::make_tuple(-1.f, 0.f),
        nb::arg("flags") = 0
    );

    // IMPLOT_API void EndPlot();
    m.def("EndPlot", []() { ImPlot::EndPlot(); });

    /*
    IMPLOT_API bool BeginSubplots(const char* title_id,
                                int rows,
                                int cols,
                                const ImVec2& size,
                                ImPlotSubplotFlags flags = 0,
                                float* row_ratios        = nullptr,
                                float* col_ratios        = nullptr);
    */
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
        nb::arg("title_id"),
        nb::arg("rows"),
        nb::arg("cols"),
        nb::arg("size") = std::make_tuple(-1.f, 0.f),
        nb::arg("flags") = 0,
        nb::arg("row_ratios") = std::vector<float>(),
        nb::arg("col_ratios") = std::vector<float>()
    );

    // IMPLOT_API void EndSubplots();
    m.def("EndSubplots", []() { ImPlot::EndSubplots(); });


    //-----------------------------------------------------------------------------
    // [SECTION] Setup
    //-----------------------------------------------------------------------------
    
    // IMPLOT_API void SetupAxis(ImAxis axis, const char* label=nullptr, ImPlotAxisFlags flags=0);
    m.def(
        "SetupAxis",
        [](ImAxis axis, const char* label, ImPlotAxisFlags flags) {
            ImPlot::SetupAxis(axis, label, flags);
        },
        nb::arg("axis"),
        nb::arg("label") = "",
        nb::arg("flags") = 0
    );

    // IMPLOT_API void SetupAxisLimits(ImAxis axis, double v_min, double v_max, ImPlotCond cond = ImPlotCond_Once);
    m.def(
        "SetupAxisLimits",
        [](ImAxis axis, double v_min, double v_max, ImPlotCond cond) {
            ImPlot::SetupAxisLimits(axis, v_min, v_max, cond);
        },
        nb::arg("axis"),
        nb::arg("vmin"),
        nb::arg("vmax"),
        nb::arg("cond") = (int)ImPlotCond_Once
    );

    // IMPLOT_API void SetupAxisFormat(ImAxis axis, const char* fmt);
    m.def(
        "SetupAxisFormat",
        [](ImAxis axis, const char* fmt) {
            ImPlot::SetupAxisFormat(axis, fmt);
        },
        nb::arg("axis"),
        nb::arg("fmt")
    );


    // IMPLOT_API void SetupAxisTicks(ImAxis axis, const double* values, int n_ticks, const char* const labels[]=nullptr, bool keep_default=false);
    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, const Eigen::VectorXd& values, const std::vector<std::string>& labels, bool keep_default) {
            if(labels.size() > 0 && (labels.size() != values.size())) throw std::runtime_error("input sizes don't match");
            const auto _labels = convert_string_items(labels);
            ImPlot::SetupAxisTicks(axis, values.data(), values.size(), labels.size() == 0 ? nullptr : _labels.data(), keep_default);
        },
        nb::arg("axis"),
        nb::arg("values"),
        nb::arg("labels") = std::vector<std::string>(),
        nb::arg("keep_default") = false
    );

    // IMPLOT_API void SetupAxisTicks(ImAxis axis, const double* values, int n_ticks, const char* const labels[]=nullptr, bool keep_default=false);
    m.def(
        "SetupAxisTicks",
        [](ImAxis axis, double v_min, double v_max, int n_ticks, const std::vector<std::string>& labels, bool keep_default) {
            if(labels.size() > 0 && (labels.size() != n_ticks)) throw std::runtime_error("input sizes don't match");
            const auto _labels = convert_string_items(labels);
            ImPlot::SetupAxisTicks(axis, v_min, v_max, n_ticks, labels.size() == 0 ? nullptr : _labels.data(), keep_default);
        },
        nb::arg("axis"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("n_ticks"),
        nb::arg("labels") = std::vector<std::string>(),
        nb::arg("keep_default") = false
    );


    // IMPLOT_API void SetupAxisScale(ImAxis axis, ImPlotScale scale);
    m.def(
        "SetupAxisScale",
        [](ImAxis axis, ImPlotScale scale) {
            ImPlot::SetupAxisScale(axis, scale);
        },
        nb::arg("axis"),
        nb::arg("scale")
    );

    // IMPLOT_API void SetupAxisLimitsConstraints(ImAxis axis, double v_min, double v_max);
    m.def(
        "SetupAxisLimitsConstraints",
        [](ImAxis axis, double v_min, double v_max) {
            ImPlot::SetupAxisLimitsConstraints(axis, v_min, v_max);
        },
        nb::arg("axis"),
        nb::arg("v_min"),
        nb::arg("v_max")
    );

    // IMPLOT_API void SetupAxisZoomConstraints(ImAxis axis, double z_min, double z_max);
    m.def(
        "SetupAxisZoomConstraints",
        [](ImAxis axis, double z_min, double z_max) {
            ImPlot::SetupAxisZoomConstraints(axis, z_min, z_max);
        },
        nb::arg("axis"),
        nb::arg("z_min"),
        nb::arg("z_max")
    );

    // IMPLOT_API void SetupAxes(const char* x_label, const char* y_label, ImPlotAxisFlags x_flags=0, ImPlotAxisFlags y_flags=0);
    m.def(
        "SetupAxes",
        [](const char* x_label, const char* y_label, ImPlotAxisFlags x_flags, ImPlotAxisFlags y_flags) {
            ImPlot::SetupAxes(x_label, y_label, x_flags, y_flags);
        },
        nb::arg("x_label"),
        nb::arg("y_label"),
        nb::arg("x_flags") = 0,
        nb::arg("y_flags") = 0
    );

    // IMPLOT_API void SetupAxesLimits(double x_min, double x_max, double y_min, double y_max, ImPlotCond cond = ImPlotCond_Once);
    m.def(
        "SetupAxesLimits",
        [](double x_min, double x_max, double y_min, double y_max, ImPlotCond cond) {
            ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max, cond);
        },
        nb::arg("x_min"),
        nb::arg("x_max"),
        nb::arg("y_min"),
        nb::arg("y_max"),
        nb::arg("cond") = (int)ImPlotCond_Once
    );

    // IMPLOT_API void SetupLegend(ImPlotLocation location, ImPlotLegendFlags flags=0);
    m.def(
        "SetupLegend",
        [](ImPlotLocation location, ImPlotLegendFlags flags) {
            ImPlot::SetupLegend(location, flags);
        },
        nb::arg("location"),
        nb::arg("flags") = 0
    );

    // IMPLOT_API void SetupMouseText(ImPlotLocation location, ImPlotMouseTextFlags flags=0);
    m.def(
        "SetupMouseText",
        [](ImPlotLocation location, ImPlotMouseTextFlags flags) {
            ImPlot::SetupMouseText(location, flags);
        },
        nb::arg("location"),
        nb::arg("flags") = 0
    );

    // IMPLOT_API void SetupFinish();
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

    // IMPLOT_TMP void PlotLine(const char* label_id, const T* values, int count, double xscale=1, double xstart=0, ImPlotLineFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotLine",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotLineFlags flags) {
            ImPlot::PlotLine(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("xscale")=1.,
        nb::arg("xstart")=0.,
        nb::arg("flags")=0
    );
   

    // IMPLOT_TMP void PlotLine(const char* label_id, const T* xs, const T* ys, int count, ImPlotLineFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotLine",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotLineFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotLine(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("flags") = 0
    );
    
    // PlotScatter

    // IMPLOT_TMP void PlotScatter(const char* label_id, const T* values, int count, double xscale=1, double xstart=0, ImPlotScatterFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotScatter",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotScatterFlags flags) {
            ImPlot::PlotScatter(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("xscale")=1.,
        nb::arg("xstart")=0.,
        nb::arg("flags")=0
    );
    
    // IMPLOT_TMP void PlotScatter(const char* label_id, const T* xs, const T* ys, int count, ImPlotScatterFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotScatter",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotScatterFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotScatter(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("flags") = 0
    );

    // PlotStairs

    // IMPLOT_TMP void PlotStairs(const char* label_id, const T* values, int count, double xscale=1, double xstart=0, ImPlotStairsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotStairs",
        [](const char* label_id, const Eigen::VectorXd& values, double xscale, double xstart, ImPlotStairsFlags flags) {
            ImPlot::PlotStairs(label_id, values.data(), values.size(), xscale, xstart, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("xscale")=1.,
        nb::arg("xstart")=0.,
        nb::arg("flags")=0
    );
    
    // IMPLOT_TMP void PlotStairs(const char* label_id, const T* xs, const T* ys, int count, ImPlotStairsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotStairs",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotStairsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotStairs(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("flags") = 0
    );

    // PlotShaded
    
    // IMPLOT_TMP void PlotShaded(const char* label_id, const T* values, int count, double yref=0, double xscale=1, double xstart=0, ImPlotShadedFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& values, double yref, double xscale, double xstart, ImPlotShadedFlags flags) {
            ImPlot::PlotShaded(label_id, values.data(), values.size(), yref, xscale, xstart, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("yref")=0.,
        nb::arg("xscale")=1.,
        nb::arg("xstart")=0.,
        nb::arg("flags")=0
    );
    
    // IMPLOT_TMP void PlotShaded(const char* label_id, const T* xs, const T* ys, int count, double yref=0, ImPlotShadedFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, double yref, ImPlotShadedFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotShaded(label_id, xs.data(), ys.data(), xs.size(), yref, flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("yref")=0.,
        nb::arg("flags") = 0
    );
    
    // IMPLOT_TMP void PlotShaded(const char* label_id, const T* xs, const T* ys1, const T* ys2, int count, ImPlotShadedFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotShaded",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys1, const Eigen::VectorXd& ys2, ImPlotShadedFlags flags) {
            if(xs.size() != ys1.size()) throw std::runtime_error("invalid input sizes");
            if(xs.size() != ys2.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotShaded(label_id, xs.data(), ys1.data(), ys2.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys1"),
        nb::arg("ys2"),
        nb::arg("flags") = 0
    );

    // PlotBars

    // IMPLOT_TMP void PlotBars(const char* label_id, const T* values, int count, double bar_size=0.67, double shift=0, ImPlotBarsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotBars",
        [](const char* label_id, const Eigen::VectorXd& values, double bar_size, double shift, ImPlotBarsFlags flags) {
            ImPlot::PlotBars(label_id, values.data(), values.size(), bar_size, shift, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("bar_size")=0.67,
        nb::arg("shift")=0.,
        nb::arg("flags")=0
    );

    // IMPLOT_TMP void PlotBars(const char* label_id, const T* xs, const T* ys, int count, double bar_size, ImPlotBarsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotBars",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, double bar_size, ImPlotBarsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotBars(label_id, xs.data(), ys.data(), xs.size(), bar_size, flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("bar_size"),
        nb::arg("flags") = 0
    );

    // PlotBarGroups

    // IMPLOT_TMP void PlotBarGroups(const char* const label_ids[], const T* values, int item_count, int group_count, double group_size=0.67, double shift=0, ImPlotBarGroupsFlags flags=0);
    m.def(
        "PlotBarGroups",
        [](const std::vector<std::string>& label_ids, const Eigen::MatrixXd& values, double group_size, double shift, ImPlotBarGroupsFlags flags) {
            if(label_ids.size() != values.rows()) throw std::runtime_error("label_ids size must match values rows");
            const auto _label_ids = convert_string_items(label_ids);
            ImPlot::PlotBarGroups(_label_ids.data(), values.data(), values.rows(), values.cols(), group_size, shift, flags);
        },
        nb::arg("label_ids"),
        nb::arg("values"),
        nb::arg("group_size")=0.67,
        nb::arg("shift")=0.,
        nb::arg("flags")=0
    );

    // PlotErrorBars

    // IMPLOT_TMP void PlotErrorBars(const char* label_id, const T* xs, const T* ys, const T* err, int count, ImPlotErrorBarsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotErrorBars",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, const Eigen::VectorXd& err, ImPlotErrorBarsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            if(xs.size() != err.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotErrorBars(label_id, xs.data(), ys.data(), err.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("err"),
        nb::arg("flags") = 0
    );

    // IMPLOT_TMP void PlotErrorBars(const char* label_id, const T* xs, const T* ys, const T* neg, const T* pos, int count, ImPlotErrorBarsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotErrorBars",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, const Eigen::VectorXd& neg, const Eigen::VectorXd& pos, ImPlotErrorBarsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            if(xs.size() != neg.size()) throw std::runtime_error("invalid input sizes");
            if(xs.size() != pos.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotErrorBars(label_id, xs.data(), ys.data(), neg.data(), pos.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("neg"),
        nb::arg("pos"),
        nb::arg("flags") = 0
    );

    // PlotStems

    // IMPLOT_TMP void PlotStems(const char* label_id, const T* values, int count, double ref=0, double scale=1, double start=0, ImPlotStemsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotStems",
        [](const char* label_id, const Eigen::VectorXd& values, double ref, double scale, double start, ImPlotStemsFlags flags) {
            ImPlot::PlotStems(label_id, values.data(), values.size(), ref, scale, start, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("ref")=0.,
        nb::arg("scale")=1.,
        nb::arg("start")=0.,
        nb::arg("flags")=0
    );

    // IMPLOT_TMP void PlotStems(const char* label_id, const T* xs, const T* ys, int count, double ref=0, ImPlotStemsFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotStems",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, double ref, ImPlotStemsFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotStems(label_id, xs.data(), ys.data(), xs.size(), ref, flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("ref")=0.,
        nb::arg("flags") = 0
    );

    // PlotInfLines
    
    // IMPLOT_TMP void PlotInfLines(const char* label_id, const T* values, int count, ImPlotInfLinesFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotInfLines",
        [](const char* label_id, const Eigen::VectorXd& values, ImPlotInfLinesFlags flags) {
            ImPlot::PlotInfLines(label_id, values.data(), values.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("flags")=0
    );
    
    // PlotPieChart

    // IMPLOT_TMP void PlotPieChart(const char* const label_ids[], const T* values, int count, double x, double y, double radius, ImPlotFormatter fmt, void* fmt_data=nullptr, double angle0=90, ImPlotPieChartFlags flags=0);
    m.def(
        "PlotPieChart",
        [](const std::vector<std::string>& label_ids, const Eigen::VectorXd& values, double x, double y, double radius, const char* label_fmt, double angle0, ImPlotPieChartFlags flags) {
            if(label_ids.size() != values.size()) throw std::runtime_error("input sizes don't match");
            const auto _label_ids = convert_string_items(label_ids);
            ImPlot::PlotPieChart(_label_ids.data(), values.data(), values.size(), x, y, radius, label_fmt, angle0, flags);
        },
        nb::arg("label_ids"),
        nb::arg("values"),
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("radius"),
        nb::arg("label_fmt") = "%.1f",
        nb::arg("angle0") = 90,
        nb::arg("flags") = 0
    );
    

    // PlotHeatmap

    // IMPLOT_TMP void PlotHeatmap(const char* label_id, const T* values, int rows, int cols, double scale_min=0, double scale_max=0, const char* label_fmt="%.1f", const ImPlotPoint& bounds_min=ImPlotPoint(0,0), const ImPlotPoint& bounds_max=ImPlotPoint(1,1), ImPlotHeatmapFlags flags=0);
    m.def(
        "PlotHeatmap",
        [](const char* label_id, const Eigen::MatrixXd& values, double scale_min, double scale_max, const char* label_fmt, const Vec2T& bounds_min, const Vec2T& bounds_max, ImPlotHeatmapFlags flags) {
            ImPlotPoint pt_min(std::get<0>(bounds_min), std::get<1>(bounds_min));
            ImPlotPoint pt_max(std::get<0>(bounds_max), std::get<1>(bounds_max));
            ImPlot::PlotHeatmap(label_id, values.data(), values.rows(), values.cols(), scale_min, scale_max, label_fmt, pt_min, pt_max, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("scale_min") = 0.,
        nb::arg("scale_max") = 0.,
        nb::arg("label_fmt") = "%.1f",
        nb::arg("bounds_min") = Vec2T(0., 0.),
        nb::arg("bounds_max") = Vec2T(1., 1.),
        nb::arg("flags") = 0
    );

    // PlotHistogram
    
    // IMPLOT_TMP double PlotHistogram(const char* label_id, const T* values, int count, int bins=ImPlotBin_Sturges, double bar_scale=1.0, ImPlotRange range=ImPlotRange(), ImPlotHistogramFlags flags=0);
    m.def(
        "PlotHistogram",
        [](const char* label_id, const Eigen::VectorXd& values, int bins, double bar_scale, const Vec2T& range, ImPlotHistogramFlags flags) {
            ImPlotRange imrange(std::get<0>(range), std::get<1>(range));
            ImPlot::PlotHistogram(label_id, values.data(), values.size(), bins, bar_scale, imrange, flags);
        },
        nb::arg("label_id"),
        nb::arg("values"),
        nb::arg("bins") = (int)ImPlotBin_Sturges,
        nb::arg("bar_scale") = 1.0,
        nb::arg("range") = std::make_tuple(0.f, 0.f),
        nb::arg("flags") = 0
    );

    // PlotHistogram2D

    // IMPLOT_TMP double PlotHistogram2D(const char* label_id, const T* xs, const T* ys, int count, int x_bins=ImPlotBin_Sturges, int y_bins=ImPlotBin_Sturges, ImPlotRect range=ImPlotRect(), ImPlotHistogramFlags flags=0);
    m.def(
        "PlotHistogram2D",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, int x_bins, int y_bins, const Vec4T& range, ImPlotHistogramFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlotRect imrange(std::get<0>(range), std::get<1>(range), std::get<2>(range), std::get<3>(range));
            ImPlot::PlotHistogram2D(label_id, xs.data(), ys.data(), xs.size(), x_bins, y_bins, imrange, flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("x_bins") = (int)ImPlotBin_Sturges,
        nb::arg("y_bins") = (int)ImPlotBin_Sturges,
        nb::arg("range") = Vec4T(0., 0., 0., 0.),
        nb::arg("flags") = 0
    );

    // PlotDigital

    // IMPLOT_TMP void PlotDigital(const char* label_id, const T* xs, const T* ys, int count, ImPlotDigitalFlags flags=0, int offset=0, int stride=sizeof(T));
    m.def(
        "PlotDigital",
        [](const char* label_id, const Eigen::VectorXd& xs, const Eigen::VectorXd& ys, ImPlotDigitalFlags flags) {
            if(xs.size() != ys.size()) throw std::runtime_error("invalid input sizes");
            ImPlot::PlotDigital(label_id, xs.data(), ys.data(), xs.size(), flags);
        },
        nb::arg("label_id"),
        nb::arg("xs"),
        nb::arg("ys"),
        nb::arg("flags") = 0
    );

    // PlotImage

    // IMPLOT_API void PlotImage(const char* label_id, ImTextureID tex_ref, const ImPlotPoint& bounds_min, const ImPlotPoint& bounds_max, const ImVec2& uv0=ImVec2(0,0), const ImVec2& uv1=ImVec2(1,1), const ImVec4& tint_col=ImVec4(1,1,1,1), ImPlotImageFlags flags=0);
    m.def(
        "PlotImage",
        [](const char* label_id, ImTextureID tex_ref, const Vec2T& bounds_min, const Vec2T& bounds_max, const Vec2T& uv0, const Vec2T& uv1, const Vec4T& tint_col, ImPlotImageFlags flags) {
            ImPlotPoint pt_min(std::get<0>(bounds_min), std::get<1>(bounds_min));
            ImPlotPoint pt_max(std::get<0>(bounds_max), std::get<1>(bounds_max));
            ImPlot::PlotImage(label_id, tex_ref, pt_min, pt_max, to_vec2(uv0), to_vec2(uv1), to_vec4(tint_col), flags);
        },
        nb::arg("label_id"),
        nb::arg("tex_ref"),
        nb::arg("bounds_min"),
        nb::arg("bounds_max"),
        nb::arg("uv0") = Vec2T(0.f, 0.f),
        nb::arg("uv1") = Vec2T(1.f, 1.f),
        nb::arg("tint_col") = Vec4T(1.f, 1.f, 1.f, 1.f),
        nb::arg("flags") = 0
    );

    // PlotText

    // IMPLOT_API void PlotText(const char* text, double x, double y, const ImVec2& pix_offset=ImVec2(0,0), ImPlotTextFlags flags=0);
    m.def(
        "PlotText",
        [](const char* text, double x, double y, const Vec2T& pix_offset, ImPlotTextFlags flags) {
            ImPlot::PlotText(text, x, y, to_vec2(pix_offset), flags);
        },
        nb::arg("text"),
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("pix_offset") = Vec2T(0.f, 0.f),
        nb::arg("flags") = 0
    );

    // PlotDummy

    // IMPLOT_API void PlotDummy(const char* label_id, ImPlotDummyFlags flags=0);
    m.def(
        "PlotDummy",
        [](const char* label_id, ImPlotDummyFlags flags) {
            ImPlot::PlotDummy(label_id, flags);
        },
        nb::arg("label_id"),
        nb::arg("flags") = 0
    );


    //-----------------------------------------------------------------------------
    // [SECTION] Plot Tools
    //-----------------------------------------------------------------------------

    // IMPLOT_API bool DragPoint(int id, double* x, double* y, const ImVec4& col, float size = 4, ImPlotDragToolFlags flags = 0, bool* out_clicked = nullptr, bool* out_hovered = nullptr, bool* held = nullptr);
    m.def(
        "DragPoint",
        [](int id, double x, double y, const Vec4T& col, float size, ImPlotDragToolFlags flags) {
            bool result = ImPlot::DragPoint(id, &x, &y, to_vec4(col), size, flags);
            return std::make_tuple(result, x, y);
        },
        nb::arg("id"),
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("size") = 4.f,
        nb::arg("flags") = 0
    );

    // IMPLOT_API bool DragLineX(int id, double* x, const ImVec4& col, float thickness = 1, ImPlotDragToolFlags flags = 0, bool* out_clicked = nullptr, bool* out_hovered = nullptr, bool* held = nullptr);
    m.def(
        "DragLineX",
        [](int id, double x, const Vec4T& col, float thickness, ImPlotDragToolFlags flags) {
            bool result = ImPlot::DragLineX(id, &x, to_vec4(col), thickness, flags);
            return std::make_tuple(result, x);
        },
        nb::arg("id"),
        nb::arg("x"),
        nb::arg("col"),
        nb::arg("thickness") = 1.f,
        nb::arg("flags") = 0
    );

    // IMPLOT_API bool DragLineY(int id, double* y, const ImVec4& col, float thickness = 1, ImPlotDragToolFlags flags = 0, bool* out_clicked = nullptr, bool* out_hovered = nullptr, bool* held = nullptr);
    m.def(
        "DragLineY",
        [](int id, double y, const Vec4T& col, float thickness, ImPlotDragToolFlags flags) {
            bool result = ImPlot::DragLineY(id, &y, to_vec4(col), thickness, flags);
            return std::make_tuple(result, y);
        },
        nb::arg("id"),
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("thickness") = 1.f,
        nb::arg("flags") = 0
    );

    // IMPLOT_API bool DragRect(int id, double* x1, double* y1, double* x2, double* y2, const ImVec4& col, ImPlotDragToolFlags flags = 0, bool* out_clicked = nullptr, bool* out_hovered = nullptr, bool* held = nullptr);
    m.def(
        "DragRect",
        [](int id, double x1, double y1, double x2, double y2, const Vec4T& col, ImPlotDragToolFlags flags) {
            bool result = ImPlot::DragRect(id, &x1, &y1, &x2, &y2, to_vec4(col), flags);
            return std::make_tuple(result, x1, y1, x2, y2);
        },
        nb::arg("id"),
        nb::arg("x1"),
        nb::arg("y1"),
        nb::arg("x2"),
        nb::arg("y2"),
        nb::arg("col"),
        nb::arg("flags") = 0
    );

    // IMPLOT_API void Annotation(double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, bool round = false);
    m.def(
        "Annotation",
        [](double x, double y, const Vec4T& col, const Vec2T& pix_offset, bool clamp, bool round) {
            ImPlot::Annotation(x, y, to_vec4(col), to_vec2(pix_offset), clamp, round);
        },
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("pix_offset"),
        nb::arg("clamp"),
        nb::arg("round") = false
    );

    // IMPLOT_API void Annotation(double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, const char* fmt, ...) IM_FMTARGS(6);
    m.def(
        "Annotation",
        [](double x, double y, const Vec4T& col, const Vec2T& pix_offset, bool clamp, const char* text) {
            ImPlot::Annotation(x, y, to_vec4(col), to_vec2(pix_offset), clamp, "%s", text);
        },
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("pix_offset"),
        nb::arg("clamp"),
        nb::arg("text")
    );

    // IMPLOT_API void TagX(double x, const ImVec4& col, bool round = false);
    m.def(
        "TagX",
        [](double x, const Vec4T& col, bool round) {
            ImPlot::TagX(x, to_vec4(col), round);
        },
        nb::arg("x"),
        nb::arg("col"),
        nb::arg("round") = false
    );

    // IMPLOT_API void TagX(double x, const ImVec4& col, const char* fmt, ...) IM_FMTARGS(3);
    m.def(
        "TagX",
        [](double x, const Vec4T& col, const char* text) {
            ImPlot::TagX(x, to_vec4(col), "%s", text);
        },
        nb::arg("x"),
        nb::arg("col"),
        nb::arg("text")
    );

    // IMPLOT_API void TagY(double y, const ImVec4& col, bool round = false);
    m.def(
        "TagY",
        [](double y, const Vec4T& col, bool round) {
            ImPlot::TagY(y, to_vec4(col), round);
        },
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("round") = false
    );

    // IMPLOT_API void TagY(double y, const ImVec4& col, const char* fmt, ...) IM_FMTARGS(3);
    m.def(
        "TagY",
        [](double y, const Vec4T& col, const char* text) {
            ImPlot::TagY(y, to_vec4(col), "%s", text);
        },
        nb::arg("y"),
        nb::arg("col"),
        nb::arg("text")
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Plot Utils
    //-----------------------------------------------------------------------------

    // IMPLOT_API void SetAxis(ImAxis axis);
    m.def(
        "SetAxis",
        [](ImAxis axis) {
            ImPlot::SetAxis(axis);
        },
        nb::arg("axis")
    );

    // IMPLOT_API void SetAxes(ImAxis x_axis, ImAxis y_axis);
    m.def(
        "SetAxes",
        [](ImAxis x_axis, ImAxis y_axis) {
            ImPlot::SetAxes(x_axis, y_axis);
        },
        nb::arg("x_axis"),
        nb::arg("y_axis")
    );

    // IMPLOT_API ImPlotPoint PixelsToPlot(const ImVec2& pix, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "PixelsToPlot",
        [](const Vec2T& pix, ImAxis x_axis, ImAxis y_axis) {
            ImPlotPoint result = ImPlot::PixelsToPlot(to_vec2(pix), x_axis, y_axis);
            return std::make_tuple(result.x, result.y);
        },
        nb::arg("pix"),
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API ImPlotPoint PixelsToPlot(float x, float y, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "PixelsToPlot",
        [](float x, float y, ImAxis x_axis, ImAxis y_axis) {
            ImPlotPoint result = ImPlot::PixelsToPlot(x, y, x_axis, y_axis);
            return std::make_tuple(result.x, result.y);
        },
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API ImVec2 PlotToPixels(const ImPlotPoint& plt, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "PlotToPixels",
        [](const Vec2T& plt, ImAxis x_axis, ImAxis y_axis) {
            ImPlotPoint pt(std::get<0>(plt), std::get<1>(plt));
            ImVec2 result = ImPlot::PlotToPixels(pt, x_axis, y_axis);
            return std::make_tuple(result.x, result.y);
        },
        nb::arg("plt"),
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API ImVec2 PlotToPixels(double x, double y, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "PlotToPixels",
        [](double x, double y, ImAxis x_axis, ImAxis y_axis) {
            ImVec2 result = ImPlot::PlotToPixels(x, y, x_axis, y_axis);
            return std::make_tuple(result.x, result.y);
        },
        nb::arg("x"),
        nb::arg("y"),
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API ImVec2 GetPlotPos();
    m.def(
        "GetPlotPos",
        []() {
            ImVec2 result = ImPlot::GetPlotPos();
            return std::make_tuple(result.x, result.y);
        }
    );

    // IMPLOT_API ImVec2 GetPlotSize();
    m.def(
        "GetPlotSize",
        []() {
            ImVec2 result = ImPlot::GetPlotSize();
            return std::make_tuple(result.x, result.y);
        }
    );

    // IMPLOT_API ImPlotPoint GetPlotMousePos(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "GetPlotMousePos",
        [](ImAxis x_axis, ImAxis y_axis) {
            ImPlotPoint result = ImPlot::GetPlotMousePos(x_axis, y_axis);
            return std::make_tuple(result.x, result.y);
        },
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API ImPlotRect GetPlotLimits(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "GetPlotLimits",
        [](ImAxis x_axis, ImAxis y_axis) {
            ImPlotRect result = ImPlot::GetPlotLimits(x_axis, y_axis);
            return std::make_tuple(result.X.Min, result.X.Max, result.Y.Min, result.Y.Max);
        },
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API bool IsPlotHovered();
    m.def(
        "IsPlotHovered",
        []() {
            return ImPlot::IsPlotHovered();
        }
    );

    // IMPLOT_API bool IsAxisHovered(ImAxis axis);
    m.def(
        "IsAxisHovered",
        [](ImAxis axis) {
            return ImPlot::IsAxisHovered(axis);
        },
        nb::arg("axis")
    );

    // IMPLOT_API bool IsSubplotsHovered();
    m.def(
        "IsSubplotsHovered",
        []() {
            return ImPlot::IsSubplotsHovered();
        }
    );

    // IMPLOT_API bool IsPlotSelected();
    m.def(
        "IsPlotSelected",
        []() {
            return ImPlot::IsPlotSelected();
        }
    );

    // IMPLOT_API ImPlotRect GetPlotSelection(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO);
    m.def(
        "GetPlotSelection",
        [](ImAxis x_axis, ImAxis y_axis) {
            ImPlotRect result = ImPlot::GetPlotSelection(x_axis, y_axis);
            return std::make_tuple(result.X.Min, result.X.Max, result.Y.Min, result.Y.Max);
        },
        nb::arg("x_axis") = IMPLOT_AUTO,
        nb::arg("y_axis") = IMPLOT_AUTO
    );

    // IMPLOT_API void CancelPlotSelection();
    m.def(
        "CancelPlotSelection",
        []() {
            ImPlot::CancelPlotSelection();
        }
    );

    // IMPLOT_API void HideNextItem(bool hidden = true, ImPlotCond cond = ImPlotCond_Once);
    m.def(
        "HideNextItem",
        [](bool hidden, ImPlotCond cond) {
            ImPlot::HideNextItem(hidden, cond);
        },
        nb::arg("hidden") = true,
        nb::arg("cond") = static_cast<int>(ImPlotCond_Once)
    );

    // IMPLOT_API bool BeginAlignedPlots(const char* group_id, bool vertical = true);
    m.def(
        "BeginAlignedPlots",
        [](const char* group_id, bool vertical) {
            return ImPlot::BeginAlignedPlots(group_id, vertical);
        },
        nb::arg("group_id"),
        nb::arg("vertical") = true
    );

    // IMPLOT_API void EndAlignedPlots();
    m.def(
        "EndAlignedPlots",
        []() {
            ImPlot::EndAlignedPlots();
        }
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Legend Utils
    //-----------------------------------------------------------------------------

    // IMPLOT_API bool BeginLegendPopup(const char* label_id, ImGuiMouseButton mouse_button=1);
    m.def(
        "BeginLegendPopup",
        [](const char* label_id, ImGuiMouseButton mouse_button) {
            return ImPlot::BeginLegendPopup(label_id, mouse_button);
        },
        nb::arg("label_id"),
        nb::arg("mouse_button") = 1
    );

    // IMPLOT_API void EndLegendPopup();
    m.def(
        "EndLegendPopup",
        []() {
            ImPlot::EndLegendPopup();
        }
    );

    // IMPLOT_API bool IsLegendEntryHovered(const char* label_id);
    m.def(
        "IsLegendEntryHovered",
        [](const char* label_id) {
            return ImPlot::IsLegendEntryHovered(label_id);
        },
        nb::arg("label_id")
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Drag and Drop
    //-----------------------------------------------------------------------------

    // IMPLOT_API bool BeginDragDropTargetPlot();
    m.def(
        "BeginDragDropTargetPlot",
        []() {
            return ImPlot::BeginDragDropTargetPlot();
        }
    );

    // IMPLOT_API bool BeginDragDropTargetAxis(ImAxis axis);
    m.def(
        "BeginDragDropTargetAxis",
        [](ImAxis axis) {
            return ImPlot::BeginDragDropTargetAxis(axis);
        },
        nb::arg("axis")
    );

    // IMPLOT_API bool BeginDragDropTargetLegend();
    m.def(
        "BeginDragDropTargetLegend",
        []() {
            return ImPlot::BeginDragDropTargetLegend();
        }
    );

    // IMPLOT_API void EndDragDropTarget();
    m.def(
        "EndDragDropTarget",
        []() {
            ImPlot::EndDragDropTarget();
        }
    );

    // IMPLOT_API bool BeginDragDropSourcePlot(ImGuiDragDropFlags flags=0);
    m.def(
        "BeginDragDropSourcePlot",
        [](ImGuiDragDropFlags flags) {
            return ImPlot::BeginDragDropSourcePlot(flags);
        },
        nb::arg("flags") = 0
    );

    // IMPLOT_API bool BeginDragDropSourceAxis(ImAxis axis, ImGuiDragDropFlags flags=0);
    m.def(
        "BeginDragDropSourceAxis",
        [](ImAxis axis, ImGuiDragDropFlags flags) {
            return ImPlot::BeginDragDropSourceAxis(axis, flags);
        },
        nb::arg("axis"),
        nb::arg("flags") = 0
    );

    // IMPLOT_API bool BeginDragDropSourceItem(const char* label_id, ImGuiDragDropFlags flags=0);
    m.def(
        "BeginDragDropSourceItem",
        [](const char* label_id, ImGuiDragDropFlags flags) {
            return ImPlot::BeginDragDropSourceItem(label_id, flags);
        },
        nb::arg("label_id"),
        nb::arg("flags") = 0
    );

    // IMPLOT_API void EndDragDropSource();
    m.def(
        "EndDragDropSource",
        []() {
            ImPlot::EndDragDropSource();
        }
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Styling
    //-----------------------------------------------------------------------------

    // IMPLOT_API ImPlotStyle& GetStyle();
    m.def(
        "GetStyle",
        []() -> ImPlotStyle& {
            return ImPlot::GetStyle();
        },
        nb::rv_policy::reference
    );

    // IMPLOT_API void StyleColorsAuto(ImPlotStyle* dst = nullptr);
    m.def(
        "StyleColorsAuto",
        [](ImPlotStyle* dst) {
            ImPlot::StyleColorsAuto(dst);
        },
        nb::arg("dst") = nullptr
    );

    // IMPLOT_API void StyleColorsClassic(ImPlotStyle* dst = nullptr);
    m.def(
        "StyleColorsClassic",
        [](ImPlotStyle* dst) {
            ImPlot::StyleColorsClassic(dst);
        },
        nb::arg("dst") = nullptr
    );

    // IMPLOT_API void StyleColorsDark(ImPlotStyle* dst = nullptr);
    m.def(
        "StyleColorsDark",
        [](ImPlotStyle* dst) {
            ImPlot::StyleColorsDark(dst);
        },
        nb::arg("dst") = nullptr
    );

    // IMPLOT_API void StyleColorsLight(ImPlotStyle* dst = nullptr);
    m.def(
        "StyleColorsLight",
        [](ImPlotStyle* dst) {
            ImPlot::StyleColorsLight(dst);
        },
        nb::arg("dst") = nullptr
    );

    // IMPLOT_API void PushStyleColor(ImPlotCol idx, ImU32 col);
    m.def(
        "PushStyleColor",
        [](ImPlotCol idx, ImU32 col) {
            ImPlot::PushStyleColor(idx, col);
        },
        nb::arg("idx"),
        nb::arg("col")
    );

    // IMPLOT_API void PushStyleColor(ImPlotCol idx, const ImVec4& col);
    m.def(
        "PushStyleColor",
        [](ImPlotCol idx, const Vec4T& col) {
            ImPlot::PushStyleColor(idx, to_vec4(col));
        },
        nb::arg("idx"),
        nb::arg("col")
    );

    // IMPLOT_API void PopStyleColor(int count = 1);
    m.def(
        "PopStyleColor",
        [](int count) {
            ImPlot::PopStyleColor(count);
        },
        nb::arg("count") = 1
    );

    // IMPLOT_API void PushStyleVar(ImPlotStyleVar idx, float val);
    m.def(
        "PushStyleVar",
        [](ImPlotStyleVar idx, float val) {
            ImPlot::PushStyleVar(idx, val);
        },
        nb::arg("idx"),
        nb::arg("val")
    );

    // IMPLOT_API void PushStyleVar(ImPlotStyleVar idx, int val);
    m.def(
        "PushStyleVar",
        [](ImPlotStyleVar idx, int val) {
            ImPlot::PushStyleVar(idx, val);
        },
        nb::arg("idx"),
        nb::arg("val")
    );

    // IMPLOT_API void PushStyleVar(ImPlotStyleVar idx, const ImVec2& val);
    m.def(
        "PushStyleVar",
        [](ImPlotStyleVar idx, const Vec2T& val) {
            ImPlot::PushStyleVar(idx, to_vec2(val));
        },
        nb::arg("idx"),
        nb::arg("val")
    );

    // IMPLOT_API void PopStyleVar(int count = 1);
    m.def(
        "PopStyleVar",
        [](int count) {
            ImPlot::PopStyleVar(count);
        },
        nb::arg("count") = 1
    );

    // IMPLOT_API void SetNextLineStyle(const ImVec4& col = IMPLOT_AUTO_COL, float weight = IMPLOT_AUTO);
    m.def(
        "SetNextLineStyle",
        [](const Vec4T& col, float weight) {
            ImPlot::SetNextLineStyle(to_vec4(col), weight);
        },
        nb::arg("col") = Vec4T(0.f, 0.f, 0.f, -1.f),  // IMPLOT_AUTO_COL
        nb::arg("weight") = -1.f  // IMPLOT_AUTO
    );

    // IMPLOT_API void SetNextFillStyle(const ImVec4& col = IMPLOT_AUTO_COL, float alpha_mod = IMPLOT_AUTO);
    m.def(
        "SetNextFillStyle",
        [](const Vec4T& col, float alpha_mod) {
            ImPlot::SetNextFillStyle(to_vec4(col), alpha_mod);
        },
        nb::arg("col") = Vec4T(0.f, 0.f, 0.f, -1.f),  // IMPLOT_AUTO_COL
        nb::arg("alpha_mod") = -1.f  // IMPLOT_AUTO
    );

    // IMPLOT_API void SetNextMarkerStyle(ImPlotMarker marker = IMPLOT_AUTO, float size = IMPLOT_AUTO, const ImVec4& fill = IMPLOT_AUTO_COL, float weight = IMPLOT_AUTO, const ImVec4& outline = IMPLOT_AUTO_COL);
    m.def(
        "SetNextMarkerStyle",
        [](ImPlotMarker marker, float size, const Vec4T& fill, float weight, const Vec4T& outline) {
            ImPlot::SetNextMarkerStyle(marker, size, to_vec4(fill), weight, to_vec4(outline));
        },
        nb::arg("marker") = -1,  // IMPLOT_AUTO
        nb::arg("size") = -1.f,  // IMPLOT_AUTO
        nb::arg("fill") = Vec4T(0.f, 0.f, 0.f, -1.f),  // IMPLOT_AUTO_COL
        nb::arg("weight") = -1.f,  // IMPLOT_AUTO
        nb::arg("outline") = Vec4T(0.f, 0.f, 0.f, -1.f)  // IMPLOT_AUTO_COL
    );

    // IMPLOT_API void SetNextErrorBarStyle(const ImVec4& col = IMPLOT_AUTO_COL, float size = IMPLOT_AUTO, float weight = IMPLOT_AUTO);
    m.def(
        "SetNextErrorBarStyle",
        [](const Vec4T& col, float size, float weight) {
            ImPlot::SetNextErrorBarStyle(to_vec4(col), size, weight);
        },
        nb::arg("col") = Vec4T(0.f, 0.f, 0.f, -1.f),  // IMPLOT_AUTO_COL
        nb::arg("size") = -1.f,  // IMPLOT_AUTO
        nb::arg("weight") = -1.f  // IMPLOT_AUTO
    );

    // IMPLOT_API ImVec4 GetLastItemColor();
    m.def(
        "GetLastItemColor",
        []() {
            return from_vec4(ImPlot::GetLastItemColor());
        }
    );

    // IMPLOT_API const char* GetStyleColorName(ImPlotCol idx);
    m.def(
        "GetStyleColorName",
        [](ImPlotCol idx) {
            return ImPlot::GetStyleColorName(idx);
        },
        nb::arg("idx")
    );

    // IMPLOT_API const char* GetMarkerName(ImPlotMarker idx);
    m.def(
        "GetMarkerName",
        [](ImPlotMarker idx) {
            return ImPlot::GetMarkerName(idx);
        },
        nb::arg("idx")
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Colormaps
    //-----------------------------------------------------------------------------

    // IMPLOT_API ImPlotColormap AddColormap(const char* name, const ImVec4* cols, int size, bool qual=true);
    m.def(
        "AddColormap",
        [](const char* name, const std::vector<Vec4T>& cols, bool qual) {
            std::vector<ImVec4> imcols;
            imcols.reserve(cols.size());
            for(const auto& c : cols) {
                imcols.push_back(to_vec4(c));
            }
            return ImPlot::AddColormap(name, imcols.data(), imcols.size(), qual);
        },
        nb::arg("name"),
        nb::arg("cols"),
        nb::arg("qual") = true
    );

    // IMPLOT_API int GetColormapCount();
    m.def(
        "GetColormapCount",
        []() {
            return ImPlot::GetColormapCount();
        }
    );

    // IMPLOT_API const char* GetColormapName(ImPlotColormap cmap);
    m.def(
        "GetColormapName",
        [](ImPlotColormap cmap) {
            return ImPlot::GetColormapName(cmap);
        },
        nb::arg("cmap")
    );

    // IMPLOT_API ImPlotColormap GetColormapIndex(const char* name);
    m.def(
        "GetColormapIndex",
        [](const char* name) {
            return ImPlot::GetColormapIndex(name);
        },
        nb::arg("name")
    );

    // IMPLOT_API void PushColormap(ImPlotColormap cmap);
    m.def(
        "PushColormap",
        [](ImPlotColormap cmap) {
            ImPlot::PushColormap(cmap);
        },
        nb::arg("cmap")
    );

    // IMPLOT_API void PushColormap(const char* name);
    m.def(
        "PushColormap",
        [](const char* name) {
            ImPlot::PushColormap(name);
        },
        nb::arg("name")
    );

    // IMPLOT_API void PopColormap(int count = 1);
    m.def(
        "PopColormap",
        [](int count) {
            ImPlot::PopColormap(count);
        },
        nb::arg("count") = 1
    );

    // IMPLOT_API ImVec4 NextColormapColor();
    m.def(
        "NextColormapColor",
        []() {
            return from_vec4(ImPlot::NextColormapColor());
        }
    );

    // IMPLOT_API int GetColormapSize(ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "GetColormapSize",
        [](ImPlotColormap cmap) {
            return ImPlot::GetColormapSize(cmap);
        },
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API ImVec4 GetColormapColor(int idx, ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "GetColormapColor",
        [](int idx, ImPlotColormap cmap) {
            return from_vec4(ImPlot::GetColormapColor(idx, cmap));
        },
        nb::arg("idx"),
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API ImVec4 SampleColormap(float t, ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "SampleColormap",
        [](float t, ImPlotColormap cmap) {
            return from_vec4(ImPlot::SampleColormap(t, cmap));
        },
        nb::arg("t"),
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API void ColormapScale(const char* label, double scale_min, double scale_max, const ImVec2& size = ImVec2(0,0), const char* format = "%g", ImPlotColormapScaleFlags flags = 0, ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "ColormapScale",
        [](const char* label, double scale_min, double scale_max, const Vec2T& size, const char* format, ImPlotColormapScaleFlags flags, ImPlotColormap cmap) {
            ImPlot::ColormapScale(label, scale_min, scale_max, to_vec2(size), format, flags, cmap);
        },
        nb::arg("label"),
        nb::arg("scale_min"),
        nb::arg("scale_max"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("format") = "%g",
        nb::arg("flags") = 0,
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API bool ColormapSlider(const char* label, float* t, ImVec4* out = nullptr, const char* format = "", ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "ColormapSlider",
        [](const char* label, float t, const char* format, ImPlotColormap cmap) {
            ImVec4 out;
            bool result = ImPlot::ColormapSlider(label, &t, &out, format, cmap);
            return std::make_tuple(result, t, from_vec4(out));
        },
        nb::arg("label"),
        nb::arg("t"),
        nb::arg("format") = "",
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API bool ColormapButton(const char* label, const ImVec2& size = ImVec2(0,0), ImPlotColormap cmap = IMPLOT_AUTO);
    m.def(
        "ColormapButton",
        [](const char* label, const Vec2T& size, ImPlotColormap cmap) {
            return ImPlot::ColormapButton(label, to_vec2(size), cmap);
        },
        nb::arg("label"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("cmap") = IMPLOT_AUTO
    );

    // IMPLOT_API void BustColorCache(const char* plot_title_id = nullptr);
    m.def(
        "BustColorCache",
        [](const char* plot_title_id) {
            ImPlot::BustColorCache(plot_title_id);
        },
        nb::arg("plot_title_id") = nullptr
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Input Mapping
    //-----------------------------------------------------------------------------

    // IMPLOT_API ImPlotInputMap& GetInputMap();
    m.def(
        "GetInputMap",
        []() -> ImPlotInputMap& {
            return ImPlot::GetInputMap();
        },
        nb::rv_policy::reference
    );

    // IMPLOT_API void MapInputDefault(ImPlotInputMap* dst = nullptr);
    m.def(
        "MapInputDefault",
        [](ImPlotInputMap* dst) {
            ImPlot::MapInputDefault(dst);
        },
        nb::arg("dst") = nullptr
    );

    // IMPLOT_API void MapInputReverse(ImPlotInputMap* dst = nullptr);
    m.def(
        "MapInputReverse",
        [](ImPlotInputMap* dst) {
            ImPlot::MapInputReverse(dst);
        },
        nb::arg("dst") = nullptr
    );

    //-----------------------------------------------------------------------------
    // [SECTION] Miscellaneous
    //-----------------------------------------------------------------------------

    // IMPLOT_API void ItemIcon(const ImVec4& col);
    m.def(
        "ItemIcon",
        [](const Vec4T& col) {
            ImPlot::ItemIcon(to_vec4(col));
        },
        nb::arg("col")
    );

    // IMPLOT_API void ItemIcon(ImU32 col);
    m.def(
        "ItemIcon",
        [](ImU32 col) {
            ImPlot::ItemIcon(col);
        },
        nb::arg("col")
    );

    // IMPLOT_API void ColormapIcon(ImPlotColormap cmap);
    m.def(
        "ColormapIcon",
        [](ImPlotColormap cmap) {
            ImPlot::ColormapIcon(cmap);
        },
        nb::arg("cmap")
    );

    // IMPLOT_API ImDrawList* GetPlotDrawList();
    m.def(
        "GetPlotDrawList",
        []() -> ImDrawList* {
            return ImPlot::GetPlotDrawList();
        },
        nb::rv_policy::reference
    );

    // IMPLOT_API void PushPlotClipRect(float expand=0);
    m.def(
        "PushPlotClipRect",
        [](float expand) {
            ImPlot::PushPlotClipRect(expand);
        },
        nb::arg("expand") = 0.f
    );

    // IMPLOT_API void PopPlotClipRect();
    m.def(
        "PopPlotClipRect",
        []() {
            ImPlot::PopPlotClipRect();
        }
    );

    // IMPLOT_API bool ShowStyleSelector(const char* label);
    m.def(
        "ShowStyleSelector",
        [](const char* label) {
            return ImPlot::ShowStyleSelector(label);
        },
        nb::arg("label")
    );

    // IMPLOT_API bool ShowColormapSelector(const char* label);
    m.def(
        "ShowColormapSelector",
        [](const char* label) {
            return ImPlot::ShowColormapSelector(label);
        },
        nb::arg("label")
    );

    // IMPLOT_API bool ShowInputMapSelector(const char* label);
    m.def(
        "ShowInputMapSelector",
        [](const char* label) {
            return ImPlot::ShowInputMapSelector(label);
        },
        nb::arg("label")
    );

    // IMPLOT_API void ShowStyleEditor(ImPlotStyle* ref = nullptr);
    m.def(
        "ShowStyleEditor",
        [](ImPlotStyle* ref) {
            ImPlot::ShowStyleEditor(ref);
        },
        nb::arg("ref") = nullptr
    );

    // IMPLOT_API void ShowUserGuide();
    m.def(
        "ShowUserGuide",
        []() {
            ImPlot::ShowUserGuide();
        }
    );

    // IMPLOT_API void ShowMetricsWindow(bool* p_popen = nullptr);
    m.def(
        "ShowMetricsWindow",
        [](bool p_open) {
            ImPlot::ShowMetricsWindow(&p_open);
            return p_open;
        },
        nb::arg("p_open") = true
    );

    // IMPLOT_API void ShowDemoWindow(bool* p_open = nullptr);
    // (commented out because we don't currently compile the demo source file)
    // m.def(
    //     "ShowDemoWindow",
    //     [](bool p_open) {
    //         ImPlot::ShowDemoWindow(&p_open);
    //         return p_open;
    //     },
    //     nb::arg("p_open") = true
    // );

}

void bind_implot_enums(nb::module_& m) {

  { // ImAxis ImAxis
  auto e = nb::enum_<ImAxis_>(m, "ImAxis");
    e.value("ImAxis_X1",                               ImAxis_X1);                               m.attr("ImAxis_X1")                               = static_cast<int>(ImAxis_X1);
    e.value("ImAxis_X2",                               ImAxis_X2);                               m.attr("ImAxis_X2")                               = static_cast<int>(ImAxis_X2);
    e.value("ImAxis_X3",                               ImAxis_X3);                               m.attr("ImAxis_X3")                               = static_cast<int>(ImAxis_X3);
    e.value("ImAxis_Y1",                               ImAxis_Y1);                               m.attr("ImAxis_Y1")                               = static_cast<int>(ImAxis_Y1);
    e.value("ImAxis_Y2",                               ImAxis_Y2);                               m.attr("ImAxis_Y2")                               = static_cast<int>(ImAxis_Y2);
    e.value("ImAxis_Y3",                               ImAxis_Y3);                               m.attr("ImAxis_Y3")                               = static_cast<int>(ImAxis_Y3);
    e.value("ImAxis_COUNT",                            ImAxis_COUNT);                            m.attr("ImAxis_COUNT")                            = static_cast<int>(ImAxis_COUNT);
  ;
  }

  { // ImPlotFlags ImPlotFlags_
  auto e = nb::enum_<ImPlotFlags_>(m, "ImPlotFlags");
    e.value("ImPlotFlags_None",                        ImPlotFlags_None);                        m.attr("ImPlotFlags_None")                        = static_cast<int>(ImPlotFlags_None);
    e.value("ImPlotFlags_NoTitle",                     ImPlotFlags_NoTitle);                     m.attr("ImPlotFlags_NoTitle")                     = static_cast<int>(ImPlotFlags_NoTitle);
    e.value("ImPlotFlags_NoLegend",                    ImPlotFlags_NoLegend);                    m.attr("ImPlotFlags_NoLegend")                    = static_cast<int>(ImPlotFlags_NoLegend);
    e.value("ImPlotFlags_NoMouseText",                 ImPlotFlags_NoMouseText);                 m.attr("ImPlotFlags_NoMouseText")                 = static_cast<int>(ImPlotFlags_NoMouseText);
    e.value("ImPlotFlags_NoInputs",                    ImPlotFlags_NoInputs);                    m.attr("ImPlotFlags_NoInputs")                    = static_cast<int>(ImPlotFlags_NoInputs);
    e.value("ImPlotFlags_NoMenus",                     ImPlotFlags_NoMenus);                     m.attr("ImPlotFlags_NoMenus")                     = static_cast<int>(ImPlotFlags_NoMenus);
    e.value("ImPlotFlags_NoBoxSelect",                 ImPlotFlags_NoBoxSelect);                 m.attr("ImPlotFlags_NoBoxSelect")                 = static_cast<int>(ImPlotFlags_NoBoxSelect);
    e.value("ImPlotFlags_NoFrame",                     ImPlotFlags_NoFrame);                     m.attr("ImPlotFlags_NoFrame")                     = static_cast<int>(ImPlotFlags_NoFrame);
    e.value("ImPlotFlags_Equal",                       ImPlotFlags_Equal);                       m.attr("ImPlotFlags_Equal")                       = static_cast<int>(ImPlotFlags_Equal);
    e.value("ImPlotFlags_Crosshairs",                  ImPlotFlags_Crosshairs);                  m.attr("ImPlotFlags_Crosshairs")                  = static_cast<int>(ImPlotFlags_Crosshairs);
    e.value("ImPlotFlags_CanvasOnly",                  ImPlotFlags_CanvasOnly);                  m.attr("ImPlotFlags_CanvasOnly")                  = static_cast<int>(ImPlotFlags_CanvasOnly);
  ;
  }

  { // ImPlotAxisFlags ImPlotAxisFlags_
  auto e = nb::enum_<ImPlotAxisFlags_>(m, "ImPlotAxisFlags");
    e.value("ImPlotAxisFlags_None",                    ImPlotAxisFlags_None);                    m.attr("ImPlotAxisFlags_None")                    = static_cast<int>(ImPlotAxisFlags_None);
    e.value("ImPlotAxisFlags_NoLabel",                 ImPlotAxisFlags_NoLabel);                 m.attr("ImPlotAxisFlags_NoLabel")                 = static_cast<int>(ImPlotAxisFlags_NoLabel);
    e.value("ImPlotAxisFlags_NoGridLines",             ImPlotAxisFlags_NoGridLines);             m.attr("ImPlotAxisFlags_NoGridLines")             = static_cast<int>(ImPlotAxisFlags_NoGridLines);
    e.value("ImPlotAxisFlags_NoTickMarks",             ImPlotAxisFlags_NoTickMarks);             m.attr("ImPlotAxisFlags_NoTickMarks")             = static_cast<int>(ImPlotAxisFlags_NoTickMarks);
    e.value("ImPlotAxisFlags_NoTickLabels",            ImPlotAxisFlags_NoTickLabels);            m.attr("ImPlotAxisFlags_NoTickLabels")            = static_cast<int>(ImPlotAxisFlags_NoTickLabels);
    e.value("ImPlotAxisFlags_NoInitialFit",            ImPlotAxisFlags_NoInitialFit);            m.attr("ImPlotAxisFlags_NoInitialFit")            = static_cast<int>(ImPlotAxisFlags_NoInitialFit);
    e.value("ImPlotAxisFlags_NoMenus",                 ImPlotAxisFlags_NoMenus);                 m.attr("ImPlotAxisFlags_NoMenus")                 = static_cast<int>(ImPlotAxisFlags_NoMenus);
    e.value("ImPlotAxisFlags_NoSideSwitch",            ImPlotAxisFlags_NoSideSwitch);            m.attr("ImPlotAxisFlags_NoSideSwitch")            = static_cast<int>(ImPlotAxisFlags_NoSideSwitch);
    e.value("ImPlotAxisFlags_NoHighlight",             ImPlotAxisFlags_NoHighlight);             m.attr("ImPlotAxisFlags_NoHighlight")             = static_cast<int>(ImPlotAxisFlags_NoHighlight);
    e.value("ImPlotAxisFlags_Opposite",                ImPlotAxisFlags_Opposite);                m.attr("ImPlotAxisFlags_Opposite")                = static_cast<int>(ImPlotAxisFlags_Opposite);
    e.value("ImPlotAxisFlags_Foreground",              ImPlotAxisFlags_Foreground);              m.attr("ImPlotAxisFlags_Foreground")              = static_cast<int>(ImPlotAxisFlags_Foreground);
    e.value("ImPlotAxisFlags_Invert",                  ImPlotAxisFlags_Invert);                  m.attr("ImPlotAxisFlags_Invert")                  = static_cast<int>(ImPlotAxisFlags_Invert);
    e.value("ImPlotAxisFlags_AutoFit",                 ImPlotAxisFlags_AutoFit);                 m.attr("ImPlotAxisFlags_AutoFit")                 = static_cast<int>(ImPlotAxisFlags_AutoFit);
    e.value("ImPlotAxisFlags_RangeFit",                ImPlotAxisFlags_RangeFit);                m.attr("ImPlotAxisFlags_RangeFit")                = static_cast<int>(ImPlotAxisFlags_RangeFit);
    e.value("ImPlotAxisFlags_PanStretch",              ImPlotAxisFlags_PanStretch);              m.attr("ImPlotAxisFlags_PanStretch")              = static_cast<int>(ImPlotAxisFlags_PanStretch);
    e.value("ImPlotAxisFlags_LockMin",                 ImPlotAxisFlags_LockMin);                 m.attr("ImPlotAxisFlags_LockMin")                 = static_cast<int>(ImPlotAxisFlags_LockMin);
    e.value("ImPlotAxisFlags_LockMax",                 ImPlotAxisFlags_LockMax);                 m.attr("ImPlotAxisFlags_LockMax")                 = static_cast<int>(ImPlotAxisFlags_LockMax);
    e.value("ImPlotAxisFlags_Lock",                    ImPlotAxisFlags_Lock);                    m.attr("ImPlotAxisFlags_Lock")                    = static_cast<int>(ImPlotAxisFlags_Lock);
    e.value("ImPlotAxisFlags_NoDecorations",           ImPlotAxisFlags_NoDecorations);           m.attr("ImPlotAxisFlags_NoDecorations")           = static_cast<int>(ImPlotAxisFlags_NoDecorations);
    e.value("ImPlotAxisFlags_AuxDefault",              ImPlotAxisFlags_AuxDefault);              m.attr("ImPlotAxisFlags_AuxDefault")              = static_cast<int>(ImPlotAxisFlags_AuxDefault);
  ;
  }

  { // ImPlotSubplotFlags ImPlotSubplotFlags_
  auto e = nb::enum_<ImPlotSubplotFlags_>(m, "ImPlotSubplotFlags");
    e.value("ImPlotSubplotFlags_None",                 ImPlotSubplotFlags_None);                 m.attr("ImPlotSubplotFlags_None")                 = static_cast<int>(ImPlotSubplotFlags_None);
    e.value("ImPlotSubplotFlags_NoTitle",              ImPlotSubplotFlags_NoTitle);              m.attr("ImPlotSubplotFlags_NoTitle")              = static_cast<int>(ImPlotSubplotFlags_NoTitle);
    e.value("ImPlotSubplotFlags_NoLegend",             ImPlotSubplotFlags_NoLegend);             m.attr("ImPlotSubplotFlags_NoLegend")             = static_cast<int>(ImPlotSubplotFlags_NoLegend);
    e.value("ImPlotSubplotFlags_NoMenus",              ImPlotSubplotFlags_NoMenus);              m.attr("ImPlotSubplotFlags_NoMenus")              = static_cast<int>(ImPlotSubplotFlags_NoMenus);
    e.value("ImPlotSubplotFlags_NoResize",             ImPlotSubplotFlags_NoResize);             m.attr("ImPlotSubplotFlags_NoResize")             = static_cast<int>(ImPlotSubplotFlags_NoResize);
    e.value("ImPlotSubplotFlags_NoAlign",              ImPlotSubplotFlags_NoAlign);              m.attr("ImPlotSubplotFlags_NoAlign")              = static_cast<int>(ImPlotSubplotFlags_NoAlign);
    e.value("ImPlotSubplotFlags_ShareItems",           ImPlotSubplotFlags_ShareItems);           m.attr("ImPlotSubplotFlags_ShareItems")           = static_cast<int>(ImPlotSubplotFlags_ShareItems);
    e.value("ImPlotSubplotFlags_LinkRows",             ImPlotSubplotFlags_LinkRows);             m.attr("ImPlotSubplotFlags_LinkRows")             = static_cast<int>(ImPlotSubplotFlags_LinkRows);
    e.value("ImPlotSubplotFlags_LinkCols",             ImPlotSubplotFlags_LinkCols);             m.attr("ImPlotSubplotFlags_LinkCols")             = static_cast<int>(ImPlotSubplotFlags_LinkCols);
    e.value("ImPlotSubplotFlags_LinkAllX",             ImPlotSubplotFlags_LinkAllX);             m.attr("ImPlotSubplotFlags_LinkAllX")             = static_cast<int>(ImPlotSubplotFlags_LinkAllX);
    e.value("ImPlotSubplotFlags_LinkAllY",             ImPlotSubplotFlags_LinkAllY);             m.attr("ImPlotSubplotFlags_LinkAllY")             = static_cast<int>(ImPlotSubplotFlags_LinkAllY);
    e.value("ImPlotSubplotFlags_ColMajor",             ImPlotSubplotFlags_ColMajor);             m.attr("ImPlotSubplotFlags_ColMajor")             = static_cast<int>(ImPlotSubplotFlags_ColMajor);
  ;
  }

  { // ImPlotLegendFlags ImPlotLegendFlags_
  auto e = nb::enum_<ImPlotLegendFlags_>(m, "ImPlotLegendFlags");
    e.value("ImPlotLegendFlags_None",                  ImPlotLegendFlags_None);                  m.attr("ImPlotLegendFlags_None")                  = static_cast<int>(ImPlotLegendFlags_None);
    e.value("ImPlotLegendFlags_NoButtons",             ImPlotLegendFlags_NoButtons);             m.attr("ImPlotLegendFlags_NoButtons")             = static_cast<int>(ImPlotLegendFlags_NoButtons);
    e.value("ImPlotLegendFlags_NoHighlightItem",       ImPlotLegendFlags_NoHighlightItem);       m.attr("ImPlotLegendFlags_NoHighlightItem")       = static_cast<int>(ImPlotLegendFlags_NoHighlightItem);
    e.value("ImPlotLegendFlags_NoHighlightAxis",       ImPlotLegendFlags_NoHighlightAxis);       m.attr("ImPlotLegendFlags_NoHighlightAxis")       = static_cast<int>(ImPlotLegendFlags_NoHighlightAxis);
    e.value("ImPlotLegendFlags_NoMenus",               ImPlotLegendFlags_NoMenus);               m.attr("ImPlotLegendFlags_NoMenus")               = static_cast<int>(ImPlotLegendFlags_NoMenus);
    e.value("ImPlotLegendFlags_Outside",               ImPlotLegendFlags_Outside);               m.attr("ImPlotLegendFlags_Outside")               = static_cast<int>(ImPlotLegendFlags_Outside);
    e.value("ImPlotLegendFlags_Horizontal",            ImPlotLegendFlags_Horizontal);            m.attr("ImPlotLegendFlags_Horizontal")            = static_cast<int>(ImPlotLegendFlags_Horizontal);
    e.value("ImPlotLegendFlags_Sort",                  ImPlotLegendFlags_Sort);                  m.attr("ImPlotLegendFlags_Sort")                  = static_cast<int>(ImPlotLegendFlags_Sort);
  ;
  }

  { // ImPlotMouseTextFlags ImPlotMouseTextFlags_
  auto e = nb::enum_<ImPlotMouseTextFlags_>(m, "ImPlotMouseTextFlags");
    e.value("ImPlotMouseTextFlags_None",               ImPlotMouseTextFlags_None);               m.attr("ImPlotMouseTextFlags_None")               = static_cast<int>(ImPlotMouseTextFlags_None);
    e.value("ImPlotMouseTextFlags_NoAuxAxes",          ImPlotMouseTextFlags_NoAuxAxes);          m.attr("ImPlotMouseTextFlags_NoAuxAxes")          = static_cast<int>(ImPlotMouseTextFlags_NoAuxAxes);
    e.value("ImPlotMouseTextFlags_NoFormat",           ImPlotMouseTextFlags_NoFormat);           m.attr("ImPlotMouseTextFlags_NoFormat")           = static_cast<int>(ImPlotMouseTextFlags_NoFormat);
    e.value("ImPlotMouseTextFlags_ShowAlways",         ImPlotMouseTextFlags_ShowAlways);         m.attr("ImPlotMouseTextFlags_ShowAlways")         = static_cast<int>(ImPlotMouseTextFlags_ShowAlways);
  ;
  }

  { // ImPlotDragToolFlags ImPlotDragToolFlags_
  auto e = nb::enum_<ImPlotDragToolFlags_>(m, "ImPlotDragToolFlags");
    e.value("ImPlotDragToolFlags_None",                ImPlotDragToolFlags_None);                m.attr("ImPlotDragToolFlags_None")                = static_cast<int>(ImPlotDragToolFlags_None);
    e.value("ImPlotDragToolFlags_NoCursors",           ImPlotDragToolFlags_NoCursors);           m.attr("ImPlotDragToolFlags_NoCursors")           = static_cast<int>(ImPlotDragToolFlags_NoCursors);
    e.value("ImPlotDragToolFlags_NoFit",               ImPlotDragToolFlags_NoFit);               m.attr("ImPlotDragToolFlags_NoFit")               = static_cast<int>(ImPlotDragToolFlags_NoFit);
    e.value("ImPlotDragToolFlags_NoInputs",            ImPlotDragToolFlags_NoInputs);            m.attr("ImPlotDragToolFlags_NoInputs")            = static_cast<int>(ImPlotDragToolFlags_NoInputs);
    e.value("ImPlotDragToolFlags_Delayed",             ImPlotDragToolFlags_Delayed);             m.attr("ImPlotDragToolFlags_Delayed")             = static_cast<int>(ImPlotDragToolFlags_Delayed);
  ;
  }

  { // ImPlotColormapScaleFlags ImPlotColormapScaleFlags_
  auto e = nb::enum_<ImPlotColormapScaleFlags_>(m, "ImPlotColormapScaleFlags");
    e.value("ImPlotColormapScaleFlags_None",           ImPlotColormapScaleFlags_None);           m.attr("ImPlotColormapScaleFlags_None")           = static_cast<int>(ImPlotColormapScaleFlags_None);
    e.value("ImPlotColormapScaleFlags_NoLabel",        ImPlotColormapScaleFlags_NoLabel);        m.attr("ImPlotColormapScaleFlags_NoLabel")        = static_cast<int>(ImPlotColormapScaleFlags_NoLabel);
    e.value("ImPlotColormapScaleFlags_Opposite",       ImPlotColormapScaleFlags_Opposite);       m.attr("ImPlotColormapScaleFlags_Opposite")       = static_cast<int>(ImPlotColormapScaleFlags_Opposite);
    e.value("ImPlotColormapScaleFlags_Invert",         ImPlotColormapScaleFlags_Invert);         m.attr("ImPlotColormapScaleFlags_Invert")         = static_cast<int>(ImPlotColormapScaleFlags_Invert);
  ;
  }

  { // ImPlotItemFlags ImPlotItemFlags_
  auto e = nb::enum_<ImPlotItemFlags_>(m, "ImPlotItemFlags");
    e.value("ImPlotItemFlags_None",                    ImPlotItemFlags_None);                    m.attr("ImPlotItemFlags_None")                    = static_cast<int>(ImPlotItemFlags_None);
    e.value("ImPlotItemFlags_NoLegend",                ImPlotItemFlags_NoLegend);                m.attr("ImPlotItemFlags_NoLegend")                = static_cast<int>(ImPlotItemFlags_NoLegend);
    e.value("ImPlotItemFlags_NoFit",                   ImPlotItemFlags_NoFit);                   m.attr("ImPlotItemFlags_NoFit")                   = static_cast<int>(ImPlotItemFlags_NoFit);
  ;
  }

  { // ImPlotLineFlags ImPlotLineFlags_
  auto e = nb::enum_<ImPlotLineFlags_>(m, "ImPlotLineFlags");
    e.value("ImPlotLineFlags_None",                    ImPlotLineFlags_None);                    m.attr("ImPlotLineFlags_None")                    = static_cast<int>(ImPlotLineFlags_None);
    e.value("ImPlotLineFlags_Segments",                ImPlotLineFlags_Segments);                m.attr("ImPlotLineFlags_Segments")                = static_cast<int>(ImPlotLineFlags_Segments);
    e.value("ImPlotLineFlags_Loop",                    ImPlotLineFlags_Loop);                    m.attr("ImPlotLineFlags_Loop")                    = static_cast<int>(ImPlotLineFlags_Loop);
    e.value("ImPlotLineFlags_SkipNaN",                 ImPlotLineFlags_SkipNaN);                 m.attr("ImPlotLineFlags_SkipNaN")                 = static_cast<int>(ImPlotLineFlags_SkipNaN);
    e.value("ImPlotLineFlags_NoClip",                  ImPlotLineFlags_NoClip);                  m.attr("ImPlotLineFlags_NoClip")                  = static_cast<int>(ImPlotLineFlags_NoClip);
    e.value("ImPlotLineFlags_Shaded",                  ImPlotLineFlags_Shaded);                  m.attr("ImPlotLineFlags_Shaded")                  = static_cast<int>(ImPlotLineFlags_Shaded);
  ;
  }

  { // ImPlotScatterFlags ImPlotScatterFlags_
  auto e = nb::enum_<ImPlotScatterFlags_>(m, "ImPlotScatterFlags");
    e.value("ImPlotScatterFlags_None",                 ImPlotScatterFlags_None);                 m.attr("ImPlotScatterFlags_None")                 = static_cast<int>(ImPlotScatterFlags_None);
    e.value("ImPlotScatterFlags_NoClip",               ImPlotScatterFlags_NoClip);               m.attr("ImPlotScatterFlags_NoClip")               = static_cast<int>(ImPlotScatterFlags_NoClip);
  ;
  }

  { // ImPlotStairsFlags ImPlotStairsFlags_
  auto e = nb::enum_<ImPlotStairsFlags_>(m, "ImPlotStairsFlags");
    e.value("ImPlotStairsFlags_None",                  ImPlotStairsFlags_None);                  m.attr("ImPlotStairsFlags_None")                  = static_cast<int>(ImPlotStairsFlags_None);
    e.value("ImPlotStairsFlags_PreStep",               ImPlotStairsFlags_PreStep);               m.attr("ImPlotStairsFlags_PreStep")               = static_cast<int>(ImPlotStairsFlags_PreStep);
    e.value("ImPlotStairsFlags_Shaded",                ImPlotStairsFlags_Shaded);                m.attr("ImPlotStairsFlags_Shaded")                = static_cast<int>(ImPlotStairsFlags_Shaded);
  ;
  }

  { // ImPlotShadedFlags ImPlotShadedFlags_
  auto e = nb::enum_<ImPlotShadedFlags_>(m, "ImPlotShadedFlags");
    e.value("ImPlotShadedFlags_None",                  ImPlotShadedFlags_None);                  m.attr("ImPlotShadedFlags_None")                  = static_cast<int>(ImPlotShadedFlags_None);
  ;
  }

  { // ImPlotBarsFlags ImPlotBarsFlags_
  auto e = nb::enum_<ImPlotBarsFlags_>(m, "ImPlotBarsFlags");
    e.value("ImPlotBarsFlags_None",                    ImPlotBarsFlags_None);                    m.attr("ImPlotBarsFlags_None")                    = static_cast<int>(ImPlotBarsFlags_None);
    e.value("ImPlotBarsFlags_Horizontal",              ImPlotBarsFlags_Horizontal);              m.attr("ImPlotBarsFlags_Horizontal")              = static_cast<int>(ImPlotBarsFlags_Horizontal);
  ;
  }

  { // ImPlotBarGroupsFlags ImPlotBarGroupsFlags_
  auto e = nb::enum_<ImPlotBarGroupsFlags_>(m, "ImPlotBarGroupsFlags");
    e.value("ImPlotBarGroupsFlags_None",               ImPlotBarGroupsFlags_None);               m.attr("ImPlotBarGroupsFlags_None")               = static_cast<int>(ImPlotBarGroupsFlags_None);
    e.value("ImPlotBarGroupsFlags_Horizontal",         ImPlotBarGroupsFlags_Horizontal);         m.attr("ImPlotBarGroupsFlags_Horizontal")         = static_cast<int>(ImPlotBarGroupsFlags_Horizontal);
    e.value("ImPlotBarGroupsFlags_Stacked",            ImPlotBarGroupsFlags_Stacked);            m.attr("ImPlotBarGroupsFlags_Stacked")            = static_cast<int>(ImPlotBarGroupsFlags_Stacked);
  ;
  }

  { // ImPlotErrorBarsFlags ImPlotErrorBarsFlags_
  auto e = nb::enum_<ImPlotErrorBarsFlags_>(m, "ImPlotErrorBarsFlags");
    e.value("ImPlotErrorBarsFlags_None",               ImPlotErrorBarsFlags_None);               m.attr("ImPlotErrorBarsFlags_None")               = static_cast<int>(ImPlotErrorBarsFlags_None);
    e.value("ImPlotErrorBarsFlags_Horizontal",         ImPlotErrorBarsFlags_Horizontal);         m.attr("ImPlotErrorBarsFlags_Horizontal")         = static_cast<int>(ImPlotErrorBarsFlags_Horizontal);
  ;
  }

  { // ImPlotStemsFlags ImPlotStemsFlags_
  auto e = nb::enum_<ImPlotStemsFlags_>(m, "ImPlotStemsFlags");
    e.value("ImPlotStemsFlags_None",                   ImPlotStemsFlags_None);                   m.attr("ImPlotStemsFlags_None")                   = static_cast<int>(ImPlotStemsFlags_None);
    e.value("ImPlotStemsFlags_Horizontal",             ImPlotStemsFlags_Horizontal);             m.attr("ImPlotStemsFlags_Horizontal")             = static_cast<int>(ImPlotStemsFlags_Horizontal);
  ;
  }

  { // ImPlotInfLinesFlags ImPlotInfLinesFlags_
  auto e = nb::enum_<ImPlotInfLinesFlags_>(m, "ImPlotInfLinesFlags");
    e.value("ImPlotInfLinesFlags_None",                ImPlotInfLinesFlags_None);                m.attr("ImPlotInfLinesFlags_None")                = static_cast<int>(ImPlotInfLinesFlags_None);
    e.value("ImPlotInfLinesFlags_Horizontal",          ImPlotInfLinesFlags_Horizontal);          m.attr("ImPlotInfLinesFlags_Horizontal")          = static_cast<int>(ImPlotInfLinesFlags_Horizontal);
  ;
  }

  { // ImPlotPieChartFlags ImPlotPieChartFlags_
  auto e = nb::enum_<ImPlotPieChartFlags_>(m, "ImPlotPieChartFlags");
    e.value("ImPlotPieChartFlags_None",                ImPlotPieChartFlags_None);                m.attr("ImPlotPieChartFlags_None")                = static_cast<int>(ImPlotPieChartFlags_None);
    e.value("ImPlotPieChartFlags_Normalize",           ImPlotPieChartFlags_Normalize);           m.attr("ImPlotPieChartFlags_Normalize")           = static_cast<int>(ImPlotPieChartFlags_Normalize);
    e.value("ImPlotPieChartFlags_IgnoreHidden",        ImPlotPieChartFlags_IgnoreHidden);        m.attr("ImPlotPieChartFlags_IgnoreHidden")        = static_cast<int>(ImPlotPieChartFlags_IgnoreHidden);
    e.value("ImPlotPieChartFlags_Exploding",           ImPlotPieChartFlags_Exploding);           m.attr("ImPlotPieChartFlags_Exploding")           = static_cast<int>(ImPlotPieChartFlags_Exploding);
  ;
  }

  { // ImPlotHeatmapFlags ImPlotHeatmapFlags_
  auto e = nb::enum_<ImPlotHeatmapFlags_>(m, "ImPlotHeatmapFlags");
    e.value("ImPlotHeatmapFlags_None",                 ImPlotHeatmapFlags_None);                 m.attr("ImPlotHeatmapFlags_None")                 = static_cast<int>(ImPlotHeatmapFlags_None);
    e.value("ImPlotHeatmapFlags_ColMajor",             ImPlotHeatmapFlags_ColMajor);             m.attr("ImPlotHeatmapFlags_ColMajor")             = static_cast<int>(ImPlotHeatmapFlags_ColMajor);
  ;
  }

  { // ImPlotHistogramFlags ImPlotHistogramFlags_
  auto e = nb::enum_<ImPlotHistogramFlags_>(m, "ImPlotHistogramFlags");
    e.value("ImPlotHistogramFlags_None",               ImPlotHistogramFlags_None);               m.attr("ImPlotHistogramFlags_None")               = static_cast<int>(ImPlotHistogramFlags_None);
    e.value("ImPlotHistogramFlags_Horizontal",         ImPlotHistogramFlags_Horizontal);         m.attr("ImPlotHistogramFlags_Horizontal")         = static_cast<int>(ImPlotHistogramFlags_Horizontal);
    e.value("ImPlotHistogramFlags_Cumulative",         ImPlotHistogramFlags_Cumulative);         m.attr("ImPlotHistogramFlags_Cumulative")         = static_cast<int>(ImPlotHistogramFlags_Cumulative);
    e.value("ImPlotHistogramFlags_Density",            ImPlotHistogramFlags_Density);            m.attr("ImPlotHistogramFlags_Density")            = static_cast<int>(ImPlotHistogramFlags_Density);
    e.value("ImPlotHistogramFlags_NoOutliers",         ImPlotHistogramFlags_NoOutliers);         m.attr("ImPlotHistogramFlags_NoOutliers")         = static_cast<int>(ImPlotHistogramFlags_NoOutliers);
    e.value("ImPlotHistogramFlags_ColMajor",           ImPlotHistogramFlags_ColMajor);           m.attr("ImPlotHistogramFlags_ColMajor")           = static_cast<int>(ImPlotHistogramFlags_ColMajor);
  ;
  }

  { // ImPlotDigitalFlags ImPlotDigitalFlags_
  auto e = nb::enum_<ImPlotDigitalFlags_>(m, "ImPlotDigitalFlags");
    e.value("ImPlotDigitalFlags_None",                 ImPlotDigitalFlags_None);                 m.attr("ImPlotDigitalFlags_None")                 = static_cast<int>(ImPlotDigitalFlags_None);
  ;
  }

  { // ImPlotImageFlags ImPlotImageFlags_
  auto e = nb::enum_<ImPlotImageFlags_>(m, "ImPlotImageFlags");
    e.value("ImPlotImageFlags_None",                   ImPlotImageFlags_None);                   m.attr("ImPlotImageFlags_None")                   = static_cast<int>(ImPlotImageFlags_None);
  ;
  }

  { // ImPlotTextFlags ImPlotTextFlags_
  auto e = nb::enum_<ImPlotTextFlags_>(m, "ImPlotTextFlags");
    e.value("ImPlotTextFlags_None",                    ImPlotTextFlags_None);                    m.attr("ImPlotTextFlags_None")                    = static_cast<int>(ImPlotTextFlags_None);
    e.value("ImPlotTextFlags_Vertical",                ImPlotTextFlags_Vertical);                m.attr("ImPlotTextFlags_Vertical")                = static_cast<int>(ImPlotTextFlags_Vertical);
  ;
  }

  { // ImPlotDummyFlags ImPlotDummyFlags_
  auto e = nb::enum_<ImPlotDummyFlags_>(m, "ImPlotDummyFlags");
    e.value("ImPlotDummyFlags_None",                   ImPlotDummyFlags_None);                   m.attr("ImPlotDummyFlags_None")                   = static_cast<int>(ImPlotDummyFlags_None);
  ;
  }

  { // ImPlotCond ImPlotCond_
  auto e = nb::enum_<ImPlotCond_>(m, "ImPlotCond");
    e.value("ImPlotCond_None",                         ImPlotCond_None);                         m.attr("ImPlotCond_None")                         = static_cast<int>(ImPlotCond_None);
    e.value("ImPlotCond_Always",                       ImPlotCond_Always);                       m.attr("ImPlotCond_Always")                       = static_cast<int>(ImPlotCond_Always);
    e.value("ImPlotCond_Once",                         ImPlotCond_Once);                         m.attr("ImPlotCond_Once")                         = static_cast<int>(ImPlotCond_Once);
  ;
  }

  { // ImPlotCol ImPlotCol_
  auto e = nb::enum_<ImPlotCol_>(m, "ImPlotCol");
    e.value("ImPlotCol_Line",                          ImPlotCol_Line);                          m.attr("ImPlotCol_Line")                          = static_cast<int>(ImPlotCol_Line);
    e.value("ImPlotCol_Fill",                          ImPlotCol_Fill);                          m.attr("ImPlotCol_Fill")                          = static_cast<int>(ImPlotCol_Fill);
    e.value("ImPlotCol_MarkerOutline",                 ImPlotCol_MarkerOutline);                 m.attr("ImPlotCol_MarkerOutline")                 = static_cast<int>(ImPlotCol_MarkerOutline);
    e.value("ImPlotCol_MarkerFill",                    ImPlotCol_MarkerFill);                    m.attr("ImPlotCol_MarkerFill")                    = static_cast<int>(ImPlotCol_MarkerFill);
    e.value("ImPlotCol_ErrorBar",                      ImPlotCol_ErrorBar);                      m.attr("ImPlotCol_ErrorBar")                      = static_cast<int>(ImPlotCol_ErrorBar);
    e.value("ImPlotCol_FrameBg",                       ImPlotCol_FrameBg);                       m.attr("ImPlotCol_FrameBg")                       = static_cast<int>(ImPlotCol_FrameBg);
    e.value("ImPlotCol_PlotBg",                        ImPlotCol_PlotBg);                        m.attr("ImPlotCol_PlotBg")                        = static_cast<int>(ImPlotCol_PlotBg);
    e.value("ImPlotCol_PlotBorder",                    ImPlotCol_PlotBorder);                    m.attr("ImPlotCol_PlotBorder")                    = static_cast<int>(ImPlotCol_PlotBorder);
    e.value("ImPlotCol_LegendBg",                      ImPlotCol_LegendBg);                      m.attr("ImPlotCol_LegendBg")                      = static_cast<int>(ImPlotCol_LegendBg);
    e.value("ImPlotCol_LegendBorder",                  ImPlotCol_LegendBorder);                  m.attr("ImPlotCol_LegendBorder")                  = static_cast<int>(ImPlotCol_LegendBorder);
    e.value("ImPlotCol_LegendText",                    ImPlotCol_LegendText);                    m.attr("ImPlotCol_LegendText")                    = static_cast<int>(ImPlotCol_LegendText);
    e.value("ImPlotCol_TitleText",                     ImPlotCol_TitleText);                     m.attr("ImPlotCol_TitleText")                     = static_cast<int>(ImPlotCol_TitleText);
    e.value("ImPlotCol_InlayText",                     ImPlotCol_InlayText);                     m.attr("ImPlotCol_InlayText")                     = static_cast<int>(ImPlotCol_InlayText);
    e.value("ImPlotCol_AxisText",                      ImPlotCol_AxisText);                      m.attr("ImPlotCol_AxisText")                      = static_cast<int>(ImPlotCol_AxisText);
    e.value("ImPlotCol_AxisGrid",                      ImPlotCol_AxisGrid);                      m.attr("ImPlotCol_AxisGrid")                      = static_cast<int>(ImPlotCol_AxisGrid);
    e.value("ImPlotCol_AxisTick",                      ImPlotCol_AxisTick);                      m.attr("ImPlotCol_AxisTick")                      = static_cast<int>(ImPlotCol_AxisTick);
    e.value("ImPlotCol_AxisBg",                        ImPlotCol_AxisBg);                        m.attr("ImPlotCol_AxisBg")                        = static_cast<int>(ImPlotCol_AxisBg);
    e.value("ImPlotCol_AxisBgHovered",                 ImPlotCol_AxisBgHovered);                 m.attr("ImPlotCol_AxisBgHovered")                 = static_cast<int>(ImPlotCol_AxisBgHovered);
    e.value("ImPlotCol_AxisBgActive",                  ImPlotCol_AxisBgActive);                  m.attr("ImPlotCol_AxisBgActive")                  = static_cast<int>(ImPlotCol_AxisBgActive);
    e.value("ImPlotCol_Selection",                     ImPlotCol_Selection);                     m.attr("ImPlotCol_Selection")                     = static_cast<int>(ImPlotCol_Selection);
    e.value("ImPlotCol_Crosshairs",                    ImPlotCol_Crosshairs);                    m.attr("ImPlotCol_Crosshairs")                    = static_cast<int>(ImPlotCol_Crosshairs);
    e.value("ImPlotCol_COUNT",                         ImPlotCol_COUNT);                         m.attr("ImPlotCol_COUNT")                         = static_cast<int>(ImPlotCol_COUNT);
  ;
  }

  { // ImPlotStyleVar ImPlotStyleVar_
  auto e = nb::enum_<ImPlotStyleVar_>(m, "ImPlotStyleVar");
    e.value("ImPlotStyleVar_LineWeight",               ImPlotStyleVar_LineWeight);               m.attr("ImPlotStyleVar_LineWeight")               = static_cast<int>(ImPlotStyleVar_LineWeight);
    e.value("ImPlotStyleVar_Marker",                   ImPlotStyleVar_Marker);                   m.attr("ImPlotStyleVar_Marker")                   = static_cast<int>(ImPlotStyleVar_Marker);
    e.value("ImPlotStyleVar_MarkerSize",               ImPlotStyleVar_MarkerSize);               m.attr("ImPlotStyleVar_MarkerSize")               = static_cast<int>(ImPlotStyleVar_MarkerSize);
    e.value("ImPlotStyleVar_MarkerWeight",             ImPlotStyleVar_MarkerWeight);             m.attr("ImPlotStyleVar_MarkerWeight")             = static_cast<int>(ImPlotStyleVar_MarkerWeight);
    e.value("ImPlotStyleVar_FillAlpha",                ImPlotStyleVar_FillAlpha);                m.attr("ImPlotStyleVar_FillAlpha")                = static_cast<int>(ImPlotStyleVar_FillAlpha);
    e.value("ImPlotStyleVar_ErrorBarSize",             ImPlotStyleVar_ErrorBarSize);             m.attr("ImPlotStyleVar_ErrorBarSize")             = static_cast<int>(ImPlotStyleVar_ErrorBarSize);
    e.value("ImPlotStyleVar_ErrorBarWeight",           ImPlotStyleVar_ErrorBarWeight);           m.attr("ImPlotStyleVar_ErrorBarWeight")           = static_cast<int>(ImPlotStyleVar_ErrorBarWeight);
    e.value("ImPlotStyleVar_DigitalBitHeight",         ImPlotStyleVar_DigitalBitHeight);         m.attr("ImPlotStyleVar_DigitalBitHeight")         = static_cast<int>(ImPlotStyleVar_DigitalBitHeight);
    e.value("ImPlotStyleVar_DigitalBitGap",            ImPlotStyleVar_DigitalBitGap);            m.attr("ImPlotStyleVar_DigitalBitGap")            = static_cast<int>(ImPlotStyleVar_DigitalBitGap);
    e.value("ImPlotStyleVar_PlotBorderSize",           ImPlotStyleVar_PlotBorderSize);           m.attr("ImPlotStyleVar_PlotBorderSize")           = static_cast<int>(ImPlotStyleVar_PlotBorderSize);
    e.value("ImPlotStyleVar_MinorAlpha",               ImPlotStyleVar_MinorAlpha);               m.attr("ImPlotStyleVar_MinorAlpha")               = static_cast<int>(ImPlotStyleVar_MinorAlpha);
    e.value("ImPlotStyleVar_MajorTickLen",             ImPlotStyleVar_MajorTickLen);             m.attr("ImPlotStyleVar_MajorTickLen")             = static_cast<int>(ImPlotStyleVar_MajorTickLen);
    e.value("ImPlotStyleVar_MinorTickLen",             ImPlotStyleVar_MinorTickLen);             m.attr("ImPlotStyleVar_MinorTickLen")             = static_cast<int>(ImPlotStyleVar_MinorTickLen);
    e.value("ImPlotStyleVar_MajorTickSize",            ImPlotStyleVar_MajorTickSize);            m.attr("ImPlotStyleVar_MajorTickSize")            = static_cast<int>(ImPlotStyleVar_MajorTickSize);
    e.value("ImPlotStyleVar_MinorTickSize",            ImPlotStyleVar_MinorTickSize);            m.attr("ImPlotStyleVar_MinorTickSize")            = static_cast<int>(ImPlotStyleVar_MinorTickSize);
    e.value("ImPlotStyleVar_MajorGridSize",            ImPlotStyleVar_MajorGridSize);            m.attr("ImPlotStyleVar_MajorGridSize")            = static_cast<int>(ImPlotStyleVar_MajorGridSize);
    e.value("ImPlotStyleVar_MinorGridSize",            ImPlotStyleVar_MinorGridSize);            m.attr("ImPlotStyleVar_MinorGridSize")            = static_cast<int>(ImPlotStyleVar_MinorGridSize);
    e.value("ImPlotStyleVar_PlotPadding",              ImPlotStyleVar_PlotPadding);              m.attr("ImPlotStyleVar_PlotPadding")              = static_cast<int>(ImPlotStyleVar_PlotPadding);
    e.value("ImPlotStyleVar_LabelPadding",             ImPlotStyleVar_LabelPadding);             m.attr("ImPlotStyleVar_LabelPadding")             = static_cast<int>(ImPlotStyleVar_LabelPadding);
    e.value("ImPlotStyleVar_LegendPadding",            ImPlotStyleVar_LegendPadding);            m.attr("ImPlotStyleVar_LegendPadding")            = static_cast<int>(ImPlotStyleVar_LegendPadding);
    e.value("ImPlotStyleVar_LegendInnerPadding",       ImPlotStyleVar_LegendInnerPadding);       m.attr("ImPlotStyleVar_LegendInnerPadding")       = static_cast<int>(ImPlotStyleVar_LegendInnerPadding);
    e.value("ImPlotStyleVar_LegendSpacing",            ImPlotStyleVar_LegendSpacing);            m.attr("ImPlotStyleVar_LegendSpacing")            = static_cast<int>(ImPlotStyleVar_LegendSpacing);
    e.value("ImPlotStyleVar_MousePosPadding",          ImPlotStyleVar_MousePosPadding);          m.attr("ImPlotStyleVar_MousePosPadding")          = static_cast<int>(ImPlotStyleVar_MousePosPadding);
    e.value("ImPlotStyleVar_AnnotationPadding",        ImPlotStyleVar_AnnotationPadding);        m.attr("ImPlotStyleVar_AnnotationPadding")        = static_cast<int>(ImPlotStyleVar_AnnotationPadding);
    e.value("ImPlotStyleVar_FitPadding",               ImPlotStyleVar_FitPadding);               m.attr("ImPlotStyleVar_FitPadding")               = static_cast<int>(ImPlotStyleVar_FitPadding);
    e.value("ImPlotStyleVar_PlotDefaultSize",          ImPlotStyleVar_PlotDefaultSize);          m.attr("ImPlotStyleVar_PlotDefaultSize")          = static_cast<int>(ImPlotStyleVar_PlotDefaultSize);
    e.value("ImPlotStyleVar_PlotMinSize",              ImPlotStyleVar_PlotMinSize);              m.attr("ImPlotStyleVar_PlotMinSize")              = static_cast<int>(ImPlotStyleVar_PlotMinSize);
    e.value("ImPlotStyleVar_COUNT",                    ImPlotStyleVar_COUNT);                    m.attr("ImPlotStyleVar_COUNT")                    = static_cast<int>(ImPlotStyleVar_COUNT);
  ;
  }

  { // ImPlotScale ImPlotScale_
  auto e = nb::enum_<ImPlotScale_>(m, "ImPlotScale");
    e.value("ImPlotScale_Linear",                      ImPlotScale_Linear);                      m.attr("ImPlotScale_Linear")                      = static_cast<int>(ImPlotScale_Linear);
    e.value("ImPlotScale_Time",                        ImPlotScale_Time);                        m.attr("ImPlotScale_Time")                        = static_cast<int>(ImPlotScale_Time);
    e.value("ImPlotScale_Log10",                       ImPlotScale_Log10);                       m.attr("ImPlotScale_Log10")                       = static_cast<int>(ImPlotScale_Log10);
    e.value("ImPlotScale_SymLog",                      ImPlotScale_SymLog);                      m.attr("ImPlotScale_SymLog")                      = static_cast<int>(ImPlotScale_SymLog);
  ;
  }

  { // ImPlotMarker ImPlotMarker_
  auto e = nb::enum_<ImPlotMarker_>(m, "ImPlotMarker");
    e.value("ImPlotMarker_None",                       ImPlotMarker_None);                       m.attr("ImPlotMarker_None")                       = static_cast<int>(ImPlotMarker_None);
    e.value("ImPlotMarker_Circle",                     ImPlotMarker_Circle);                     m.attr("ImPlotMarker_Circle")                     = static_cast<int>(ImPlotMarker_Circle);
    e.value("ImPlotMarker_Square",                     ImPlotMarker_Square);                     m.attr("ImPlotMarker_Square")                     = static_cast<int>(ImPlotMarker_Square);
    e.value("ImPlotMarker_Diamond",                    ImPlotMarker_Diamond);                    m.attr("ImPlotMarker_Diamond")                    = static_cast<int>(ImPlotMarker_Diamond);
    e.value("ImPlotMarker_Up",                         ImPlotMarker_Up);                         m.attr("ImPlotMarker_Up")                         = static_cast<int>(ImPlotMarker_Up);
    e.value("ImPlotMarker_Down",                       ImPlotMarker_Down);                       m.attr("ImPlotMarker_Down")                       = static_cast<int>(ImPlotMarker_Down);
    e.value("ImPlotMarker_Left",                       ImPlotMarker_Left);                       m.attr("ImPlotMarker_Left")                       = static_cast<int>(ImPlotMarker_Left);
    e.value("ImPlotMarker_Right",                      ImPlotMarker_Right);                      m.attr("ImPlotMarker_Right")                      = static_cast<int>(ImPlotMarker_Right);
    e.value("ImPlotMarker_Cross",                      ImPlotMarker_Cross);                      m.attr("ImPlotMarker_Cross")                      = static_cast<int>(ImPlotMarker_Cross);
    e.value("ImPlotMarker_Plus",                       ImPlotMarker_Plus);                       m.attr("ImPlotMarker_Plus")                       = static_cast<int>(ImPlotMarker_Plus);
    e.value("ImPlotMarker_Asterisk",                   ImPlotMarker_Asterisk);                   m.attr("ImPlotMarker_Asterisk")                   = static_cast<int>(ImPlotMarker_Asterisk);
    e.value("ImPlotMarker_COUNT",                      ImPlotMarker_COUNT);                      m.attr("ImPlotMarker_COUNT")                      = static_cast<int>(ImPlotMarker_COUNT);
  ;
  }

  { // ImPlotColormap ImPlotColormap_
  auto e = nb::enum_<ImPlotColormap_>(m, "ImPlotColormap");
    e.value("ImPlotColormap_Deep",                     ImPlotColormap_Deep);                     m.attr("ImPlotColormap_Deep")                     = static_cast<int>(ImPlotColormap_Deep);
    e.value("ImPlotColormap_Dark",                     ImPlotColormap_Dark);                     m.attr("ImPlotColormap_Dark")                     = static_cast<int>(ImPlotColormap_Dark);
    e.value("ImPlotColormap_Pastel",                   ImPlotColormap_Pastel);                   m.attr("ImPlotColormap_Pastel")                   = static_cast<int>(ImPlotColormap_Pastel);
    e.value("ImPlotColormap_Paired",                   ImPlotColormap_Paired);                   m.attr("ImPlotColormap_Paired")                   = static_cast<int>(ImPlotColormap_Paired);
    e.value("ImPlotColormap_Viridis",                  ImPlotColormap_Viridis);                  m.attr("ImPlotColormap_Viridis")                  = static_cast<int>(ImPlotColormap_Viridis);
    e.value("ImPlotColormap_Plasma",                   ImPlotColormap_Plasma);                   m.attr("ImPlotColormap_Plasma")                   = static_cast<int>(ImPlotColormap_Plasma);
    e.value("ImPlotColormap_Hot",                      ImPlotColormap_Hot);                      m.attr("ImPlotColormap_Hot")                      = static_cast<int>(ImPlotColormap_Hot);
    e.value("ImPlotColormap_Cool",                     ImPlotColormap_Cool);                     m.attr("ImPlotColormap_Cool")                     = static_cast<int>(ImPlotColormap_Cool);
    e.value("ImPlotColormap_Pink",                     ImPlotColormap_Pink);                     m.attr("ImPlotColormap_Pink")                     = static_cast<int>(ImPlotColormap_Pink);
    e.value("ImPlotColormap_Jet",                      ImPlotColormap_Jet);                      m.attr("ImPlotColormap_Jet")                      = static_cast<int>(ImPlotColormap_Jet);
    e.value("ImPlotColormap_Twilight",                 ImPlotColormap_Twilight);                 m.attr("ImPlotColormap_Twilight")                 = static_cast<int>(ImPlotColormap_Twilight);
    e.value("ImPlotColormap_RdBu",                     ImPlotColormap_RdBu);                     m.attr("ImPlotColormap_RdBu")                     = static_cast<int>(ImPlotColormap_RdBu);
    e.value("ImPlotColormap_BrBG",                     ImPlotColormap_BrBG);                     m.attr("ImPlotColormap_BrBG")                     = static_cast<int>(ImPlotColormap_BrBG);
    e.value("ImPlotColormap_PiYG",                     ImPlotColormap_PiYG);                     m.attr("ImPlotColormap_PiYG")                     = static_cast<int>(ImPlotColormap_PiYG);
    e.value("ImPlotColormap_Spectral",                 ImPlotColormap_Spectral);                 m.attr("ImPlotColormap_Spectral")                 = static_cast<int>(ImPlotColormap_Spectral);
    e.value("ImPlotColormap_Greys",                    ImPlotColormap_Greys);                    m.attr("ImPlotColormap_Greys")                    = static_cast<int>(ImPlotColormap_Greys);
  ;
  }

  { // ImPlotLocation ImPlotLocation_
  auto e = nb::enum_<ImPlotLocation_>(m, "ImPlotLocation");
    e.value("ImPlotLocation_Center",                   ImPlotLocation_Center);                   m.attr("ImPlotLocation_Center")                   = static_cast<int>(ImPlotLocation_Center);
    e.value("ImPlotLocation_North",                    ImPlotLocation_North);                    m.attr("ImPlotLocation_North")                    = static_cast<int>(ImPlotLocation_North);
    e.value("ImPlotLocation_South",                    ImPlotLocation_South);                    m.attr("ImPlotLocation_South")                    = static_cast<int>(ImPlotLocation_South);
    e.value("ImPlotLocation_West",                     ImPlotLocation_West);                     m.attr("ImPlotLocation_West")                     = static_cast<int>(ImPlotLocation_West);
    e.value("ImPlotLocation_East",                     ImPlotLocation_East);                     m.attr("ImPlotLocation_East")                     = static_cast<int>(ImPlotLocation_East);
    e.value("ImPlotLocation_NorthWest",                ImPlotLocation_NorthWest);                m.attr("ImPlotLocation_NorthWest")                = static_cast<int>(ImPlotLocation_NorthWest);
    e.value("ImPlotLocation_NorthEast",                ImPlotLocation_NorthEast);                m.attr("ImPlotLocation_NorthEast")                = static_cast<int>(ImPlotLocation_NorthEast);
    e.value("ImPlotLocation_SouthWest",                ImPlotLocation_SouthWest);                m.attr("ImPlotLocation_SouthWest")                = static_cast<int>(ImPlotLocation_SouthWest);
    e.value("ImPlotLocation_SouthEast",                ImPlotLocation_SouthEast);                m.attr("ImPlotLocation_SouthEast")                = static_cast<int>(ImPlotLocation_SouthEast);
  ;
  }

  { // ImPlotBin ImPlotBin_
  auto e = nb::enum_<ImPlotBin_>(m, "ImPlotBin");
    e.value("ImPlotBin_Sqrt",                          ImPlotBin_Sqrt);                          m.attr("ImPlotBin_Sqrt")                          = static_cast<int>(ImPlotBin_Sqrt);
    e.value("ImPlotBin_Sturges",                       ImPlotBin_Sturges);                       m.attr("ImPlotBin_Sturges")                       = static_cast<int>(ImPlotBin_Sturges);
    e.value("ImPlotBin_Rice",                          ImPlotBin_Rice);                          m.attr("ImPlotBin_Rice")                          = static_cast<int>(ImPlotBin_Rice);
    e.value("ImPlotBin_Scott",                         ImPlotBin_Scott);                         m.attr("ImPlotBin_Scott")                         = static_cast<int>(ImPlotBin_Scott);
  ;
  }

}

// clang-format on
