import polyscope_bindings as psb

import os

import numpy as np

from polyscope.core import get_render_engine_backend_name


# Dependencies which are needed for interop but otherwise optional for polyscope
#
# Try both of these imports, but fail silently if they don't work (we will try 
# again and print an informative error below only if a relevant function is called)
try: 
    import cuda
    from cuda import cudart
    import cupy
except ImportError: 
    _has_cuda_libs = False
else:
    _has_cuda_libs = True

# This seems absurd! These constants are needed for cuda.cudart calls, but there is apparently no canonical way to get them without introducing an additional dependency.
# See discussion https://discourse.panda3d.org/t/allowing-torch-tensorflow-to-directly-access-rendered-image-in-gpu/29119/3
# As a workaround, we hardcord their constant values, fetched from https://cvs.khronos.org/svn/repos/ogl/trunk/doc/registry/public/api/GL/glcorearb.h
_CONSTANT_GL_TEXTURE_2D = int('0DE1',16)
_CONSTANT_GL_TEXTURE_3D = int('806F',16)

## Experimental things

def check_device_module_availibility():

    supported_backends = ["openGL3_glfw"]
    if get_render_engine_backend_name() not in supported_backends:
        raise ValueError(f"This Polyscope functionality is not supported by the current rendering backend ({get_render_engine_backend_name()}. Supported backends: {','.join(supported_backends)}.")

    if not _has_cuda_libs:
        raise ImportError('This Polyscope functionality requires cuda bindings to be installed. Please install the packages `cuda` and `cupy`. https://nvidia.github.io/cuda-python/ & https://cupy.dev/')


# TODO is it possible to implement this without relying on exceptions?
'''
def is_dlpack(obj):
    return hasattr(obj, '__dlpack__') and hasattr(obj, '__dlpack_device__')
'''

def is_cuda_array_interface(obj):
    return hasattr(obj, '__cuda_array_interface__')


def format_cudart_err(err):
    return (
        f"{cudart.cudaGetErrorName(err)[1].decode('utf-8')}({int(err)}): "
        f"{cudart.cudaGetErrorString(err)[1].decode('utf-8')}"
    )


def check_cudart_err(args):
    if isinstance(args, tuple):
        assert len(args) >= 1
        err = args[0]
        if len(args) == 1:
            ret = None
        elif len(args) == 2:
            ret = args[1]
        else:
            ret = args[1:]
    else:
        err = args
        ret = None

    assert isinstance(err, cudart.cudaError_t), type(err)
    if err != cudart.cudaError_t.cudaSuccess:
        raise RuntimeError(format_cudart_err(err))

    return ret

class CUDAOpenGLMappedAttributeBuffer:

    # Roughly based on this, see for more goodies: https://gist.github.com/keckj/e37d312128eac8c5fca790ce1e7fc437

    def __init__(self, gl_attribute_native_id, buffer_type):
        check_device_module_availibility()

        self.gl_attribute_native_id = gl_attribute_native_id
        self.buffer_type = buffer_type
        self.resource_handle = None
        self.cuda_buffer_ptr = None
        self.cuda_buffer_size = -1


        # Sanity checks
        if self.buffer_type != psb.DeviceBufferType.attribute:
            raise ValueError("device buffer type should be attribute")

        # Register the buffer 
        self.resource_handle = check_cudart_err(
            cudart.cudaGraphicsGLRegisterBuffer(
                self.gl_attribute_native_id,
                # NOTE: setting write-only flag
                cudart.cudaGraphicsRegisterFlags.cudaGraphicsRegisterFlagsWriteDiscard
                # cudart.cudaGraphicsRegisterFlags.cudaGraphicsRegisterFlagsNone
            )
        )
        
    def __del__(self):
        self.unregister()

    def unregister(self):
        self.unmap()
        self.resource_handle = check_cudart_err(
            cudart.cudaGraphicsUnregisterResource(self.resource_handle))

    def map(self):
        """
        Returns a cupy memory pointer to the buffer
        """

        if self.cuda_buffer_ptr is not None:
            return 

        check_cudart_err(cudart.cudaGraphicsMapResources(1, self.resource_handle, None))

        ptr, size = check_cudart_err(cudart.cudaGraphicsResourceGetMappedPointer(self.resource_handle))

        self.cuda_buffer_ptr = cupy.cuda.MemoryPointer(cupy.cuda.UnownedMemory(ptr, size, self), 0)
        self.cuda_buffer_size = size


    def unmap(self):
        if self.cuda_buffer_ptr is None:
            return

        check_cudart_err(cudart.cudaGraphicsUnmapResources(1, self.resource_handle, None))

        self.cuda_buffer_ptr = None
        self.cuda_buffer_size = -1
    
    def set_data_from_array(self, arr, expected_shape=None, expected_dtype=None):
        
        self.map()
      
        cupy_arr = self.get_array_from_unknown_data(arr)
        
        # do some shape & type checks
        if expected_dtype is not None and cupy_arr.dtype != expected_dtype:
            raise ValueError(f"dlpack array has wrong dtype, expected {expected_dtype} but got {cupy_arr.dtype}")

        if expected_shape is not None and cupy_arr.shape != expected_shape:
            raise ValueError(f"dlpack array has wrong shape, expected {expected_shape} but got {cupy_arr.shape}")

        if cupy_arr.nbytes != self.cuda_buffer_size: 
            # if cupy_arr has the right size/dtype, it should have exactly the same 
            # number of bytes as the destination. This is just lazily saving us 
            # from repeating the math, and also directly validates the copy we 
            # are about to do below.
            raise ValueError(f"Mapped buffer write has wrong size, expected {cupy_arr.nbytes} bytes but got {self.cuda_buffer_size} bytes. Could it be the wrong size/shape or wrong dtype?")


        # perform the actualy copy
        self.cuda_buffer_ptr.copy_from_device(cupy_arr.data, self.cuda_buffer_size)

        self.unmap() 


    def get_array_from_unknown_data(self, arr):
        
        # Dispatch to one of the kinds of objects that we can read from

        # __cuda_array_interface__
        if is_cuda_array_interface(arr):
            return cupy.ascontiguousarray(cupy.asarray(arr))

        # __dlpack__
        # (I can't figure out any way to check this except try-catch)
        try:
            return cupy.ascontiguousarray(cupy.from_dlpack(arr))
        except ValueError:
            pass 
       
        raise ValueError("Cannot read from device data object. Must be a _dlpack_ array or implement the __cuda_array_interface__.")


class CUDAOpenGLMappedTextureBuffer:


    def __init__(self, gl_attribute_native_id, buffer_type):
        check_device_module_availibility()

        self.gl_attribute_native_id = gl_attribute_native_id
        self.buffer_type = buffer_type
        self.resource_handle = None
        self.cuda_buffer_array = None # NOTE: 'array' has a special cuda meaning here relating to texture memory

        # Register the buffer 

        if self.buffer_type == psb.DeviceBufferType.attribute:
            raise ValueError("type should be texture*")
        
        elif self.buffer_type == psb.DeviceBufferType.texture1d:
            raise ValueError("1d texture writes are not supported")
            # apparently not supported (?!) 
            # see cudaGraphicsGLRegisterImage in these docs https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__OPENGL.html

        elif self.buffer_type == psb.DeviceBufferType.texture2d:

            self.resource_handle = check_cudart_err(
                cudart.cudaGraphicsGLRegisterImage(
                    self.gl_attribute_native_id,
                    _CONSTANT_GL_TEXTURE_2D,
                    cudart.cudaGraphicsRegisterFlags.cudaGraphicsRegisterFlagsWriteDiscard
                )
            )

        elif self.buffer_type == psb.DeviceBufferType.texture3d:
            raise ValueError("3d texture writes are not implemented")


    def __del__(self):
        self.unregister()

    def unregister(self):
        self.unmap()
        self.resource_handle = check_cudart_err(
            cudart.cudaGraphicsUnregisterResource(self.resource_handle))

    def map(self):
        if self.cuda_buffer_array is not None:
            return

        check_cudart_err(cudart.cudaGraphicsMapResources(1, self.resource_handle, None))

        self.cuda_buffer_array = check_cudart_err(cudart.cudaGraphicsSubResourceGetMappedArray(self.resource_handle, 0, 0))


    def unmap(self):
        if self.cuda_buffer_array is None:
            return

        check_cudart_err(cudart.cudaGraphicsUnmapResources(1, self.resource_handle, None))

        self.cuda_buffer_array = None
    
    def set_data_from_array(self, arr, expected_shape=None, expected_dtype=None):
        
        self.map()

        # get some info about the polyscope buffer we just mapped
        desc, extent, flags = check_cudart_err(cudart.cudaArrayGetInfo(self.cuda_buffer_array))

        # find a way to access the input array
        cupy_arr = self.get_array_from_unknown_data(arr)
            
        # do some shape & type checks
        if expected_dtype is not None and cupy_arr.dtype != expected_dtype:
            raise ValueError(f"dlpack array has wrong dtype, expected {expected_dtype} but got {cupy_arr.dtype}")

        if expected_shape is not None and cupy_arr.shape != expected_shape:
            raise ValueError(f"dlpack array has wrong shape, expected {expected_shape} but got {cupy_arr.shape}")


        if self.buffer_type == psb.DeviceBufferType.texture2d:
        
            buff_width = extent.width
            buff_height = extent.height
            buff_bytes_per = (desc.x + desc.y + desc.z + desc.w) // 8
        
            # do some shape & type checks
            expected_bytes = buff_width * buff_height * buff_bytes_per
            if cupy_arr.nbytes != expected_bytes:
                # if cupy_arr has the right size/dtype, it should have exactly the same 
                # number of bytes as the destination. This is just lazily saving us 
                # from repeating the math, and also directly validates the copy we 
                # are about to do below.
                raise ValueError(f"Mapped buffer write has wrong size, expected {cupy_arr.nbytes} bytes but got {expected_bytes} bytes. Could it be the wrong size/shape or wrong dtype?")
            

            # perform the actual copy
            check_cudart_err(
                cuda.cudart.cudaMemcpy2DToArray(
                    self.cuda_buffer_array, 0, 0, 
                    cupy_arr.data.ptr, buff_width * buff_bytes_per, buff_width * buff_bytes_per, buff_height, 
                    cudart.cudaMemcpyKind.cudaMemcpyDeviceToDevice
                )
            )

        else:
            raise ValueError("not implemented")

        self.unmap() 


    def get_array_from_unknown_data(self, arr):
        
        # Dispatch to one of the kinds of objects that we can read from

        # __cuda_array_interface__
        if is_cuda_array_interface(arr):
            return cupy.ascontiguousarray(cupy.asarray(arr))

        # __dlpack__
        # (I can't figure out any way to check this except try-catch)
        try:
            return cupy.ascontiguousarray(cupy.from_dlpack(arr))
        except ValueError:
            pass 
       
        raise ValueError("Cannot read from device data object. Must be a _dlpack_ array or implement the __cuda_array_interface__.")
