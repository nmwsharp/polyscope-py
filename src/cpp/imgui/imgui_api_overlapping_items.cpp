#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_overlapping_items(nb::module_& m) {

    // Overlapping mode
    // IMGUI_API void          SetNextItemAllowOverlap();
    m.def("SetNextItemAllowOverlap", []() { ImGui::SetNextItemAllowOverlap(); });

}
// clang-format on
