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

import polyscope
import polyscope.imgui as psim
from polyscope import imgui as psim
import potpourri3d as pp3d
import igl
import imageio

import sys
import argparse
import numpy as np

# Helper funcs for defining implicits
def sphere_sdf(pts):
    res = np.linalg.norm(pts, axis=-1) - 1.
    return res
def color_func(pts):
    # return np.cos(3*pts)**2
    A = np.ones_like(pts) * 0.3
    A[:,0] = np.cos(3*pts[:,0])**2
    return A

is_test_clicking = False

def main():

    parser = argparse.ArgumentParser()

    # Build arguments
    parser.add_argument('--mesh', type=str, help='path to a mesh')
    parser.add_argument('--image', type=str, help='path to a image')
    parser.add_argument('--pointcloud', default=False, action='store_true')
    parser.add_argument('--volumemesh', default=False, action='store_true')
    parser.add_argument('--volumegrid', default=False, action='store_true')

    # Parse arguments
    args = parser.parse_args()



    # Set up a simple callback and UI button
    def my_function():
        pass

    def callback():
        # Executed every frame

        global is_test_clicking

        if is_test_clicking:
            if(psim.Button("Cancel")):
                is_test_clicking = False

            io = psim.GetIO()
            if io.MouseClicked[0]:
                screen_coords = io.MousePos
                pick_result = polyscope.pick(screen_coords=screen_coords)
                print(pick_result)
                is_test_clicking = False

        if(psim.Button("Test button")):
            my_function()

        implicit_ui()

        if(psim.Button("Test pick")):
            is_test_clicking = True


    polyscope.set_user_callback(callback)
   

    ### Polyscope things example

    # Always initialize exactly once
    polyscope.init() 

    # polyscope.set_ground_plane_mode("shadow_only")
    polyscope.set_verbosity(101)

    ## Examples with a mesh
    if args.mesh:
        # Load a mesh argument
        verts, faces = pp3d.read_mesh(args.mesh)

        corner_UVs = None 
        # verts, UVs, _, faces, UVinds, _ = igl.read_obj(args.mesh)
        # corner_UVs = UVs[UVinds,:].reshape(-1,2)
        # print(corner_UVs.shape)
        # 
        # color_tex = imageio.imread(args.image) / 255.
        # print(color_tex.shape)
        # print(UVs[:10,:])

        ps_mesh = polyscope.register_surface_mesh("test mesh", verts, faces, enabled=True)

        # Scalar functions
        ps_mesh.add_scalar_quantity("X", verts[:,0])
        ps_mesh.add_scalar_quantity("Y", verts[:,1])

        if corner_UVs is not None:
            ps_mesh.add_parameterization_quantity("param", corner_UVs, defined_on='corners')
            ps_mesh.add_color_quantity("color_tex", color_tex, defined_on='texture', param_name="param", image_origin='upper_left')
            ps_mesh.add_scalar_quantity("scalar_tex", color_tex[:,:,1], defined_on='texture', param_name="param")
            polyscope.add_color_image_quantity("my im", color_tex)

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
    if args.pointcloud:
        ps_points = polyscope.register_point_cloud("test points", verts, point_render_mode='sphere')

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
    if args.volumemesh:
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
        
    
    if args.volumegrid:

        # Any implicit function mapping [N,3] numpy array 
        # of locations --> [N] numpy array of values
        def sphere_sdf(pts):
            res = np.linalg.norm(pts, axis=-1) - 1.
            return res

        # Create the grid structure
        bound_min = np.array([-1., -1., -1.])
        bound_max = np.array([+1., +1., +1.])
        node_dims = np.array([128,128,128])
        ps_grid = polyscope.register_volume_grid("test volume grid", bound_min, bound_max, node_dims)

        # This makes polyscope register the scalar quantity by calling 
        # your function for each point on the grid (so you don't have 
        # to worry about getting indexing right)
        ps_grid.add_scalar_quantity_from_callable("sdf", sphere_sdf)

        polyscope.show()

    # Back to empty
    polyscope.show() 

    # polyscope.clear_user_callback()


def implicit_ui():

    if(psim.Button("Render sphere SDF")):
        # polyscope.render_implicit_surface("sphere sdf", sphere_sdf, 'sphere_march', enabled=True)
        polyscope.render_implicit_surface_color("sphere sdf", sphere_sdf, color_func, 'sphere_march', enabled=True)



if __name__ == '__main__':
    main()
