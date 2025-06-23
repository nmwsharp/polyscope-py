import polyscope_bindings as psb

import numpy as np

from polyscope.device_interop import CUDAOpenGLMappedAttributeBuffer, CUDAOpenGLMappedTextureBuffer

# A cache of mapped buffers
_mapped_buffer_cache_CUDAOpenGL = {} # maps uniqueID --> buffer object

class ManagedBuffer:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constructor, use structure.get_buffer("name") or another like it
    def __init__(self, instance, buffer_type):

        self.uniqueID = None # gets overwritten below, setting early so it is defined if __del__ gets called

        self.bound_buffer = instance
        self.buffer_type = buffer_type
        self.device_buffer_type = self.bound_buffer.get_device_buffer_type()
        
        self.buffer_weak_ref = self.bound_buffer.get_generic_weak_handle()
        self.uniqueID = self.buffer_weak_ref.get_unique_ID()
    
    def __del__(self):
        # NOTE: this means that if the user writes the common ps.get_buffer("name").update_data_from_device(arr), then
        # we are re-registering the buffer every time, which could be slow, and is unintuitive.
        self.release_mapped_buffer_CUDAOpenGL()
       
    def check_ref_still_valid(self):
        if not self.buffer_weak_ref.is_valid():
            raise ValueError("[polyscope] lifetime of underlying buffer has expired")
    
    def size(self):
        self.check_ref_still_valid()

        return self.bound_buffer.size()
    
    def get_texture_size(self):
        self.check_ref_still_valid()

        return self.bound_buffer.get_texture_size()
    
    def has_data(self):
        self.check_ref_still_valid()

        return self.bound_buffer.has_data()
    
    def summary_string(self):
        self.check_ref_still_valid()
        return self.bound_buffer.summary_string()
    
    def get_value(self, ind, indY=None, indZ=None):
        self.check_ref_still_valid()

        # warning: expensive, don't call it in a loop
        if indZ is not None:
            return self.bound_buffer.get_value(ind, indY, indZ)
        if indY is not None:
            return self.bound_buffer.get_value(ind, indY)
        return self.bound_buffer.get_value(ind)

    def update_data(self, new_vals):
        self.check_ref_still_valid()

        new_vals = new_vals.reshape((self.size(),-1))

        self.update_data_from_host(new_vals)

    def update_data_from_host(self, new_vals):
        self.check_ref_still_valid()

        # TODO: this actually calls functions with different signatures based on
        # what the underlying kind of buffer is. We should probably document it
        # better or provide some error checking at the Python level.
        # NOTE: this method calls mark_host_buffer_updated() internally, so there is no need to call it again
        self.bound_buffer.update_data(new_vals)
    
    def update_data_from_device(self, new_vals_device):
        self.check_ref_still_valid()

        mapped_buffer = self.get_mapped_buffer_CUDAOpenGL()

        if self.device_buffer_type == psb.DeviceBufferType.attribute:

            mapped_buffer.set_data_from_array(new_vals_device, self.bound_buffer.get_device_buffer_size_in_bytes())

            self.bound_buffer.mark_render_attribute_buffer_updated()

        else: # texture

            mapped_buffer.set_data_from_array(new_vals_device, self.bound_buffer.get_texture_size(),
                                              self.bound_buffer.get_device_buffer_element_size_in_bytes())

            self.bound_buffer.mark_render_texture_buffer_updated()

    def get_mapped_buffer_CUDAOpenGL(self):
        self.check_ref_still_valid()

        if self.uniqueID not in _mapped_buffer_cache_CUDAOpenGL:
            # create a new one
            if self.device_buffer_type == psb.DeviceBufferType.attribute:
                nativeID = self.bound_buffer.get_native_render_attribute_buffer_ID()

                _mapped_buffer_cache_CUDAOpenGL[self.uniqueID] = \
                    CUDAOpenGLMappedAttributeBuffer(
                            nativeID,
                            self.device_buffer_type
                    )

            else: # texture
                nativeID = self.bound_buffer.get_native_render_texture_buffer_ID()
                
                _mapped_buffer_cache_CUDAOpenGL[self.uniqueID] = \
                    CUDAOpenGLMappedTextureBuffer(
                            nativeID,
                            self.device_buffer_type
                    )

            
        return _mapped_buffer_cache_CUDAOpenGL[self.uniqueID]
    
    def release_mapped_buffer_CUDAOpenGL(self):
        if self.uniqueID in _mapped_buffer_cache_CUDAOpenGL:
            _mapped_buffer_cache_CUDAOpenGL[self.uniqueID].cleanup()
            del _mapped_buffer_cache_CUDAOpenGL[self.uniqueID]
    
    def get_texture_native_id(self):
        if self.device_buffer_type == psb.DeviceBufferType.attribute:
            raise ValueError("buffer is not a texture (perhaps try the 'attribute' variant?)")

        return self.bound_buffer.get_native_render_texture_buffer_ID()
    
    def get_attribute_native_id(self):
        if self.device_buffer_type != psb.DeviceBufferType.attribute:
            raise ValueError("buffer is not an attribute (perhaps try the 'texture' variant?)")

        return self.bound_buffer.get_native_render_attribute_buffer_ID()


    def mark_device_buffer_updated(self):

        if self.device_buffer_type == psb.DeviceBufferType.attribute:
            self.bound_buffer.mark_render_attribute_buffer_updated()
        else: # texture
            self.bound_buffer.mark_render_texture_buffer_updated()
