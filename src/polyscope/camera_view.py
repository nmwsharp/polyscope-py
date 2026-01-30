import polyscope_bindings as psb

from polyscope.core import glm3, CameraParameters
from polyscope.structure import Structure

import numpy as np
from numpy.typing import ArrayLike

class CameraView(Structure):
    bound_instance: psb.CameraView

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_camera_view instead
    def __init__(self, 
                 name: str | None = None, 
                 camera_parameters: CameraParameters | None = None, 
                 instance: psb.CameraView | None = None) -> None:
        
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            assert name is not None
            assert camera_parameters is not None

            # Create a new instance
            self.bound_instance = psb.register_camera_view(name, camera_parameters.instance)


    # Update
    def update_camera_parameters(self, camera_parameters : CameraParameters) -> None:
        self.bound_instance.update_camera_parameters(camera_parameters.instance)

    ## Camera things

    def set_view_to_this_camera(self, with_flight: bool = False) -> None:
        self.bound_instance.set_view_to_this_camera(with_flight)
    
    def get_camera_parameters(self) -> CameraParameters:
        return CameraParameters(instance=self.bound_instance.get_camera_parameters())

    ## Options
    
    # Widget color
    def set_widget_color(self, val: ArrayLike) -> None:
        self.bound_instance.set_widget_color(glm3(val))
    def get_widget_color(self) -> tuple[float, float, float]:
        return self.bound_instance.get_widget_color().as_tuple()
    
    # Widget thickness
    def set_widget_thickness(self, val : float) -> None:
        self.bound_instance.set_widget_thickness(float(val))
    def get_widget_thickness(self) -> float:
        return self.bound_instance.get_widget_thickness()
    
    # Widget focal length
    def set_widget_focal_length(self, val: float, relative: bool = True) -> None:
        self.bound_instance.set_widget_focal_length(float(val), relative)
    def get_widget_focal_length(self) -> float:
        return self.bound_instance.get_widget_focal_length()
    

    ## Quantities
       

def register_camera_view(name, 
                         camera_parameters: CameraParameters,
                         enabled: bool | None = None, 
                         transparency: float | None = None,
                         widget_color: ArrayLike | None = None, 
                         widget_thickness: float | None = None, 
                         widget_focal_length: float | None = None,
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

def remove_camera_view(name: str, error_if_absent: bool = True) -> None:
    """Remove a camera view by name"""
    psb.remove_camera_view(name, error_if_absent)

def get_camera_view(name: str) -> CameraView:
    """Get camera view by name"""
    if not has_camera_view(name):
        raise ValueError("no camera view with name " + str(name))

    raw_instance = psb.get_camera_view(name)

    # Wrap the instance
    return CameraView(instance=raw_instance)

def has_camera_view(name: str) -> bool:
    """Check if a camera view exists by name"""
    return psb.has_camera_view(name)
    
