import unittest
import os
import sys
import os.path as path
import numpy as np

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))
sys.path.append(os.path.join(os.path.dirname(__file__), "../source/"))

import polyscope as ps

# Path to test assets
assets_prefix = path.join(path.dirname(__file__), "assets/")
assetpath_spot = path.join(assets_prefix, "spot.obj")


class TestCore(unittest.TestCase):

    def test_show(self):
        ps.show(forFrames=3)


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
        
        
        p2 = ps.register_point_cloud("test_cloud2", self.generate_points(),
                enabled=False, material='wax', radius=0.03, color=(1., 0., 0.))

        ps.show(3)
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
        
        
        p2 = ps.register_curve_network("test_network2", self.generate_points(), self.generate_edges(), 
                enabled=False, material='wax', radius=0.03, color=(1., 0., 0.))

        ps.show(3)
        ps.remove_all_structures()
    
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

    def test_options(self):
        pass


if __name__ == '__main__':

    # Really global setup.
    # Note that since these tests depend on the bound object's global state, 
    # we generally cannot continue past the first failed test.
    ps.set_errors_throw_exceptions(True)
    ps.init() 

    unittest.main()
