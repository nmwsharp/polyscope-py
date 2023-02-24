import polyscope as ps
import numpy as np

ps.init()

# test that UI doesn't show groups until they're added
ps.show()

# test group creation, hierarchy and structure assignment
g = ps.register_group("pretty shapes")
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
    ps_vol = ps.register_volume_mesh("my volume {}".format(i), verts, mixed_cells=cells)
    ps.set_parent_group(ps_vol, g4)

# test setting a group to enabled/disabled
ps.set_group_enabled(g4, False)

# test UI
ps.show()

# test group removal
ps.remove_group(g4)

ps.show()

# test subroup removal
gtop = ps.register_group("top")
gmid = ps.register_group("mid")
gbot = ps.register_group("bot")
ps.set_parent_group(gmid, gtop)
ps.set_parent_group(gbot, gmid)
ps.remove_group(gmid)

ps.show()

# Test using references to deleted groups
ps.set_parent_group(g4, g) # predictably causes an error

# Test (misguided) attempt to create a loop
ga = ps.register_group("group_a")
gb = ps.register_group("group_b")
ps.set_parent_group(ga, gb)
ps.set_parent_group(gb, ga) # creates a loop, should cause an error

ps.show()



