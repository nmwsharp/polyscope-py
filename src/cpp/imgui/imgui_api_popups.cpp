#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_popups(nb::module_& m) {

    // Popups, Modals
    // IMGUI_API bool          BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);
    m.def(
        "BeginPopup",
        [](const char* str_id, ImGuiWindowFlags flags) { return ImGui::BeginPopup(str_id, flags); },
        nb::arg("str_id"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          BeginPopupModal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    m.def(
        "BeginPopupModal",
        [](const char* name, bool p_open, ImGuiWindowFlags flags) {
            bool result = ImGui::BeginPopupModal(name, &p_open, flags);
            return std::make_tuple(result, p_open);
        },
        nb::arg("name"),
        nb::arg("p_open"),
        nb::arg("flags") = 0);

    // IMGUI_API void          EndPopup();
    m.def("EndPopup", []() { ImGui::EndPopup(); });

    // Popups: open/close functions
    // IMGUI_API void          OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0);
    m.def(
        "OpenPopup",
        [](const char* str_id, ImGuiPopupFlags popup_flags) { ImGui::OpenPopup(str_id, popup_flags); },
        nb::arg("str_id"),
        nb::arg("popup_flags") = 0);

    // IMGUI_API void          OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0);
    m.def(
        "OpenPopup",
        [](ImGuiID id, ImGuiPopupFlags popup_flags) { ImGui::OpenPopup(id, popup_flags); },
        nb::arg("id"),
        nb::arg("popup_flags") = 0);

    // IMGUI_API void          OpenPopupOnItemClick(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    m.def(
        "OpenPopupOnItemClick",
        [](const char* str_id, ImGuiPopupFlags popup_flags) { ImGui::OpenPopupOnItemClick(str_id, popup_flags); },
        nb::arg("str_id") = nullptr,
        nb::arg("popup_flags") = 1);

    // IMGUI_API void          CloseCurrentPopup();
    m.def("CloseCurrentPopup", []() { ImGui::CloseCurrentPopup(); });

    // Popups: open+begin combined functions helpers
    // IMGUI_API bool          BeginPopupContextItem(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    m.def(
        "BeginPopupContextItem",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextItem(str_id, popup_flags);
        },
        nb::arg("str_id") = nullptr,
        nb::arg("popup_flags") = 1);

    // IMGUI_API bool          BeginPopupContextWindow(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    m.def(
        "BeginPopupContextWindow",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextWindow(str_id, popup_flags);
        },
        nb::arg("str_id") = nullptr,
        nb::arg("popup_flags") = 1);

    // IMGUI_API bool          BeginPopupContextVoid(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    m.def(
        "BeginPopupContextVoid",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextVoid(str_id, popup_flags);
        },
        nb::arg("str_id") = nullptr,
        nb::arg("popup_flags") = 1);

    // Popups: query functions
    // IMGUI_API bool          IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0);
    m.def(
        "IsPopupOpen",
        [](const char* str_id, ImGuiPopupFlags flags) { return ImGui::IsPopupOpen(str_id, flags); },
        nb::arg("str_id"),
        nb::arg("flags") = 0);

}
// clang-format on
