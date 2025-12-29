#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>


// clang-format off
void bind_imgui_structs(nb::module_& m) {

    // NOTE: opaque structs like ImGuiContext are not bound here,
    // see imgui_utils.h for where we mark them Opaque, which is sufficient
    // to make them usable.
    

    nb::class_<ImFontAtlas>(m, "ImFontAtlas")
      .def("AddFontFromFileTTF",
          [](ImFontAtlas& o, std::string filename, float size_pixels) { 
            return o.AddFontFromFileTTF(filename.c_str(), size_pixels);}, 
          nb::rv_policy::reference)

      // TODO add bindings to the rest of the font functions
      
      ;

    nb::class_<ImFont>(m, "ImFont")
      // TODO add bindings to the rest of the font functions
      
      ;


    // Table sorting
    nb::class_<ImGuiTableSortSpecs>(m, "ImGuiTableSortSpecs")
    .def("Specs", [](ImGuiTableSortSpecs& o) {
        std::vector<ImGuiTableColumnSortSpecs> specs;
        for (int i = 0; i < o.SpecsCount; i++) {
            specs.push_back(o.Specs[i]);
        }
        return specs;}
    )
    .def_ro("SpecsCount", &ImGuiTableSortSpecs::SpecsCount)
    .def_rw("SpecsDirty", &ImGuiTableSortSpecs::SpecsDirty)
    ;

    nb::class_<ImGuiTableColumnSortSpecs>(m, "ImGuiTableColumnSortSpecs")
    .def_ro("ColumnUserID", &ImGuiTableColumnSortSpecs::ColumnUserID)
    .def_ro("ColumnIndex", &ImGuiTableColumnSortSpecs::ColumnIndex)
    .def_ro("SortOrder", &ImGuiTableColumnSortSpecs::SortOrder)
    .def_ro("SortDirection", &ImGuiTableColumnSortSpecs::SortDirection)
    ;

    // Drag and drop payload
    nb::class_<ImGuiPayload>(m, "ImGuiPayload")
    .def_ro("DataSize", &ImGuiPayload::DataSize)
    .def("IsDataType", &ImGuiPayload::IsDataType, nb::arg("type"))
    .def("IsPreview", &ImGuiPayload::IsPreview)
    .def("IsDelivery", &ImGuiPayload::IsDelivery)
    // Note: Data field not bound (void* pointer)
    ;

    // Draw data
    nb::class_<ImDrawData>(m, "ImDrawData")
    .def_ro("Valid", &ImDrawData::Valid)
    .def_ro("CmdListsCount", &ImDrawData::CmdListsCount)
    .def_ro("TotalIdxCount", &ImDrawData::TotalIdxCount)
    .def_ro("TotalVtxCount", &ImDrawData::TotalVtxCount)
    .def_prop_ro("DisplayPos", [](const ImDrawData& o) { return from_vec2(o.DisplayPos); })
    .def_prop_ro("DisplaySize", [](const ImDrawData& o) { return from_vec2(o.DisplaySize); })
    .def_prop_ro("FramebufferScale", [](const ImDrawData& o) { return from_vec2(o.FramebufferScale); })
    .def("ScaleClipRects", [](ImDrawData& o, const Vec2T& fb_scale) {
        o.ScaleClipRects(to_vec2(fb_scale));
    }, nb::arg("fb_scale"))
    // Note: CmdLists and OwnerViewport not bound (internal pointers)
    ;

    // Viewport
    nb::class_<ImGuiViewport>(m, "ImGuiViewport")
    .def_ro("ID", &ImGuiViewport::ID)
    .def_ro("Flags", &ImGuiViewport::Flags)
    .def_prop_ro("Pos", [](const ImGuiViewport& o) { return from_vec2(o.Pos); })
    .def_prop_ro("Size", [](const ImGuiViewport& o) { return from_vec2(o.Size); })
    .def_prop_ro("WorkPos", [](const ImGuiViewport& o) { return from_vec2(o.WorkPos); })
    .def_prop_ro("WorkSize", [](const ImGuiViewport& o) { return from_vec2(o.WorkSize); })
    .def("GetCenter", [](const ImGuiViewport& o) { return from_vec2(o.GetCenter()); })
    .def("GetWorkCenter", [](const ImGuiViewport& o) { return from_vec2(o.GetWorkCenter()); })
    // Note: PlatformHandle and PlatformHandleRaw not bound (void* pointers)
    ;

}

// clang-format on