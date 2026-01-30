## Track the __version__ attribute
from importlib.metadata import version, PackageNotFoundError

try:
    __version__ = version("polyscope")
except PackageNotFoundError:
    # Package is not installed, fall back to a default
    __version__ = "unknown"

## Enums
from polyscope_bindings import (
    NavigateStyle,
    ProjectionMode,
    UpDir,
    FrontDir,
    DataType,
    VectorType,
    ParamCoordsType,
    ParamVizStyle,
    BackFacePolicy,
    LimitFPSMode,
    GroundPlaneMode,
    GroundPlaneHeightMode,
    TransparencyMode,
    CurveNetworkElement,
    MeshElement,
    MeshSelectionMode,
    VolumeMeshElement,
    VolumeGridElement,
    PointRenderMode,
    FilterMode,
    ImageOrigin,
    MeshShadeStyle,
    IsolineStyle,
    ImplicitRenderMode,
    ManagedBufferType,
    DeviceBufferType,
)

from polyscope.enums import *
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

