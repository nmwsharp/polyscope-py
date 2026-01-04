#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_macros(nb::module_& m) {

  m.def("IM_COL32", [](uint8_t R, uint8_t G, uint8_t B, uint8_t A) { return IM_COL32(R,G,B,A); });

}
// clang-format on
