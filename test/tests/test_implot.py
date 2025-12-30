from os import listdir
import os.path as path
from os.path import isfile, join
import unittest

import numpy as np

import polyscope as ps
import polyscope.imgui as psim
import polyscope.implot as psimplot

class TestImPlotBindings(unittest.TestCase):

    def test_plot_line(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("line plot"):
                psimplot.PlotLine("line1", np.random.rand(10))
                psimplot.PlotLine("line2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotLine("line3", np.random.rand(10), psimplot.ImPlotLineFlags_Shaded)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_scatter(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("scatter plot"):
                psimplot.PlotScatter("scatter1", np.random.rand(10))
                psimplot.PlotScatter("scatter2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotScatter("scatter3", np.random.rand(10), psimplot.ImPlotScatterFlags_NoClip)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_stairs(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("stairs plot"):
                psimplot.PlotStairs("stairs1", np.random.rand(10))
                psimplot.PlotStairs("stairs2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotStairs("stairs3", np.random.rand(10), psimplot.ImPlotStairsFlags_Shaded)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_shaded(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("shaded plot"):
                psimplot.PlotShaded("shaded1", np.random.rand(10))
                psimplot.PlotShaded("shaded2", np.random.rand(10), yref=1.0)
                psimplot.PlotShaded("shaded3", np.random.rand(10), np.random.rand(10))
                psimplot.PlotShaded("shaded4", np.random.rand(10), np.random.rand(10), np.random.rand(10))
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_bars(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("bars plot"):
                psimplot.PlotBars("bars1", np.random.rand(10))
                psimplot.PlotBars("bars2", np.random.rand(10), np.random.rand(10), 0.67)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_bar_groups(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("bar groups plot"):
                data = np.random.rand(3, 5)
                psimplot.PlotBarGroups(["A", "B", "C"], data)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_error_bars(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("error bars plot"):
                xs = np.random.rand(10)
                ys = np.random.rand(10)
                err = np.random.rand(10) * 0.1
                psimplot.PlotErrorBars("error1", xs, ys, err)
                psimplot.PlotErrorBars("error2", xs, ys, err, err)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_stems(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("stems plot"):
                psimplot.PlotStems("stems1", np.random.rand(10))
                psimplot.PlotStems("stems2", np.random.rand(10), np.random.rand(10))
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_inf_lines(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("inf lines plot"):
                psimplot.PlotInfLines("vlines", np.random.rand(3))
                psimplot.PlotInfLines("hlines", np.random.rand(3), psimplot.ImPlotInfLinesFlags_Horizontal)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_pie_chart(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("pie chart plot"):
                psimplot.PlotPieChart(["cat1", "cat2", "cat3"], np.random.rand(3), 0.5, 0.5, 0.5)
                psimplot.PlotPieChart(["A", "B"], np.random.rand(2), x=2., y=3., radius=4.)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_heatmap(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("heatmap plot"):
                data = np.random.rand(5, 10)
                psimplot.PlotHeatmap("heatmap", data)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_histogram(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("histogram plot"):
                psimplot.PlotHistogram("hist1", np.random.rand(100))
                psimplot.PlotHistogram("hist2", np.random.rand(100), bins=20)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_histogram_2d(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("histogram 2d plot"):
                psimplot.PlotHistogram2D("hist2d", np.random.rand(100), np.random.rand(100))
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_digital(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("digital plot"):
                xs = np.linspace(0, 10, 100)
                ys = (np.sin(xs) > 0).astype(float)
                psimplot.PlotDigital("digital", xs, ys)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_text(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("text plot"):
                psimplot.PlotText("Hello", 0.5, 0.5)
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_dummy(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("dummy plot"):
                psimplot.PlotDummy("dummy")
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_tools(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("tools plot"):
                result, x, y = psimplot.DragPoint(0, 0.5, 0.5, (1, 0, 0, 1))
                result, x = psimplot.DragLineX(1, 0.3, (0, 1, 0, 1))
                result, y = psimplot.DragLineY(2, 0.7, (0, 0, 1, 1))
                result, x1, y1, x2, y2 = psimplot.DragRect(3, 0.2, 0.2, 0.8, 0.8, (1, 1, 0, 1))

                psimplot.Annotation(0.5, 0.5, (1, 0, 1, 1), (0, 0), True)
                psimplot.Annotation(0.3, 0.7, (0, 1, 1, 1), (10, 10), True, "Note")

                psimplot.TagX(0.5, (1, 0, 0, 1))
                psimplot.TagY(0.5, (0, 1, 0, 1))

                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_plot_utils(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("utils plot"):
                psimplot.SetAxis(psimplot.ImAxis_X1)
                psimplot.SetAxes(psimplot.ImAxis_X1, psimplot.ImAxis_Y1)

                px, py = psimplot.PixelsToPlot((100, 100))
                px, py = psimplot.PixelsToPlot(100, 100)

                px, py = psimplot.PlotToPixels((0.5, 0.5))
                px, py = psimplot.PlotToPixels(0.5, 0.5)

                pos = psimplot.GetPlotPos()
                size = psimplot.GetPlotSize()
                mouse_pos = psimplot.GetPlotMousePos()
                xmin, xmax, ymin, ymax = psimplot.GetPlotLimits()

                is_hovered = psimplot.IsPlotHovered()
                is_axis_hovered = psimplot.IsAxisHovered(psimplot.ImAxis_X1)

                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_legend_utils(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("legend plot"):
                psimplot.PlotLine("line", np.random.rand(10))

                if psimplot.BeginLegendPopup("line"):
                    psim.Text("Legend popup")
                    psimplot.EndLegendPopup()

                is_hovered = psimplot.IsLegendEntryHovered("line")

                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_styling(self):
        def imgui_callback():
            # Get and modify style
            style = psimplot.GetStyle()
            style.LineWeight = 2.0
            style.MarkerSize = 5.0

            # Style colors
            psimplot.StyleColorsDark()

            # Push/pop style colors
            psimplot.PushStyleColor(psimplot.ImPlotCol_Line, (1, 0, 0, 1))
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("styled plot"):
                psimplot.PlotLine("red line", np.random.rand(10))
                psimplot.EndPlot()
            psimplot.PopStyleColor()

            # Push/pop style vars
            psimplot.PushStyleVar(psimplot.ImPlotStyleVar_LineWeight, 3.0)
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("thick plot"):
                psimplot.PlotLine("thick line", np.random.rand(10))
                psimplot.EndPlot()
            psimplot.PopStyleVar()

            # Set next item styles
            psimplot.SetNextLineStyle((0, 1, 0, 1), 2.0)
            psimplot.SetNextFillStyle((0, 0, 1, 0.5))
            psimplot.SetNextMarkerStyle(psimplot.ImPlotMarker_Circle, 8.0)

            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("next style plot"):
                psimplot.PlotLine("styled line", np.random.rand(10))
                psimplot.EndPlot()

            # Color names
            name = psimplot.GetStyleColorName(psimplot.ImPlotCol_Line)
            marker_name = psimplot.GetMarkerName(psimplot.ImPlotMarker_Circle)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_colormaps(self):

        # Add custom colormap
        colors = [(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1)]
        cmap = psimplot.AddColormap("custom", colors)

        def imgui_callback():

            # Colormap info
            count = psimplot.GetColormapCount()
            name = psimplot.GetColormapName(psimplot.ImPlotColormap_Deep)
            idx = psimplot.GetColormapIndex("Deep")

            # Push/pop colormap
            psimplot.PushColormap(psimplot.ImPlotColormap_Viridis)
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("colormap plot"):
                for i in range(5):
                    color = psimplot.NextColormapColor()
                    psimplot.PlotLine(f"line{i}", np.random.rand(10))
                psimplot.EndPlot()
            psimplot.PopColormap()

            # Colormap utils
            size = psimplot.GetColormapSize()
            color = psimplot.GetColormapColor(0)
            sampled = psimplot.SampleColormap(0.5)

            # Colormap widgets
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("colormap widgets"):
                psimplot.ColormapScale("scale", 0.0, 1.0, (60, 200))
                psimplot.EndPlot()

            result, t, color = psimplot.ColormapSlider("slider", 0.5)
            button_pressed = psimplot.ColormapButton("button")

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_input_mapping(self):
        def imgui_callback():
            # Get and modify input map
            input_map = psimplot.GetInputMap()
            input_map.ZoomRate = 0.2

            # Map defaults
            psimplot.MapInputDefault()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_misc(self):
        def imgui_callback():
            # Item icons
            psimplot.ItemIcon((1, 0, 0, 1))
            psimplot.ColormapIcon(psimplot.ImPlotColormap_Viridis)

            # Selectors
            psimplot.ShowStyleSelector("Style")
            psimplot.ShowColormapSelector("Colormap")
            psimplot.ShowInputMapSelector("Input Map")

            # User guide
            if psim.CollapsingHeader("User Guide"):
                psimplot.ShowUserGuide()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_subplots(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginSubplots("subplots", 2, 3, (800, 400)):
                for i in range(6):
                    if psimplot.BeginPlot(f"subplot_{i}"):
                        psimplot.PlotLine("line", np.random.rand(10))
                        psimplot.EndPlot()
                psimplot.EndSubplots()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_setup_axes(self):
        def imgui_callback():
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("setup plot"):
                psimplot.SetupAxes("X Axis", "Y Axis")
                psimplot.SetupAxis(psimplot.ImAxis_X1, "Time")
                psimplot.SetupAxisLimits(psimplot.ImAxis_X1, 0, 10)
                psimplot.SetupAxisFormat(psimplot.ImAxis_Y1, "%.2f")
                psimplot.SetupAxisTicks(psimplot.ImAxis_X1, 0, 10, 11)

                psimplot.PlotLine("data", np.random.rand(10))
                psimplot.EndPlot()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()
