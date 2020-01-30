import polyscope_bindings as psb


class PointCloud:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    def __init__(self):
        self.bound_cloud = psb.register_point_cloud(name, points)

    def remove(self):
        self.bound_cloud.remove()

    def set_enabled(self, val=True):
        self.bound_cloud.enabled(val)
        

def register_point_cloud(name, points,
        enabled=None):
    """Register a new point cloud"""

    p = psb.register_point_cloud(name, points)

    # if(m.shade_smooth is not None):
        # m.shade_smooth


    # == Apply options

    if enabled is not None:
        p.set_enabled(enabled)

    return p

def remove_point_cloud(name, error_if_absent=True):
    """Remove a point cloud by name"""
    psb.remove_point_cloud(name, error_if_absent)


def has_point_cloud(name):
    """Check if a point cloud exists name"""
    return psb.has_point_cloud(name)
    
