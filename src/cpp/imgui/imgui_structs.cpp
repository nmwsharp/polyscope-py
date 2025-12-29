#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>


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

// clang-format on