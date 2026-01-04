#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_tables(nb::module_& m) {

    // Tables
    // IMGUI_API bool          BeginTable(const char* str_id, int columns, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f);
    m.def(
        "BeginTable",
        [](const char* str_id, int columns, ImGuiTableFlags flags, const Vec2T& outer_size, float inner_width) {
            return ImGui::BeginTable(str_id, columns, flags, to_vec2(outer_size), inner_width);
        },
        nb::arg("str_id"),
        nb::arg("columns"),
        nb::arg("flags") = 0,
        nb::arg("outer_size") = Vec2T(0.f, 0.f),
        nb::arg("inner_width") = 0.0f);

    // IMGUI_API void          EndTable();
    m.def("EndTable", []() { ImGui::EndTable(); });

    // IMGUI_API void          TableNextRow(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f);
    m.def(
        "TableNextRow",
        [](ImGuiTableRowFlags row_flags, float min_row_height) {
            ImGui::TableNextRow(row_flags, min_row_height);
        },
        nb::arg("row_flags") = 0,
        nb::arg("min_row_height") = 0.0f);

    // IMGUI_API bool          TableNextColumn();
    m.def("TableNextColumn", []() { return ImGui::TableNextColumn(); });

    // IMGUI_API bool          TableSetColumnIndex(int column_n);
    m.def(
        "TableSetColumnIndex",
        [](int column_n) { return ImGui::TableSetColumnIndex(column_n); },
        nb::arg("column_n"));

    // IMGUI_API void          TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
    m.def(
        "TableSetupColumn",
        [](const char* label, ImGuiTableColumnFlags flags, float init_width_or_weight, ImGuiID user_id) {
            ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id);
        },
        nb::arg("label"),
        nb::arg("flags") = 0,
        nb::arg("init_width_or_weight") = 0.0f,
        nb::arg("user_id") = 0);

    // IMGUI_API void          TableSetupScrollFreeze(int cols, int rows);
    m.def(
        "TableSetupScrollFreeze",
        [](int cols, int rows) { ImGui::TableSetupScrollFreeze(cols, rows); },
        nb::arg("cols"),
        nb::arg("rows"));

    // IMGUI_API void          TableHeader(const char* label);
    m.def(
        "TableHeader",
        [](const char* label) { ImGui::TableHeader(label); },
        nb::arg("label"));

    // IMGUI_API void          TableHeadersRow();
    m.def("TableHeadersRow", []() { ImGui::TableHeadersRow(); });

    // IMGUI_API void          TableAngledHeadersRow();
    m.def("TableAngledHeadersRow", []() { ImGui::TableAngledHeadersRow(); });

    // IMGUI_API ImGuiTableSortSpecs*  TableGetSortSpecs();
    m.def("TableGetSortSpecs", []() { return ImGui::TableGetSortSpecs(); }, nb::rv_policy::reference);

    // IMGUI_API int                   TableGetColumnCount();
    m.def("TableGetColumnCount", []() { return ImGui::TableGetColumnCount(); });

    // IMGUI_API int                   TableGetColumnIndex();
    m.def("TableGetColumnIndex", []() { return ImGui::TableGetColumnIndex(); });

    // IMGUI_API int                   TableGetRowIndex();
    m.def("TableGetRowIndex", []() { return ImGui::TableGetRowIndex(); });

    // IMGUI_API const char*           TableGetColumnName(int column_n = -1);
    m.def(
        "TableGetColumnName",
        [](int column_n) { return ImGui::TableGetColumnName(column_n); },
        nb::arg("column_n") = -1);

    // IMGUI_API ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1);
    m.def(
        "TableGetColumnFlags",
        [](int column_n) { return ImGui::TableGetColumnFlags(column_n); },
        nb::arg("column_n") = -1);

    // IMGUI_API void                  TableSetColumnEnabled(int column_n, bool v);
    m.def(
        "TableSetColumnEnabled",
        [](int column_n, bool v) { ImGui::TableSetColumnEnabled(column_n, v); },
        nb::arg("column_n"),
        nb::arg("v"));

    // IMGUI_API int                   TableGetHoveredColumn();
    m.def("TableGetHoveredColumn", []() { return ImGui::TableGetHoveredColumn(); });

    // IMGUI_API void                  TableSetBgColor(ImGuiTableBgTarget target, ImU32 color, int column_n = -1);
    m.def(
        "TableSetBgColor",
        [](ImGuiTableBgTarget target, ImU32 color, int column_n) {
            ImGui::TableSetBgColor(target, color, column_n);
        },
        nb::arg("target"),
        nb::arg("color"),
        nb::arg("column_n") = -1);

}
// clang-format on
