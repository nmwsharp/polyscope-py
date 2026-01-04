#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_disabling(nb::module_& m) {

    // Disabling [BETA API]
    // IMGUI_API void          BeginDisabled(bool disabled = true);
    m.def(
        "BeginDisabled",
        [](bool disabled) { ImGui::BeginDisabled(disabled); },
        nb::arg("disabled") = true);

    // IMGUI_API void          EndDisabled();
    m.def("EndDisabled", []() { ImGui::EndDisabled(); });

}
// clang-format on
