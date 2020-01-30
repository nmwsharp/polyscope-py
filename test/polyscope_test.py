import unittest
import os
import sys
import os.path as path
import numpy as np

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))

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

        # Radius
        p.set_point_radius(0.01)
        p.set_point_radius(0.1, relative=False)
        
        # Color
        p.set_point_color((0.3, 0.3, 0.5))
        
        
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
