#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/simple_triangle_mesh.h"

#include "utils.h"

void bind_simple_triangle_mesh(nb::module_& m) {

  // == Quantity types

  // Scalar quantities
  bindScalarQuantity<ps::SimpleTriangleMeshVertexScalarQuantity>(m, "SimpleTriangleMeshVertexScalarQuantity")
      .def("update_data", &ps::SimpleTriangleMeshVertexScalarQuantity::updateData<Eigen::VectorXf>,
           nb::arg("values"), "Update scalar values (count must stay the same)");
  bindScalarQuantity<ps::SimpleTriangleMeshFaceScalarQuantity>(m, "SimpleTriangleMeshFaceScalarQuantity")
      .def("update_data", &ps::SimpleTriangleMeshFaceScalarQuantity::updateData<Eigen::VectorXf>,
           nb::arg("values"), "Update scalar values (count must stay the same)");

  // Color quantities
  bindColorQuantity<ps::SimpleTriangleMeshVertexColorQuantity>(m, "SimpleTriangleMeshVertexColorQuantity")
      .def("update_data", &ps::SimpleTriangleMeshVertexColorQuantity::updateData<Eigen::MatrixXf>,
           nb::arg("values"), "Update color values (count must stay the same)");
  bindColorQuantity<ps::SimpleTriangleMeshFaceColorQuantity>(m, "SimpleTriangleMeshFaceColorQuantity")
      .def("update_data", &ps::SimpleTriangleMeshFaceColorQuantity::updateData<Eigen::MatrixXf>,
           nb::arg("values"), "Update color values (count must stay the same)");


  // == Helper classes
  nb::class_<ps::SimpleTriangleMeshPickResult>(m, "SimpleTriangleMeshPickResult")
      .def(nb::init<>())
      .def_ro("element_type", &ps::SimpleTriangleMeshPickResult::elementType)
      .def_ro("index", &ps::SimpleTriangleMeshPickResult::index);


  // == Main class
  bindStructure<ps::SimpleTriangleMesh>(m, "SimpleTriangleMesh")

      // basics
      .def("n_vertices", &ps::SimpleTriangleMesh::nVertices, "# vertices")
      .def("n_faces", &ps::SimpleTriangleMesh::nFaces, "# faces")

      // update
      .def("update_vertex_positions", &ps::SimpleTriangleMesh::updateVertexPositions<Eigen::MatrixXf>,
           "Update vertex positions (vertex count must stay the same)")
      .def("update", &ps::SimpleTriangleMesh::update<Eigen::MatrixXf, Eigen::MatrixXi>,
           nb::arg("vertices"), nb::arg("faces"),
           "Update vertices and faces (counts may change)")
      .def("update_mesh", &ps::SimpleTriangleMesh::updateMesh<Eigen::MatrixXf, Eigen::MatrixXi>,
           nb::arg("vertices"), nb::arg("faces"),
           "Update vertices and faces (counts may change), also updates object-space bounds")
      .def("reserve", &ps::SimpleTriangleMesh::reserve,
           nb::arg("n_verts"), nb::arg("n_faces"),
           "Pre-allocate capacity to avoid reallocations on future updates")

      // options
      .def("set_color", &ps::SimpleTriangleMesh::setSurfaceColor, "Set surface color")
      .def("get_color", &ps::SimpleTriangleMesh::getSurfaceColor, "Get surface color")
      .def("set_back_face_policy", &ps::SimpleTriangleMesh::setBackFacePolicy, "Set back face policy")
      .def("get_back_face_policy", &ps::SimpleTriangleMesh::getBackFacePolicy, "Get back face policy")
      .def("set_back_face_color", &ps::SimpleTriangleMesh::setBackFaceColor, "Set back face color")
      .def("get_back_face_color", &ps::SimpleTriangleMesh::getBackFaceColor, "Get back face color")
      .def("set_material", &ps::SimpleTriangleMesh::setMaterial, "Set material")
      .def("get_material", &ps::SimpleTriangleMesh::getMaterial, "Get material")
      .def("set_selection_mode", &ps::SimpleTriangleMesh::setSelectionMode, "Set selection mode")
      .def("get_selection_mode", &ps::SimpleTriangleMesh::getSelectionMode, "Get selection mode")

      // picking
      .def("interpret_pick_result", &ps::SimpleTriangleMesh::interpretPickResult)

      // quantities — scalars
      .def("add_vertex_scalar_quantity", &ps::SimpleTriangleMesh::addVertexScalarQuantity<Eigen::VectorXf>,
           "Add a scalar quantity at vertices", nb::arg("name"), nb::arg("values"),
           nb::arg("data_type") = ps::DataType::STANDARD, nb::rv_policy::reference)
      .def("add_face_scalar_quantity", &ps::SimpleTriangleMesh::addFaceScalarQuantity<Eigen::VectorXf>,
           "Add a scalar quantity at faces", nb::arg("name"), nb::arg("values"),
           nb::arg("data_type") = ps::DataType::STANDARD, nb::rv_policy::reference)

      // quantities — colors
      .def("add_vertex_color_quantity", &ps::SimpleTriangleMesh::addVertexColorQuantity<Eigen::MatrixXf>,
           "Add a color quantity at vertices", nb::arg("name"), nb::arg("values"), nb::rv_policy::reference)
      .def("add_face_color_quantity", &ps::SimpleTriangleMesh::addFaceColorQuantity<Eigen::MatrixXf>,
           "Add a color quantity at faces", nb::arg("name"), nb::arg("values"), nb::rv_policy::reference);


  // == Module-level functions
  m.def("register_simple_triangle_mesh",
        &ps::registerSimpleTriangleMesh<Eigen::MatrixXf, Eigen::MatrixXi>,
        nb::arg("name"), nb::arg("vertices"), nb::arg("faces"),
        "Register a simple triangle mesh", nb::rv_policy::reference);

  m.def("remove_simple_triangle_mesh", &ps::removeSimpleTriangleMesh,
        nb::arg("name"), nb::arg("error_if_absent") = false,
        "Remove a simple triangle mesh by name");
  m.def("get_simple_triangle_mesh", &ps::getSimpleTriangleMesh,
        nb::arg("name") = "", "Get a simple triangle mesh by name", nb::rv_policy::reference);
  m.def("has_simple_triangle_mesh", &ps::hasSimpleTriangleMesh,
        nb::arg("name") = "", "Check for a simple triangle mesh by name");
}
