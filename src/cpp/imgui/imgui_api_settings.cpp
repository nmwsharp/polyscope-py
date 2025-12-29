// Settings/.Ini Utilities

#include "imgui_utils.h"

// clang-format off

void bind_settings(nb::module_& m) {
    m.def("LoadIniSettingsFromDisk", &ImGui::LoadIniSettingsFromDisk, nb::arg("ini_filename"));
    m.def("LoadIniSettingsFromMemory", &ImGui::LoadIniSettingsFromMemory, nb::arg("ini_data"), nb::arg("ini_size") = 0);
    m.def("SaveIniSettingsToDisk", &ImGui::SaveIniSettingsToDisk, nb::arg("ini_filename"));
    m.def("SaveIniSettingsToMemory", [](std::optional<size_t*> out_ini_size) {
        size_t size;
        const char* result = ImGui::SaveIniSettingsToMemory(out_ini_size.has_value() ? out_ini_size.value() : &size);
        if (out_ini_size.has_value()) {
            return std::make_tuple(std::string(result), *out_ini_size.value());
        } else {
            return std::make_tuple(std::string(result), size);
        }
    }, nb::arg("out_ini_size") = std::nullopt);
}
