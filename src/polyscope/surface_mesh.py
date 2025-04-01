import polyscope_bindings as psb
import numpy as np

from polyscope.core import str_to_datatype, str_to_vectortype, str_to_param_coords_type,            \
                           str_to_param_viz_style, str_to_back_face_policy, back_face_policy_to_str,\
                           str_to_image_origin, glm3, enum_to_str, str_to_enum
from polyscope.structure import Structure
from polyscope.common import process_quantity_args, process_scalar_args, process_color_args, process_vector_args, process_texture_map_args, process_parameterization_args, check_all_args_processed, check_is_scalar_image, check_is_image3

class SurfaceMesh(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_surface_mesh instead
    def __init__(self, name=None, vertices=None, faces=None, instance=None):
        
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance
            self.check_shape(vertices)
    
            if isinstance(faces, np.ndarray):
                # Faces is a numpy array
            
                if (len(faces.shape) != 2): raise ValueError("surface mesh face array should have shape (F,D) for some D; shape is " + str(faces.shape))

                if vertices.shape[1] == 3:
                    self.bound_instance = psb.register_surface_mesh(name, vertices, faces) 
                elif vertices.shape[1] == 2:
                    self.bound_instance = psb.register_surface_mesh2D(name, vertices, faces) 

            else:
                # Faces is something else, try to iterate through it to build a list of lists
                faces_copy = []
                for f in faces:
                    f_copy = [v for v in f]
                    faces_copy.append(f_copy)

                if vertices.shape[1] == 3:
                    self.bound_instance = psb.register_surface_mesh_list(name, vertices, faces) 
                elif vertices.shape[1] == 2:
                    self.bound_instance = psb.register_surface_mesh_list2D(name, vertices, faces) 

                        

    def check_shape(self, points):
        # Helper to validate arrays
        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("surface mesh vertex positions should have shape (N,3) or (N,2); shape is " + str(points.shape))
      

    def n_vertices(self):
        return self.bound_instance.n_vertices()
    def n_faces(self):
        return self.bound_instance.n_faces()
    def n_edges(self):
        return self.bound_instance.n_edges()
    def n_halfedges(self):
        return self.bound_instance.n_halfedges()
    def n_corners(self):
        return self.bound_instance.n_corners()


    # Update
    def update_vertex_positions(self, vertices):
        self.check_shape(vertices)
        
        if vertices.shape[1] == 3:
            self.bound_instance.update_vertex_positions(vertices)
        elif vertices.shape[1] == 2:
            self.bound_instance.update_vertex_positions2D(vertices)
        else:
            raise ValueError("bad vertex shape")
    
    # Custom transparency quantity
    def set_transparency_quantity(self, quantity_name):
        self.bound_instance.set_transparency_quantity(quantity_name)
    def clear_transparency_quantity(self):
        self.bound_instance.clear_transparency_quantity()
    
    
    # Picking
    def append_pick_data(self, pick_result):
        struct_result = self.bound_instance.interpret_pick_result(pick_result.raw_result)
        pick_result.structure_data["element_type"] = enum_to_str(struct_result.element_type)
        pick_result.structure_data["index"] = struct_result.index
        bary_coords = np.array(struct_result.bary_coords.as_tuple())
        if not (bary_coords == np.array((-1,-1,-1))).all():
            pick_result.structure_data["bary_coords"] = bary_coords

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
    
    # Smooth shade
    def set_smooth_shade(self, val):
        self.bound_instance.set_smooth_shade(val)
    def get_smooth_shade(self):
        return self.bound_instance.get_smooth_shade()
    
    # Selection Mode
    def set_selection_mode(self, val):
        self.bound_instance.set_selection_mode(str_to_enum(val, psb.MeshSelectionMode))
    def get_selection_mode(self):
        return enum_to_str(self.bound_instance.get_selection_mode())
    
    # Material
    def set_material(self, mat):
        self.bound_instance.set_material(mat)
    def get_material(self):
        return self.bound_instance.get_material()

    # Color
    def set_back_face_policy(self, val):
        self.bound_instance.set_back_face_policy(str_to_back_face_policy(val))
    def get_back_face_policy(self):
        return back_face_policy_to_str(self.bound_instance.get_back_face_policy())
    
    # Back face color
    def set_back_face_color(self, val):
        self.bound_instance.set_back_face_color(glm3(val))
    def get_back_face_color(self):
        return self.bound_instance.get_back_face_color().as_tuple()
    

    def mark_edges_as_used(self):
        self.bound_instance.mark_edges_as_used()
    
    def mark_halfedges_as_used(self):
        self.bound_instance.mark_halfedges_as_used()
    
    def mark_corners_as_used(self):
        self.bound_instance.mark_corners_as_used()

    ## Permutations and bases

    def set_edge_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_edges(): raise ValueError("'perm' should be an array with one entry per edge")
        if expected_size is None: expected_size = 0
        self.bound_instance.set_edge_permutation(perm, expected_size)
    
    def set_corner_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_corners(): raise ValueError("'perm' should be an array with one entry per corner")
        if expected_size is None: expected_size = 0
        self.bound_instance.set_corner_permutation(perm, expected_size)
    
    def set_halfedge_permutation(self, perm, expected_size=None):
        if len(perm.shape) != 1 or perm.shape[0] != self.n_halfedges(): raise ValueError("'perm' should be an array with one entry per halfedge")
        if expected_size is None: expected_size = 0
        self.bound_instance.set_halfedge_permutation(perm, expected_size)
    
    def set_all_permutations(self, 
            vertex_perm=None, vertex_perm_size=None, # now ignored 
            face_perm=None, face_perm_size=None,     # now ignored
            edge_perm=None, edge_perm_size=None,
            corner_perm=None, corner_perm_size=None,
            halfedge_perm=None, halfedge_perm_size=None):

        if edge_perm is not None: self.set_edge_permutation(edge_perm, edge_perm_size)
        if corner_perm is not None: self.set_corner_permutation(corner_perm, corner_perm_size)
        if halfedge_perm is not None: self.set_halfedge_permutation(halfedge_perm, halfedge_perm_size)
    


    ## Quantities

    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='vertices', datatype="standard", param_name=None, image_origin="upper_left", **scalar_args):

        if defined_on != 'texture' and len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_instance.add_face_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'edges':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_instance.add_edge_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'halfedges':
            if values.shape[0] != self.n_halfedges(): raise ValueError("'values' should be a length n_halfedges array")
            q = self.bound_instance.add_halfedge_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'corners':
            if values.shape[0] != self.n_corners(): raise ValueError("'values' should be a length n_corners array")
            q = self.bound_instance.add_corner_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'texture':
            check_is_scalar_image(values)
            dimY = values.shape[0]
            dimX = values.shape[1]
            if not isinstance(param_name, str): 
                raise ValueError("when adding a quantity defined in a texture, you must pass 'param_name' as a string giving the name of a parameterization quantity on this structure, which provides the UV coords")
            q = self.bound_instance.add_texture_scalar_quantity(name, param_name, dimX, dimY, values.flatten(), str_to_image_origin(image_origin), str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces', 'edges', 'halfedges', 'corners', 'texture']".format(defined_on))
            

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, scalar_args)
        process_scalar_args(self, q, scalar_args)
        process_texture_map_args(self, q, scalar_args)
        check_all_args_processed(self, q, scalar_args)

    
    # Color
    def add_color_quantity(self, name, values, defined_on='vertices', param_name=None, image_origin="upper_left", **color_args):
        if defined_on != 'texture' and (len(values.shape) != 2 or values.shape[1] != 3): raise ValueError("'values' should be an Nx3 array")
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_color_quantity(name, values)
        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_instance.add_face_color_quantity(name, values)
        elif defined_on == 'texture':
            check_is_image3(values)
            dimY = values.shape[0]
            dimX = values.shape[1]
            if not isinstance(param_name, str): 
                raise ValueError("when adding a quantity defined in a texture, you must pass 'param_name' as a string giving the name of a parameterization quantity on this structure, which provides the UV coords")
            q = self.bound_instance.add_texture_color_quantity(name, param_name, dimX, dimY, values.reshape(-1,3), str_to_image_origin(image_origin))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces', 'texture']".format(defined_on))


        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, color_args)
        process_color_args(self, q, color_args)
        process_texture_map_args(self, q, color_args)
        check_all_args_processed(self, q, color_args)
    
    
    # Distance
    # [deprecated], this is just a special set of options for a scalar quantity now
    def add_distance_quantity(self, name, values, defined_on='vertices', enabled=None, signed=False, vminmax=None, stripe_size=None, stripe_size_relative=True, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")

            if signed:
                q = self.bound_instance.add_vertex_signed_distance_quantity(name, values)
            else:
                q = self.bound_instance.add_vertex_distance_quantity(name, values)
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
    def add_parameterization_quantity(self, name, values, defined_on='vertices', coords_type='unit', **parameterization_args):

        if len(values.shape) != 2 or values.shape[1] != 2: raise ValueError("'values' should be an (Nx2) array")

        # parse the coords type in to an enum
        coords_type_enum = str_to_param_coords_type(coords_type)

        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            q = self.bound_instance.add_vertex_parameterization_quantity(name, values, coords_type_enum)
        elif defined_on == 'corners':
            if values.shape[0] != self.n_corners(): raise ValueError("'values' should be a length n_faces array")
            q = self.bound_instance.add_corner_parameterization_quantity(name, values, coords_type_enum)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'corners']".format(defined_on))
            
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, parameterization_args)
        process_parameterization_args(self, q, parameterization_args)
        check_all_args_processed(self, q, parameterization_args)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='vertices', vectortype="standard", **vector_args):
        if len(values.shape) != 2 or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")

            if values.shape[1] == 2:
                q = self.bound_instance.add_vertex_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_instance.add_vertex_vector_quantity(name, values, str_to_vectortype(vectortype))

        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            
            if values.shape[1] == 2:
                q = self.bound_instance.add_face_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_instance.add_face_vector_quantity(name, values, str_to_vectortype(vectortype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))

        
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)
    
    
    def add_tangent_vector_quantity(self, name, values, basisX, basisY, n_sym=1, defined_on='vertices', vectortype="standard", **vector_args):

        if len(values.shape) != 2 or values.shape[1] != 2: raise ValueError("'values' should be an Nx2 array")
        if len(basisX.shape) != 2 or basisX.shape[1] != 3: raise ValueError("'basisX' should be an Nx3 array")
        if len(basisY.shape) != 2 or basisY.shape[1] != 3: raise ValueError("'basisY' should be an Nx3 array")
        
        
        if defined_on == 'vertices':
            if values.shape[0] != self.n_vertices(): raise ValueError("'values' should be a length n_vertices array")
            if basisX.shape[0] != self.n_vertices(): raise ValueError("'basisX' should be a length n_vertices array")
            if basisY.shape[0] != self.n_vertices(): raise ValueError("'basisY' should be a length n_vertices array")

            q = self.bound_instance.add_vertex_tangent_vector_quantity(name, values, basisX, basisY, n_sym, str_to_vectortype(vectortype))

        elif defined_on == 'faces':
            if values.shape[0] != self.n_faces(): raise ValueError("'values' should be a length n_faces array")
            if basisX.shape[0] != self.n_faces(): raise ValueError("'basisX' should be a length n_faces array")
            if basisY.shape[0] != self.n_faces(): raise ValueError("'basisY' should be a length n_faces array")
            
            q = self.bound_instance.add_face_tangent_vector_quantity(name, values, basisX, basisY, n_sym, str_to_vectortype(vectortype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['vertices', 'faces']".format(defined_on))

        
        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)
    
    
    def add_one_form_vector_quantity(self, name, values, orientations, **vector_args):

        if len(values.shape) != 1 or values.shape[0] != self.n_edges(): raise ValueError("'values' should be length n_edges array")
        if len(orientations.shape) != 1 or orientations.shape[0] != self.n_edges(): raise ValueError("'orientations' should be length n_edges array")

        q = self.bound_instance.add_one_form_tangent_vector_quantity(name, values, orientations)

        # process and act on additional arguments
        # note: each step modifies the args dict and removes processed args
        process_quantity_args(self, q, vector_args)
        process_vector_args(self, q, vector_args)
        check_all_args_processed(self, q, vector_args)



def register_surface_mesh(name, vertices, faces, enabled=None, color=None, edge_color=None, smooth_shade=None, 
                          edge_width=None, material=None, back_face_policy=None, back_face_color=None, transparency=None):
    """Register a new surface mesh"""

    if not psb.is_initialized():
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
    
