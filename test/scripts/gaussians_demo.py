import torch
import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "src")))
if os.name == 'nt': # if Windows
    # handle default location where VS puts binary
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "build", "Debug")))
else:
    # normal / unix case
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "build")))


import polyscope as ps
import polyscope.imgui as psim
from polyscope import imgui as psim

import sys
import argparse
import numpy as np
from plyfile import PlyData


def load_gaussians_from_ply(path_ply, device='cuda'):

    plydata = PlyData.read(path_ply)

    centers = np.stack((np.asarray(plydata.elements[0]["x"]),
                    np.asarray(plydata.elements[0]["y"]),
                    np.asarray(plydata.elements[0]["z"])),  axis=1)
    opacities = np.asarray(plydata.elements[0]["opacity"])

    features_dc = np.zeros((centers.shape[0], 3, 1))
    features_dc[:, 0, 0] = np.asarray(plydata.elements[0]["f_dc_0"])
    features_dc[:, 1, 0] = np.asarray(plydata.elements[0]["f_dc_1"])
    features_dc[:, 2, 0] = np.asarray(plydata.elements[0]["f_dc_2"])

    extra_f_names = [p.name for p in plydata.elements[0].properties if p.name.startswith("f_rest_")]
    extra_f_names = sorted(extra_f_names, key = lambda x: int(x.split('_')[-1]))
    features_extra = np.zeros((centers.shape[0], len(extra_f_names)))
    for idx, attr_name in enumerate(extra_f_names):
        features_extra[:, idx] = np.asarray(plydata.elements[0][attr_name])

    scale_names = [p.name for p in plydata.elements[0].properties if p.name.startswith("scale_")]
    scale_names = sorted(scale_names, key = lambda x: int(x.split('_')[-1]))
    scales = np.zeros((centers.shape[0], len(scale_names)))
    for idx, attr_name in enumerate(scale_names):
        scales[:, idx] = np.asarray(plydata.elements[0][attr_name])

    rot_names = [p.name for p in plydata.elements[0].properties if p.name.startswith("rot")]
    rot_names = sorted(rot_names, key = lambda x: int(x.split('_')[-1]))
    rots = np.zeros((centers.shape[0], len(rot_names)))
    for idx, attr_name in enumerate(rot_names):
        rots[:, idx] = np.asarray(plydata.elements[0][attr_name])

    with torch.no_grad():
        centers = torch.tensor(centers, dtype=torch.float, device=device,)
        features_dc = torch.tensor(features_dc, dtype=torch.float, device=device).transpose(1, 2).contiguous()
        # features_rest = torch.tensor(features_extra, dtype=torch.float, device=device).transpose(1, 2).contiguous()
        opacity = torch.tensor(opacities, dtype=torch.float, device=device)
        scaling = torch.tensor(scales, dtype=torch.float, device=device)
        rotation = torch.tensor(rots, dtype=torch.float, device=device)


    # apply activations
    # (assumes the file holds pre-activated values)
    opacity = torch.sigmoid(opacity)
    scaling = torch.exp(scaling)

    return centers, features_dc, opacity, scaling, rotation

def main():

    parser = argparse.ArgumentParser()

    # Build arguments
    parser.add_argument('--gaussian_ply', type=str, help='path to a .ply file')

    # Parse arguments
    args = parser.parse_args()


    ps.init()
    ps.set_ground_plane_mode("none")

    # Load the file
    centers, features_dc, opacity, scaling, rotation = load_gaussians_from_ply(args.gaussian_ply)
    print(f"Loaded {centers.shape[0]} gaussian particles")

    # Register Gaussians
    ps.register_gaussian_particles("gaussians",
                                   subsample_factor=2, # set to >1 for fast rendering at lower resolution
                                   # the arguments below are passed directly
                                   # to gsplat.rasterization(...). See the docs there for the meaning
                                   # and other parameters you can pass.
                                   means=centers.unsqueeze(0),
                                   colors=features_dc.unsqueeze(0),
                                   opacities=opacity.unsqueeze(0),
                                   scales=scaling.unsqueeze(0),
                                   quats=rotation.unsqueeze(0),
                                   sh_degree=0,
                                )

    ps.show()


if __name__ == '__main__':
    main()
