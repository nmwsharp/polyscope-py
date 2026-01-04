import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "src")))
if os.name == 'nt': # if Windows
    # handle default location where VS puts binary
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "Debug")))
else:
    # normal / unix case
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build")))

import polyscope as ps
import polyscope.imgui as psim
from polyscope import imgui as psim
import potpourri3d as pp3d

import sys
import argparse
import numpy as np

import torch as torch

def toNP(arr):
    return arr.detach().cpu().numpy()

def main():

    parser = argparse.ArgumentParser()

    # Build arguments

    # Parse arguments
    args = parser.parse_args()

    device = torch.device('cuda:0')
    #device = torch.device('cpu')
    dtype = torch.float32

    ui_nPts = 10000
    ui_gpu_update = True
    ui_step_size = 0.01

    nPts = ui_nPts
    step_size = ui_step_size
    gpu_update = ui_gpu_update

    pos = torch.zeros((nPts,3), device=device, dtype=dtype)
    ps_pts = None
   
    def reinitialize():
        nonlocal nPts, ui_nPts, step_size, ui_step_size, gpu_update, ui_gpu_update, pos, ps_pts

        nPts = ui_nPts
        step_size = ui_step_size
        gpu_update = ui_gpu_update

        pos = torch.zeros((nPts,3), device=device, dtype=dtype)

        ps_pts = ps.register_point_cloud("points", toNP(pos), point_render_mode='quad')
       
    def step_simulation():
        nonlocal pos

        steps = torch.randn((nPts, 3), dtype=pos.dtype, device=pos.device) * step_size
        pos += steps
    
    def update_viz():
        nonlocal pos

        if gpu_update:
            ps_pts.get_buffer('points').update_data_from_device(pos)

        else:
            ps_pts.update_point_positions(toNP(pos))

    def callback():
        nonlocal ui_nPts, ui_step_size, ui_gpu_update

        _, ui_nPts = psim.InputInt("nPts", ui_nPts)
        _, ui_step_size = psim.InputFloat("step size", ui_step_size)
        _, ui_gpu_update = psim.Checkbox("gpu update", ui_gpu_update)

        # Executed every frame
        if(psim.Button("Re-initialize")):
            reinitialize()

        step_simulation()
        update_viz()


    ps.set_user_callback(callback)

    ps.set_automatically_compute_scene_extents(False)
    ps.set_length_scale(1.)
    low = np.array((-1, -1., -1.)) 
    high = np.array((1., 1., 1.))
    ps.set_bounding_box(low, high)

    # Always initialize exactly once
    ps.init() 

    reinitialize()

    ps.set_ground_plane_mode("shadow_only")

    ps.show() 


if __name__ == '__main__':
    main()
