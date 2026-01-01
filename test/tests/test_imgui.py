from os import listdir
import os.path as path
from os.path import isfile, join
import unittest

import numpy as np

import polyscope as ps
import polyscope.imgui as psim
import polyscope.implot as psimplot

class TestImGuiBindings(unittest.TestCase):

    def test_context_creation(self):
        # Test context creation functions using capsules
        # Note: We don't actually switch contexts in this test, just verify the bindings work

        def imgui_callback():
            # Get current context (should exist since Polyscope created one)
            ctx = psim.GetCurrentContext()
            self.assertIsNotNone(ctx)

            # We don't test CreateContext/DestroyContext/SetCurrentContext here
            # because Polyscope manages the context and we don't want to interfere

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_draw_lists(self):
        # Test background and foreground draw list access

        def imgui_callback():
            # Get draw lists
            bg_list = psim.GetBackgroundDrawList()
            fg_list = psim.GetForegroundDrawList()

            self.assertIsNotNone(bg_list)
            self.assertIsNotNone(fg_list)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_misc_utils(self):
        # Test miscellaneous utility functions

        def imgui_callback():
            # Test time and frame count
            time_val = psim.GetTime()
            self.assertIsInstance(time_val, float)
            self.assertGreaterEqual(time_val, 0.0)

            frame_count = psim.GetFrameCount()
            self.assertIsInstance(frame_count, int)
            self.assertGreaterEqual(frame_count, 0)

            # Test rectangle visibility
            visible1 = psim.IsRectVisible((100.0, 100.0))
            self.assertIsInstance(visible1, bool)

            visible2 = psim.IsRectVisible((0.0, 0.0), (100.0, 100.0))
            self.assertIsInstance(visible2, bool)

            # Test style color name
            color_name = psim.GetStyleColorName(0)
            self.assertIsInstance(color_name, str)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_text_utils(self):
        # Test text utility functions

        def imgui_callback():
            # Test text size calculation
            text_size = psim.CalcTextSize("Hello World")
            self.assertIsInstance(text_size, tuple)
            self.assertEqual(len(text_size), 2)
            self.assertGreater(text_size[0], 0.0)  # width should be positive
            self.assertGreater(text_size[1], 0.0)  # height should be positive

            # Test with wrap width
            text_size_wrapped = psim.CalcTextSize("Hello World", wrap_width=100.0)
            self.assertIsInstance(text_size_wrapped, tuple)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_color_utils(self):
        # Test color conversion utilities

        def imgui_callback():
            # Test U32 to Float4 conversion
            color_u32 = 0xFF8080FF  # RGBA
            color_float4 = psim.ColorConvertU32ToFloat4(color_u32)
            self.assertIsInstance(color_float4, tuple)
            self.assertEqual(len(color_float4), 4)

            # Test Float4 to U32 conversion
            color_back = psim.ColorConvertFloat4ToU32(color_float4)
            self.assertIsInstance(color_back, int)

            # Test RGB to HSV conversion
            hsv = psim.ColorConvertRGBtoHSV(1.0, 0.5, 0.25)
            self.assertIsInstance(hsv, tuple)
            self.assertEqual(len(hsv), 3)

            # Test HSV to RGB conversion
            rgb = psim.ColorConvertHSVtoRGB(hsv[0], hsv[1], hsv[2])
            self.assertIsInstance(rgb, tuple)
            self.assertEqual(len(rgb), 3)
            # Values should be close to original
            self.assertAlmostEqual(rgb[0], 1.0, places=5)
            self.assertAlmostEqual(rgb[1], 0.5, places=5)
            self.assertAlmostEqual(rgb[2], 0.25, places=5)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_inputs_keyboard(self):
        # Test keyboard input functions

        def imgui_callback():
            # Test key state queries (won't be pressed, but should return valid bools)
            is_down = psim.IsKeyDown(psim.ImGuiKey_A)
            self.assertIsInstance(is_down, bool)

            is_pressed = psim.IsKeyPressed(psim.ImGuiKey_Space)
            self.assertIsInstance(is_pressed, bool)

            is_released = psim.IsKeyReleased(psim.ImGuiKey_Enter)
            self.assertIsInstance(is_released, bool)

            # Test key name
            key_name = psim.GetKeyName(psim.ImGuiKey_A)
            self.assertIsInstance(key_name, str)

            # Test key chord
            is_chord = psim.IsKeyChordPressed(psim.ImGuiMod_Ctrl | psim.ImGuiKey_S)
            self.assertIsInstance(is_chord, bool)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_inputs_mouse(self):
        # Test mouse input functions

        def imgui_callback():
            # Test mouse button states
            is_down = psim.IsMouseDown(psim.ImGuiMouseButton_Left)
            self.assertIsInstance(is_down, bool)

            is_clicked = psim.IsMouseClicked(psim.ImGuiMouseButton_Left)
            self.assertIsInstance(is_clicked, bool)

            is_released = psim.IsMouseReleased(psim.ImGuiMouseButton_Left)
            self.assertIsInstance(is_released, bool)

            is_double_clicked = psim.IsMouseDoubleClicked(psim.ImGuiMouseButton_Left)
            self.assertIsInstance(is_double_clicked, bool)

            # Test mouse position
            mouse_pos = psim.GetMousePos()
            self.assertIsInstance(mouse_pos, tuple)
            self.assertEqual(len(mouse_pos), 2)

            # Test mouse position validity
            is_valid = psim.IsMousePosValid()
            self.assertIsInstance(is_valid, bool)

            # Test mouse dragging
            is_dragging = psim.IsMouseDragging(psim.ImGuiMouseButton_Left)
            self.assertIsInstance(is_dragging, bool)

            drag_delta = psim.GetMouseDragDelta()
            self.assertIsInstance(drag_delta, tuple)
            self.assertEqual(len(drag_delta), 2)

            # Test mouse cursor
            cursor = psim.GetMouseCursor()
            self.assertIsInstance(cursor, int)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_clipboard(self):
        # Test clipboard functions

        def imgui_callback():
            # Set clipboard text
            test_text = "Test clipboard content"
            psim.SetClipboardText(test_text)

            # Get clipboard text
            clipboard_text = psim.GetClipboardText()
            self.assertIsInstance(clipboard_text, str)
            self.assertEqual(clipboard_text, test_text)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_io_struct(self):
        # Test ImGuiIO struct bindings

        def imgui_callback():
            io = psim.GetIO()
            self.assertIsNotNone(io)

            # Test reading some properties
            display_size = io.DisplaySize
            self.assertIsInstance(display_size, tuple)
            self.assertEqual(len(display_size), 2)

            delta_time = io.DeltaTime
            self.assertIsInstance(delta_time, float)
            self.assertGreater(delta_time, 0.0)

            # Test output state flags
            want_capture_mouse = io.WantCaptureMouse
            self.assertIsInstance(want_capture_mouse, bool)

            want_capture_keyboard = io.WantCaptureKeyboard
            self.assertIsInstance(want_capture_keyboard, bool)

            # Test framerate
            framerate = io.Framerate
            self.assertIsInstance(framerate, float)
            self.assertGreater(framerate, 0.0)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_style_struct(self):
        # Test ImGuiStyle struct bindings

        def imgui_callback():
            style = psim.GetStyle()
            self.assertIsNotNone(style)

            # Test reading some properties
            alpha = style.Alpha
            self.assertIsInstance(alpha, float)

            window_padding = style.WindowPadding
            self.assertIsInstance(window_padding, tuple)
            self.assertEqual(len(window_padding), 2)

            # Test color access
            color_count = style.GetColorCount()
            self.assertIsInstance(color_count, int)
            self.assertGreater(color_count, 0)

            # Get a color
            text_color = style.GetColor(psim.ImGuiCol_Text)
            self.assertIsInstance(text_color, tuple)
            self.assertEqual(len(text_color), 4)

            # Set a color and get it back
            test_color = (0.1, 0.2, 0.3, 0.4)
            style.SetColor(psim.ImGuiCol_Text, test_color)
            retrieved_color = style.GetColor(psim.ImGuiCol_Text)
            for i in range(4):
                self.assertAlmostEqual(retrieved_color[i], test_color[i], places=5)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_fonts(self):
        # Test font bindings

        def imgui_callback():
            io = psim.GetIO()

            # Get font atlas
            font_atlas = io.Fonts
            self.assertIsNotNone(font_atlas)

            # Get default font
            font = io.FontDefault
            if font is not None:
                # Test font properties
                is_loaded = font.IsLoaded()
                self.assertIsInstance(is_loaded, bool)

                font_size = font.FontSize
                self.assertIsInstance(font_size, float)
                self.assertGreater(font_size, 0.0)

                # Test text size calculation
                text_size = font.CalcTextSizeA(font_size, 1000.0, 0.0, "Test")
                self.assertIsInstance(text_size, tuple)
                self.assertEqual(len(text_size), 2)

                # Test char advance
                advance = font.GetCharAdvance(ord('A'))
                self.assertIsInstance(advance, float)
                self.assertGreater(advance, 0.0)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_drawlist_struct(self):
        # Test ImDrawList bindings with actual drawing

        def imgui_callback():
            # Get draw lists
            bg_list = psim.GetBackgroundDrawList()
            fg_list = psim.GetForegroundDrawList()
            self.assertIsNotNone(bg_list)
            self.assertIsNotNone(fg_list)

            # Test adding various primitives to background
            bg_list.AddLine((10.0, 10.0), (100.0, 100.0), 0xFFFFFFFF, thickness=2.0)
            bg_list.AddRect((20.0, 20.0), (120.0, 120.0), 0xFF00FFFF, rounding=5.0, thickness=1.0)
            bg_list.AddRectFilled((30.0, 30.0), (130.0, 130.0), 0xFF00FF00, rounding=3.0)
            bg_list.AddCircle((200.0, 200.0), 50.0, 0xFFFF0000, num_segments=32, thickness=2.0)
            bg_list.AddCircleFilled((300.0, 300.0), 30.0, 0xFF0000FF)
            bg_list.AddTriangle((400.0, 400.0), (450.0, 400.0), (425.0, 450.0), 0xFFFFFF00, thickness=1.5)
            bg_list.AddTriangleFilled((500.0, 500.0), (550.0, 500.0), (525.0, 550.0), 0xFF00FFFF)
            bg_list.AddQuad((150.0, 150.0), (180.0, 150.0), (180.0, 180.0), (150.0, 180.0), 0xFFFF00FF, thickness=1.0)
            bg_list.AddQuadFilled((160.0, 160.0), (190.0, 160.0), (190.0, 190.0), (160.0, 190.0), 0xFF00FF00)

            # Test text rendering
            bg_list.AddText((50.0, 50.0), psim.IM_COL32(255, 255, 255, 255), "Test Text")

            # Test bezier curves
            bg_list.AddBezierCubic((600.0, 400.0), (650.0, 350.0), (700.0, 450.0), (750.0, 400.0), 0xFFFFFFFF, thickness=2.0)
            bg_list.AddBezierQuadratic((600.0, 500.0), (650.0, 450.0), (700.0, 500.0), 0xFFFF00FF, thickness=2.0)

            # Test polylines
            points = np.array([(800.0, 400.0), (850.0, 420.0), (830.0, 460.0), (870.0, 480.0)])
            bg_list.AddPolyline(points, psim.IM_COL32(255, 255, 255, 255), flags=psim.ImDrawFlags_RoundCornersAll, thickness=2.0)
            bg_list.AddConvexPolyFilled(points, psim.IM_COL32(0, 255, 255, 255))

            # Test path API (for custom shapes)
            fg_list.PathClear()
            fg_list.PathLineTo((100.0, 600.0))
            fg_list.PathLineTo((150.0, 650.0))
            fg_list.PathLineTo((200.0, 600.0))
            fg_list.PathStroke(psim.IM_COL32(255, 0, 0, 255), flags=psim.ImDrawFlags_Closed, thickness=2.0)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_basic(self):
        # Test basic widget functionality

        def imgui_callback():
            # Test button
            if psim.Button("Test Button"):
                pass  # Button was clicked

            # Test button with size
            if psim.Button("Sized Button", (100, 30)):
                pass

            # Test small button
            if psim.SmallButton("Small"):
                pass

            # Test invisible button
            if psim.InvisibleButton("invisible", (50, 50)):
                pass

            # Test arrow button
            if psim.ArrowButton("arrow_left", psim.ImGuiDir_Left):
                pass

            # Test checkbox
            changed, value = psim.Checkbox("Test Checkbox", True)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, bool)

            # Test radio button
            if psim.RadioButton("Radio A", True):
                pass
            if psim.RadioButton("Radio B", False):
                pass

            # Test progress bar
            psim.ProgressBar(0.5)
            psim.ProgressBar(0.75, (200, 0), "75%")

            # Test bullet
            psim.Bullet()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_input(self):
        # Test input widgets

        def imgui_callback():
            # Test InputText
            changed, text = psim.InputText("Text Input", "initial text")
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(text, str)

            # Test InputTextMultiline
            changed, text = psim.InputTextMultiline("Multiline", "line1\nline2", (200, 100))
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(text, str)

            # Test InputTextWithHint
            changed, text = psim.InputTextWithHint("With Hint", "enter text here...", "")
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(text, str)

            # Test InputInt
            changed, value = psim.InputInt("Int Input", 42)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, int)

            # Test InputFloat
            changed, value = psim.InputFloat("Float Input", 3.14)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, float)

            # Test InputFloat2
            changed, values = psim.InputFloat2("Float2", (1.0, 2.0))
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(values, tuple)
            self.assertEqual(len(values), 2)

            # Test InputFloat3
            changed, values = psim.InputFloat3("Float3", (1.0, 2.0, 3.0))
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(values, tuple)
            self.assertEqual(len(values), 3)

            # Test InputFloat4
            changed, values = psim.InputFloat4("Float4", (1.0, 2.0, 3.0, 4.0))
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(values, tuple)
            self.assertEqual(len(values), 4)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_sliders(self):
        # Test slider widgets

        def imgui_callback():
            # Test SliderFloat
            changed, value = psim.SliderFloat("Slider", 0.5, v_min=0.0, v_max=1.0)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, float)

            # Test SliderFloat with format
            changed, value = psim.SliderFloat("Slider %.3f", 0.5, v_min=0.0, v_max=1.0, format="%.3f")
            self.assertIsInstance(changed, bool)

            # Test SliderFloat2
            changed, values = psim.SliderFloat2("Slider2", (0.3, 0.7), v_min=0.0, v_max=1.0)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(values, tuple)
            self.assertEqual(len(values), 2)

            # Test SliderFloat3
            changed, values = psim.SliderFloat3("Slider3", (0.2, 0.5, 0.8), v_min=0.0, v_max=1.0)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(values), 3)

            # Test SliderFloat4
            changed, values = psim.SliderFloat4("Slider4", (0.1, 0.3, 0.6, 0.9), v_min=0.0, v_max=1.0)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(values), 4)

            # Test SliderInt
            changed, value = psim.SliderInt("SliderInt", 50, v_min=0, v_max=100)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, int)

            # Test SliderAngle
            changed, value = psim.SliderAngle("Angle", 0.0)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, float)

            # Test VSliderFloat
            changed, value = psim.VSliderFloat("VSlider", (30, 100), 0.5, v_min=0.0, v_max=1.0)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, float)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_drag(self):
        # Test drag widgets

        def imgui_callback():
            # Test DragFloat
            changed, value = psim.DragFloat("Drag", 1.0, v_speed=0.1)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, float)

            # Test DragFloat with range
            changed, value = psim.DragFloat("Drag Range", 1.0, v_speed=0.1, v_min=0.0, v_max=10.0)
            self.assertIsInstance(changed, bool)

            # Test DragFloat2
            changed, values = psim.DragFloat2("Drag2", (1.0, 2.0))
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(values), 2)

            # Test DragFloat3
            changed, values = psim.DragFloat3("Drag3", (1.0, 2.0, 3.0))
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(values), 3)

            # Test DragFloat4
            changed, values = psim.DragFloat4("Drag4", (1.0, 2.0, 3.0, 4.0))
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(values), 4)

            # Test DragInt
            changed, value = psim.DragInt("DragInt", 5, v_speed=1)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(value, int)

            # Test DragFloatRange2
            changed, v_min, v_max = psim.DragFloatRange2("Range", 1.0, 5.0)
            self.assertIsInstance(changed, bool)
            self.assertIsInstance(v_min, float)
            self.assertIsInstance(v_max, float)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_color(self):
        # Test color widgets

        def imgui_callback():
            # Test ColorEdit3
            target_color = (1.0, 0.5, 0.25)
            changed, color = psim.ColorEdit3("Color3", target_color)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(color), 3)
            for i in range(3):
                self.assertAlmostEqual(color[i], target_color[i], places=3)
    
            # Test ColorEdit4
            target_color4 = (1.0, 0.5, 0.25, 0.8)
            changed, color = psim.ColorEdit4("Color4", target_color4)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(color), 4)
            for i in range(4):
                self.assertAlmostEqual(color[i], target_color4[i], places=3)

            # Test ColorPicker3
            changed, color = psim.ColorPicker3("Picker3", target_color)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(color), 3)
            for i in range(3):
                self.assertAlmostEqual(color[i], target_color[i], places=3)

            # Test ColorPicker4
            target_color4_picker = (0.5, 0.5, 1.0, 1.0)
            changed, color = psim.ColorPicker4("Picker4", target_color4_picker)
            self.assertIsInstance(changed, bool)
            self.assertEqual(len(color), 4)
            for i in range(4):
                self.assertAlmostEqual(color[i], target_color4_picker[i], places=3)

            # Test ColorButton
            if psim.ColorButton("color_btn", (1.0, 0.0, 0.0, 1.0)):
                pass

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_combo(self):
        # Test combo box widgets

        def imgui_callback():
            # Test BeginCombo/EndCombo
            if psim.BeginCombo("Combo", "Preview"):
                if psim.Selectable("Option 1", False):
                    pass
                if psim.Selectable("Option 2", True):
                    pass
                if psim.Selectable("Option 3", False):
                    pass
                psim.EndCombo()

            # Test ListBox
            if psim.BeginListBox("ListBox"):
                if psim.Selectable("Item 1", False):
                    pass
                if psim.Selectable("Item 2", True):
                    pass
                if psim.Selectable("Item 3", False):
                    pass
                psim.EndListBox()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_widgets_trees(self):
        # Test tree widgets

        def imgui_callback():
            # Test TreeNode
            if psim.TreeNode("Tree Node"):
                psim.TextUnformatted("Child content")
                if psim.TreeNode("Nested Node"):
                    psim.TextUnformatted("Nested content")
                    psim.TreePop()
                psim.TreePop()

            # Test CollapsingHeader
            if psim.CollapsingHeader("Collapsing Header"):
                psim.TextUnformatted("Header content")

            # Test with flags
            if psim.CollapsingHeader("Header with Flags", psim.ImGuiTreeNodeFlags_DefaultOpen):
                psim.TextUnformatted("Content")

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_layout_and_cursor(self):
        # Test layout and cursor positioning

        def imgui_callback():
            # Test SameLine
            psim.TextUnformatted("Text1")
            psim.SameLine()
            psim.TextUnformatted("Text2")

            # Test NewLine
            psim.NewLine()

            # Test Spacing
            psim.Spacing()

            # Test Separator
            psim.Separator()

            # Test Indent/Unindent
            psim.Indent()
            psim.TextUnformatted("Indented text")
            psim.Unindent()

            # Test cursor position
            psim.SetCursorPos((100.0, 100.0))
            psim.Dummy((5,5))
            pos = psim.GetCursorPos()
            self.assertIsInstance(pos, tuple)
            self.assertEqual(len(pos), 2)

            # Test cursor screen position
            screen_pos = psim.GetCursorScreenPos()
            self.assertIsInstance(screen_pos, tuple)
            self.assertEqual(len(screen_pos), 2)

            # Test content region
            avail = psim.GetContentRegionAvail()
            self.assertIsInstance(avail, tuple)
            self.assertEqual(len(avail), 2)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_windows(self):
        # Test window functions

        def imgui_callback():
            # Test Begin/End
            if psim.Begin("Test Window"):
                psim.TextUnformatted("Window content")
                psim.End()

            # Test Begin with close button
            opened, should_close = psim.Begin("Window with Close", True)
            if opened:
                psim.TextUnformatted("Content")
                psim.End()

            # Test window with flags
            if psim.Begin("Window with Flags", flags=psim.ImGuiWindowFlags_NoResize):
                psim.TextUnformatted("No resize")
                psim.End()

            # Test child window
            if psim.BeginChild("ChildWindow", (200, 100)):
                psim.TextUnformatted("Child content")
                psim.EndChild()

            # Test window queries
            is_focused = psim.IsWindowFocused()
            self.assertIsInstance(is_focused, bool)

            is_hovered = psim.IsWindowHovered()
            self.assertIsInstance(is_hovered, bool)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_tooltips_and_popups(self):
        # Test tooltips and popups

        def imgui_callback():
            # Test tooltip
            psim.TextUnformatted("Hover me")
            if psim.IsItemHovered():
                psim.BeginTooltip()
                psim.TextUnformatted("This is a tooltip")
                psim.EndTooltip()

            # Test SetTooltip
            psim.TextUnformatted("Hover me too")
            if psim.IsItemHovered():
                psim.SetTooltip("Simple tooltip")

            # Test popup
            if psim.Button("Open Popup"):
                psim.OpenPopup("test_popup")

            if psim.BeginPopup("test_popup"):
                psim.TextUnformatted("Popup content")
                if psim.Button("Close"):
                    psim.CloseCurrentPopup()
                psim.EndPopup()

            # Test modal popup
            if psim.Button("Open Modal"):
                psim.OpenPopup("modal_popup")

            if psim.BeginPopupModal("modal_popup"):
                psim.TextUnformatted("Modal content")
                if psim.Button("OK"):
                    psim.CloseCurrentPopup()
                psim.EndPopup()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_menus(self):
        # Test menu functions

        def imgui_callback():
            if psim.BeginMenuBar():
                if psim.BeginMenu("File"):
                    if psim.MenuItem("New"):
                        pass
                    if psim.MenuItem("Open"):
                        pass
                    psim.Separator()
                    if psim.MenuItem("Exit"):
                        pass
                    psim.EndMenu()

                if psim.BeginMenu("Edit"):
                    if psim.MenuItem("Undo"):
                        pass
                    if psim.MenuItem("Redo"):
                        pass
                    psim.EndMenu()

                psim.EndMenuBar()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_payload_struct(self):
        # Test ImGuiPayload bindings

        def imgui_callback():
            # Create a simple drag/drop scenario
            if psim.BeginDragDropSource():
                # In a real scenario, you'd set payload data here
                # We just test that the structure exists
                psim.EndDragDropSource()

            # Test getting payload during drag/drop
            if psim.BeginDragDropTarget():
                payload = psim.AcceptDragDropPayload("TEST_TYPE")
                if payload is not None:
                    # Test payload methods
                    data_size = payload.DataSize
                    self.assertIsInstance(data_size, int)

                    is_preview = payload.IsPreview()
                    self.assertIsInstance(is_preview, bool)

                    is_delivery = payload.IsDelivery()
                    self.assertIsInstance(is_delivery, bool)

                psim.EndDragDropTarget()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_viewport_struct(self):
        # Test ImGuiViewport bindings

        def imgui_callback():
            # Get main viewport
            viewport = psim.GetMainViewport()
            self.assertIsNotNone(viewport)

            # Test viewport properties
            viewport_id = viewport.ID
            self.assertIsInstance(viewport_id, int)

            flags = viewport.Flags
            self.assertIsInstance(flags, int)

            pos = viewport.Pos
            self.assertIsInstance(pos, tuple)
            self.assertEqual(len(pos), 2)

            size = viewport.Size
            self.assertIsInstance(size, tuple)
            self.assertEqual(len(size), 2)

            work_pos = viewport.WorkPos
            self.assertIsInstance(work_pos, tuple)
            self.assertEqual(len(work_pos), 2)

            work_size = viewport.WorkSize
            self.assertIsInstance(work_size, tuple)
            self.assertEqual(len(work_size), 2)

            # Test helper methods
            center = viewport.GetCenter()
            self.assertIsInstance(center, tuple)
            self.assertEqual(len(center), 2)

            work_center = viewport.GetWorkCenter()
            self.assertIsInstance(work_center, tuple)
            self.assertEqual(len(work_center), 2)

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()

    def test_table_sorting(self):
        # Test table sorting specs

        def imgui_callback():
            if psim.BeginTable("test_table", 3, psim.ImGuiTableFlags_Sortable):
                psim.TableSetupColumn("Column A", psim.ImGuiTableColumnFlags_DefaultSort)
                psim.TableSetupColumn("Column B")
                psim.TableSetupColumn("Column C")
                psim.TableHeadersRow()

                # Get sort specs
                sort_specs = psim.TableGetSortSpecs()
                if sort_specs is not None:
                    # Test sort specs properties
                    specs_count = sort_specs.SpecsCount
                    self.assertIsInstance(specs_count, int)

                    specs_dirty = sort_specs.SpecsDirty
                    self.assertIsInstance(specs_dirty, bool)

                    # Get specs list
                    specs_list = sort_specs.Specs()
                    self.assertIsInstance(specs_list, list)

                    if len(specs_list) > 0:
                        spec = specs_list[0]
                        # Test column sort spec properties
                        col_id = spec.ColumnUserID
                        self.assertIsInstance(col_id, int)

                        col_index = spec.ColumnIndex
                        self.assertIsInstance(col_index, int)

                        sort_order = spec.SortOrder
                        self.assertIsInstance(sort_order, int)

                        sort_direction = spec.SortDirection

                # Add some dummy rows
                for i in range(3):
                    psim.TableNextRow()
                    psim.TableNextColumn()
                    psim.TextUnformatted(f"A{i}")
                    psim.TableNextColumn()
                    psim.TextUnformatted(f"B{i}")
                    psim.TableNextColumn()
                    psim.TextUnformatted(f"C{i}")

                psim.EndTable()

        ps.set_user_callback(imgui_callback)
        ps.show(3)
        ps.clear_user_callback()
    
    
    def test_combined_1(self):

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
    