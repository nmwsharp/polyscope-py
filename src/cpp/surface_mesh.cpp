#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;


void bind_surface_mesh(py::module& m) {


  // == Helper quantity classes

  // Scalar quantities
  bindScalarQuantity<ps::SurfaceVertexScalarQuantity>(m, "SurfaceVertexScalarQuantity");
  bindScalarQuantity<ps::SurfaceFaceScalarQuantity>(m, "SurfaceFaceScalarQuantity");
  bindScalarQuantity<ps::SurfaceEdgeScalarQuantity>(m, "SurfaceEdgeScalarQuantity");
  bindScalarQuantity<ps::SurfaceHalfedgeScalarQuantity>(m, "SurfaceHalfedgeScalarQuantity");

  // Color quantities
  bindColorQuantity<ps::SurfaceVertexColorQuantity>(m, "SurfaceVertexColorQuantity");
  bindColorQuantity<ps::SurfaceFaceColorQuantity>(m, "SurfaceFaceColorQuantity");

  // Parameterization quantities
  py::class_<ps::SurfaceCornerParameterizationQuantity>(m, "SurfaceCornerParameterizationQuantity")
      .def("set_enabled", &ps::SurfaceCornerParameterizationQuantity::setEnabled, "Set enabled")
      .def("set_style", &ps::SurfaceCornerParameterizationQuantity::setStyle, "Set style")
      .def("set_grid_colors", &ps::SurfaceCornerParameterizationQuantity::setGridColors, "Set grid colors")
      .def("set_checker_colors", &ps::SurfaceCornerParameterizationQuantity::setCheckerColors, "Set checker colors")
      .def("set_checker_size", &ps::SurfaceCornerParameterizationQuantity::setCheckerSize, "Set checker size")
      .def("set_color_map", &ps::SurfaceCornerParameterizationQuantity::setColorMap, "Set color map");
  py::class_<ps::SurfaceVertexParameterizationQuantity>(m, "SurfaceVertexParameterizationQuantity")
      .def("set_enabled", &ps::SurfaceVertexParameterizationQuantity::setEnabled, "Set enabled")
      .def("set_style", &ps::SurfaceVertexParameterizationQuantity::setStyle, "Set style")
      .def("set_grid_colors", &ps::SurfaceVertexParameterizationQuantity::setGridColors, "Set grid colors")
      .def("set_checker_colors", &ps::SurfaceVertexParameterizationQuantity::setCheckerColors, "Set checker colors")
      .def("set_checker_size", &ps::SurfaceVertexParameterizationQuantity::setCheckerSize, "Set checker size")
      .def("set_color_map", &ps::SurfaceVertexParameterizationQuantity::setColorMap, "Set color map");

  // Vector quantities
  bindVectorQuantity<ps::SurfaceVertexVectorQuantity>(m, "SurfaceVertexVectorQuantity");
  bindVectorQuantity<ps::SurfaceFaceVectorQuantity>(m, "SurfaceFaceVectorQuantity");
  bindVectorQuantity<ps::SurfaceVertexIntrinsicVectorQuantity>(m, "SurfaceVertexIntrinsicVectorQuantity")
      .def("set_ribbon_enabled", &ps::SurfaceVertexIntrinsicVectorQuantity::setEnabled, "Set ribbon enabled");
  bindVectorQuantity<ps::SurfaceFaceIntrinsicVectorQuantity>(m, "SurfaceFaceIntrinsicVectorQuantity")
      .def("set_ribbon_enabled", &ps::SurfaceFaceIntrinsicVectorQuantity::setEnabled, "Set ribbon enabled");
  bindVectorQuantity<ps::SurfaceOneFormIntrinsicVectorQuantity>(m, "SurfaceOneFormIntrinsicVectorQuantity")
      .def("set_ribbon_enabled", &ps::SurfaceOneFormIntrinsicVectorQuantity::setEnabled, "Set ribbon enabled");


  // == Main class
  py::class_<ps::SurfaceMesh>(m, "SurfaceMesh")

      // basics
      .def("remove", &ps::SurfaceMesh::remove, "Remove the structure")
      .def("set_enabled", &ps::SurfaceMesh::setEnabled, "Enable the structure")
      .def("is_enabled", &ps::SurfaceMesh::isEnabled, "Check if the structure is enabled")
      .def("set_transparency", &ps::SurfaceMesh::setTransparency, "Set transparency alpha")
      .def("get_transparency", &ps::SurfaceMesh::getTransparency, "Get transparency alpha")
      .def("remove_all_quantities", &ps::SurfaceMesh::removeAllQuantities, "Remove all quantities")
      .def("remove_quantity", &ps::SurfaceMesh::removeQuantity, "Remove a quantity")
      .def("update_vertex_positions", &ps::SurfaceMesh::updateVertexPositions<Eigen::MatrixXd>,
           "Update vertex positions")
      .def("update_vertex_positions2D", &ps::SurfaceMesh::updateVertexPositions2D<Eigen::MatrixXd>,
           "Update vertex positions")
      .def("n_vertices", &ps::SurfaceMesh::nVertices, "# vertices")
      .def("n_faces", &ps::SurfaceMesh::nFaces, "# edges")
      .def("n_edges", &ps::SurfaceMesh::nEdges, "# edges")
      .def("n_corners", &ps::SurfaceMesh::nCorners, "# corners")
      .def("n_halfedges", &ps::SurfaceMesh::nHalfedges, "# halfedges")

      // options
      .def("set_color", &ps::SurfaceMesh::setSurfaceColor, "Set surface color")
      .def("get_color", &ps::SurfaceMesh::getSurfaceColor, "Get surface color")
      .def("set_edge_color", &ps::SurfaceMesh::setEdgeColor, "Set edge color")
      .def("get_edge_color", &ps::SurfaceMesh::getEdgeColor, "Get edge color")
      .def("set_edge_width", &ps::SurfaceMesh::setEdgeWidth, "Set edge width")
      .def("get_edge_width", &ps::SurfaceMesh::getEdgeWidth, "Get edge width")
      .def("set_smooth_shade", &ps::SurfaceMesh::setSmoothShade, "Set smooth shading")
      .def("get_smooth_shade", &ps::SurfaceMesh::isSmoothShade, "Get if smooth shading is enabled")
      .def("set_material", &ps::SurfaceMesh::setMaterial, "Set material")
      .def("get_material", &ps::SurfaceMesh::getMaterial, "Get material")
      .def("set_back_face_policy", &ps::SurfaceMesh::setBackFacePolicy, "Set back face policy")
      .def("get_back_face_policy", &ps::SurfaceMesh::getBackFacePolicy, "Get back face policy")
      .def("set_back_face_color", &ps::SurfaceMesh::setBackFaceColor, "Set back face color")
      .def("get_back_face_color", &ps::SurfaceMesh::getBackFaceColor, "Get back face color")

      // slice planes
      .def("set_ignore_slice_plane", &ps::SurfaceMesh::setIgnoreSlicePlane, "Set ignore slice plane")
      .def("get_ignore_slice_plane", &ps::SurfaceMesh::getIgnoreSlicePlane, "Get ignore slice plane")
      .def("set_cull_whole_elements", &ps::SurfaceMesh::setCullWholeElements, "Set cull whole elements")
      .def("get_cull_whole_elements", &ps::SurfaceMesh::getCullWholeElements, "Get cull whole elements")
     

      // permutations & bases
      .def("set_vertex_permutation", &ps::SurfaceMesh::setVertexPermutation<Eigen::VectorXi>, "Set vertex permutation")
      .def("set_face_permutation", &ps::SurfaceMesh::setFacePermutation<Eigen::VectorXi>, "Set face permutation")
      .def("set_edge_permutation", &ps::SurfaceMesh::setEdgePermutation<Eigen::VectorXi>, "Set edge permutation")
      .def("set_halfedge_permutation", &ps::SurfaceMesh::setHalfedgePermutation<Eigen::VectorXi>,
           "Set halfedge permutation")
      .def("set_corner_permutation", &ps::SurfaceMesh::setCornerPermutation<Eigen::VectorXi>, "Set corner permutation")
      .def("set_vertex_tangent_basisX", &ps::SurfaceMesh::setVertexTangentBasisX<Eigen::MatrixXd>,
           "Set vertex tangent bases")
      .def("set_vertex_tangent_basisX2D", &ps::SurfaceMesh::setVertexTangentBasisX2D<Eigen::MatrixXd>,
           "Set vertex tangent bases")
      .def("set_face_tangent_basisX", &ps::SurfaceMesh::setFaceTangentBasisX<Eigen::MatrixXd>, "Set face tangent bases")
      .def("set_face_tangent_basisX2D", &ps::SurfaceMesh::setFaceTangentBasisX2D<Eigen::MatrixXd>,
           "Set face tangent bases")

      // = quantities

      // Scalars
      .def("add_vertex_scalar_quantity", &ps::SurfaceMesh::addVertexScalarQuantity<Eigen::VectorXd>,
           "Add a scalar function at vertices", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_face_scalar_quantity", &ps::SurfaceMesh::addFaceScalarQuantity<Eigen::VectorXd>,
           "Add a scalar function at faces", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_edge_scalar_quantity", &ps::SurfaceMesh::addEdgeScalarQuantity<Eigen::VectorXd>,
           "Add a scalar function at edges", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_halfedge_scalar_quantity", &ps::SurfaceMesh::addHalfedgeScalarQuantity<Eigen::VectorXd>,
           "Add a scalar function at halfedges", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)

      // Colors
      .def("add_vertex_color_quantity", &ps::SurfaceMesh::addVertexColorQuantity<Eigen::MatrixXd>,
           "Add a color value at vertices", py::return_value_policy::reference)
      .def("add_face_color_quantity", &ps::SurfaceMesh::addFaceColorQuantity<Eigen::MatrixXd>,
           "Add a color value at faces", py::return_value_policy::reference)

      // Distance
      .def("add_vertex_distance_quantity", &ps::SurfaceMesh::addVertexDistanceQuantity<Eigen::VectorXd>,
           "Add a distance function at vertices", py::return_value_policy::reference)
      .def("add_vertex_signed_distance_quantity", &ps::SurfaceMesh::addVertexSignedDistanceQuantity<Eigen::VectorXd>,
           "Add a signed distance function at vertices", py::return_value_policy::reference)

      // Parameterization
      .def("add_corner_parameterization_quantity", &ps::SurfaceMesh::addParameterizationQuantity<Eigen::MatrixXd>,
           "Add a parameterization at corners", py::return_value_policy::reference)
      .def("add_vertex_parameterization_quantity", &ps::SurfaceMesh::addVertexParameterizationQuantity<Eigen::MatrixXd>,
           "Add a parameterization at vertices", py::return_value_policy::reference)

      // Vector
      .def("add_vertex_vector_quantity", &ps::SurfaceMesh::addVertexVectorQuantity<Eigen::MatrixXd>,
           "Add a vertex vector quantity", py::return_value_policy::reference)
      .def("add_face_vector_quantity", &ps::SurfaceMesh::addFaceVectorQuantity<Eigen::MatrixXd>,
           "Add a face vector quantity", py::return_value_policy::reference)
      .def("add_vertex_vector_quantity2D", &ps::SurfaceMesh::addVertexVectorQuantity2D<Eigen::MatrixXd>,
           "Add a vertex 2D vector quantity", py::return_value_policy::reference)
      .def("add_face_vector_quantity2D", &ps::SurfaceMesh::addFaceVectorQuantity2D<Eigen::MatrixXd>,
           "Add a face 2D vector quantity", py::return_value_policy::reference)
      .def("add_vertex_intrinsic_vector_quantity", &ps::SurfaceMesh::addVertexIntrinsicVectorQuantity<Eigen::MatrixXd>,
           "Add a vertex intrinsic vector quantity", py::return_value_policy::reference)
      .def("add_face_intrinsic_vector_quantity", &ps::SurfaceMesh::addFaceIntrinsicVectorQuantity<Eigen::MatrixXd>,
           "Add a face intrinsic vector quantity", py::return_value_policy::reference)
      .def("add_one_form_intrinsic_vector_quantity",
           &ps::SurfaceMesh::addOneFormIntrinsicVectorQuantity<Eigen::VectorXd, Eigen::Matrix<bool, Eigen::Dynamic, 1>>,
           "Add a one form intrinsic vector quantity", py::return_value_policy::reference);


  // Static adders and getters
  m.def("register_surface_mesh", &ps::registerSurfaceMesh<Eigen::MatrixXd, Eigen::MatrixXi>, py::arg("name"),
        py::arg("vertices"), py::arg("faces"), "Register a surface mesh", py::return_value_policy::reference);
  m.def("register_surface_mesh2D", &ps::registerSurfaceMesh2D<Eigen::MatrixXd, Eigen::MatrixXi>, py::arg("name"),
        py::arg("vertices"), py::arg("faces"), "Register a surface mesh", py::return_value_policy::reference);
  m.def("register_surface_mesh_list", &ps::registerSurfaceMesh<Eigen::MatrixXd, std::vector<std::vector<size_t>>>,
        py::arg("name"), py::arg("vertices"), py::arg("faces"), "Register a surface mesh from a nested list",
        py::return_value_policy::reference);
  m.def("register_surface_mesh_list2D", &ps::registerSurfaceMesh2D<Eigen::MatrixXd, std::vector<std::vector<size_t>>>,
        py::arg("name"), py::arg("vertices"), py::arg("faces"), "Register a surface mesh from a nested list",
        py::return_value_policy::reference);

  m.def("remove_surface_mesh", &polyscope::removeSurfaceMesh, "Remove a surface mesh by name");
  m.def("get_surface_mesh", &polyscope::getSurfaceMesh, "Get a surface mesh by name",
        py::return_value_policy::reference);
  m.def("has_surface_mesh", &polyscope::hasSurfaceMesh, "Check for a surface mesh by name");
}
