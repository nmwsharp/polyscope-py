import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))

import polyscope

import sys
import argparse
import numpy as np
import meshio 

def main():

    parser = argparse.ArgumentParser()

    # Build arguments
    parser.add_argument('mesh', type=str, help='path to a mesh')

    # Parse arguments
    args = parser.parse_args()

    # Load a mesh argument
    # verts, faces = igl.read_triangle_mesh(args.mesh)
    m = meshio.read(args.mesh)
    verts = m.points
    faces = m.cells['triangle']


    ### Polyscope things example

    # Always initialize exactly once
    polyscope.init() 


    ## Examples with a mesh
    if True:
        ps_mesh = polyscope.register_surface_mesh("test mesh", verts, faces)

        # Scalar functions
        ps_mesh.add_vertex_scalar_quantity("X", verts[:,0])
        ps_mesh.add_vertex_scalar_quantity("Y", verts[:,1])

        # Look at them
        polyscope.show() 

        # Clear out the quantities
        ps_mesh.remove_all_quantities()

        # Add another one and look again
        polyscope.get_surface_mesh("test mesh").add_vertex_scalar_quantity("Z", verts[:,2]) # this time, get mesh by name
        polyscope.show() 
        
        # Remove the whole mesh structure
        polyscope.remove_all_structures()



    ## Examples with a point cloud
    if True:
        ps_points = polyscope.register_point_cloud("test points", verts)

        # Scalar functions
        ps_points.add_scalar_quantity("X", verts[:,0])

        # Look at them
        polyscope.show() 

        # Clear out the quantities
        ps_points.remove_all_quantities()

        # Add more and look again
        ps_points.add_scalar_quantity("Y", verts[:,1])
        polyscope.get_point_cloud("test points").add_scalar_quantity("Z", verts[:,2]) # this time, get structure by name
        polyscope.show() 

        # Add some vectors
        vecs = np.random.rand(verts.shape[0], 3) - 0.5 
        polyscope.get_point_cloud("test points").add_vector_quantity("vecs", vecs) 

        # Add some colors
        colors = np.random.rand(verts.shape[0], 3)
        polyscope.get_point_cloud("test points").add_color_quantity("colors", colors) 
    
        # Show 
        polyscope.show() 

        # Remove the whole point cloud structure
        polyscope.remove_all_structures()




    # Back to empty
    polyscope.show() 

if __name__ == '__main__':
    main()
