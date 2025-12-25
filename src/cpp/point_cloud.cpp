#include "Eigen/Dense"

#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"

#include "utils.h"

// clang-format off
void bind_point_cloud(nb::module_& m) {

  // == Helper classes
  nb::class_<ps::PointCloudPickResult>(m, "PointCloudPickResult")
   .def(nb::init<>())
   .def_ro("index", &ps::PointCloudPickResult::index)
  ;

  // Scalar quantities
  bindScalarQuantity<ps::PointCloudScalarQuantity>(m, "PointCloudScalarQuantity");

  // Color quantities
  bindColorQuantity<ps::PointCloudColorQuantity>(m, "PointCloudColorQuantity");

  // Vector quantities
  bindVectorQuantity<ps::PointCloudVectorQuantity>(m, "PointCloudVectorQuantity");

  // Parameterization quantities
  nb::class_<ps::PointCloudParameterizationQuantity>(m, "PointCloudParameterizationQuantity")
      .def("set_enabled", &ps::PointCloudParameterizationQuantity::setEnabled, "Set enabled")
      .def("set_style", &ps::PointCloudParameterizationQuantity::setStyle, "Set style")
      .def("set_grid_colors", &ps::PointCloudParameterizationQuantity::setGridColors, "Set grid colors")
      .def("set_checker_colors", &ps::PointCloudParameterizationQuantity::setCheckerColors, "Set checker colors")
      .def("set_checker_size", &ps::PointCloudParameterizationQuantity::setCheckerSize, "Set checker size")
      .def("set_color_map", &ps::PointCloudParameterizationQuantity::setColorMap, "Set color map")
    ;

  // == Main class
  bindStructure<ps::PointCloud>(m, "PointCloud")

    // basics
    .def("update_point_positions", &ps::PointCloud::updatePointPositions<Eigen::MatrixXf>, "Update point positions")
    .def("update_point_positions2D", &ps::PointCloud::updatePointPositions2D<Eigen::MatrixXf>, "Update point positions")
    .def("n_points", &ps::PointCloud::nPoints, "# points")

    // options
    .def("set_radius", &ps::PointCloud::setPointRadius, "Set radius")
    .def("get_radius", &ps::PointCloud::getPointRadius, "Get radius")
    .def("set_color", &ps::PointCloud::setPointColor, "Set color")
    .def("get_color", &ps::PointCloud::getPointColor, "Get color")
    .def("set_material", &ps::PointCloud::setMaterial, "Set material")
    .def("get_material", &ps::PointCloud::getMaterial, "Get material")
    .def("set_point_render_mode", &ps::PointCloud::setPointRenderMode, "Set point render mode")
    .def("get_point_render_mode", &ps::PointCloud::getPointRenderMode, "Get point render mode")

    // picking
    .def("interpret_pick_result", &ps::PointCloud::interpretPickResult)

    // variable radius
    .def("set_point_radius_quantity", 
        nb::overload_cast<std::string, bool>(&ps::PointCloud::setPointRadiusQuantity), 
        "Use a scalar to set radius by name", nb::arg("quantity_name"), nb::arg("autoscale")=true)
    .def("clear_point_radius_quantity", &ps::PointCloud::clearPointRadiusQuantity, "Clear any quantity setting the radius")
    
    // scalar transparency
    .def("set_transparency_quantity", 
        nb::overload_cast<std::string>(&ps::PointCloud::setTransparencyQuantity), nb::arg("quantity_name"))
    .def("clear_transparency_quantity", &ps::PointCloud::clearTransparencyQuantity)
        
    // quantities
    .def("add_color_quantity", &ps::PointCloud::addColorQuantity<Eigen::MatrixXf>, "Add a color function at points",
        nb::arg("name"), nb::arg("values"), nb::rv_policy::reference)
    .def("add_scalar_quantity", &ps::PointCloud::addScalarQuantity<Eigen::VectorXf>, "Add a scalar function at points",
        nb::arg("name"), nb::arg("values"), nb::arg("data_type")=ps::DataType::STANDARD, nb::rv_policy::reference)
    .def("add_vector_quantity", &ps::PointCloud::addVectorQuantity<Eigen::MatrixXf>, "Add a vector function at points",
        nb::arg("name"), nb::arg("values"), nb::arg("vector_type")=ps::VectorType::STANDARD, nb::rv_policy::reference)
    .def("add_vector_quantity2D", &ps::PointCloud::addVectorQuantity2D<Eigen::MatrixXf>, "Add a vector function at points",
        nb::arg("name"), nb::arg("values"), nb::arg("vector_type")=ps::VectorType::STANDARD, nb::rv_policy::reference)
    .def("add_parameterization_quantity", &ps::PointCloud::addParameterizationQuantity<Eigen::MatrixXf>, 
        nb::rv_policy::reference)

    ;

  // Static adders and getters
  m.def("register_point_cloud", &ps::registerPointCloud<Eigen::MatrixXf>, 
      nb::arg("name"), nb::arg("values"), "Register a point cloud", nb::rv_policy::reference);
  m.def("register_point_cloud2D", &ps::registerPointCloud2D<Eigen::MatrixXf>, 
      nb::arg("name"), nb::arg("values"), "Register a point cloud", nb::rv_policy::reference);
  m.def("remove_point_cloud", &polyscope::removePointCloud, "Remove a point cloud by name");
  m.def("get_point_cloud", &polyscope::getPointCloud, "Get a point cloud by name", nb::rv_policy::reference);
  m.def("has_point_cloud", &polyscope::hasPointCloud, "Check for a point cloud by name");

}
// clang-format on
