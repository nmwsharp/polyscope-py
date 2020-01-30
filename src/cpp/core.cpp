#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"

namespace py = pybind11;
namespace ps = polyscope;

// =====================================================================
// ======================  Point Cloud  ================================
// =====================================================================


ps::PointCloud* register_point_cloud(std::string name, Eigen::MatrixXd points) {
  if (points.cols() == 2) {
    return ps::registerPointCloud2D(name, points);
  } else if (points.cols() == 3) {
    return ps::registerPointCloud(name, points);
  } else {
    throw std::runtime_error("points array must have 2 or 3 columns. has: " + std::to_string(points.cols()));
  }
}

// Forward-declare bindings from other files
void bind_surface_mesh(py::module& m);


// Actual binding code
// clang-format off
PYBIND11_MODULE(polyscope_bindings, m) {
  m.doc() = "Polyscope low-level bindings";
  
  
  // Basic flow 
  m.def("init", &ps::init, "Initialize Polyscope");
  m.def("show", &ps::show, "Show the Polyscope GUI (blocks until UI is exited)");
  m.def("remove_all_structures", &ps::removeAllStructures, "Remove all structures from polyscope");

  
  // === Enums and other options
  py::enum_<ps::DataType>(m, "DataType")
    .value("standard", ps::DataType::STANDARD)
    .value("symmetric", ps::DataType::SYMMETRIC)
    .value("magnitude", ps::DataType::MAGNITUDE)
    .export_values(); 
  py::enum_<ps::VectorType>(m, "VectorType")
    .value("standard", ps::VectorType::STANDARD)
    .value("ambient", ps::VectorType::AMBIENT)
    .export_values(); 
 

  // === Point Cloud

  // Helper classes
  py::class_<ps::PointCloudColorQuantity>(m, "PointCloudColorQuantity");
  py::class_<ps::PointCloudScalarQuantity>(m, "PointCloudScalarQuantity");
  py::class_<ps::PointCloudVectorQuantity>(m, "PointCloudVectorQuantity");

  // Main class, with adder methods
  py::class_<ps::PointCloud>(m, "PointCloud")
    .def("enabled", &ps::PointCloud::setEnabled, "Enable the quantity")
    .def("remove_all_quantities", &ps::PointCloud::removeAllQuantities, "Remove all quantities")
    .def("add_color_quantity", &ps::PointCloud::addColorQuantity<Eigen::MatrixXd>, "Add a color function at points",
        py::arg("name"), py::arg("values"), py::return_value_policy::reference)
    .def("add_scalar_quantity", &ps::PointCloud::addScalarQuantity<Eigen::VectorXd>, "Add a scalar function at points",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_vector_quantity", &ps::PointCloud::addVectorQuantity<Eigen::MatrixXd>, "Add a vector function at points",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_point_cloud", &register_point_cloud, "Register a point cloud", py::return_value_policy::reference);
  m.def("get_point_cloud", &polyscope::getPointCloud, "Get a point cloud by name", py::return_value_policy::reference);

  bind_surface_mesh(m);

}

// clang-format on
