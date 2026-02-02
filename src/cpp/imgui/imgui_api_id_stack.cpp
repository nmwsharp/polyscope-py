#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_id_stack(nb::module_& m) {

    // ID stack/scopes
    // IMGUI_API void          PushID(const char* str_id);
    m.def(
        "PushID",
        [](const char* str_id) { ImGui::PushID(str_id); },
        nb::arg("str_id"));

    // IMGUI_API void          PushID(const char* str_id_begin, const char* str_id_end);
    // TODO: bind this overload

    // IMGUI_API void          PushID(const void* ptr_id);
    // TODO: bind this overload

    // IMGUI_API void          PushID(int int_id);
    m.def(
        "PushID",
        [](int int_id) { ImGui::PushID(int_id); },
        nb::arg("int_id"));

    // IMGUI_API void          PopID();
    m.def("PopID", []() { ImGui::PopID(); });

    // IMGUI_API ImGuiID       GetID(const char* str_id);
    m.def(
        "GetID",
        [](const char* str_id) { return ImGui::GetID(str_id); },
        nb::arg("str_id"));

    // IMGUI_API ImGuiID       GetID(const char* str_id_begin, const char* str_id_end);
    // TODO: bind this overload

    // IMGUI_API ImGuiID       GetID(const void* ptr_id);
    // TODO: bind this overload

    // IMGUI_API ImGuiID       GetID(int int_id);
    m.def(
        "GetID",
        [](int int_id) { return ImGui::GetID(int_id); },
        nb::arg("int_id"));

}
// clang-format on
