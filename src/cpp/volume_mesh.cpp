#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/volume_mesh.h"

#include "utils.h"


void bind_volume_mesh(nb::module_& m) {

  // == Helper classes
  nb::class_<ps::VolumeMeshPickResult>(m, "VolumeMeshPickResult")
   .def(nb::init<>())
   .def_ro("element_type", &ps::VolumeMeshPickResult::elementType)
   .def_ro("index", &ps::VolumeMeshPickResult::index)
  ;

  // Scalar quantities
  bindVMVScalarQuantity<ps::VolumeMeshVertexScalarQuantity>(m, "VolumeMeshVertexScalarQuantity");
  bindScalarQuantity<ps::VolumeMeshCellScalarQuantity>(m, "VolumeMeshCellScalarQuantity");

  // Color quantities
  bindColorQuantity<ps::VolumeMeshVertexColorQuantity>(m, "VolumeMeshVertexColorQuantity");
  bindColorQuantity<ps::VolumeMeshCellColorQuantity>(m, "VolumeMeshCellColorQuantity");

  // Vector quantities
  bindVectorQuantity<ps::VolumeMeshVertexVectorQuantity>(m, "VolumeMeshVertexVectorQuantity");
  bindVectorQuantity<ps::VolumeMeshCellVectorQuantity>(m, "VolumeMeshCellVectorQuantity");

  // == Main class
  bindStructure<ps::VolumeMesh>(m, "VolumeMesh")

      // basics
      .def("update_vertex_positions", &ps::VolumeMesh::updateVertexPositions<Eigen::MatrixXf>,
           "Update vertex positions")
      .def("n_vertices", &ps::VolumeMesh::nVertices, "# vertices")
      .def("n_faces", &ps::VolumeMesh::nFaces, "# faces")
      .def("n_cells", &ps::VolumeMesh::nCells, "# cells")

      // options
      .def("set_color", &ps::VolumeMesh::setColor, "Set mesh color")
      .def("get_color", &ps::VolumeMesh::getColor, "Get mesh color")
      .def("set_interior_color", &ps::VolumeMesh::setInteriorColor, "Set interior mesh color")
      .def("get_interior_color", &ps::VolumeMesh::getInteriorColor, "Get interior mesh color")
      .def("set_edge_color", &ps::VolumeMesh::setEdgeColor, "Set edge color")
      .def("get_edge_color", &ps::VolumeMesh::getEdgeColor, "Get edge color")
      .def("set_edge_width", &ps::VolumeMesh::setEdgeWidth, "Set edge width")
      .def("get_edge_width", &ps::VolumeMesh::getEdgeWidth, "Get edge width")
      .def("set_material", &ps::VolumeMesh::setMaterial, "Set material")
      .def("get_material", &ps::VolumeMesh::getMaterial, "Get material")

      // picking
      .def("interpret_pick_result", &ps::VolumeMesh::interpretPickResult)

      // = quantities

      // Scalars
      .def("add_vertex_scalar_quantity", &ps::VolumeMesh::addVertexScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at vertices", nb::arg("name"), nb::arg("values"),
           nb::arg("data_type") = ps::DataType::STANDARD, nb::rv_policy::reference)
      .def("add_cell_scalar_quantity", &ps::VolumeMesh::addCellScalarQuantity<Eigen::VectorXf>,
           "Add a scalar function at cells", nb::arg("name"), nb::arg("values"),
           nb::arg("data_type") = ps::DataType::STANDARD, nb::rv_policy::reference)

      // Colors
      .def("add_vertex_color_quantity", &ps::VolumeMesh::addVertexColorQuantity<Eigen::MatrixXf>,
           "Add a color value at vertices", nb::rv_policy::reference)
      .def("add_cell_color_quantity", &ps::VolumeMesh::addCellColorQuantity<Eigen::MatrixXf>,
           "Add a color value at cells", nb::rv_policy::reference)


      // Vector
      .def("add_vertex_vector_quantity", &ps::VolumeMesh::addVertexVectorQuantity<Eigen::MatrixXf>,
           "Add a vertex vector quantity", nb::rv_policy::reference)
      .def("add_cell_vector_quantity", &ps::VolumeMesh::addCellVectorQuantity<Eigen::MatrixXf>,
           "Add a cell vector quantity", nb::rv_policy::reference);


  // Static adders and getters
  m.def("register_tet_mesh", &ps::registerTetMesh<Eigen::MatrixXf, Eigen::MatrixXi>, nb::arg("name"),
        nb::arg("vertices"), nb::arg("tets"), "Register a volume mesh of tet cells",
        nb::rv_policy::reference);
  m.def("register_hex_mesh", &ps::registerHexMesh<Eigen::MatrixXf, Eigen::MatrixXi>, nb::arg("name"),
        nb::arg("vertices"), nb::arg("hexes"), "Register a volume mesh of hex cells",
        nb::rv_policy::reference);
  m.def("register_volume_mesh", &ps::registerVolumeMesh<Eigen::MatrixXf, Eigen::MatrixXi>, nb::arg("name"),
        nb::arg("vertices"), nb::arg("cells"), "Register a volume mesh with a mix of element types",
        nb::rv_policy::reference);
  m.def("register_tet_hex_mesh", &ps::registerTetHexMesh<Eigen::MatrixXf, Eigen::MatrixXi, Eigen::MatrixXi>,
        nb::arg("name"), nb::arg("vertices"), nb::arg("tets"), nb::arg("hexes"),
        "Register a volume mesh with lists of tet and hex elements", nb::rv_policy::reference);

  m.def("remove_volume_mesh", &polyscope::removeVolumeMesh, "Remove a volume mesh by name");
  m.def("get_volume_mesh", &polyscope::getVolumeMesh, "Get a volume mesh by name", nb::rv_policy::reference);
  m.def("has_volume_mesh", &polyscope::hasVolumeMesh, "Check for a volume mesh by name");
}
