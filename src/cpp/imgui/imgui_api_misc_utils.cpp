// Miscellaneous Utilities

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_misc_utils(nb::module_& m) {
    // IMGUI_API bool          IsRectVisible(const ImVec2& size);                                  // test if rectangle (of given size, starting from cursor position) is visible / not clipped.
    m.def("IsRectVisible", [](const Vec2T& size) {
        return ImGui::IsRectVisible(to_vec2(size));
    }, nb::arg("size"));

    // IMGUI_API bool          IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);      // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
    m.def("IsRectVisible", [](const Vec2T& rect_min, const Vec2T& rect_max) {
        return ImGui::IsRectVisible(to_vec2(rect_min), to_vec2(rect_max));
    }, nb::arg("rect_min"), nb::arg("rect_max"));

    // IMGUI_API double        GetTime();                                                          // get global imgui time. incremented by io.DeltaTime every frame.
    m.def("GetTime", &ImGui::GetTime);

    // IMGUI_API int           GetFrameCount();                                                    // get global imgui frame count. incremented by 1 every frame.
    m.def("GetFrameCount", &ImGui::GetFrameCount);

    // IMGUI_API ImDrawListSharedData* GetDrawListSharedData();                                    // you may use this when creating your own ImDrawList instances.
    // Not bound, this is only useful to create your own ImDrawList instances, which we do not support

    // IMGUI_API const char*   GetStyleColorName(ImGuiCol idx);                                    // get a string corresponding to the enum value (for display, saving, etc.).
    m.def("GetStyleColorName", &ImGui::GetStyleColorName, nb::arg("idx"));

    // IMGUI_API void          SetStateStorage(ImGuiStorage* storage);                             // replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
    m.def("SetStateStorage", &ImGui::SetStateStorage, nb::arg("storage"));

    // IMGUI_API ImGuiStorage* GetStateStorage();
    m.def("GetStateStorage", &ImGui::GetStateStorage, nb::rv_policy::reference);
}
