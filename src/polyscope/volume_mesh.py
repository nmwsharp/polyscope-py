import polyscope_bindings as psb
import numpy as np

from polyscope.core import str_to_datatype, str_to_vectortype, str_to_param_coords_type, str_to_param_viz_style, glm3, enum_to_str
from polyscope.structure import Structure
from polyscope.common import process_quantity_args, process_scalar_args, process_color_args, process_vector_args, check_all_args_processed

class VolumeMesh(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_volume_mesh instead
    def __init__(self, name=None, vertices=None, tets=None, hexes=None, mixed_cells=None, instance=None):
        
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance

            self.check_shape(vertices)
            self.check_index_array(tets, 4, "tets")
            self.check_index_array(hexes, 8, "tets")
            self.check_index_array(mixed_cells, 8, "tets")

            if mixed_cells is not None and (tets is not None or hexes is not None):
                raise ValueError("specify EITHER mixed_cells OR tets/hexes but not both")

            if mixed_cells is not None:
                self.bound_instance = psb.register_volume_mesh(name, vertices, mixed_cells)

            else:
                if tets is None:
                    self.bound_instance = psb.register_hex_mesh(name, vertices, hexes)
                elif hexes is None:
                    self.bound_instance = psb.register_tet_mesh(name, vertices, tets)
                else:
                    self.bound_instance = psb.register_tet_hex_mesh(name, vertices, tets, hexes)


    def check_shape(self, points):
        # Helper to validate arrays
        
        if points is None:
            raise ValueError("must specify volume mesh vertex positions")
        
        if len(points.shape) !=2 or points.shape[1] != 3:
            raise ValueError("volume mesh vertex positions should have shape (N,3); shape is " + str(points.shape))

    def check_index_array(self, arr, dim, name):
        # Helper to validate arrays

        # check the type
        if arr is None:
            return
        if not isinstance(arr, np.ndarray):
            raise ValueError("volume mesh {} array should be a numpy array, but is {}".format(name, type(arr)))
        if not issubclass(arr.dtype.type, np.integer):
            raise ValueError("volume mesh {} array should be an integer array".format(name))

        # check the dimension
        if (len(arr.shape) != 2) or (arr.shape[1] != dim):
            raise ValueError("volume mesh {} array should have shape (N,{}); shape is {}".format(name, dim, str(arr.shape)))


    def n_vertices(self):
        return self.bound_instance.n_vertices()
    def n_faces(self):
        return self.bound_instance.n_faces()
    def n_cells(self):
        return self.bound_instance.n_cells()

    ## Structure management

    # Update
    def update_vertex_positions(self, vertices):
        self.check_shape(vertices)
        self.bound_instance.update_vertex_positions(vertices)


    ## Options
    
    # Color
    def set_color(self, val):
        self.bound_instance.set_color(glm3(val))
    def get_color(self):
        return self.bound_instance.get_color().as_tuple()
    
    # Interior Color
    def set_interior_color(self, val):
        self.bound_instance.set_interior_color(glm3(val))
    def get_interior_color(self):
        return self.bound_instance.get_interior_color().as_tuple()
    
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
    
    # Material
    def set_material(self, mat):
        self.bound_instance.set_material(mat)
    def get_material(self):
        return self.bound_instance.get_material()

    # Picking
    def append_pick_data(self, pick_result):
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = enum_to_str(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index


    ## Quantities

    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='vertices', datatype="standard", **scalar_args):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_instance.add_cell_scalar_quantity(name, values, str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))
  

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)

    
    
    # Color
    def add_color_quantity(self, name, values, defined_on='vertices', **color_args):
        if len(values.shape) != 2 or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_color_quantity(name, values)
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_instance.add_cell_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))


        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, color_args)
        process_color_args(self, q, color_args)
        check_all_args_processed(self, q, color_args)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='vertices', vectortype="standard", **vector_args):
        if len(values.shape) != 2 or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_vector_quantity(name, values, str_to_vectortype(vectortype))
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_instance.add_cell_vector_quantity(name, values, str_to_vectortype(vectortype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))


        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)
    
    

def register_volume_mesh(name, vertices, tets=None, hexes=None, mixed_cells=None, enabled=None, color=None, interior_color=None, edge_color=None, edge_width=None, material=None, transparency=None):

    """Register a new volume mesh"""

    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")
    
    p = VolumeMesh(name, vertices=vertices, tets=tets, hexes=hexes, mixed_cells=mixed_cells)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if color is not None:
        p.set_color(color)
    if interior_color is not None:
        p.set_interior_color(interior_color)
    if edge_color is not None:
        p.set_edge_color(edge_color)
    if edge_width is not None:
        p.set_edge_width(edge_width)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p

def remove_volume_mesh(name, error_if_absent=True):
    """Remove a volume mesh by name"""
    psb.remove_volume_mesh(name, error_if_absent)

def get_volume_mesh(name):
    """Get volume mesh by name"""
    if not has_volume_mesh(name):
        raise ValueError("no volume mesh with name " + str(name))

    raw = psb.get_volume_mesh(name)

    # Wrap the instance
    return VolumeMesh(instance=raw)

def has_volume_mesh(name):
    """Check if a volume mesh exists by name"""
    return psb.has_volume_mesh(name)
    
