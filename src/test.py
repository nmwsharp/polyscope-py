import polyscope as ps
import numpy as np
ps.init()
for i in range(3):
    nodes = np.random.rand(100, 3)
    edges = np.random.randint(0, 100, size=(250,2))
    ps_net = ps.register_curve_network("my network {}".format(i), nodes, edges)
g = ps.register_group("my_group")
g1 = ps.register_group("child_group1")
ps.set_parent_group(g1, g)
ps.set_parent_group(ps_net, g1)
ps.show()
