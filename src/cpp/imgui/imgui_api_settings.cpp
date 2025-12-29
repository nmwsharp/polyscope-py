// Settings/.Ini Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_settings(nb::module_& m) {

    // IMGUI_API void          LoadIniSettingsFromDisk(const char* ini_filename);                  // call after CreateContext() and before the first call to NewFrame(). NewFrame() automatically calls LoadIniSettingsFromDisk(io.IniFilename).
    m.def("LoadIniSettingsFromDisk", &ImGui::LoadIniSettingsFromDisk, nb::arg("ini_filename"));

    // IMGUI_API void          LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size=0); // call after CreateContext() and before the first call to NewFrame() to provide .ini data from your own data source.
    m.def("LoadIniSettingsFromMemory", &ImGui::LoadIniSettingsFromMemory, nb::arg("ini_data"), nb::arg("ini_size") = 0);

    // IMGUI_API void          SaveIniSettingsToDisk(const char* ini_filename);                    // this is automatically called (if io.IniFilename is not empty) a few seconds after any modification that should be reflected in the .ini file (and also by DestroyContext).
    m.def("SaveIniSettingsToDisk", &ImGui::SaveIniSettingsToDisk, nb::arg("ini_filename"));
    
    // IMGUI_API const char*   SaveIniSettingsToMemory(size_t* out_ini_size = NULL);               // return a zero-terminated string with the .ini data which you can save by your own mean. call when io.WantSaveIniSettings is set, then save data by your own mean and clear io.WantSaveIniSettings.
    m.def("SaveIniSettingsToMemory", []() { return ImGui::SaveIniSettingsToMemory(); });
}
