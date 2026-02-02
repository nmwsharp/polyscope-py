#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_viewports(nb::module_& m) {

    // Viewports
    // IMGUI_API ImGuiViewport* GetMainViewport();
    m.def("GetMainViewport", []() { return ImGui::GetMainViewport(); }, nb::rv_policy::reference);

}
// clang-format on
