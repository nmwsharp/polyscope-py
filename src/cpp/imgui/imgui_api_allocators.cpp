// Memory Allocators

#include "imgui_utils.h"

// clang-format off

void bind_imgui_api_allocators(nb::module_& m) {
    // IMGUI_API void          SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func, ImGuiMemFreeFunc free_func, void* user_data = NULL);
    // Not bound - takes function pointers and void* user_data, difficult to bind properly for Python use

    // IMGUI_API void          GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data);
    // Not bound - takes function pointers and void* user_data, difficult to bind properly for Python use

    // IMGUI_API void*         MemAlloc(size_t size);
    m.def("MemAlloc", &ImGui::MemAlloc, nb::arg("size"), nb::rv_policy::reference);

    // IMGUI_API void          MemFree(void* ptr);
    m.def("MemFree", &ImGui::MemFree, nb::arg("ptr"));
}
