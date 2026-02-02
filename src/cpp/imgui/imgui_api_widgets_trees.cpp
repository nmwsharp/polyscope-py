#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_trees(nb::module_& m) {

    // Widgets: Trees
    // IMGUI_API bool          TreeNode(const char* label);
    m.def(
        "TreeNode",
        [](const char* label) { return ImGui::TreeNode(label); },
        nb::arg("label"));

    // IMGUI_API bool          TreeNode(const char* str_id, const char* fmt, ...) IM_FMTARGS(2);
    m.def(
        "TreeNode",
        [](const char* str_id, const char* text) { return ImGui::TreeNode(str_id, "%s", text); },
        nb::arg("str_id"),
        nb::arg("text"));

    // IMGUI_API bool          TreeNode(const void* ptr_id, const char* fmt, ...) IM_FMTARGS(2);
    // TODO: Pointer ID version not bound

    // IMGUI_API bool          TreeNodeV(const char* str_id, const char* fmt, va_list args) IM_FMTLIST(2);
    // TODO: Variadic version not bound

    // IMGUI_API bool          TreeNodeV(const void* ptr_id, const char* fmt, va_list args) IM_FMTLIST(2);
    // TODO: Variadic version not bound

    // IMGUI_API bool          TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
    m.def(
        "TreeNodeEx",
        [](const char* label, ImGuiTreeNodeFlags flags) { return ImGui::TreeNodeEx(label, flags); },
        nb::arg("label"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    m.def(
        "TreeNodeEx",
        [](const char* str_id, ImGuiTreeNodeFlags flags, const char* text) {
            return ImGui::TreeNodeEx(str_id, flags, "%s", text);
        },
        nb::arg("str_id"),
        nb::arg("flags"),
        nb::arg("text"));

    // IMGUI_API bool          TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    // TODO: Pointer ID version not bound

    // IMGUI_API bool          TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    // TODO: Variadic version not bound

    // IMGUI_API bool          TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    // TODO: Variadic version not bound

    // IMGUI_API void          TreePush(const char* str_id);
    m.def(
        "TreePush",
        [](const char* str_id) { ImGui::TreePush(str_id); },
        nb::arg("str_id"));

    // IMGUI_API void          TreePush(const void* ptr_id);
    // TODO: Pointer ID version not bound

    // IMGUI_API void          TreePop();
    m.def("TreePop", []() { ImGui::TreePop(); });

    // IMGUI_API float         GetTreeNodeToLabelSpacing();
    m.def("GetTreeNodeToLabelSpacing", []() { return ImGui::GetTreeNodeToLabelSpacing(); });

    // IMGUI_API bool          CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);
    m.def(
        "CollapsingHeader",
        [](const char* label, ImGuiTreeNodeFlags flags) { return ImGui::CollapsingHeader(label, flags); },
        nb::arg("label"),
        nb::arg("flags") = 0);

    // IMGUI_API bool          CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0);
    m.def(
        "CollapsingHeader",
        [](const char* label, bool p_visible, ImGuiTreeNodeFlags flags) {
            bool result = ImGui::CollapsingHeader(label, &p_visible, flags);
            return std::make_tuple(result, p_visible);
        },
        nb::arg("label"),
        nb::arg("p_visible"),
        nb::arg("flags") = 0);

    // IMGUI_API void          SetNextItemOpen(bool is_open, ImGuiCond cond = 0);
    m.def(
        "SetNextItemOpen",
        [](bool is_open, ImGuiCond cond) { ImGui::SetNextItemOpen(is_open, cond); },
        nb::arg("is_open"),
        nb::arg("cond") = 0);

    // IMGUI_API void          SetNextItemStorageID(ImGuiID storage_id);
    m.def(
        "SetNextItemStorageID",
        [](ImGuiID storage_id) { ImGui::SetNextItemStorageID(storage_id); },
        nb::arg("storage_id"));

}
// clang-format on
