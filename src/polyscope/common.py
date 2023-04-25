import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3, str_to_point_render_mode, point_render_mode_to_str, str_to_param_viz_style


def process_color_args(structure, quantity, color_args):

    for arg,val in color_args.items():

        if arg == 'enabled' and val is not None:
            quantity.set_enabled(val)
        
        else:
            raise ValueError(f"Polyscope: Unrecognized color quantity keyword argument {arg}: {val}")


def process_scalar_args(structure, quantity, scalar_args):

    for arg,val in scalar_args.items():

        if arg == 'enabled' and val is not None:
            quantity.set_enabled(val)
        
        elif arg == 'vminmax' and val is not None:
            quantity.set_map_range(val)
        
        elif arg == 'cmap' and val is not None:
            quantity.set_color_map(val)

        else:
            raise ValueError(f"Polyscope: Unrecognized scalar quantity keyword argument {arg}: {val}")

def process_vector_args(structure, quantity, vector_args):

    for arg,val in vector_args.items():

        if arg == 'enabled' and val is not None:
            quantity.set_enabled(val)
        
        elif arg == 'length' and val is not None:
            quantity.set_length(val, True)
        
        elif arg == 'radius' and val is not None:
            quantity.set_radius(val, True)
        
        elif arg == 'color' and val is not None:
            quantity.set_color(glm3(val))
        
        else:
            raise ValueError(f"Polyscope: Unrecognized vector quantity keyword argument {arg}: {val}")

def process_parameterization_args(structure, quantity, parameterization_args):

    for arg,val in parameterization_args.items():

        if arg == 'enabled' and val is not None:
            quantity.set_enabled(val)
        
        elif arg == 'viz_style' and val is not None:
            viz_style_enum = str_to_param_viz_style(val)
            quantity.set_style(viz_style_enum)
        
        elif arg == 'grid_colors' and val is not None:
            quantity.set_grid_colors((glm3(val[0]), glm3(val[1])))
        
        elif arg == 'checker_colors' and val is not None:
            quantity.set_checker_colors((glm3(val[0]), glm3(val[1])))
        
        elif arg == 'checker_size' and val is not None:
            quantity.set_checker_size(val)
        
        elif arg == 'cmap' and val is not None:
            quantity.set_color_map(val)
        
        else:
            raise ValueError(f"Polyscope: Unrecognized parameterization quantity keyword argument {arg}: {val}")

