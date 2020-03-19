import polyscope_bindings as psb

from polyscope.core import str_to_datatype

class PointCloud:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    def __init__(self, name, points):
        self.check_shape(points)

        if points.shape[1] == 3:
            self.bound_cloud = psb.register_point_cloud(name, points)
        elif points.shape[1] == 2:
            self.bound_cloud = psb.register_point_cloud2D(name, points)
        else:
            raise ValueError("bad point cloud shape")

    def check_shape(self, points):
        # Helper to validate arrays

        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("Point cloud positions should have shape (N,3); shape is " + str(points.shape))

    ## Structure management
    
    def remove(self):
        '''Remove the structure itself'''
        self.bound_cloud.remove()
    def remove_all_quantities(self):
        '''Remove all quantities on the structure'''
        self.bound_cloud.remove_all_quantities()
    def remove_quantity(self, name):
        '''Remove a single quantity on the structure'''
        self.bound_cloud.remove_quantity(name)

    # Enable/disable
    def set_enabled(self, val=True):
        self.bound_cloud.set_enabled(val)
    def is_enabled(self):
        return self.bound_cloud.is_enabled()

    # Update
    def update_point_positions(self, points):
        self.check_shape(points)
        
        if points.shape[1] == 3:
            self.bound_cloud.update_point_positions(points)
        elif points.shape[1] == 2:
            self.bound_cloud.update_point_positions2D(points)
        else:
            raise ValueError("bad point cloud shape")

    ## Options
   
    # Point radius
    def set_point_radius(self, rad, relative=True):
        self.bound_cloud.set_point_radius(rad, relative)
    def get_point_radius(self):
        return self.bound_cloud.get_point_radius()
    
    # Point color
    def set_point_color(self, val):
        self.bound_cloud.set_point_color(psb.glm_vec3(val[0], val[1], val[2]))
    def get_point_color(self):
        return self.bound_cloud.get_point_color().as_tuple()
    
    # Point material
    def set_material(self, mat):
        self.bound_cloud.set_material(mat)
    def get_material(self):
        return self.bound_cloud.get_material()


    ## Quantities
       
    # Scalar
    def add_scalar_quantity(self, name, values, enabled=None, datatype="standard", vminmax=None, cmap=None):
        if len(values.shape) != 1: raise ValueError("'values' should be a 1D array")
            
        q = self.bound_cloud.add_scalar_quantity(name, values, str_to_datatype(datatype))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if vminmax is not None:
            q.set_map_range(vminmax)
        if cmap is not None:
            q.set_color_map(cmap)



def register_point_cloud(name, points,
        enabled=None, point_radius=None, point_color=None):
    """Register a new point cloud"""

    p = PointCloud(name, points)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if point_radius is not None:
        p.set_point_radius(point_radius)
    if point_color is not None:
        p.set_point_color(point_color)

    return p

def remove_point_cloud(name, error_if_absent=True):
    """Remove a point cloud by name"""
    psb.remove_point_cloud(name, error_if_absent)


def has_point_cloud(name):
    """Check if a point cloud exists name"""
    return psb.has_point_cloud(name)
    
