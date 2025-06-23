#pragma once

#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <glm/glm.hpp>

#include "Eigen/Dense"

#include "polyscope/image_quantity.h"

namespace py = pybind11;
namespace ps = polyscope;

// For overloaded functions, with C++11 compiler only
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

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

template <typename StructureT, typename T, typename C>
void def_get_managed_buffer(C& c, std::string postfix) {
  c.def(("get_buffer_" + postfix).c_str(),
        [](StructureT& s, std::string buffer_name) -> ps::render::ManagedBuffer<T>& {
          return s.template getManagedBuffer<T>(buffer_name);
        },
        "get managed buffer", py::return_value_policy::reference);
}

template <typename StructureT, typename T, typename C>
void def_get_quantity_managed_buffer(C& c, std::string postfix) {
  c.def(("get_quantity_buffer_" + postfix).c_str(),
        [](StructureT& s, std::string quantity_name, std::string buffer_name) -> ps::render::ManagedBuffer<T>& {
          ps::Quantity* qPtr = s.getQuantity(quantity_name);
          if (qPtr) {
            return qPtr->template getManagedBuffer<T>(buffer_name);
          }
          ps::FloatingQuantity* fqPtr = s.getFloatingQuantity(quantity_name);
          if (fqPtr) {
            return fqPtr->template getManagedBuffer<T>(buffer_name);
          }
          ps::exception("structure " + s.name + " has no quantity " + quantity_name);

          // this line should be unreachable, it is here to convince the compiler that we don't need a return value
          // here, to silence warnings
          throw std::logic_error("structure has no such quantity");
        },
        "get quantity managed buffer", py::return_value_policy::reference);
}


template <typename StructureT, typename T, typename C>
void def_all_managed_buffer_funcs(C& c, ps::ManagedBufferType t) {
  def_get_managed_buffer<StructureT, T>(c, ps::typeName(t));
  def_get_quantity_managed_buffer<StructureT, T>(c, ps::typeName(t));
}


// Add common bindings for structures
template <typename StructureT>
py::class_<StructureT> bindStructure(py::module& m, std::string name) {

  py::class_<StructureT, ps::Structure> s(m, name.c_str());

  // structure basics
  s.def("remove", &StructureT::remove, "Remove the structure")
      .def(
          "get_name", [](StructureT& s) { return s.name; }, "Ge the name")
      .def("get_unique_prefix", &StructureT::uniquePrefix, "Get unique prefix")
      .def("set_enabled", &StructureT::setEnabled, "Enable the structure")
      .def("enable_isolate", &StructureT::enableIsolate, "Enable the structure, disable all of same type")
      .def("is_enabled", &StructureT::isEnabled, "Check if the structure is enabled")
      .def("set_transparency", &StructureT::setTransparency, "Set transparency alpha")
      .def("get_transparency", &StructureT::getTransparency, "Get transparency alpha")

      // group things
      .def("add_to_group", overload_cast_<std::string>()(&StructureT::addToGroup), "Add to group")

      // slice plane things
      .def("set_ignore_slice_plane", &StructureT::setIgnoreSlicePlane, "Set ignore slice plane")
      .def("get_ignore_slice_plane", &StructureT::getIgnoreSlicePlane, "Get ignore slice plane")
      .def("set_cull_whole_elements", &StructureT::setCullWholeElements, "Set cull whole elements")
      .def("get_cull_whole_elements", &StructureT::getCullWholeElements, "Get cull whole elememts")

      // quantites
      .def("remove_all_quantities", &StructureT::removeAllQuantities, "Remove all quantities")
      .def("remove_quantity", &StructureT::removeQuantity, py::arg("name"), py::arg("errorIfAbsent") = false,
           "Remove a quantity")

      // transform management
      // clang-format off
      .def("center_bounding_box", &StructureT::centerBoundingBox, "center bounding box")
      .def("rescale_to_unit", &StructureT::rescaleToUnit, "set the transform so the object has length scale 1")
      .def("reset_transform", &StructureT::resetTransform, "reset the transform to the identity")
      .def("set_transform", [](StructureT& s, Eigen::Matrix4f T) { s.setTransform(eigen2glm(T)); }, "set the transform to the given 4x4 homogenous transform matrix")
      .def("set_position", [](StructureT& s, Eigen::Vector3f T) { s.setPosition(eigen2glm(T)); }, "set the translation component of the transform to the given position")
      .def("translate", [](StructureT& s, Eigen::Vector3f T) { s.translate(eigen2glm(T)); }, "apply the given translation to the shape, updating its position")
      .def("get_transform", [](StructureT& s) { return glm2eigen(s.getTransform()); }, "get the current 4x4 transform matrix")
      .def("get_position", [](StructureT& s) { return glm2eigen(s.getPosition()); }, "get the position of the shape origin after transform")
      .def("set_transform_gizmo_enabled", &StructureT::setTransformGizmoEnabled)
      .def("get_transform_gizmo_enabled", &StructureT::getTransformGizmoEnabled)
      
      // floating quantites
      .def("add_scalar_image_quantity", &StructureT::template addScalarImageQuantity<Eigen::VectorXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("values"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::arg("type")=ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_color_image_quantity", &StructureT::template addColorImageQuantity<Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("values_rgb"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)
      .def("add_color_alpha_image_quantity", &StructureT::template addColorAlphaImageQuantity<Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("values_rgba"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)
      .def("add_depth_render_image_quantity", &StructureT::template addDepthRenderImageQuantity<Eigen::VectorXf, Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("depthData"), py::arg("normalData"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)
      .def("add_color_render_image_quantity", &StructureT::template addColorRenderImageQuantity<Eigen::VectorXf, Eigen::MatrixXf, Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("depthData"), py::arg("normalData"), py::arg("colorData"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)
      .def("add_scalar_render_image_quantity", &StructureT::template addScalarRenderImageQuantity<Eigen::VectorXf, Eigen::MatrixXf, Eigen::VectorXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("depthData"), py::arg("normalData"), py::arg("scalarData"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::arg("type")=ps::DataType::STANDARD, py::return_value_policy::reference)
      .def("add_raw_color_render_image_quantity", &StructureT::template addRawColorRenderImageQuantity<Eigen::VectorXf, Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("depthData"), py::arg("colorData"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)
      .def("add_raw_color_alpha_render_image_quantity", &StructureT::template addRawColorAlphaRenderImageQuantity<Eigen::VectorXf, Eigen::MatrixXf>, py::arg("name"), py::arg("dimX"), py::arg("dimY"), py::arg("depthData"), py::arg("colorData"), py::arg("imageOrigin")=ps::ImageOrigin::UpperLeft, py::return_value_policy::reference)

      ;

      // managed buffer things
      def_all_managed_buffer_funcs<StructureT, float> (s, ps::ManagedBufferType::Float);
      def_all_managed_buffer_funcs<StructureT, double>(s, ps::ManagedBufferType::Double);
      
      def_all_managed_buffer_funcs<StructureT, glm::vec2>(s, ps::ManagedBufferType::Vec2);
      def_all_managed_buffer_funcs<StructureT, glm::vec3>(s, ps::ManagedBufferType::Vec3);
      def_all_managed_buffer_funcs<StructureT, glm::vec4>(s, ps::ManagedBufferType::Vec4);
      
      def_all_managed_buffer_funcs<StructureT, std::array<glm::vec3,2>>(s, ps::ManagedBufferType::Arr2Vec3);
      def_all_managed_buffer_funcs<StructureT, std::array<glm::vec3,3>>(s, ps::ManagedBufferType::Arr3Vec3);
      def_all_managed_buffer_funcs<StructureT, std::array<glm::vec3,4>>(s, ps::ManagedBufferType::Arr4Vec3);
      
      def_all_managed_buffer_funcs<StructureT, uint32_t> (s, ps::ManagedBufferType::UInt32);
      def_all_managed_buffer_funcs<StructureT, int32_t>  (s, ps::ManagedBufferType::Int32);
      
      def_all_managed_buffer_funcs<StructureT, glm::uvec2>(s, ps::ManagedBufferType::UVec2);
      def_all_managed_buffer_funcs<StructureT, glm::uvec3>(s, ps::ManagedBufferType::UVec3);
      def_all_managed_buffer_funcs<StructureT, glm::uvec4>(s, ps::ManagedBufferType::UVec4);

      s.def("has_buffer_type", &StructureT::hasManagedBufferType, "has managed buffer type");
      s.def("has_quantity_buffer_type", [](StructureT& s, std::string quantity_name, std::string buffer_name) {
          ps::Quantity* qPtr = s.getQuantity(quantity_name);
          if (qPtr) {
            return qPtr->hasManagedBufferType(buffer_name);
          }
          ps::FloatingQuantity* fqPtr = s.getFloatingQuantity(quantity_name);
          if (fqPtr) {
            return fqPtr->hasManagedBufferType(buffer_name);
          }
          return std::make_tuple(false, ps::ManagedBufferType::Float);
        }, "has quantity managed buffer type");


  // clang-format on
  return s;
}

// Common bindings for quantities that do not fall in to a more specific quantity below
template <typename Q>
py::class_<Q> bindQuantity(py::module& m, std::string name) {
  return py::class_<Q>(m, name.c_str()).def("set_enabled", &Q::setEnabled, "Set enabled");
}


// Add common bindings for all scalar quantities
template <typename ScalarQ>
py::class_<ScalarQ> bindScalarQuantity(py::module& m, std::string name) {
  return bindQuantity<ScalarQ>(m, name.c_str())
      .def("set_color_map", &ScalarQ::setColorMap, "Set color map")
      .def("set_map_range", &ScalarQ::setMapRange, "Set map range")
      .def("set_isolines_enabled", &ScalarQ::setIsolinesEnabled)
      .def("set_isoline_style", &ScalarQ::setIsolineStyle)
      .def("set_isoline_period", &ScalarQ::setIsolinePeriod, "Set isoline period")
      .def("set_isoline_width", &ScalarQ::setIsolineWidth, "Set isoline width") // deprecated
      .def("set_isoline_darkness", &ScalarQ::setIsolineDarkness)
      .def("set_isoline_contour_thickness", &ScalarQ::setIsolineContourThickness);
}

template <typename VolumeMeshVertexScalarQuantity>
py::class_<VolumeMeshVertexScalarQuantity> bindVMVScalarQuantity(py::module& m, std::string name) {
  return bindQuantity<VolumeMeshVertexScalarQuantity>(m, name.c_str())
      .def("set_color_map", &VolumeMeshVertexScalarQuantity::setColorMap, "Set color map")
      .def("set_map_range", &VolumeMeshVertexScalarQuantity::setMapRange, "Set map range")
      .def("set_isoline_width", &VolumeMeshVertexScalarQuantity::setIsolineWidth, "Set isoline width")
      .def("set_level_set_enable", &VolumeMeshVertexScalarQuantity::setEnabledLevelSet,
           "Set level set rendering enabled")
      .def("set_level_set_value", &VolumeMeshVertexScalarQuantity::setLevelSetValue, "Set level set value")
      .def("set_level_set_visible_quantity", &VolumeMeshVertexScalarQuantity::setLevelSetVisibleQuantity,
           "Set quantity to show on level set");
}

// Add common bindings for all color quantities
template <typename ColorQ>
py::class_<ColorQ> bindColorQuantity(py::module& m, std::string name) {
  return bindQuantity<ColorQ>(m, name.c_str());
}

// Add common bindings for all vector quantities
template <typename VectorQ>
py::class_<VectorQ> bindVectorQuantity(py::module& m, std::string name) {
  return bindQuantity<VectorQ>(m, name.c_str())
      .def("set_length", &VectorQ::setVectorLengthScale, "Set length")
      .def("set_radius", &VectorQ::setVectorRadius, "Set radius")
      .def("set_color", &VectorQ::setVectorColor, "Set color")
      .def("set_material", &VectorQ::setMaterial, "Set material");
}

// Add common bindings for all texture map quantities
// (this one is 'additive', )
template <typename TextureQ>
void addTextureMapQuantityBindings(py::class_<TextureQ>& boundTextureQ) {
  boundTextureQ.def("set_filter_mode", &TextureQ::setFilterMode, "Set filter mode");
}

// Add common image options
// Note: unlike the others above, this adds methods to an existing quantity rather than binding a new one.
template <typename ImageQ>
void addImageQuantityBindings(py::class_<ImageQ>& imageQ) {

  imageQ.def("set_show_fullscreen", &ImageQ::setShowFullscreen);
  imageQ.def("get_show_fullscreen", &ImageQ::getShowFullscreen);

  imageQ.def("set_show_in_imgui_window", &ImageQ::setShowInImGuiWindow);
  imageQ.def("get_show_in_imgui_window", &ImageQ::getShowInImGuiWindow);

  imageQ.def("set_show_in_camera_billboard", &ImageQ::setShowInCameraBillboard);
  imageQ.def("get_show_in_camera_billboard", &ImageQ::getShowInCameraBillboard);

  imageQ.def("set_transparency", &ImageQ::setTransparency);
  imageQ.def("get_transparency", &ImageQ::getTransparency);
}
