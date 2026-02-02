#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>

// clang-format off
void bind_imgui_api_menus(nb::module_& m) {

    // Widgets: Menus
    // IMGUI_API bool          BeginMenuBar();
    m.def("BeginMenuBar", []() { return ImGui::BeginMenuBar(); });

    // IMGUI_API void          EndMenuBar();
    m.def("EndMenuBar", []() { ImGui::EndMenuBar(); });

    // IMGUI_API bool          BeginMainMenuBar();
    m.def("BeginMainMenuBar", []() { return ImGui::BeginMainMenuBar(); });

    // IMGUI_API void          EndMainMenuBar();
    m.def("EndMainMenuBar", []() { ImGui::EndMainMenuBar(); });

    // IMGUI_API bool          BeginMenu(const char* label, bool enabled = true);
    m.def(
        "BeginMenu",
        [](const char* label, bool enabled) { return ImGui::BeginMenu(label, enabled); },
        nb::arg("label"),
        nb::arg("enabled") = true);

    // IMGUI_API void          EndMenu();
    m.def("EndMenu", []() { ImGui::EndMenu(); });

    // IMGUI_API bool          MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);
    m.def(
        "MenuItem",
        [](const char* label, std::optional<std::string> shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label, to_char_ptr(shortcut), selected, enabled);
        },
        nb::arg("label"),
        nb::arg("shortcut") = nb::none(),
        nb::arg("selected") = false,
        nb::arg("enabled") = true);

    // IMGUI_API bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);
    m.def(
        "MenuItem",
        [](const char* label, const char* shortcut, bool p_selected, bool enabled) {
            bool result = ImGui::MenuItem(label, shortcut, &p_selected, enabled);
            return std::make_tuple(result, p_selected);
        },
        nb::arg("label"),
        nb::arg("shortcut"),
        nb::arg("p_selected"),
        nb::arg("enabled") = true);

}
// clang-format on
