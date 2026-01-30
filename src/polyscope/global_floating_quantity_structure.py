import polyscope_bindings as psb

from polyscope.structure import Structure

class FloatingQuantityStructure(Structure):

    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope

    def __init__(self):
        super().__init__()
        self.bound_instance = psb.get_global_floating_quantity_structure()

