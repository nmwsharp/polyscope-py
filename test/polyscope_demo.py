import os
import sys
import os.path as path

# Path to where the bindings live
sys.path.append(os.path.join(os.path.dirname(__file__), "../build/"))
sys.path.append(os.path.join(os.path.dirname(__file__), "../src/"))

import polyscope
import potpourri3d as pp3d

import sys
import argparse
import numpy as np

def main():

    parser = argparse.ArgumentParser()

    # Build arguments
    parser.add_argument('mesh', type=str, help='path to a mesh')

    # Parse arguments
    args = parser.parse_args()

    # Load a mesh argument
    verts, faces = pp3d.read_mesh(args.mesh)


    ### Polyscope things example

    # Always initialize exactly once
    polyscope.init() 

    polyscope.set_ground_plane_mode("shadow_only")

    ## Examples with a mesh
    if True:
        ps_mesh = polyscope.register_surface_mesh("test mesh", verts, faces, enabled=True)

        # Scalar functions
        ps_mesh.add_scalar_quantity("X", verts[:,0])
        ps_mesh.add_scalar_quantity("Y", verts[:,1])

        # Look at them
        polyscope.show() 

        # Clear out the quantities
        ps_mesh.remove_all_quantities()

        # Add another one and look again
        polyscope.get_surface_mesh("test mesh").add_scalar_quantity("Z", verts[:,2]) # this time, get mesh by name
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
        # ps_points.set_point_radius_quantity("Y")
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


    # Volume mesh examples
    if True:
        verts = np.array([
            [0, 0, 0],
            [1, 0, 0],
            [1, 1, 0],
            [0, 1, 0],
            [0, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [0, 1, 1],
            [1, 1, 1.5]
        ])
        cells = np.array([
          [0, 1, 2, 3, 4, 5, 6, 7],
          [7, 5, 6, 8, -1, -1, -1, -1],
        ])
        ps_vol = polyscope.register_volume_mesh("test volume mesh", verts, mixed_cells=cells)

        ps_vol.set_enabled(False) # disable
        ps_vol.set_enabled() # default is true

        ps_vol.set_color((0.3, 0.6, 0.8)) # rgb triple on [0,1]
        ps_vol.set_interior_color((0.4, 0.7, 0.9))
        ps_vol.set_edge_color((0.8, 0.8, 0.8)) 
        ps_vol.set_edge_width(1.0)
        ps_vol.set_material("wax")

        # alternately:
        polyscope.register_volume_mesh("my mesh2", verts, mixed_cells=cells, enabled=False, 
                                 color=(1., 0., 0.), interior_color=(0., 1., 0.),
                                 edge_color=((0.8, 0.8, 0.8)), edge_width=1.0, 
                                 material='wax')
        polyscope.show()


        verts = np.array([
            [0, 0, 0],
            [1, 0, 0],
            [1, 1, 0],
            [0, 1, 0],
            [0, 0, 1],
            [1, 0, 1],
            [1, 1, 1],
            [0, 1, 1],
            [1, 1, 1.5]
        ])
        cells = np.array([
          [0, 1, 2, 3, 4, 5, 6, 7],
          [7, 5, 6, 8, -1, -1, -1, -1],
        ])
        ps_vol = polyscope.register_volume_mesh("test volume mesh", verts, mixed_cells=cells)

        # ps_vol = polyscope.register_volume_mesh("test volume mesh", verts, tets=cells)

        verts, tets, _ = igl.read_mesh("my_mesh.mesh")
        ps_vol = polyscope.register_volume_mesh("test volume mesh", verts, tets=tets)

        n_vert = verts.shape[0]
        n_cell = tets.shape[0]

        # Scalar functions
        ps_vol.add_scalar_quantity("X", verts[:,0])
        ps_vol.add_scalar_quantity("Y", verts[:,1])
        data = np.random.rand(n_cell)
        ps_vol.add_scalar_quantity("cell val", data, defined_on='cells')

        # Look at them
        polyscope.show() 

        # Clear out the quantities
        ps_vol.remove_all_quantities()

        
        # Remove the whole mesh structure
        polyscope.remove_all_structures()

    # Back to empty
    polyscope.show() 

if __name__ == '__main__':
    main()
