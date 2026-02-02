#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_obsolete(nb::module_& m) {
    
    // OBSOLETED in 1.91.9 (from February 2025)
    // IMGUI_API void      Image(ImTextureID user_texture_id, const ImVec2& image_size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col);
    // TODO

    // OBSOLETED in 1.91.0 (from July 2024)

    // static inline void  PushButtonRepeat(bool repeat)
    // TODO
    // static inline void  PopButtonRepeat()
    // TODO
    // static inline void  PushTabStop(bool tab_stop)
    // TODO
    // static inline void  PopTabStop()

    // IMGUI_API ImVec2    GetContentRegionMax();
    m.def("GetContentRegionMax", []() {
        return from_vec2(ImGui::GetContentRegionMax()); });
    
        // IMGUI_API ImVec2    GetWindowContentRegionMin();
    m.def("GetWindowContentRegionMin", []() {
        return from_vec2(ImGui::GetWindowContentRegionMin()); });

    // IMGUI_API ImVec2    GetWindowContentRegionMax();
    m.def("GetWindowContentRegionMax", []() {
        return from_vec2(ImGui::GetWindowContentRegionMax()); });

}
// clang-format on
