#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/curve_network.h"
#include "polyscope/polyscope.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;


// clang-format off
void bind_curve_network(py::module& m) {
  
  // == Helper quantity classes
  
  // Scalar quantities
  bindScalarQuantity<ps::CurveNetworkNodeScalarQuantity>(m, "CurveNetworkNodeScalarQuantity");
  bindScalarQuantity<ps::CurveNetworkEdgeScalarQuantity>(m, "CurveNetworkEdgeScalarQuantity");

  // Color quantities
  bindColorQuantity<ps::CurveNetworkNodeColorQuantity>(m, "CurveNetworkNodeColorQuantity");
  bindColorQuantity<ps::CurveNetworkEdgeColorQuantity>(m, "CurveNetworkEdgeColorQuantity");

  // Vector quantities
  bindVectorQuantity<ps::CurveNetworkNodeVectorQuantity>(m, "CurveNetworkNodeVectorQuantity");
  bindVectorQuantity<ps::CurveNetworkEdgeVectorQuantity>(m, "CurveNetworkEdgeVectorQuantity");


  // == Main class
  bindStructure<ps::CurveNetwork>(m, "CurveNetwork")

    // basics
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
    
    // slice planes
    .def("set_ignore_slice_plane", &ps::CurveNetwork::setIgnoreSlicePlane, "Set ignore slice plane")
    .def("get_ignore_slice_plane", &ps::CurveNetwork::getIgnoreSlicePlane, "Get ignore slice plane")
    .def("set_cull_whole_elements", &ps::CurveNetwork::setCullWholeElements, "Set cull whole elements")
    .def("get_cull_whole_elements", &ps::CurveNetwork::getCullWholeElements, "Get cull whole elements")


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
