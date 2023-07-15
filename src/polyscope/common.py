import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3, str_to_point_render_mode, point_render_mode_to_str, str_to_param_viz_style


def check_is_scalar_image(values):
    if len(values.shape) != 2:
        raise ValueError(f"'values' should be a (height,width) array. Shape is {values.shape}.")

def check_is_image3(values):
    if len(values.shape) != 3 or values.shape[2] != 3: 
        raise ValueError(f"'values' should be a (height,width,3) array. Shape is {values.shape}.")

def check_is_image4(values):
    if len(values.shape) != 3 or values.shape[2] != 4: 
        raise ValueError(f"'values' should be a (height,width,4) array. Shape is {values.shape}.")

def check_image_dims_compatible(images):

    dimX = None
    dimY = None

    for img in images:

        if dimX is None:
            dimX = img.shape[0]
            dimY = img.shape[1]
        else:
            new_dimX = img.shape[0]
            new_dimY = img.shape[1]

            if (dimX, dimY) != (new_dimX, new_dimY):
                raise ValueError(f"image inputs must have same resolution. One is {(dimX,dimY)} but another is {(new_dimX, new_dimY)}.")

def check_and_pop_arg(d, argname):
    if argname in d:
        return d.pop(argname)
    return None

# Process args, removing them from the dict if they are present
def process_quantity_args(structure, quantity, quantity_args):

    val = check_and_pop_arg(quantity_args, 'enabled')
    if val is not None:
        quantity.set_enabled(val)

# Process args, removing them from the dict if they are present
def process_color_args(structure, quantity, color_args):

    pass # none yet


# Process args, removing them from the dict if they are present
def process_scalar_args(structure, quantity, scalar_args):

    val = check_and_pop_arg(scalar_args, 'vminmax')
    if val is not None:
        quantity.set_map_range(val)
        
    val = check_and_pop_arg(scalar_args, 'cmap')
    if val is not None:
        quantity.set_color_map(val)


# Process args, removing them from the dict if they are present
def process_vector_args(structure, quantity, vector_args):
    
    val = check_and_pop_arg(vector_args, 'length')
    if val is not None:
        quantity.set_length(val, True)
    
    val = check_and_pop_arg(vector_args, 'radius')
    if val is not None:
        quantity.set_radius(val, True)
    
    val = check_and_pop_arg(vector_args, 'color')
    if val is not None:
        quantity.set_color(glm3(val))


# Process args, removing them from the dict if they are present
def process_parameterization_args(structure, quantity, parameterization_args):

    val = check_and_pop_arg(parameterization_args, 'viz_style')
    if val is not None:
        viz_style_enum = str_to_param_viz_style(val)
        quantity.set_style(viz_style_enum)

    val = check_and_pop_arg(parameterization_args, 'grid_colors')
    if val is not None:
        quantity.set_grid_colors((glm3(val[0]), glm3(val[1])))
    
    val = check_and_pop_arg(parameterization_args, 'checker_colors')
    if val is not None:
        quantity.set_checker_colors((glm3(val[0]), glm3(val[1])))
    
    val = check_and_pop_arg(parameterization_args, 'checker_size')
    if val is not None:
        quantity.set_checker_size(val)
    
    val = check_and_pop_arg(parameterization_args, 'cmap')
    if val is not None:
        quantity.set_color_map(val)
        

# Process args, removing them from the dict if they are present
def process_image_args(structure, quantity, image_args):

    val = check_and_pop_arg(image_args, 'show_fullscreen')
    if val is not None:
        quantity.set_show_fullscreen(val)
    
    val = check_and_pop_arg(image_args, 'show_in_imgui_window')
    if val is not None:
        quantity.set_show_in_imgui_window(val)
    
    val = check_and_pop_arg(image_args, 'show_in_camera_billboard')
    if val is not None:
        quantity.set_show_in_camera_billboard(val)
    
    val = check_and_pop_arg(image_args, 'transparency')
    if val is not None:
        quantity.set_transparency(val)

# Process args, removing them from the dict if they are present
def process_render_image_args(structure, quantity, image_args):

    val = check_and_pop_arg(image_args, 'transparency')
    if val is not None:
        quantity.set_transparency(val)
    
    val = check_and_pop_arg(image_args, 'material')
    if val is not None:
        quantity.set_material(val)
    

def check_all_args_processed(structure, quantity, args):
    for arg,val in args.items():
        raise ValueError(f"Polyscope: Unrecognized quantity keyword argument {arg}: {val}")

