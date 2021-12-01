#pragma once

#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <glm/glm.hpp>

#include "Eigen/Dense"

namespace py = pybind11;

// Some conversion helpers
template <typename T, int m, int n>
inline glm::mat<m, n, T> eigen2glm(const Eigen::Matrix<T, m, n>& mat_eigen) {
  glm::mat<m, n, T> mat_glm;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      mat_glm[j][i] = mat_eigen(i, j);
    }
  }
  return mat_glm;
}
template <typename T, int m>
inline glm::vec<m, T> eigen2glm(const Eigen::Matrix<T, m, 1>& vec_eigen) {
  glm::vec<m, T> vec_glm;
  for (int i = 0; i < m; ++i) {
    vec_glm[i] = vec_eigen(i);
  }
  return vec_glm;
}
template <typename T, int m, int n>
inline Eigen::Matrix<T, m, n> glm2eigen(const glm::mat<m, n, T>& mat_glm) {
  Eigen::Matrix<T, m, n> mat_eigen;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      mat_eigen(i, j) = mat_glm[j][i];
    }
  }
  return mat_eigen;
}
template <typename T, int m>
inline Eigen::Matrix<T, m, 1> glm2eigen(const glm::vec<m, T>& vec_glm) {
  Eigen::Matrix<T, m, 1> vec_eigen;
  for (int i = 0; i < m; ++i) {
    vec_eigen(i) = vec_glm[i];
  }
  return vec_eigen;
}

// Add common bindings for structures
template <typename StructureT>
py::class_<StructureT> bindStructure(py::module& m, std::string name) {
  return py::class_<StructureT>(m, name.c_str())

      // structure basics
      .def("remove", &StructureT::remove, "Remove the structure")
      .def("set_enabled", &StructureT::setEnabled, "Enable the structure")
      .def("enable_isolate", &StructureT::enableIsolate, "Enable the structure, disable all of same type")
      .def("is_enabled", &StructureT::isEnabled, "Check if the structure is enabled")
      .def("set_transparency", &StructureT::setTransparency, "Set transparency alpha")
      .def("get_transparency", &StructureT::getTransparency, "Get transparency alpha")

      // quantites
      .def("remove_all_quantities", &StructureT::removeAllQuantities, "Remove all quantities")
      .def("remove_quantity", &StructureT::removeQuantity, "Remove a quantity")

      // transform management
      // clang-format off
      .def("center_bounding_box", &StructureT::centerBoundingBox, "center bounding box")
      .def("rescale_to_unit", &StructureT::rescaleToUnit, "set the transform so the object has length scale 1")
      .def("reset_transform", &StructureT::resetTransform, "reset the transform to the identity")
      .def("set_transform", [](StructureT& s, Eigen::Matrix4f T) { s.setTransform(eigen2glm(T)); }, "set the transform to the given 4x4 homogenous transform matrix")
      .def("set_position", [](StructureT& s, Eigen::Vector3f T) { s.setPosition(eigen2glm(T)); }, "set the translation component of the transform to the given position")
      .def("translate", [](StructureT& s, Eigen::Vector3f T) { s.translate(eigen2glm(T)); }, "apply the given translation to the shape, updating its position")
      .def("get_transform", [](StructureT& s) { return glm2eigen(s.getTransform()); }, "get the current 4x4 transform matrix")
      .def("get_position", [](StructureT& s) { return glm2eigen(s.getPosition()); }, "get the position of the shape origin after transform");
  // clang-format on
}


// Add common bindings for all scalar quantities
template <typename ScalarQ>
py::class_<ScalarQ> bindScalarQuantity(py::module& m, std::string name) {
  return py::class_<ScalarQ>(m, name.c_str())
      .def("set_enabled", &ScalarQ::setEnabled, "Set enabled")
      .def("set_color_map", &ScalarQ::setColorMap, "Set color map")
      .def("set_map_range", &ScalarQ::setMapRange, "Set map range")
      .def("set_isoline_width", &ScalarQ::setIsolineWidth, "Set isoline width");
}

template<typename VolumeMeshVertexScalarQuantity>
py::class_<VolumeMeshVertexScalarQuantity> bindVMVScalarQuantity(py::module& m, std::string name) {
  return py::class_<VolumeMeshVertexScalarQuantity>(m, name.c_str())
    .def("set_enabled", &VolumeMeshVertexScalarQuantity::setEnabled, "Set enabled")
    .def("set_color_map", &VolumeMeshVertexScalarQuantity::setColorMap, "Set color map")
    .def("set_map_range", &VolumeMeshVertexScalarQuantity::setMapRange, "Set map range")
    .def("set_isoline_width", &VolumeMeshVertexScalarQuantity::setIsolineWidth, "Set isoline width")
    .def("set_level_set_enable", &VolumeMeshVertexScalarQuantity::setEnabledLevelSet, "Set level set rendering enabled")
    .def("set_level_set_value", &VolumeMeshVertexScalarQuantity::setLevelSetValue, "Set level set value")
    .def("set_level_set_visible_quantity", &VolumeMeshVertexScalarQuantity::setLevelSetVisibleQuantity, "Set quantity to show on level set");
}

// Add common bindings for all color quantities
template <typename ColorQ>
py::class_<ColorQ> bindColorQuantity(py::module& m, std::string name) {
  return py::class_<ColorQ>(m, name.c_str()).def("set_enabled", &ColorQ::setEnabled, "Set enabled");
}

// Add common bindings for all vector quantities
template <typename VectorQ>
py::class_<VectorQ> bindVectorQuantity(py::module& m, std::string name) {
  return py::class_<VectorQ>(m, name.c_str())
      .def("set_enabled", &VectorQ::setEnabled, "Set enabled")
      .def("set_length", &VectorQ::setVectorLengthScale, "Set length")
      .def("set_radius", &VectorQ::setVectorRadius, "Set radius")
      .def("set_color", &VectorQ::setVectorColor, "Set color");
}
