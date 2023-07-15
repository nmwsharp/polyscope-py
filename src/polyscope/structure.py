import polyscope_bindings as psb

from polyscope.floating_quantities import add_scalar_image_quantity, add_color_image_quantity, add_color_alpha_image_quantity, add_depth_render_image_quantity, add_color_render_image_quantity, add_scalar_render_image_quantity

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

    def add_scalar_image_quantity(self, name, values, image_origin="upper_left", datatype="standard", **option_args):
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_scalar_image_quantity(name, values, image_origin=image_origin, datatype=datatype, struct_ref=self, **option_args)
    
    def add_color_image_quantity(self, name, values, image_origin="upper_left", **option_args):
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_image_quantity(name, values, image_origin=image_origin, struct_ref=self, **option_args)

    def add_color_alpha_image_quantity(self, name, values, image_origin="upper_left", **option_args):
        """
        Add a "floating" image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_alpha_image_quantity(name, values, image_origin=image_origin, struct_ref=self, **option_args)

    ## Render Image
    
    def add_depth_render_image_quantity(self, name, depth_values, normal_values, image_origin="upper_left", color=None, **option_args):
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_depth_render_image_quantity(name, depth_values, normal_values, image_origin=image_origin, color=color, struct_ref=self, **option_args)

    def add_color_render_image_quantity(self, name, depth_values, normal_values, color_values, image_origin="upper_left", **option_args):
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_color_render_image_quantity(name, depth_values, normal_values, color_values, image_origin=image_origin, struct_ref=self, **option_args)

    def add_scalar_render_image_quantity(self, name, depth_values, normal_values, scalar_values, image_origin="upper_left", **option_args):
        """
        Add a "floating" render image quantity to the structure
        """

        # Call the general version (this abstraction allows us to handle the free-floating case via the same code)
        return add_scalar_render_image_quantity(name, depth_values, normal_values, scalar_values, image_origin=image_origin, struct_ref=self, **option_args)

