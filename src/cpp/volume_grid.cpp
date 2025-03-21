#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"
#include "polyscope/volume_grid.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;


void bind_volume_grid(py::module& m) {

  // == Helper classes
  py::class_<ps::VolumeGridPickResult>(m, "VolumeGridPickResult")
   .def(py::init<>())
   .def_readonly("element_type", &ps::VolumeGridPickResult::elementType)
   .def_readonly("index", &ps::VolumeGridPickResult::index)
  ;

  // Scalar quantities
  bindScalarQuantity<ps::VolumeGridNodeScalarQuantity>(m, "VolumeGridNodeScalarQuantity")
    .def("set_gridcube_viz_enabled", &ps::VolumeGridNodeScalarQuantity::setGridcubeVizEnabled)
    .def("set_isosurface_viz_enabled", &ps::VolumeGridNodeScalarQuantity::setIsosurfaceVizEnabled)
    .def("set_isosurface_level", &ps::VolumeGridNodeScalarQuantity::setIsosurfaceLevel)
    .def("set_isosurface_color", &ps::VolumeGridNodeScalarQuantity::setIsosurfaceColor)
    .def("set_slice_planes_affect_isosurface", &ps::VolumeGridNodeScalarQuantity::setSlicePlanesAffectIsosurface)
    .def("register_isosurface_as_mesh_with_name", 
        [](ps::VolumeGridNodeScalarQuantity& x, std::string name) { return x.registerIsosurfaceAsMesh(name); }, 
        py::return_value_policy::reference)
    ;

  bindScalarQuantity<ps::VolumeGridCellScalarQuantity>(m, "VolumeGridCellScalarQuantity")
    .def("set_gridcube_viz_enabled", &ps::VolumeGridCellScalarQuantity::setGridcubeVizEnabled)
    ;

  // == Main class
  bindStructure<ps::VolumeGrid>(m, "VolumeGrid")

      // basics
      .def("n_nodes", &ps::VolumeGrid::nNodes)
      .def("n_cells", &ps::VolumeGrid::nCells)
      .def("grid_spacing", &ps::VolumeGrid::gridSpacing)
      .def("get_grid_node_dim", &ps::VolumeGrid::getGridNodeDim)
      .def("get_grid_cell_dim", &ps::VolumeGrid::getGridCellDim)
      .def("get_bound_min", [](ps::VolumeGrid& x) { return glm2eigen(x.getBoundMin()); })
      .def("get_bound_max", [](ps::VolumeGrid& x) { return glm2eigen(x.getBoundMax()); })
      
      .def("mark_nodes_as_used", &ps::VolumeGrid::markNodesAsUsed)
      .def("mark_cells_as_used", &ps::VolumeGrid::markCellsAsUsed)

      // options
      .def("set_color", &ps::VolumeGrid::setColor)
      .def("get_color", &ps::VolumeGrid::getColor)
      .def("set_edge_color", &ps::VolumeGrid::setEdgeColor)
      .def("get_edge_color", &ps::VolumeGrid::getEdgeColor)
      .def("set_material", &ps::VolumeGrid::setMaterial, "Set material")
      .def("get_material", &ps::VolumeGrid::getMaterial, "Get material")
      .def("set_edge_width", &ps::VolumeGrid::setEdgeWidth, "Set edge width")
      .def("get_edge_width", &ps::VolumeGrid::getEdgeWidth, "Get edge width")
      .def("set_cube_size_factor", &ps::VolumeGrid::setCubeSizeFactor, "Set cube size factor")
      .def("get_cube_size_factor", &ps::VolumeGrid::getCubeSizeFactor, "Get cube size factor")

      // picking
      .def("interpret_pick_result", &ps::VolumeGrid::interpretPickResult)

      // = quantities

      // Scalars
      .def("add_node_scalar_quantity", &ps::VolumeGrid::addNodeScalarQuantity<Eigen::VectorXf>, 
          py::arg("name"), py::arg("values"), py::arg("data_type") = ps::DataType::STANDARD, 
          py::return_value_policy::reference)

      .def("add_cell_scalar_quantity", &ps::VolumeGrid::addCellScalarQuantity<Eigen::VectorXf>,
          py::arg("name"), py::arg("values"), py::arg("data_type") = ps::DataType::STANDARD, 
          py::return_value_policy::reference)
      
      // add from a callable lambda
      .def("add_node_scalar_quantity_from_callable", [](
            ps::VolumeGrid& grid,
            std::string name, 
            const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
            ps::DataType data_type) { 

          // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
          // Create a wrapper function that goes to/from the Eigen mats
          auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
            Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
            Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
            mapped_result = func(mapped_pos);
          };

          return grid.addNodeScalarQuantityFromBatchCallable(name, wrapped_func, data_type);
      }, 
      py::arg("name"), py::arg("values"), py::arg("data_type") = ps::DataType::STANDARD,
      py::return_value_policy::reference)
      
      .def("add_cell_scalar_quantity_from_callable", [](
            ps::VolumeGrid& grid,
            std::string name, 
            const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
            ps::DataType data_type) { 

          // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
          // Create a wrapper function that goes to/from the Eigen mats
          auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
            Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
            Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
            mapped_result = func(mapped_pos);
          };

          return grid.addNodeScalarQuantityFromBatchCallable(name, wrapped_func, data_type);
      }, 
      py::arg("name"), py::arg("values"), py::arg("data_type") = ps::DataType::STANDARD,
      py::return_value_policy::reference)

      // Colors

      // Vectors

    ;

  // Static adders and getters
  m.def("register_volume_grid", overload_cast_<std::string, glm::uvec3, glm::vec3, glm::vec3>()(&ps::registerVolumeGrid), py::arg("name"),
        py::arg("gridNodeDim"), py::arg("boundMin"), py::arg("boundMax"), py::return_value_policy::reference);

  m.def("remove_volume_grid", &polyscope::removeVolumeGrid);
  m.def("get_volume_grid", &polyscope::getVolumeGrid, py::return_value_policy::reference);
  m.def("has_volume_grid", &polyscope::hasVolumeGrid);
}
