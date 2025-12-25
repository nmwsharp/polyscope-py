#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h> 

void bind_imgui_structs(nb::module_& m);
void bind_imgui_methods(nb::module_& m);
void bind_imgui_enums(nb::module_& m);

void bind_imgui(nb::module_& m) {
  auto imgui_module = m.def_submodule("imgui", "ImGui bindings");
  bind_imgui_structs(imgui_module);
  bind_imgui_methods(imgui_module);
  bind_imgui_enums(imgui_module);
}

// clang-format off

struct InputTextCallback_UserData {
  std::string* str;
  ImGuiInputTextCallback chain_callback;
  void* chain_callback_user_data;
};

static int input_text_callback(ImGuiInputTextCallbackData* data) {
  auto* user_data = reinterpret_cast<InputTextCallback_UserData*>(data->UserData);
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    // Resize string callback
    // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we
    // need to set them back to what we want.
    auto* str = user_data->str;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char*)str->c_str();
  } else if (user_data->chain_callback) {
    // Forward to user callback, if any
    data->UserData = user_data->chain_callback_user_data;
    return user_data->chain_callback(data);
  }
  return 0;
}


// clang-format off
void bind_imgui_structs(nb::module_& m) {

    // ImGuiIO
    nb::class_<ImGuiIO>(m, "ImGuiIO")
    .def_rw("DisplaySize"                                ,&ImGuiIO::DisplaySize                                        )
    .def_rw("DeltaTime"                                  ,&ImGuiIO::DeltaTime                                          ) 
    .def_rw("IniSavingRate"                              ,&ImGuiIO::IniSavingRate                                      )     
    .def_rw("IniFilename"                                ,&ImGuiIO::IniFilename                                        )   
    .def_rw("MouseDoubleClickTime"                       ,&ImGuiIO::MouseDoubleClickTime                               )            
    .def_rw("MouseDoubleClickMaxDist"                    ,&ImGuiIO::MouseDoubleClickMaxDist                            )               
    .def_rw("MouseDragThreshold"                         ,&ImGuiIO::MouseDragThreshold                                 )          
    .def_rw("KeyRepeatDelay"                             ,&ImGuiIO::KeyRepeatDelay                                     )      
    .def_rw("KeyRepeatRate"                              ,&ImGuiIO::KeyRepeatRate                                      )     
    .def_rw("Fonts"                                      ,&ImGuiIO::Fonts                                              )
    .def_rw("FontGlobalScale"                            ,&ImGuiIO::FontGlobalScale                                    )       
    .def_rw("FontAllowUserScaling"                       ,&ImGuiIO::FontAllowUserScaling                               )            
    .def_rw("FontDefault"                                ,&ImGuiIO::FontDefault                                        )   
    .def_rw("DisplayFramebufferScale"                    ,&ImGuiIO::DisplayFramebufferScale                            )               
    .def_rw("MouseDrawCursor"                            ,&ImGuiIO::MouseDrawCursor                                    )       
    .def_rw("ConfigMacOSXBehaviors"                      ,&ImGuiIO::ConfigMacOSXBehaviors                              )             
    .def_rw("ConfigInputTextCursorBlink"                 ,&ImGuiIO::ConfigInputTextCursorBlink                         )                  
    .def_rw("ConfigDragClickToInputText"                 ,&ImGuiIO::ConfigDragClickToInputText                         )                  
    .def_rw("ConfigWindowsResizeFromEdges"               ,&ImGuiIO::ConfigWindowsResizeFromEdges                       )                    
    .def_rw("ConfigWindowsMoveFromTitleBarOnly"          ,&ImGuiIO::ConfigWindowsMoveFromTitleBarOnly                  )                         
    .def_rw("ConfigMemoryCompactTimer"                   ,&ImGuiIO::ConfigMemoryCompactTimer                           )                
    .def_prop_ro("MousePos"                              , [](ImGuiIO& o) { return from_vec2(o.MousePos);}             )
    .def_prop_ro("MouseDown"                             , [](ImGuiIO& o) { return std::to_array(o.MouseDown);}        )
    .def_rw("MouseWheel"                                 ,&ImGuiIO::MouseWheel                                         )  
    .def_rw("MouseWheelH"                                ,&ImGuiIO::MouseWheelH                                        )   
    .def_rw("KeyCtrl"                                    ,&ImGuiIO::KeyCtrl                                            )  
    .def_rw("KeyShift"                                   ,&ImGuiIO::KeyShift                                           ) 
    .def_rw("KeyAlt"                                     ,&ImGuiIO::KeyAlt                                             )
    .def_rw("KeySuper"                                   ,&ImGuiIO::KeySuper                                           )
    .def_rw("WantCaptureMouse"                           ,&ImGuiIO::WantCaptureMouse                                   )        
    .def_rw("WantCaptureKeyboard"                        ,&ImGuiIO::WantCaptureKeyboard                                )           
    .def_rw("WantTextInput"                              ,&ImGuiIO::WantTextInput                                      )     
    .def_rw("WantSetMousePos"                            ,&ImGuiIO::WantSetMousePos                                    )       
    .def_rw("WantSaveIniSettings"                        ,&ImGuiIO::WantSaveIniSettings                                )           
    .def_rw("NavActive"                                  ,&ImGuiIO::NavActive                                          ) 
    .def_rw("NavVisible"                                 ,&ImGuiIO::NavVisible                                         )  
    .def_rw("Framerate"                                  ,&ImGuiIO::Framerate                                          ) 
    .def_rw("MetricsRenderVertices"                      ,&ImGuiIO::MetricsRenderVertices                              )             
    .def_rw("MetricsRenderIndices"                       ,&ImGuiIO::MetricsRenderIndices                               )            
    .def_rw("MetricsRenderWindows"                       ,&ImGuiIO::MetricsRenderWindows                               )            
    .def_rw("MetricsActiveWindows"                       ,&ImGuiIO::MetricsActiveWindows                               )            
    .def_prop_ro("MouseDelta"                            , [](ImGuiIO& o) { return from_vec2(o.MouseDelta);})
    .def_rw("WantCaptureMouseUnlessPopupClose"           ,&ImGuiIO::WantCaptureMouseUnlessPopupClose                   )                        
    .def_rw("KeyMods"                                    ,&ImGuiIO::KeyMods                                            ) 
    .def_rw("MousePosPrev"                               ,&ImGuiIO::MousePosPrev                                       )    
    .def_prop_ro("MouseClickedPos"                       , [](ImGuiIO& o) { return std::to_array(o.MouseClickedPos);                   })
    .def_prop_ro("MouseClickedTime"                      , [](ImGuiIO& o) { return std::to_array(o.MouseClickedTime);                  })
    .def_prop_ro("MouseClicked"                          , [](ImGuiIO& o) { return std::to_array(o.MouseClicked);                      })
    .def_prop_ro("MouseDoubleClicked"                    , [](ImGuiIO& o) { return std::to_array(o.MouseDoubleClicked);                })
    .def_prop_ro("MouseClickedCount"                     , [](ImGuiIO& o) { return std::to_array(o.MouseClickedCount);                 })
    .def_prop_ro("MouseClickedLastCount"                 , [](ImGuiIO& o) { return std::to_array(o.MouseClickedLastCount);             })
    .def_prop_ro("MouseReleased"                         , [](ImGuiIO& o) { return std::to_array(o.MouseReleased);                     })
    .def_prop_ro("MouseDownOwned"                        , [](ImGuiIO& o) { return std::to_array(o.MouseDownOwned);                    })
    .def_prop_ro("MouseDownOwnedUnlessPopupClose"        , [](ImGuiIO& o) { return std::to_array(o.MouseDownOwnedUnlessPopupClose);    })
    .def_prop_ro("MouseDownDuration"                     , [](ImGuiIO& o) { return std::to_array(o.MouseDownDuration);                 })
    .def_prop_ro("MouseDownDurationPrev"                 , [](ImGuiIO& o) { return std::to_array(o.MouseDownDurationPrev);             })
    .def_prop_ro("MouseDragMaxDistanceSqr"               , [](ImGuiIO& o) { return std::to_array(o.MouseDragMaxDistanceSqr);           })
    .def_rw("PenPressure"                                ,&ImGuiIO::PenPressure                                        )   
    .def_rw("AppFocusLost"                               ,&ImGuiIO::AppFocusLost                                       )    
    .def_rw("InputQueueSurrogate"                        ,&ImGuiIO::InputQueueSurrogate                                )           
    .def_rw("InputQueueCharacters"                       ,&ImGuiIO::InputQueueCharacters                               )            

    ;


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

    #define VEC2_PROPERTY(name)                            \
        def_prop_rw(#name, [](const ImGuiStyle& style) {  \
            return from_vec2(style.name);                  \
        }, [](ImGuiStyle& style, const Vec2T& value) {     \
            style.name = to_vec2(value);                   \
        })


    // Style
    nb::class_<ImGuiStyle>(m, "ImGuiStyle")
        .def_rw("Alpha", &ImGuiStyle::Alpha)                                        // float
        .def_rw("DisabledAlpha", &ImGuiStyle::DisabledAlpha)                        // float
        .VEC2_PROPERTY(WindowPadding)                                               // ImVec2
        .def_rw("WindowRounding", &ImGuiStyle::WindowRounding)                      // float
        .def_rw("WindowBorderSize", &ImGuiStyle::WindowBorderSize)                  // float
        .def_rw("WindowBorderHoverPadding", &ImGuiStyle::WindowBorderHoverPadding)  // float
        .VEC2_PROPERTY(WindowMinSize)                                               // ImVec2
        .VEC2_PROPERTY(WindowTitleAlign)                                            // ImVec2
        .def_rw("WindowMenuButtonPosition", &ImGuiStyle::WindowMenuButtonPosition)  // ImGuiDir
        .def_rw("ChildRounding", &ImGuiStyle::ChildRounding)                        // float
        .def_rw("ChildBorderSize", &ImGuiStyle::ChildBorderSize)                    // float
        .def_rw("PopupRounding", &ImGuiStyle::PopupRounding)                        // float
        .def_rw("PopupBorderSize", &ImGuiStyle::PopupBorderSize)                    // float
        .VEC2_PROPERTY(FramePadding)                                                // ImVec2
        .def_rw("FrameRounding", &ImGuiStyle::FrameRounding)                        // float
        .def_rw("FrameBorderSize", &ImGuiStyle::FrameBorderSize)                    // float
        .VEC2_PROPERTY(ItemSpacing)                                                 // ImVec2
        .VEC2_PROPERTY(ItemInnerSpacing)                                            // ImVec2
        .VEC2_PROPERTY(CellPadding)                                                 // ImVec2
        .VEC2_PROPERTY(TouchExtraPadding)                                           // ImVec2
        .def_rw("IndentSpacing", &ImGuiStyle::IndentSpacing)                        // float
        .def_rw("ColumnsMinSpacing", &ImGuiStyle::ColumnsMinSpacing)                // float
        .def_rw("ScrollbarSize", &ImGuiStyle::ScrollbarSize)                        // float
        .def_rw("ScrollbarRounding", &ImGuiStyle::ScrollbarRounding)                // float
        .def_rw("GrabMinSize", &ImGuiStyle::GrabMinSize)                            // float
        .def_rw("GrabRounding", &ImGuiStyle::GrabRounding)                          // float
        .def_rw("LogSliderDeadzone", &ImGuiStyle::LogSliderDeadzone)                // float
        .def_rw("ImageBorderSize", &ImGuiStyle::ImageBorderSize)                    // float
        .def_rw("TabRounding", &ImGuiStyle::TabRounding)                            // float
        .def_rw("TabBorderSize", &ImGuiStyle::TabBorderSize)                        // float
        .def_rw("TabCloseButtonMinWidthSelected", &ImGuiStyle::TabCloseButtonMinWidthSelected)      // float
        .def_rw("TabCloseButtonMinWidthUnselected", &ImGuiStyle::TabCloseButtonMinWidthUnselected)  // float
        .def_rw("TabBarBorderSize", &ImGuiStyle::TabBarBorderSize)                  // float
        .def_rw("TabBarOverlineSize", &ImGuiStyle::TabBarOverlineSize)              // float
        .def_rw("TableAngledHeadersAngle", &ImGuiStyle::TableAngledHeadersAngle)    // float
        .VEC2_PROPERTY(TableAngledHeadersTextAlign)                                 // ImVec2
        .def_rw("ColorButtonPosition", &ImGuiStyle::ColorButtonPosition)            // ImGuiDir
        .VEC2_PROPERTY(ButtonTextAlign)                                             // ImVec2
        .VEC2_PROPERTY(SelectableTextAlign)                                         // ImVec2
        .def_rw("SeparatorTextBorderSize", &ImGuiStyle::SeparatorTextBorderSize)    // float
        .VEC2_PROPERTY(SeparatorTextAlign)                                          // ImVec2
        .VEC2_PROPERTY(SeparatorTextPadding)                                        // ImVec2
        .VEC2_PROPERTY(DisplayWindowPadding)                                        // ImVec2
        .VEC2_PROPERTY(DisplaySafeAreaPadding)                                      // ImVec2
        .def_rw("MouseCursorScale", &ImGuiStyle::MouseCursorScale)                  // float
        .def_rw("AntiAliasedLines", &ImGuiStyle::AntiAliasedLines)                  // bool
        .def_rw("AntiAliasedLinesUseTex", &ImGuiStyle::AntiAliasedLinesUseTex)      // bool
        .def_rw("AntiAliasedFill", &ImGuiStyle::AntiAliasedFill)                    // bool
        .def_rw("CurveTessellationTol", &ImGuiStyle::CurveTessellationTol)          // float
        .def_rw("CircleTessellationMaxError", &ImGuiStyle::CircleTessellationMaxError)  // float

        // FIXME
        // .def_rw("Colors", &ImGuiStyle::Colors)

        // Colors (ImVec4[ImGuiCol_COUNT])
        // Note: having explicit getter and setter functions for colors will avoid accidental no-ops such as:
        //     style.Colors[2] = ...
        // FIXME
        /*
        .def("GetColors", [](const ImGuiStyle &o) {
            nb::list colors;
            for (int i = 0; i < ImGuiCol_COUNT; i++) {
                colors.append(from_vec4(o.Colors[i]));
            }
            return colors;
        })
        .def("SetColors", [](ImGuiStyle &o, const nb::list& colors) {
            if (colors.size() != ImGuiCol_COUNT) {
                throw std::runtime_error("Expected " + std::to_string(ImGuiCol_COUNT) 
                                         + " colors, got " + std::to_string(colors.size()));
            }
            for (int i = 0; i < ImGuiCol_COUNT; i++) {
                if (nb::len(colors[i]) != 4) {
                    throw std::runtime_error("Expected 4 elements for color " + std::to_string(i) 
                                             + ", got " + std::to_string(nb::len(colors[i])));
                }
                o.Colors[i] = to_vec4(nb::cast<Vec4T>(colors[i]));
            }
        }, nb::arg("colors"))
        */ 

        // Behaviors
        // (It is possible to modify those fields mid-frame if specific behavior need it, unlike e.g. configuration fields in ImGuiIO)
        .def_rw("HoverStationaryDelay", &ImGuiStyle::HoverStationaryDelay)           // float
        .def_rw("HoverDelayShort", &ImGuiStyle::HoverDelayShort)                     // float
        .def_rw("HoverDelayNormal", &ImGuiStyle::HoverDelayNormal)                   // float
        .def_rw("HoverFlagsForTooltipMouse", &ImGuiStyle::HoverFlagsForTooltipMouse) // ImGuiHoveredFlags
        .def_rw("HoverFlagsForTooltipNav", &ImGuiStyle::HoverFlagsForTooltipNav)     // ImGuiHoveredFlags

        .def("ScaleAllSizes", &ImGuiStyle::ScaleAllSizes);

    #undef VEC2_PROPERTY
}

void bind_imgui_methods(nb::module_& m) {

    // Main
    m.def("GetIO", &ImGui::GetIO, nb::rv_policy::reference);
    m.def("GetStyle", &ImGui::GetStyle, nb::rv_policy::reference);

    // Windows
    m.def(
        "Begin",
        [](const char* name, bool open, ImGuiWindowFlags flags) {
            const auto clicked = ImGui::Begin(name, &open, flags);
            return std::make_tuple(clicked, open);
        },
        nb::arg("name"),
        nb::arg("open"),
        nb::arg("flags") = 0);
    m.def("End", []() { ImGui::End(); });

    // Child Windows
    m.def(
        "BeginChild",
        [](const char* str_id, Vec2T size, bool border, ImGuiWindowFlags flags) {
            return ImGui::BeginChild(str_id, to_vec2(size), border, flags);
        },
        nb::arg("str_id"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("border") = false,
        nb::arg("flags") = 0);
    m.def(
        "BeginChild",
        [](ImGuiID id, const Vec2T& size, bool border, ImGuiWindowFlags flags) {
            return ImGui::BeginChild(id, to_vec2(size), border, flags);
        },
        nb::arg("id"),
        nb::arg("size") = Vec2T(0.f, 0.f),
        nb::arg("border") = false,
        nb::arg("flags") = 0);
    m.def("EndChild", []() { ImGui::EndChild(); });

    // Windows Utilities
    m.def("IsWindowAppearing", []() { return ImGui::IsWindowAppearing(); });
    m.def("IsWindowCollapsed", []() { return ImGui::IsWindowCollapsed(); });
    m.def(
        "IsWindowFocused",
        [](ImGuiFocusedFlags flags) { return ImGui::IsWindowFocused(flags); },
        nb::arg("flags") = 0);
    m.def(
        "IsWindowHovered",
        [](ImGuiFocusedFlags flags) { return ImGui::IsWindowHovered(flags); },
        nb::arg("flags") = 0);
    m.def("GetWindowDrawList", []() { return ImGui::GetWindowDrawList(); }, nb::rv_policy::reference);
    m.def("GetWindowPos", []() { return from_vec2(ImGui::GetWindowPos()); });
    m.def("GetWindowSize", []() { return from_vec2(ImGui::GetWindowSize()); });
    m.def("GetWindowWidth", []() { return ImGui::GetWindowWidth(); });
    m.def("GetWindowHeight", []() { return ImGui::GetWindowHeight(); });
    m.def(
        "SetNextWindowPos",
        [](const Vec2T& pos, ImGuiCond cond, const Vec2T& pivot) {
            ImGui::SetNextWindowPos(to_vec2(pos), cond, to_vec2(pivot));
        },
        nb::arg("pos"),
        nb::arg("cond") = 0,
        nb::arg("pivot") = Vec2T(0., 0.));
    m.def(
        "SetNextWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetNextWindowSize(to_vec2(size), cond); },
        nb::arg("size"),
        nb::arg("cond") = 0);
    m.def(
        "SetNextWindowSizeConstraints",
        [](const Vec2T& size_min, const Vec2T& size_max) {
            ImGui::SetNextWindowSizeConstraints(to_vec2(size_min), to_vec2(size_max));
        },
        nb::arg("size_min"),
        nb::arg("size_max"));
    m.def(
        "SetNextWindowContextSize",
        [](const Vec2T& size) { ImGui::SetNextWindowContentSize(to_vec2(size)); },
        nb::arg("size"));
    m.def(
        "SetNextWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetNextWindowCollapsed(collapsed, cond); },
        nb::arg("collapsed"),
        nb::arg("cond") = 0);
    m.def("SetNextWindowFocus", []() { ImGui::SetNextWindowFocus(); });
    m.def("SetNextWindowBgAlpha", [](float alpha) { ImGui::SetNextWindowBgAlpha(alpha); });
    m.def(
        "SetWindowPos",
        [](const Vec2T& pos, ImGuiCond cond) { ImGui::SetWindowPos(to_vec2(pos), cond); },
        nb::arg("pos"),
        nb::arg("cond") = 0);
    m.def(
        "SetWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetWindowSize(to_vec2(size), cond); },
        nb::arg("size"),
        nb::arg("cond") = 0);
    m.def(
        "SetWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(collapsed, cond); },
        nb::arg("collapsed"),
        nb::arg("cond") = 0);
    m.def("set_window_focus", []() { ImGui::SetWindowFocus(); });
    m.def(
        "SetWindowFontScale",
        [](float scale) { ImGui::SetWindowFontScale(scale); },
        nb::arg("scale"));
    m.def(
        "SetWindowPos",
        [](const char* name, const Vec2T& pos, ImGuiCond cond) {
            ImGui::SetWindowPos(name, to_vec2(pos), cond);
        },
        nb::arg("name"),
        nb::arg("pos"),
        nb::arg("cond") = 0);
    m.def(
        "SetWindowSize",
        [](const char* name, const Vec2T& size, ImGuiCond cond) {
            ImGui::SetWindowSize(name, to_vec2(size), cond);
        },
        nb::arg("name"),
        nb::arg("size"),
        nb::arg("cond") = 0);
    m.def(
        "SetWindowCollapsed",
        [](const char* name, bool collapsed, ImGuiCond cond) {
            ImGui::SetWindowCollapsed(name, collapsed, cond);
        },
        nb::arg("name"),
        nb::arg("collapsed"),
        nb::arg("cond") = 0);
    m.def(
        "SetWindowFocus", [](const char* name) { ImGui::SetWindowFocus(name); }, nb::arg("name"));

    // Content region
    m.def("GetContentRegionMax", []() {
        return from_vec2(ImGui::GetContentRegionMax()); });
    m.def("GetContentRegionAvail", []() {
        return from_vec2(ImGui::GetContentRegionAvail()); });
    m.def("GetWindowContentRegionMin", []() {
        return from_vec2(ImGui::GetWindowContentRegionMin()); });
    m.def("GetWindowContentRegionMax", []() {
        return from_vec2(ImGui::GetWindowContentRegionMax()); });

    // Windows Scrolling
    m.def("GetScrollX", []() { return ImGui::GetScrollX(); });
    m.def("GetScrollY", []() { return ImGui::GetScrollY(); });
    m.def("GetScrollMaxX", []() { return ImGui::GetScrollMaxX(); });
    m.def("GetScrollMaxY", []() { return ImGui::GetScrollMaxY(); });
    m.def(
        "SetScrollX",
        [](float scroll_x) { ImGui::SetScrollX(scroll_x); },
        nb::arg("scroll_x"));
    m.def(
        "SetScrollY",
        [](float scroll_y) { ImGui::SetScrollY(scroll_y); },
        nb::arg("scroll_y"));
    m.def(
        "SetScrollHereX",
        [](float center_x_ratio) { ImGui::SetScrollHereX(center_x_ratio); },
        nb::arg("center_x_ratio") = 0.5f);
    m.def(
        "SetScrollHereY",
        [](float center_y_ratio) { ImGui::SetScrollHereY(center_y_ratio); },
        nb::arg("center_y_ratio") = 0.5f);
    m.def(
        "SetScrollFromPosX",
        [](float local_x, float center_x_ratio) { ImGui::SetScrollFromPosX(local_x, center_x_ratio); },
        nb::arg("local_x"),
        nb::arg("center_x_ratio") = 0.5f);
    m.def(
        "SetScrollFromPosY",
        [](float local_y, float center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); },
        nb::arg("local_y"),
        nb::arg("center_y_ratio") = 0.5f);

    // Parameters stacks (shared)
    IMGUI_API void          PushFont(ImFont* font);                                         // use NULL as a shortcut to push default font
    IMGUI_API void          PopFont();
    m.def(
        "PushFont",
        [](ImFont* font) { ImGui::PushFont(font); },
        nb::arg("font"));
    m.def(
        "PopFont",
        []() { ImGui::PopFont(); }
        );
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); },
        nb::arg("idx"),
        nb::arg("col"));
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, const Vec4T& col) { ImGui::PushStyleColor(idx, to_vec4(col)); },
        nb::arg("idx"),
        nb::arg("col"));
    m.def(
        "PopStyleColor", [](int count) { ImGui::PopStyleColor(count); }, nb::arg("count") = 1);
    m.def(
        "PushStyleVar",
        [](ImGuiCol idx, float val) { ImGui::PushStyleVar(idx, val); },
        nb::arg("idx"),
        nb::arg("val"));
    m.def(
        "PushStyleVar",
        [](ImGuiCol idx, const Vec2T& val) { ImGui::PushStyleVar(idx, to_vec2(val)); },
        nb::arg("idx"),
        nb::arg("val"));
    m.def(
        "PopStyleVar", [](int count) { ImGui::PopStyleVar(count); }, nb::arg("count") = 1);
    m.def(
        "GetStyleColorVec4",
        [](ImGuiCol idx) { return from_vec4(ImGui::GetStyleColorVec4(idx)); },
        nb::arg("idx"));
    m.def("GetFontSize", []() { return ImGui::GetFontSize(); });
    m.def("GetFontTexUvWhitePixel",
            []() { return from_vec2(ImGui::GetFontTexUvWhitePixel()); });
    m.def(
        "GetColorU32",
        [](ImGuiCol idx, float alpha_mul) { return ImGui::GetColorU32(idx, alpha_mul); },
        nb::arg("idx"),
        nb::arg("alpha_mul") = 1.0f);
    m.def(
        "GetColorU32", [](const Vec4T& col) { return ImGui::GetColorU32(to_vec4(col)); }, nb::arg("col"));
    m.def(
        "GetColorU32", [](ImU32 col) { return ImGui::GetColorU32(col); }, nb::arg("col"));

    // Parameters stacks (current window)
    m.def(
        "PushItemWidth",
        [](float item_width) { return ImGui::PushItemWidth(item_width); },
        nb::arg("item_width"));
    m.def("PopItemWidth", []() { ImGui::PopItemWidth(); });
    m.def(
        "SetNextItemWidth",
        [](float item_width) { return ImGui::SetNextItemWidth(item_width); },
        nb::arg("item_width"));
    m.def("CalcItemWidth", []() { return ImGui::CalcItemWidth(); });
    m.def(
        "PushTextWrapPos",
        [](float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); },
        nb::arg("wrap_local_pos_x") = 0.0f);
    m.def("PopTextWrapPos", []() { ImGui::PopTextWrapPos(); });
    m.def(
        "PushAllowKeyboardFocus",
        [](bool allow_keyboard_focus) { ImGui::PushAllowKeyboardFocus(allow_keyboard_focus); },
        nb::arg("allow_keyboard_focus"));
    m.def("PopAllowKeyboardFocus", []() { ImGui::PopAllowKeyboardFocus(); });
    m.def(
        "PushButtonRepeat",
        [](bool repeat) { ImGui::PushButtonRepeat(repeat); },
        nb::arg("allow_keyboard_focus"));
    m.def("PopButtonRepeat", []() { ImGui::PopButtonRepeat(); });

    // Cursor / Layout
    m.def("Separator", []() { ImGui::Separator(); });
    m.def(
        "SameLine",
        [](float offset_from_start_x, float spacing) { ImGui::SameLine(); },
        nb::arg("offset_from_start_x") = 0.0f,
        nb::arg("offset") = -1.0f);
    m.def("NewLine", []() { ImGui::NewLine(); });
    m.def("Spacing", []() { ImGui::Spacing(); });
    m.def("Dummy", [](const Vec2T& size) { ImGui::Dummy(to_vec2(size)); });
    m.def(
        "Indent", [](float indent_w) { ImGui::Indent(indent_w); }, nb::arg("indent_w") = 0.f);
    m.def(
        "Unindent", [](float indent_w) { ImGui::Unindent(indent_w); }, nb::arg("indent_w") = 0.f);
    m.def("BeginGroup", []() { ImGui::BeginGroup(); });
    m.def("EndGroup", []() { ImGui::EndGroup(); });
    m.def("GetCursorPos", []() { return from_vec2(ImGui::GetCursorPos()); });
    m.def("GetCursorPosX", []() { return ImGui::GetCursorPosX(); });
    m.def("GetCursorPosY", []() { return ImGui::GetCursorPosY(); });
    m.def(
        "SetCursorPos",
        [](const Vec2T& local_pos) { ImGui::SetCursorPos(to_vec2(local_pos)); },
        nb::arg("local_pos"));
    m.def(
        "SetCursorPosX",
        [](float local_x) { ImGui::SetCursorPosX(local_x); },
        nb::arg("local_x"));
    m.def(
        "SetCursorPosY",
        [](float local_y) { ImGui::SetCursorPosY(local_y); },
        nb::arg("local_y"));
    m.def("GetCursorStartPos", []() { return from_vec2(ImGui::GetCursorStartPos()); });
    m.def("GetCursorScreenPos", []() { return from_vec2(ImGui::GetCursorScreenPos()); });
    m.def(
        "SetCursorScreenPos",
        [](const Vec2T& pos) { ImGui::SetCursorScreenPos(to_vec2(pos)); },
        nb::arg("pos"));
    m.def("AlignTextToFramePadding", []() { ImGui::AlignTextToFramePadding(); });
    m.def("GetTextLineHeight", []() { return ImGui::GetTextLineHeight(); });
    m.def("GetTextLineHeightWithSpacing", []() { return ImGui::GetTextLineHeightWithSpacing(); });
    m.def("GetFrameHeight", []() { return ImGui::GetFrameHeight(); });
    m.def("GetFrameHeightWithSpacing", []() { return ImGui::GetFrameHeightWithSpacing(); });

    // ID stack/scopes
    m.def(
        "PushID", [](const char* str_id) { ImGui::PushID(str_id); }, nb::arg("str_id"));
    m.def(
        "PushID", [](int int_id) { ImGui::PushID(int_id); }, nb::arg("int_id"));
    m.def("PopID", []() { ImGui::PopID(); });
    m.def(
        "GetID", [](const char* str_id) { return ImGui::GetID(str_id); }, nb::arg("str_id"));
    
    // these are typos (bad capitalization). kept around to avoid needless breaking changes
    m.def(
        "PushId", [](const char* str_id) { ImGui::PushID(str_id); }, nb::arg("str_id"));
    m.def(
        "PushId", [](int int_id) { ImGui::PushID(int_id); }, nb::arg("int_id"));
    m.def(
        "GetId", [](const char* str_id) { return ImGui::GetID(str_id); }, nb::arg("str_id"));

    // Widgets: Text
    m.def(
        "TextUnformatted", [](const char* text) { ImGui::TextUnformatted(text); }, nb::arg("text"));
    m.def(
        "Text", [](const char* text) { ImGui::Text("%s", text); }, nb::arg("text"));
    m.def(
        "TextColored",
        [](const Vec4T& color, const char* text) { ImGui::TextColored(to_vec4(color), "%s", text); },
        nb::arg("color"),
        nb::arg("text"));
    m.def(
        "TextDisabled", [](const char* text) { ImGui::TextDisabled("%s", text); }, nb::arg("text"));
    m.def(
        "TextWrapped", [](const char* text) { ImGui::TextWrapped("%s", text); }, nb::arg("text"));
    m.def(
        "LabelText",
        [](const char* label, const char* text) { ImGui::LabelText(label, "%s", text); },
        nb::arg("label"),
        nb::arg("text"));
    m.def(
        "BulletText",
        [](const char* fmt) { ImGui::BulletText("%s", fmt); },
        nb::arg("text"));
    m.def(
        "SeparatorText",
        [](const char* label) { ImGui::SeparatorText(label); },
        nb::arg("label"));

    // Widgets: Main
    m.def(
        "Button",
        [](const char* label, const Vec2T& size) { return ImGui::Button(label, to_vec2(size)); },
        nb::arg("label"),
        nb::arg("size") = Vec2T(0.f, 0.f));
    m.def(
        "SmallButton",
        [](const char* label) { return ImGui::SmallButton(label); },
        nb::arg("label"));
    m.def(
        "InvisibleButton",
        [](const char* str_id, const Vec2T& size) {
            return ImGui::InvisibleButton(str_id, to_vec2(size));
        },
        nb::arg("str_id"),
        nb::arg("size"));
    m.def(
        "ArrowButton",
        [](const char* str_id, ImGuiDir dir) { return ImGui::ArrowButton(str_id, dir); },
        nb::arg("str_id"),
        nb::arg("dir"));
    m.def(
        "Checkbox",
        [](const char* label, bool v) {
            const auto clicked = ImGui::Checkbox(label, &v);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"));
    m.def(
        "CheckboxFlags",
        [](const char* label, unsigned int flags, unsigned int flags_value) {
            const auto clicked = ImGui::CheckboxFlags(label, &flags, flags_value);
            return std::make_tuple(clicked, flags);
        },
        nb::arg("label"),
        nb::arg("flags"),
        nb::arg("flags_value"));
    m.def(
        "RadioButton",
        [](const char* label, bool active) { return ImGui::RadioButton(label, active); },
        nb::arg("label"),
        nb::arg("active"));
    m.def(
        "RadioButton",
        [](const char* label, int v, int v_button) {
            const auto clicked = ImGui::RadioButton(label, &v, v_button);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_button"));
    m.def(
        "ProgressBar",
        [](float fraction, const Vec2T& size_arg) {
            ImGui::ProgressBar(fraction, to_vec2(size_arg));
        },
        nb::arg("fraction"),
        nb::arg("size_arg") = Vec2T(-1.f, 0.f));
    m.def("Bullet", []() { ImGui::Bullet(); });

    // Widgets: Image
    m.def(
        "Image",
        [](ImTextureID user_texture_id, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1) {
            ImGui::Image(user_texture_id, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1));
        },
        nb::arg("user_texture_id"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.0f, 0.0f),
        nb::arg("uv1") = Vec2T(1.0f, 1.0f));
    m.def(
        "ImageWithBg",
        [](ImTextureID user_texture_id, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1, const Vec4T& bg_col, const Vec4T& tint_col) {
            ImGui::ImageWithBg(user_texture_id, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1), to_vec4(bg_col), to_vec4(tint_col));
        },
        nb::arg("user_texture_id"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.0f, 0.0f),
        nb::arg("uv1") = Vec2T(1.0f, 1.0f),
        nb::arg("bg_col") = Vec4T(0.0f, 0.0f, 0.0f, 0.0f),
        nb::arg("tint_col") = Vec4T(1.0f, 1.0f, 1.0f, 1.0f));

    m.def(
        "ImageButton",
        [](const char* str_id, ImTextureID user_texture_id, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1, const Vec4T& bg_col, const Vec4T& tint_col) {
            return ImGui::ImageButton(str_id, user_texture_id, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1), to_vec4(bg_col), to_vec4(tint_col));
        },
        nb::arg("str_id"),
        nb::arg("user_texture_id"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.0f, 0.0f),
        nb::arg("uv1") = Vec2T(1.0f, 1.0f),
        nb::arg("bg_col") = Vec4T(0.0f, 0.0f, 0.0f, 0.0f),
        nb::arg("tint_col") = Vec4T(1.0f, 1.0f, 1.0f, 1.0f));


    // Widgets: Combo Box
    m.def(
        "BeginCombo",
        [](const char* label, const char* preview_value, ImGuiComboFlags flags) {
            return ImGui::BeginCombo(label, preview_value, flags);
        },
        nb::arg("label"),
        nb::arg("preview_value"),
        nb::arg("flags") = 0);
    m.def("EndCombo", []() { ImGui::EndCombo(); });
    m.def(
        "Combo",
        [](const char* label,
            int current_item,
            const std::vector<std::string>& items,
            int popup_max_height_in_items) {
            const auto _items = convert_string_items(items);
            const auto clicked = ImGui::Combo(
                label, &current_item, _items.data(), _items.size(), popup_max_height_in_items);
            return std::make_tuple(clicked, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items"),
        nb::arg("popup_max_height_in_items") = -1);
    m.def(
        "Combo",
        [](const char* label,
            int current_item,
            const char* items_separated_by_zeros,
            int popup_max_height_in_items) {
            const auto clicked = ImGui::Combo(
                label, &current_item, items_separated_by_zeros, popup_max_height_in_items);
            return std::make_tuple(clicked, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items_separated_by_zeros"),
        nb::arg("popup_max_height_in_items") = -1);

    // Widgets: Drags
    m.def(
        "DragFloat",
        [](const char* label,
            float v,
            float v_speed,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "DragFloat2",
        [](const char* label,
            std::array<float, 2> v,
            float v_speed,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked =
                ImGui::DragFloat2(label, v.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "DragFloat3",
        [](const char* label,
            std::array<float, 3> v,
            float v_speed,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked =
                ImGui::DragFloat3(label, v.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "DragFloat4",
        [](const char* label,
            std::array<float, 4> v,
            float v_speed,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked =
                ImGui::DragFloat4(label, v.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "DragFloatRange2",
        [](const char* label,
            std::array<float, 2> v_current_min,
            std::array<float, 2> v_current_max,
            float v_speed,
            float v_min,
            float v_max,
            const char* format,
            const char* format_max,
            float power) {
            auto clicked = ImGui::DragFloatRange2(label,
                                                    v_current_min.data(),
                                                    v_current_max.data(),
                                                    v_speed,
                                                    v_min,
                                                    v_max,
                                                    format,
                                                    format_max,
                                                    power);
            return std::make_tuple(clicked, v_current_min, v_current_max);
        },
        nb::arg("label"),
        nb::arg("v_current_min"),
        nb::arg("v_current_max"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("format_max") = nullptr,
        nb::arg("power") = 1.0f);

    m.def(
        "DragInt",
        [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format) {
            auto clicked = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "DragInt2",
        [](const char* label,
            std::array<int, 2> v,
            float v_speed,
            int v_min,
            int v_max,
            const char* format) {
            auto clicked = ImGui::DragInt2(label, v.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "DragInt3",
        [](const char* label,
            std::array<int, 3> v,
            float v_speed,
            int v_min,
            int v_max,
            const char* format) {
            auto clicked = ImGui::DragInt3(label, v.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "DragInt4",
        [](const char* label,
            std::array<int, 4> v,
            float v_speed,
            int v_min,
            int v_max,
            const char* format) {
            auto clicked = ImGui::DragInt4(label, v.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "DragIntRange2",
        [](const char* label,
            std::array<int, 2> v_current_min,
            std::array<int, 2> v_current_max,
            float v_speed,
            int v_min,
            int v_max,
            const char* format,
            const char* format_max) {
            auto clicked = ImGui::DragIntRange2(label,
                                                v_current_min.data(),
                                                v_current_max.data(),
                                                v_speed,
                                                v_min,
                                                v_max,
                                                format,
                                                format_max);
            return std::make_tuple(clicked, v_current_min, v_current_max);
        },
        nb::arg("label"),
        nb::arg("v_current_min"),
        nb::arg("v_current_max"),
        nb::arg("v_speed") = 1.0f,
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d",
        nb::arg("format_max") = nullptr);

    // Widgets: Sliders
    m.def(
        "SliderFloat",
        [](const char* label, float v, float v_min, float v_max, const char* format, float power) {
            auto clicked = ImGui::SliderFloat(label, &v, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "SliderFloat2",
        [](const char* label,
            std::array<float, 2> v,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked = ImGui::SliderFloat2(label, v.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "SliderFloat3",
        [](const char* label,
            std::array<float, 3> v,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked = ImGui::SliderFloat3(label, v.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);
    m.def(
        "SliderFloat4",
        [](const char* label,
            std::array<float, 4> v,
            float v_min,
            float v_max,
            const char* format,
            float power) {
            auto clicked = ImGui::SliderFloat4(label, v.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min"),
        nb::arg("v_max"),
        nb::arg("format") = "%.3f",
        nb::arg("power") = 1.0f);

    m.def(
        "SliderAngle",
        [](const char* label,
            float v_rad,
            float v_degrees_min,
            float v_degrees_max,
            const char* format) {
            auto clicked = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format);
            return std::make_tuple(clicked, v_rad);
        },
        nb::arg("label"),
        nb::arg("v_rad"),
        nb::arg("v_degrees_min") = -360.0f,
        nb::arg("v_degrees_max") = +360.0f,
        nb::arg("format") = "%.0f deg");

    m.def(
        "SliderInt",
        [](const char* label, int v, int v_min, int v_max, const char* format) {
            auto v_ = v;
            auto clicked = ImGui::SliderInt(label, &v_, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "SliderInt2",
        [](const char* label,
            const std::array<int, 2>& v,
            int v_min,
            int v_max,
            const char* format) {
            auto v_ = v;
            auto clicked = ImGui::SliderInt2(label, v_.data(), v_min, v_max, format);
            return std::make_tuple(clicked, v_);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "SliderInt3",
        [](const char* label,
            const std::array<int, 3>& v,
            int v_min,
            int v_max,
            const char* format) {
            auto v_ = v;
            auto clicked = ImGui::SliderInt3(label, v_.data(), v_min, v_max, format);
            return std::make_tuple(clicked, v_);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");
    m.def(
        "SliderInt4",
        [](const char* label,
            const std::array<int, 4>& v,
            int v_min,
            int v_max,
            const char* format) {
            auto v_ = v;
            auto clicked = ImGui::SliderInt4(label, v_.data(), v_min, v_max, format);
            return std::make_tuple(clicked, v_);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("v_min") = 0,
        nb::arg("v_max") = 0,
        nb::arg("format") = "%d");

    // Widgets: Input with Keyboard
    m.def(
        "InputText",
        [](const char* label, const std::string& buf, ImGuiInputTextFlags flags) {
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto buf_ = buf;
            InputTextCallback_UserData cb_user_data;
            cb_user_data.str = &buf_;
            cb_user_data.chain_callback = nullptr;
            cb_user_data.chain_callback_user_data = nullptr;
            const auto clicked = ImGui::InputText(label,
                                                    (char*)buf_.c_str(),
                                                    buf_.capacity() + 1,
                                                    flags,
                                                    input_text_callback,
                                                    &cb_user_data);
            return std::make_tuple(clicked, buf_);
        },
        nb::arg("label"),
        nb::arg("buf"),
        nb::arg("flags") = 0);
    m.def(
        "InputTextMultiline",
        [](const char* label,
            const std::string& buf,
            const Vec2T& size,
            ImGuiInputTextFlags flags) {
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto buf_ = buf;
            InputTextCallback_UserData cb_user_data;
            cb_user_data.str = &buf_;
            cb_user_data.chain_callback = nullptr;
            cb_user_data.chain_callback_user_data = nullptr;
            const auto clicked = ImGui::InputTextMultiline(label,
                                                            (char*)buf_.c_str(),
                                                            buf_.capacity() + 1,
                                                            to_vec2(size),
                                                            flags,
                                                            input_text_callback,
                                                            &cb_user_data);
            return std::make_tuple(clicked, buf_);
        },
        nb::arg("label"),
        nb::arg("buf"),
        nb::arg("size") = std::make_tuple(0.f, 0.f),
        nb::arg("flags") = 0);
    m.def(
        "InputTextWithHint",
        [](const char* label, const char* hint, const std::string& buf, ImGuiInputTextFlags flags) {
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto buf_ = buf;
            InputTextCallback_UserData cb_user_data;
            cb_user_data.str = &buf_;
            cb_user_data.chain_callback = nullptr;
            cb_user_data.chain_callback_user_data = nullptr;
            const auto clicked = ImGui::InputTextWithHint(label,
                                                            hint,
                                                            (char*)buf_.c_str(),
                                                            buf_.capacity() + 1,
                                                            flags,
                                                            input_text_callback,
                                                            &cb_user_data);
            return std::make_tuple(clicked, buf_);
        },
        nb::arg("label"),
        nb::arg("hint"),
        nb::arg("buf"),
        nb::arg("flags") = 0);
    m.def(
        "InputFloat",
        [](const char* label,
            float v,
            float step,
            float step_fast,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat(label, &v, step, step_fast, format, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 0.f,
        nb::arg("step_fast") = 0.f,
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);
    m.def(
        "InputFloat2",
        [](const char* label,
            std::array<float, 2> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat2(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);
    m.def(
        "InputFloat3",
        [](const char* label,
            std::array<float, 3> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat3(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);
    m.def(
        "InputFloat4",
        [](const char* label,
            std::array<float, 4> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat4(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("format") = "%.3f",
        nb::arg("flags") = 0);
    m.def(
        "InputInt",
        [](const char* label, int v, float step, float step_fast, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt(label, &v, step, step_fast, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 0.f,
        nb::arg("step_fast") = 0.f,
        nb::arg("flags") = 0);
    m.def(
        "InputInt2",
        [](const char* label, std::array<int, 2> v, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt2(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);
    m.def(
        "InputInt3",
        [](const char* label, std::array<int, 3> v, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt3(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);
    m.def(
        "InputInt4",
        [](const char* label, std::array<int, 4> v, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt4(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("flags") = 0);
    m.def(
        "InputDouble",
        [](const char* label,
            double v,
            double step,
            double step_fast,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputDouble(label, &v, step, step_fast, format, flags);
            return std::make_tuple(clicked, v);
        },
        nb::arg("label"),
        nb::arg("v"),
        nb::arg("step") = 0.f,
        nb::arg("step_fast") = 0.f,
        nb::arg("format") = "%.6f",
        nb::arg("flags") = 0);

    // Widgets: Color Editor/Picker
    m.def(
        "ColorEdit3",
        [](const char* label, const std::array<float, 3>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorEdit3(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        nb::arg("label"),
        nb::arg("def"),
        nb::arg("flags") = 0);
    m.def(
        "ColorEdit4",
        [](const char* label, const std::array<float, 4>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorEdit4(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        nb::arg("label"),
        nb::arg("def"),
        nb::arg("flags") = 0);
    m.def(
        "ColorPicker3",
        [](const char* label, const std::array<float, 3>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorPicker3(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        nb::arg("label"),
        nb::arg("def"),
        nb::arg("flags") = 0);
    m.def(
        "ColorPicker4",
        [](const char* label, const std::array<float, 4>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorPicker4(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        nb::arg("label"),
        nb::arg("def"),
        nb::arg("flags") = 0);
    m.def(
        "ColorButton",
        [](const char* label, const Vec4T& col, ImGuiColorEditFlags flags, const Vec2T& size) {
            auto col_ = col;
            const auto clicked = ImGui::ColorButton(label, to_vec4(col), flags, to_vec2(size));
            return std::make_tuple(clicked, col_);
        },
        nb::arg("label"),
        nb::arg("def"),
        nb::arg("flags") = 0,
        nb::arg("size") = std::make_tuple(0.f, 0.f));
    m.def(
        "SetColorEditOptions",
        [](ImGuiColorEditFlags flags) { ImGui::SetColorEditOptions(flags); },
        nb::arg("flags"));

    // Widgets: Trees
    m.def(
        "TreeNode", [](const char* label) { return ImGui::TreeNode(label); }, nb::arg("label"));
    m.def(
        "TreeNodeEx",
        [](const char* label, ImGuiTreeNodeFlags flags) { return ImGui::TreeNodeEx(label, flags); },
        nb::arg("label"),
        nb::arg("flags") = 0);
    m.def(
        "TreePush", [](const char* str_id) { ImGui::TreePush(str_id); }, nb::arg("str_id"));
    m.def("TreePop", []() { ImGui::TreePop(); });
    m.def("GetTreeNodeToLabelSpacing", []() { return ImGui::GetTreeNodeToLabelSpacing(); });
    m.def(
        "CollapsingHeader",
        [](const char* label, ImGuiTreeNodeFlags flags) {
            return ImGui::CollapsingHeader(label, flags);
        },
        nb::arg("label"),
        nb::arg("flags") = 0);
    m.def(
        "CollapsingHeader",
        [](const char* label, bool open, ImGuiTreeNodeFlags flags) {
            const auto clicked = ImGui::CollapsingHeader(label, &open, flags);
            return std::make_tuple(clicked, open);
        },
        nb::arg("label"),
        nb::arg("open"),
        nb::arg("flags") = 0);
    m.def(
        "SetNextItemOpen",
        [](bool is_open, ImGuiCond cond) { ImGui::SetNextItemOpen(is_open, cond); },
        nb::arg("is_open"),
        nb::arg("cond") = 0);

    // Widgets: Selectables
    m.def(
        "Selectable",
        [](const char* label, bool selected, ImGuiSelectableFlags flags, const Vec2T& size) {
            const auto clicked = ImGui::Selectable(label, &selected, flags, to_vec2(size));
            return std::make_tuple(clicked, selected);
        },
        nb::arg("label"),
        nb::arg("selected") = false,
        nb::arg("flags") = 0,
        nb::arg("size") = std::make_tuple(0.f, 0.f));

    // Widgets: List Boxes
    m.def(
        "BeginListBox",
        [](const char* label,
            const Vec2T& size
          ) {
            return ImGui::BeginListBox(label, to_vec2(size));
        },
        nb::arg("label"),
        nb::arg("size") = Vec2T(0,0));
    m.def(
        "EndListBox",
        []() {
            ImGui::EndListBox();
        });
    m.def(
        "ListBox",
        [](const char* label,
            int current_item,
            const std::vector<std::string>& items,
            int height_in_items) {
            const auto _items = convert_string_items(items);
            const auto clicked =
                ImGui::ListBox(label, &current_item, _items.data(), _items.size(), height_in_items);
            return std::make_tuple(clicked, current_item);
        },
        nb::arg("label"),
        nb::arg("current_item"),
        nb::arg("items"),
        nb::arg("height_in_items") = -1);

    // Widgets: Data Plotting
    m.def(
        "PlotLines",
        [](
            const char *label,
            const std::vector<float>& values,
            int values_offset,
            const char *overlay_text,
            float scale_min,
            float scale_max,
            const Vec2T& graph_size
        ) {
            ImGui::PlotLines(label, values.data(), values.size(), values_offset, overlay_text, scale_min, scale_max, to_vec2(graph_size));
        },
        nb::arg("label"),
        nb::arg("values"),
        nb::arg("values_offset") = 0,
        nb::arg("overlay_text") = nullptr,
        nb::arg("scale_min") = FLT_MAX,
        nb::arg("scale_max") = FLT_MAX,
        nb::arg("graph_size") = std::make_tuple(0.f, 0.f)
    );
    m.def(
        "PlotHistogram",
        [](
            const char *label,
            const std::vector<float>& values,
            int values_offset,
            const char *overlay_text,
            float scale_min,
            float scale_max,
            const Vec2T& graph_size
        ) {
            ImGui::PlotHistogram(label, values.data(), values.size(), values_offset, overlay_text, scale_min, scale_max, to_vec2(graph_size));
        },
        nb::arg("label"),
        nb::arg("values"),
        nb::arg("values_offset") = 0,
        nb::arg("overlay_text") = nullptr,
        nb::arg("scale_min") = FLT_MAX,
        nb::arg("scale_max") = FLT_MAX,
        nb::arg("graph_size") = std::make_tuple(0.f, 0.f)
    );

    // Widgets: Value() Helpers.
    m.def("Value", [](const char *prefix, bool b){ ImGui::Value(prefix, b); }, nb::arg("prefix"), nb::arg("b"));
    m.def("Value", [](const char *prefix, int v){ ImGui::Value(prefix, v); }, nb::arg("prefix"), nb::arg("v"));
    m.def(
        "Value",
        [](const char *prefix, float v, const char * float_format) {
            ImGui::Value(prefix, v, float_format);
        },
        nb::arg("prefix"),
        nb::arg("b"),
        nb::arg("float_format") = nullptr
    );

    // Widgets: Menus
    m.def("BeginMenuBar", []() { return ImGui::BeginMenuBar(); });
    m.def("EndMenuBar", []() { ImGui::EndMenuBar(); });
    m.def("BeginMainMenuBar", []() { return ImGui::BeginMainMenuBar(); });
    m.def("EndMainMenuBar", []() { return ImGui::EndMainMenuBar(); });
    m.def(
        "BeginMenu",
        [](const char* label, bool enabled) { return ImGui::BeginMenu(label, enabled); },
        nb::arg("label"),
        nb::arg("enabled") = true);
    m.def("EndMenu", []() { ImGui::EndMenu(); });
    m.def(
        "MenuItem",
        [](const char* label, const char* shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label, shortcut, selected, enabled);
        },
        nb::arg("label"),
        nb::arg("shortcut") = nullptr,
        nb::arg("selected") = false,
        nb::arg("enabled") = true);

    // Tooltips
    m.def("BeginTooltip", []() { ImGui::BeginTooltip(); });
    m.def("EndTooltip", []() { ImGui::EndTooltip(); });
    m.def("SetTooltip", [](const char *value) { ImGui::SetTooltip("%s", value); });

    // Popups, Modals
    m.def(
        "OpenPopup", [](const char* str_id) { ImGui::OpenPopup(str_id); }, nb::arg("str_id"));
    m.def(
        "BeginPopup",
        [](const char* str_id, ImGuiWindowFlags flags) { return ImGui::BeginPopup(str_id, flags); },
        nb::arg("str_id"),
        nb::arg("flags") = 0);
    m.def(
        "BeginPopupContextItem",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextItem(str_id, popup_flags);
        },
        nb::arg("str_id"),
        nb::arg("popup_flags") = 1);
    m.def(
        "BeginPopupContextWindow",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextWindow(str_id, popup_flags);
        },
        nb::arg("str_id"),
        nb::arg("popup_flags") = 1);
    m.def(
        "BeginPopupContextVoid",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextVoid(str_id, popup_flags);
        },
        nb::arg("str_id"),
        nb::arg("popup_flags") = 1);
    m.def(
        "BeginPopupModal",
        [](const char* str_id, bool open, ImGuiWindowFlags flags) {
            auto open_ = open;
            return ImGui::BeginPopupModal(str_id, &open_, flags);
        },
        nb::arg("str_id"),
        nb::arg("open"),
        nb::arg("flags") = 0);
    m.def("EndPopup", []() { ImGui::EndPopup(); });
    m.def(
        "OpenPopupOnItemClick",
        [](const char* str_id, ImGuiWindowFlags popup_flags) {
            return ImGui::OpenPopupOnItemClick(str_id, popup_flags);
        },
        nb::arg("str_id"),
        nb::arg("popup_flags") = 1);
    m.def(
        "IsPopupOpen",
        [](const char* str_id, ImGuiPopupFlags popup_flags) { return ImGui::IsPopupOpen(str_id, popup_flags); },
        nb::arg("str_id"),
        nb::arg("flags") = 0);
    m.def("CloseCurrentPopup", []() { ImGui::CloseCurrentPopup(); });

    // Tables
    m.def(
        "BeginTable",
        [](const char*str_id, int columns, ImGuiTableFlags flags, Vec2T size, float innerwidth) -> bool {
            return ImGui::BeginTable(str_id, columns, flags, to_vec2(size), innerwidth);
        },
        nb::arg("str"),
        nb::arg("columns"),
        nb::arg("flags") = 0,
        nb::arg("size") = std::make_tuple(0.f, 0.f),
        nb::arg("inner_width") = 0.f
    );
    m.def( "EndTable", []() { ImGui::EndTable(); } );
    m.def(
        "TableNextRow",
        [](ImGuiTableRowFlags flags, float min_row_height) {
            ImGui::TableNextRow(flags, min_row_height);
        },
        nb::arg("flags") = 0,
        nb::arg("min_row_height") = 0.f
    );
    m.def(
        "TableNextColumn",
        []() -> bool {
            return ImGui::TableNextColumn();
        }
    );
    m.def(
        "TableSetColumnIndex",
        [](int column_n) -> bool {
            return ImGui::TableSetColumnIndex(column_n);
        },
        nb::arg("column_n")
    );

    // Table headers and columns
    m.def(
        "TableSetupColumn",
        [](const char* label, ImGuiTableColumnFlags flags, float init_width_or_height, ImGuiID user_id) {
            ImGui::TableSetupColumn(label, flags, init_width_or_height, user_id);
        },
        nb::arg("label"),
        nb::arg("flags") = 0,
        nb::arg("init_width_or_height") = 0.f,
        nb::arg("user_id") = 0u
    );
    m.def(
        "TableSetupScrollFreeze",
        [](int cols, int rows) {
            ImGui::TableSetupScrollFreeze(cols, rows);
        },
        nb::arg("cols"),
        nb::arg("rows")
    );
    m.def(
        "TableHeader",
        [](const char* label) {
            ImGui::TableHeader(label);
        },
        nb::arg("label")
    );
    m.def("TableHeadersRow", []() { ImGui::TableHeadersRow(); });
    m.def("TableAngledHeadersRow", []() { ImGui::TableAngledHeadersRow(); });

    // Table miscellaneous functions
         
    // warning! this function returns a pointer which is only valid for a short time, within the same frame and before next call to BeginTable() (see imgui docs)
    // you will get undefined behavior if you try to use it later
    m.def("TableGetSortSpecs", []() -> ImGuiTableSortSpecs* { return ImGui::TableGetSortSpecs(); }, nb::rv_policy::reference);
    m.def("TableGetColumnCount", []() -> int { return ImGui::TableGetColumnCount(); });
    m.def("TableGetColumnIndex", []() -> int { return ImGui::TableGetColumnIndex(); });
    m.def("TableGetRowIndex", []() -> int { return ImGui::TableGetRowIndex(); });
    m.def(
        "TableGetColumnName",
        [](int column_n) { return nb::str(ImGui::TableGetColumnName(column_n)); },
        nb::arg("column_n") = -1
    );
    /* TableGetColumnFlags not included for the same reasons. */
    m.def(
        "TableSetColumnEnabled",
        [](int column_n, bool enable) { return ImGui::TableSetColumnEnabled(column_n, enable); },
        nb::arg("column_n"),
        nb::arg("v")
    );
    m.def("TableGetHoveredColumn", []() -> int { return ImGui::TableGetHoveredColumn(); });
    m.def(
        "TableSetBgColor",
        [](ImGuiTableBgTarget target, ImU32 color, int column_n) {
          return ImGui::TableSetBgColor(target, color, column_n);
        },
        nb::arg("target"),
        nb::arg("color"),
        nb::arg("column_n") = -1
    );

    // Columns
    m.def(
        "Columns",
        [](int count, const char *id, bool border) {
            ImGui::Columns(count, id, border);
        },
        nb::arg("count") = 1,
        nb::arg("id") = nullptr,
        nb::arg("border") = true
    );
    m.def("NextColumn", []() { ImGui::NextColumn(); });
    m.def("GetColumnIndex", []() { return ImGui::GetColumnIndex(); });
    m.def(
        "GetColumnWidth",
        [](int column_index) {
            return ImGui::GetColumnWidth(column_index);
        },
        nb::arg("column_index") = -1
    );
    m.def(
        "SetColumnWidth",
        [](int column_index, float width) {
            ImGui::SetColumnWidth(column_index, width);
        },
        nb::arg("column_index"),
        nb::arg("width")
    );
    m.def(
        "GetColumnOffset",
        [](int column_index) {
            return ImGui::GetColumnOffset(column_index);
        },
        nb::arg("column_index") = -1
    );
    m.def(
        "SetColumnOffset",
        [](int column_index, float width) {
            ImGui::SetColumnOffset(column_index, width);
        },
        nb::arg("column_index"),
        nb::arg("offset_x")
    );
    m.def("GetColumnsCount", []() { return ImGui::GetColumnsCount(); });

    // Tab Bars, Tabs
    m.def(
        "BeginTabBar",
        [](const char *str_id, ImGuiTabBarFlags flags) {
            return ImGui::BeginTabBar(str_id, flags);
        },
        nb::arg("str_id"),
        nb::arg("flags") = 0
    );
    m.def("EndTabBar", []() { ImGui::EndTabBar(); });
    m.def(
        "BeginTabItem",
        [](const char *str, bool open, ImGuiTabBarFlags flags) {
            const auto clicked = ImGui::BeginTabItem(str, &open, flags);
            return std::make_tuple(clicked, open);
        },
        nb::arg("str"),
        nb::arg("open"),
        nb::arg("flags") = 0
    );
    m.def("EndTabItem", []() { ImGui::EndTabItem(); });
    m.def(
        "SetTabItemClosed",
        [](const char *tab_or_docked_window_label) {
            ImGui::SetTabItemClosed(tab_or_docked_window_label);
        },
        nb::arg("tab_or_docked_window_label")
    );

    // Logging/Capture
    m.def(
        "LogToTTY",
        [](int auto_open_depth) {
            ImGui::LogToTTY(auto_open_depth);
        },
        nb::arg("auto_open_depth") = -1
    );
    m.def(
        "LogToFile",
        [](int auto_open_depth, const char *filename) {
            ImGui::LogToFile(auto_open_depth, filename);
        },
        nb::arg("auto_open_depth") = -1,
        nb::arg("filename") = nullptr
    );
    m.def(
        "LogToClipboard",
        [](int auto_open_depth) {
            ImGui::LogToClipboard(auto_open_depth);
        },
        nb::arg("auto_open_depth") = -1
    );
    m.def("LogFinish", []() { ImGui::LogFinish(); });
    m.def("LogButtons", []() { ImGui::LogButtons(); });

    // Disabling
    m.def("BeginDisabled", 
        [](bool disable) { 
          return ImGui::BeginDisabled(disable);
        }, nb::arg("disable"));
    m.def("EndDisabled", []() { ImGui::EndDisabled(); });

    // Clipping
    m.def(
        "PushClipRect",
        [](
            const Vec2T& clip_rect_min,
            const Vec2T& clip_rect_max,
            bool intersect_with_current_clip_rect
        ) {
            ImGui::PushClipRect(to_vec2(clip_rect_min), to_vec2(clip_rect_max), intersect_with_current_clip_rect);
        },
        nb::arg("clip_rect_min"),
        nb::arg("clip_rect_max"),
        nb::arg("intersect_with_current_clip_rect")
    );
    m.def("PopClipRect", []() { ImGui::PopClipRect(); });

    // Focus, Activation
    m.def("SetItemDefaultFocus", []() { ImGui::SetItemDefaultFocus(); });
    m.def(
        "SetKeyboardFocusHere",
        [](int offset) { ImGui::SetKeyboardFocusHere(offset); },
        nb::arg("offset")
    );

    // Item/Widgets Utilities
    m.def(
        "IsItemHovered",
        [](ImGuiHoveredFlags flags) { return ImGui::IsItemHovered(flags); },
        nb::arg("flags") = 0);
    m.def("IsItemActive", []() { return ImGui::IsItemActive(); });
    m.def("IsItemFocused", []() { return ImGui::IsItemFocused(); });
    m.def(
        "IsItemClicked",
        [](ImGuiMouseButton mouse_button) { return ImGui::IsItemClicked(mouse_button); },
        nb::arg("mouse_button") = 0);
    m.def("IsItemVisible", []() { return ImGui::IsItemVisible(); });
    m.def("IsItemEdited", []() { return ImGui::IsItemEdited(); });
    m.def("IsItemActivated", []() { return ImGui::IsItemActivated(); });
    m.def("IsItemDeactivated", []() { return ImGui::IsItemDeactivated(); });
    m.def("IsItemDeactivatedAfterEdit", []() { return ImGui::IsItemDeactivatedAfterEdit(); });
    m.def("IsItemToggledOpen", []() { return ImGui::IsItemToggledOpen(); });
    m.def("IsAnyItemHovered", []() { return ImGui::IsAnyItemHovered(); });
    m.def("IsAnyItemActive", []() { return ImGui::IsAnyItemActive(); });
    m.def("IsAnyItemFocused", []() { return ImGui::IsAnyItemFocused(); });
    m.def("GetItemRectMin", []() { return from_vec2(ImGui::GetItemRectMin()); });
    m.def("GetItemRectMax", []() { return from_vec2(ImGui::GetItemRectMax()); });
    m.def("GetItemRectSize", []() { return from_vec2(ImGui::GetItemRectSize()); });
    m.def("SetItemAllowOverlap", []() { ImGui::SetItemAllowOverlap(); });

    // Background/Foreground Draw Lists
    m.def("GetBackgroundDrawList", &ImGui::GetBackgroundDrawList, nb::rv_policy::reference);
    m.def("GetForegroundDrawList", &ImGui::GetForegroundDrawList, nb::rv_policy::reference);

    // Miscellaneous Utilities
    m.def(
        "IsRectVisible",
        [](const Vec2T& size) {
            return ImGui::IsRectVisible(to_vec2(size));
        },
        nb::arg("size")
    );
    m.def(
        "IsRectVisible",
        [](const Vec2T& rect_min, const Vec2T& rect_max) {
            return ImGui::IsRectVisible(to_vec2(rect_min), to_vec2(rect_max));
        },
        nb::arg("rect_min"),
        nb::arg("rect_max")
    );
    m.def("GetTime", []() { return ImGui::GetTime(); });
    m.def("GetFrameCount", []() { return ImGui::GetFrameCount(); });
    m.def("GetStyleColorName", [](ImGuiCol idx) { return ImGui::GetStyleColorName(idx); });
    m.def(
        "BeginChildFrame",
        [](ImGuiID id, const Vec2T& size, ImGuiWindowFlags flags) {
            return ImGui::BeginChildFrame(id, to_vec2(size), flags);
        },
        nb::arg("id"),
        nb::arg("size"),
        nb::arg("flags") = 0
    );
    m.def("EndChildFrame", []() { ImGui::EndChildFrame(); });

    // Text Utilities
    m.def(
        "CalcTextSize",
        [](const char *text, const char *text_end, bool hide_text_after_double_hash, float wrap_width) {
            return from_vec2(ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width));
        },
        nb::arg("text"),
        nb::arg("text_end") = nullptr,
        nb::arg("hide_text_after_double_hash") = false,
        nb::arg("wrap_width") = -1.f
    );

    // Utilities: Mouse
    m.def("IsMouseDown", [](ImGuiMouseButton button) { return ImGui::IsMouseDown(button); }, nb::arg("button"));
    m.def(
        "IsMouseClicked",
        [](ImGuiMouseButton button, bool repeat) { return ImGui::IsMouseClicked(button, repeat); },
        nb::arg("button"),
        nb::arg("repeat") = false
    );
    m.def("IsMouseReleased", [](ImGuiMouseButton button) { return ImGui::IsMouseReleased(button); }, nb::arg("button"));
    m.def("IsMouseDoubleClicked", [](ImGuiMouseButton button) { return ImGui::IsMouseDoubleClicked(button); }, nb::arg("button"));
    m.def(
        "IsMouseHoveringRect",
        [](const Vec2T& r_min, const Vec2T& r_max, bool clip) {
            return ImGui::IsMouseHoveringRect(to_vec2(r_min), to_vec2(r_max), clip);
        },
        nb::arg("r_min"),
        nb::arg("r_max"),
        nb::arg("clip") = true
    );
    m.def("IsAnyMouseDown", []() { return ImGui::IsAnyMouseDown(); });
    m.def("GetMousePos", []() { return from_vec2(ImGui::GetMousePos()); });
    m.def("GetMousePosOnOpeningCurrentPopup", []() { return from_vec2(ImGui::GetMousePosOnOpeningCurrentPopup()); });
    m.def(
        "IsMouseDragging",
        [](ImGuiMouseButton button, float lock_threshold) { return ImGui::IsMouseDragging(button, lock_threshold); },
        nb::arg("button"),
        nb::arg("lock_threshold") = -1.f
    );
    m.def("ResetMouseDragDelta", [](ImGuiMouseButton button) { ImGui::ResetMouseDragDelta(button); }, nb::arg("button"));
    m.def("GetMouseCursor", []() { return ImGui::GetMouseCursor(); });
    m.def("SetMouseCursor", [](ImGuiMouseCursor cursor_type) { ImGui::SetMouseCursor(cursor_type); }, nb::arg("cursor_type"));
    m.def("SetNextFrameWantCaptureMouse", [](bool want_capture_mouse) { ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse); }, nb::arg("want_capture_mouse"));

    // Inputs Utilities: Keyboard
    m.def("IsKeyDown", [](ImGuiKey user_key_index) { return ImGui::IsKeyDown(user_key_index); }, nb::arg("user_key_index"));
    m.def("IsKeyPressed", [](ImGuiKey user_key_index, bool repeat) { return ImGui::IsKeyPressed(user_key_index, repeat); }, nb::arg("user_key_index"), nb::arg("repeat")=true);
    m.def("IsKeyReleased", [](ImGuiKey user_key_index) { return ImGui::IsKeyReleased(user_key_index); }, nb::arg("user_key_index"));
    m.def(
        "GetKeyPressedAmount",
        [](ImGuiKey key_index, float repeat_delay, float rate) {
            return ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate);
        },
        nb::arg("key_index"),
        nb::arg("repeat_delay"),
        nb::arg("rate")
    );
    m.def(
        "SetNextFrameWantCaptureKeyboard",
        [](bool want_capture_keyboard) {
            ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard);
        },
        nb::arg("want_capture_keyboard") = true
    );

    // Clipboard Utilities
    m.def("GetClipboardText", []() { return ImGui::GetClipboardText(); });
    m.def("SetClipboardText", [](const char *text) { ImGui::SetClipboardText(text); }, nb::arg("text"));

    // Settings/.Ini Utilities
    m.def("LoadIniSettingsFromDisk", [](const char *ini_filename) { ImGui::LoadIniSettingsFromDisk(ini_filename); }, nb::arg("ini_filename"));
    m.def("LoadIniSettingsFromMemory", [](const char *ini_data) { ImGui::LoadIniSettingsFromMemory(ini_data); }, nb::arg("ini_data"));
    m.def("SaveIniSettingsToDisk", [](const char *ini_filename) { ImGui::SaveIniSettingsToDisk(ini_filename); }, nb::arg("ini_filename"));
    m.def("SaveIniSettingsToMemory", []() { return ImGui::SaveIniSettingsToMemory(); });

    // Draw Commands 
    nb::class_<ImDrawList>(m, "ImDrawList")

        // Clip Rect

        .def(
            "PushClipRect",
            [](ImDrawList& self, const Vec2T& clip_rect_min, const Vec2T& clip_rect_max, bool intersect_with_current_clip_rect) {
                self.PushClipRect(to_vec2(clip_rect_min), to_vec2(clip_rect_max), intersect_with_current_clip_rect);
            },
            nb::arg("clip_rect_min"),
            nb::arg("clip_rect_max"),
            nb::arg("intersect_with_current_clip_rect") = false
        )
        .def("PushClipRectFullScreen", &ImDrawList::PushClipRectFullScreen)
        .def("PopClipRect", &ImDrawList::PopClipRect)
        .def("GetClipRectMin", [](ImDrawList& self) { return from_vec2(self.GetClipRectMin()); })
        .def("GetClipRectMax", [](ImDrawList& self) { return from_vec2(self.GetClipRectMax()); })

        // Primitives

        .def(
            "AddLine", 
            [](ImDrawList& draw_list, const Vec2T& p1, const Vec2T& p2, ImU32 col, float thickness) {
                draw_list.AddLine(to_vec2(p1), to_vec2(p2), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddRect", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags, float thickness) {
                self.AddRect(to_vec2(p_min), to_vec2(p_max), col, rounding, flags, thickness);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col"),
            nb::arg("rounding") = 0.0f,
            nb::arg("flags") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddRectFilled", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags) {
                self.AddRectFilled(to_vec2(p_min), to_vec2(p_max), col, rounding, flags);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col"),
            nb::arg("rounding") = 0.0f,
            nb::arg("flags") = 0
        )
        .def(
            "AddRectFilledMultiColor", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left) {
                self.AddRectFilledMultiColor(to_vec2(p_min), to_vec2(p_max), col_upr_left, col_upr_right, col_bot_right, col_bot_left);
            },
            nb::arg("p_min"),
            nb::arg("p_max"),
            nb::arg("col_upr_left"),
            nb::arg("col_upr_right"),
            nb::arg("col_bot_right"),
            nb::arg("col_bot_left")
        )
        .def(
            "AddQuad", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness) {
                self.AddQuad(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddQuadFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col) {
                self.AddQuadFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col")
        )
        .def(
            "AddTriangle", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness) {
                self.AddTriangle(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col"),
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddTriangleFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col) {
                self.AddTriangleFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), col);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col")
        )
        .def(
            "AddCircle", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddCircle(to_vec2(center), radius, col, num_segments, thickness);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddCircleFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddCircleFilled(to_vec2(center), radius, col, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddNgon", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddNgon(to_vec2(center), radius, col, num_segments, thickness);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0,
            nb::arg("thickness") = 1.0f
        )
        .def(
            "AddNgonFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddNgonFilled(to_vec2(center), radius, col, num_segments);
            },
            nb::arg("center"),
            nb::arg("radius"),
            nb::arg("col"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddText", 
            [](ImDrawList& self, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end) {
                self.AddText(to_vec2(pos), col, text_begin, text_end);
            },
            nb::arg("pos"),
            nb::arg("col"),
            nb::arg("text_begin"),
            nb::arg("text_end") = nullptr
        )
        .def(
            "AddText", 
            [](ImDrawList& self, ImFont* font, float font_size, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width) {
                self.AddText(font, font_size, to_vec2(pos), col, text_begin, text_end, wrap_width);
            },
            nb::arg("font"),
            nb::arg("font_size"),
            nb::arg("pos"),
            nb::arg("col"),
            nb::arg("text_begin"),
            nb::arg("text_end") = nullptr,
            nb::arg("wrap_width") = 0.0f
        )
        .def(
            "AddPolyline", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col, ImDrawFlags flags, float thickness) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddPolyline(points_vec2.data(), num_points, col, flags, thickness);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col"),
            nb::arg("flags"),
            nb::arg("thickness")
        )
        .def(
            "AddConvexPolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConvexPolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        .def(
            "AddBezierCubic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierCubic(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness, num_segments);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("p4"),
            nb::arg("col"),
            nb::arg("thickness"),
            nb::arg("num_segments") = 0
        )
        .def(
            "AddBezierQuadratic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierQuadratic(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness, num_segments);
            },
            nb::arg("p1"),
            nb::arg("p2"),
            nb::arg("p3"),
            nb::arg("col"),
            nb::arg("thickness"),
            nb::arg("num_segments") = 0
        )

        // General Polygon

        .def(
            "AddPolyline", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col, ImDrawFlags flags, float thickness) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddPolyline(points_vec2.data(), num_points, col, flags, thickness);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col"),
            nb::arg("flags"),
            nb::arg("thickness")
        )
        .def(
            "AddConvexPolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConvexPolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        .def(
            "AddConcavePolyFilled", 
            [](ImDrawList& self, const std::vector<Vec2T>& points, int num_points, ImU32 col) {
                std::vector<ImVec2> points_vec2(points.size());
                for (int i = 0; i < points.size(); i++) {
                    points_vec2[i] = to_vec2(points[i]);
                } 
                self.AddConcavePolyFilled(points_vec2.data(), num_points, col);
            },
            nb::arg("points"),
            nb::arg("num_points"),
            nb::arg("col")
        )
        
    ;
        

    // Macros etc
    m.def("IM_COL32", [](uint8_t R, uint8_t G, uint8_t B, uint8_t A) { return IM_COL32(R,G,B,A); });
}
// clang-format on

void bind_imgui_enums(nb::module_& m) {

  nb::enum_<ImGuiDir>(m, "ImGuiDir");
  nb::enum_<ImGuiMouseSource>(m, "ImGuiMouseSource");
  nb::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection");

  m.attr("ImGuiWindowFlags_None") = static_cast<int>(ImGuiWindowFlags_None);
  m.attr("ImGuiWindowFlags_NoTitleBar") = static_cast<int>(ImGuiWindowFlags_NoTitleBar);
  m.attr("ImGuiWindowFlags_NoResize") = static_cast<int>(ImGuiWindowFlags_NoResize);
  m.attr("ImGuiWindowFlags_NoMove") = static_cast<int>(ImGuiWindowFlags_NoMove);
  m.attr("ImGuiWindowFlags_NoScrollbar") = static_cast<int>(ImGuiWindowFlags_NoScrollbar);
  m.attr("ImGuiWindowFlags_NoScrollWithMouse") = static_cast<int>(ImGuiWindowFlags_NoScrollWithMouse);
  m.attr("ImGuiWindowFlags_NoCollapse") = static_cast<int>(ImGuiWindowFlags_NoCollapse);
  m.attr("ImGuiWindowFlags_AlwaysAutoResize") = static_cast<int>(ImGuiWindowFlags_AlwaysAutoResize);
  m.attr("ImGuiWindowFlags_NoBackground") = static_cast<int>(ImGuiWindowFlags_NoBackground);
  m.attr("ImGuiWindowFlags_NoSavedSettings") = static_cast<int>(ImGuiWindowFlags_NoSavedSettings);
  m.attr("ImGuiWindowFlags_NoMouseInputs") = static_cast<int>(ImGuiWindowFlags_NoMouseInputs);
  m.attr("ImGuiWindowFlags_MenuBar") = static_cast<int>(ImGuiWindowFlags_MenuBar);
  m.attr("ImGuiWindowFlags_HorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_HorizontalScrollbar);
  m.attr("ImGuiWindowFlags_NoFocusOnAppearing") = static_cast<int>(ImGuiWindowFlags_NoFocusOnAppearing);
  m.attr("ImGuiWindowFlags_NoBringToFrontOnFocus") = static_cast<int>(ImGuiWindowFlags_NoBringToFrontOnFocus);
  m.attr("ImGuiWindowFlags_AlwaysVerticalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysVerticalScrollbar);
  m.attr("ImGuiWindowFlags_AlwaysHorizontalScrollbar") = static_cast<int>(ImGuiWindowFlags_AlwaysHorizontalScrollbar);
  m.attr("ImGuiWindowFlags_AlwaysUseWindowPadding") = static_cast<int>(ImGuiWindowFlags_AlwaysUseWindowPadding);
  m.attr("ImGuiWindowFlags_NoNavInputs") = static_cast<int>(ImGuiWindowFlags_NoNavInputs);
  m.attr("ImGuiWindowFlags_NoNavFocus") = static_cast<int>(ImGuiWindowFlags_NoNavFocus);
  m.attr("ImGuiWindowFlags_UnsavedDocument") = static_cast<int>(ImGuiWindowFlags_UnsavedDocument);
  m.attr("ImGuiWindowFlags_NoNav") = static_cast<int>(ImGuiWindowFlags_NoNav);
  m.attr("ImGuiWindowFlags_NoDecoration") = static_cast<int>(ImGuiWindowFlags_NoDecoration);
  m.attr("ImGuiWindowFlags_NoInputs") = static_cast<int>(ImGuiWindowFlags_NoInputs);
  m.attr("ImGuiWindowFlags_NavFlattened") = static_cast<int>(ImGuiWindowFlags_NavFlattened);
  m.attr("ImGuiWindowFlags_ChildWindow") = static_cast<int>(ImGuiWindowFlags_ChildWindow);
  m.attr("ImGuiWindowFlags_Tooltip") = static_cast<int>(ImGuiWindowFlags_Tooltip);
  m.attr("ImGuiWindowFlags_Popup") = static_cast<int>(ImGuiWindowFlags_Popup);
  m.attr("ImGuiWindowFlags_Modal") = static_cast<int>(ImGuiWindowFlags_Modal);
  m.attr("ImGuiWindowFlags_ChildMenu") = static_cast<int>(ImGuiWindowFlags_ChildMenu);

  m.attr("ImGuiInputTextFlags_None") = static_cast<int>(ImGuiInputTextFlags_None);
  m.attr("ImGuiInputTextFlags_CharsDecimal") = static_cast<int>(ImGuiInputTextFlags_CharsDecimal);
  m.attr("ImGuiInputTextFlags_CharsHexadecimal") = static_cast<int>(ImGuiInputTextFlags_CharsHexadecimal);
  m.attr("ImGuiInputTextFlags_CharsUppercase") = static_cast<int>(ImGuiInputTextFlags_CharsUppercase);
  m.attr("ImGuiInputTextFlags_CharsNoBlank") = static_cast<int>(ImGuiInputTextFlags_CharsNoBlank);
  m.attr("ImGuiInputTextFlags_AutoSelectAll") = static_cast<int>(ImGuiInputTextFlags_AutoSelectAll);
  m.attr("ImGuiInputTextFlags_EnterReturnsTrue") = static_cast<int>(ImGuiInputTextFlags_EnterReturnsTrue);
  m.attr("ImGuiInputTextFlags_CallbackCompletion") = static_cast<int>(ImGuiInputTextFlags_CallbackCompletion);
  m.attr("ImGuiInputTextFlags_CallbackHistory") = static_cast<int>(ImGuiInputTextFlags_CallbackHistory);
  m.attr("ImGuiInputTextFlags_CallbackAlways") = static_cast<int>(ImGuiInputTextFlags_CallbackAlways);
  m.attr("ImGuiInputTextFlags_CallbackCharFilter") = static_cast<int>(ImGuiInputTextFlags_CallbackCharFilter);
  m.attr("ImGuiInputTextFlags_AllowTabInput") = static_cast<int>(ImGuiInputTextFlags_AllowTabInput);
  m.attr("ImGuiInputTextFlags_CtrlEnterForNewLine") = static_cast<int>(ImGuiInputTextFlags_CtrlEnterForNewLine);
  m.attr("ImGuiInputTextFlags_NoHorizontalScroll") = static_cast<int>(ImGuiInputTextFlags_NoHorizontalScroll);
  m.attr("ImGuiInputTextFlags_AlwaysOverwrite") = static_cast<int>(ImGuiInputTextFlags_AlwaysOverwrite);
  m.attr("ImGuiInputTextFlags_ReadOnly") = static_cast<int>(ImGuiInputTextFlags_ReadOnly);
  m.attr("ImGuiInputTextFlags_Password") = static_cast<int>(ImGuiInputTextFlags_Password);
  m.attr("ImGuiInputTextFlags_NoUndoRedo") = static_cast<int>(ImGuiInputTextFlags_NoUndoRedo);
  m.attr("ImGuiInputTextFlags_CharsScientific") = static_cast<int>(ImGuiInputTextFlags_CharsScientific);
  m.attr("ImGuiInputTextFlags_CallbackResize") = static_cast<int>(ImGuiInputTextFlags_CallbackResize);

  m.attr("ImGuiTreeNodeFlags_None") = static_cast<int>(ImGuiTreeNodeFlags_None);
  m.attr("ImGuiTreeNodeFlags_Selected") = static_cast<int>(ImGuiTreeNodeFlags_Selected);
  m.attr("ImGuiTreeNodeFlags_Framed") = static_cast<int>(ImGuiTreeNodeFlags_Framed);
  m.attr("ImGuiTreeNodeFlags_AllowItemOverlap") = static_cast<int>(ImGuiTreeNodeFlags_AllowItemOverlap);
  m.attr("ImGuiTreeNodeFlags_NoTreePushOnOpen") = static_cast<int>(ImGuiTreeNodeFlags_NoTreePushOnOpen);
  m.attr("ImGuiTreeNodeFlags_NoAutoOpenOnLog") = static_cast<int>(ImGuiTreeNodeFlags_NoAutoOpenOnLog);
  m.attr("ImGuiTreeNodeFlags_DefaultOpen") = static_cast<int>(ImGuiTreeNodeFlags_DefaultOpen);
  m.attr("ImGuiTreeNodeFlags_OpenOnDoubleClick") = static_cast<int>(ImGuiTreeNodeFlags_OpenOnDoubleClick);
  m.attr("ImGuiTreeNodeFlags_OpenOnArrow") = static_cast<int>(ImGuiTreeNodeFlags_OpenOnArrow);
  m.attr("ImGuiTreeNodeFlags_Leaf") = static_cast<int>(ImGuiTreeNodeFlags_Leaf);
  m.attr("ImGuiTreeNodeFlags_Bullet") = static_cast<int>(ImGuiTreeNodeFlags_Bullet);
  m.attr("ImGuiTreeNodeFlags_FramePadding") = static_cast<int>(ImGuiTreeNodeFlags_FramePadding);
  m.attr("ImGuiTreeNodeFlags_SpanAvailWidth") = static_cast<int>(ImGuiTreeNodeFlags_SpanAvailWidth);
  m.attr("ImGuiTreeNodeFlags_SpanFullWidth") = static_cast<int>(ImGuiTreeNodeFlags_SpanFullWidth);
  m.attr("ImGuiTreeNodeFlags_NavLeftJumpsBackHere") = static_cast<int>(ImGuiTreeNodeFlags_NavLeftJumpsBackHere);
  m.attr("ImGuiTreeNodeFlags_CollapsingHeader") = static_cast<int>(ImGuiTreeNodeFlags_CollapsingHeader);

  m.attr("ImGuiSelectableFlags_None") = static_cast<int>(ImGuiSelectableFlags_None);
  m.attr("ImGuiSelectableFlags_DontClosePopups") = static_cast<int>(ImGuiSelectableFlags_DontClosePopups);
  m.attr("ImGuiSelectableFlags_SpanAllColumns") = static_cast<int>(ImGuiSelectableFlags_SpanAllColumns);
  m.attr("ImGuiSelectableFlags_AllowDoubleClick") = static_cast<int>(ImGuiSelectableFlags_AllowDoubleClick);
  m.attr("ImGuiSelectableFlags_Disabled") = static_cast<int>(ImGuiSelectableFlags_Disabled);
  m.attr("ImGuiSelectableFlags_AllowItemOverlap") = static_cast<int>(ImGuiSelectableFlags_AllowItemOverlap);

  m.attr("ImGuiComboFlags_None") = static_cast<int>(ImGuiComboFlags_None);
  m.attr("ImGuiComboFlags_PopupAlignLeft") = static_cast<int>(ImGuiComboFlags_PopupAlignLeft);
  m.attr("ImGuiComboFlags_HeightSmall") = static_cast<int>(ImGuiComboFlags_HeightSmall);
  m.attr("ImGuiComboFlags_HeightRegular") = static_cast<int>(ImGuiComboFlags_HeightRegular);
  m.attr("ImGuiComboFlags_HeightLarge") = static_cast<int>(ImGuiComboFlags_HeightLarge);
  m.attr("ImGuiComboFlags_HeightLargest") = static_cast<int>(ImGuiComboFlags_HeightLargest);
  m.attr("ImGuiComboFlags_NoArrowButton") = static_cast<int>(ImGuiComboFlags_NoArrowButton);
  m.attr("ImGuiComboFlags_NoPreview") = static_cast<int>(ImGuiComboFlags_NoPreview);
  m.attr("ImGuiComboFlags_HeightMask_") = static_cast<int>(ImGuiComboFlags_HeightMask_);

  m.attr("ImGuiTabBarFlags_None") = static_cast<int>(ImGuiTabBarFlags_None);
  m.attr("ImGuiTabBarFlags_Reorderable") = static_cast<int>(ImGuiTabBarFlags_Reorderable);
  m.attr("ImGuiTabBarFlags_AutoSelectNewTabs") = static_cast<int>(ImGuiTabBarFlags_AutoSelectNewTabs);
  m.attr("ImGuiTabBarFlags_TabListPopupButton") = static_cast<int>(ImGuiTabBarFlags_TabListPopupButton);
  m.attr("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton") =
      static_cast<int>(ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
  m.attr("ImGuiTabBarFlags_NoTabListScrollingButtons") = static_cast<int>(ImGuiTabBarFlags_NoTabListScrollingButtons);
  m.attr("ImGuiTabBarFlags_NoTooltip") = static_cast<int>(ImGuiTabBarFlags_NoTooltip);
  m.attr("ImGuiTabBarFlags_FittingPolicyResizeDown") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyResizeDown);
  m.attr("ImGuiTabBarFlags_FittingPolicyScroll") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyScroll);
  m.attr("ImGuiTabBarFlags_FittingPolicyMask_") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyMask_);
  m.attr("ImGuiTabBarFlags_FittingPolicyDefault_") = static_cast<int>(ImGuiTabBarFlags_FittingPolicyDefault_);

  m.attr("ImGuiTabItemFlags_None") = static_cast<int>(ImGuiTabItemFlags_None);
  m.attr("ImGuiTabItemFlags_UnsavedDocument") = static_cast<int>(ImGuiTabItemFlags_UnsavedDocument);
  m.attr("ImGuiTabItemFlags_SetSelected") = static_cast<int>(ImGuiTabItemFlags_SetSelected);
  m.attr("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton") =
      static_cast<int>(ImGuiTabItemFlags_NoCloseWithMiddleMouseButton);
  m.attr("ImGuiTabItemFlags_NoPushId") = static_cast<int>(ImGuiTabItemFlags_NoPushId);

  m.attr("ImGuiTableFlags_None") = static_cast<int>(ImGuiTableFlags_None);
  m.attr("ImGuiTableFlags_Resizable") = static_cast<int>(ImGuiTableFlags_Resizable);
  m.attr("ImGuiTableFlags_Reorderable") = static_cast<int>(ImGuiTableFlags_Reorderable);
  m.attr("ImGuiTableFlags_Hideable") = static_cast<int>(ImGuiTableFlags_Hideable);
  m.attr("ImGuiTableFlags_Sortable") = static_cast<int>(ImGuiTableFlags_Sortable);
  m.attr("ImGuiTableFlags_NoSavedSettings") = static_cast<int>(ImGuiTableFlags_NoSavedSettings);
  m.attr("ImGuiTableFlags_ContextMenuInBody") = static_cast<int>(ImGuiTableFlags_ContextMenuInBody);
  m.attr("ImGuiTableFlags_RowBg") = static_cast<int>(ImGuiTableFlags_RowBg);
  m.attr("ImGuiTableFlags_BordersInnerH") = static_cast<int>(ImGuiTableFlags_BordersInnerH);
  m.attr("ImGuiTableFlags_BordersOuterH") = static_cast<int>(ImGuiTableFlags_BordersOuterH);
  m.attr("ImGuiTableFlags_BordersInnerV") = static_cast<int>(ImGuiTableFlags_BordersInnerV);
  m.attr("ImGuiTableFlags_BordersOuterV") = static_cast<int>(ImGuiTableFlags_BordersOuterV);
  m.attr("ImGuiTableFlags_BordersH") = static_cast<int>(ImGuiTableFlags_BordersH);
  m.attr("ImGuiTableFlags_BordersV") = static_cast<int>(ImGuiTableFlags_BordersV);
  m.attr("ImGuiTableFlags_BordersInner") = static_cast<int>(ImGuiTableFlags_BordersInner);
  m.attr("ImGuiTableFlags_BordersOuter") = static_cast<int>(ImGuiTableFlags_BordersOuter);
  m.attr("ImGuiTableFlags_Borders") = static_cast<int>(ImGuiTableFlags_Borders);
  m.attr("ImGuiTableFlags_NoBordersInBody") = static_cast<int>(ImGuiTableFlags_NoBordersInBody);
  m.attr("ImGuiTableFlags_NoBordersInBodyUntilResize") = static_cast<int>(ImGuiTableFlags_NoBordersInBodyUntilResize);
  m.attr("ImGuiTableFlags_SizingFixedFit") = static_cast<int>(ImGuiTableFlags_SizingFixedFit);
  m.attr("ImGuiTableFlags_SizingFixedSame") = static_cast<int>(ImGuiTableFlags_SizingFixedSame);
  m.attr("ImGuiTableFlags_SizingStretchProp") = static_cast<int>(ImGuiTableFlags_SizingStretchProp);
  m.attr("ImGuiTableFlags_SizingStretchSame") = static_cast<int>(ImGuiTableFlags_SizingStretchSame);
  m.attr("ImGuiTableFlags_NoHostExtendX") = static_cast<int>(ImGuiTableFlags_NoHostExtendX);
  m.attr("ImGuiTableFlags_NoHostExtendY") = static_cast<int>(ImGuiTableFlags_NoHostExtendY);
  m.attr("ImGuiTableFlags_NoKeepColumnsVisible") = static_cast<int>(ImGuiTableFlags_NoKeepColumnsVisible);
  m.attr("ImGuiTableFlags_PreciseWidths") = static_cast<int>(ImGuiTableFlags_PreciseWidths);
  m.attr("ImGuiTableFlags_NoClip") = static_cast<int>(ImGuiTableFlags_NoClip);
  m.attr("ImGuiTableFlags_PadOuterX") = static_cast<int>(ImGuiTableFlags_PadOuterX);
  m.attr("ImGuiTableFlags_NoPadOuterX") = static_cast<int>(ImGuiTableFlags_NoPadOuterX);
  m.attr("ImGuiTableFlags_NoPadInnerX") = static_cast<int>(ImGuiTableFlags_NoPadInnerX);
  m.attr("ImGuiTableFlags_ScrollX") = static_cast<int>(ImGuiTableFlags_ScrollX);
  m.attr("ImGuiTableFlags_ScrollY") = static_cast<int>(ImGuiTableFlags_ScrollY);
  m.attr("ImGuiTableFlags_SortMulti") = static_cast<int>(ImGuiTableFlags_SortMulti);
  m.attr("ImGuiTableFlags_SortTristate") = static_cast<int>(ImGuiTableFlags_SortTristate);
  m.attr("ImGuiTableFlags_HighlightHoveredColumn") = static_cast<int>(ImGuiTableFlags_HighlightHoveredColumn);

  m.attr("ImGuiTableColumnFlags_None") = static_cast<int>(ImGuiTableColumnFlags_None);
  m.attr("ImGuiTableColumnFlags_Disabled") = static_cast<int>(ImGuiTableColumnFlags_Disabled);
  m.attr("ImGuiTableColumnFlags_DefaultHide") = static_cast<int>(ImGuiTableColumnFlags_DefaultHide);
  m.attr("ImGuiTableColumnFlags_DefaultSort") = static_cast<int>(ImGuiTableColumnFlags_DefaultSort);
  m.attr("ImGuiTableColumnFlags_WidthStretch") = static_cast<int>(ImGuiTableColumnFlags_WidthStretch);
  m.attr("ImGuiTableColumnFlags_WidthFixed") = static_cast<int>(ImGuiTableColumnFlags_WidthFixed);
  m.attr("ImGuiTableColumnFlags_NoResize") = static_cast<int>(ImGuiTableColumnFlags_NoResize);
  m.attr("ImGuiTableColumnFlags_NoReorder") = static_cast<int>(ImGuiTableColumnFlags_NoReorder);
  m.attr("ImGuiTableColumnFlags_NoHide") = static_cast<int>(ImGuiTableColumnFlags_NoHide);
  m.attr("ImGuiTableColumnFlags_NoClip") = static_cast<int>(ImGuiTableColumnFlags_NoClip);
  m.attr("ImGuiTableColumnFlags_NoSort") = static_cast<int>(ImGuiTableColumnFlags_NoSort);
  m.attr("ImGuiTableColumnFlags_NoSortAscending") = static_cast<int>(ImGuiTableColumnFlags_NoSortAscending);
  m.attr("ImGuiTableColumnFlags_NoSortDescending") = static_cast<int>(ImGuiTableColumnFlags_NoSortDescending);
  m.attr("ImGuiTableColumnFlags_NoHeaderLabel") = static_cast<int>(ImGuiTableColumnFlags_NoHeaderLabel);
  m.attr("ImGuiTableColumnFlags_NoHeaderWidth") = static_cast<int>(ImGuiTableColumnFlags_NoHeaderWidth);
  m.attr("ImGuiTableColumnFlags_PreferSortAscending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortAscending);
  m.attr("ImGuiTableColumnFlags_PreferSortDescending") = static_cast<int>(ImGuiTableColumnFlags_PreferSortDescending);
  m.attr("ImGuiTableColumnFlags_IndentEnable") = static_cast<int>(ImGuiTableColumnFlags_IndentEnable);
  m.attr("ImGuiTableColumnFlags_IndentDisable") = static_cast<int>(ImGuiTableColumnFlags_IndentDisable);
  m.attr("ImGuiTableColumnFlags_AngledHeader") = static_cast<int>(ImGuiTableColumnFlags_AngledHeader);
  m.attr("ImGuiTableColumnFlags_IsEnabled") = static_cast<int>(ImGuiTableColumnFlags_IsEnabled);
  m.attr("ImGuiTableColumnFlags_IsVisible") = static_cast<int>(ImGuiTableColumnFlags_IsVisible);
  m.attr("ImGuiTableColumnFlags_IsSorted") = static_cast<int>(ImGuiTableColumnFlags_IsSorted);
  m.attr("ImGuiTableColumnFlags_IsHovered") = static_cast<int>(ImGuiTableColumnFlags_IsHovered);
  
  m.attr("ImGuiTableRowFlags_None") = static_cast<int>(ImGuiTableRowFlags_None);
  m.attr("ImGuiTableRowFlags_Headers") = static_cast<int>(ImGuiTableRowFlags_Headers);
  
  m.attr("ImGuiTableBgTarget_None") = static_cast<int>(ImGuiTableBgTarget_None);
  m.attr("ImGuiTableBgTarget_RowBg0") = static_cast<int>(ImGuiTableBgTarget_RowBg0);
  m.attr("ImGuiTableBgTarget_RowBg1") = static_cast<int>(ImGuiTableBgTarget_RowBg1);
  m.attr("ImGuiTableBgTarget_CellBg") = static_cast<int>(ImGuiTableBgTarget_CellBg);

  m.attr("ImGuiFocusedFlags_None") = static_cast<int>(ImGuiFocusedFlags_None);
  m.attr("ImGuiFocusedFlags_ChildWindows") = static_cast<int>(ImGuiFocusedFlags_ChildWindows);
  m.attr("ImGuiFocusedFlags_RootWindow") = static_cast<int>(ImGuiFocusedFlags_RootWindow);
  m.attr("ImGuiFocusedFlags_AnyWindow") = static_cast<int>(ImGuiFocusedFlags_AnyWindow);
  m.attr("ImGuiFocusedFlags_RootAndChildWindows") = static_cast<int>(ImGuiFocusedFlags_RootAndChildWindows);

  m.attr("ImGuiHoveredFlags_None") = static_cast<int>(ImGuiHoveredFlags_None);
  m.attr("ImGuiHoveredFlags_ChildWindows") = static_cast<int>(ImGuiHoveredFlags_ChildWindows);
  m.attr("ImGuiHoveredFlags_RootWindow") = static_cast<int>(ImGuiHoveredFlags_RootWindow);
  m.attr("ImGuiHoveredFlags_AnyWindow") = static_cast<int>(ImGuiHoveredFlags_AnyWindow);
  m.attr("ImGuiHoveredFlags_AllowWhenBlockedByPopup") = static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
  m.attr("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem") =
      static_cast<int>(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
  m.attr("ImGuiHoveredFlags_AllowWhenOverlapped") = static_cast<int>(ImGuiHoveredFlags_AllowWhenOverlapped);
  m.attr("ImGuiHoveredFlags_AllowWhenDisabled") = static_cast<int>(ImGuiHoveredFlags_AllowWhenDisabled);
  m.attr("ImGuiHoveredFlags_RectOnly") = static_cast<int>(ImGuiHoveredFlags_RectOnly);
  m.attr("ImGuiHoveredFlags_RootAndChildWindows") = static_cast<int>(ImGuiHoveredFlags_RootAndChildWindows);

  m.attr("ImGuiDragDropFlags_None") = static_cast<int>(ImGuiDragDropFlags_None);
  m.attr("ImGuiDragDropFlags_SourceNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_SourceNoPreviewTooltip);
  m.attr("ImGuiDragDropFlags_SourceNoDisableHover") = static_cast<int>(ImGuiDragDropFlags_SourceNoDisableHover);
  m.attr("ImGuiDragDropFlags_SourceNoHoldToOpenOthers") = static_cast<int>(ImGuiDragDropFlags_SourceNoHoldToOpenOthers);
  m.attr("ImGuiDragDropFlags_SourceAllowNullID") = static_cast<int>(ImGuiDragDropFlags_SourceAllowNullID);
  m.attr("ImGuiDragDropFlags_SourceExtern") = static_cast<int>(ImGuiDragDropFlags_SourceExtern);
  m.attr("ImGuiDragDropFlags_SourceAutoExpirePayload") = static_cast<int>(ImGuiDragDropFlags_SourceAutoExpirePayload);
  m.attr("ImGuiDragDropFlags_AcceptBeforeDelivery") = static_cast<int>(ImGuiDragDropFlags_AcceptBeforeDelivery);
  m.attr("ImGuiDragDropFlags_AcceptNoDrawDefaultRect") = static_cast<int>(ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
  m.attr("ImGuiDragDropFlags_AcceptNoPreviewTooltip") = static_cast<int>(ImGuiDragDropFlags_AcceptNoPreviewTooltip);
  m.attr("ImGuiDragDropFlags_AcceptPeekOnly") = static_cast<int>(ImGuiDragDropFlags_AcceptPeekOnly);

  m.attr("ImGuiDataType_S8") = static_cast<int>(ImGuiDataType_S8);
  m.attr("ImGuiDataType_U8") = static_cast<int>(ImGuiDataType_U8);
  m.attr("ImGuiDataType_S16") = static_cast<int>(ImGuiDataType_S16);
  m.attr("ImGuiDataType_U16") = static_cast<int>(ImGuiDataType_U16);
  m.attr("ImGuiDataType_S32") = static_cast<int>(ImGuiDataType_S32);
  m.attr("ImGuiDataType_U32") = static_cast<int>(ImGuiDataType_U32);
  m.attr("ImGuiDataType_S64") = static_cast<int>(ImGuiDataType_S64);
  m.attr("ImGuiDataType_U64") = static_cast<int>(ImGuiDataType_U64);
  m.attr("ImGuiDataType_Float") = static_cast<int>(ImGuiDataType_Float);
  m.attr("ImGuiDataType_Double") = static_cast<int>(ImGuiDataType_Double);
  m.attr("ImGuiDataType_COUNT") = static_cast<int>(ImGuiDataType_COUNT);

  m.attr("ImGuiDir_None") = static_cast<int>(ImGuiDir_None);
  m.attr("ImGuiDir_Left") = static_cast<int>(ImGuiDir_Left);
  m.attr("ImGuiDir_Right") = static_cast<int>(ImGuiDir_Right);
  m.attr("ImGuiDir_Up") = static_cast<int>(ImGuiDir_Up);
  m.attr("ImGuiDir_Down") = static_cast<int>(ImGuiDir_Down);
  m.attr("ImGuiDir_COUNT") = static_cast<int>(ImGuiDir_COUNT);

  m.attr("ImGuiSortDirection_None") = static_cast<int>(ImGuiSortDirection_None);
  m.attr("ImGuiSortDirection_Ascending") = static_cast<int>(ImGuiSortDirection_Ascending);
  m.attr("ImGuiSortDirection_Descending") = static_cast<int>(ImGuiSortDirection_Descending);

  // TODO replace all enum bindings to work like this (although it does force us to repeat ourselves twice)
  nb::enum_<ImGuiKey>(m, "ImGuiKey")
    .value("ImGuiKey_None", ImGuiKey::ImGuiKey_None)
    .value("ImGuiKey_Tab", ImGuiKey::ImGuiKey_Tab)
    .value("ImGuiKey_LeftArrow", ImGuiKey::ImGuiKey_LeftArrow)
    .value("ImGuiKey_RightArrow", ImGuiKey::ImGuiKey_RightArrow)
    .value("ImGuiKey_UpArrow", ImGuiKey::ImGuiKey_UpArrow)
    .value("ImGuiKey_DownArrow", ImGuiKey::ImGuiKey_DownArrow)
    .value("ImGuiKey_PageUp", ImGuiKey::ImGuiKey_PageUp)
    .value("ImGuiKey_PageDown", ImGuiKey::ImGuiKey_PageDown)
    .value("ImGuiKey_Home", ImGuiKey::ImGuiKey_Home)
    .value("ImGuiKey_End", ImGuiKey::ImGuiKey_End)
    .value("ImGuiKey_Insert", ImGuiKey::ImGuiKey_Insert)
    .value("ImGuiKey_Delete", ImGuiKey::ImGuiKey_Delete)
    .value("ImGuiKey_Backspace", ImGuiKey::ImGuiKey_Backspace)
    .value("ImGuiKey_Space", ImGuiKey::ImGuiKey_Space)
    .value("ImGuiKey_Enter", ImGuiKey::ImGuiKey_Enter)
    .value("ImGuiKey_Escape", ImGuiKey::ImGuiKey_Escape)
    .value("ImGuiKey_LeftCtrl", ImGuiKey::ImGuiKey_LeftCtrl)
    .value("ImGuiKey_LeftShift", ImGuiKey::ImGuiKey_LeftShift)
    .value("ImGuiKey_LeftAlt", ImGuiKey::ImGuiKey_LeftAlt)
    .value("ImGuiKey_LeftSuper", ImGuiKey::ImGuiKey_LeftSuper)
    .value("ImGuiKey_RightCtrl", ImGuiKey::ImGuiKey_RightCtrl)
    .value("ImGuiKey_RightShift", ImGuiKey::ImGuiKey_RightShift)
    .value("ImGuiKey_RightAlt", ImGuiKey::ImGuiKey_RightAlt)
    .value("ImGuiKey_RightSuper", ImGuiKey::ImGuiKey_RightSuper)
    .value("ImGuiKey_Menu", ImGuiKey::ImGuiKey_Menu)
    .value("ImGuiKey_0", ImGuiKey::ImGuiKey_0)
    .value("ImGuiKey_1", ImGuiKey::ImGuiKey_1)
    .value("ImGuiKey_2", ImGuiKey::ImGuiKey_2)
    .value("ImGuiKey_3", ImGuiKey::ImGuiKey_3)
    .value("ImGuiKey_4", ImGuiKey::ImGuiKey_4)
    .value("ImGuiKey_5", ImGuiKey::ImGuiKey_5)
    .value("ImGuiKey_6", ImGuiKey::ImGuiKey_6)
    .value("ImGuiKey_7", ImGuiKey::ImGuiKey_7)
    .value("ImGuiKey_8", ImGuiKey::ImGuiKey_8)
    .value("ImGuiKey_9", ImGuiKey::ImGuiKey_9)
    .value("ImGuiKey_A", ImGuiKey::ImGuiKey_A)
    .value("ImGuiKey_B", ImGuiKey::ImGuiKey_B)
    .value("ImGuiKey_C", ImGuiKey::ImGuiKey_C)
    .value("ImGuiKey_D", ImGuiKey::ImGuiKey_D)
    .value("ImGuiKey_E", ImGuiKey::ImGuiKey_E)
    .value("ImGuiKey_F", ImGuiKey::ImGuiKey_F)
    .value("ImGuiKey_G", ImGuiKey::ImGuiKey_G)
    .value("ImGuiKey_H", ImGuiKey::ImGuiKey_H)
    .value("ImGuiKey_I", ImGuiKey::ImGuiKey_I)
    .value("ImGuiKey_J", ImGuiKey::ImGuiKey_J)
    .value("ImGuiKey_K", ImGuiKey::ImGuiKey_K)
    .value("ImGuiKey_L", ImGuiKey::ImGuiKey_L)
    .value("ImGuiKey_M", ImGuiKey::ImGuiKey_M)
    .value("ImGuiKey_N", ImGuiKey::ImGuiKey_N)
    .value("ImGuiKey_O", ImGuiKey::ImGuiKey_O)
    .value("ImGuiKey_P", ImGuiKey::ImGuiKey_P)
    .value("ImGuiKey_Q", ImGuiKey::ImGuiKey_Q)
    .value("ImGuiKey_R", ImGuiKey::ImGuiKey_R)
    .value("ImGuiKey_S", ImGuiKey::ImGuiKey_S)
    .value("ImGuiKey_T", ImGuiKey::ImGuiKey_T)
    .value("ImGuiKey_U", ImGuiKey::ImGuiKey_U)
    .value("ImGuiKey_V", ImGuiKey::ImGuiKey_V)
    .value("ImGuiKey_W", ImGuiKey::ImGuiKey_W)
    .value("ImGuiKey_X", ImGuiKey::ImGuiKey_X)
    .value("ImGuiKey_Y", ImGuiKey::ImGuiKey_Y)
    .value("ImGuiKey_Z", ImGuiKey::ImGuiKey_Z)
    .value("ImGuiKey_F1", ImGuiKey::ImGuiKey_F1)
    .value("ImGuiKey_F2", ImGuiKey::ImGuiKey_F2)
    .value("ImGuiKey_F3", ImGuiKey::ImGuiKey_F3)
    .value("ImGuiKey_F4", ImGuiKey::ImGuiKey_F4)
    .value("ImGuiKey_F5", ImGuiKey::ImGuiKey_F5)
    .value("ImGuiKey_F6", ImGuiKey::ImGuiKey_F6)
    .value("ImGuiKey_F7", ImGuiKey::ImGuiKey_F7)
    .value("ImGuiKey_F8", ImGuiKey::ImGuiKey_F8)
    .value("ImGuiKey_F9", ImGuiKey::ImGuiKey_F9)
    .value("ImGuiKey_F10", ImGuiKey::ImGuiKey_F10)
    .value("ImGuiKey_F11", ImGuiKey::ImGuiKey_F11)
    .value("ImGuiKey_F12", ImGuiKey::ImGuiKey_F12)
    .value("ImGuiKey_F13", ImGuiKey::ImGuiKey_F13)
    .value("ImGuiKey_F14", ImGuiKey::ImGuiKey_F14)
    .value("ImGuiKey_F15", ImGuiKey::ImGuiKey_F15)
    .value("ImGuiKey_F16", ImGuiKey::ImGuiKey_F16)
    .value("ImGuiKey_F17", ImGuiKey::ImGuiKey_F17)
    .value("ImGuiKey_F18", ImGuiKey::ImGuiKey_F18)
    .value("ImGuiKey_F19", ImGuiKey::ImGuiKey_F19)
    .value("ImGuiKey_F20", ImGuiKey::ImGuiKey_F20)
    .value("ImGuiKey_F21", ImGuiKey::ImGuiKey_F21)
    .value("ImGuiKey_F22", ImGuiKey::ImGuiKey_F22)
    .value("ImGuiKey_F23", ImGuiKey::ImGuiKey_F23)
    .value("ImGuiKey_F24", ImGuiKey::ImGuiKey_F24)
    .value("ImGuiKey_Apostrophe", ImGuiKey::ImGuiKey_Apostrophe)
    .value("ImGuiKey_Comma", ImGuiKey::ImGuiKey_Comma)
    .value("ImGuiKey_Minus", ImGuiKey::ImGuiKey_Minus)
    .value("ImGuiKey_Period", ImGuiKey::ImGuiKey_Period)
    .value("ImGuiKey_Slash", ImGuiKey::ImGuiKey_Slash)
    .value("ImGuiKey_Semicolon", ImGuiKey::ImGuiKey_Semicolon)
    .value("ImGuiKey_Equal", ImGuiKey::ImGuiKey_Equal)
    .value("ImGuiKey_LeftBracket", ImGuiKey::ImGuiKey_LeftBracket)
    .value("ImGuiKey_Backslash", ImGuiKey::ImGuiKey_Backslash)
    .value("ImGuiKey_RightBracket", ImGuiKey::ImGuiKey_RightBracket)
    .value("ImGuiKey_GraveAccent", ImGuiKey::ImGuiKey_GraveAccent)
    .value("ImGuiKey_CapsLock", ImGuiKey::ImGuiKey_CapsLock)
    .value("ImGuiKey_ScrollLock", ImGuiKey::ImGuiKey_ScrollLock)
    .value("ImGuiKey_NumLock", ImGuiKey::ImGuiKey_NumLock)
    .value("ImGuiKey_PrintScreen", ImGuiKey::ImGuiKey_PrintScreen)
    .value("ImGuiKey_Pause", ImGuiKey::ImGuiKey_Pause)
    .value("ImGuiKey_Keypad0", ImGuiKey::ImGuiKey_Keypad0)
    .value("ImGuiKey_Keypad1", ImGuiKey::ImGuiKey_Keypad1)
    .value("ImGuiKey_Keypad2", ImGuiKey::ImGuiKey_Keypad2)
    .value("ImGuiKey_Keypad3", ImGuiKey::ImGuiKey_Keypad3)
    .value("ImGuiKey_Keypad4", ImGuiKey::ImGuiKey_Keypad4)
    .value("ImGuiKey_Keypad5", ImGuiKey::ImGuiKey_Keypad5)
    .value("ImGuiKey_Keypad6", ImGuiKey::ImGuiKey_Keypad6)
    .value("ImGuiKey_Keypad7", ImGuiKey::ImGuiKey_Keypad7)
    .value("ImGuiKey_Keypad8", ImGuiKey::ImGuiKey_Keypad8)
    .value("ImGuiKey_Keypad9", ImGuiKey::ImGuiKey_Keypad9)
    .value("ImGuiKey_KeypadDecimal", ImGuiKey::ImGuiKey_KeypadDecimal)
    .value("ImGuiKey_KeypadDivide", ImGuiKey::ImGuiKey_KeypadDivide)
    .value("ImGuiKey_KeypadMultiply", ImGuiKey::ImGuiKey_KeypadMultiply)
    .value("ImGuiKey_KeypadSubtract", ImGuiKey::ImGuiKey_KeypadSubtract)
    .value("ImGuiKey_KeypadAdd", ImGuiKey::ImGuiKey_KeypadAdd)
    .value("ImGuiKey_KeypadEnter", ImGuiKey::ImGuiKey_KeypadEnter)
    .value("ImGuiKey_KeypadEqual", ImGuiKey::ImGuiKey_KeypadEqual)
    .value("ImGuiKey_AppBack", ImGuiKey::ImGuiKey_AppBack)
    .value("ImGuiKey_AppForward", ImGuiKey::ImGuiKey_AppForward)
    .value("ImGuiKey_GamepadStart", ImGuiKey::ImGuiKey_GamepadStart)
    .value("ImGuiKey_GamepadBack", ImGuiKey::ImGuiKey_GamepadBack)
    .value("ImGuiKey_GamepadFaceUp", ImGuiKey::ImGuiKey_GamepadFaceUp)
    .value("ImGuiKey_GamepadFaceDown", ImGuiKey::ImGuiKey_GamepadFaceDown)
    .value("ImGuiKey_GamepadFaceLeft", ImGuiKey::ImGuiKey_GamepadFaceLeft)
    .value("ImGuiKey_GamepadFaceRight", ImGuiKey::ImGuiKey_GamepadFaceRight)
    .value("ImGuiKey_GamepadDpadUp", ImGuiKey::ImGuiKey_GamepadDpadUp)
    .value("ImGuiKey_GamepadDpadDown", ImGuiKey::ImGuiKey_GamepadDpadDown)
    .value("ImGuiKey_GamepadDpadLeft", ImGuiKey::ImGuiKey_GamepadDpadLeft)
    .value("ImGuiKey_GamepadDpadRight", ImGuiKey::ImGuiKey_GamepadDpadRight)
    .value("ImGuiKey_GamepadL1", ImGuiKey::ImGuiKey_GamepadL1)
    .value("ImGuiKey_GamepadR1", ImGuiKey::ImGuiKey_GamepadR1)
    .value("ImGuiKey_GamepadL2", ImGuiKey::ImGuiKey_GamepadL2)
    .value("ImGuiKey_GamepadR2", ImGuiKey::ImGuiKey_GamepadR2)
    .value("ImGuiKey_GamepadL3", ImGuiKey::ImGuiKey_GamepadL3)
    .value("ImGuiKey_GamepadR3", ImGuiKey::ImGuiKey_GamepadR3)
    .value("ImGuiKey_GamepadLStickUp", ImGuiKey::ImGuiKey_GamepadLStickUp)
    .value("ImGuiKey_GamepadLStickDown", ImGuiKey::ImGuiKey_GamepadLStickDown)
    .value("ImGuiKey_GamepadLStickLeft", ImGuiKey::ImGuiKey_GamepadLStickLeft)
    .value("ImGuiKey_GamepadLStickRight", ImGuiKey::ImGuiKey_GamepadLStickRight)
    .value("ImGuiKey_GamepadRStickUp", ImGuiKey::ImGuiKey_GamepadRStickUp)
    .value("ImGuiKey_GamepadRStickDown", ImGuiKey::ImGuiKey_GamepadRStickDown)
    .value("ImGuiKey_GamepadRStickLeft", ImGuiKey::ImGuiKey_GamepadRStickLeft)
    .value("ImGuiKey_GamepadRStickRight", ImGuiKey::ImGuiKey_GamepadRStickRight)
    .value("ImGuiKey_ModCtrl", ImGuiKey::ImGuiKey_ModCtrl)
    .value("ImGuiKey_ModShift", ImGuiKey::ImGuiKey_ModShift)
    .value("ImGuiKey_ModAlt", ImGuiKey::ImGuiKey_ModAlt)
    .value("ImGuiKey_ModSuper", ImGuiKey::ImGuiKey_ModSuper)
  ;

  m.attr("ImGuiKey_None") = ImGuiKey::ImGuiKey_None;
  m.attr("ImGuiKey_Tab") = ImGuiKey::ImGuiKey_Tab;
  m.attr("ImGuiKey_LeftArrow") = ImGuiKey::ImGuiKey_LeftArrow;
  m.attr("ImGuiKey_RightArrow") = ImGuiKey::ImGuiKey_RightArrow;
  m.attr("ImGuiKey_UpArrow") = ImGuiKey::ImGuiKey_UpArrow;
  m.attr("ImGuiKey_DownArrow") = ImGuiKey::ImGuiKey_DownArrow;
  m.attr("ImGuiKey_PageUp") = ImGuiKey::ImGuiKey_PageUp;
  m.attr("ImGuiKey_PageDown") = ImGuiKey::ImGuiKey_PageDown;
  m.attr("ImGuiKey_Home") = ImGuiKey::ImGuiKey_Home;
  m.attr("ImGuiKey_End") = ImGuiKey::ImGuiKey_End;
  m.attr("ImGuiKey_Insert") = ImGuiKey::ImGuiKey_Insert;
  m.attr("ImGuiKey_Delete") = ImGuiKey::ImGuiKey_Delete;
  m.attr("ImGuiKey_Backspace") = ImGuiKey::ImGuiKey_Backspace;
  m.attr("ImGuiKey_Space") = ImGuiKey::ImGuiKey_Space;
  m.attr("ImGuiKey_Enter") = ImGuiKey::ImGuiKey_Enter;
  m.attr("ImGuiKey_Escape") = ImGuiKey::ImGuiKey_Escape;
  m.attr("ImGuiKey_LeftCtrl") = ImGuiKey::ImGuiKey_LeftCtrl;
  m.attr("ImGuiKey_LeftShift") = ImGuiKey::ImGuiKey_LeftShift;
  m.attr("ImGuiKey_LeftAlt") = ImGuiKey::ImGuiKey_LeftAlt;
  m.attr("ImGuiKey_LeftSuper") = ImGuiKey::ImGuiKey_LeftSuper;
  m.attr("ImGuiKey_RightCtrl") = ImGuiKey::ImGuiKey_RightCtrl;
  m.attr("ImGuiKey_RightShift") = ImGuiKey::ImGuiKey_RightShift;
  m.attr("ImGuiKey_RightAlt") = ImGuiKey::ImGuiKey_RightAlt;
  m.attr("ImGuiKey_RightSuper") = ImGuiKey::ImGuiKey_RightSuper;
  m.attr("ImGuiKey_Menu") = ImGuiKey::ImGuiKey_Menu;
  m.attr("ImGuiKey_0") = ImGuiKey::ImGuiKey_0;
  m.attr("ImGuiKey_1") = ImGuiKey::ImGuiKey_1;
  m.attr("ImGuiKey_2") = ImGuiKey::ImGuiKey_2;
  m.attr("ImGuiKey_3") = ImGuiKey::ImGuiKey_3;
  m.attr("ImGuiKey_4") = ImGuiKey::ImGuiKey_4;
  m.attr("ImGuiKey_5") = ImGuiKey::ImGuiKey_5;
  m.attr("ImGuiKey_6") = ImGuiKey::ImGuiKey_6;
  m.attr("ImGuiKey_7") = ImGuiKey::ImGuiKey_7;
  m.attr("ImGuiKey_8") = ImGuiKey::ImGuiKey_8;
  m.attr("ImGuiKey_9") = ImGuiKey::ImGuiKey_9;
  m.attr("ImGuiKey_A") = ImGuiKey::ImGuiKey_A;
  m.attr("ImGuiKey_B") = ImGuiKey::ImGuiKey_B;
  m.attr("ImGuiKey_C") = ImGuiKey::ImGuiKey_C;
  m.attr("ImGuiKey_D") = ImGuiKey::ImGuiKey_D;
  m.attr("ImGuiKey_E") = ImGuiKey::ImGuiKey_E;
  m.attr("ImGuiKey_F") = ImGuiKey::ImGuiKey_F;
  m.attr("ImGuiKey_G") = ImGuiKey::ImGuiKey_G;
  m.attr("ImGuiKey_H") = ImGuiKey::ImGuiKey_H;
  m.attr("ImGuiKey_I") = ImGuiKey::ImGuiKey_I;
  m.attr("ImGuiKey_J") = ImGuiKey::ImGuiKey_J;
  m.attr("ImGuiKey_K") = ImGuiKey::ImGuiKey_K;
  m.attr("ImGuiKey_L") = ImGuiKey::ImGuiKey_L;
  m.attr("ImGuiKey_M") = ImGuiKey::ImGuiKey_M;
  m.attr("ImGuiKey_N") = ImGuiKey::ImGuiKey_N;
  m.attr("ImGuiKey_O") = ImGuiKey::ImGuiKey_O;
  m.attr("ImGuiKey_P") = ImGuiKey::ImGuiKey_P;
  m.attr("ImGuiKey_Q") = ImGuiKey::ImGuiKey_Q;
  m.attr("ImGuiKey_R") = ImGuiKey::ImGuiKey_R;
  m.attr("ImGuiKey_S") = ImGuiKey::ImGuiKey_S;
  m.attr("ImGuiKey_T") = ImGuiKey::ImGuiKey_T;
  m.attr("ImGuiKey_U") = ImGuiKey::ImGuiKey_U;
  m.attr("ImGuiKey_V") = ImGuiKey::ImGuiKey_V;
  m.attr("ImGuiKey_W") = ImGuiKey::ImGuiKey_W;
  m.attr("ImGuiKey_X") = ImGuiKey::ImGuiKey_X;
  m.attr("ImGuiKey_Y") = ImGuiKey::ImGuiKey_Y;
  m.attr("ImGuiKey_Z") = ImGuiKey::ImGuiKey_Z;
  m.attr("ImGuiKey_F1") = ImGuiKey::ImGuiKey_F1;
  m.attr("ImGuiKey_F2") = ImGuiKey::ImGuiKey_F2;
  m.attr("ImGuiKey_F3") = ImGuiKey::ImGuiKey_F3;
  m.attr("ImGuiKey_F4") = ImGuiKey::ImGuiKey_F4;
  m.attr("ImGuiKey_F5") = ImGuiKey::ImGuiKey_F5;
  m.attr("ImGuiKey_F6") = ImGuiKey::ImGuiKey_F6;
  m.attr("ImGuiKey_F7") = ImGuiKey::ImGuiKey_F7;
  m.attr("ImGuiKey_F8") = ImGuiKey::ImGuiKey_F8;
  m.attr("ImGuiKey_F9") = ImGuiKey::ImGuiKey_F9;
  m.attr("ImGuiKey_F10") = ImGuiKey::ImGuiKey_F10;
  m.attr("ImGuiKey_F11") = ImGuiKey::ImGuiKey_F11;
  m.attr("ImGuiKey_F12") = ImGuiKey::ImGuiKey_F12;
  m.attr("ImGuiKey_F13") = ImGuiKey::ImGuiKey_F13;
  m.attr("ImGuiKey_F14") = ImGuiKey::ImGuiKey_F14;
  m.attr("ImGuiKey_F15") = ImGuiKey::ImGuiKey_F15;
  m.attr("ImGuiKey_F16") = ImGuiKey::ImGuiKey_F16;
  m.attr("ImGuiKey_F17") = ImGuiKey::ImGuiKey_F17;
  m.attr("ImGuiKey_F18") = ImGuiKey::ImGuiKey_F18;
  m.attr("ImGuiKey_F19") = ImGuiKey::ImGuiKey_F19;
  m.attr("ImGuiKey_F20") = ImGuiKey::ImGuiKey_F20;
  m.attr("ImGuiKey_F21") = ImGuiKey::ImGuiKey_F21;
  m.attr("ImGuiKey_F22") = ImGuiKey::ImGuiKey_F22;
  m.attr("ImGuiKey_F23") = ImGuiKey::ImGuiKey_F23;
  m.attr("ImGuiKey_F24") = ImGuiKey::ImGuiKey_F24;
  m.attr("ImGuiKey_Apostrophe") = ImGuiKey::ImGuiKey_Apostrophe;
  m.attr("ImGuiKey_Comma") = ImGuiKey::ImGuiKey_Comma;
  m.attr("ImGuiKey_Minus") = ImGuiKey::ImGuiKey_Minus;
  m.attr("ImGuiKey_Period") = ImGuiKey::ImGuiKey_Period;
  m.attr("ImGuiKey_Slash") = ImGuiKey::ImGuiKey_Slash;
  m.attr("ImGuiKey_Semicolon") = ImGuiKey::ImGuiKey_Semicolon;
  m.attr("ImGuiKey_Equal") = ImGuiKey::ImGuiKey_Equal;
  m.attr("ImGuiKey_LeftBracket") = ImGuiKey::ImGuiKey_LeftBracket;
  m.attr("ImGuiKey_Backslash") = ImGuiKey::ImGuiKey_Backslash;
  m.attr("ImGuiKey_RightBracket") = ImGuiKey::ImGuiKey_RightBracket;
  m.attr("ImGuiKey_GraveAccent") = ImGuiKey::ImGuiKey_GraveAccent;
  m.attr("ImGuiKey_CapsLock") = ImGuiKey::ImGuiKey_CapsLock;
  m.attr("ImGuiKey_ScrollLock") = ImGuiKey::ImGuiKey_ScrollLock;
  m.attr("ImGuiKey_NumLock") = ImGuiKey::ImGuiKey_NumLock;
  m.attr("ImGuiKey_PrintScreen") = ImGuiKey::ImGuiKey_PrintScreen;
  m.attr("ImGuiKey_Pause") = ImGuiKey::ImGuiKey_Pause;
  m.attr("ImGuiKey_Keypad0") = ImGuiKey::ImGuiKey_Keypad0;
  m.attr("ImGuiKey_Keypad1") = ImGuiKey::ImGuiKey_Keypad1;
  m.attr("ImGuiKey_Keypad2") = ImGuiKey::ImGuiKey_Keypad2;
  m.attr("ImGuiKey_Keypad3") = ImGuiKey::ImGuiKey_Keypad3;
  m.attr("ImGuiKey_Keypad4") = ImGuiKey::ImGuiKey_Keypad4;
  m.attr("ImGuiKey_Keypad5") = ImGuiKey::ImGuiKey_Keypad5;
  m.attr("ImGuiKey_Keypad6") = ImGuiKey::ImGuiKey_Keypad6;
  m.attr("ImGuiKey_Keypad7") = ImGuiKey::ImGuiKey_Keypad7;
  m.attr("ImGuiKey_Keypad8") = ImGuiKey::ImGuiKey_Keypad8;
  m.attr("ImGuiKey_Keypad9") = ImGuiKey::ImGuiKey_Keypad9;
  m.attr("ImGuiKey_KeypadDecimal") = ImGuiKey::ImGuiKey_KeypadDecimal;
  m.attr("ImGuiKey_KeypadDivide") = ImGuiKey::ImGuiKey_KeypadDivide;
  m.attr("ImGuiKey_KeypadMultiply") = ImGuiKey::ImGuiKey_KeypadMultiply;
  m.attr("ImGuiKey_KeypadSubtract") = ImGuiKey::ImGuiKey_KeypadSubtract;
  m.attr("ImGuiKey_KeypadAdd") = ImGuiKey::ImGuiKey_KeypadAdd;
  m.attr("ImGuiKey_KeypadEnter") = ImGuiKey::ImGuiKey_KeypadEnter;
  m.attr("ImGuiKey_KeypadEqual") = ImGuiKey::ImGuiKey_KeypadEqual;
  m.attr("ImGuiKey_AppBack") = ImGuiKey::ImGuiKey_AppBack;
  m.attr("ImGuiKey_AppForward") = ImGuiKey::ImGuiKey_AppForward;
  m.attr("ImGuiKey_GamepadStart") = ImGuiKey::ImGuiKey_GamepadStart;
  m.attr("ImGuiKey_GamepadBack") = ImGuiKey::ImGuiKey_GamepadBack;
  m.attr("ImGuiKey_GamepadFaceUp") = ImGuiKey::ImGuiKey_GamepadFaceUp;
  m.attr("ImGuiKey_GamepadFaceDown") = ImGuiKey::ImGuiKey_GamepadFaceDown;
  m.attr("ImGuiKey_GamepadFaceLeft") = ImGuiKey::ImGuiKey_GamepadFaceLeft;
  m.attr("ImGuiKey_GamepadFaceRight") = ImGuiKey::ImGuiKey_GamepadFaceRight;
  m.attr("ImGuiKey_GamepadDpadUp") = ImGuiKey::ImGuiKey_GamepadDpadUp;
  m.attr("ImGuiKey_GamepadDpadDown") = ImGuiKey::ImGuiKey_GamepadDpadDown;
  m.attr("ImGuiKey_GamepadDpadLeft") = ImGuiKey::ImGuiKey_GamepadDpadLeft;
  m.attr("ImGuiKey_GamepadDpadRight") = ImGuiKey::ImGuiKey_GamepadDpadRight;
  m.attr("ImGuiKey_GamepadL1") = ImGuiKey::ImGuiKey_GamepadL1;
  m.attr("ImGuiKey_GamepadR1") = ImGuiKey::ImGuiKey_GamepadR1;
  m.attr("ImGuiKey_GamepadL2") = ImGuiKey::ImGuiKey_GamepadL2;
  m.attr("ImGuiKey_GamepadR2") = ImGuiKey::ImGuiKey_GamepadR2;
  m.attr("ImGuiKey_GamepadL3") = ImGuiKey::ImGuiKey_GamepadL3;
  m.attr("ImGuiKey_GamepadR3") = ImGuiKey::ImGuiKey_GamepadR3;
  m.attr("ImGuiKey_GamepadLStickUp") = ImGuiKey::ImGuiKey_GamepadLStickUp;
  m.attr("ImGuiKey_GamepadLStickDown") = ImGuiKey::ImGuiKey_GamepadLStickDown;
  m.attr("ImGuiKey_GamepadLStickLeft") = ImGuiKey::ImGuiKey_GamepadLStickLeft;
  m.attr("ImGuiKey_GamepadLStickRight") = ImGuiKey::ImGuiKey_GamepadLStickRight;
  m.attr("ImGuiKey_GamepadRStickUp") = ImGuiKey::ImGuiKey_GamepadRStickUp;
  m.attr("ImGuiKey_GamepadRStickDown") = ImGuiKey::ImGuiKey_GamepadRStickDown;
  m.attr("ImGuiKey_GamepadRStickLeft") = ImGuiKey::ImGuiKey_GamepadRStickLeft;
  m.attr("ImGuiKey_GamepadRStickRight") = ImGuiKey::ImGuiKey_GamepadRStickRight;
  m.attr("ImGuiKey_ModCtrl") = ImGuiKey::ImGuiKey_ModCtrl;
  m.attr("ImGuiKey_ModShift") = ImGuiKey::ImGuiKey_ModShift;
  m.attr("ImGuiKey_ModAlt") = ImGuiKey::ImGuiKey_ModAlt;
  m.attr("ImGuiKey_ModSuper") = ImGuiKey::ImGuiKey_ModSuper;

  m.attr("ImGuiMod_None") = static_cast<int>(ImGuiMod_None);
  m.attr("ImGuiMod_Ctrl") = static_cast<int>(ImGuiMod_Ctrl);
  m.attr("ImGuiMod_Shift") = static_cast<int>(ImGuiMod_Shift);
  m.attr("ImGuiMod_Alt") = static_cast<int>(ImGuiMod_Alt);
  m.attr("ImGuiMod_Super") = static_cast<int>(ImGuiMod_Super);
  m.attr("ImGuiMod_Mask_") = static_cast<int>(ImGuiMod_Mask_);

  m.attr("ImGuiConfigFlags_None") = static_cast<int>(ImGuiConfigFlags_None);
  m.attr("ImGuiConfigFlags_NavEnableKeyboard") = static_cast<int>(ImGuiConfigFlags_NavEnableKeyboard);
  m.attr("ImGuiConfigFlags_NavEnableGamepad") = static_cast<int>(ImGuiConfigFlags_NavEnableGamepad);
  m.attr("ImGuiConfigFlags_NavEnableSetMousePos") = static_cast<int>(ImGuiConfigFlags_NavEnableSetMousePos);
  m.attr("ImGuiConfigFlags_NavNoCaptureKeyboard") = static_cast<int>(ImGuiConfigFlags_NavNoCaptureKeyboard);
  m.attr("ImGuiConfigFlags_NoMouse") = static_cast<int>(ImGuiConfigFlags_NoMouse);
  m.attr("ImGuiConfigFlags_NoMouseCursorChange") = static_cast<int>(ImGuiConfigFlags_NoMouseCursorChange);
  m.attr("ImGuiConfigFlags_IsSRGB") = static_cast<int>(ImGuiConfigFlags_IsSRGB);
  m.attr("ImGuiConfigFlags_IsTouchScreen") = static_cast<int>(ImGuiConfigFlags_IsTouchScreen);

  m.attr("ImGuiBackendFlags_None") = static_cast<int>(ImGuiBackendFlags_None);
  m.attr("ImGuiBackendFlags_HasGamepad") = static_cast<int>(ImGuiBackendFlags_HasGamepad);
  m.attr("ImGuiBackendFlags_HasMouseCursors") = static_cast<int>(ImGuiBackendFlags_HasMouseCursors);
  m.attr("ImGuiBackendFlags_HasSetMousePos") = static_cast<int>(ImGuiBackendFlags_HasSetMousePos);
  m.attr("ImGuiBackendFlags_RendererHasVtxOffset") = static_cast<int>(ImGuiBackendFlags_RendererHasVtxOffset);

  m.attr("ImGuiCol_Text") = static_cast<int>(ImGuiCol_Text);
  m.attr("ImGuiCol_TextDisabled") = static_cast<int>(ImGuiCol_TextDisabled);
  m.attr("ImGuiCol_WindowBg") = static_cast<int>(ImGuiCol_WindowBg);
  m.attr("ImGuiCol_ChildBg") = static_cast<int>(ImGuiCol_ChildBg);
  m.attr("ImGuiCol_PopupBg") = static_cast<int>(ImGuiCol_PopupBg);
  m.attr("ImGuiCol_Border") = static_cast<int>(ImGuiCol_Border);
  m.attr("ImGuiCol_BorderShadow") = static_cast<int>(ImGuiCol_BorderShadow);
  m.attr("ImGuiCol_FrameBg") = static_cast<int>(ImGuiCol_FrameBg);
  m.attr("ImGuiCol_FrameBgHovered") = static_cast<int>(ImGuiCol_FrameBgHovered);
  m.attr("ImGuiCol_FrameBgActive") = static_cast<int>(ImGuiCol_FrameBgActive);
  m.attr("ImGuiCol_TitleBg") = static_cast<int>(ImGuiCol_TitleBg);
  m.attr("ImGuiCol_TitleBgActive") = static_cast<int>(ImGuiCol_TitleBgActive);
  m.attr("ImGuiCol_TitleBgCollapsed") = static_cast<int>(ImGuiCol_TitleBgCollapsed);
  m.attr("ImGuiCol_MenuBarBg") = static_cast<int>(ImGuiCol_MenuBarBg);
  m.attr("ImGuiCol_ScrollbarBg") = static_cast<int>(ImGuiCol_ScrollbarBg);
  m.attr("ImGuiCol_ScrollbarGrab") = static_cast<int>(ImGuiCol_ScrollbarGrab);
  m.attr("ImGuiCol_ScrollbarGrabHovered") = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
  m.attr("ImGuiCol_ScrollbarGrabActive") = static_cast<int>(ImGuiCol_ScrollbarGrabActive);
  m.attr("ImGuiCol_CheckMark") = static_cast<int>(ImGuiCol_CheckMark);
  m.attr("ImGuiCol_SliderGrab") = static_cast<int>(ImGuiCol_SliderGrab);
  m.attr("ImGuiCol_ScrollbarGrabHovered") = static_cast<int>(ImGuiCol_ScrollbarGrabHovered);
  m.attr("ImGuiCol_SliderGrabActive") = static_cast<int>(ImGuiCol_SliderGrabActive);
  m.attr("ImGuiCol_Button") = static_cast<int>(ImGuiCol_Button);
  m.attr("ImGuiCol_ButtonHovered") = static_cast<int>(ImGuiCol_ButtonHovered);
  m.attr("ImGuiCol_ButtonActive") = static_cast<int>(ImGuiCol_ButtonActive);
  m.attr("ImGuiCol_Header") = static_cast<int>(ImGuiCol_Header);
  m.attr("ImGuiCol_HeaderHovered") = static_cast<int>(ImGuiCol_HeaderHovered);
  m.attr("ImGuiCol_HeaderActive") = static_cast<int>(ImGuiCol_HeaderActive);
  m.attr("ImGuiCol_Separator") = static_cast<int>(ImGuiCol_Separator);
  m.attr("ImGuiCol_SeparatorHovered") = static_cast<int>(ImGuiCol_SeparatorHovered);
  m.attr("ImGuiCol_SeparatorActive") = static_cast<int>(ImGuiCol_SeparatorActive);
  m.attr("ImGuiCol_ResizeGrip") = static_cast<int>(ImGuiCol_ResizeGrip);
  m.attr("ImGuiCol_ResizeGripHovered") = static_cast<int>(ImGuiCol_ResizeGripHovered);
  m.attr("ImGuiCol_ResizeGripActive") = static_cast<int>(ImGuiCol_ResizeGripActive);
  m.attr("ImGuiCol_TabHovered") = static_cast<int>(ImGuiCol_TabHovered);
  m.attr("ImGuiCol_Tab") = static_cast<int>(ImGuiCol_Tab);
  m.attr("ImGuiCol_TabSelected") = static_cast<int>(ImGuiCol_TabSelected);
  m.attr("ImGuiCol_TabSelectedOverline") = static_cast<int>(ImGuiCol_TabSelectedOverline);
  m.attr("ImGuiCol_TabDimmed") = static_cast<int>(ImGuiCol_TabDimmed);
  m.attr("ImGuiCol_TabDimmedSelected") = static_cast<int>(ImGuiCol_TabDimmedSelected);
  m.attr("ImGuiCol_TabDimmedSelectedOverline") = static_cast<int>(ImGuiCol_TabDimmedSelectedOverline);
  m.attr("ImGuiCol_TabActive") = static_cast<int>(ImGuiCol_TabSelected);  // Deprecated
  m.attr("ImGuiCol_TabUnfocused") = static_cast<int>(ImGuiCol_TabUnfocused);
  m.attr("ImGuiCol_TabUnfocusedActive") = static_cast<int>(ImGuiCol_TabUnfocusedActive);
  m.attr("ImGuiCol_PlotLines") = static_cast<int>(ImGuiCol_PlotLines);
  m.attr("ImGuiCol_PlotLinesHovered") = static_cast<int>(ImGuiCol_PlotLinesHovered);
  m.attr("ImGuiCol_PlotHistogram") = static_cast<int>(ImGuiCol_PlotHistogram);
  m.attr("ImGuiCol_PlotHistogramHovered") = static_cast<int>(ImGuiCol_PlotHistogramHovered);
  m.attr("ImGuiCol_TableHeaderBg") = static_cast<int>(ImGuiCol_TableHeaderBg);
  m.attr("ImGuiCol_TableBorderStrong") = static_cast<int>(ImGuiCol_TableBorderStrong);
  m.attr("ImGuiCol_TableBorderLight") = static_cast<int>(ImGuiCol_TableBorderLight);
  m.attr("ImGuiCol_TableRowBg") = static_cast<int>(ImGuiCol_TableRowBg);
  m.attr("ImGuiCol_TableRowBgAlt") = static_cast<int>(ImGuiCol_TableRowBgAlt);
  m.attr("ImGuiCol_TextLink") = static_cast<int>(ImGuiCol_TextLink);
  m.attr("ImGuiCol_TextSelectedBg") = static_cast<int>(ImGuiCol_TextSelectedBg);
  m.attr("ImGuiCol_DragDropTarget") = static_cast<int>(ImGuiCol_DragDropTarget);
  m.attr("ImGuiCol_NavCursor") = static_cast<int>(ImGuiCol_NavCursor);
  m.attr("ImGuiCol_NavWindowingHighlight") = static_cast<int>(ImGuiCol_NavWindowingHighlight);
  m.attr("ImGuiCol_NavHighlight") = static_cast<int>(ImGuiCol_NavCursor);  // Deprecated
  m.attr("ImGuiCol_NavWindowingDimBg") = static_cast<int>(ImGuiCol_NavWindowingDimBg);
  m.attr("ImGuiCol_ModalWindowDimBg") = static_cast<int>(ImGuiCol_ModalWindowDimBg);
  m.attr("ImGuiCol_COUNT") = static_cast<int>(ImGuiCol_COUNT);

  m.attr("ImGuiStyleVar_Alpha") = static_cast<int>(ImGuiStyleVar_Alpha);
  m.attr("ImGuiStyleVar_WindowPadding") = static_cast<int>(ImGuiStyleVar_WindowPadding);
  m.attr("ImGuiStyleVar_WindowRounding") = static_cast<int>(ImGuiStyleVar_WindowRounding);
  m.attr("ImGuiStyleVar_WindowBorderSize") = static_cast<int>(ImGuiStyleVar_WindowBorderSize);
  m.attr("ImGuiStyleVar_WindowMinSize") = static_cast<int>(ImGuiStyleVar_WindowMinSize);
  m.attr("ImGuiStyleVar_WindowTitleAlign") = static_cast<int>(ImGuiStyleVar_WindowTitleAlign);
  m.attr("ImGuiStyleVar_ChildRounding") = static_cast<int>(ImGuiStyleVar_ChildRounding);
  m.attr("ImGuiStyleVar_ChildBorderSize") = static_cast<int>(ImGuiStyleVar_ChildBorderSize);
  m.attr("ImGuiStyleVar_PopupRounding") = static_cast<int>(ImGuiStyleVar_PopupRounding);
  m.attr("ImGuiStyleVar_PopupBorderSize") = static_cast<int>(ImGuiStyleVar_PopupBorderSize);
  m.attr("ImGuiStyleVar_FramePadding") = static_cast<int>(ImGuiStyleVar_FramePadding);
  m.attr("ImGuiStyleVar_FrameRounding") = static_cast<int>(ImGuiStyleVar_FrameRounding);
  m.attr("ImGuiStyleVar_FrameBorderSize") = static_cast<int>(ImGuiStyleVar_FrameBorderSize);
  m.attr("ImGuiStyleVar_ItemSpacing") = static_cast<int>(ImGuiStyleVar_ItemSpacing);
  m.attr("ImGuiStyleVar_ItemInnerSpacing") = static_cast<int>(ImGuiStyleVar_ItemInnerSpacing);
  m.attr("ImGuiStyleVar_IndentSpacing") = static_cast<int>(ImGuiStyleVar_IndentSpacing);
  m.attr("ImGuiStyleVar_ScrollbarSize") = static_cast<int>(ImGuiStyleVar_ScrollbarSize);
  m.attr("ImGuiStyleVar_ScrollbarRounding") = static_cast<int>(ImGuiStyleVar_ScrollbarRounding);
  m.attr("ImGuiStyleVar_GrabMinSize") = static_cast<int>(ImGuiStyleVar_GrabMinSize);
  m.attr("ImGuiStyleVar_GrabRounding") = static_cast<int>(ImGuiStyleVar_GrabRounding);
  m.attr("ImGuiStyleVar_TabRounding") = static_cast<int>(ImGuiStyleVar_TabRounding);
  m.attr("ImGuiStyleVar_ButtonTextAlign") = static_cast<int>(ImGuiStyleVar_ButtonTextAlign);
  m.attr("ImGuiStyleVar_SelectableTextAlign") = static_cast<int>(ImGuiStyleVar_SelectableTextAlign);
  m.attr("ImGuiStyleVar_COUNT") = static_cast<int>(ImGuiStyleVar_COUNT);

  m.attr("ImGuiColorEditFlags_None") = static_cast<int>(ImGuiColorEditFlags_None);
  m.attr("ImGuiColorEditFlags_NoAlpha") = static_cast<int>(ImGuiColorEditFlags_NoAlpha);
  m.attr("ImGuiColorEditFlags_NoPicker") = static_cast<int>(ImGuiColorEditFlags_NoPicker);
  m.attr("ImGuiColorEditFlags_NoOptions") = static_cast<int>(ImGuiColorEditFlags_NoOptions);
  m.attr("ImGuiColorEditFlags_NoSmallPreview") = static_cast<int>(ImGuiColorEditFlags_NoSmallPreview);
  m.attr("ImGuiColorEditFlags_NoInputs") = static_cast<int>(ImGuiColorEditFlags_NoInputs);
  m.attr("ImGuiColorEditFlags_NoTooltip") = static_cast<int>(ImGuiColorEditFlags_NoTooltip);
  m.attr("ImGuiColorEditFlags_NoLabel") = static_cast<int>(ImGuiColorEditFlags_NoLabel);
  m.attr("ImGuiColorEditFlags_NoSidePreview") = static_cast<int>(ImGuiColorEditFlags_NoSidePreview);
  m.attr("ImGuiColorEditFlags_NoDragDrop") = static_cast<int>(ImGuiColorEditFlags_NoDragDrop);
  m.attr("ImGuiColorEditFlags_NoBorder") = static_cast<int>(ImGuiColorEditFlags_NoBorder);
  m.attr("ImGuiColorEditFlags_AlphaBar") = static_cast<int>(ImGuiColorEditFlags_AlphaBar);
  m.attr("ImGuiColorEditFlags_AlphaPreview") = static_cast<int>(ImGuiColorEditFlags_AlphaPreview);
  m.attr("ImGuiColorEditFlags_AlphaPreviewHalf") = static_cast<int>(ImGuiColorEditFlags_AlphaPreviewHalf);
  m.attr("ImGuiColorEditFlags_HDR") = static_cast<int>(ImGuiColorEditFlags_HDR);
  m.attr("ImGuiColorEditFlags_DisplayRGB") = static_cast<int>(ImGuiColorEditFlags_DisplayRGB);
  m.attr("ImGuiColorEditFlags_DisplayHSV") = static_cast<int>(ImGuiColorEditFlags_DisplayHSV);
  m.attr("ImGuiColorEditFlags_DisplayHex") = static_cast<int>(ImGuiColorEditFlags_DisplayHex);
  m.attr("ImGuiColorEditFlags_Uint8") = static_cast<int>(ImGuiColorEditFlags_Uint8);
  m.attr("ImGuiColorEditFlags_Float") = static_cast<int>(ImGuiColorEditFlags_Float);
  m.attr("ImGuiColorEditFlags_PickerHueBar") = static_cast<int>(ImGuiColorEditFlags_PickerHueBar);
  m.attr("ImGuiColorEditFlags_PickerHueWheel") = static_cast<int>(ImGuiColorEditFlags_PickerHueWheel);
  m.attr("ImGuiColorEditFlags_InputRGB") = static_cast<int>(ImGuiColorEditFlags_InputRGB);
  m.attr("ImGuiColorEditFlags_InputHSV") = static_cast<int>(ImGuiColorEditFlags_InputHSV);

  m.attr("ImGuiMouseButton_Left") = static_cast<int>(ImGuiMouseButton_Left);
  m.attr("ImGuiMouseButton_Right") = static_cast<int>(ImGuiMouseButton_Right);
  m.attr("ImGuiMouseButton_Middle") = static_cast<int>(ImGuiMouseButton_Middle);
  m.attr("ImGuiMouseButton_COUNT") = static_cast<int>(ImGuiMouseButton_COUNT);

  m.attr("ImGuiMouseCursor_None") = static_cast<int>(ImGuiMouseCursor_None);
  m.attr("ImGuiMouseCursor_Arrow") = static_cast<int>(ImGuiMouseCursor_Arrow);
  m.attr("ImGuiMouseCursor_TextInput") = static_cast<int>(ImGuiMouseCursor_TextInput);
  m.attr("ImGuiMouseCursor_ResizeAll") = static_cast<int>(ImGuiMouseCursor_ResizeAll);
  m.attr("ImGuiMouseCursor_ResizeNS") = static_cast<int>(ImGuiMouseCursor_ResizeNS);
  m.attr("ImGuiMouseCursor_ResizeEW") = static_cast<int>(ImGuiMouseCursor_ResizeEW);
  m.attr("ImGuiMouseCursor_ResizeNESW") = static_cast<int>(ImGuiMouseCursor_ResizeNESW);
  m.attr("ImGuiMouseCursor_ResizeNWSE") = static_cast<int>(ImGuiMouseCursor_ResizeNWSE);
  m.attr("ImGuiMouseCursor_Hand") = static_cast<int>(ImGuiMouseCursor_Hand);
  m.attr("ImGuiMouseCursor_NotAllowed") = static_cast<int>(ImGuiMouseCursor_NotAllowed);
  m.attr("ImGuiMouseCursor_COUNT") = static_cast<int>(ImGuiMouseCursor_COUNT);

  m.attr("ImGuiCond_Always") = static_cast<int>(ImGuiCond_Always);
  m.attr("ImGuiCond_Once") = static_cast<int>(ImGuiCond_Once);
  m.attr("ImGuiCond_FirstUseEver") = static_cast<int>(ImGuiCond_FirstUseEver);
  m.attr("ImGuiCond_Appearing") = static_cast<int>(ImGuiCond_Appearing);

  // ImDrawFlags
  m.attr("ImDrawFlags_None") = static_cast<int>(ImDrawFlags_None);
  m.attr("ImDrawFlags_Closed") = static_cast<int>(ImDrawFlags_Closed);
  m.attr("ImDrawFlags_RoundCornersTopLeft") = static_cast<int>(ImDrawFlags_RoundCornersTopLeft);
  m.attr("ImDrawFlags_RoundCornersTopRight") = static_cast<int>(ImDrawFlags_RoundCornersTopRight);
  m.attr("ImDrawFlags_RoundCornersBottomLeft") = static_cast<int>(ImDrawFlags_RoundCornersBottomLeft);
  m.attr("ImDrawFlags_RoundCornersBottomRight") = static_cast<int>(ImDrawFlags_RoundCornersBottomRight);
  m.attr("ImDrawFlags_RoundCornersNone") = static_cast<int>(ImDrawFlags_RoundCornersNone);
  m.attr("ImDrawFlags_RoundCornersTop") = static_cast<int>(ImDrawFlags_RoundCornersTop);
  m.attr("ImDrawFlags_RoundCornersBottom") = static_cast<int>(ImDrawFlags_RoundCornersBottom);
  m.attr("ImDrawFlags_RoundCornersLeft") = static_cast<int>(ImDrawFlags_RoundCornersLeft);
  m.attr("ImDrawFlags_RoundCornersRight") = static_cast<int>(ImDrawFlags_RoundCornersRight);
  m.attr("ImDrawFlags_RoundCornersAll") = static_cast<int>(ImDrawFlags_RoundCornersAll);

}
