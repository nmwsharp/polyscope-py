#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_tooltips(nb::module_& m) {

    // Tooltips
    // IMGUI_API bool          BeginTooltip();
    m.def("BeginTooltip", []() { return ImGui::BeginTooltip(); });

    // IMGUI_API void          EndTooltip();
    m.def("EndTooltip", []() { ImGui::EndTooltip(); });

    // IMGUI_API void          SetTooltip(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "SetTooltip",
        [](const char* text) { ImGui::SetTooltip("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          SetTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: Variadic version not bound

    // IMGUI_API bool          BeginItemTooltip();
    m.def("BeginItemTooltip", []() { return ImGui::BeginItemTooltip(); });

    // IMGUI_API void          SetItemTooltip(const char* fmt, ...) IM_FMTARGS(1);
    m.def(
        "SetItemTooltip",
        [](const char* text) { ImGui::SetItemTooltip("%s", text); },
        nb::arg("text"));

    // IMGUI_API void          SetItemTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);
    // TODO: Variadic version not bound

}
// clang-format on
