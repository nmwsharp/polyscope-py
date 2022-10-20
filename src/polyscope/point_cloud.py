import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3, str_to_point_render_mode, point_render_mode_to_str

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
    
    # Transparency
    def set_transparency(self, val):
        self.bound_cloud.set_transparency(val)
    def get_transparency(self):
        return self.bound_cloud.get_transparency()
   
    # Transformation things
    def center_bounding_box(self):
        self.bound_cloud.center_bounding_box()
    def rescale_to_unit(self):
        self.bound_cloud.rescale_to_unit()
    def reset_transform(self):
        self.bound_cloud.reset_transform()
    def set_transform(self, new_mat4x4):
        self.bound_cloud.set_transform(new_mat4x4)
    def set_position(self, new_vec3):
        self.bound_cloud.set_position(new_vec3)
    def translate(self, trans_vec3):
        self.bound_cloud.translate(trans_vec3)
    def get_transform(self):
        return self.bound_cloud.get_transform()
    def get_position(self):
        return self.bound_cloud.get_position()
    
    # Point render mode
    def set_point_render_mode(self, val):
        self.bound_cloud.set_point_render_mode(str_to_point_render_mode(val))
    def get_point_render_mode(self):
        return point_render_mode_to_str(self.bound_cloud.get_point_render_mode())

    # Slice planes
    def set_cull_whole_elements(self, val):
        self.bound_cloud.set_cull_whole_elements(val)
    def get_cull_whole_elements(self):
        return self.bound_cloud.get_cull_whole_elements()
    def set_ignore_slice_plane(self, plane, val):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            self.bound_cloud.set_ignore_slice_plane(plane, val)
        else:
            self.bound_cloud.set_ignore_slice_plane(plane.get_name(), val)
    def get_ignore_slice_plane(self, plane):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            return self.bound_cloud.get_ignore_slice_plane(plane)
        else:
            return self.bound_cloud.get_ignore_slice_plane(plane.get_name())

    # Update
    def update_point_positions(self, points):
        self.check_shape(points)
        
        if points.shape[1] == 3:
            self.bound_cloud.update_point_positions(points)
        elif points.shape[1] == 2:
            self.bound_cloud.update_point_positions2D(points)
        else:
            raise ValueError("bad point cloud shape")

    def set_point_radius_quantity(self, quantity_name, autoscale=True):
        self.bound_cloud.set_point_radius_quantity(quantity_name, autoscale)
    
    def clear_point_radius_quantity(self):
        self.bound_cloud.clear_point_radius_quantity()

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


def register_point_cloud(name, points, enabled=None, radius=None, point_render_mode=None, color=None, material=None, transparency=None):
    """Register a new point cloud"""
    if not psb.isInitialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = PointCloud(name, points)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if radius is not None:
        p.set_radius(radius)
    if point_render_mode is not None:
        p.set_point_render_mode(point_render_mode)
    if color is not None:
        p.set_color(color)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

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
    
