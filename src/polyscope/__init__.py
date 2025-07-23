## Track the __version__ attribute 
try:
    from importlib.metadata import version, PackageNotFoundError
except ImportError:
    # Python < 3.8
    from importlib_metadata import version, PackageNotFoundError

try:
    __version__ = version("polyscope")
except PackageNotFoundError:
    # Package is not installed, fall back to a default
    __version__ = "unknown"

from polyscope.core import *

from polyscope.structure import *
from polyscope.floating_quantities import *
from polyscope.managed_buffer import *
from polyscope.implicit_helpers import *
from polyscope.device_interop import *

from polyscope.surface_mesh import *
from polyscope.point_cloud import *
from polyscope.curve_network import *
from polyscope.volume_mesh import *
from polyscope.volume_grid import *
from polyscope.camera_view import *
from polyscope.global_floating_quantity_structure import *
