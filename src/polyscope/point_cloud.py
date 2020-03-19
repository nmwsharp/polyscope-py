import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3

class PointCloud:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_point_cloud instead
    def __init__(self, name=None, points=None, instance=None):

        if instance is not None:
            # Wrap an existing instance
            self.bound_cloud = instance

        else:
            # Create a new instance

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
        
        
    def n_points(self):
        return self.bound_cloud.n_points()

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
    def set_radius(self, rad, relative=True):
        self.bound_cloud.set_radius(rad, relative)
    def get_radius(self):
        return self.bound_cloud.get_radius()
    
    # Point color
    def set_color(self, val):
        self.bound_cloud.set_color(glm3(val))
    def get_color(self):
        return self.bound_cloud.get_color().as_tuple()
    
    # Point material
    def set_material(self, mat):
        self.bound_cloud.set_material(mat)
    def get_material(self):
        return self.bound_cloud.get_material()


    ## Quantities
       
    # Scalar
    def add_scalar_quantity(self, name, values, enabled=None, datatype="standard", vminmax=None, cmap=None):
        if len(values.shape) != 1 or values.shape[0] != self.n_points(): raise ValueError("'values' should be a length-N array")
            
        q = self.bound_cloud.add_scalar_quantity(name, values, str_to_datatype(datatype))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if vminmax is not None:
            q.set_map_range(vminmax)
        if cmap is not None:
            q.set_color_map(cmap)
    
    
    # Color
    def add_color_quantity(self, name, values, enabled=None):
        if len(values.shape) != 2 or values.shape[0] != self.n_points() or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
            
        q = self.bound_cloud.add_color_quantity(name, values)

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
    
    
    # Vector
    def add_vector_quantity(self, name, values, enabled=None, vectortype="standard", length=None, radius=None, color=None):
        if len(values.shape) != 2 or values.shape[0] != self.n_points() or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        if values.shape[1] == 2:
            q = self.bound_cloud.add_vector_quantity2D(name, values, str_to_vectortype(vectortype))
        elif values.shape[1] == 3:
            q = self.bound_cloud.add_vector_quantity(name, values, str_to_vectortype(vectortype))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if length is not None:
            q.set_length(length, True)
        if radius is not None:
            q.set_radius(radius, True)
        if color is not None:
            q.set_color(glm3(color))


def register_point_cloud(name, points, enabled=None, radius=None, color=None, material=None):
    """Register a new point cloud"""

    p = PointCloud(name, points)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if radius is not None:
        p.set_radius(radius)
    if color is not None:
        p.set_color(color)
    if material is not None:
        p.set_material(material)

    return p

def remove_point_cloud(name, error_if_absent=True):
    """Remove a point cloud by name"""
    psb.remove_point_cloud(name, error_if_absent)

def get_point_cloud(name):
    """Get point cloud by name"""
    if not has_point_cloud(name):
        raise ValueError("no point cloud with name " + str(name))

    raw_cloud = psb.get_point_cloud(name)

    # Wrap the instance
    return PointCloud(instance=raw_cloud)

def has_point_cloud(name):
    """Check if a point cloud exists by name"""
    return psb.has_point_cloud(name)
    
