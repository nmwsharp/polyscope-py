#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/sparse_volume_grid.h"

#include "utils.h"


void bind_sparse_volume_grid(nb::module_& m) {

  // == Helper classes
  nb::class_<ps::SparseVolumeGridPickResult>(m, "SparseVolumeGridPickResult")
   .def(nb::init<>())
   .def_ro("element_type", &ps::SparseVolumeGridPickResult::elementType)
   .def_ro("cell_index", &ps::SparseVolumeGridPickResult::cellIndex)
   .def_ro("cell_flat_index", &ps::SparseVolumeGridPickResult::cellFlatIndex)
   .def_ro("node_index", &ps::SparseVolumeGridPickResult::nodeIndex)
  ;

  // Scalar quantities
  bindScalarQuantity<ps::SparseVolumeGridCellScalarQuantity>(m, "SparseVolumeGridCellScalarQuantity")
    ;

  bindScalarQuantity<ps::SparseVolumeGridNodeScalarQuantity>(m, "SparseVolumeGridNodeScalarQuantity")
    ;

  // Color quantities
  bindColorQuantity<ps::SparseVolumeGridCellColorQuantity>(m, "SparseVolumeGridCellColorQuantity")
    ;

  bindColorQuantity<ps::SparseVolumeGridNodeColorQuantity>(m, "SparseVolumeGridNodeColorQuantity")
    ;

  // == Main class
  bindStructure<ps::SparseVolumeGrid>(m, "SparseVolumeGrid")

      // basics
      .def("n_cells", &ps::SparseVolumeGrid::nCells)
      .def("n_nodes", &ps::SparseVolumeGrid::nNodes)
      .def("get_origin", [](ps::SparseVolumeGrid& x) { return glm2eigen(x.getOrigin()); })
      .def("get_grid_cell_width", [](ps::SparseVolumeGrid& x) { return glm2eigen(x.getGridCellWidth()); })

      .def("mark_nodes_as_used", &ps::SparseVolumeGrid::markNodesAsUsed)

      // options
      .def("set_color", &ps::SparseVolumeGrid::setColor)
      .def("get_color", &ps::SparseVolumeGrid::getColor)
      .def("set_edge_color", &ps::SparseVolumeGrid::setEdgeColor)
      .def("get_edge_color", &ps::SparseVolumeGrid::getEdgeColor)
      .def("set_material", &ps::SparseVolumeGrid::setMaterial, "Set material")
      .def("get_material", &ps::SparseVolumeGrid::getMaterial, "Get material")
      .def("set_edge_width", &ps::SparseVolumeGrid::setEdgeWidth, "Set edge width")
      .def("get_edge_width", &ps::SparseVolumeGrid::getEdgeWidth, "Get edge width")
      .def("set_cube_size_factor", &ps::SparseVolumeGrid::setCubeSizeFactor, "Set cube size factor")
      .def("get_cube_size_factor", &ps::SparseVolumeGrid::getCubeSizeFactor, "Get cube size factor")
      .def("set_render_mode", &ps::SparseVolumeGrid::setRenderMode, "Set voxel render mode")
      .def("get_render_mode", &ps::SparseVolumeGrid::getRenderMode, "Get voxel render mode")
      .def("set_wireframe_radius", &ps::SparseVolumeGrid::setWireframeRadius, "Set wireframe radius")
      .def("get_wireframe_radius", &ps::SparseVolumeGrid::getWireframeRadius, "Get wireframe radius")
      .def("set_wireframe_color", &ps::SparseVolumeGrid::setWireframeColor, "Set wireframe color")
      .def("get_wireframe_color", &ps::SparseVolumeGrid::getWireframeColor, "Get wireframe color")

      // picking
      .def("interpret_pick_result", &ps::SparseVolumeGrid::interpretPickResult)

      // = quantities

      // Cell scalar
      .def("add_cell_scalar_quantity", &ps::SparseVolumeGrid::addCellScalarQuantity<Eigen::VectorXf>,
          nb::arg("name"), nb::arg("values"), nb::arg("data_type") = ps::DataType::STANDARD,
          nb::rv_policy::reference)

      // Node scalar
      .def("add_node_scalar_quantity", &ps::SparseVolumeGrid::addNodeScalarQuantity<Eigen::MatrixXi, Eigen::VectorXf>,
          nb::arg("name"), nb::arg("node_indices"), nb::arg("node_values"), nb::arg("data_type") = ps::DataType::STANDARD,
          nb::rv_policy::reference)

      // Cell color
      .def("add_cell_color_quantity", &ps::SparseVolumeGrid::addCellColorQuantity<Eigen::MatrixXf>,
          nb::arg("name"), nb::arg("colors"),
          nb::rv_policy::reference)

      // Node color
      .def("add_node_color_quantity", &ps::SparseVolumeGrid::addNodeColorQuantity<Eigen::MatrixXi, Eigen::MatrixXf>,
          nb::arg("name"), nb::arg("node_indices"), nb::arg("node_colors"),
          nb::rv_policy::reference)

    ;

  // Static adders and getters
  m.def("register_sparse_volume_grid",
        &ps::registerSparseVolumeGrid<Eigen::MatrixXi>,
        nb::arg("name"), nb::arg("origin"), nb::arg("grid_cell_width"), nb::arg("occupied_cells"),
        nb::rv_policy::reference);

  m.def("remove_sparse_volume_grid", &polyscope::removeSparseVolumeGrid);
  m.def("get_sparse_volume_grid", &polyscope::getSparseVolumeGrid, nb::rv_policy::reference);
  m.def("has_sparse_volume_grid", &polyscope::hasSparseVolumeGrid);
}
