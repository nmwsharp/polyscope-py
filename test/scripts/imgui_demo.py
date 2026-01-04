import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "src")))
if os.name == 'nt': # if Windows
    # handle default location where VS puts binary
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "Debug")))
else:
    # normal / unix case
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build")))

import polyscope
import polyscope.imgui as psim
import sys

def main():

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
    
    alt_font = None

    def my_function():
        # ... do something important here ...
        print("executing function")

    # Define our callback function, which Polyscope will repeatedly execute while running the UI.
    # We can write any code we want here, but in particular it is an opportunity to create ImGui 
    # interface elements and define a custom UI.
    def callback():

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


        # Create an annotation window, use a custom font
        if False:
            psim.SetNextWindowPos((200, 200))
            psim.SetNextWindowSize((100, 50))
            psim.SetNextWindowBgAlpha(0.8)
            psim.Begin("Annotation Window", None, psim.ImGuiWindowFlags_NoDecoration)
            psim.PushFont(alt_font)
            psim.TextUnformatted("annotation text")
            psim.PopFont()
            psim.End()

    polyscope.init() 
    polyscope.set_user_callback(callback)

    
    # Load a custom font
    if False:
        io = psim.GetIO()
        alt_font = io.Fonts.AddFontFromFileTTF("your_font_file.otf", 50)


    polyscope.show()

if __name__ == '__main__':
    main()
