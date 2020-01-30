#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "Eigen/Dense"

#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"

namespace py = pybind11;
namespace ps = polyscope;




// Forward-declare bindings from other files
void bind_surface_mesh(py::module& m);
void bind_point_cloud(py::module& m);

// Actual binding code
// clang-format off
PYBIND11_MODULE(polyscope_bindings, m) {
  m.doc() = "Polyscope low-level bindings";
  
  
  // === Basic flow 
  m.def("init", &ps::init, "Initialize Polyscope");
  m.def("show", &ps::show, "Show the Polyscope GUI (blocks until UI is exited)", 
      py::arg("forFrames") = std::numeric_limits<size_t>::max());

  // === Structure management
  m.def("remove_all_structures", &ps::removeAllStructures, "Remove all structures from polyscope");

  // === Small options
  m.def("set_errors_throw_exceptions", [](bool x) { ps::options::errorsThrowExceptions = x; });

  // === Enums
  py::enum_<ps::DataType>(m, "DataType")
    .value("standard", ps::DataType::STANDARD)
    .value("symmetric", ps::DataType::SYMMETRIC)
    .value("magnitude", ps::DataType::MAGNITUDE)
    .export_values(); 

  py::enum_<ps::VectorType>(m, "VectorType")
    .value("standard", ps::VectorType::STANDARD)
    .value("ambient", ps::VectorType::AMBIENT)
    .export_values(); 
 

  // Bind structures defined in other files
  bind_surface_mesh(m);
  bind_point_cloud(m);

}

// clang-format on
