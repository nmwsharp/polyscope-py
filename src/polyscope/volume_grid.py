import polyscope_bindings as psb
import numpy as np

from polyscope.core import str_to_datatype, str_to_vectortype, str_to_param_coords_type, str_to_param_viz_style, glm3, glm3u, enum_to_str
from polyscope.structure import Structure
from polyscope.common import process_quantity_args, process_scalar_args, process_color_args, process_vector_args, check_all_args_processed, check_and_pop_arg

def process_volume_grid_scalar_args(structure, quantity, scalar_args, defined_on):

    val = check_and_pop_arg(scalar_args, 'enable_gridcube_viz')
    if val is not None:
        quantity.set_gridcube_viz_enabled(val)
   
    if defined_on == 'nodes':

        val = check_and_pop_arg(scalar_args, 'enable_isosurface_viz')
        if val is not None:
            quantity.set_isosurface_viz_enabled(val)
        
        val = check_and_pop_arg(scalar_args, 'isosurface_level')
        if val is not None:
            quantity.set_isosurface_level(val)
        
        val = check_and_pop_arg(scalar_args, 'isosurface_color')
        if val is not None:
            quantity.set_isosurface_color(glm3(val))
        
        val = check_and_pop_arg(scalar_args, 'slice_planes_affect_isosurface')
        if val is not None:
            quantity.set_slice_planes_affect_isosurface(val)
        
        val = check_and_pop_arg(scalar_args, 'register_isosurface_as_mesh_with_name')
        if val is not None:
            quantity.register_isosurface_as_mesh_with_name(val)
        

class VolumeGrid(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_volume_grid instead
    def __init__(self, name=None, node_dims=None, bound_low=None, bound_high=None, instance=None):
        
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance

            node_dims = glm3u(node_dims)
            bound_low = glm3(bound_low)
            bound_high = glm3(bound_high)

            self.bound_instance = psb.register_volume_grid(name, node_dims, bound_low, bound_high)


    def n_nodes(self):
        return self.bound_instance.n_nodes()
    def n_cells(self):
        return self.bound_instance.n_cells()
    def grid_spacing(self):
        return self.bound_instance.grid_spacing()
    def get_grid_node_dim(self):
        return self.bound_instance.get_grid_node_dim().as_tuple()
    def get_grid_cell_dim(self):
        return self.bound_instance.get_grid_cell_dim().as_tuple()
    def get_bound_min(self):
        return self.bound_instance.get_bound_min()
    def get_bound_max(self):
        return self.bound_instance.get_bound_max()

    ## Structure management

    ## Options

    # Color
    def set_color(self, val):
        self.bound_instance.set_color(glm3(val))
    def get_color(self):
        return self.bound_instance.get_color().as_tuple()
    
    # Edge Color
    def set_edge_color(self, val):
        self.bound_instance.set_edge_color(glm3(val))
    def get_edge_color(self):
        return self.bound_instance.get_edge_color().as_tuple()
    
    # Edge width
    def set_edge_width(self, val):
        self.bound_instance.set_edge_width(val)
    def get_edge_width(self):
        return self.bound_instance.get_edge_width()
    
    # Edge width
    def set_cube_size_factor(self, val):
        self.bound_instance.set_cube_size_factor(val)
    def get_cube_size_factor(self):
        return self.bound_instance.get_cube_size_factor()
    
    # Material
    def set_material(self, mat):
        self.bound_instance.set_material(mat)
    def get_material(self):
        return self.bound_instance.get_material()

    ## Other stateful options

    def mark_nodes_as_used(self):
        return self.bound_instance.mark_nodes_as_used()
    def mark_cells_as_used(self):
        return self.bound_instance.mark_cells_as_used()


    # Picking
    def append_pick_data(self, pick_result):
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = enum_to_str(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index

    ## Quantities

    # Scalar

    def add_scalar_quantity(self, name, values, defined_on='nodes', datatype="standard", **scalar_args):

        # NOTE: notice the .flatten('F') below to flatten in Fortran order. This assumes the input data is indexed like array[xInd,yInd,zInd],
        # and converts to the internal x-changes-fastest data layout that the volume grid uses.

        if defined_on == 'nodes':

            if values.shape != self.get_grid_node_dim(): raise ValueError(f"'values' should be a {self.get_grid_node_dim()} array")

            q = self.bound_instance.add_node_scalar_quantity(name, values.flatten('F'), str_to_datatype(datatype))

        elif defined_on == 'cells':
            
            if values.shape != self.get_grid_cell_dim(): raise ValueError(f"'values' should be a {self.get_grid_cell_dim()} array")

            q = self.bound_instance.add_cell_scalar_quantity(name, values.flatten('F'), str_to_datatype(datatype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))
  

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_volume_grid_scalar_args(self, q, scalar_args, defined_on)
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)


    def add_scalar_quantity_from_callable(self, name, func, defined_on='nodes', datatype="standard", **scalar_args):

        if defined_on == 'nodes':

            q = self.bound_instance.add_node_scalar_quantity_from_callable(name, func, str_to_datatype(datatype))

        elif defined_on == 'cells':
            
            q = self.bound_instance.add_cell_scalar_quantity_from_callable(name, func, str_to_datatype(datatype))
            
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'cells']".format(defined_on))
  

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_volume_grid_scalar_args(self, q, scalar_args, defined_on)
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)
   

def register_volume_grid(name, node_dims, bound_low, bound_high, enabled=None, color=None, edge_color=None, edge_width=None, cube_size_factor=None, material=None, transparency=None):

    """Register a new volume grid"""

    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")
    
    p = VolumeGrid(name, node_dims=node_dims, bound_low=bound_low, bound_high=bound_high)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if color is not None:
        p.set_color(color)
    if edge_color is not None:
        p.set_edge_color(edge_color)
    if edge_width is not None:
        p.set_edge_width(edge_width)
    if cube_size_factor is not None:
        p.set_cube_size_factor(cube_size_factor)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p

def remove_volume_grid(name, error_if_absent=True):
    """Remove a volume grid by name"""
    psb.remove_volume_grid(name, error_if_absent)

def get_volume_grid(name):
    """Get volume grid by name"""
    if not has_volume_grid(name):
        raise ValueError("no volume grid with name " + str(name))

    raw = psb.get_volume_grid(name)

    # Wrap the instance
    return VolumeGrid(instance=raw)

def has_volume_grid(name):
    """Check if a volume grid exists by name"""
    return psb.has_volume_grid(name)
    
