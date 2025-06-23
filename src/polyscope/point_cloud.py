import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3, str_to_point_render_mode, point_render_mode_to_str, str_to_param_coords_type
from polyscope.structure import Structure
from polyscope.common import process_quantity_args, process_scalar_args, process_color_args, process_vector_args, process_parameterization_args, check_all_args_processed

class PointCloud(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_point_cloud instead
    def __init__(self, name=None, points=None, instance=None):

        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance

            self.check_shape(points)

            if points.shape[1] == 3:
                self.bound_instance = psb.register_point_cloud(name, points)
            elif points.shape[1] == 2:
                self.bound_instance = psb.register_point_cloud2D(name, points)
            else:
                raise ValueError("bad point cloud shape")


    def check_shape(self, points):
        # Helper to validate arrays

        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("Point cloud positions should have shape (N,3); shape is " + str(points.shape))
        
    def n_points(self):
        return self.bound_instance.n_points()

    # Point render mode
    def set_point_render_mode(self, val):
        self.bound_instance.set_point_render_mode(str_to_point_render_mode(val))
    def get_point_render_mode(self):
        return point_render_mode_to_str(self.bound_instance.get_point_render_mode())


    # Update
    def update_point_positions(self, points):
        self.check_shape(points)
        
        if points.shape[1] == 3:
            self.bound_instance.update_point_positions(points)
        elif points.shape[1] == 2:
            self.bound_instance.update_point_positions2D(points)
        else:
            raise ValueError("bad point cloud shape")

    # Custom radius quantity
    def set_point_radius_quantity(self, quantity_name, autoscale=True):
        self.bound_instance.set_point_radius_quantity(quantity_name, autoscale)
    def clear_point_radius_quantity(self):
        self.bound_instance.clear_point_radius_quantity()
   
    # Custom transparency quantity
    def set_transparency_quantity(self, quantity_name):
        self.bound_instance.set_transparency_quantity(quantity_name)
    def clear_transparency_quantity(self):
        self.bound_instance.clear_transparency_quantity()

    ## Options
   
    # Point radius
    def set_radius(self, rad, relative=True):
        self.bound_instance.set_radius(rad, relative)
    def get_radius(self):
        return self.bound_instance.get_radius()
    
    # Point color
    def set_color(self, val):
        self.bound_instance.set_color(glm3(val))
    def get_color(self):
        return self.bound_instance.get_color().as_tuple()
    
    # Point material
    def set_material(self, mat):
        self.bound_instance.set_material(mat)
    def get_material(self):
        return self.bound_instance.get_material()

    def append_pick_data(self, pick_result):
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["index"] = struct_result.index

    ## Quantities
       
    # Scalar
    def add_scalar_quantity(self, name, values, datatype="standard", **scalar_args):
        if len(values.shape) != 1 or values.shape[0] != self.n_points(): raise ValueError("'values' should be a length-N array")
            
        q = self.bound_instance.add_scalar_quantity(name, values, str_to_datatype(datatype))

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)
    
    
    # Color
    def add_color_quantity(self, name, values, **color_args):
        if len(values.shape) != 2 or values.shape[0] != self.n_points() or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
            
        q = self.bound_instance.add_color_quantity(name, values)
        
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, color_args)
        process_color_args(self, q, color_args)
        check_all_args_processed(self, q, color_args)
    
    
    # Vector
    def add_vector_quantity(self, name, values, vectortype="standard", **vector_args):
        if len(values.shape) != 2 or values.shape[0] != self.n_points() or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        if values.shape[1] == 2:
            q = self.bound_instance.add_vector_quantity2D(name, values, str_to_vectortype(vectortype))
        elif values.shape[1] == 3:
            q = self.bound_instance.add_vector_quantity(name, values, str_to_vectortype(vectortype))
        
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)

    # Parameterization
    def add_parameterization_quantity(self, name, values, coords_type='unit', **parameterization_args):

        if len(values.shape) != 2 or values.shape[0] != self.n_points() or values.shape[1] != 2: raise ValueError("'values' should be an Nx2 array")

        # parse the coords type in to an enum
        coords_type_enum = str_to_param_coords_type(coords_type)

        q = self.bound_instance.add_parameterization_quantity(name, values, coords_type_enum)
            
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, parameterization_args)
        process_parameterization_args(self, q, parameterization_args, is_surface=False)
        check_all_args_processed(self, q, parameterization_args)


def register_point_cloud(name, points, enabled=None, radius=None, point_render_mode=None, color=None, material=None, transparency=None):
    """Register a new point cloud"""
    if not psb.is_initialized():
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
    
