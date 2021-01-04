import sys, os

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))
sys.path.append(os.path.join(os.path.dirname(__file__), "../src/"))

import numpy as np
import polyscope as ps


ps.set_use_prefs_file(False)
ps.set_always_redraw(True)
ps.init()


np.random.seed(1)
points = np.random.rand(4, 3)
vals = np.random.rand(4, 3)


ps_cloud = ps.register_point_cloud('points', 5*points, enabled=True, radius=0.08)
ps_cloud.add_color_quantity("rand colors", vals, enabled=True)
ps.screenshot(filename='points_z.png')
ps.show()

ps_cloud = ps.register_point_cloud('points', points, enabled=True, radius=0.08)
ps_cloud.add_color_quantity("rand colors", vals, enabled=True)
ps.reset_camera_to_home_view()
ps.screenshot(filename='points_y.png')
ps.show()
