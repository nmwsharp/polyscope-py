#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

namespace py = pybind11;
namespace ps = polyscope;

ps::SurfaceMesh* register_surface_mesh(std::string name, Eigen::MatrixXd verts, Eigen::MatrixXi faces) {
  if (verts.cols() == 2) {
    return ps::registerSurfaceMesh2D(name, verts, faces);
  } else if (verts.cols() == 3) {
    return ps::registerSurfaceMesh(name, verts, faces);
  } else {
    throw std::runtime_error("vertices array must have 2 or 3 columns. has: " + std::to_string(verts.cols()));
  }
}



void bind_surface_mesh(py::module& m) {
  
  // Helper classes
  py::class_<ps::SurfaceVertexScalarQuantity>(m, "SurfaceVertexScalarQuantity");
  py::class_<ps::SurfaceFaceScalarQuantity>(m, "SurfaceFaceScalarQuantity");
  py::class_<ps::SurfaceVertexVectorQuantity>(m, "SurfaceVertexVectorQuantity");
  py::class_<ps::SurfaceFaceVectorQuantity>(m, "SurfaceFaceVectorQuantity");

  // Main class, with adder methods
  py::class_<ps::SurfaceMesh>(m, "SurfaceMesh")
    .def("set_enabled", &ps::SurfaceMesh::setEnabled, "Enable the quantity")
    .def("remove_all_quantities", &ps::SurfaceMesh::removeAllQuantities, "Remove all quantities")
    .def("add_vertex_scalar_quantity", &ps::SurfaceMesh::addVertexScalarQuantity<Eigen::VectorXd>, "Add a scalar function at vertices",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_face_scalar_quantity", &ps::SurfaceMesh::addFaceScalarQuantity<Eigen::VectorXd>, "Add a scalar function at faces",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_vertex_vector_quantity", &ps::SurfaceMesh::addVertexVectorQuantity<Eigen::MatrixXd>, "Add a vector function at vertices",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference)
    .def("add_face_vector_quantity", &ps::SurfaceMesh::addFaceVectorQuantity<Eigen::MatrixXd>, "Add a vector function at faces",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_surface_mesh", &register_surface_mesh, "Register a surface mesh", py::return_value_policy::reference);
  m.def("get_surface_mesh", &polyscope::getSurfaceMesh, "Get a surface mesh by name", py::return_value_policy::reference);
}
