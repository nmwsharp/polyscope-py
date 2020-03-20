#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

namespace py = pybind11;
namespace ps = polyscope;


void bind_surface_mesh(py::module& m) {
  
  // Helper classes
  py::class_<ps::SurfaceVertexScalarQuantity>(m, "SurfaceVertexScalarQuantity");
  py::class_<ps::SurfaceFaceScalarQuantity>(m, "SurfaceFaceScalarQuantity");
  py::class_<ps::SurfaceVertexVectorQuantity>(m, "SurfaceVertexVectorQuantity");
  py::class_<ps::SurfaceFaceVectorQuantity>(m, "SurfaceFaceVectorQuantity");

  // Main class
  py::class_<ps::SurfaceMesh>(m, "SurfaceMesh")
    
    // basics
    .def("remove", &ps::SurfaceMesh::remove, "Remove the structure")
    .def("set_enabled", &ps::SurfaceMesh::setEnabled, "Enable the structure")
    .def("is_enabled", &ps::SurfaceMesh::isEnabled, "Check if the structure is enabled")
    .def("remove_all_quantities", &ps::SurfaceMesh::removeAllQuantities, "Remove all quantities")
    .def("remove_quantity", &ps::SurfaceMesh::removeQuantity, "Remove a quantity")
    .def("update_vertex_positions", &ps::SurfaceMesh::updateVertexPositions<Eigen::MatrixXd>, "Update vertex positions")
    .def("update_vertex_positions2D", &ps::SurfaceMesh::updateVertexPositions2D<Eigen::MatrixXd>, "Update vertex positions")
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

    // quantities
    .def("add_vertex_scalar_quantity", &ps::SurfaceMesh::addVertexScalarQuantity<Eigen::VectorXd>, "Add a scalar function at vertices",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_face_scalar_quantity", &ps::SurfaceMesh::addFaceScalarQuantity<Eigen::VectorXd>, "Add a scalar function at faces",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_vertex_vector_quantity", &ps::SurfaceMesh::addVertexVectorQuantity<Eigen::MatrixXd>, "Add a vector function at vertices",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference)
    .def("add_face_vector_quantity", &ps::SurfaceMesh::addFaceVectorQuantity<Eigen::MatrixXd>, "Add a vector function at faces",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  
  // Static adders and getters
  m.def("register_surface_mesh", &ps::registerSurfaceMesh<Eigen::MatrixXd, Eigen::MatrixXi>, 
      py::arg("name"), py::arg("nodes"), py::arg("edges"),
      "Register a surface mesh", py::return_value_policy::reference);
  m.def("register_surface_mesh2D", &ps::registerSurfaceMesh2D<Eigen::MatrixXd, Eigen::MatrixXi>, 
      py::arg("name"), py::arg("nodes"), py::arg("edges"),
      "Register a surface mesh", py::return_value_policy::reference);

  m.def("remove_surface_mesh", &polyscope::removeSurfaceMesh, "Remove a surface mesh by name");
  m.def("get_surface_mesh", &polyscope::getSurfaceMesh, "Get a surface mesh by name", py::return_value_policy::reference);
  m.def("has_surface_mesh", &polyscope::hasSurfaceMesh, "Check for a surface mesh by name");
}
