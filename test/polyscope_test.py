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
        
        ps.show(3)
    
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
    

class TestStructureManagement(unittest.TestCase):

    def test_remove_all(self):
        pass


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
        
        # Back face policy
        p.set_back_face_policy("different")
        self.assertEqual("different", p.get_back_face_policy())
        p.set_back_face_policy("cull")
        
        # Transparency
        p.set_transparency(0.8)
        self.assertAlmostEqual(0.8, p.get_transparency())
      
        # Set with optional arguments 
        p2 = ps.register_surface_mesh("test_mesh", self.generate_verts(), self.generate_faces(), 
                    enabled=True, material='wax', color=(1., 0., 0.), edge_color=(0.5, 0.5, 0.5), 
                    smooth_shade=True, edge_width=0.5, back_face_policy="cull",
                    transparency=0.9)
        
        # Make sure shadows work
        ps.set_ground_plane_mode("shadow_only")

        ps.show(3)
        ps.remove_all_structures()
        ps.set_transparency_mode('none')
    
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

        plane.set_sliced_volume_mesh("test_mesh")
        self.assertEqual("test_mesh", plane.get_sliced_volume_mesh())

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
