#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_columns_legacy(nb::module_& m) {

    // Legacy Columns API (prefer using Tables!)
    // IMGUI_API void          Columns(int count = 1, const char* id = NULL, bool borders = true);
    m.def(
        "Columns",
        [](int count, const char* id, bool borders) { ImGui::Columns(count, id, borders); },
        nb::arg("count") = 1,
        nb::arg("id") = nb::none(),
        nb::arg("borders") = true);

    // IMGUI_API void          NextColumn();
    m.def("NextColumn", []() { ImGui::NextColumn(); });

    // IMGUI_API int           GetColumnIndex();
    m.def("GetColumnIndex", []() { return ImGui::GetColumnIndex(); });

    // IMGUI_API float         GetColumnWidth(int column_index = -1);
    m.def(
        "GetColumnWidth",
        [](int column_index) { return ImGui::GetColumnWidth(column_index); },
        nb::arg("column_index") = -1);

    // IMGUI_API void          SetColumnWidth(int column_index, float width);
    m.def(
        "SetColumnWidth",
        [](int column_index, float width) { ImGui::SetColumnWidth(column_index, width); },
        nb::arg("column_index"),
        nb::arg("width"));

    // IMGUI_API float         GetColumnOffset(int column_index = -1);
    m.def(
        "GetColumnOffset",
        [](int column_index) { return ImGui::GetColumnOffset(column_index); },
        nb::arg("column_index") = -1);

    // IMGUI_API void          SetColumnOffset(int column_index, float offset_x);
    m.def(
        "SetColumnOffset",
        [](int column_index, float offset_x) { ImGui::SetColumnOffset(column_index, offset_x); },
        nb::arg("column_index"),
        nb::arg("offset_x"));

    // IMGUI_API int           GetColumnsCount();
    m.def("GetColumnsCount", []() { return ImGui::GetColumnsCount(); });

}
// clang-format on
