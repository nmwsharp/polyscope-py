#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_window_manipulation(nb::module_& m) {

    // Window manipulation
    // IMGUI_API void          SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0));
    m.def(
        "SetNextWindowPos",
        [](const Vec2T& pos, ImGuiCond cond, const Vec2T& pivot) {
            ImGui::SetNextWindowPos(to_vec2(pos), cond, to_vec2(pivot));
        },
        nb::arg("pos"),
        nb::arg("cond") = 0,
        nb::arg("pivot") = Vec2T(0., 0.));

    // IMGUI_API void          SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    m.def(
        "SetNextWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetNextWindowSize(to_vec2(size), cond); },
        nb::arg("size"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL);
    // TODO: bind callback version
    m.def(
        "SetNextWindowSizeConstraints",
        [](const Vec2T& size_min, const Vec2T& size_max) {
            ImGui::SetNextWindowSizeConstraints(to_vec2(size_min), to_vec2(size_max));
        },
        nb::arg("size_min"),
        nb::arg("size_max"));

    // IMGUI_API void          SetNextWindowContentSize(const ImVec2& size);
    m.def(
        "SetNextWindowContentSize",
        [](const Vec2T& size) { ImGui::SetNextWindowContentSize(to_vec2(size)); },
        nb::arg("size"));

    // IMGUI_API void          SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    m.def(
        "SetNextWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetNextWindowCollapsed(collapsed, cond); },
        nb::arg("collapsed"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetNextWindowFocus();
    m.def("SetNextWindowFocus", []() { ImGui::SetNextWindowFocus(); });

    // IMGUI_API void          SetNextWindowScroll(const ImVec2& scroll);
    m.def(
        "SetNextWindowScroll",
        [](const Vec2T& scroll) { ImGui::SetNextWindowScroll(to_vec2(scroll)); },
        nb::arg("scroll"));

    // IMGUI_API void          SetNextWindowBgAlpha(float alpha);
    m.def(
        "SetNextWindowBgAlpha",
        [](float alpha) { ImGui::SetNextWindowBgAlpha(alpha); },
        nb::arg("alpha"));

    // IMGUI_API void          SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
    m.def(
        "SetWindowPos",
        [](const Vec2T& pos, ImGuiCond cond) { ImGui::SetWindowPos(to_vec2(pos), cond); },
        nb::arg("pos"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    m.def(
        "SetWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetWindowSize(to_vec2(size), cond); },
        nb::arg("size"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    m.def(
        "SetWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(collapsed, cond); },
        nb::arg("collapsed"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowFocus();
    m.def("SetWindowFocus", []() { ImGui::SetWindowFocus(); });

    // IMGUI_API void          SetWindowFontScale(float scale);
    m.def(
        "SetWindowFontScale",
        [](float scale) { ImGui::SetWindowFontScale(scale); },
        nb::arg("scale"));

    // IMGUI_API void          SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);
    m.def(
        "SetWindowPos",
        [](const char* name, const Vec2T& pos, ImGuiCond cond) {
            ImGui::SetWindowPos(name, to_vec2(pos), cond);
        },
        nb::arg("name"),
        nb::arg("pos"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);
    m.def(
        "SetWindowSize",
        [](const char* name, const Vec2T& size, ImGuiCond cond) {
            ImGui::SetWindowSize(name, to_vec2(size), cond);
        },
        nb::arg("name"),
        nb::arg("size"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);
    m.def(
        "SetWindowCollapsed",
        [](const char* name, bool collapsed, ImGuiCond cond) {
            ImGui::SetWindowCollapsed(name, collapsed, cond);
        },
        nb::arg("name"),
        nb::arg("collapsed"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetWindowFocus(const char* name);
    m.def(
        "SetWindowFocus",
        [](const char* name) { ImGui::SetWindowFocus(name); },
        nb::arg("name"));

}
// clang-format on
