import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3

class CurveNetwork:

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    # End users should not call this constrctor, use register_curve_network instead
    def __init__(self, name=None, nodes=None, edges=None, instance=None):

        if instance is not None:
            # Wrap an existing instance
            self.bound_network = instance

        else:
            # Create a new instance
            self.check_shape(nodes)

            if isinstance(edges, str): 
                # Special case: edges as a string key

                if edges not in ['line', 'loop']: raise ValueError("bad edges setting, if not numpy array must be in 'line' or 'loop', got " + str(edges))

                if nodes.shape[1] == 3:
                    if edges == 'line':
                        self.bound_network = psb.register_curve_network_line(name, nodes)
                    elif edges == 'loop':
                        self.bound_network = psb.register_curve_network_loop(name, nodes)
                elif nodes.shape[1] == 2:
                    if edges == 'line':
                        self.bound_network = psb.register_curve_network_line2D(name, nodes)
                    elif edges == 'loop':
                        self.bound_network = psb.register_curve_network_loop2D(name, nodes)
            else:
                # Common case: process edges as numpy array

                if (len(edges.shape) != 2) or (edges.shape[1] != 2):
                    raise ValueError("curve network edges should have shape (N_edge,2); shape is " + str(edges.shape))

                if nodes.shape[1] == 3:
                    self.bound_network = psb.register_curve_network(name, nodes, edges) 
                elif nodes.shape[1] == 2:
                    self.bound_network = psb.register_curve_network2D(name, nodes, edges) 

    def check_shape(self, points):
        # Helper to validate arrays
        if (len(points.shape) != 2) or (points.shape[1] not in (2,3)):
            raise ValueError("curve network node positions should have shape (N,3); shape is " + str(points.shape))
       
    def n_nodes(self):
        return self.bound_network.n_nodes()
    def n_edges(self):
        return self.bound_network.n_edges()


    ## Structure management
    
    def remove(self):
        '''Remove the structure itself'''
        self.bound_network.remove()
    def remove_all_quantities(self):
        '''Remove all quantities on the structure'''
        self.bound_network.remove_all_quantities()
    def remove_quantity(self, name):
        '''Remove a single quantity on the structure'''
        self.bound_network.remove_quantity(name)

    # Enable/disable
    def set_enabled(self, val=True):
        self.bound_network.set_enabled(val)
    def is_enabled(self):
        return self.bound_network.is_enabled()
    
    # Transparency
    def set_transparency(self, val):
        self.bound_network.set_transparency(val)
    def get_transparency(self):
        return self.bound_network.get_transparency()
    
    # Transformation things
    def center_bounding_box(self):
        self.bound_network.center_bounding_box()
    def rescale_to_unit(self):
        self.bound_network.rescale_to_unit()
    def reset_transform(self):
        self.bound_network.reset_transform()
    def set_transform(self, new_mat4x4):
        self.bound_network.set_transform(new_mat4x4)
    def set_position(self, new_vec3):
        self.bound_network.set_position(new_vec3)
    def translate(self, trans_vec3):
        self.bound_network.translate(trans_vec3)
    def get_transform(self):
        return self.bound_network.get_transform()
    def get_position(self):
        return self.bound_network.get_position()
    
    # Slice planes
    def set_cull_whole_elements(self, val):
        self.bound_network.set_cull_whole_elements(val)
    def get_cull_whole_elements(self):
        return self.bound_network.get_cull_whole_elements()
    def set_ignore_slice_plane(self, plane, val):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            self.bound_network.set_ignore_slice_plane(plane, val)
        else:
            self.bound_network.set_ignore_slice_plane(plane.get_name(), val)
    def get_ignore_slice_plane(self, plane):
        # take either a string or a slice plane object as input
        if isinstance(plane, str):
            return self.bound_network.get_ignore_slice_plane(plane)
        else:
            return self.bound_network.get_ignore_slice_plane(plane.get_name())

    # Update
    def update_node_positions(self, nodes):
        self.check_shape(nodes)
        
        if nodes.shape[1] == 3:
            self.bound_network.update_node_positions(nodes)
        elif nodes.shape[1] == 2:
            self.bound_network.update_node_positions2D(nodes)
        else:
            raise ValueError("bad node shape")

    ## Options
   
    # Radius
    def set_radius(self, rad, relative=True):
        self.bound_network.set_radius(rad, relative)
    def get_radius(self):
        return self.bound_network.get_radius()
    
    # Color
    def set_color(self, val):
        self.bound_network.set_color(glm3(val))
    def get_color(self):
        return self.bound_network.get_color().as_tuple()
    
    # Material
    def set_material(self, mat):
        self.bound_network.set_material(mat)
    def get_material(self):
        return self.bound_network.get_material()


    ## Quantities
       
    # Scalar
    def add_scalar_quantity(self, name, values, defined_on='nodes', enabled=None, datatype="standard", vminmax=None, cmap=None):

        if len(values.shape) != 1: raise ValueError("'values' should be a length-N array")

        if defined_on == 'nodes':
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_network.add_node_scalar_quantity(name, values, str_to_datatype(datatype))
        elif defined_on == 'edges':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_network.add_edge_scalar_quantity(name, values, str_to_datatype(datatype))
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))
            

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if vminmax is not None:
            q.set_map_range(vminmax)
        if cmap is not None:
            q.set_color_map(cmap)
    
    
    # Color
    def add_color_quantity(self, name, values, defined_on='nodes', enabled=None):
        if len(values.shape) != 2 or values.shape[1] != 3: raise ValueError("'values' should be an Nx3 array")
            
        
        if defined_on == 'nodes':
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")
            q = self.bound_network.add_node_color_quantity(name, values)
        elif defined_on == 'edges':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            q = self.bound_network.add_edge_color_quantity(name, values)
        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
    
    
    # Vector
    def add_vector_quantity(self, name, values, defined_on='nodes', enabled=None, vectortype="standard", length=None, radius=None, color=None):
        if len(values.shape) != 2 or values.shape[1] not in [2,3]: raise ValueError("'values' should be an Nx3 array (or Nx2 for 2D)")
        
        
        if defined_on == 'nodes':
            if values.shape[0] != self.n_nodes(): raise ValueError("'values' should be a length n_nodes array")

            if values.shape[1] == 2:
                q = self.bound_network.add_node_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_network.add_node_vector_quantity(name, values, str_to_vectortype(vectortype))

        elif defined_on == 'edges':
            if values.shape[0] != self.n_edges(): raise ValueError("'values' should be a length n_edges array")
            
            if values.shape[1] == 2:
                q = self.bound_network.add_edge_vector_quantity2D(name, values, str_to_vectortype(vectortype))
            elif values.shape[1] == 3:
                q = self.bound_network.add_edge_vector_quantity(name, values, str_to_vectortype(vectortype))

        else:
            raise ValueError("bad `defined_on` value {}, should be one of ['nodes', 'edges']".format(defined_on))

        # Support optional params
        if enabled is not None:
            q.set_enabled(enabled)
        if length is not None:
            q.set_length(length, True)
        if radius is not None:
            q.set_radius(radius, True)
        if color is not None:
            q.set_color(glm3(color))


def register_curve_network(name, nodes, edges, enabled=None, radius=None, color=None, material=None, transparency=None):
    """Register a new curve network"""
    if not psb.isInitialized():
        raise RuntimeError("Polyscope has not been initialized")
    
    p = CurveNetwork(name, nodes, edges)

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if radius is not None:
        p.set_radius(radius)
    if color is not None:
        p.set_color(color)
    if material is not None:
        p.set_material(material)
    if transparency is not None:
        p.set_transparency(transparency)

    return p

def remove_curve_network(name, error_if_absent=True):
    """Remove a curve network by name"""
    psb.remove_curve_network(name, error_if_absent)

def get_curve_network(name):
    """Get curve network by name"""
    if not has_curve_network(name):
        raise ValueError("no curve network with name " + str(name))

    raw = psb.get_curve_network(name)

    # Wrap the instance
    return CurveNetwork(instance=raw)

def has_curve_network(name):
    """Check if a curve network exists by name"""
    return psb.has_curve_network(name)
    
