#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/curve_network.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;


void bind_surface_mesh(py::module& m) {


  // == Helper classes
  py::class_<ps::SurfaceMeshPickResult>(m, "SurfaceMeshPickResult")
   .def(py::init<>())
   .def_readonly("element_type", &ps::SurfaceMeshPickResult::elementType)
   .def_readonly("index", &ps::SurfaceMeshPickResult::index)
   .def_readonly("bary_coords", &ps::SurfaceMeshPickResult::baryCoords)
  ;


  // Scalar quantities
  bindScalarQuantity<ps::SurfaceVertexScalarQuantity>(m, "SurfaceVertexScalarQuantity");
  bindScalarQuantity<ps::SurfaceFaceScalarQuantity>(m, "SurfaceFaceScalarQuantity");
  bindScalarQuantity<ps::SurfaceEdgeScalarQuantity>(m, "SurfaceEdgeScalarQuantity");
  bindScalarQuantity<ps::SurfaceHalfedgeScalarQuantity>(m, "SurfaceHalfedgeScalarQuantity");
  bindScalarQuantity<ps::SurfaceCornerScalarQuantity>(m, "SurfaceCornerScalarQuantity");
  py::class_<ps::SurfaceTextureScalarQuantity> boundScalarQ = 
     bindScalarQuantity<ps::SurfaceTextureScalarQuantity>(m, "SurfaceTextureScalarQuantity");
  addTextureMapQuantityBindings<ps::SurfaceTextureScalarQuantity>(boundScalarQ);

  // Color quantities
  bindColorQuantity<ps::SurfaceVertexColorQuantity>(m, "SurfaceVertexColorQuantity");
  bindColorQuantity<ps::SurfaceFaceColorQuantity>(m, "SurfaceFaceColorQuantity");
  py::class_<ps::SurfaceTextureColorQuantity> boundColorQ = 
     bindColorQuantity<ps::SurfaceTextureColorQuantity>(m, "SurfaceTextureColorQuantity");
  addTextureMapQuantityBindings<ps::SurfaceTextureColorQuantity>(boundColorQ);


  // Parameterization quantities
  py::class_<ps::SurfaceCornerParameterizationQuantity>(m, "SurfaceCornerParameterizationQuantity")
      .def("set_enabled", &ps::SurfaceCornerParameterizationQuantity::setEnabled, "Set enabled")
      .def("set_style", &ps::SurfaceCornerParameterizationQuantity::setStyle, "Set style")
      .def("set_grid_colors", &ps::SurfaceCornerParameterizationQuantity::setGridColors, "Set grid colors")
      .def("set_checker_colors", &ps::SurfaceCornerParameterizationQuantity::setCheckerColors, "Set checker colors")
      .def("set_checker_size", &ps::SurfaceCornerParameterizationQuantity::setCheckerSize, "Set checker size")
      .def("set_color_map", &ps::SurfaceCornerParameterizationQuantity::setColorMap, "Set color map")
      .def("set_island_labels", &ps::SurfaceCornerParameterizationQuantity::setIslandLabels<Eigen::VectorXf>)
      .def("create_curve_network_from_seams", &ps::SurfaceCornerParameterizationQuantity::createCurveNetworkFromSeams, py::return_value_policy::reference);
  py::class_<ps::SurfaceVertexParameterizationQuantity>(m, "SurfaceVertexParameterizationQuantity")
      .def("set_enabled", &ps::SurfaceVertexParameterizationQuantity::setEnabled, "Set enabled")
      .def("set_style", &ps::SurfaceVertexParameterizationQuantity::setStyle, "Set style")
      .def("set_grid_colors", &ps::SurfaceVertexParameterizationQuantity::setGridColors, "Set grid colors")
      .def("set_checker_colors", &ps::SurfaceVertexParameterizationQuantity::setCheckerColors, "Set checker colors")
      .def("set_checker_size", &ps::SurfaceVertexParameterizationQuantity::setCheckerSize, "Set checker size")
      .def("set_color_map", &ps::SurfaceVertexParameterizationQuantity::setColorMap, "Set color map")
      .def("set_island_labels", &ps::SurfaceVertexParameterizationQuantity::setIslandLabels<Eigen::VectorXf>)
      .def("create_curve_network_from_seams", &ps::SurfaceVertexParameterizationQuantity::createCurveNetworkFromSeams, py::return_value_policy::reference);

  // Vector quantities
  bindVectorQuantity<ps::SurfaceVertexVectorQuantity>(m, "SurfaceVertexVectorQuantity");
  bindVectorQuantity<ps::SurfaceFaceVectorQuantity>(m, "SurfaceFaceVectorQuantity");
  bindVectorQuantity<ps::SurfaceVertexTangentVectorQuantity>(m, "SurfaceVertexTangentVectorQuantity");
  bindVectorQuantity<ps::SurfaceFaceTangentVectorQuantity>(m, "SurfaceFaceTangentVectorQuantity");
  bindVectorQuantity<ps::SurfaceOneFormTangentVectorQuantity>(m, "SurfaceOneFormTangentVectorQuantity");


  // == Main class
  bindStructure<ps::SurfaceMesh>(m, "SurfaceMesh")

      // basics
      .def("update_vertex_positions", &ps::SurfaceMesh::updateVertexPositions<Eigen::MatrixXf>,
           "Update vertex positions")
      .def("update_vertex_positions2D", &ps::SurfaceMesh::updateVertexPositions2D<Eigen::MatrixXf>,
           "Update vertex positions")
      .def("n_vertices", &ps::SurfaceMesh::nVertices, "# vertices")
      .def("n_faces", &ps::SurfaceMesh::nFaces, "# faces")
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
      .def("set_shade_style", &ps::SurfaceMesh::setShadeStyle, "Set shading")
      .def("get_shade_style", &ps::SurfaceMesh::getShadeStyle, "Get shading")
      .def("set_selection_mode", &ps::SurfaceMesh::setSelectionMode)
      .def("get_selection_mode", &ps::SurfaceMesh::getSelectionMode)
      .def("set_material", &ps::SurfaceMesh::setMaterial, "Set material")
      .def("get_material", &ps::SurfaceMesh::getMaterial, "Get material")
      .def("set_back_face_policy", &ps::SurfaceMesh::setBackFacePolicy, "Set back face policy")
      .def("get_back_face_policy", &ps::SurfaceMesh::getBackFacePolicy, "Get back face policy")
      .def("set_back_face_color", &ps::SurfaceMesh::setBackFaceColor, "Set back face color")
      .def("get_back_face_color", &ps::SurfaceMesh::getBackFaceColor, "Get back face color")
    
      // picking
      .def("interpret_pick_result", &ps::SurfaceMesh::interpretPickResult)

      // permutations & bases
      .def("set_edge_permutation", &ps::SurfaceMesh::setEdgePermutation<Eigen::VectorXi>, "Set edge permutation")
      .def("set_halfedge_permutation", &ps::SurfaceMesh::setHalfedgePermutation<Eigen::VectorXi>,
           "Set halfedge permutation")
      .def("set_corner_permutation", &ps::SurfaceMesh::setCornerPermutation<Eigen::VectorXi>, "Set corner permutation")
      
      .def("mark_edges_as_used", &ps::SurfaceMesh::markEdgesAsUsed)
      .def("mark_halfedges_as_used", &ps::SurfaceMesh::markHalfedgesAsUsed)
      .def("mark_corners_as_used", &ps::SurfaceMesh::markCornersAsUsed)

      // scalar transparency
      .def("set_transparency_quantity", 
          overload_cast_<std::string>()(&ps::SurfaceMesh::setTransparencyQuantity), py::arg("quantity_name"))
      .def("clear_transparency_quantity", &ps::SurfaceMesh::clearTransparencyQuantity)

      // = quantities

      // Scalars
      .def("add_vertex_scalar_quantity", &ps::SurfaceMesh::addVertexScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at vertices", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_face_scalar_quantity", &ps::SurfaceMesh::addFaceScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at faces", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_edge_scalar_quantity", &ps::SurfaceMesh::addEdgeScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at edges", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_halfedge_scalar_quantity", &ps::SurfaceMesh::addHalfedgeScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at halfedges", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_corner_scalar_quantity", &ps::SurfaceMesh::addCornerScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at corners", py::arg("name"), py::arg("values"),
           py::arg("data_type") = ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_texture_scalar_quantity",
           overload_cast_<std::string, std::string, size_t, size_t, const Eigen::VectorXf&, ps::ImageOrigin,
                          polyscope::DataType>()(&ps::SurfaceMesh::addTextureScalarQuantity<Eigen::VectorXf>),
           "Add a scalar function from a texture map", py::arg("name"), py::arg("param_name"), py::arg("dimX"),
           py::arg("dimY"), py::arg("values"), py::arg("image_origin"), py::arg("data_type") = ps::DataType::STANDARD,
           py::return_value_policy::reference)

      // Colors
      .def("add_vertex_color_quantity", &ps::SurfaceMesh::addVertexColorQuantity<Eigen::MatrixXf>,
           "Add a color value at vertices", py::return_value_policy::reference)
      .def("add_face_color_quantity", &ps::SurfaceMesh::addFaceColorQuantity<Eigen::MatrixXf>,
           "Add a color value at faces", py::return_value_policy::reference)
      .def("add_texture_color_quantity",
           overload_cast_<std::string, std::string, size_t, size_t, const Eigen::MatrixXf&, ps::ImageOrigin>()(
               &ps::SurfaceMesh::addTextureColorQuantity<Eigen::MatrixXf>),
           "Add a color function from a texture map", py::arg("name"), py::arg("param_name"), py::arg("dimX"),
           py::arg("dimY"), py::arg("colors"), py::arg("image_origin"), py::return_value_policy::reference)

      // Distance
      .def("add_vertex_distance_quantity", &ps::SurfaceMesh::addVertexDistanceQuantity<Eigen::VectorXf>,
           "Add a distance function at vertices", py::return_value_policy::reference)
      .def("add_vertex_signed_distance_quantity", &ps::SurfaceMesh::addVertexSignedDistanceQuantity<Eigen::VectorXf>,
           "Add a signed distance function at vertices", py::return_value_policy::reference)

      // Parameterization
      .def("add_corner_parameterization_quantity", &ps::SurfaceMesh::addParameterizationQuantity<Eigen::MatrixXf>,
           "Add a parameterization at corners", py::return_value_policy::reference)
      .def("add_vertex_parameterization_quantity", &ps::SurfaceMesh::addVertexParameterizationQuantity<Eigen::MatrixXf>,
           "Add a parameterization at vertices", py::return_value_policy::reference)

      // Vector
      .def("add_vertex_vector_quantity", &ps::SurfaceMesh::addVertexVectorQuantity<Eigen::MatrixXf>,
           "Add a vertex vector quantity", py::return_value_policy::reference)
      .def("add_face_vector_quantity", &ps::SurfaceMesh::addFaceVectorQuantity<Eigen::MatrixXf>,
           "Add a face vector quantity", py::return_value_policy::reference)
      .def("add_vertex_vector_quantity2D", &ps::SurfaceMesh::addVertexVectorQuantity2D<Eigen::MatrixXf>,
           "Add a vertex 2D vector quantity", py::return_value_policy::reference)
      .def("add_face_vector_quantity2D", &ps::SurfaceMesh::addFaceVectorQuantity2D<Eigen::MatrixXf>,
           "Add a face 2D vector quantity", py::return_value_policy::reference)
      .def("add_vertex_tangent_vector_quantity",
           &ps::SurfaceMesh::addVertexTangentVectorQuantity<Eigen::MatrixXf, Eigen::MatrixXf, Eigen::MatrixXf>,
           "Add a vertex tangent vector quantity", py::return_value_policy::reference)
      .def("add_face_tangent_vector_quantity",
           &ps::SurfaceMesh::addFaceTangentVectorQuantity<Eigen::MatrixXf, Eigen::MatrixXf, Eigen::MatrixXf>,
           "Add a face tangent vector quantity", py::return_value_policy::reference)
      .def("add_one_form_tangent_vector_quantity",
           &ps::SurfaceMesh::addOneFormTangentVectorQuantity<Eigen::VectorXf, Eigen::Matrix<bool, Eigen::Dynamic, 1>>,
           "Add a one form tangent vector quantity", py::return_value_policy::reference);


  // Static adders and getters
  m.def("register_surface_mesh", &ps::registerSurfaceMesh<Eigen::MatrixXf, Eigen::MatrixXi>, py::arg("name"),
        py::arg("vertices"), py::arg("faces"), "Register a surface mesh", py::return_value_policy::reference);
  m.def("register_surface_mesh2D", &ps::registerSurfaceMesh2D<Eigen::MatrixXf, Eigen::MatrixXi>, py::arg("name"),
        py::arg("vertices"), py::arg("faces"), "Register a surface mesh", py::return_value_policy::reference);
  m.def("register_surface_mesh_list", &ps::registerSurfaceMesh<Eigen::MatrixXf, std::vector<std::vector<size_t>>>,
        py::arg("name"), py::arg("vertices"), py::arg("faces"), "Register a surface mesh from a nested list",
        py::return_value_policy::reference);
  m.def("register_surface_mesh_list2D", &ps::registerSurfaceMesh2D<Eigen::MatrixXf, std::vector<std::vector<size_t>>>,
        py::arg("name"), py::arg("vertices"), py::arg("faces"), "Register a surface mesh from a nested list",
        py::return_value_policy::reference);

  m.def("remove_surface_mesh", &polyscope::removeSurfaceMesh, "Remove a surface mesh by name");
  m.def("get_surface_mesh", &polyscope::getSurfaceMesh, "Get a surface mesh by name",
        py::return_value_policy::reference);
  m.def("has_surface_mesh", &polyscope::hasSurfaceMesh, "Check for a surface mesh by name");
}
