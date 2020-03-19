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
        ps.register_point_cloud("test_cloud", self.generate_points())
        self.assertTrue(ps.has_point_cloud("test_cloud"))
        self.assertFalse(ps.has_point_cloud("nope"))
      
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
        self.assertEqual(p.N, 10) # field N only appears in wrapped instance

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
        p.set_point_radius(0.01)
        p.set_point_radius(0.1, relative=False)
        self.assertAlmostEqual(0.1, p.get_point_radius())
        
        # Color
        color = (0.3, 0.3, 0.5)
        p.set_point_color(color)
        ret_color = p.get_point_color()
        for i in range(3):
            self.assertAlmostEqual(ret_color[i], color[i])
        
        # Material
        p.set_material("candy")
        self.assertEqual("candy", p.get_material())
        p.set_material("clay")
        
        
        p2 = ps.register_point_cloud("test_cloud2", self.generate_points(),
                enabled=False, point_radius=0.03, point_color=(1., 0., 0.))

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
        ps.show(3)
        
        p.add_scalar_quantity("test_vals", vals, enabled=True)
        ps.show(3)
        
        p.add_scalar_quantity("test_vals_with_range", vals, vminmax=(-5., 5.), enabled=True)
        ps.show(3)
        
        p.add_scalar_quantity("test_vals_with_datatype", vals, enabled=True, datatype='symmetric')
        ps.show(3)
        
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
        ps.show(3)
        
        p.add_color_quantity("test_vals", vals, enabled=True)
        ps.show(3)
        
        p.remove_all_quantities()
        ps.remove_all_structures()
    
    def test_vector(self):
        pts = self.generate_points()
        N = pts.shape[0]
        p = ps.register_point_cloud("test_cloud", pts)
        vals = np.random.rand(N,3)

        p.add_vector_quantity("test_vals", vals)
        ps.show(3)
        
        p.add_vector_quantity("test_vals", vals, enabled=True)
        ps.show(3)
        
        p.add_vector_quantity("test_vals", vals, enabled=True, vectortype='ambient')
        ps.show(3)
        
        p.add_vector_quantity("test_vals", vals, enabled=True, length=0.005)
        ps.show(3)
        
        p.add_vector_quantity("test_vals", vals, enabled=True, radius=0.001)
        ps.show(3)
        
        p.add_vector_quantity("test_vals", vals, enabled=True, color=(0.2, 0.5, 0.5))
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
