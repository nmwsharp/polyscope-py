import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3

class SurfaceMesh:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_surface_mesh instead
    def __init__(self, name=None, vertices=None, faces=None, instance=None):


        # TODO ragged vertex arrays

        if instance is not None:
            # Wrap an existing instance
            self.bound_mesh = instance

        else:
            # Create a new instance
            self.check_shape(vertices)

            if (len(faces.shape) != 2):
                raise ValueError("surface mesh face array should have shape (F,D) for some D; shape is " + str(faces.shape))

            if vertices.shape[1] == 3:
                self.bound_mesh = psb.register_surface_mesh(name, vertices, faces) 
            elif vertices.shape[1] == 2:
                self.bound_mesh = psb.register_surface_mesh2D(name, vertices, faces) 

    def check_shape(self, points):
        # Helper to validate arrays
        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("surface mesh node positions should have shape (N,3) or (N,2); shape is " + str(points.shape))
      

    def n_vertices(self):
        return self.bound_mesh.n_vertices()
    def n_faces(self):
        return self.bound_mesh.n_faces()
    def n_edges(self):
        return self.bound_mesh.n_edges()
    def n_halfedges(self):
        return self.bound_mesh.n_halfedges()
    def n_corners(self):
        return self.bound_mesh.n_corners()

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

    # Update
    def update_vertex_positions(self, vertices):
        self.check_shape(vertices)
        
        if vertices.shape[1] == 3:
            self.bound_mesh.update_vertex_positions(vertices)
        elif vertices.shape[1] == 2:
            self.bound_mesh.update_vertex_positions2D(vertices)
        else:
            raise ValueError("bad node shape")

    ## Options

    
    # Color
    def set_color(self, val):
        self.bound_mesh.set_color(glm3(val))
    def get_color(self):
        return self.bound_mesh.get_color().as_tuple()
    
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
    
    # Smooth shade
    def set_smooth_shade(self, val):
        self.bound_mesh.set_smooth_shade(val)
    def get_smooth_shade(self):
        return self.bound_mesh.get_smooth_shade()
    
    # Material
    def set_material(self, mat):
        self.bound_mesh.set_material(mat)
    def get_material(self):
        return self.bound_mesh.get_material()


    ## Quantities
    '''

    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='vertices', enabled=None, datatype="standard", vminmax=None, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_mesh.add_node_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'faces':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_mesh.add_edge_scalar_quantity(name, values, str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))
            

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
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_mesh.add_node_color_quantity(name, values)
        elif defined_on == 'faces':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_mesh.add_edge_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='vertices', enabled=None, vectortype="standard", length=None, radius=None, color=None):
        if len(values.shape) != 2 or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")

            if values.shape[1] == 2:
                q = self.bound_mesh.add_node_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_mesh.add_node_vector_quantity(name, values, str_to_vectortype(vectortype))

        elif defined_on == 'faces':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            
            if values.shape[1] == 2:
                q = self.bound_mesh.add_edge_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_mesh.add_edge_vector_quantity(name, values, str_to_vectortype(vectortype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if length is not None:
            q.set_length(length, True)
        if radius is not None:
            q.set_radius(radius, True)
        if color is not None:
            q.set_color(glm3(color))
    '''


def register_surface_mesh(name, vertices, faces, enabled=None, color=None, edge_color=None, smooth_shade=None, 
                          edge_width=None, material=None):
    """Register a new surface mesh"""

    p = SurfaceMesh(name, vertices, faces)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if color is not None:
        p.set_color(color)
    if edge_color is not None:
        p.set_edge_color(edge_color)
    if edge_width is not None:
        p.set_edge_width(edge_width)
    if smooth_shade is not None:
        p.set_smooth_shade(smooth_shade)
    if material is not None:
        p.set_material(material)

    return p

def remove_surface_mesh(name, error_if_absent=True):
    """Remove a surface mesh by name"""
    psb.remove_surface_mesh(name, error_if_absent)

def get_surface_mesh(name):
    """Get surface mesh by name"""
    if not has_surface_mesh(name):
        raise ValueError("no surface mesh with name " + str(name))

    raw = psb.get_surface_mesh(name)

    # Wrap the instance
    return SurfaceMesh(instance=raw)

def has_surface_mesh(name):
    """Check if a surface mesh exists by name"""
    return psb.has_surface_mesh(name)
    
