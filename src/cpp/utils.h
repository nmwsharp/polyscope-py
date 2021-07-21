#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;

// Add common bindings for all scalar quantities
template<typename ScalarQ>
py::class_<ScalarQ> bindScalarQuantity(py::module& m, std::string name) {
  return py::class_<ScalarQ>(m, name.c_str())
    .def("set_enabled", &ScalarQ::setEnabled, "Set enabled")
    .def("set_color_map", &ScalarQ::setColorMap, "Set color map")
    .def("set_map_range", &ScalarQ::setMapRange, "Set map range")
    .def("set_isoline_width", &ScalarQ::setIsolineWidth, "Set isoline width");
}

// Add common bindings for all color quantities
template<typename ColorQ>
py::class_<ColorQ> bindColorQuantity(py::module& m, std::string name) {
  return py::class_<ColorQ>(m, name.c_str())
    .def("set_enabled", &ColorQ::setEnabled, "Set enabled");
}

// Add common bindings for all vector quantities
template<typename VectorQ>
py::class_<VectorQ> bindVectorQuantity(py::module& m, std::string name) {
  return py::class_<VectorQ>(m, name.c_str())
      .def("set_enabled", &VectorQ::setEnabled, "Set enabled")
      .def("set_length",  &VectorQ::setVectorLengthScale, "Set length")
      .def("set_radius",  &VectorQ::setVectorRadius, "Set radius")
      .def("set_color",   &VectorQ::setVectorColor, "Set color");
}
