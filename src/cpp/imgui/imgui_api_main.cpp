#include "imgui_utils.h"

// clang-format off
void bind_imgui_api_main(nb::module_& m) {

    // Main

    // IMGUI_API ImGuiIO&      GetIO();
    m.def("GetIO", &ImGui::GetIO, nb::rv_policy::reference);

    // IMGUI_API ImGuiPlatformIO& GetPlatformIO();
    // This is very low-level.
    // m.def("GetPlatformIO", &ImGui::GetPlatformIO, nb::rv_policy::reference);

    // IMGUI_API ImGuiStyle&   GetStyle();                                 // access the Style structure (colors, sizes). Always use PushStyleColor(), PushStyleVar() to modify style mid-frame!
    m.def("GetStyle", &ImGui::GetStyle, nb::rv_policy::reference);

    // IMGUI_API void          NewFrame();
    m.def("NewFrame", &ImGui::NewFrame);

    // IMGUI_API void          EndFrame(); 
    m.def("EndFrame", &ImGui::EndFrame);

    // IMGUI_API void          Render();
    m.def("Render", &ImGui::Render);

    // IMGUI_API ImDrawData*   GetDrawData();
    m.def("GetDrawData", &ImGui::GetDrawData, nb::rv_policy::reference);

}
// clang-format on