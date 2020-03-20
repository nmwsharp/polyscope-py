#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/curve_network.h"
#include "polyscope/polyscope.h"

namespace py = pybind11;
namespace ps = polyscope;


// clang-format off
void bind_curve_network(py::module& m) {

  // Helper quantity classes
  py::class_<ps::CurveNetworkNodeColorQuantity>(m, "CurveNetworkNodeColorQuantity")
    .def("set_enabled", &ps::CurveNetworkNodeColorQuantity::setEnabled, "Set enabled");
  py::class_<ps::CurveNetworkEdgeColorQuantity>(m, "CurveNetworkEdgeColorQuantity")
    .def("set_enabled", &ps::CurveNetworkEdgeColorQuantity::setEnabled, "Set enabled");

  py::class_<ps::CurveNetworkNodeScalarQuantity>(m, "CurveNetworkNodeScalarQuantity")
    .def("set_enabled", &ps::CurveNetworkNodeScalarQuantity::setEnabled, "Set enabled")
    .def("set_color_map", &ps::CurveNetworkNodeScalarQuantity::setColorMap, "Set color map")
    .def("set_map_range", &ps::CurveNetworkNodeScalarQuantity::setMapRange, "Set map range");
  py::class_<ps::CurveNetworkEdgeScalarQuantity>(m, "CurveNetworkEdgeScalarQuantity")
    .def("set_enabled", &ps::CurveNetworkEdgeScalarQuantity::setEnabled, "Set enabled")
    .def("set_color_map", &ps::CurveNetworkEdgeScalarQuantity::setColorMap, "Set color map")
    .def("set_map_range", &ps::CurveNetworkEdgeScalarQuantity::setMapRange, "Set map range");

  py::class_<ps::CurveNetworkNodeVectorQuantity>(m, "CurveNetworkNodeVectorQuantity")
    .def("set_enabled", &ps::CurveNetworkNodeVectorQuantity::setEnabled, "Set enabled")
    .def("set_length", &ps::CurveNetworkNodeVectorQuantity::setVectorLengthScale, "Set length")
    .def("set_radius", &ps::CurveNetworkNodeVectorQuantity::setVectorRadius, "Set radius")
    .def("set_color", &ps::CurveNetworkNodeVectorQuantity::setVectorColor, "Set color");
  py::class_<ps::CurveNetworkEdgeVectorQuantity>(m, "CurveNetworkEdgeVectorQuantity")
    .def("set_enabled", &ps::CurveNetworkEdgeVectorQuantity::setEnabled, "Set enabled")
    .def("set_length", &ps::CurveNetworkEdgeVectorQuantity::setVectorLengthScale, "Set length")
    .def("set_radius", &ps::CurveNetworkEdgeVectorQuantity::setVectorRadius, "Set radius")
    .def("set_color", &ps::CurveNetworkEdgeVectorQuantity::setVectorColor, "Set color");

  // Main class
  py::class_<ps::CurveNetwork>(m, "CurveNetwork")

    // basics
    .def("remove", &ps::CurveNetwork::remove, "Remove the structure")
    .def("set_enabled", &ps::CurveNetwork::setEnabled, "Enable the structure")
    .def("is_enabled", &ps::CurveNetwork::isEnabled, "Check if the structure is enabled")
    .def("remove_all_quantities", &ps::CurveNetwork::removeAllQuantities, "Remove all quantities")
    .def("remove_quantity", &ps::CurveNetwork::removeQuantity, "Remove a quantity")
    .def("update_node_positions", &ps::CurveNetwork::updateNodePositions<Eigen::MatrixXd>, "Update node positions")
    .def("update_node_positions2D", &ps::CurveNetwork::updateNodePositions2D<Eigen::MatrixXd>, "Update node positions")
    .def("n_nodes", &ps::CurveNetwork::nNodes, "# nodes")
    .def("n_edges", &ps::CurveNetwork::nEdges, "# edges")

    // options
    .def("set_radius", &ps::CurveNetwork::setRadius, "Set radius")
    .def("get_radius", &ps::CurveNetwork::getRadius, "Get radius")
    .def("set_color", &ps::CurveNetwork::setColor, "Set color")
    .def("get_color", &ps::CurveNetwork::getColor, "Get color")
    .def("set_material", &ps::CurveNetwork::setMaterial, "Set material")
    .def("get_material", &ps::CurveNetwork::getMaterial, "Get material")

    // quantities
    .def("add_node_color_quantity", &ps::CurveNetwork::addNodeColorQuantity<Eigen::MatrixXd>, "Add a color function at nodes",
        py::arg("name"), py::arg("values"), py::return_value_policy::reference)
    .def("add_edge_color_quantity", &ps::CurveNetwork::addEdgeColorQuantity<Eigen::MatrixXd>, "Add a color function at edges",
        py::arg("name"), py::arg("values"), py::return_value_policy::reference)
    .def("add_node_scalar_quantity", &ps::CurveNetwork::addNodeScalarQuantity<Eigen::VectorXd>, "Add a scalar function at nodes",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_edge_scalar_quantity", &ps::CurveNetwork::addEdgeScalarQuantity<Eigen::VectorXd>, "Add a scalar function at edge",
        py::arg("name"), py::arg("values"), py::arg("data_type")=ps::DataType::STANDARD, py::return_value_policy::reference)
    .def("add_node_vector_quantity", &ps::CurveNetwork::addNodeVectorQuantity<Eigen::MatrixXd>, "Add a vector function at nodes",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference)
    .def("add_node_vector_quantity2D", &ps::CurveNetwork::addNodeVectorQuantity2D<Eigen::MatrixXd>, "Add a vector function at nodes",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference)
    .def("add_edge_vector_quantity", &ps::CurveNetwork::addEdgeVectorQuantity<Eigen::MatrixXd>, "Add a vector function at edges",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference)
    .def("add_edge_vector_quantity2D", &ps::CurveNetwork::addEdgeVectorQuantity2D<Eigen::MatrixXd>, "Add a vector function at edges",
        py::arg("name"), py::arg("values"), py::arg("vector_type")=ps::VectorType::STANDARD, py::return_value_policy::reference);

  // Static adders and getters
  m.def("register_curve_network", &ps::registerCurveNetwork<Eigen::MatrixXd, Eigen::MatrixXi>, 
      py::arg("name"), py::arg("nodes"), py::arg("edges"),
      "Register a curve network", py::return_value_policy::reference);
  m.def("register_curve_network2D", &ps::registerCurveNetwork2D<Eigen::MatrixXd, Eigen::MatrixXi>, 
      py::arg("name"), py::arg("nodes"), py::arg("edges"),
      "Register a curve network", py::return_value_policy::reference);
  
  m.def("register_curve_network_line", &ps::registerCurveNetworkLine<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("nodes"), 
      "Register a curve network", py::return_value_policy::reference);
  m.def("register_curve_network_line2D", &ps::registerCurveNetworkLine2D<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("nodes"),
      "Register a curve network", py::return_value_policy::reference);
  
  m.def("register_curve_network_loop", &ps::registerCurveNetworkLoop<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("nodes"),
      "Register a curve network", py::return_value_policy::reference);
  m.def("register_curve_network_loop2D", &ps::registerCurveNetworkLoop2D<Eigen::MatrixXd>, 
      py::arg("name"), py::arg("nodes"), 
      "Register a curve network", py::return_value_policy::reference);

  m.def("remove_curve_network", &polyscope::removeCurveNetwork, "Remove a curve network by name");
  m.def("get_curve_network", &polyscope::getCurveNetwork, "Get a curve network by name", py::return_value_policy::reference);
  m.def("has_curve_network", &polyscope::hasCurveNetwork, "Check for a curve network by name");

}
// clang-format on
