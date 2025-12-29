// Memory Allocators

#include "imgui_utils.h"

// clang-format off

void bind_allocators(nb::module_& m) {
    // Note: SetAllocatorFunctions and GetAllocatorFunctions take function pointers and void* user_data
    // These are difficult to bind properly for Python use, so we skip them
    // Most Python users won't need to override ImGui's allocators

    // IMGUI_API void*         MemAlloc(size_t size);
    m.def("MemAlloc", &ImGui::MemAlloc, nb::arg("size"), nb::rv_policy::reference);

    // IMGUI_API void          MemFree(void* ptr);
    m.def("MemFree", &ImGui::MemFree, nb::arg("ptr"));
}
