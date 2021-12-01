import unittest
import os
import sys
import os.path as path
import numpy as np
from os import listdir
from os.path import isfile, join

# Path to where the bindings live
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "src")))
if os.name == 'nt': # if Windows
    # handle default location where VS puts binary
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "Debug")))
else:
    # normal / unix case
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build")))


import polyscope as ps
import polyscope.imgui as psim

# Path to test assets
assets_prefix = path.join(path.dirname(__file__), "assets/")

class TestCore(unittest.TestCase):


    def test_show(self):
        ps.show(forFrames=3)

    def test_options(self):

        # Remember, polyscope has global state, so we're actually setting these for the remainder of the tests (lol)

        ps.set_program_name("polyscope test prog")
        ps.set_verbosity(2)
        ps.set_print_prefix("polyscope test")
        ps.set_errors_throw_exceptions(True)
        ps.set_max_fps(60)
        ps.set_use_prefs_file(True)
        ps.set_always_redraw(False)
        
        ps.set_enable_render_error_checks(True)
        
        ps.set_autocenter_structures(False)
        ps.set_autoscale_structures(False)

        ps.set_build_gui(True)
        ps.set_open_imgui_window_for_user_callback(True)
        ps.set_invoke_user_callback_for_nested_show(False)
        ps.set_give_focus_on_show(True)
        
        ps.show(3)

    def test_callbacks(self):

        # Simple callback function
        # (we use 'counts' to ensure it gets called)
        counts = [0]
        def sample_callback():
            counts[0] = counts[0] + 1

        ps.set_user_callback(sample_callback)
        ps.show(3)
       
        # Make sure the callback got called
        self.assertEqual(3, counts[0])

        ps.clear_user_callback()
        ps.show(3)
        
        # Make sure the callback didn't get called any more
        self.assertEqual(3, counts[0])
        
        # Make sure clearing twice is ok
        ps.clear_user_callback()
    
    def test_view_options(self):

        ps.set_navigation_style("turntable")
        ps.set_navigation_style("free")
        ps.set_navigation_style("planar")

        ps.set_up_dir("x_up")
        ps.set_up_dir("neg_x_up")
        ps.set_up_dir("y_up")
        ps.set_up_dir("neg_y_up")
        ps.set_up_dir("z_up")
        ps.set_up_dir("neg_z_up")
        
        ps.set_view_projection_mode("orthographic")
        ps.set_view_projection_mode("perspective")
        
        ps.show(3)
    
        ps.set_up_dir("y_up")

    def test_camera_movement(self):

        ps.reset_camera_to_home_view()
       
        ps.look_at((0., 0., 5.), (1., 1., 1.))
        ps.look_at(np.array((0., 0., 5.)), (1., 1., 1.), fly_to=True)
        
        ps.look_at_dir((0., 0., 5.), (1., 1., 1.), (-1., -1., 0.))
        ps.look_at_dir((0., 0., 5.), (1., 1., 1.), np.array((-1., -1., 0.)), fly_to=True)
        
        ps.show(3)
    
    def test_ground_options(self):

        ps.set_ground_plane_mode("none")
        ps.set_ground_plane_mode("tile")
        ps.set_ground_plane_mode("tile_reflection")
        ps.set_ground_plane_mode("shadow_only")

        ps.set_ground_plane_height_factor(1.5, is_relative=False)
        ps.set_ground_plane_height_factor(0.)
        
        ps.set_shadow_blur_iters(3)
        ps.set_shadow_darkness(0.1)
        
        ps.show(3)
    
    def test_transparency_options(self):

        ps.set_transparency_mode('none')
        ps.set_transparency_mode('simple')
        ps.set_transparency_mode('pretty')
        
        ps.set_transparency_render_passes(6)
        
        ps.show(3)
        
        ps.set_transparency_mode('none')
    
    def test_render_options(self):

        ps.set_SSAA_factor(2)
        ps.show(3)
        ps.set_SSAA_factor(1)

    def test_screenshot(self):

        ps.screenshot()
        ps.screenshot(transparent_bg=False)
        ps.screenshot("test_shot.png", transparent_bg=True)
        
        ps.set_screenshot_extension(".jpg")
        ps.set_screenshot_extension(".png")
    
        ps.show(3)
    
    def test_slice_plane(self):

        plane1 = ps.add_scene_slice_plane()
        plane2 = ps.add_scene_slice_plane()

        plane1.set_pose((-.5, 0., 0.), (1., 1., 1.)) 

        plane1.set_active(False)
        self.assertEqual(False, plane1.get_active())
        
        plane1.set_draw_plane(False)
        self.assertEqual(False, plane1.get_draw_plane())
        
        plane1.set_draw_widget(False)
        self.assertEqual(False, plane1.get_draw_widget())

        ps.show(3)

        ps.remove_last_scene_slice_plane()
        ps.remove_last_scene_slice_plane()


    def test_load_material(self):

        ps.load_static_material("test_static", path.join(assets_prefix, "testwax_b.jpg"))
        ps.load_blendable_material("test_blend1", filenames=(
                        path.join(assets_prefix, "testwax_r.jpg"),
                        path.join(assets_prefix, "testwax_b.jpg"),
                        path.join(assets_prefix, "testwax_g.jpg"),
                        path.join(assets_prefix, "testwax_k.jpg")
                    ))
        
        ps.load_blendable_material("test_blend2", 
            filename_base=path.join(assets_prefix, "testwax"),
            filename_ext=".jpg")
    
    def test_load_cmap(self):
        ps.load_color_map("test_cmap", path.join(assets_prefix, "test_colormap.png"))
    

    def test_scene_extents(self):

        ps.set_automatically_compute_scene_extents(False)

        ps.set_length_scale(3.)
        self.assertAlmostEqual(ps.get_length_scale(), 3.)

        low = np.array((-1, -2., -3.)) 
        high = np.array((1., 2., 3.))
        ps.set_bounding_box(low, high)
        plow, phigh = ps.get_bounding_box()
        self.assertTrue(np.abs(plow-low).sum() < 0.0001)
        self.assertTrue(np.abs(phigh-high).sum() < 0.0001)
        
        ps.set_automatically_compute_scene_extents(True)
   

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
            print("executing function")

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


class TestStructureManagement(unittest.TestCase):

    def test_remove_all(self):
        pass

def test_transforms(t,s):

    T = np.array([
        [1., 0., 0., 3.],
        [0., 0., -1., -2.],
        [0., 1., 0., 5.],
        [0., 0., 0., 1.]
        ])
    v = np.array([1., 2., 3.])

    s.get_transform()
    s.get_position()
    s.center_bounding_box()
    s.rescale_to_unit()

    s.reset_transform()
    t.assertTrue(np.abs(s.get_transform()-np.eye(4)).sum() < 1e-4)
    t.assertTrue(np.abs(s.get_position()).sum() < 1e-4)
    
    s.set_transform(T)
    t.assertTrue(np.abs(s.get_transform()-T).sum() < 1e-4)

    s.reset_transform()
    s.set_position(v)
    t.assertTrue(np.abs(s.get_position()-v).sum() < 1e-4)

    s.translate(v)
    t.assertTrue(np.abs(s.get_position()-2.*v).sum() < 1e-4)


class TestPointCloud(unittest.TestCase):

    def generate_points(self, n_pts=10):
        np.random.seed(777)        
        return np.random.rand(n_pts, 3)

    def test_add_remove(self):

        # add
        p = ps.register_point_cloud("test_cloud", self.generate_points())
        self.assertTrue(ps.has_point_cloud("test_cloud"))
        self.assertFalse(ps.has_point_cloud("nope"))
        self.assertEqual(p.n_points(), 10)
      
        # remove by name
        ps.register_point_cloud("test_cloud2", self.generate_points())
        ps.remove_point_cloud("test_cloud2")
        self.assertTrue(ps.has_point_cloud("test_cloud"))
        self.assertFalse(ps.has_point_cloud("test_cloud2"))

        # remove by ref
        c = ps.register_point_cloud("test_cloud2", self.generate_points())
        c.remove()
        self.assertTrue(ps.has_point_cloud("test_cloud"))
        self.assertFalse(ps.has_point_cloud("test_cloud2"))

        # get by name
        ps.register_point_cloud("test_cloud3", self.generate_points(n_pts=10))
        p = ps.get_point_cloud("test_cloud3") # should be wrapped instance, not underlying PSB instance
        self.assertTrue(isinstance(p, ps.PointCloud))

        ps.remove_all_structures()
        
    def test_render(self):

        ps.register_point_cloud("test_cloud", self.generate_points())
        ps.show(3)
        ps.remove_all_structures()

    def test_options(self):

        p = ps.register_point_cloud("test_cloud", self.generate_points())

        # Set enabled
        p.set_enabled()
        p.set_enabled(False)
        p.set_enabled(True)
        self.assertTrue(p.is_enabled())

        # Radius
        p.set_radius(0.01)
        p.set_radius(0.1, relative=False)
        self.assertAlmostEqual(0.1, p.get_radius())
       
        # Render mode
        p.set_point_render_mode("sphere")
        self.assertEqual("sphere", p.get_point_render_mode())
        p.set_point_render_mode("quad")
        self.assertEqual("quad", p.get_point_render_mode())
        
        # Color
        color = (0.3, 0.3, 0.5)
        p.set_color(color)
        ret_color = p.get_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        # Material
        p.set_material("candy")
        self.assertEqual("candy", p.get_material())
        p.set_material("clay")
        
        # Transparency
        p.set_transparency(0.8)
        self.assertAlmostEqual(0.8, p.get_transparency())
        
        p2 = ps.register_point_cloud("test_cloud2", self.generate_points(),
                enabled=True, material='wax', radius=0.03, color=(1., 0., 0.), transparency=0.7)
                

        ps.show(3)
        ps.remove_all_structures()
        ps.set_transparency_mode('none')
    
    def test_transform(self):

        ps_cloud = ps.register_point_cloud("test_cloud", self.generate_points())
        test_transforms(self,ps_cloud)
        ps.remove_all_structures()
    
    def test_update(self):

        p = ps.register_point_cloud("test_cloud", self.generate_points())
        ps.show(3)

        newPos = self.generate_points() - 0.5
        p.update_point_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()
    
    
    def test_2D(self):
        np.random.seed(777)        
        points2D = np.random.rand(12, 2)

        p = ps.register_point_cloud("test_cloud", points2D)
        ps.show(3)

        newPos = points2D - 0.5
        p.update_point_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()
    
    def test_transparent_rendering(self):

        p = ps.register_point_cloud("test_cloud", self.generate_points(),
                transparency=0.5)

        ps.set_transparency_mode('none')
        ps.show(3)
        ps.set_transparency_mode('simple')
        ps.show(3)
        ps.set_transparency_mode('pretty')
        ps.show(3)
        
        ps.set_transparency_mode('none')
        ps.remove_all_structures()
    
    def test_slice_plane(self):

        p = ps.register_point_cloud("test_cloud", self.generate_points())

        plane = ps.add_scene_slice_plane()
        p.set_cull_whole_elements(True)
        ps.show(3)
        p.set_cull_whole_elements(False)
        ps.show(3)
        
        p.set_ignore_slice_plane(plane, True)
        self.assertEqual(True, p.get_ignore_slice_plane(plane))
        p.set_ignore_slice_plane(plane.get_name(), False)
        self.assertEqual(False, p.get_ignore_slice_plane(plane.get_name()))

        ps.remove_all_structures()
        ps.remove_last_scene_slice_plane()

    def test_scalar(self):
        pts = self.generate_points()
        N = pts.shape[0]
        ps.register_point_cloud("test_cloud", pts)
        p = ps.get_point_cloud("test_cloud")
        vals = np.random.rand(N)

        p.add_scalar_quantity("test_vals", vals)
        p.add_scalar_quantity("test_vals", vals, enabled=True)
        p.add_scalar_quantity("test_vals_with_range", vals, vminmax=(-5., 5.), enabled=True)
        p.add_scalar_quantity("test_vals_with_datatype", vals, enabled=True, datatype='symmetric')
        p.add_scalar_quantity("test_vals_with_cmap", vals, enabled=True, cmap='blues')
        ps.show(3)

        # test some additions/removal while we're at it
        p.remove_quantity("test_vals")
        p.remove_quantity("not_here") # should not error
        p.remove_all_quantities()
        p.remove_all_quantities()
        ps.remove_all_structures()
    
    def test_color(self):
        pts = self.generate_points()
        N = pts.shape[0]
        p = ps.register_point_cloud("test_cloud", pts)
        vals = np.random.rand(N,3)

        p.add_color_quantity("test_vals", vals)
        p.add_color_quantity("test_vals", vals, enabled=True)
        ps.show(3)
        
        p.remove_all_quantities()
        ps.remove_all_structures()
    
    def test_vector(self):
        pts = self.generate_points()
        N = pts.shape[0]
        p = ps.register_point_cloud("test_cloud", pts)
        vals = np.random.rand(N,3)

        p.add_vector_quantity("test_vals1", vals)
        p.add_vector_quantity("test_vals2", vals, enabled=True)
        p.add_vector_quantity("test_vals3", vals, enabled=True, vectortype='ambient')
        p.add_vector_quantity("test_vals4", vals, enabled=True, length=0.005)
        p.add_vector_quantity("test_vals5", vals, enabled=True, radius=0.001)
        p.add_vector_quantity("test_vals6", vals, enabled=True, color=(0.2, 0.5, 0.5))

        # 2D 
        p.add_vector_quantity("test_vals7", vals[:,:2], enabled=True, radius=0.001)

        ps.show(3)
    
        p.remove_all_quantities()
        ps.remove_all_structures()
    

    def test_variable_radius(self):
        pts = self.generate_points()
        N = pts.shape[0]
        ps.register_point_cloud("test_cloud", pts)
        p = ps.get_point_cloud("test_cloud")
        vals = np.random.rand(N)

        p.add_scalar_quantity("test_vals", vals)

        p.set_point_radius_quantity("test_vals")
        ps.show(3)
        p.clear_point_radius_quantity()
        ps.show(3)
        p.set_point_radius_quantity("test_vals", False)
        ps.show(3)

        ps.remove_all_structures()
    
class TestCurveNetwork(unittest.TestCase):

    def generate_points(self, n_pts=10):
        np.random.seed(777)        
        return np.random.rand(n_pts, 3)
    
    def generate_edges(self, n_pts=10):
        np.random.seed(777)        
        return np.random.randint(0, n_pts, size=(2*n_pts,2))

    def test_add_remove(self):

        # add
        n = ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())
        self.assertTrue(ps.has_curve_network("test_network"))
        self.assertFalse(ps.has_curve_network("nope"))
        self.assertEqual(n.n_nodes(), 10)
        self.assertEqual(n.n_edges(), 20)
      
        # remove by name
        ps.register_curve_network("test_network2", self.generate_points(), self.generate_edges())
        ps.remove_curve_network("test_network2")
        self.assertTrue(ps.has_curve_network("test_network"))
        self.assertFalse(ps.has_curve_network("test_network2"))

        # remove by ref
        c = ps.register_curve_network("test_network2", self.generate_points(), self.generate_edges())
        c.remove()
        self.assertTrue(ps.has_curve_network("test_network"))
        self.assertFalse(ps.has_curve_network("test_network2"))

        # get by name
        ps.register_curve_network("test_network3", self.generate_points(), self.generate_edges())
        p = ps.get_curve_network("test_network3") # should be wrapped instance, not underlying PSB instance
        self.assertTrue(isinstance(p, ps.CurveNetwork))

        ps.remove_all_structures()

    def test_convenience_add(self):
        ps.register_curve_network("test_network_line", self.generate_points(), 'line')
        ps.register_curve_network("test_network_line2D", self.generate_points()[:,:2], 'line')
        ps.register_curve_network("test_network_loop", self.generate_points(), 'loop')
        ps.register_curve_network("test_network_loop2D", self.generate_points()[:,:2], 'loop')

        ps.show(3)
        ps.remove_all_structures();
        
    def test_render(self):

        ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())
        ps.show(3)
        ps.remove_all_structures()

    def test_options(self):

        p = ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())

        # Set enabled
        p.set_enabled()
        p.set_enabled(False)
        p.set_enabled(True)
        self.assertTrue(p.is_enabled())

        # Radius
        p.set_radius(0.01)
        p.set_radius(0.1, relative=False)
        self.assertAlmostEqual(0.1, p.get_radius())
        
        # Color
        color = (0.3, 0.3, 0.5)
        p.set_color(color)
        ret_color = p.get_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        # Material
        p.set_material("candy")
        self.assertEqual("candy", p.get_material())
        p.set_material("clay")
        
        # Transparency
        p.set_transparency(0.8)
        self.assertAlmostEqual(0.8, p.get_transparency())
        
        p2 = ps.register_curve_network("test_network2", self.generate_points(), self.generate_edges(), 
                enabled=False, material='wax', radius=0.03, color=(1., 0., 0.), transparency=0.9)

        ps.show(3)
        ps.remove_all_structures()
        ps.set_transparency_mode('none')
    
    def test_transform(self):

        p = ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())
        test_transforms(self,p)
        ps.remove_all_structures()
    
    def test_slice_plane(self):

        p = ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())

        plane = ps.add_scene_slice_plane()
        p.set_cull_whole_elements(True)
        ps.show(3)
        p.set_cull_whole_elements(False)
        ps.show(3)
        
        p.set_ignore_slice_plane(plane, True)
        self.assertEqual(True, p.get_ignore_slice_plane(plane))
        p.set_ignore_slice_plane(plane.get_name(), False)
        self.assertEqual(False, p.get_ignore_slice_plane(plane.get_name()))

        ps.remove_all_structures()
        ps.remove_last_scene_slice_plane()

    
    def test_update(self):

        p = ps.register_curve_network("test_network", self.generate_points(), self.generate_edges())
        ps.show(3)

        newPos = self.generate_points() - 0.5
        p.update_node_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()
    
    
    def test_2D(self):
        np.random.seed(777)        
        points2D = np.random.rand(10, 2)

        p = ps.register_curve_network("test_network", points2D, self.generate_edges())
        ps.show(3)

        newPos = points2D - 0.5
        p.update_node_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()

    def test_scalar(self):
        pts = self.generate_points()
        N = pts.shape[0]
        ps.register_curve_network("test_network", pts, self.generate_edges())
        p = ps.get_curve_network("test_network")

        for on in ['nodes', 'edges']:
       
            if on == 'nodes':
                vals = np.random.rand(N)
            elif on  == 'edges':
                vals = np.random.rand(2*N)

            p.add_scalar_quantity("test_vals", vals, defined_on=on)
            p.add_scalar_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_scalar_quantity("test_vals_with_range", vals, defined_on=on, vminmax=(-5., 5.), enabled=True)
            p.add_scalar_quantity("test_vals_with_datatype", vals, defined_on=on, enabled=True, datatype='symmetric')
            p.add_scalar_quantity("test_vals_with_cmap", vals, defined_on=on, enabled=True, cmap='blues')

            ps.show(3)

            # test some additions/removal while we're at it
            p.remove_quantity("test_vals")
            p.remove_quantity("not_here") # should not error
            p.remove_all_quantities()
            p.remove_all_quantities()

        ps.remove_all_structures()
    
    def test_color(self):
        pts = self.generate_points()
        N = pts.shape[0]
        p = ps.register_curve_network("test_network", pts, self.generate_edges())

        for on in ['nodes', 'edges']:
       
            if on == 'nodes':
                vals = np.random.rand(N,3)
            elif on  == 'edges':
                vals = np.random.rand(2*N, 3)

            p.add_color_quantity("test_vals", vals, defined_on=on)
            p.add_color_quantity("test_vals", vals, defined_on=on, enabled=True)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()
    
    def test_vector(self):
        pts = self.generate_points()
        N = pts.shape[0]
        p = ps.register_curve_network("test_network", pts, self.generate_edges())
        vals = np.random.rand(N,3)
        
        for on in ['nodes', 'edges']:
       
            if on == 'nodes':
                vals = np.random.rand(N,3)
            elif on  == 'edges':
                vals = np.random.rand(2*N, 3)

            p.add_vector_quantity("test_vals1", vals, defined_on=on)
            p.add_vector_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_vector_quantity("test_vals3", vals, defined_on=on, enabled=True, vectortype='ambient')
            p.add_vector_quantity("test_vals4", vals, defined_on=on, enabled=True, length=0.005)
            p.add_vector_quantity("test_vals5", vals, defined_on=on, enabled=True, radius=0.001)
            p.add_vector_quantity("test_vals6", vals, defined_on=on, enabled=True, color=(0.2, 0.5, 0.5))
            
            # 2D 
            p.add_vector_quantity("test_vals7", vals[:,:2], defined_on=on, enabled=True, radius=0.001)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()


class TestSurfaceMesh(unittest.TestCase):

    def generate_verts(self, n_pts=10):
        np.random.seed(777)        
        return np.random.rand(n_pts, 3)
    
    def generate_faces(self, n_pts=10):
        np.random.seed(777)        
        return np.random.randint(0, n_pts, size=(2*n_pts,3))
    
    def test_add_remove(self):

        # add
        n = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        self.assertTrue(ps.has_surface_mesh("test_mesh"))
        self.assertFalse(ps.has_surface_mesh("nope"))
        self.assertEqual(n.n_vertices(), 10)
        self.assertEqual(n.n_faces(), 20)
        self.assertGreater(n.n_edges(), 1)
        self.assertEqual(n.n_corners(), 3*20)
        self.assertEqual(n.n_halfedges(), 3*20)
      
        # remove by name
        ps.register_surface_mesh("test_mesh2", self.generate_verts(), self.generate_faces())
        ps.remove_surface_mesh("test_mesh2")
        self.assertTrue(ps.has_surface_mesh("test_mesh"))
        self.assertFalse(ps.has_surface_mesh("test_mesh2"))

        # remove by ref
        c = ps.register_surface_mesh("test_mesh2", self.generate_verts(), self.generate_faces())
        c.remove()
        self.assertTrue(ps.has_surface_mesh("test_mesh"))
        self.assertFalse(ps.has_surface_mesh("test_mesh2"))

        # get by name
        ps.register_surface_mesh("test_mesh3", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh3") # should be wrapped instance, not underlying PSB instance
        self.assertTrue(isinstance(p, ps.SurfaceMesh))

        ps.remove_all_structures()
    
    
    def test_add_quad(self):

        n_pts=10
        faces = np.random.randint(0, n_pts, size=(2*n_pts,4))
        ps.register_surface_mesh("test_mesh", self.generate_verts(), faces)
        ps.show(3)
        ps.remove_all_structures()
    
    def test_add_varied_degree(self):

        n_pts = 10
        n_face = 20
        faces = []
        for i in range(n_face):
            faces.append([0,1,2,])
            faces.append([0,1,2,4])
            faces.append([0,1,2,4,5])

        ps.register_surface_mesh("test_mesh", self.generate_verts(), faces)
        ps.show(3)
        ps.remove_all_structures()

    def test_render(self):

        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        ps.show(3)
        ps.remove_all_structures()


    def test_options(self):

        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())

        # Set enabled
        p.set_enabled()
        p.set_enabled(False)
        p.set_enabled(True)
        self.assertTrue(p.is_enabled())
    
        # Color
        color = (0.3, 0.3, 0.5)
        p.set_color(color)
        ret_color = p.get_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])

        # Edge color
        color = (0.1, 0.5, 0.5)
        p.set_edge_color(color)
        ret_color = p.get_edge_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        ps.show(3)

        # Smooth shade
        p.set_smooth_shade(True)
        ps.show(3)
        self.assertTrue(p.get_smooth_shade())
        p.set_smooth_shade(False)
        ps.show(3)

        # Edge width 
        p.set_edge_width(1.5)
        ps.show(3)
        self.assertAlmostEqual(p.get_edge_width(), 1.5)
        
        # Material
        p.set_material("candy")
        self.assertEqual("candy", p.get_material())
        p.set_material("clay")
        
        # Back face 
        p.set_back_face_policy("different")
        self.assertEqual("different", p.get_back_face_policy())
        p.set_back_face_policy("custom")
        self.assertEqual("custom", p.get_back_face_policy())
        p.set_back_face_color((0.25, 0.25, 0.25))
        self.assertEqual((0.25, 0.25, 0.25), p.get_back_face_color())
        p.set_back_face_policy("cull")
        
        # Transparency
        p.set_transparency(0.8)
        self.assertAlmostEqual(0.8, p.get_transparency())
      
        # Set with optional arguments 
        p2 = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces(), 
                    enabled=True, material='wax', color=(1., 0., 0.), edge_color=(0.5, 0.5, 0.5), 
                    smooth_shade=True, edge_width=0.5, back_face_policy="cull", back_face_color=(0.1, 0.1, 0.1), transparency=0.9)
        
        # Make sure shadows work
        ps.set_ground_plane_mode("shadow_only")

        ps.show(3)
        ps.remove_all_structures()
        ps.set_transparency_mode('none')
    
    def test_transform(self):

        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        test_transforms(self,p)
        ps.remove_all_structures()
    
    def test_slice_plane(self):

        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())

        plane = ps.add_scene_slice_plane()
        p.set_cull_whole_elements(True)
        ps.show(3)
        p.set_cull_whole_elements(False)
        ps.show(3)
        
        p.set_ignore_slice_plane(plane, True)
        self.assertEqual(True, p.get_ignore_slice_plane(plane))
        p.set_ignore_slice_plane(plane.get_name(), False)
        self.assertEqual(False, p.get_ignore_slice_plane(plane.get_name()))

        ps.remove_all_structures()
        ps.remove_last_scene_slice_plane()
    
    def test_update(self):

        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        ps.show(3)

        newPos = self.generate_verts() - 0.5
        p.update_vertex_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()
    
    def test_2D(self):
        np.random.seed(777)        
        points2D = self.generate_verts()[:,:2]

        p = ps.register_surface_mesh("test_mesh", points2D, self.generate_faces())
        ps.show(3)

        newPos = points2D - 0.5
        p.update_vertex_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()
    
    
    def test_permutation(self):
        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())

        p.set_vertex_permutation(np.random.permutation(p.n_vertices()))
        p.set_vertex_permutation(np.random.permutation(p.n_vertices()), 3*p.n_vertices())

        p.set_face_permutation(np.random.permutation(p.n_faces()))
        p.set_face_permutation(np.random.permutation(p.n_faces()), 3*p.n_faces())
        
        p.set_edge_permutation(np.random.permutation(p.n_edges()))
        p.set_edge_permutation(np.random.permutation(p.n_edges()), 3*p.n_edges())
        
        p.set_corner_permutation(np.random.permutation(p.n_corners()))
        p.set_corner_permutation(np.random.permutation(p.n_corners()), 3*p.n_corners())
        
        p.set_halfedge_permutation(np.random.permutation(p.n_halfedges()))
        p.set_halfedge_permutation(np.random.permutation(p.n_halfedges()), 3*p.n_halfedges())

        p = ps.register_surface_mesh("test_mesh2", self.generate_verts(), self.generate_faces())

        p.set_all_permutations(
            vertex_perm=np.random.permutation(p.n_vertices()),
            face_perm=np.random.permutation(p.n_faces()),
            edge_perm=np.random.permutation(p.n_edges()),
            corner_perm=np.random.permutation(p.n_corners()),
            halfedge_perm=np.random.permutation(p.n_halfedges()),
        )

        ps.show(3)
        ps.remove_all_structures()


    def test_tangent_basis(self):
        p = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())

        p.set_vertex_tangent_basisX(np.random.rand(p.n_vertices(), 3))
        p.set_vertex_tangent_basisX(np.random.rand(p.n_vertices(), 2))

        p.set_face_tangent_basisX(np.random.rand(p.n_faces(), 3))
        p.set_face_tangent_basisX(np.random.rand(p.n_faces(), 2))

        ps.show(3)
        ps.remove_all_structures()
    
    def test_scalar(self):
        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")

        for on in ['vertices', 'faces', 'edges', 'halfedges']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices())
            elif on == 'faces':
                vals = np.random.rand(p.n_faces())
            elif on  == 'edges':
                vals = np.random.rand(p.n_edges())
            elif on  == 'halfedges':
                vals = np.random.rand(p.n_halfedges())

            p.add_scalar_quantity("test_vals", vals, defined_on=on)
            p.add_scalar_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_scalar_quantity("test_vals_with_range", vals, defined_on=on, vminmax=(-5., 5.), enabled=True)
            p.add_scalar_quantity("test_vals_with_datatype", vals, defined_on=on, enabled=True, datatype='symmetric')
            p.add_scalar_quantity("test_vals_with_cmap", vals, defined_on=on, enabled=True, cmap='blues')

            ps.show(3)

            # test some additions/removal while we're at it
            p.remove_quantity("test_vals")
            p.remove_quantity("not_here") # should not error
            p.remove_all_quantities()
            p.remove_all_quantities()

        ps.remove_all_structures()
    
    def test_color(self):
        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")

        for on in ['vertices', 'faces']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(), 3)
            elif on == 'faces':
                vals = np.random.rand(p.n_faces(), 3)
       

            p.add_color_quantity("test_vals", vals, defined_on=on)
            p.add_color_quantity("test_vals", vals, defined_on=on, enabled=True)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()
    
    
    def test_distance(self):
        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")

        for on in ['vertices']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices())

            p.add_distance_quantity("test_vals", vals, defined_on=on)
            p.add_distance_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_distance_quantity("test_vals_with_range", vals, defined_on=on, vminmax=(-5., 5.), enabled=True)
            p.add_distance_quantity("test_vals_with_signed", vals, defined_on=on, enabled=True, signed=True)
            p.add_distance_quantity("test_vals_with_unsigned", vals, defined_on=on, enabled=True, signed=False)
            p.add_distance_quantity("test_vals_with_stripe", vals, defined_on=on, enabled=True, stripe_size=0.01)
            p.add_distance_quantity("test_vals_with_stripe_reltrue", vals, defined_on=on, enabled=True, stripe_size=0.01, stripe_size_relative=True)
            p.add_distance_quantity("test_vals_with_stripe_relfalse", vals, defined_on=on, enabled=True, stripe_size=0.01, stripe_size_relative=False)

            ps.show(3)

            p.remove_all_quantities()

        ps.remove_all_structures()

    def test_parameterization(self):

        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")

        for on in ['vertices', 'corners']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(), 2)
            elif on == 'corners':
                vals = np.random.rand(p.n_corners(), 2)

            cA = (0.1, 0.2, 0.3)
            cB = (0.4, 0.5, 0.6)

            p.add_parameterization_quantity("test_vals1", vals, defined_on=on, enabled=True)

            p.add_parameterization_quantity("test_vals2", vals, defined_on=on, coords_type='world')
            p.add_parameterization_quantity("test_vals3", vals, defined_on=on, coords_type='unit')

            p.add_parameterization_quantity("test_vals4", vals, defined_on=on, viz_style='checker')
            p.add_parameterization_quantity("test_vals5", vals, defined_on=on, viz_style='grid')
            p.add_parameterization_quantity("test_vals6", vals, defined_on=on, viz_style='local_check')
            p.add_parameterization_quantity("test_vals7", vals, defined_on=on, viz_style='local_rad')

            p.add_parameterization_quantity("test_vals8", vals, defined_on=on, grid_colors=(cA, cB))
            p.add_parameterization_quantity("test_vals9", vals, defined_on=on, checker_colors=(cA, cB))
            p.add_parameterization_quantity("test_vals10", vals, defined_on=on, checker_size=0.1)
            p.add_parameterization_quantity("test_vals11", vals, defined_on=on, cmap='blues')

            ps.show(3)

            p.remove_all_quantities()

        ps.remove_all_structures()
    
    def test_vector(self):

        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")
        
        for on in ['vertices', 'faces']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(),3)
            elif on  == 'faces':
                vals = np.random.rand(p.n_faces(), 3)

            p.add_vector_quantity("test_vals1", vals, defined_on=on)
            p.add_vector_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_vector_quantity("test_vals3", vals, defined_on=on, enabled=True, vectortype='ambient')
            p.add_vector_quantity("test_vals4", vals, defined_on=on, enabled=True, length=0.005)
            p.add_vector_quantity("test_vals5", vals, defined_on=on, enabled=True, radius=0.001)
            p.add_vector_quantity("test_vals6", vals, defined_on=on, enabled=True, color=(0.2, 0.5, 0.5))
            
            # 2D 
            p.add_vector_quantity("test_vals7", vals[:,:2], defined_on=on, enabled=True, radius=0.001)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()
   

    def test_intrinsic_vector(self):

        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")
        
        for on in ['vertices', 'faces']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(),2)
                p.set_vertex_tangent_basisX(np.random.rand(p.n_vertices(), 3));
            elif on  == 'faces':
                vals = np.random.rand(p.n_faces(), 2)
                p.set_face_tangent_basisX(np.random.rand(p.n_faces(), 3));

            p.add_intrinsic_vector_quantity("test_vals1", vals, defined_on=on)
            p.add_intrinsic_vector_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_intrinsic_vector_quantity("test_vals3", vals, defined_on=on, enabled=True, vectortype='ambient')
            p.add_intrinsic_vector_quantity("test_vals4", vals, defined_on=on, enabled=True, length=0.005)
            p.add_intrinsic_vector_quantity("test_vals5", vals, defined_on=on, enabled=True, radius=0.001)
            p.add_intrinsic_vector_quantity("test_vals6", vals, defined_on=on, enabled=True, color=(0.2, 0.5, 0.5))
            p.add_intrinsic_vector_quantity("test_vals7", vals, defined_on=on, enabled=True, radius=0.001, ribbon=True)
            p.add_intrinsic_vector_quantity("test_vals8", vals, n_sym=4, defined_on=on, enabled=True)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()
    
    def test_one_form_intrinsic_vector(self):

        ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces())
        p = ps.get_surface_mesh("test_mesh")
        p.set_vertex_tangent_basisX(np.random.rand(p.n_vertices(), 3));
        
        vals = np.random.rand(p.n_edges())
        orients = np.random.rand(p.n_edges()) > 0.5

        p.add_one_form_vector_quantity("test_vals1", vals, orients)
        p.add_one_form_vector_quantity("test_vals2", vals, orients, enabled=True)
        p.add_one_form_vector_quantity("test_vals3", vals, orients, enabled=True) 
        p.add_one_form_vector_quantity("test_vals4", vals, orients, enabled=True, length=0.005)
        p.add_one_form_vector_quantity("test_vals5", vals, orients, enabled=True, radius=0.001)
        p.add_one_form_vector_quantity("test_vals6", vals, orients, enabled=True, color=(0.2, 0.5, 0.5))
        p.add_one_form_vector_quantity("test_vals7", vals, orients, enabled=True, radius=0.001, ribbon=True)

        ps.show(3)
        p.remove_all_quantities()
        
        ps.remove_all_structures()

class TestVolumeMesh(unittest.TestCase):

    def generate_verts(self, n_pts=10):
        np.random.seed(777)        
        return np.random.rand(n_pts, 3)
    
    def generate_tets(self, n_pts=10):
        np.random.seed(777)        
        return np.random.randint(0, n_pts, size=(2*n_pts,4))
    
    def test_add_remove(self):

        # add
        n = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        self.assertTrue(ps.has_volume_mesh("test_mesh"))
        self.assertFalse(ps.has_volume_mesh("nope"))
        self.assertEqual(n.n_vertices(), 10)
        self.assertEqual(n.n_cells(), 20)
      
        # remove by name
        ps.register_volume_mesh("test_mesh2", self.generate_verts(), self.generate_tets())
        ps.remove_volume_mesh("test_mesh2")
        self.assertTrue(ps.has_volume_mesh("test_mesh"))
        self.assertFalse(ps.has_volume_mesh("test_mesh2"))

        # remove by ref
        c = ps.register_volume_mesh("test_mesh2", self.generate_verts(), self.generate_tets())
        c.remove()
        self.assertTrue(ps.has_volume_mesh("test_mesh"))
        self.assertFalse(ps.has_volume_mesh("test_mesh2"))

        # get by name
        ps.register_volume_mesh("test_mesh3", self.generate_verts(), self.generate_tets())
        p = ps.get_volume_mesh("test_mesh3") # should be wrapped instance, not underlying PSB instance
        self.assertTrue(isinstance(p, ps.VolumeMesh))

        ps.remove_all_structures()
    
    def test_render(self):

        ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        ps.show(3)
        ps.remove_all_structures()
    
    def test_add_tet(self):
        ps.register_volume_mesh("test_mesh3", self.generate_verts(), tets=self.generate_tets())
        ps.show(3)
        ps.remove_all_structures()
    
    def test_add_hex(self):
        np.random.seed(777)
        n_pts = 10
        cells = np.random.randint(0, n_pts, size=(2*n_pts,8))
        ps.register_volume_mesh("test_mesh3", self.generate_verts(), hexes=cells)
        ps.show(3)
        ps.remove_all_structures()
    
    def test_add_combined(self):
        np.random.seed(777)
        n_pts = 10
        cells = np.random.randint(0, n_pts, size=(2*n_pts,8))
        ps.register_volume_mesh("test_mesh3", self.generate_verts(), tets=self.generate_tets(), hexes=cells)
        ps.show(3)
        ps.remove_all_structures()
    
    def test_add_mixed(self):
        np.random.seed(777)
        n_pts = 10
        cells = np.random.randint(0, n_pts, size=(2*n_pts,8))
        cells[-5:,4:] = -1 # clear out some rows at end
        ps.register_volume_mesh("test_mesh3", self.generate_verts(), mixed_cells=cells)
        ps.show(3)
        ps.remove_all_structures()

        # test a few error cases
        # cells = np.random.randint(0, n_pts, size=(2*n_pts,8))
        # cells[-5:,4:] = -1 # clear out some rows at end
        # ps.register_volume_mesh("test_mesh3", self.generate_verts(), hexes=self.generate_tets())

    def test_options(self):

        p = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())

        # Set enabled
        p.set_enabled()
        p.set_enabled(False)
        p.set_enabled(True)
        self.assertTrue(p.is_enabled())
    
        # Color
        color = (0.3, 0.3, 0.5)
        p.set_color(color)
        ret_color = p.get_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        # Interior Color
        color = (0.45, 0.85, 0.2)
        p.set_interior_color(color)
        ret_color = p.get_interior_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])

        # Edge color
        color = (0.1, 0.5, 0.5)
        p.set_edge_color(color)
        ret_color = p.get_edge_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        ps.show(3)

        # Edge width 
        p.set_edge_width(1.5)
        ps.show(3)
        self.assertAlmostEqual(p.get_edge_width(), 1.5)
        
        # Material
        p.set_material("candy")
        self.assertEqual("candy", p.get_material())
        p.set_material("clay")
        
        # Transparency
        p.set_transparency(0.8)
        self.assertAlmostEqual(0.8, p.get_transparency())
      
        # Set with optional arguments 
        p2 = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets(), 
                    enabled=True, material='wax', color=(1., 0., 0.), edge_color=(0.5, 0.5, 0.5), 
                    interior_color=(0.2, 0.2, 0.2), edge_width=0.5,
                    transparency=0.9)

        ps.show(3)
        ps.remove_all_structures()
        ps.set_transparency_mode('none')
    
    def test_transform(self):

        p = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        test_transforms(self,p)
        ps.remove_all_structures()
   
    def test_slice_plane(self):

        p = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())

        plane = ps.add_scene_slice_plane()
        p.set_cull_whole_elements(True)
        ps.show(3)
        p.set_cull_whole_elements(False)
        ps.show(3)
        
        p.set_ignore_slice_plane(plane, True)
        self.assertEqual(True, p.get_ignore_slice_plane(plane))
        p.set_ignore_slice_plane(plane.get_name(), False)
        self.assertEqual(False, p.get_ignore_slice_plane(plane.get_name()))

        plane.set_volume_mesh_to_inspect("test_mesh")
        self.assertEqual("test_mesh", plane.get_volume_mesh_to_inspect())
        
        ps.show(3)

        ps.remove_all_structures()
        ps.remove_last_scene_slice_plane()

    def test_update(self):

        p = ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        ps.show(3)

        newPos = self.generate_verts() - 0.5
        p.update_vertex_positions(newPos)

        ps.show(3)
        ps.remove_all_structures()

    def test_scalar(self):
        ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        p = ps.get_volume_mesh("test_mesh")

        for on in ['vertices', 'cells']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices())
            elif on  == 'cells':
                vals = np.random.rand(p.n_cells())

            p.add_scalar_quantity("test_vals", vals, defined_on=on)
            p.add_scalar_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_scalar_quantity("test_vals_with_range", vals, defined_on=on, vminmax=(-5., 5.), enabled=True)
            p.add_scalar_quantity("test_vals_with_datatype", vals, defined_on=on, enabled=True, datatype='symmetric')
            p.add_scalar_quantity("test_vals_with_cmap", vals, defined_on=on, enabled=True, cmap='blues')

            ps.show(3)

            # test some additions/removal while we're at it
            p.remove_quantity("test_vals")
            p.remove_quantity("not_here") # should not error
            p.remove_all_quantities()
            p.remove_all_quantities()

        ps.remove_all_structures()
    
    
    def test_color(self):
        ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        p = ps.get_volume_mesh("test_mesh")

        for on in ['vertices', 'cells']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(), 3)
            elif on == 'cells':
                vals = np.random.rand(p.n_cells(), 3)
       

            p.add_color_quantity("test_vals", vals, defined_on=on)
            p.add_color_quantity("test_vals", vals, defined_on=on, enabled=True)

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()
    

    def test_vector(self):

        ps.register_volume_mesh("test_mesh", self.generate_verts(), self.generate_tets())
        p = ps.get_volume_mesh("test_mesh")
        
        for on in ['vertices', 'cells']:
       
            if on == 'vertices':
                vals = np.random.rand(p.n_vertices(),3)
            elif on  == 'cells':
                vals = np.random.rand(p.n_cells(), 3)

            p.add_vector_quantity("test_vals1", vals, defined_on=on)
            p.add_vector_quantity("test_vals2", vals, defined_on=on, enabled=True)
            p.add_vector_quantity("test_vals3", vals, defined_on=on, enabled=True, vectortype='ambient')
            p.add_vector_quantity("test_vals4", vals, defined_on=on, enabled=True, length=0.005)
            p.add_vector_quantity("test_vals5", vals, defined_on=on, enabled=True, radius=0.001)
            p.add_vector_quantity("test_vals6", vals, defined_on=on, enabled=True, color=(0.2, 0.5, 0.5))

            ps.show(3)
            p.remove_all_quantities()
        
        ps.remove_all_structures()

if __name__ == '__main__':

    # Parse out test-specific args (this is kinda poor design, but very useful)
    ps_backend = "openGL_mock"
    if len(sys.argv) > 1:
        for a in sys.argv:
            if a.startswith("backend="):
                ps_backend = a[len("backend="):]
                sys.argv.remove(a)

    # Really global setup.
    # Note that since these tests depend on the bound object's global state, 
    # we generally cannot continue past the first failed test.
    ps.set_errors_throw_exceptions(True)
    ps.init(ps_backend) 

    unittest.main()
