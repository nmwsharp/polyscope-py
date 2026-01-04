#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_child_windows(nb::module_& m) {

    // Child Windows
    // IMGUI_API bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    m.def(
        "BeginChild",
        [](const char* str_id, Vec2T size, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags) {
            return ImGui::BeginChild(str_id, to_vec2(size), child_flags, window_flags);
        },
        nb::arg("str_id"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("child_flags") = 0,
        nb::arg("window_flags") = 0);

    // IMGUI_API bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    m.def(
        "BeginChild",
        [](ImGuiID id, const Vec2T& size, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags) {
            return ImGui::BeginChild(id, to_vec2(size), child_flags, window_flags);
        },
        nb::arg("id"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("child_flags") = 0,
        nb::arg("window_flags") = 0);

    // IMGUI_API void          EndChild();
    m.def("EndChild", []() { ImGui::EndChild(); });

}
// clang-format on
