import unittest
import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))

import polyscope

# Path to test assets
assets_prefix = path.join(path.dirname(__file__), "assets/")
assetpath_spot = path.join(assets_prefix, "spot.obj")


class TestBasics(unittest.TestCase):

    def test_create_empty(self):
        pass
        # ply = happly.PlyData()

    def test_load_from_file(self):
        pass
        # ply = happly.load(assetpath_platonic_shelf_ascii)

    def test_read_double(self):
        pass
        # ply = happly.load(assetpath_platonic_shelf_ascii)
        # vals = ply["vertex"]["x"]
        # print(vals)
        # print(type(vals))
        # print(vals.dtype)


if __name__ == '__main__':
    unittest.main()
