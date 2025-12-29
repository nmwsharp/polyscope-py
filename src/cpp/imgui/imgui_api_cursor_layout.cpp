#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_cursor_layout(nb::module_& m) {

    // Layout cursor positioning
    // IMGUI_API ImVec2        GetCursorScreenPos();
    m.def("GetCursorScreenPos", []() { return from_vec2(ImGui::GetCursorScreenPos()); });

    // IMGUI_API void          SetCursorScreenPos(const ImVec2& pos);
    m.def(
        "SetCursorScreenPos",
        [](const Vec2T& pos) { ImGui::SetCursorScreenPos(to_vec2(pos)); },
        nb::arg("pos"));

    // IMGUI_API ImVec2        GetContentRegionAvail();
    m.def("GetContentRegionAvail", []() { return from_vec2(ImGui::GetContentRegionAvail()); });

    // IMGUI_API ImVec2        GetCursorPos();
    m.def("GetCursorPos", []() { return from_vec2(ImGui::GetCursorPos()); });

    // IMGUI_API float         GetCursorPosX();
    m.def("GetCursorPosX", []() { return ImGui::GetCursorPosX(); });

    // IMGUI_API float         GetCursorPosY();
    m.def("GetCursorPosY", []() { return ImGui::GetCursorPosY(); });

    // IMGUI_API void          SetCursorPos(const ImVec2& local_pos);
    m.def(
        "SetCursorPos",
        [](const Vec2T& local_pos) { ImGui::SetCursorPos(to_vec2(local_pos)); },
        nb::arg("local_pos"));

    // IMGUI_API void          SetCursorPosX(float local_x);
    m.def(
        "SetCursorPosX",
        [](float local_x) { ImGui::SetCursorPosX(local_x); },
        nb::arg("local_x"));

    // IMGUI_API void          SetCursorPosY(float local_y);
    m.def(
        "SetCursorPosY",
        [](float local_y) { ImGui::SetCursorPosY(local_y); },
        nb::arg("local_y"));

    // IMGUI_API ImVec2        GetCursorStartPos();
    m.def("GetCursorStartPos", []() { return from_vec2(ImGui::GetCursorStartPos()); });

    // Other layout functions
    // IMGUI_API void          Separator();
    m.def("Separator", []() { ImGui::Separator(); });

    // IMGUI_API void          SameLine(float offset_from_start_x=0.0f, float spacing=-1.0f);
    m.def(
        "SameLine",
        [](float offset_from_start_x, float spacing) { ImGui::SameLine(offset_from_start_x, spacing); },
        nb::arg("offset_from_start_x") = 0.0f,
        nb::arg("spacing") = -1.0f);

    // IMGUI_API void          NewLine();
    m.def("NewLine", []() { ImGui::NewLine(); });

    // IMGUI_API void          Spacing();
    m.def("Spacing", []() { ImGui::Spacing(); });

    // IMGUI_API void          Dummy(const ImVec2& size);
    m.def(
        "Dummy",
        [](const Vec2T& size) { ImGui::Dummy(to_vec2(size)); },
        nb::arg("size"));

    // IMGUI_API void          Indent(float indent_w = 0.0f);
    m.def(
        "Indent",
        [](float indent_w) { ImGui::Indent(indent_w); },
        nb::arg("indent_w") = 0.0f);

    // IMGUI_API void          Unindent(float indent_w = 0.0f);
    m.def(
        "Unindent",
        [](float indent_w) { ImGui::Unindent(indent_w); },
        nb::arg("indent_w") = 0.0f);

    // IMGUI_API void          BeginGroup();
    m.def("BeginGroup", []() { ImGui::BeginGroup(); });

    // IMGUI_API void          EndGroup();
    m.def("EndGroup", []() { ImGui::EndGroup(); });

    // IMGUI_API void          AlignTextToFramePadding();
    m.def("AlignTextToFramePadding", []() { ImGui::AlignTextToFramePadding(); });

    // IMGUI_API float         GetTextLineHeight();
    m.def("GetTextLineHeight", []() { return ImGui::GetTextLineHeight(); });

    // IMGUI_API float         GetTextLineHeightWithSpacing();
    m.def("GetTextLineHeightWithSpacing", []() { return ImGui::GetTextLineHeightWithSpacing(); });

    // IMGUI_API float         GetFrameHeight();
    m.def("GetFrameHeight", []() { return ImGui::GetFrameHeight(); });

    // IMGUI_API float         GetFrameHeightWithSpacing();
    m.def("GetFrameHeightWithSpacing", []() { return ImGui::GetFrameHeightWithSpacing(); });

}
// clang-format on
