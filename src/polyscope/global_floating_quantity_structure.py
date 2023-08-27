import polyscope_bindings as psb

from polyscope.core import str_to_datatype, str_to_vectortype, glm3, str_to_point_render_mode, point_render_mode_to_str
from polyscope.structure import Structure

class FloatingQuantityStructure(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    def __init__(self):
        super().__init__()
        self.bound_instance = psb.get_global_floating_quantity_structure()

