import polyscope as ps
import numpy as np
ps.init()
g = ps.register_group("a_group")
g1 = ps.register_group("curves")
ps.set_parent_group(g1, g)
for i in range(3):
    nodes = np.random.rand(100, 3)
    edges = np.random.randint(0, 100, size=(250,2))
    ps_net = ps.register_curve_network("my network {}".format(i), nodes, edges)
    ps.set_parent_group(ps_net, g1)
g2 = ps.register_group("points")
ps.set_parent_group(g2, g)
for i in range(3):
    points = np.random.rand(100, 3)
    ps_cloud = ps.register_point_cloud("my points {}".format(i), points)
    ps.set_parent_group(ps_cloud, g2)
g3 = ps.register_group("surfaces")
ps.set_parent_group(g3, g)
for i in range(3):
    vertices = np.random.rand(100, 3)
    faces = np.random.randint(0, 100, size=(250,3))
    ps_mesh = ps.register_surface_mesh("my mesh {}".format(i), vertices, faces)
    ps.set_parent_group(ps_mesh, g3)
g4 = ps.register_group("volumes")
ps.set_parent_group(g4, g)
for i in range(3):
    verts = np.array([
        [0, 0, 0],
        [1, 0, 0],
        [1, 1, 0],
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 1],
        [1, 1, 1],
        [0, 1, 1],
        [1, 1, 1.5]
    ])
    cells = np.array([
    [0, 1, 2, 3, 4, 5, 6, 7],
    [7, 5, 6, 8, -1, -1, -1, -1],
    ])
    ps_vol = ps.register_volume_mesh("my_volume {}".format(i), verts, mixed_cells=cells)
    ps.set_parent_group(ps_vol, g4)
ps.show()
