import polyscope_bindings as psb

from polyscope.common import check_is_scalar_image, check_is_color_image, check_is_coloralpha_image, process_scalar_args, process_color_args
from polyscope.core import image_origin_to_str, str_to_image_origin, str_to_datatype

# Base class for common properties and methods on structures
class Structure:

    def __init__(self):
        self.bound_instance = None


    ## Structure management

    def remove(self):
        '''Remove the structure itself'''
        self.bound_instance.remove()
    def remove_all_quantities(self):
        '''Remove all quantities on the structure'''
        self.bound_instance.remove_all_quantities()
    def remove_quantity(self, name):
        '''Remove a single quantity on the structure'''
        self.bound_instance.remove_quantity(name)
    

    ## Enable/disable

    def set_enabled(self, val=True):
        self.bound_instance.set_enabled(val)
    def is_enabled(self):
        return self.bound_instance.is_enabled()
    
    ## Transparency
    
    def set_transparency(self, val):
        self.bound_instance.set_transparency(val)
    def get_transparency(self):
        return self.bound_instance.get_transparency()
   
    ## Transformation things

    def center_bounding_box(self):
        self.bound_instance.center_bounding_box()
    def rescale_to_unit(self):
        self.bound_instance.rescale_to_unit()
    def reset_transform(self):
        self.bound_instance.reset_transform()
    def set_transform(self, new_mat4x4):
        self.bound_instance.set_transform(new_mat4x4)
    def set_position(self, new_vec3):
        self.bound_instance.set_position(new_vec3)
    def translate(self, trans_vec3):
        self.bound_instance.translate(trans_vec3)
    def get_transform(self):
        return self.bound_instance.get_transform()
    def get_position(self):
        return self.bound_instance.get_position()
    
    ## Slice planes

    def set_cull_whole_elements(self, val):
        self.bound_instance.set_cull_whole_elements(val)
    def get_cull_whole_elements(self):
        return self.bound_instance.get_cull_whole_elements()
    def set_ignore_slice_plane(self, plane, val):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            self.bound_instance.set_ignore_slice_plane(plane, val)
        else:
            self.bound_instance.set_ignore_slice_plane(plane.get_name(), val)
    def get_ignore_slice_plane(self, plane):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            return self.bound_instance.get_ignore_slice_plane(plane)
        else:
            return self.bound_instance.get_ignore_slice_plane(plane.get_name())


    ## Image Floating Quantities

    def add_scalar_image_quantity(self, name, dimX, dimY, values, image_origin="upper_left", datatype="standard", **scalar_args):
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_scalar_image_quantity(name, dimX, dimY, values, image_origin="upper_left", datatype="standard", struct_ref=self, **scalar_args)



def _resolve_floating_struct_instance(struct_ref):
    if struct_ref is None:
        return psb.get_global_floating_quantity_structure()
    else:
        return struct_ref.bound_instance

  
def add_scalar_image_quantity(name, dimX, dimY, values, image_origin, datatype, struct_ref=None, **scalar_args):
    
    struct_instance_ref = _resolve_floating_struct_instance(struct_ref)

    dimX = int(dimX)
    dimY = int(dimY)
    check_is_scalar_image(values, dimX, dimY)

    values_flat = values.reshape(dimX*dimY)
        
    q = struct_instance_ref.add_scalar_image_quantity(name, dimX, dimY, values_flat,              
                                             str_to_image_origin(image_origin), str_to_datatype(datatype))

    process_scalar_args(struct_ref, q, scalar_args)
