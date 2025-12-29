// Memory Allocators

#include "imgui_utils.h"

// clang-format off

void bind_allocators(nb::module_& m) {
    // Note: SetAllocatorFunctions and GetAllocatorFunctions take function pointers and void* user_data
    // These are difficult to bind properly for Python use, so we skip them
    // Most Python users won't need to override ImGui's allocators

    m.def("MemAlloc", &ImGui::MemAlloc, nb::arg("size"), nb::rv_policy::reference);
    m.def("MemFree", &ImGui::MemFree, nb::arg("ptr"));
}
