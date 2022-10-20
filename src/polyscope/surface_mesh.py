import polyscope_bindings as psb
import numpy as np

from polyscope.core import str_to_datatype, str_to_vectortype, str_to_param_coords_type,            \
                           str_to_param_viz_style, str_to_back_face_policy, back_face_policy_to_str,\
                           glm3

class SurfaceMesh:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_surface_mesh instead
    def __init__(self, name=None, vertices=None, faces=None, instance=None):

        if instance is not None:
            # Wrap an existing instance
            self.bound_mesh = instance

        else:
            # Create a new instance
            self.check_shape(vertices)
    
            if isinstance(faces, np.ndarray):
                # Faces is a numpy array
            
                if (len(faces.shape) != 2): raise ValueError("surface mesh face array should have shape (F,D) for some D; shape is " + str(faces.shape))

                if vertices.shape[1] == 3:
                    self.bound_mesh = psb.register_surface_mesh(name, vertices, faces) 
                elif vertices.shape[1] == 2:
                    self.bound_mesh = psb.register_surface_mesh2D(name, vertices, faces) 

            else:
                # Faces is something else, try to iterate through it to build a list of lists
                faces_copy = []
                for f in faces:
                    f_copy = [v for v in f]
                    faces_copy.append(f_copy)

                if vertices.shape[1] == 3:
                    self.bound_mesh = psb.register_surface_mesh_list(name, vertices, faces) 
                elif vertices.shape[1] == 2:
                    self.bound_mesh = psb.register_surface_mesh_list2D(name, vertices, faces) 

                        

    def check_shape(self, points):
        # Helper to validate arrays
        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("surface mesh vertex positions should have shape (N,3) or (N,2); shape is " + str(points.shape))
      

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
        
        if vertices.shape[1] == 3:
            self.bound_mesh.update_vertex_positions(vertices)
        elif vertices.shape[1] == 2:
            self.bound_mesh.update_vertex_positions2D(vertices)
        else:
            raise ValueError("bad vertex shape")

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

    # Color
    def set_back_face_policy(self, val):
        self.bound_mesh.set_back_face_policy(str_to_back_face_policy(val))
    def get_back_face_policy(self):
        return back_face_policy_to_str(self.bound_mesh.get_back_face_policy())
    
    # Back face color
    def set_back_face_color(self, val):
        self.bound_mesh.set_back_face_color(glm3(val))
    def get_back_face_color(self):
        return self.bound_mesh.get_back_face_color().as_tuple()

    ## Permutations and bases

    def set_vertex_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_vertices(): raise ValueError("'perm' should be an array with one entry per vertex")
        if expected_size is None: expected_size = 0
        self.bound_mesh.set_vertex_permutation(perm, expected_size)

    def set_face_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_faces(): raise ValueError("'perm' should be an array with one entry per face")
        if expected_size is None: expected_size = 0
        self.bound_mesh.set_face_permutation(perm, expected_size)
    
    def set_edge_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_edges(): raise ValueError("'perm' should be an array with one entry per edge")
        if expected_size is None: expected_size = 0
        self.bound_mesh.set_edge_permutation(perm, expected_size)
    
    def set_corner_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_corners(): raise ValueError("'perm' should be an array with one entry per corner")
        if expected_size is None: expected_size = 0
        self.bound_mesh.set_corner_permutation(perm, expected_size)
    
    def set_halfedge_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_halfedges(): raise ValueError("'perm' should be an array with one entry per halfedge")
        if expected_size is None: expected_size = 0
        self.bound_mesh.set_halfedge_permutation(perm, expected_size)
    
    def set_all_permutations(self, 
            vertex_perm=None, vertex_perm_size=None,
            face_perm=None, face_perm_size=None,
            edge_perm=None, edge_perm_size=None,
            corner_perm=None, corner_perm_size=None,
            halfedge_perm=None, halfedge_perm_size=None):

        if vertex_perm is not None: self.set_vertex_permutation(vertex_perm, vertex_perm_size)
        if face_perm is not None: self.set_face_permutation(face_perm, face_perm_size)
        if edge_perm is not None: self.set_edge_permutation(edge_perm, edge_perm_size)
        if corner_perm is not None: self.set_corner_permutation(corner_perm, corner_perm_size)
        if halfedge_perm is not None: self.set_halfedge_permutation(halfedge_perm, halfedge_perm_size)
    
    def set_vertex_tangent_basisX(self, vectors):
        if len(vectors.shape) != 2 or vectors.shape[0] != self.n_vertices() or vectors.shape[1] not in (2,3): 
            raise ValueError("'vectors' should be an array with one entry per vertex")

        if vectors.shape[1] == 2:
            self.bound_mesh.set_vertex_tangent_basisX2D(vectors)
        elif vectors.shape[1] == 3:
            self.bound_mesh.set_vertex_tangent_basisX(vectors)
    
    def set_face_tangent_basisX(self, vectors):
        if len(vectors.shape) != 2 or vectors.shape[0] != self.n_faces() or vectors.shape[1] not in (2,3): 
            raise ValueError("'vectors' should be an array with one entry per face")

        if vectors.shape[1] == 2:
            self.bound_mesh.set_face_tangent_basisX2D(vectors)
        elif vectors.shape[1] == 3:
            self.bound_mesh.set_face_tangent_basisX(vectors)
    
         


    ## Quantities

    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='vertices', enabled=None, datatype="standard", vminmax=None, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_mesh.add_vertex_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_mesh.add_face_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'edges':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_mesh.add_edge_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'halfedges':
            if values.shape[0] != self.n_halfedges(): raise ValueError("'values' should be a length n_halfedges array")
            q = self.bound_mesh.add_halfedge_scalar_quantity(name, values, str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces', 'edges', 'halfedges']".format(defined_on))
            

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
        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_mesh.add_face_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
    
    
    # Distance
    def add_distance_quantity(self, name, values, defined_on='vertices', enabled=None, signed=False, vminmax=None, stripe_size=None, stripe_size_relative=True, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")

            if signed:
                q = self.bound_mesh.add_vertex_signed_distance_quantity(name, values)
            else:
                q = self.bound_mesh.add_vertex_distance_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices']".format(defined_on))
            

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if stripe_size is not None:
            q.set_isoline_width(stripe_size, stripe_size_relative)
        if vminmax is not None:
            q.set_map_range(vminmax)
        if cmap is not None:
            q.set_color_map(cmap)
    
    
    # Parameterization
    def add_parameterization_quantity(self, name, values, defined_on='vertices', coords_type='unit', enabled=None, viz_style=None, grid_colors=None, checker_colors=None, checker_size=None, cmap=None):

        if len(values.shape) != 2 or values.shape[1] != 2: raise ValueError("'values' should be an (Nx2) array")

        # parse the coords type in to an enum
        coords_type_enum = str_to_param_coords_type(coords_type)

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_mesh.add_vertex_parameterization_quantity(name, values, coords_type_enum)
        elif defined_on == 'corners':
            if values.shape[0] != self.n_corners(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_mesh.add_corner_parameterization_quantity(name, values, coords_type_enum)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'corners']".format(defined_on))
            

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if viz_style is not None:
            viz_style_enum = str_to_param_viz_style(viz_style)
            q.set_style(viz_style_enum)
        if grid_colors is not None:
            q.set_grid_colors((glm3(grid_colors[0]), glm3(grid_colors[1])))
        if checker_colors is not None:
            q.set_checker_colors((glm3(checker_colors[0]), glm3(checker_colors[1])))
        if checker_size is not None:
            q.set_checker_size(checker_size)
        if cmap is not None:
            q.set_color_map(cmap)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='vertices', enabled=None, vectortype="standard", length=None, radius=None, color=None):
        if len(values.shape) != 2 or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")

            if values.shape[1] == 2:
                q = self.bound_mesh.add_vertex_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_mesh.add_vertex_vector_quantity(name, values, str_to_vectortype(vectortype))

        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            
            if values.shape[1] == 2:
                q = self.bound_mesh.add_face_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_mesh.add_face_vector_quantity(name, values, str_to_vectortype(vectortype))

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
    
    
    def add_intrinsic_vector_quantity(self, name, values, n_sym=1, defined_on='vertices', enabled=None, vectortype="standard", length=None, radius=None, color=None, ribbon=None):

        if len(values.shape) != 2 or values.shape[1] != 2: raise ValueError("'values' should be an Nx2 array")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")

            q = self.bound_mesh.add_vertex_intrinsic_vector_quantity(name, values, n_sym, str_to_vectortype(vectortype))

        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            
            q = self.bound_mesh.add_face_intrinsic_vector_quantity(name, values, n_sym, str_to_vectortype(vectortype))

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
        if ribbon is not None:
            q.set_ribbon_enabled(ribbon)
    
    
    def add_one_form_vector_quantity(self, name, values, orientations, enabled=None, length=None, radius=None, color=None, ribbon=None):

        if len(values.shape) != 1 or values.shape[0] != self.n_edges(): raise ValueError("'values' should be length n_edges array")
        if len(orientations.shape) != 1 or orientations.shape[0] != self.n_edges(): raise ValueError("'orientations' should be length n_edges array")

        q = self.bound_mesh.add_one_form_intrinsic_vector_quantity(name, values, orientations)

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if length is not None:
            q.set_length(length, True)
        if radius is not None:
            q.set_radius(radius, True)
        if color is not None:
            q.set_color(glm3(color))
        if ribbon is not None:
            q.set_ribbon_enabled(ribbon)


def register_surface_mesh(name, vertices, faces, enabled=None, color=None, edge_color=None, smooth_shade=None, 
                          edge_width=None, material=None, back_face_policy=None, back_face_color=None, transparency=None):
    """Register a new surface mesh"""

    if not psb.isInitialized():
        raise RuntimeError("Polyscope has not been initialized")
    
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
    if back_face_policy is not None:
        p.set_back_face_policy(back_face_policy)
    if back_face_color is not None:
        p.set_back_face_color(back_face_color)
    if transparency is not None:
        p.set_transparency(transparency)

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
    
