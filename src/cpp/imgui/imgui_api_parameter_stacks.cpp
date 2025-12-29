#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_parameter_stacks(nb::module_& m) {

    // Parameters stacks (shared)
    // IMGUI_API void          PushFont(ImFont* font);
    m.def(
        "PushFont",
        [](ImFont* font) { ImGui::PushFont(font); },
        nb::arg("font"));

    // IMGUI_API void          PopFont();
    m.def("PopFont", []() { ImGui::PopFont(); });

    // IMGUI_API void          PushStyleColor(ImGuiCol idx, ImU32 col);
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); },
        nb::arg("idx"),
        nb::arg("col"));

    // IMGUI_API void          PushStyleColor(ImGuiCol idx, const ImVec4& col);
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, const Vec4T& col) { ImGui::PushStyleColor(idx, to_vec4(col)); },
        nb::arg("idx"),
        nb::arg("col"));

    // IMGUI_API void          PopStyleColor(int count = 1);
    m.def(
        "PopStyleColor",
        [](int count) { ImGui::PopStyleColor(count); },
        nb::arg("count") = 1);

    // IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, float val);
    m.def(
        "PushStyleVar",
        [](ImGuiStyleVar idx, float val) { ImGui::PushStyleVar(idx, val); },
        nb::arg("idx"),
        nb::arg("val"));

    // IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
    m.def(
        "PushStyleVar",
        [](ImGuiStyleVar idx, const Vec2T& val) { ImGui::PushStyleVar(idx, to_vec2(val)); },
        nb::arg("idx"),
        nb::arg("val"));

    // IMGUI_API void          PushStyleVarX(ImGuiStyleVar idx, float val_x);
    m.def(
        "PushStyleVarX",
        [](ImGuiStyleVar idx, float val_x) { ImGui::PushStyleVarX(idx, val_x); },
        nb::arg("idx"),
        nb::arg("val_x"));

    // IMGUI_API void          PushStyleVarY(ImGuiStyleVar idx, float val_y);
    m.def(
        "PushStyleVarY",
        [](ImGuiStyleVar idx, float val_y) { ImGui::PushStyleVarY(idx, val_y); },
        nb::arg("idx"),
        nb::arg("val_y"));

    // IMGUI_API void          PopStyleVar(int count = 1);
    m.def(
        "PopStyleVar",
        [](int count) { ImGui::PopStyleVar(count); },
        nb::arg("count") = 1);

    // IMGUI_API void          PushItemFlag(ImGuiItemFlags option, bool enabled);
    m.def(
        "PushItemFlag",
        [](ImGuiItemFlags option, bool enabled) { ImGui::PushItemFlag(option, enabled); },
        nb::arg("option"),
        nb::arg("enabled"));

    // IMGUI_API void          PopItemFlag();
    m.def("PopItemFlag", []() { ImGui::PopItemFlag(); });

    // Parameters stacks (current window)
    // IMGUI_API void          PushItemWidth(float item_width);
    m.def(
        "PushItemWidth",
        [](float item_width) { ImGui::PushItemWidth(item_width); },
        nb::arg("item_width"));

    // IMGUI_API void          PopItemWidth();
    m.def("PopItemWidth", []() { ImGui::PopItemWidth(); });

    // IMGUI_API void          SetNextItemWidth(float item_width);
    m.def(
        "SetNextItemWidth",
        [](float item_width) { ImGui::SetNextItemWidth(item_width); },
        nb::arg("item_width"));

    // IMGUI_API float         CalcItemWidth();
    m.def("CalcItemWidth", []() { return ImGui::CalcItemWidth(); });

    // IMGUI_API void          PushTextWrapPos(float wrap_local_pos_x = 0.0f);
    m.def(
        "PushTextWrapPos",
        [](float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); },
        nb::arg("wrap_local_pos_x") = 0.0f);

    // IMGUI_API void          PopTextWrapPos();
    m.def("PopTextWrapPos", []() { ImGui::PopTextWrapPos(); });

}
// clang-format on
