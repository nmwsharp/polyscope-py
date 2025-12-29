from os import listdir
import os.path as path
from os.path import isfile, join
import unittest

import numpy as np

import polyscope as ps
import polyscope.imgui as psim
import polyscope.implot as psimplot

class TestImGuiBindings(unittest.TestCase):

    def test_ui_calls(self):

        # (this is the example from the demo and the docs)
    
        # A bunch of parameters which we will maniuplate via the UI defined below.
        # There is nothing special about these variables, you could manipulate any other 
        # kind of Python values the same way, such as entries in a dict, or class members.
        is_true1 = False
        is_true2 = True
        ui_int = 7
        ui_float1 = -3.2
        ui_float2 = 0.8
        ui_color3 = (1., 0.5, 0.5)
        ui_color4 = (0.3, 0.5, 0.5, 0.8)
        ui_angle_rad = 0.2
        ui_text = "some input text"
        ui_options = ["option A", "option B", "option C"]
        ui_options_selected = ui_options[1]

        def my_function():
            # ... do something important here ...
            pass

        # Define our callback function, which Polyscope will repeatedly execute while running the UI.
        # We can write any code we want here, but in particular it is an opportunity to create ImGui 
        # interface elements and define a custom UI.
        def imgui_callback():

            # If we want to use local variables & assign to them in the UI code below, we need to mark them as nonlocal. This is because of how Python scoping rules work, not anything particular about Polyscope or ImGui.
            # Of course, you can also use any other kind of python variable as a controllable value in the UI, such as a value from a dictionary, or a class member. Just be sure to assign the result of the ImGui call to the value, as in the examples below.
            nonlocal is_true1, is_true2, ui_int, ui_float1, ui_float2, ui_color3, ui_color4, ui_text, ui_options_selected, ui_angle_rad
            

            # == Settings
           
            # Use settings like this to change the UI appearance.
            # Note that it is a push/pop pair, with the matching pop() below.
            psim.PushItemWidth(150)


            # == Show text in the UI

            psim.TextUnformatted("Some sample text")
            psim.TextUnformatted("An important value: {}".format(42))
            psim.Separator()
            

            # == Buttons

            if(psim.Button("A button")):
                # This code is executed when the button is pressed
                print("Hello")

            # By default, each element goes on a new line. Use this 
            # to put the next element on the _same_ line.
            psim.SameLine() 
            
            if(psim.Button("Another button")):
                # This code is executed when the button is pressed
                my_function()
         

            # == Set parameters
        
            # These commands allow the user to adjust the value of variables.
            # It is important that we assign the return result to the variable to
            # update it. 
            # For most elements, the return is actually a tuple `(changed, newval)`, 
            # where `changed` indicates whether the setting was modified on this 
            # frame, and `newval` gives the new value of the variable (or the same 
            # old value if unchanged).
            #
            # For numeric inputs, ctrl-click on the box to type in a value.
           
            # Checkbox
            changed, is_true1 = psim.Checkbox("flag1", is_true1) 
            if(changed): # optionally, use this conditional to take action on the new value
                pass 
            psim.SameLine() 
            changed, is_true2 = psim.Checkbox("flag2", is_true2) 
            
            # Input ints
            changed, ui_int = psim.InputInt("ui_int", ui_int, step=1, step_fast=10) 

            # Input floats using two different styles of widget
            changed, ui_float1 = psim.InputFloat("ui_float1", ui_float1) 
            psim.SameLine() 
            changed, ui_float2 = psim.SliderFloat("ui_float2", ui_float2, v_min=-5, v_max=5)

            # Input colors
            changed, ui_color3 = psim.ColorEdit3("ui_color3", ui_color3)
            psim.SameLine() 
            changed, ui_color4 = psim.ColorEdit4("ui_color4", ui_color4)

            # Input text
            changed, ui_text = psim.InputText("enter text", ui_text)

            # Combo box to choose from options
            # There, the options are a list of strings in `ui_options`,
            # and the currently selected element is stored in `ui_options_selected`.
            psim.PushItemWidth(200)
            changed = psim.BeginCombo("Pick one", ui_options_selected)
            if changed:
                for val in ui_options:
                    if psim.Selectable(val, ui_options_selected==val):
                        ui_options_selected = val
                psim.EndCombo()
            psim.PopItemWidth()
            

            # Use tree headers to logically group options

            # This a stateful option to set the tree node below to be open initially.
            # The second argument is a flag, which works like a bitmask.
            # Many ImGui elements accept flags to modify their behavior.
            psim.SetNextItemOpen(True, psim.ImGuiCond_FirstUseEver)
           
            # The body is executed only when the sub-menu is open. Note the push/pop pair!
            if(psim.TreeNode("Collapsible sub-menu")):
                
                psim.TextUnformatted("Detailed information")
                
                if(psim.Button("sub-button")):
                    print("hello")

                # There are many different UI elements offered by ImGui, many of which
                # are bound in python by Polyscope. See ImGui's documentation in `imgui.h`,
                # or the polyscope bindings in `polyscope/src/cpp/imgui.cpp`.
                changed, ui_angle_rad = psim.SliderAngle("ui_float2", ui_angle_rad, 
                        v_degrees_min=-90, v_degrees_max=90)
                
                psim.TreePop()

            psim.PopItemWidth()


        ps.set_user_callback(imgui_callback)
        ps.show(3)
        
        ps.clear_user_callback()
    
    def test_implot(self):

        # smoke tests for implot
        def imgui_callback():

            # PlotLine
            psim.SetCursorPos((0,0)) # these calls ensure it's not clipped out and disabled
            if psimplot.BeginPlot("test line plot"):
                psimplot.PlotLine("line plot1", np.random.rand(10))
                psimplot.PlotLine("line plot2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotLine("line plot3", np.random.rand(10), psimplot.ImPlotLineFlags_Shaded + psimplot.ImPlotLineFlags_Loop)

                # test inf lines while we're at it
                psimplot.PlotInfLines("inf line v", np.random.rand(3))
                psimplot.PlotInfLines("inf line h", np.random.rand(3), psimplot.ImPlotInfLinesFlags_Horizontal)

                psimplot.EndPlot()

            # PlotScatter
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("test scatter plot"):
                psimplot.PlotScatter("scatter plot1", np.random.rand(10))
                psimplot.PlotScatter("scatter plot2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotScatter("scatter plot3", np.random.rand(10), psimplot.ImPlotScatterFlags_NoClip)
                psimplot.EndPlot()
            
            # PlotStairs
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("test stairs plot"):
                psimplot.PlotStairs("stairs plot1", np.random.rand(10))
                psimplot.PlotStairs("stairs plot2", np.random.rand(10), np.random.rand(10))
                psimplot.PlotStairs("stairs plot3", np.random.rand(10), psimplot.ImPlotStairsFlags_Shaded)
                psimplot.EndPlot()
            
            # PlotShaded
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("test shaded plot"):
                psimplot.PlotShaded("shaded plot1", np.random.rand(10))
                psimplot.PlotShaded("shaded plot1", np.random.rand(10), yref=1.0)
                psimplot.PlotShaded("shaded plot2", np.random.rand(10), np.random.rand(10), psimplot.ImPlotShadedFlags_None)
                psimplot.PlotShaded("shaded plot3", np.random.rand(10), np.random.rand(10), np.random.rand(10))
                psimplot.EndPlot()
            
            # PlotBars TODO
            
            # PlotBarGroups TODO
            
            # PlotErrorBars TODO
            
            # PlotStems TODO

            # PlotPieChart
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("test pie chart plot"):
                psimplot.PlotPieChart(["cat1", "cat2"], np.random.rand(2), 0.5, 0.5, 0.5)
                psimplot.PlotPieChart(["cat1", "cat2"], np.random.rand(2), x=2., y=3., radius=4.)
                psimplot.PlotPieChart(["cat1", "cat2"], np.random.rand(2), 2., 3., 4., flags=psimplot.ImPlotPieChartFlags_Exploding)
                psimplot.EndPlot()

            # PlotHeatMap TODO
            
            # PlotHistorgram
            psim.SetCursorPos((0,0))
            if psimplot.BeginPlot("test historgram plot"):
                psimplot.PlotHistogram("hist", np.random.rand(10))
                psimplot.PlotHistogram("hist2", np.random.rand(10), 3, range=(-2., 2.), flags=psimplot.ImPlotHistogramFlags_NoOutliers)
                psimplot.EndPlot()
            
            # Subplots
            psim.SetCursorPos((0,0))
            if psimplot.BeginSubplots("test subplot", 2, 3, (800,400)):
                for i in range(6):
                    if psimplot.BeginPlot(f"test subplot_{i}"):
                        psimplot.PlotLine("line plot", np.random.rand(10))

                        psimplot.EndPlot()

                psimplot.EndSubplots()
        
        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()