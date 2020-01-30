#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/point_cloud.h"

namespace py = pybind11;
namespace ps = polyscope;

ps::PointCloud* register_point_cloud(std::string name, Eigen::MatrixXd points) {
  if (points.cols() == 2) {
    return ps::registerPointCloud2D(name, points);
  } else if (points.cols() == 3) {
    return ps::registerPointCloud(name, points);
  } else {
    throw std::runtime_error("points array must have 2 or 3 columns. has: " + std::to_string(points.cols()));
  }
}



void bind_point_cloud(py::module& m) {

  // Helper classes
  py::class_<ps::PointCloudColorQuantity>(m, "PointCloudColorQuantity");
  py::class_<ps::PointCloudScalarQuantity>(m, "PointCloudScalarQuantity");
  py::class_<ps::PointCloudVectorQuantity>(m, "PointCloudVectorQuantity");

  // Main class, with adder methods
  py::class_<ps::PointCloud>(m, "PointCloud")
    .def("remove", &ps::PointCloud::remove, "Remove the structure")
    .def("enabled", &ps::PointCloud::setEnabled, "Enable the structure")
    .def("remove_all_quantities", &ps::PointCloud::removeAllQuantities, "Remove all quantities")
    .def("add_color_quantity", &ps::PointCloud::addColorQuantity<Eigen::MatrixXd>, "Add a color function at points",
        py::arg("name"), py::arg("values"), py::return_value_policy::reference)
    .def("add_scalar_quantity", &ps::PointCloud::addScalarQuantity<Eigen::VectorXd>, "Add a scalar function at points",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_vector_quantity", &ps::PointCloud::addVectorQuantity<Eigen::MatrixXd>, "Add a vector function at points",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_point_cloud", &register_point_cloud, "Register a point cloud", py::return_value_policy::reference);
  m.def("remove_point_cloud", &polyscope::removePointCloud, "Remove a point cloud by name");
  m.def("get_point_cloud", &polyscope::getPointCloud, "Get a point cloud by name", py::return_value_policy::reference);
  m.def("has_point_cloud", &polyscope::hasPointCloud, "Check for a point cloud by name");

}
