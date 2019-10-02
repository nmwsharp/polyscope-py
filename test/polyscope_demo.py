import unittest
import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))

import polyscope

import sys
import argparse
import numpy as np
import igl

def main():

    parser = argparse.ArgumentParser()

    # Build arguments
    parser.add_argument('mesh', type=str, help='path to a mesh')

    # Parse arguments
    args = parser.parse_args()

    # Load a mesh argument
    verts, faces = igl.read_triangle_mesh(args.mesh)




    ### Polyscope things
    polyscope.init() 

    ps_mesh = polyscope.register_surface_mesh("test mesh", verts, faces)

    # Scalar functions
    ps_mesh.add_vertex_scalar_quantity("X", verts[:,0])
    ps_mesh.add_vertex_scalar_quantity("Y", verts[:,1])

    # Look at them
    polyscope.show() 
   
    # Add another one and look again
    ps_mesh.add_vertex_scalar_quantity("Z", verts[:,2])
    polyscope.show() 

if __name__ == '__main__':
    main()
