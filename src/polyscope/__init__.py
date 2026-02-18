## Track the __version__ attribute
from importlib.metadata import version, PackageNotFoundError

try:
    __version__ = version("polyscope")
except PackageNotFoundError:
    # Package is not installed, # noqa F401 fall back to a default
    __version__ = "unknown"

## Enums
from polyscope_bindings import (
    NavigateStyle,  # noqa F401
    ProjectionMode,  # noqa F401
    UpDir,  # noqa F401
    FrontDir,  # noqa F401
    DataType,  # noqa F401
    VectorType,  # noqa F401
    ParamCoordsType,  # noqa F401
    ParamVizStyle,  # noqa F401
    BackFacePolicy,  # noqa F401
    LimitFPSMode,  # noqa F401
    GroundPlaneMode,  # noqa F401
    GroundPlaneHeightMode,  # noqa F401
    TransparencyMode,  # noqa F401
    CurveNetworkElement,  # noqa F401
    MeshElement,  # noqa F401
    MeshSelectionMode,  # noqa F401
    VolumeMeshElement,  # noqa F401
    VolumeGridElement,  # noqa F401
    SparseVolumeGridElement,  # noqa F401
    SparseVolumeGridRenderMode,  # noqa F401
    PointRenderMode,  # noqa F401
    FilterMode,  # noqa F401
    ImageOrigin,  # noqa F401
    MeshShadeStyle,  # noqa F401
    IsolineStyle,  # noqa F401
    ImplicitRenderMode,  # noqa F401
    ManagedBufferType,  # noqa F401
    DeviceBufferType,  # noqa F401
)

# Forward all functions from submodules

from polyscope.enums import *  # noqa F403
from polyscope.core import *  # noqa F403

from polyscope.structure import *  # noqa F403
from polyscope.floating_quantities import *  # noqa F403
from polyscope.managed_buffer import *  # noqa F403
from polyscope.implicit_helpers import *  # noqa F403
from polyscope.device_interop import *  # noqa F403

from polyscope.surface_mesh import *  # noqa F403
from polyscope.point_cloud import *  # noqa F403
from polyscope.curve_network import *  # noqa F403
from polyscope.volume_mesh import *  # noqa F403
from polyscope.volume_grid import *  # noqa F403
from polyscope.sparse_volume_grid import *  # noqa F403
from polyscope.camera_view import *  # noqa F403
from polyscope.global_floating_quantity_structure import *  # noqa F403
