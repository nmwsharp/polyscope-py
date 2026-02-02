#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_drag_drop(nb::module_& m) {

    // Drag and Drop
    // IMGUI_API bool          BeginDragDropSource(ImGuiDragDropFlags flags = 0);
    m.def(
        "BeginDragDropSource",
        [](ImGuiDragDropFlags flags) { return ImGui::BeginDragDropSource(flags); },
        nb::arg("flags") = 0);

    // IMGUI_API bool          SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0);
    m.def(
        "SetDragDropPayload",
        [](const char* type, const std::string& data, ImGuiCond cond) {
            return ImGui::SetDragDropPayload(type, data.c_str(), data.size(), cond);
        },
        nb::arg("type"),
        nb::arg("data"),
        nb::arg("cond") = 0);

    // IMGUI_API void          EndDragDropSource();
    m.def("EndDragDropSource", []() { ImGui::EndDragDropSource(); });

    // IMGUI_API bool                  BeginDragDropTarget();
    m.def("BeginDragDropTarget", []() { return ImGui::BeginDragDropTarget(); });

    // IMGUI_API const ImGuiPayload*   AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);
    m.def(
        "AcceptDragDropPayload",
        [](const char* type, ImGuiDragDropFlags flags) {
            return ImGui::AcceptDragDropPayload(type, flags);
        },
        nb::arg("type"),
        nb::arg("flags") = 0,
        nb::rv_policy::reference);

    // IMGUI_API void                  EndDragDropTarget();
    m.def("EndDragDropTarget", []() { ImGui::EndDragDropTarget(); });

    // IMGUI_API const ImGuiPayload*   GetDragDropPayload();
    m.def("GetDragDropPayload", []() { return ImGui::GetDragDropPayload(); }, nb::rv_policy::reference);

}
// clang-format on
