import polyscope_bindings as psb
import numpy as np

from polyscope.core import str_to_datatype, str_to_vectortype, str_to_param_coords_type, str_to_param_viz_style, glm3

class VolumeMesh:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_volume_mesh instead
    def __init__(self, name=None, vertices=None, tets=None, hexes=None, mixed_cells=None, instance=None):

        if instance is not None:
            # Wrap an existing instance
            self.bound_mesh = instance

        else:
            # Create a new instance

            self.check_shape(vertices)
            self.check_index_array(tets, 4, "tets")
            self.check_index_array(hexes, 8, "tets")
            self.check_index_array(mixed_cells, 8, "tets")

            if mixed_cells is not None and (tets is not None or hexes is not None):
                raise ValueError("specify EITHER mixed_cells OR tets/hexes but not both")

            if mixed_cells is not None:
                self.bound_mesh = psb.register_volume_mesh(name, vertices, mixed_cells)

            else:
                if tets is None:
                    self.bound_mesh = psb.register_hex_mesh(name, vertices, hexes)
                elif hexes is None:
                    self.bound_mesh = psb.register_tet_mesh(name, vertices, tets)
                else:
                    self.bound_mesh = psb.register_tet_hex_mesh(name, vertices, tets, hexes)


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
        return self.bound_mesh.n_vertices()
    def n_faces(self):
        return self.bound_mesh.n_faces()
    def n_cells(self):
        return self.bound_mesh.n_cells()

    ## Structure management
    
    def remove(self):
        '''Remove the structure itself'''
        self.bound_mesh.remove()
    def remove_all_quantities(self):
        '''Remove all quantities on the structure'''
        self.bound_mesh.remove_all_quantities()
    def remove_quantity(self, name):
        '''Remove a single quantity on the structure'''
        self.bound_mesh.remove_quantity(name)

    # Enable/disable
    def set_enabled(self, val=True):
        self.bound_mesh.set_enabled(val)
    def is_enabled(self):
        return self.bound_mesh.is_enabled()
    
    # Transparency
    def set_transparency(self, val):
        self.bound_mesh.set_transparency(val)
    def get_transparency(self):
        return self.bound_mesh.get_transparency()
    
    # Transformation things
    def center_bounding_box(self):
        self.bound_mesh.center_bounding_box()
    def rescale_to_unit(self):
        self.bound_mesh.rescale_to_unit()
    def reset_transform(self):
        self.bound_mesh.reset_transform()
    def set_transform(self, new_mat4x4):
        self.bound_mesh.set_transform(new_mat4x4)
    def set_position(self, new_vec3):
        self.bound_mesh.set_position(new_vec3)
    def translate(self, trans_vec3):
        self.bound_mesh.translate(trans_vec3)
    def get_transform(self):
        return self.bound_mesh.get_transform()
    def get_position(self):
        return self.bound_mesh.get_position()
    
    # Slice planes
    def set_cull_whole_elements(self, val):
        self.bound_mesh.set_cull_whole_elements(val)
    def get_cull_whole_elements(self):
        return self.bound_mesh.get_cull_whole_elements()
    def set_ignore_slice_plane(self, plane, val):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            self.bound_mesh.set_ignore_slice_plane(plane, val)
        else:
            self.bound_mesh.set_ignore_slice_plane(plane.get_name(), val)
    def get_ignore_slice_plane(self, plane):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            return self.bound_mesh.get_ignore_slice_plane(plane)
        else:
            return self.bound_mesh.get_ignore_slice_plane(plane.get_name())


    # Update
    def update_vertex_positions(self, vertices):
        self.check_shape(vertices)
        self.bound_mesh.update_vertex_positions(vertices)


    ## Options

    # Color
    def set_color(self, val):
        self.bound_mesh.set_color(glm3(val))
    def get_color(self):
        return self.bound_mesh.get_color().as_tuple()
    
    # Interior Color
    def set_interior_color(self, val):
        self.bound_mesh.set_interior_color(glm3(val))
    def get_interior_color(self):
        return self.bound_mesh.get_interior_color().as_tuple()
    
    # Edge Color
    def set_edge_color(self, val):
        self.bound_mesh.set_edge_color(glm3(val))
    def get_edge_color(self):
        return self.bound_mesh.get_edge_color().as_tuple()
    
    # Edge width
    def set_edge_width(self, val):
        self.bound_mesh.set_edge_width(val)
    def get_edge_width(self):
        return self.bound_mesh.get_edge_width()
    
    # Material
    def set_material(self, mat):
        self.bound_mesh.set_material(mat)
    def get_material(self):
        return self.bound_mesh.get_material()


    ## Quantities

    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='vertices', enabled=None, datatype="standard", vminmax=None, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_mesh.add_vertex_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_mesh.add_cell_scalar_quantity(name, values, str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))
            

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if vminmax is not None:
            q.set_map_range(vminmax)
        if cmap is not None:
            q.set_color_map(cmap)
    
    
    # Color
    def add_color_quantity(self, name, values, defined_on='vertices', enabled=None):
        if len(values.shape) != 2 or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_mesh.add_vertex_color_quantity(name, values)
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_mesh.add_cell_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='vertices', enabled=None, vectortype="standard", length=None, radius=None, color=None):
        if len(values.shape) != 2 or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_mesh.add_vertex_vector_quantity(name, values, str_to_vectortype(vectortype))
        elif defined_on == 'cells':
            if values.shape[0] != self.n_cells(): raise ValueError("'values' should be a length n_cells array")
            q = self.bound_mesh.add_cell_vector_quantity(name, values, str_to_vectortype(vectortype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'cells']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if length is not None:
            q.set_length(length, True)
        if radius is not None:
            q.set_radius(radius, True)
        if color is not None:
            q.set_color(glm3(color))
    
    

def register_volume_mesh(name, vertices, tets=None, hexes=None, mixed_cells=None, enabled=None, color=None, interior_color=None, edge_color=None, edge_width=None, material=None, transparency=None):

    """Register a new surface mesh"""
    if not psb.isInitialized():
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
    
