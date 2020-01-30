import polyscope_bindings as psb


class SurfaceMesh:

    # This class wraps a _reference_ to the underlying mesh object, whose lifetime is managed by Polyscope

    def __init__(self):

        self.bound_mesh = psb.register_surface_mesh(name, verts, faces)


    def set_enabled(self, val=True):
        self.bound_mesh.enabled(val)
        


def register_surface_mesh(name, verts, faces, 
        enabled=None, shade_smooth=None, surface_color=None, edge_color=None, show_edges=None):
    m = psb.register_surface_mesh(name, verts, faces)

    # if(m.shade_smooth is not None):
        # m.shade_smooth


    # == Apply options

    if enabled is not None:
        m.set_enabled(enabled)

    return m
