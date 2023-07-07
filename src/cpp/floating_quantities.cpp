#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/polyscope.h"

#include "polyscope/floating_quantities.h"
#include "polyscope/image_quantity.h"

#include "utils.h"

namespace py = pybind11;
namespace ps = polyscope;

// For overloaded functions, with C++11 compiler only
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;


// clang-format off
void bind_floating_quantities(py::module& m) {

  // == Global floating quantity management

  // global floating quantity structure
  bindStructure<ps::FloatingQuantityStructure >(m, "FloatingQuantityStructure");
  m.def("get_global_floating_quantity_structure", &ps::getGlobalFloatingQuantityStructure, py::return_value_policy::reference);

  m.def("remove_floating_quantity", &ps::removeFloatingQuantity);
  m.def("remove_all_floating_quantities", &ps::removeAllFloatingQuantities);

  // == Image floating quantities
  
  bindScalarQuantity<ps::ScalarImageQuantity>(m, "ScalarImageQuantity");
  bindColorQuantity<ps::ColorImageQuantity>(m, "ColorImageQuantity");

  m.def("add_scalar_image_quantity", &ps::addScalarImageQuantity<Eigen::VectorXd>);
  m.def("add_color_image_quantity", &ps::addColorImageQuantity<Eigen::MatrixXd>);
  m.def("add_color_alpha_image_quantity", &ps::addColorAlphaImageQuantity<Eigen::MatrixXd>);

  // == Render image floating quantities
 
  bindQuantity<ps::DepthRenderImageQuantity>(m, "DepthRenderImageQuantity");
  bindScalarQuantity<ps::ScalarRenderImageQuantity>(m, "ScalarRenderImageQuantity");
  bindColorQuantity<ps::ColorRenderImageQuantity>(m, "ColorRenderImageQuantity");
  
  m.def("add_depth_render_image_quantity", &ps::addDepthRenderImageQuantity<Eigen::VectorXd, Eigen::MatrixXd>);
  m.def("add_color_render_image_quantity", &ps::addColorRenderImageQuantity<Eigen::VectorXd, Eigen::MatrixXd, Eigen::MatrixXd>);
  m.def("add_scalar_render_image_quantity", &ps::addScalarRenderImageQuantity<Eigen::VectorXd, Eigen::MatrixXd, Eigen::VectorXd>);

}

// clang-format on
