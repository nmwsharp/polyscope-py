import polyscope_bindings as psb

import numpy as np


class ManagedBuffer:
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constructor, structure.get_buffer("name") or something like it
    def __init__(self, instance, buffer_type):

        # Wrap an existing instance
        self.bound_buffer = instance
        self.buffer_type = buffer_type
    
    def size(self):
        return self.bound_buffer.size()
    
    def get_texture_size(self):
        return self.bound_buffer.get_texture_size()
    
    def has_data(self):
        return self.bound_buffer.has_data()
    
    def summary_string(self):
        return self.bound_buffer.summary_string()
    
    def get_value(self, ind, indY=None, indZ=None):
        # warning: expensive, don't call it in a loop
        if indZ is not None:
            return self.bound_buffer.get_value(ind, indY, indZ)
        if indY is not None:
            return self.bound_buffer.get_value(ind, indY)
        return self.bound_buffer.get_value(ind)

    
    def update_data(self, new_vals):
        # TODO: this actually calls functions with different signatures based on
        # what the underlying kind of buffer is. We should probably document it
        # better or provide some error checking at the Python level.
        # NOTE: this method calss mark_host_buffer_updated() internally, so there is no need to call it again
        self.bound_buffer.update_data(new_vals);
    
    def mark_host_buffer_updated(self):
        # note: update_data() calls this internally, so currently there is no need to call this
        return self.bound_buffer.mark_host_buffer_updated()
    
    def mark_device_buffer_updated(self):
        return self.bound_buffer.mark_device_buffer_updated()
