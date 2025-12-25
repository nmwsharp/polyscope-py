#include "Eigen/Dense"

#include "polyscope/polyscope.h"

#include "polyscope/floating_quantities.h"
#include "polyscope/image_quantity.h"
#include "polyscope/implicit_helpers.h"

#include "utils.h"

// clang-format off
void bind_implicit_helpers(nb::module_& m) {

  // == Render implicit surfaces

  nb::class_<ps::ImplicitRenderOpts>(m, "ImplicitRenderOpts")
    .def(nb::init<>())
    .def_rw("cameraParameters", &ps::ImplicitRenderOpts::cameraParameters)
    .def_rw("dimX", &ps::ImplicitRenderOpts::dimX)
    .def_rw("dimY", &ps::ImplicitRenderOpts::dimY)
    .def_rw("subsampleFactor", &ps::ImplicitRenderOpts::subsampleFactor)
    .def("set_missDist", [](ps::ImplicitRenderOpts& o, float val, bool isRelative) { o.missDist.set(val, isRelative); })
    .def("set_hitDist", [](ps::ImplicitRenderOpts& o, float val, bool isRelative) { o.hitDist.set(val, isRelative); })
    .def_rw("stepFactor", &ps::ImplicitRenderOpts::stepFactor)
    .def_rw("normalSampleEps", &ps::ImplicitRenderOpts::normalSampleEps)
    .def("set_stepSize", [](ps::ImplicitRenderOpts& o, float val, bool isRelative) { o.stepSize.set(val, isRelative); })
    .def_rw("nMaxSteps", &ps::ImplicitRenderOpts::nMaxSteps)
  ;


  // NOTE: we only bind the batch functions, the one-off functions would be brutally slow due to Python overhead
 

  m.def("render_implicit_surface_batch", [](
        std::string name, 
        const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
        ps::ImplicitRenderMode mode, ps::ImplicitRenderOpts opts, ps::CameraView* cameraView
      ) { 

      // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
      // Create a wrapper function that goes to/from the Eigen mats
      auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
        mapped_result = func(mapped_pos);
      };

      if(cameraView == nullptr) {
        return ps::renderImplicitSurfaceBatch(name, wrapped_func, mode, opts);
      } else {
        return ps::renderImplicitSurfaceBatch(cameraView, name, wrapped_func, mode, opts);
      }
  }, 
    nb::arg("name"),
    nb::arg("func"),
    nb::arg("mode"),
    nb::arg("opts"),
    nb::arg("cameraView") = nb::none(),
  nb::rv_policy::reference);


  m.def("render_implicit_surface_color_batch", [](
        std::string name, 
        const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
        const std::function<Eigen::MatrixXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func_color,
        ps::ImplicitRenderMode mode, ps::ImplicitRenderOpts opts, ps::CameraView* cameraView
      ) { 

      // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
      // Create a wrapper function that goes to/from the Eigen mats
      auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
        mapped_result = func(mapped_pos);
      };
      auto wrapped_func_color = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_result(result_ptr, size, 3);
        mapped_result = func_color(mapped_pos);
      };

      if(cameraView == nullptr) {
        return ps::renderImplicitSurfaceColorBatch(name, wrapped_func, wrapped_func_color, mode, opts);
      } else {
        return ps::renderImplicitSurfaceColorBatch(cameraView, name, wrapped_func, wrapped_func_color, mode, opts);
      }
  }, 
    nb::arg("name"),
    nb::arg("func"),
    nb::arg("func_color"),
    nb::arg("mode"),
    nb::arg("opts"),
    nb::arg("cameraView") = nb::none(),
  nb::rv_policy::reference);


  m.def("render_implicit_surface_scalar_batch", [](
        std::string name, 
        const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
        const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func_scalar,
        ps::ImplicitRenderMode mode, ps::ImplicitRenderOpts opts, ps::CameraView* cameraView
      ) { 

      // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
      // Create a wrapper function that goes to/from the Eigen mats
      auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
        mapped_result = func(mapped_pos);
      };
      auto wrapped_func_scalar = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
        mapped_result = func_scalar(mapped_pos);
      };

      if(cameraView == nullptr) {
        return ps::renderImplicitSurfaceScalarBatch(name, wrapped_func, wrapped_func_scalar, mode, opts);
      } else {
        return ps::renderImplicitSurfaceScalarBatch(cameraView, name, wrapped_func, wrapped_func_scalar, mode, opts);
      }
  }, 
    nb::arg("name"),
    nb::arg("func"),
    nb::arg("func_scalar"),
    nb::arg("mode"),
    nb::arg("opts"),
    nb::arg("cameraView") = nb::none(),
  nb::rv_policy::reference);
  
  m.def("render_implicit_surface_raw_color_batch", [](
        std::string name, 
        const std::function<Eigen::VectorXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func,
        const std::function<Eigen::MatrixXf(const Eigen::Ref<const Eigen::MatrixXf>)>& func_color,
        ps::ImplicitRenderMode mode, ps::ImplicitRenderOpts opts, ps::CameraView* cameraView
      ) { 

      // Polyscope's API uses raw buffer pointers, but we use Eigen mats for pybind11.
      // Create a wrapper function that goes to/from the Eigen mats
      auto wrapped_func = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::VectorXf> mapped_result(result_ptr, size);
        mapped_result = func(mapped_pos);
      };
      auto wrapped_func_color = [&](const float* pos_ptr, float* result_ptr, uint64_t size) {
        Eigen::Map<const Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_pos(pos_ptr, size, 3);
        Eigen::Map<Eigen::Matrix<float,Eigen::Dynamic,3,Eigen::RowMajor>> mapped_result(result_ptr, size, 3);
        mapped_result = func_color(mapped_pos);
      };

      if(cameraView == nullptr) {
        return ps::renderImplicitSurfaceRawColorBatch(name, wrapped_func, wrapped_func_color, mode, opts);
      } else {
        return ps::renderImplicitSurfaceRawColorBatch(cameraView, name, wrapped_func, wrapped_func_color, mode, opts);
      }
  }, 
    nb::arg("name"),
    nb::arg("func"),
    nb::arg("func_color"),
    nb::arg("mode"),
    nb::arg("opts"),
    nb::arg("cameraView") = nb::none(),
  nb::rv_policy::reference);

}

// clang-format on
