#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"

#include "polyscope/floating_quantities.h"
#include "polyscope/image_quantity.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;

template <typename T>
py::class_<ps::render::ManagedBuffer<T>> bind_managed_buffer_T(py::module& m, ps::ManagedBufferType t) {

  return py::class_<ps::render::ManagedBuffer<T>>(m, ("ManagedBuffer_" + ps::typeName(t)).c_str())
      .def("size", &ps::render::ManagedBuffer<T>::size)
      .def("get_texture_size", &ps::render::ManagedBuffer<T>::getTextureSize)
      .def("has_data", &ps::render::ManagedBuffer<T>::hasData)
      .def("summary_string", &ps::render::ManagedBuffer<T>::summaryString)
      .def("get_device_buffer_type", &ps::render::ManagedBuffer<T>::getDeviceBufferType)
      .def("get_generic_weak_handle",
           [](ps::render::ManagedBuffer<T>& s) {
             return s.getGenericWeakHandle();
           } /* intentionally let Python manage ownership */)
      .def("get_value", overload_cast_<size_t>()(&ps::render::ManagedBuffer<T>::getValue))
      .def("get_value", overload_cast_<size_t, size_t>()(&ps::render::ManagedBuffer<T>::getValue))
      .def("get_value", overload_cast_<size_t, size_t, size_t>()(&ps::render::ManagedBuffer<T>::getValue))
      .def("mark_host_buffer_updated", &ps::render::ManagedBuffer<T>::markHostBufferUpdated)
      .def("get_device_buffer_size_in_bytes",
           [](ps::render::ManagedBuffer<T>& s) {
             // NOTE: this could cause the underlying device buffer to be allocatred if it wasn't already
             if (s.getDeviceBufferType() == polyscope::DeviceBufferType::Attribute) {
               return s.getRenderAttributeBuffer()->getDataSizeInBytes();
             } else {
               return s.getRenderTextureBuffer()->getSizeInBytes();
             }
           })
      .def("get_device_buffer_element_size_in_bytes",
           [](ps::render::ManagedBuffer<T>& s) {
             // NOTE: this could cause the underlying device buffer to be allocatred if it wasn't already
             if (s.getDeviceBufferType() == polyscope::DeviceBufferType::Attribute) {
               std::shared_ptr<polyscope::render::AttributeBuffer> buff = s.getRenderAttributeBuffer();
               return polyscope::sizeInBytes(buff->getType()) * buff->getArrayCount();
             } else {
               std::shared_ptr<polyscope::render::TextureBuffer> buff = s.getRenderTextureBuffer();
               return polyscope::sizeInBytes(buff->getFormat());
             }
           })
      .def("get_native_render_attribute_buffer_ID",
           [](ps::render::ManagedBuffer<T>& s) { return s.getRenderAttributeBuffer()->getNativeBufferID(); })
      .def("mark_render_attribute_buffer_updated", &ps::render::ManagedBuffer<T>::markRenderAttributeBufferUpdated)
      .def("get_native_render_texture_buffer_ID",
           [](ps::render::ManagedBuffer<T>& s) { return s.getRenderTextureBuffer()->getNativeBufferID(); })
      .def("mark_render_texture_buffer_updated", &ps::render::ManagedBuffer<T>::markRenderTextureBufferUpdated)


      ;
}

// clang-format off
void bind_managed_buffer(py::module& m) {

  // explicit template instantiations
  
  bind_managed_buffer_T<float>(m, ps::ManagedBufferType::Float)
    .def("update_data", [](ps::render::ManagedBuffer<float>& s, Eigen::VectorXf& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()));
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = d(i);
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<double>(m, ps::ManagedBufferType::Double)
    .def("update_data", [](ps::render::ManagedBuffer<double>& s, Eigen::VectorXd& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()));
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = d(i);
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<glm::vec2>(m, ps::ManagedBufferType::Vec2)
    .def("update_data", [](ps::render::ManagedBuffer<glm::vec2>& s, Eigen::Matrix<float, Eigen::Dynamic, 2>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 2");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1)};
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<glm::vec3>(m, ps::ManagedBufferType::Vec3)
    .def("update_data", [](ps::render::ManagedBuffer<glm::vec3>& s, Eigen::Matrix<float, Eigen::Dynamic, 3>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 3");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1), d(i,2)};
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<glm::vec4>(m, ps::ManagedBufferType::Vec4)
    .def("update_data", [](ps::render::ManagedBuffer<glm::vec4>& s, Eigen::Matrix<float, Eigen::Dynamic, 4>& d) {
      if(d.rows() != s.size() || d.cols() != 4) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 4");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1), d(i,2), d(i,3)};
      s.markHostBufferUpdated();
    })
  ;
  
  bind_managed_buffer_T<std::array<glm::vec3,2>>(m, ps::ManagedBufferType::Arr2Vec3)
    .def("update_data", [](ps::render::ManagedBuffer<std::array<glm::vec3,2>>& s, std::array<Eigen::Matrix<float, Eigen::Dynamic, 3>,2>& d) {
      for(uint32_t k = 0; k < 2; k++) {
        if(d[k].rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 3");
      }
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) {
        for(uint32_t k = 0; k < 2; k++) {
          s.data[i][k] = {d[k](i,0), d[k](i,1), d[k](i,2)};
        }
      }
      s.markHostBufferUpdated();
    })
  ;


  bind_managed_buffer_T<std::array<glm::vec3,3>>(m, ps::ManagedBufferType::Arr3Vec3)
    .def("update_data", [](ps::render::ManagedBuffer<std::array<glm::vec3,3>>& s, std::array<Eigen::Matrix<float, Eigen::Dynamic, 3>,3>& d) {
      for(uint32_t k = 0; k < 3; k++) {
        if(d[k].rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 3");
      }
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) {
        for(uint32_t k = 0; k < 3; k++) {
          s.data[i][k] = {d[k](i,0), d[k](i,1), d[k](i,2)};
        }
      }
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<std::array<glm::vec3,4>>(m, ps::ManagedBufferType::Arr4Vec3)
    .def("update_data", [](ps::render::ManagedBuffer<std::array<glm::vec3,4>>& s, std::array<Eigen::Matrix<float, Eigen::Dynamic, 3>,4>& d) {
      for(uint32_t k = 0; k < 4; k++) {
        if(d[k].rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 3");
      }
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) {
        for(uint32_t k = 0; k < 4; k++) {
          s.data[i][k] = {d[k](i,0), d[k](i,1), d[k](i,2)};
        }
      }
      s.markHostBufferUpdated();
    })
  ;
  
  bind_managed_buffer_T<uint32_t>(m, ps::ManagedBufferType::UInt32)
    .def("update_data", [](ps::render::ManagedBuffer<uint32_t>& s, Eigen::Matrix<uint32_t, Eigen::Dynamic, 1>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()));
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = d(i);
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<int32_t>(m, ps::ManagedBufferType::Int32)
    .def("update_data", [](ps::render::ManagedBuffer<uint32_t>& s, Eigen::Matrix<int32_t, Eigen::Dynamic, 1>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()));
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = d(i);
      s.markHostBufferUpdated();
    })
  ;
  
  bind_managed_buffer_T<glm::uvec2>(m, ps::ManagedBufferType::UVec2)
    .def("update_data", [](ps::render::ManagedBuffer<glm::uvec2>& s, Eigen::Matrix<uint32_t, Eigen::Dynamic, 2>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 2");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1)};
      s.markHostBufferUpdated();
    })
  ;


  bind_managed_buffer_T<glm::uvec3>(m, ps::ManagedBufferType::UVec3)
    .def("update_data", [](ps::render::ManagedBuffer<glm::uvec3>& s, Eigen::Matrix<uint32_t, Eigen::Dynamic, 3>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 3");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1), d(i,2)};
      s.markHostBufferUpdated();
    })
  ;

  bind_managed_buffer_T<glm::uvec4>(m, ps::ManagedBufferType::UVec4)
    .def("update_data", [](ps::render::ManagedBuffer<glm::uvec4>& s, Eigen::Matrix<uint32_t, Eigen::Dynamic, 4>& d) {
      if(d.rows() != s.size()) ps::exception("bad update size, should be " + std::to_string(s.size()) + " x 4");
      s.ensureHostBufferAllocated();
      for(uint32_t i = 0; i < s.size(); i++) s.data[i] = {d(i,0), d(i,1), d(i,2), d(i,3)};
      s.markHostBufferUpdated();
    })
  ;

}
