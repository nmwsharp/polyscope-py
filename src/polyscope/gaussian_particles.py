import sys
from typing import Any, Literal, overload, cast

import polyscope_bindings as psb
from polyscope.core import glm3, get_view_camera_parameters, get_view_projection_mode, update_scene_extents
from polyscope.enums import to_enum, from_enum
from polyscope.structure import Structure

import numpy as np
from numpy.typing import NDArray, ArrayLike

if sys.version_info >= (3, 11):
    from typing import Unpack
else:
    from typing_extensions import Unpack


def check_have_dependencies():
    try:
        import gsplat
    except ImportError:
        raise ImportError("gsplat package is required for Gaussian particles. Try `pip install gsplat`")

    try:
        import torch
    except ImportError:
        raise ImportError(
            "pytorch package is required for Gaussian particles. See https://pytorch.org/. It is a requred dependency of gsplat, so you should have gotten it when installing gsplat."
        )


class GaussianParticles(Structure):
    # This class wraps a _reference_ to the underlying object, whose lifetime is managed by Polyscope
    # (although, GaussianParticles is a bit different from other structures in that the underlying data is not owned on the C++ side, it's own here in the Python side)
    bound_instance: psb.GaussianParticles
    device : str

    @overload
    def __init__(self, name: str, points: ArrayLike) -> None: ...

    # End users should not call this constrctor, use register_point_cloud instead
    def __init__(
        self,
        name: str | None = None,
        instance: psb.GaussianParticles | None = None,
        **gaussian_particles_kwargs: Any
    ) -> None:
        super().__init__()

        if instance is not None:
            # Wrap an existing instance
            self.bound_instance = instance

        else:
            # Create a new instance
            assert name is not None
            self.validate_gaussian_kwargs(**gaussian_particles_kwargs)
            self.gaussian_particles_kwargs = gaussian_particles_kwargs

            self.bound_instance = psb.register_gaussian_particles(name, self.draw, self.structure_extents_callback, self.structure_deletion_callback)
            self.bound_instance.update_object_space_bounds()  # call this manually to avoid a circular problem 
            update_scene_extents()

        self.device = "cuda"

    def check_shape(self, points: NDArray) -> None:
        # Helper to validate arrays

        if (len(points.shape) != 2) or (points.shape[1] not in (2, 3)):
            raise ValueError("Point cloud positions should have shape (N,3); shape is " + str(points.shape))
        
    def validate_gaussian_kwargs(self, **kwargs) -> None:

        if "means" not in kwargs:
            raise ValueError("missing required argument 'means'")
        
        if "colors" not in kwargs:
            raise ValueError("missing required argument 'colors'")

        for key in ["viewmats", "Ks", "width", "height", "render_mode"]:
            if key in kwargs:
                raise ValueError(f"don't pass {key} as a kwarg for gsplat, it is set internally by polyscope to render")
    
    def structure_extents_callback(self):
        """
        Used to update the bounding boxes on the internal Polyscope structure
        """

        centers = self.gaussian_particles_kwargs["means"].cpu().numpy().reshape(-1, 3)

        # 25th percentile bbox for some robustness to outliers
        min_bound = np.percentile(centers, 25, axis=0)
        max_bound = np.percentile(centers, 75, axis=0)

        self.bound_instance.set_extents(glm3(min_bound), glm3(max_bound))

    def structure_deletion_callback(self):
        """
        Gets called when the underlying C++ structure is deleted, which can happen if the user calls remove_gaussian_particles, or if they call remove_everything or shutdown.
        """
        name = self.bound_instance.name
        if name in gaussian_particles_instance_cache and gaussian_particles_instance_cache[name] is self:
            del gaussian_particles_instance_cache[name]

    def n_particles(self) -> int:
        return self.bound_instance.n_particles()

    def draw(self):
        import gsplat, torch

        # print("drawing gaussian particles!")

        color_buffer = self.get_buffer("colors")
        depth_buffer = self.get_buffer("depths")

        if get_view_projection_mode() != "perspective":
            raise NotImplementedError("gaussian particles currently only support perspective projection")

        with torch.no_grad():

            render_w, render_h = self.bound_instance.get_render_dims()
            view_params = get_view_camera_parameters()
            T_camera_convent = np.array([
                [1., 0., 0., 0.],
                [0., -1., 0., 0.],  
                [0., 0., -1., 0.],
                [0., 0., 0., 1.],
            ], dtype=np.float32)

            view_mat = torch.tensor(T_camera_convent @ view_params.get_view_mat(), device=self.device)
            fov_height = np.deg2rad(view_params.get_fov_vertical_deg())
            fov_width = 2.0 * np.arctan(np.tan(fov_height / 2.0) * view_params.get_aspect())
            f_x = render_w / (2.0 * np.tan(fov_width / 2.0))
            f_y = render_h / (2.0 * np.tan(fov_height / 2.0))
            proj_mat = torch.tensor([
                [f_x, 0., render_w / 2.0],
                [0., f_y, render_h / 2.0],
                [0., 0., 1.],
            ], dtype=torch.float32, device=self.device)

            render_color, render_alpha, aux = gsplat.rasterization(
                **self.gaussian_particles_kwargs,
                viewmats=view_mat[None,None,...],
                Ks=proj_mat[None,None,...],
                width=render_w,
                height=render_h,
                render_mode="RGB+ED",
                sh_degree=0
            )

            # unbatchify
            render_color = render_color[0,...]
            render_alpha = render_alpha[0,...]

            # depth component is extra channel of color
            render_depth = render_color[..., 3]
            render_color = render_color[..., :3]
            render_coloralpha = torch.concatenate((render_color, render_alpha), dim=-1)

            # copy to the image buffer
            color_buffer.update_data_from_device(render_coloralpha.contiguous())
            depth_buffer.update_data_from_device(render_depth.contiguous())


# A cache of instances, keyed on their name.
# For all other structures, we just create new wrapper objects on-demand.
# This one is different, because the data is owned on the Python side, by a persistant instance of the Python class.
# However, we still want to offer the same API, and not force users to manually keep track of the object.
# As such, we maintain a cache of the "wrapper" objects.
gaussian_particles_instance_cache: dict[str, GaussianParticles] = {}


def register_gaussian_particles(
    name: str,
    enabled: bool | None = None,
    transparency: float | None = None,
    **gaussian_particles_kwargs: Any
) -> GaussianParticles:
    """Register a new point cloud"""
    if not psb.is_initialized():
        raise RuntimeError("Polyscope has not been initialized")

    check_have_dependencies()

    p = GaussianParticles(name, **gaussian_particles_kwargs)
    gaussian_particles_instance_cache[name] = p

    # == Apply options
    if enabled is not None:
        p.set_enabled(enabled)
    if transparency is not None:
        p.set_transparency(transparency)

    return p


def remove_gaussian_particles(name: str, error_if_absent: bool = True) -> None:
    """Remove a gaussian particles by name"""
    psb.remove_gaussian_particles(name, error_if_absent)
    del gaussian_particles_instance_cache[name]


def get_gaussian_particles(name: str) -> GaussianParticles:
    """Get gaussian particles by name"""
    if not has_gaussian_particles(name):
        raise ValueError("no gaussian particles with name " + str(name))

    if name not in gaussian_particles_instance_cache:
        # this _should_ always be in sync with the Polyscope C++ structure pool, so if this ever happens something has gone wrong.
        raise RuntimeError("internal error: gaussian particles instance cache is missing an entry for " + str(name))

    return gaussian_particles_instance_cache[name]


def has_gaussian_particles(name: str) -> bool:  #
    """Check if a gaussian particles exists by name"""
    return psb.has_gaussian_particles(name)
