import polyscope_bindings as psb

from polyscope.core import glm3, CameraParameters
from polyscope.structure import Structure

import numpy as np

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
            self.bound_instance = psb.register_camera_view(name, camera_parameters.instance)


    # Update
    def update_camera_parameters(self, camera_parameters):
        self.bound_instance.update_camera_parameters(camera_parameters.instance)


    ## Camera things

    def set_view_to_this_camera(self, with_flight=False):
        self.bound_instance.set_view_to_this_camera(with_flight)
    
    def get_camera_parameters(self):
        return CameraParameters(instance=self.bound_instance.get_camera_parameters())

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
    def set_widget_focal_length(self, val, relative=True):
        self.bound_instance.set_widget_focal_length(float(val), relative)
    def get_widget_focal_length(self):
        return self.bound_instance.get_widget_focal_length()
    

    ## Quantities
       

def register_camera_view(name, camera_parameters,
                         enabled=None, transparency=None,
                         widget_color=None, widget_thickness=None, widget_focal_length=None,
                         ):
    """Register a new camera view"""
    if not psb.is_initialized():
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
    
