import polyscope_bindings as psb

from polyscope.core import glm3, radians, degrees
from polyscope.structure import Structure
from polyscope.common import process_color_args, process_scalar_args, process_vector_args

from math import tan, atan

import numpy as np

'''
def canonicalize_camera_params(root, look_dir, up_dir, view_mat, fov_vert_deg, fov_horz_deg, aspect):

    # validate combinations of args
   
    # check for a valid combination of extrinsics
    ext_as_vec = (root is not None) or (look_dir is not None) or (up_dir is not None)
    if ext_as_vec:
        if (root is None) or (look_dir is None) or (up_dir is None):
            raise ValueError("if any of 'root', 'look_dir', 'up_dir' is specified, they all must be") 
        if view_mat is not None:
            raise ValueError("if any of 'root', 'look_dir', 'up_dir' is specified, 'view_mat' cannot be specified") 
        
        # convert to glm vectors
        root = glm3(root)
        look_dir = glm3(look_dir)
        up_dir = glm3(up_dir)

        ext_vals = {
                'style' : 'vec',
                'root' : root,
                'look_dir' : look_dir,
                'up_dir' : up_dir,
            }

    ext_as_mat = view_mat is not None
    if ext_as_mat:
        view_mat = np.array(view_mat)
        
        ext_vals = {
                'style' : 'mat',
                'view_mat' : view_mat,
            }


    # check for a valid combination of intrinsics
    # aspect is defined as "width over height"
    if fov_vert_deg is not None:
        if aspect is not None:
            pass
        elif fov_horz_deg is not None:
            aspect = tan(0.5*radians(float(fov_horz_deg))) / tan(0.5*radians(float(fov_vert_deg)))
        else:
            raise ValueError("must pass one of 'fov_horz_deg' or 'aspect'")

    elif fov_horz_deg is not None:
        if aspect is not None:
            fov_vert_deg = degrees(2. * atan(tan(0.5*radians(float(fov_horz_deg))) / aspect))
        else:
            raise ValueError("must pass one of 'fov_horz_deg' or 'aspect'")
    else:
        raise ValueError("must pass one of 'fov_vert_deg' or 'fov_horz_deg'")
            
    int_vals = {
        'fov_vert_deg' : float(fov_vert_deg),
        'aspect' : float(aspect)
        }


    return ext_vals, int_vals
'''



class CameraView(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_camera_view instead
    def __init__(self, name=None, camera_parameters=None, instance=None):
        
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance
            self.bound_instance = psb.register_camera_view_vec(name, camera_parameters)


    # Update
    def update_camera_parameters(self, camera_parameters):
        self.bound_instance.update_camera_parameters(camera_parameters)


    ## Camera things

    def set_view_to_this_camera(self, with_flight=False):
        self.bound_cloud.set_view_to_this_camera(with_flight)
    
    def get_parameters(self):
        return CameraParameters(instance=self.bound_cloud.get_parameters())

    ## Options
    
    # Widget color
    def set_widget_color(self, val):
        self.bound_instance.set_widget_color(glm3(val))
    def get_widget_color(self):
        return self.bound_instance.get_widget_color().as_tuple()
    
    # Widget thickness
    def set_widget_thickness(self, val):
        self.bound_instance.set_widget_thickness(float(val))
    def get_widget_thickness(self):
        return self.bound_instance.get_widget_thickness()
    
    # Widget focal length
    def set_widget_focal_length(self, val):
        self.bound_instance.set_widget_focal_length(float(val))
    def get_widget_focal_length(self):
        return self.bound_instance.get_widget_focal_length()
    

    ## Quantities
       

def register_camera_view(name, camera_parameters,
                         enabled=None, transparency=None,
                         widget_color=None, widget_thickness=None, widget_focal_length=None,
                         ):
    """Register a new camera view"""
    if not psb.isInitialized():
        raise RuntimeError("Polyscope has not been initialized")

    p = CameraView(name, camera_parameters)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if transparency is not None:
        p.set_transparency(transparency)
    if widget_color is not None:
        p.set_widget_color(widget_color)
    if widget_thickness is not None:
        p.set_widget_thickness(widget_thickness)
    if widget_focal_length is not None:
        p.set_widget_focal_length(widget_focal_length)

    return p

def remove_camera_view(name, error_if_absent=True):
    """Remove a camera view by name"""
    psb.remove_camera_view(name, error_if_absent)

def get_camera_view(name):
    """Get camera view by name"""
    if not has_camera_view(name):
        raise ValueError("no camera view with name " + str(name))

    raw_instance = psb.get_camera_view(name)

    # Wrap the instance
    return CameraView(instance=raw_instance)

def has_camera_view(name):
    """Check if a camera view exists by name"""
    return psb.has_camera_view(name)
    
