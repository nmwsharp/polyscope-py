#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/point_cloud.h"

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

// =====================================================================
// =====================  Surface Mesh  ================================
// =====================================================================


ps::SurfaceMesh* register_surface_mesh(std::string name, Eigen::MatrixXd verts, Eigen::MatrixXi faces) {
  if (verts.cols() == 2) {
    return ps::registerSurfaceMesh2D(name, verts, faces);
  } else if (verts.cols() == 3) {
    return ps::registerSurfaceMesh(name, verts, faces);
  } else {
    throw std::runtime_error("vertices array must have 2 or 3 columns. has: " + std::to_string(verts.cols()));
  }
}


// Actual binding code
// clang-format off
PYBIND11_MODULE(polyscope, m) {
  m.doc() = "Polyscope! Easy 3D visualization for your data.";
  
  
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


  // === Surface Mesh

  // Helper classes
  py::class_<ps::SurfaceVertexScalarQuantity>(m, "SurfaceVertexScalarQuantity");

  // Main class, with adder methods
  py::class_<ps::SurfaceMesh>(m, "SurfaceMesh")
    .def("remove_all_quantities", &ps::SurfaceMesh::removeAllQuantities, "Remove all quantities")
    .def("add_vertex_scalar_quantity", &ps::SurfaceMesh::addVertexScalarQuantity<Eigen::VectorXd>, "Add a scalar function at vertices",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_face_scalar_quantity", &ps::SurfaceMesh::addFaceScalarQuantity<Eigen::VectorXd>, "Add a scalar function at faces",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_surface_mesh", &register_surface_mesh, "Register a surface mesh", py::return_value_policy::reference);
  m.def("get_surface_mesh", &polyscope::getSurfaceMesh, "Get a surface mesh by name", py::return_value_policy::reference);

	// Wrap the main PlyData class
  //py::class_<boundplydata>(m, "plydata")
    //.def(py::init<>())
		////.def("get_property_double", &BoundPLYData::getProperty<double>)
		//.def("__getitem__", &BoundPLYData::getElement);
	//py::return_value_policy::move);
	//.def(py::init<const std::string &>());

	// Wrap the helper element class
  //py::class_<BoundPLYElementRef>(m, "PlyElement")
    //.def(py::init<happly::PLYData&, const std::string&>())
		//.def("__getitem__", &BoundPLYElementRef::getProperty<double>);
  
	//// Loaders
  //m.def("load", &load, "Load from named file.");

}

// clang-format on
