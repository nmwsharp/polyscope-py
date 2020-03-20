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


def register_curve_network(name, nodes, edges, enabled=None, radius=None, color=None, material=None):
    """Register a new curve network"""

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
    
