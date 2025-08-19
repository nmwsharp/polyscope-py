#include "imgui.h"
#include "implot.h"

#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "utils.h"
#include "imgui_utils.h"


void bind_imgui_structs(py::module& m);
void bind_imgui_methods(py::module& m);
void bind_imgui_enums(py::module& m);

void bind_imgui(py::module& m) {
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
void bind_imgui_structs(py::module& m) {

    // ImGuiIO
    py::class_<ImGuiIO>(m, "ImGuiIO")
    .def_readwrite("DisplaySize"                                ,&ImGuiIO::DisplaySize                                        )
    .def_readwrite("DeltaTime"                                  ,&ImGuiIO::DeltaTime                                          ) 
    .def_readwrite("IniSavingRate"                              ,&ImGuiIO::IniSavingRate                                      )     
    .def_readwrite("IniFilename"                                ,&ImGuiIO::IniFilename                                        )   
    .def_readwrite("MouseDoubleClickTime"                       ,&ImGuiIO::MouseDoubleClickTime                               )            
    .def_readwrite("MouseDoubleClickMaxDist"                    ,&ImGuiIO::MouseDoubleClickMaxDist                            )               
    .def_readwrite("MouseDragThreshold"                         ,&ImGuiIO::MouseDragThreshold                                 )          
    .def_readwrite("KeyRepeatDelay"                             ,&ImGuiIO::KeyRepeatDelay                                     )      
    .def_readwrite("KeyRepeatRate"                              ,&ImGuiIO::KeyRepeatRate                                      )     
    .def_readwrite("Fonts"                                      ,&ImGuiIO::Fonts                                              )
    .def_readwrite("FontGlobalScale"                            ,&ImGuiIO::FontGlobalScale                                    )       
    .def_readwrite("FontAllowUserScaling"                       ,&ImGuiIO::FontAllowUserScaling                               )            
    .def_readwrite("FontDefault"                                ,&ImGuiIO::FontDefault                                        )   
    .def_readwrite("DisplayFramebufferScale"                    ,&ImGuiIO::DisplayFramebufferScale                            )               
    .def_readwrite("MouseDrawCursor"                            ,&ImGuiIO::MouseDrawCursor                                    )       
    .def_readwrite("ConfigMacOSXBehaviors"                      ,&ImGuiIO::ConfigMacOSXBehaviors                              )             
    .def_readwrite("ConfigInputTextCursorBlink"                 ,&ImGuiIO::ConfigInputTextCursorBlink                         )                  
    .def_readwrite("ConfigDragClickToInputText"                 ,&ImGuiIO::ConfigDragClickToInputText                         )                  
    .def_readwrite("ConfigWindowsResizeFromEdges"               ,&ImGuiIO::ConfigWindowsResizeFromEdges                       )                    
    .def_readwrite("ConfigWindowsMoveFromTitleBarOnly"          ,&ImGuiIO::ConfigWindowsMoveFromTitleBarOnly                  )                         
    .def_readwrite("ConfigMemoryCompactTimer"                   ,&ImGuiIO::ConfigMemoryCompactTimer                           )                
    .def_property_readonly("MousePos"                           , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return from_vec2(o.MousePos);})
    .def_property_readonly("MouseDown"                          , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDown , ob};})
    .def_readwrite("MouseWheel"                                 ,&ImGuiIO::MouseWheel                                         )  
    .def_readwrite("MouseWheelH"                                ,&ImGuiIO::MouseWheelH                                        )   
    .def_readwrite("KeyCtrl"                                    ,&ImGuiIO::KeyCtrl                                            )  
    .def_readwrite("KeyShift"                                   ,&ImGuiIO::KeyShift                                           ) 
    .def_readwrite("KeyAlt"                                     ,&ImGuiIO::KeyAlt                                             )
    .def_readwrite("KeySuper"                                   ,&ImGuiIO::KeySuper                                           )
    .def_readwrite("WantCaptureMouse"                           ,&ImGuiIO::WantCaptureMouse                                   )        
    .def_readwrite("WantCaptureKeyboard"                        ,&ImGuiIO::WantCaptureKeyboard                                )           
    .def_readwrite("WantTextInput"                              ,&ImGuiIO::WantTextInput                                      )     
    .def_readwrite("WantSetMousePos"                            ,&ImGuiIO::WantSetMousePos                                    )       
    .def_readwrite("WantSaveIniSettings"                        ,&ImGuiIO::WantSaveIniSettings                                )           
    .def_readwrite("NavActive"                                  ,&ImGuiIO::NavActive                                          ) 
    .def_readwrite("NavVisible"                                 ,&ImGuiIO::NavVisible                                         )  
    .def_readwrite("Framerate"                                  ,&ImGuiIO::Framerate                                          ) 
    .def_readwrite("MetricsRenderVertices"                      ,&ImGuiIO::MetricsRenderVertices                              )             
    .def_readwrite("MetricsRenderIndices"                       ,&ImGuiIO::MetricsRenderIndices                               )            
    .def_readwrite("MetricsRenderWindows"                       ,&ImGuiIO::MetricsRenderWindows                               )            
    .def_readwrite("MetricsActiveWindows"                       ,&ImGuiIO::MetricsActiveWindows                               )            
    .def_property_readonly("MouseDelta"                           , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return from_vec2(o.MouseDelta);})
    .def_readwrite("WantCaptureMouseUnlessPopupClose"           ,&ImGuiIO::WantCaptureMouseUnlessPopupClose                   )                        
    .def_readwrite("KeyMods"                                    ,&ImGuiIO::KeyMods                                            ) 
    .def_readwrite("MousePosPrev"                               ,&ImGuiIO::MousePosPrev                                       )    
    .def_property_readonly("MouseClickedPos"                    , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseClickedPos, ob};})
    .def_property_readonly("MouseClickedTime"                   , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseClickedTime, ob};})
    .def_property_readonly("MouseClicked"                       , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseClicked, ob};})
    .def_property_readonly("MouseDoubleClicked"                 , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDoubleClicked, ob};})
    .def_property_readonly("MouseClickedCount"                  , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseClickedCount, ob};})
    .def_property_readonly("MouseClickedLastCount"              , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseClickedLastCount, ob};})
    .def_property_readonly("MouseReleased"                      , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseReleased, ob};})
    .def_property_readonly("MouseDownOwned"                     , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDownOwned, ob};})
    .def_property_readonly("MouseDownOwnedUnlessPopupClose"     , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDownOwnedUnlessPopupClose, ob};})
    .def_property_readonly("MouseDownDuration"                  , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDownDuration, ob};})
    .def_property_readonly("MouseDownDurationPrev"              , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDownDurationPrev, ob};})
    .def_property_readonly("MouseDragMaxDistanceSqr"            , [](py::object& ob) { ImGuiIO& o = ob.cast<ImGuiIO&>(); return py::array{5, o.MouseDragMaxDistanceSqr, ob};})
    .def_readwrite("PenPressure"                                ,&ImGuiIO::PenPressure                                        )   
    .def_readwrite("AppFocusLost"                               ,&ImGuiIO::AppFocusLost                                       )    
    .def_readwrite("InputQueueSurrogate"                        ,&ImGuiIO::InputQueueSurrogate                                )           
    .def_readwrite("InputQueueCharacters"                       ,&ImGuiIO::InputQueueCharacters                               )            

    ;


    py::class_<ImFontAtlas>(m, "ImFontAtlas")
      .def("AddFontFromFileTTF",
          [](py::object& ob, std::string filename, float size_pixels) { ImFontAtlas& o = ob.cast<ImFontAtlas&>(); return o.AddFontFromFileTTF(filename.c_str(), size_pixels);}, 
          py::return_value_policy::reference)

      // TODO add bindings to the rest of the font functions
      
      ;

    py::class_<ImFont>(m, "ImFont")

      // TODO add bindings to the rest of the font functions
      
      ;

}

void bind_imgui_methods(py::module& m) {

    // Main
    m.def("GetIO", &ImGui::GetIO, py::return_value_policy::reference);

    // Windows
    m.def(
        "Begin",
        [](const char* name, bool open, ImGuiWindowFlags flags) {
            const auto clicked = ImGui::Begin(name, &open, flags);
            return std::make_tuple(clicked, open);
        },
        py::arg("name"),
        py::arg("open"),
        py::arg("flags") = 0);
    m.def("End", []() { ImGui::End(); });

    // Child Windows
    m.def(
        "BeginChild",
        [](const char* str_id, const Vec2T& size, bool border, ImGuiWindowFlags flags) {
            return ImGui::BeginChild(str_id, to_vec2(size), border, flags);
        },
        py::arg("str_id"),
        py::arg("size") = std::make_tuple(0.f, 0.f),
        py::arg("border") = false,
        py::arg("flags") = 0);
    m.def(
        "BeginChild",
        [](ImGuiID id, const Vec2T& size, bool border, ImGuiWindowFlags flags) {
            return ImGui::BeginChild(id, to_vec2(size), border, flags);
        },
        py::arg("id"),
        py::arg("size") = std::make_tuple(0.f, 0.f),
        py::arg("border") = false,
        py::arg("flags") = 0);
    m.def("EndChild", []() { ImGui::EndChild(); });

    // Windows Utilities
    m.def("IsWindowAppearing", []() { return ImGui::IsWindowAppearing(); });
    m.def("IsWindowCollapsed", []() { return ImGui::IsWindowCollapsed(); });
    m.def(
        "IsWindowFocused",
        [](ImGuiFocusedFlags flags) { return ImGui::IsWindowFocused(flags); },
        py::arg("flags") = 0);
    m.def(
        "IsWindowHovered",
        [](ImGuiFocusedFlags flags) { return ImGui::IsWindowHovered(flags); },
        py::arg("flags") = 0);
    m.def("GetWindowDrawList", []() { return ImGui::GetWindowDrawList(); }, py::return_value_policy::reference);
    m.def("GetWindowPos", []() { return from_vec2(ImGui::GetWindowPos()); });
    m.def("GetWindowSize", []() { return from_vec2(ImGui::GetWindowSize()); });
    m.def("GetWindowWidth", []() { return ImGui::GetWindowWidth(); });
    m.def("GetWindowHeight", []() { return ImGui::GetWindowHeight(); });
    m.def(
        "SetNextWindowPos",
        [](const Vec2T& pos, ImGuiCond cond, const Vec2T& pivot) {
            ImGui::SetNextWindowPos(to_vec2(pos), cond, to_vec2(pivot));
        },
        py::arg("pos"),
        py::arg("cond") = 0,
        py::arg("pivot") = std::make_tuple(0., 0.));
    m.def(
        "SetNextWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetNextWindowSize(to_vec2(size), cond); },
        py::arg("size"),
        py::arg("cond") = 0);
    m.def(
        "SetNextWindowSizeConstraints",
        [](const Vec2T& size_min, const Vec2T& size_max) {
            ImGui::SetNextWindowSizeConstraints(to_vec2(size_min), to_vec2(size_max));
        },
        py::arg("size_min"),
        py::arg("size_max"));
    m.def(
        "SetNextWindowContextSize",
        [](const Vec2T& size) { ImGui::SetNextWindowContentSize(to_vec2(size)); },
        py::arg("size"));
    m.def(
        "SetNextWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetNextWindowCollapsed(collapsed, cond); },
        py::arg("collapsed"),
        py::arg("cond") = 0);
    m.def("SetNextWindowFocus", []() { ImGui::SetNextWindowFocus(); });
    m.def("SetNextWindowBgAlpha", [](float alpha) { ImGui::SetNextWindowBgAlpha(alpha); });
    m.def(
        "SetWindowPos",
        [](const Vec2T& pos, ImGuiCond cond) { ImGui::SetWindowPos(to_vec2(pos), cond); },
        py::arg("pos"),
        py::arg("cond") = 0);
    m.def(
        "SetWindowSize",
        [](const Vec2T& size, ImGuiCond cond) { ImGui::SetWindowSize(to_vec2(size), cond); },
        py::arg("size"),
        py::arg("cond") = 0);
    m.def(
        "SetWindowCollapsed",
        [](bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(collapsed, cond); },
        py::arg("collapsed"),
        py::arg("cond") = 0);
    m.def("set_window_focus", []() { ImGui::SetWindowFocus(); });
    m.def(
        "SetWindowFontScale",
        [](float scale) { ImGui::SetWindowFontScale(scale); },
        py::arg("scale"));
    m.def(
        "SetWindowPos",
        [](const char* name, const Vec2T& pos, ImGuiCond cond) {
            ImGui::SetWindowPos(name, to_vec2(pos), cond);
        },
        py::arg("name"),
        py::arg("pos"),
        py::arg("cond") = 0);
    m.def(
        "SetWindowSize",
        [](const char* name, const Vec2T& size, ImGuiCond cond) {
            ImGui::SetWindowSize(name, to_vec2(size), cond);
        },
        py::arg("name"),
        py::arg("size"),
        py::arg("cond") = 0);
    m.def(
        "SetWindowCollapsed",
        [](const char* name, bool collapsed, ImGuiCond cond) {
            ImGui::SetWindowCollapsed(name, collapsed, cond);
        },
        py::arg("name"),
        py::arg("collapsed"),
        py::arg("cond") = 0);
    m.def(
        "SetWindowFocus", [](const char* name) { ImGui::SetWindowFocus(name); }, py::arg("name"));

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
        py::arg("scroll_x"));
    m.def(
        "SetScrollY",
        [](float scroll_y) { ImGui::SetScrollY(scroll_y); },
        py::arg("scroll_y"));
    m.def(
        "SetScrollHereX",
        [](float center_x_ratio) { ImGui::SetScrollHereX(center_x_ratio); },
        py::arg("center_x_ratio") = 0.5f);
    m.def(
        "SetScrollHereY",
        [](float center_y_ratio) { ImGui::SetScrollHereY(center_y_ratio); },
        py::arg("center_y_ratio") = 0.5f);
    m.def(
        "SetScrollFromPosX",
        [](float local_x, float center_x_ratio) { ImGui::SetScrollFromPosX(local_x, center_x_ratio); },
        py::arg("local_x"),
        py::arg("center_x_ratio") = 0.5f);
    m.def(
        "SetScrollFromPosY",
        [](float local_y, float center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); },
        py::arg("local_y"),
        py::arg("center_y_ratio") = 0.5f);

    // Parameters stacks (shared)
    IMGUI_API void          PushFont(ImFont* font);                                         // use NULL as a shortcut to push default font
    IMGUI_API void          PopFont();
    m.def(
        "PushFont",
        [](ImFont* font) { ImGui::PushFont(font); },
        py::arg("font"));
    m.def(
        "PopFont",
        []() { ImGui::PopFont(); }
        );
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); },
        py::arg("idx"),
        py::arg("col"));
    m.def(
        "PushStyleColor",
        [](ImGuiCol idx, const Vec4T& col) { ImGui::PushStyleColor(idx, to_vec4(col)); },
        py::arg("idx"),
        py::arg("col"));
    m.def(
        "PopStyleColor", [](int count) { ImGui::PopStyleColor(count); }, py::arg("count") = 1);
    m.def(
        "PushStyleVar",
        [](ImGuiCol idx, float val) { ImGui::PushStyleVar(idx, val); },
        py::arg("idx"),
        py::arg("val"));
    m.def(
        "PushStyleVar",
        [](ImGuiCol idx, const Vec2T& val) { ImGui::PushStyleVar(idx, to_vec2(val)); },
        py::arg("idx"),
        py::arg("val"));
    m.def(
        "PopStyleVar", [](int count) { ImGui::PopStyleVar(count); }, py::arg("count") = 1);
    m.def(
        "GetStyleColorVec4",
        [](ImGuiCol idx) { return from_vec4(ImGui::GetStyleColorVec4(idx)); },
        py::arg("idx"));
    m.def("GetFontSize", []() { return ImGui::GetFontSize(); });
    m.def("GetFontTexUvWhitePixel",
            []() { return from_vec2(ImGui::GetFontTexUvWhitePixel()); });
    m.def(
        "GetColorU32",
        [](ImGuiCol idx, float alpha_mul) { return ImGui::GetColorU32(idx, alpha_mul); },
        py::arg("idx"),
        py::arg("alpha_mul") = 1.0f);
    m.def(
        "GetColorU32", [](const Vec4T& col) { return ImGui::GetColorU32(to_vec4(col)); }, py::arg("col"));
    m.def(
        "GetColorU32", [](ImU32 col) { return ImGui::GetColorU32(col); }, py::arg("col"));

    // Parameters stacks (current window)
    m.def(
        "PushItemWidth",
        [](float item_width) { return ImGui::PushItemWidth(item_width); },
        py::arg("item_width"));
    m.def("PopItemWidth", []() { ImGui::PopItemWidth(); });
    m.def(
        "SetNextItemWidth",
        [](float item_width) { return ImGui::SetNextItemWidth(item_width); },
        py::arg("item_width"));
    m.def("CalcItemWidth", []() { return ImGui::CalcItemWidth(); });
    m.def(
        "PushTextWrapPos",
        [](float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); },
        py::arg("wrap_local_pos_x") = 0.0f);
    m.def("PopTextWrapPos", []() { ImGui::PopTextWrapPos(); });
    m.def(
        "PushAllowKeyboardFocus",
        [](bool allow_keyboard_focus) { ImGui::PushAllowKeyboardFocus(allow_keyboard_focus); },
        py::arg("allow_keyboard_focus"));
    m.def("PopAllowKeyboardFocus", []() { ImGui::PopAllowKeyboardFocus(); });
    m.def(
        "PushButtonRepeat",
        [](bool repeat) { ImGui::PushButtonRepeat(repeat); },
        py::arg("allow_keyboard_focus"));
    m.def("PopButtonRepeat", []() { ImGui::PopButtonRepeat(); });

    // Cursor / Layout
    m.def("Separator", []() { ImGui::Separator(); });
    m.def(
        "SameLine",
        [](float offset_from_start_x, float spacing) { ImGui::SameLine(); },
        py::arg("offset_from_start_x") = 0.0f,
        py::arg("offset") = -1.0f);
    m.def("NewLine", []() { ImGui::NewLine(); });
    m.def("Spacing", []() { ImGui::Spacing(); });
    m.def("Dummy", [](const Vec2T& size) { ImGui::Dummy(to_vec2(size)); });
    m.def(
        "Indent", [](float indent_w) { ImGui::Indent(indent_w); }, py::arg("indent_w") = 0.f);
    m.def(
        "Unindent", [](float indent_w) { ImGui::Unindent(indent_w); }, py::arg("indent_w") = 0.f);
    m.def("BeginGroup", []() { ImGui::BeginGroup(); });
    m.def("EndGroup", []() { ImGui::EndGroup(); });
    m.def("GetCursorPos", []() { return from_vec2(ImGui::GetCursorPos()); });
    m.def("GetCursorPosX", []() { return ImGui::GetCursorPosX(); });
    m.def("GetCursorPosY", []() { return ImGui::GetCursorPosY(); });
    m.def(
        "SetCursorPos",
        [](const Vec2T& local_pos) { ImGui::SetCursorPos(to_vec2(local_pos)); },
        py::arg("local_pos"));
    m.def(
        "SetCursorPosX",
        [](float local_x) { ImGui::SetCursorPosX(local_x); },
        py::arg("local_x"));
    m.def(
        "SetCursorPosY",
        [](float local_y) { ImGui::SetCursorPosY(local_y); },
        py::arg("local_y"));
    m.def("GetCursorStartPos", []() { return from_vec2(ImGui::GetCursorStartPos()); });
    m.def("GetCursorScreenPos", []() { return from_vec2(ImGui::GetCursorScreenPos()); });
    m.def(
        "SetCursorScreenPos",
        [](const Vec2T& pos) { ImGui::SetCursorScreenPos(to_vec2(pos)); },
        py::arg("pos"));
    m.def("AlignTextToFramePadding", []() { ImGui::AlignTextToFramePadding(); });
    m.def("GetTextLineHeight", []() { return ImGui::GetTextLineHeight(); });
    m.def("GetTextLineHeightWithSpacing", []() { return ImGui::GetTextLineHeightWithSpacing(); });
    m.def("GetFrameHeight", []() { return ImGui::GetFrameHeight(); });
    m.def("GetFrameHeightWithSpacing", []() { return ImGui::GetFrameHeightWithSpacing(); });

    // ID stack/scopes
    m.def(
        "PushID", [](const char* str_id) { ImGui::PushID(str_id); }, py::arg("str_id"));
    m.def(
        "PushID", [](int int_id) { ImGui::PushID(int_id); }, py::arg("int_id"));
    m.def("PopID", []() { ImGui::PopID(); });
    m.def(
        "GetID", [](const char* str_id) { return ImGui::GetID(str_id); }, py::arg("str_id"));
    
    // these are typos (bad capitalization). kept around to avoid needless breaking changes
    m.def(
        "PushId", [](const char* str_id) { ImGui::PushID(str_id); }, py::arg("str_id"));
    m.def(
        "PushId", [](int int_id) { ImGui::PushID(int_id); }, py::arg("int_id"));
    m.def(
        "GetId", [](const char* str_id) { return ImGui::GetID(str_id); }, py::arg("str_id"));

    // Widgets: Text
    m.def(
        "TextUnformatted", [](const char* text) { ImGui::TextUnformatted(text); }, py::arg("text"));
    m.def(
        "Text", [](const char* text) { ImGui::Text("%s", text); }, py::arg("text"));
    m.def(
        "TextColored",
        [](const Vec4T& color, const char* text) { ImGui::TextColored(to_vec4(color), "%s", text); },
        py::arg("color"),
        py::arg("text"));
    m.def(
        "TextDisabled", [](const char* text) { ImGui::TextDisabled("%s", text); }, py::arg("text"));
    m.def(
        "TextWrapped", [](const char* text) { ImGui::TextWrapped("%s", text); }, py::arg("text"));
    m.def(
        "LabelText",
        [](const char* label, const char* text) { ImGui::LabelText(label, "%s", text); },
        py::arg("label"),
        py::arg("text"));
    m.def(
        "BulletText",
        [](const char* fmt) { ImGui::BulletText("%s", fmt); },
        py::arg("text"));

    // Widgets: Main
    m.def(
        "Button",
        [](const char* label, const Vec2T& size) { return ImGui::Button(label, to_vec2(size)); },
        py::arg("label"),
        py::arg("size") = std::make_tuple(0.f, 0.f));
    m.def(
        "SmallButton",
        [](const char* label) { return ImGui::SmallButton(label); },
        py::arg("label"));
    m.def(
        "InvisibleButton",
        [](const char* str_id, const Vec2T& size) {
            return ImGui::InvisibleButton(str_id, to_vec2(size));
        },
        py::arg("str_id"),
        py::arg("size"));
    m.def(
        "ArrowButton",
        [](const char* str_id, ImGuiDir dir) { return ImGui::ArrowButton(str_id, dir); },
        py::arg("str_id"),
        py::arg("dir"));
    m.def(
        "Checkbox",
        [](const char* label, bool v) {
            const auto clicked = ImGui::Checkbox(label, &v);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"));
    m.def(
        "CheckboxFlags",
        [](const char* label, unsigned int flags, unsigned int flags_value) {
            const auto clicked = ImGui::CheckboxFlags(label, &flags, flags_value);
            return std::make_tuple(clicked, flags);
        },
        py::arg("label"),
        py::arg("flags"),
        py::arg("flags_value"));
    m.def(
        "RadioButton",
        [](const char* label, bool active) { return ImGui::RadioButton(label, active); },
        py::arg("label"),
        py::arg("active"));
    m.def(
        "RadioButton",
        [](const char* label, int v, int v_button) {
            const auto clicked = ImGui::RadioButton(label, &v, v_button);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_button"));
    m.def(
        "ProgressBar",
        [](float fraction, const Vec2T& size_arg) {
            ImGui::ProgressBar(fraction, to_vec2(size_arg));
        },
        py::arg("fraction"),
        py::arg("size_arg") = std::make_tuple(-1.f, 0.f));
    m.def("Bullet", []() { ImGui::Bullet(); });

    // Widgets: Combo Box
    m.def(
        "BeginCombo",
        [](const char* label, const char* preview_value, ImGuiComboFlags flags) {
            return ImGui::BeginCombo(label, preview_value, flags);
        },
        py::arg("label"),
        py::arg("preview_value"),
        py::arg("flags") = 0);
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
        py::arg("label"),
        py::arg("current_item"),
        py::arg("items"),
        py::arg("popup_max_height_in_items") = -1);
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
        py::arg("label"),
        py::arg("current_item"),
        py::arg("items_separated_by_zeros"),
        py::arg("popup_max_height_in_items") = -1);

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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v_current_min"),
        py::arg("v_current_max"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("format_max") = nullptr,
        py::arg("power") = 1.0f);

    m.def(
        "DragInt",
        [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format) {
            auto clicked = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v_current_min"),
        py::arg("v_current_max"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d",
        py::arg("format_max") = nullptr);

    // Widgets: Sliders
    m.def(
        "SliderFloat",
        [](const char* label, float v, float v_min, float v_max, const char* format, float power) {
            auto clicked = ImGui::SliderFloat(label, &v, v_min, v_max, format, power);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min"),
        py::arg("v_max"),
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);

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
        py::arg("label"),
        py::arg("v_rad"),
        py::arg("v_degrees_min") = -360.0f,
        py::arg("v_degrees_max") = +360.0f,
        py::arg("format") = "%.0f deg");

    m.def(
        "SliderInt",
        [](const char* label, int v, int v_min, int v_max, const char* format) {
            auto v_ = v;
            auto clicked = ImGui::SliderInt(label, &v_, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");
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
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0,
        py::arg("v_max") = 0,
        py::arg("format") = "%d");

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
        py::arg("label"),
        py::arg("buf"),
        py::arg("flags") = 0);
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
        py::arg("label"),
        py::arg("buf"),
        py::arg("size") = std::make_tuple(0.f, 0.f),
        py::arg("flags") = 0);
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
        py::arg("label"),
        py::arg("hint"),
        py::arg("buf"),
        py::arg("flags") = 0);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("step") = 0.f,
        py::arg("step_fast") = 0.f,
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputFloat2",
        [](const char* label,
            std::array<float, 2> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat2(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputFloat3",
        [](const char* label,
            std::array<float, 3> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat3(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputFloat4",
        [](const char* label,
            std::array<float, 4> v,
            const char* format,
            ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputFloat4(label, v.data(), format, flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputInt",
        [](const char* label, int v, float step, float step_fast, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt(label, &v, step, step_fast, flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("step") = 0.f,
        py::arg("step_fast") = 0.f,
        py::arg("flags") = 0);
    m.def(
        "InputInt2",
        [](const char* label, std::array<int, 2> v, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt2(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("flags") = 0);
    m.def(
        "InputInt3",
        [](const char* label, std::array<int, 3> v, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt3(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("flags") = 0);
    m.def(
        "InputInt4",
        [](const char* label, std::array<int, 4> v, ImGuiInputTextFlags flags) {
            const auto clicked = ImGui::InputInt4(label, v.data(), flags);
            return std::make_tuple(clicked, v);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("flags") = 0);
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
        py::arg("label"),
        py::arg("v"),
        py::arg("step") = 0.f,
        py::arg("step_fast") = 0.f,
        py::arg("format") = "%.6f",
        py::arg("flags") = 0);

    // Widgets: Color Editor/Picker
    m.def(
        "ColorEdit3",
        [](const char* label, const std::array<float, 3>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorEdit3(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        py::arg("label"),
        py::arg("def"),
        py::arg("flags") = 0);
    m.def(
        "ColorEdit4",
        [](const char* label, const std::array<float, 4>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorEdit4(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        py::arg("label"),
        py::arg("def"),
        py::arg("flags") = 0);
    m.def(
        "ColorPicker3",
        [](const char* label, const std::array<float, 3>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorPicker3(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        py::arg("label"),
        py::arg("def"),
        py::arg("flags") = 0);
    m.def(
        "ColorPicker4",
        [](const char* label, const std::array<float, 4>& col, ImGuiColorEditFlags flags) {
            auto col_ = col;
            const auto clicked = ImGui::ColorPicker4(label, col_.data(), flags);
            return std::make_tuple(clicked, col_);
        },
        py::arg("label"),
        py::arg("def"),
        py::arg("flags") = 0);
    m.def(
        "ColorButton",
        [](const char* label, const Vec4T& col, ImGuiColorEditFlags flags, const Vec2T& size) {
            auto col_ = col;
            const auto clicked = ImGui::ColorButton(label, to_vec4(col), flags, to_vec2(size));
            return std::make_tuple(clicked, col_);
        },
        py::arg("label"),
        py::arg("def"),
        py::arg("flags") = 0,
        py::arg("size") = std::make_tuple(0.f, 0.f));
    m.def(
        "SetColorEditOptions",
        [](ImGuiColorEditFlags flags) { ImGui::SetColorEditOptions(flags); },
        py::arg("flags"));

    // Widgets: Trees
    m.def(
        "TreeNode", [](const char* label) { return ImGui::TreeNode(label); }, py::arg("label"));
    m.def(
        "TreeNodeEx",
        [](const char* label, ImGuiTreeNodeFlags flags) { return ImGui::TreeNodeEx(label, flags); },
        py::arg("label"),
        py::arg("flags") = 0);
    m.def(
        "TreePush", [](const char* str_id) { ImGui::TreePush(str_id); }, py::arg("str_id"));
    m.def("TreePop", []() { ImGui::TreePop(); });
    m.def("GetTreeNodeToLabelSpacing", []() { return ImGui::GetTreeNodeToLabelSpacing(); });
    m.def(
        "CollapsingHeader",
        [](const char* label, ImGuiTreeNodeFlags flags) {
            return ImGui::CollapsingHeader(label, flags);
        },
        py::arg("label"),
        py::arg("flags") = 0);
    m.def(
        "CollapsingHeader",
        [](const char* label, bool open, ImGuiTreeNodeFlags flags) {
            const auto clicked = ImGui::CollapsingHeader(label, &open, flags);
            return std::make_tuple(clicked, open);
        },
        py::arg("label"),
        py::arg("open"),
        py::arg("flags") = 0);
    m.def(
        "SetNextItemOpen",
        [](bool is_open, ImGuiCond cond) { ImGui::SetNextItemOpen(is_open, cond); },
        py::arg("is_open"),
        py::arg("cond") = 0);

    // Widgets: Selectables
    m.def(
        "Selectable",
        [](const char* label, bool selected, ImGuiSelectableFlags flags, const Vec2T& size) {
            const auto clicked = ImGui::Selectable(label, &selected, flags, to_vec2(size));
            return std::make_tuple(clicked, selected);
        },
        py::arg("label"),
        py::arg("selected") = false,
        py::arg("flags") = 0,
        py::arg("size") = std::make_tuple(0.f, 0.f));

    // Widgets: List Boxes
    m.def(
        "BeginListBox",
        [](const char* label,
            const Vec2T& size
          ) {
            return ImGui::BeginListBox(label, to_vec2(size));
        },
        py::arg("label"),
        py::arg("size") = Vec2T(0,0));
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
        py::arg("label"),
        py::arg("current_item"),
        py::arg("items"),
        py::arg("height_in_items") = -1);

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
        py::arg("label"),
        py::arg("values"),
        py::arg("values_offset") = 0,
        py::arg("overlay_text") = nullptr,
        py::arg("scale_min") = FLT_MAX,
        py::arg("scale_max") = FLT_MAX,
        py::arg("graph_size") = std::make_tuple(0.f, 0.f)
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
        py::arg("label"),
        py::arg("values"),
        py::arg("values_offset") = 0,
        py::arg("overlay_text") = nullptr,
        py::arg("scale_min") = FLT_MAX,
        py::arg("scale_max") = FLT_MAX,
        py::arg("graph_size") = std::make_tuple(0.f, 0.f)
    );

    // Widgets: Value() Helpers.
    m.def("Value", [](const char *prefix, bool b){ ImGui::Value(prefix, b); }, py::arg("prefix"), py::arg("b"));
    m.def("Value", [](const char *prefix, int v){ ImGui::Value(prefix, v); }, py::arg("prefix"), py::arg("v"));
    m.def(
        "Value",
        [](const char *prefix, float v, const char * float_format) {
            ImGui::Value(prefix, v, float_format);
        },
        py::arg("prefix"),
        py::arg("b"),
        py::arg("float_format") = nullptr
    );

    // Widgets: Menus
    m.def("BeginMenuBar", []() { return ImGui::BeginMenuBar(); });
    m.def("EndMenuBar", []() { ImGui::EndMenuBar(); });
    m.def("BeginMainMenuBar", []() { return ImGui::BeginMainMenuBar(); });
    m.def("EndMainMenuBar", []() { return ImGui::EndMainMenuBar(); });
    m.def(
        "BeginMenu",
        [](const char* label, bool enabled) { return ImGui::BeginMenu(label, enabled); },
        py::arg("label"),
        py::arg("enabled") = true);
    m.def("EndMenu", []() { ImGui::EndMenu(); });
    m.def(
        "MenuItem",
        [](const char* label, const char* shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label, shortcut, selected, enabled);
        },
        py::arg("label"),
        py::arg("shortcut") = nullptr,
        py::arg("selected") = false,
        py::arg("enabled") = true);

    // Tooltips
    m.def("BeginTooltip", []() { ImGui::BeginTooltip(); });
    m.def("EndTooltip", []() { ImGui::EndTooltip(); });
    m.def("SetTooltip", [](const char *value) { ImGui::SetTooltip("%s", value); });

    // Popups, Modals
    m.def(
        "OpenPopup", [](const char* str_id) { ImGui::OpenPopup(str_id); }, py::arg("str_id"));
    m.def(
        "BeginPopup",
        [](const char* str_id, ImGuiWindowFlags flags) { return ImGui::BeginPopup(str_id, flags); },
        py::arg("str_id"),
        py::arg("flags") = 0);
    m.def(
        "BeginPopupContextItem",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextItem(str_id, popup_flags);
        },
        py::arg("str_id"),
        py::arg("popup_flags") = 1);
    m.def(
        "BeginPopupContextWindow",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextWindow(str_id, popup_flags);
        },
        py::arg("str_id"),
        py::arg("popup_flags") = 1);
    m.def(
        "BeginPopupContextVoid",
        [](const char* str_id, ImGuiPopupFlags popup_flags) {
            return ImGui::BeginPopupContextVoid(str_id, popup_flags);
        },
        py::arg("str_id"),
        py::arg("popup_flags") = 1);
    m.def(
        "BeginPopupModal",
        [](const char* str_id, bool open, ImGuiWindowFlags flags) {
            auto open_ = open;
            return ImGui::BeginPopupModal(str_id, &open_, flags);
        },
        py::arg("str_id"),
        py::arg("open"),
        py::arg("flags") = 0);
    m.def("EndPopup", []() { ImGui::EndPopup(); });
    m.def(
        "OpenPopupOnItemClick",
        [](const char* str_id, ImGuiWindowFlags popup_flags) {
            return ImGui::OpenPopupOnItemClick(str_id, popup_flags);
        },
        py::arg("str_id"),
        py::arg("popup_flags") = 1);
    m.def(
        "IsPopupOpen",
        [](const char* str_id, ImGuiPopupFlags popup_flags) { return ImGui::IsPopupOpen(str_id, popup_flags); },
        py::arg("str_id"),
        py::arg("flags") = 0);
    m.def("CloseCurrentPopup", []() { ImGui::CloseCurrentPopup(); });

    // Columns
    m.def(
        "Columns",
        [](int count, const char *id, bool border) {
            ImGui::Columns(count, id, border);
        },
        py::arg("count") = 1,
        py::arg("id") = nullptr,
        py::arg("border") = true
    );
    m.def("NextColumn", []() { ImGui::NextColumn(); });
    m.def("GetColumnIndex", []() { return ImGui::GetColumnIndex(); });
    m.def(
        "GetColumnWidth",
        [](int column_index) {
            return ImGui::GetColumnWidth(column_index);
        },
        py::arg("column_index") = -1
    );
    m.def(
        "SetColumnWidth",
        [](int column_index, float width) {
            ImGui::SetColumnWidth(column_index, width);
        },
        py::arg("column_index"),
        py::arg("width")
    );
    m.def(
        "GetColumnOffset",
        [](int column_index) {
            return ImGui::GetColumnOffset(column_index);
        },
        py::arg("column_index") = -1
    );
    m.def(
        "SetColumnOffset",
        [](int column_index, float width) {
            ImGui::SetColumnOffset(column_index, width);
        },
        py::arg("column_index"),
        py::arg("offset_x")
    );
    m.def("GetColumnsCount", []() { return ImGui::GetColumnsCount(); });

    // Tab Bars, Tabs
    m.def(
        "BeginTabBar",
        [](const char *str_id, ImGuiTabBarFlags flags) {
            return ImGui::BeginTabBar(str_id, flags);
        },
        py::arg("str_id"),
        py::arg("flags") = 0
    );
    m.def("EndTabBar", []() { ImGui::EndTabBar(); });
    m.def(
        "BeginTabItem",
        [](const char *str, bool open, ImGuiTabBarFlags flags) {
            const auto clicked = ImGui::BeginTabItem(str, &open, flags);
            return std::make_tuple(clicked, open);
        },
        py::arg("str"),
        py::arg("open"),
        py::arg("flags") = 0
    );
    m.def("EndTabItem", []() { ImGui::EndTabItem(); });
    m.def(
        "SetTabItemClosed",
        [](const char *tab_or_docked_window_label) {
            ImGui::SetTabItemClosed(tab_or_docked_window_label);
        },
        py::arg("tab_or_docked_window_label")
    );

    // Logging/Capture
    m.def(
        "LogToTTY",
        [](int auto_open_depth) {
            ImGui::LogToTTY(auto_open_depth);
        },
        py::arg("auto_open_depth") = -1
    );
    m.def(
        "LogToFile",
        [](int auto_open_depth, const char *filename) {
            ImGui::LogToFile(auto_open_depth, filename);
        },
        py::arg("auto_open_depth") = -1,
        py::arg("filename") = nullptr
    );
    m.def(
        "LogToClipboard",
        [](int auto_open_depth) {
            ImGui::LogToClipboard(auto_open_depth);
        },
        py::arg("auto_open_depth") = -1
    );
    m.def("LogFinish", []() { ImGui::LogFinish(); });
    m.def("LogButtons", []() { ImGui::LogButtons(); });

    // Disabling
    m.def("BeginDisabled", 
        [](bool disable) { 
          return ImGui::BeginDisabled(disable);
        }, py::arg("disable"));
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
        py::arg("clip_rect_min"),
        py::arg("clip_rect_max"),
        py::arg("intersect_with_current_clip_rect")
    );
    m.def("PopClipRect", []() { ImGui::PopClipRect(); });

    // Focus, Activation
    m.def("SetItemDefaultFocus", []() { ImGui::SetItemDefaultFocus(); });
    m.def(
        "SetKeyboardFocusHere",
        [](int offset) { ImGui::SetKeyboardFocusHere(offset); },
        py::arg("offset")
    );

    // Item/Widgets Utilities
    m.def(
        "IsItemHovered",
        [](ImGuiHoveredFlags flags) { return ImGui::IsItemHovered(flags); },
        py::arg("flags") = 0);
    m.def("IsItemActive", []() { return ImGui::IsItemActive(); });
    m.def("IsItemFocused", []() { return ImGui::IsItemFocused(); });
    m.def(
        "IsItemClicked",
        [](ImGuiMouseButton mouse_button) { return ImGui::IsItemClicked(mouse_button); },
        py::arg("mouse_button") = 0);
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
    m.def("GetBackgroundDrawList", &ImGui::GetBackgroundDrawList, py::return_value_policy::reference);
    m.def("GetForegroundDrawList", &ImGui::GetForegroundDrawList, py::return_value_policy::reference);

    // Miscellaneous Utilities
    m.def(
        "IsRectVisible",
        [](const Vec2T& size) {
            return ImGui::IsRectVisible(to_vec2(size));
        },
        py::arg("size")
    );
    m.def(
        "IsRectVisible",
        [](const Vec2T& rect_min, const Vec2T& rect_max) {
            return ImGui::IsRectVisible(to_vec2(rect_min), to_vec2(rect_max));
        },
        py::arg("rect_min"),
        py::arg("rect_max")
    );
    m.def("GetTime", []() { return ImGui::GetTime(); });
    m.def("GetFrameCount", []() { return ImGui::GetFrameCount(); });
    m.def("GetStyleColorName", [](ImGuiCol idx) { return ImGui::GetStyleColorName(idx); });
    m.def(
        "BeginChildFrame",
        [](ImGuiID id, const Vec2T& size, ImGuiWindowFlags flags) {
            return ImGui::BeginChildFrame(id, to_vec2(size), flags);
        },
        py::arg("id"),
        py::arg("size"),
        py::arg("flags") = 0
    );
    m.def("EndChildFrame", []() { ImGui::EndChildFrame(); });

    // Text Utilities
    m.def(
        "CalcTextSize",
        [](const char *text, const char *text_end, bool hide_text_after_double_hash, float wrap_width) {
            return from_vec2(ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width));
        },
        py::arg("text"),
        py::arg("text_end") = nullptr,
        py::arg("hide_text_after_double_hash") = false,
        py::arg("wrap_width") = -1.f
    );

    // Utilities: Mouse
    m.def("IsMouseDown", [](ImGuiMouseButton button) { return ImGui::IsMouseDown(button); }, py::arg("button"));
    m.def(
        "IsMouseClicked",
        [](ImGuiMouseButton button, bool repeat) { return ImGui::IsMouseClicked(button, repeat); },
        py::arg("button"),
        py::arg("repeat") = false
    );
    m.def("IsMouseReleased", [](ImGuiMouseButton button) { return ImGui::IsMouseReleased(button); }, py::arg("button"));
    m.def("IsMouseDoubleClicked", [](ImGuiMouseButton button) { return ImGui::IsMouseDoubleClicked(button); }, py::arg("button"));
    m.def(
        "IsMouseHoveringRect",
        [](const Vec2T& r_min, const Vec2T& r_max, bool clip) {
            return ImGui::IsMouseHoveringRect(to_vec2(r_min), to_vec2(r_max), clip);
        },
        py::arg("r_min"),
        py::arg("r_max"),
        py::arg("clip") = true
    );
    m.def("IsAnyMouseDown", []() { return ImGui::IsAnyMouseDown(); });
    m.def("GetMousePos", []() { return from_vec2(ImGui::GetMousePos()); });
    m.def("GetMousePosOnOpeningCurrentPopup", []() { return from_vec2(ImGui::GetMousePosOnOpeningCurrentPopup()); });
    m.def(
        "IsMouseDragging",
        [](ImGuiMouseButton button, float lock_threshold) { return ImGui::IsMouseDragging(button, lock_threshold); },
        py::arg("button"),
        py::arg("lock_threshold") = -1.f
    );
    m.def("ResetMouseDragDelta", [](ImGuiMouseButton button) { ImGui::ResetMouseDragDelta(button); }, py::arg("button"));
    m.def("GetMouseCursor", []() { return ImGui::GetMouseCursor(); });
    m.def("SetMouseCursor", [](ImGuiMouseCursor cursor_type) { ImGui::SetMouseCursor(cursor_type); }, py::arg("cursor_type"));
    m.def("SetNextFrameWantCaptureMouse", [](bool want_capture_mouse) { ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse); }, py::arg("want_capture_mouse"));

    // Inputs Utilities: Keyboard
    m.def("IsKeyDown", [](ImGuiKey user_key_index) { return ImGui::IsKeyDown(user_key_index); }, py::arg("user_key_index"));
    m.def("IsKeyPressed", [](ImGuiKey user_key_index, bool repeat) { return ImGui::IsKeyPressed(user_key_index, repeat); }, py::arg("user_key_index"), py::arg("repeat")=true);
    m.def("IsKeyReleased", [](ImGuiKey user_key_index) { return ImGui::IsKeyReleased(user_key_index); }, py::arg("user_key_index"));
    m.def(
        "GetKeyPressedAmount",
        [](ImGuiKey key_index, float repeat_delay, float rate) {
            return ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate);
        },
        py::arg("key_index"),
        py::arg("repeat_delay"),
        py::arg("rate")
    );
    m.def(
        "SetNextFrameWantCaptureKeyboard",
        [](bool want_capture_keyboard) {
            ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard);
        },
        py::arg("want_capture_keyboard") = true
    );

    // Clipboard Utilities
    m.def("GetClipboardText", []() { return ImGui::GetClipboardText(); });
    m.def("SetClipboardText", [](const char *text) { ImGui::SetClipboardText(text); }, py::arg("text"));

    // Settings/.Ini Utilities
    m.def("LoadIniSettingsFromDisk", [](const char *ini_filename) { ImGui::LoadIniSettingsFromDisk(ini_filename); }, py::arg("ini_filename"));
    m.def("LoadIniSettingsFromMemory", [](const char *ini_data) { ImGui::LoadIniSettingsFromMemory(ini_data); }, py::arg("ini_data"));
    m.def("SaveIniSettingsToDisk", [](const char *ini_filename) { ImGui::SaveIniSettingsToDisk(ini_filename); }, py::arg("ini_filename"));
    m.def("SaveIniSettingsToMemory", []() { return ImGui::SaveIniSettingsToMemory(); });

    // Draw Commands 
    py::class_<ImDrawList>(m, "ImDrawList")

        // Clip Rect

        .def(
            "PushClipRect",
            [](ImDrawList& self, const Vec2T& clip_rect_min, const Vec2T& clip_rect_max, bool intersect_with_current_clip_rect) {
                self.PushClipRect(to_vec2(clip_rect_min), to_vec2(clip_rect_max), intersect_with_current_clip_rect);
            },
            py::arg("clip_rect_min"),
            py::arg("clip_rect_max"),
            py::arg("intersect_with_current_clip_rect") = false
        )
        .def("PushClipRectFullScreen", &ImDrawList::PushClipRectFullScreen)
        .def("PopClipRect", &ImDrawList::PopClipRect)
        .def("GetClipRectMin", [](ImDrawList& self) { return from_vec2(self.GetClipRectMin()); })
        .def("GetClipRectMax", [](ImDrawList& self) { return from_vec2(self.GetClipRectMax()); })

        // Primitives

        .def(
            "AddLine", 
            [](py::object& draw_list_obj, const Vec2T& p1, const Vec2T& p2, ImU32 col, float thickness) {
                ImDrawList& draw_list = draw_list_obj.cast<ImDrawList&>();
                draw_list.AddLine(to_vec2(p1), to_vec2(p2), col, thickness);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("col"),
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddRect", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags, float thickness) {
                self.AddRect(to_vec2(p_min), to_vec2(p_max), col, rounding, flags, thickness);
            },
            py::arg("p_min"),
            py::arg("p_max"),
            py::arg("col"),
            py::arg("rounding") = 0.0f,
            py::arg("flags") = 0,
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddRectFilled", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col, float rounding, ImDrawFlags flags) {
                self.AddRectFilled(to_vec2(p_min), to_vec2(p_max), col, rounding, flags);
            },
            py::arg("p_min"),
            py::arg("p_max"),
            py::arg("col"),
            py::arg("rounding") = 0.0f,
            py::arg("flags") = 0
        )
        .def(
            "AddRectFilledMultiColor", 
            [](ImDrawList& self, const Vec2T& p_min, const Vec2T& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left) {
                self.AddRectFilledMultiColor(to_vec2(p_min), to_vec2(p_max), col_upr_left, col_upr_right, col_bot_right, col_bot_left);
            },
            py::arg("p_min"),
            py::arg("p_max"),
            py::arg("col_upr_left"),
            py::arg("col_upr_right"),
            py::arg("col_bot_right"),
            py::arg("col_bot_left")
        )
        .def(
            "AddQuad", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness) {
                self.AddQuad(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("p4"),
            py::arg("col"),
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddQuadFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col) {
                self.AddQuadFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("p4"),
            py::arg("col")
        )
        .def(
            "AddTriangle", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness) {
                self.AddTriangle(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("col"),
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddTriangleFilled", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col) {
                self.AddTriangleFilled(to_vec2(p1), to_vec2(p2), to_vec2(p3), col);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("col")
        )
        .def(
            "AddCircle", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddCircle(to_vec2(center), radius, col, num_segments, thickness);
            },
            py::arg("center"),
            py::arg("radius"),
            py::arg("col"),
            py::arg("num_segments") = 0,
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddCircleFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddCircleFilled(to_vec2(center), radius, col, num_segments);
            },
            py::arg("center"),
            py::arg("radius"),
            py::arg("col"),
            py::arg("num_segments") = 0
        )
        .def(
            "AddNgon", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments, float thickness) {
                self.AddNgon(to_vec2(center), radius, col, num_segments, thickness);
            },
            py::arg("center"),
            py::arg("radius"),
            py::arg("col"),
            py::arg("num_segments") = 0,
            py::arg("thickness") = 1.0f
        )
        .def(
            "AddNgonFilled", 
            [](ImDrawList& self, const Vec2T& center, const float radius, ImU32 col, int num_segments) {
                self.AddNgonFilled(to_vec2(center), radius, col, num_segments);
            },
            py::arg("center"),
            py::arg("radius"),
            py::arg("col"),
            py::arg("num_segments") = 0
        )
        .def(
            "AddText", 
            [](ImDrawList& self, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end) {
                self.AddText(to_vec2(pos), col, text_begin, text_end);
            },
            py::arg("pos"),
            py::arg("col"),
            py::arg("text_begin"),
            py::arg("text_end") = nullptr
        )
        .def(
            "AddText", 
            [](ImDrawList& self, ImFont* font, float font_size, const Vec2T& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width) {
                self.AddText(font, font_size, to_vec2(pos), col, text_begin, text_end, wrap_width);
            },
            py::arg("font"),
            py::arg("font_size"),
            py::arg("pos"),
            py::arg("col"),
            py::arg("text_begin"),
            py::arg("text_end") = nullptr,
            py::arg("wrap_width") = 0.0f
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
            py::arg("points"),
            py::arg("num_points"),
            py::arg("col"),
            py::arg("flags"),
            py::arg("thickness")
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
            py::arg("points"),
            py::arg("num_points"),
            py::arg("col")
        )
        .def(
            "AddBezierCubic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, const Vec2T& p4, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierCubic(to_vec2(p1), to_vec2(p2), to_vec2(p3), to_vec2(p4), col, thickness, num_segments);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("p4"),
            py::arg("col"),
            py::arg("thickness"),
            py::arg("num_segments") = 0
        )
        .def(
            "AddBezierQuadratic", 
            [](ImDrawList& self, const Vec2T& p1, const Vec2T& p2, const Vec2T& p3, ImU32 col, float thickness, int num_segments = 0) {
                self.AddBezierQuadratic(to_vec2(p1), to_vec2(p2), to_vec2(p3), col, thickness, num_segments);
            },
            py::arg("p1"),
            py::arg("p2"),
            py::arg("p3"),
            py::arg("col"),
            py::arg("thickness"),
            py::arg("num_segments") = 0
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
            py::arg("points"),
            py::arg("num_points"),
            py::arg("col"),
            py::arg("flags"),
            py::arg("thickness")
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
            py::arg("points"),
            py::arg("num_points"),
            py::arg("col")
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
            py::arg("points"),
            py::arg("num_points"),
            py::arg("col")
        )
        
    ;
        

    // Macros etc
    m.def("IM_COL32", [](uint8_t R, uint8_t G, uint8_t B, uint8_t A) { return IM_COL32(R,G,B,A); });
}
// clang-format on

void bind_imgui_enums(py::module& m) {

  py::enum_<ImGuiKey>(m, "ImGuiKey");

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

  m.attr("ImGuiKey_Tab") = static_cast<ImGuiKey>(ImGuiKey_Tab);
  m.attr("ImGuiKey_None") = static_cast<ImGuiKey>(ImGuiKey_None);
  m.attr("ImGuiKey_Tab") = static_cast<ImGuiKey>(ImGuiKey_Tab);
  m.attr("ImGuiKey_LeftArrow") = static_cast<ImGuiKey>(ImGuiKey_LeftArrow);
  m.attr("ImGuiKey_RightArrow") = static_cast<ImGuiKey>(ImGuiKey_RightArrow);
  m.attr("ImGuiKey_UpArrow") = static_cast<ImGuiKey>(ImGuiKey_UpArrow);
  m.attr("ImGuiKey_DownArrow") = static_cast<ImGuiKey>(ImGuiKey_DownArrow);
  m.attr("ImGuiKey_PageUp") = static_cast<ImGuiKey>(ImGuiKey_PageUp);
  m.attr("ImGuiKey_PageDown") = static_cast<ImGuiKey>(ImGuiKey_PageDown);
  m.attr("ImGuiKey_Home") = static_cast<ImGuiKey>(ImGuiKey_Home);
  m.attr("ImGuiKey_End") = static_cast<ImGuiKey>(ImGuiKey_End);
  m.attr("ImGuiKey_Insert") = static_cast<ImGuiKey>(ImGuiKey_Insert);
  m.attr("ImGuiKey_Delete") = static_cast<ImGuiKey>(ImGuiKey_Delete);
  m.attr("ImGuiKey_Backspace") = static_cast<ImGuiKey>(ImGuiKey_Backspace);
  m.attr("ImGuiKey_Space") = static_cast<ImGuiKey>(ImGuiKey_Space);
  m.attr("ImGuiKey_Enter") = static_cast<ImGuiKey>(ImGuiKey_Enter);
  m.attr("ImGuiKey_Escape") = static_cast<ImGuiKey>(ImGuiKey_Escape);
  m.attr("ImGuiKey_LeftCtrl") = static_cast<ImGuiKey>(ImGuiKey_LeftCtrl);
  m.attr("ImGuiKey_LeftShift") = static_cast<ImGuiKey>(ImGuiKey_LeftShift);
  m.attr("ImGuiKey_LeftAlt") = static_cast<ImGuiKey>(ImGuiKey_LeftAlt);
  m.attr("ImGuiKey_LeftSuper") = static_cast<ImGuiKey>(ImGuiKey_LeftSuper);
  m.attr("ImGuiKey_RightCtrl") = static_cast<ImGuiKey>(ImGuiKey_RightCtrl);
  m.attr("ImGuiKey_RightShift") = static_cast<ImGuiKey>(ImGuiKey_RightShift);
  m.attr("ImGuiKey_RightAlt") = static_cast<ImGuiKey>(ImGuiKey_RightAlt);
  m.attr("ImGuiKey_RightSuper") = static_cast<ImGuiKey>(ImGuiKey_RightSuper);
  m.attr("ImGuiKey_Menu") = static_cast<ImGuiKey>(ImGuiKey_Menu);
  m.attr("ImGuiKey_0") = static_cast<ImGuiKey>(ImGuiKey_0);
  m.attr("ImGuiKey_1") = static_cast<ImGuiKey>(ImGuiKey_1);
  m.attr("ImGuiKey_2") = static_cast<ImGuiKey>(ImGuiKey_2);
  m.attr("ImGuiKey_3") = static_cast<ImGuiKey>(ImGuiKey_3);
  m.attr("ImGuiKey_4") = static_cast<ImGuiKey>(ImGuiKey_4);
  m.attr("ImGuiKey_5") = static_cast<ImGuiKey>(ImGuiKey_5);
  m.attr("ImGuiKey_6") = static_cast<ImGuiKey>(ImGuiKey_6);
  m.attr("ImGuiKey_7") = static_cast<ImGuiKey>(ImGuiKey_7);
  m.attr("ImGuiKey_8") = static_cast<ImGuiKey>(ImGuiKey_8);
  m.attr("ImGuiKey_9") = static_cast<ImGuiKey>(ImGuiKey_9);
  m.attr("ImGuiKey_A") = static_cast<ImGuiKey>(ImGuiKey_A);
  m.attr("ImGuiKey_B") = static_cast<ImGuiKey>(ImGuiKey_B);
  m.attr("ImGuiKey_C") = static_cast<ImGuiKey>(ImGuiKey_C);
  m.attr("ImGuiKey_D") = static_cast<ImGuiKey>(ImGuiKey_D);
  m.attr("ImGuiKey_E") = static_cast<ImGuiKey>(ImGuiKey_E);
  m.attr("ImGuiKey_F") = static_cast<ImGuiKey>(ImGuiKey_F);
  m.attr("ImGuiKey_G") = static_cast<ImGuiKey>(ImGuiKey_G);
  m.attr("ImGuiKey_H") = static_cast<ImGuiKey>(ImGuiKey_H);
  m.attr("ImGuiKey_I") = static_cast<ImGuiKey>(ImGuiKey_I);
  m.attr("ImGuiKey_J") = static_cast<ImGuiKey>(ImGuiKey_J);
  m.attr("ImGuiKey_K") = static_cast<ImGuiKey>(ImGuiKey_K);
  m.attr("ImGuiKey_L") = static_cast<ImGuiKey>(ImGuiKey_L);
  m.attr("ImGuiKey_M") = static_cast<ImGuiKey>(ImGuiKey_M);
  m.attr("ImGuiKey_N") = static_cast<ImGuiKey>(ImGuiKey_N);
  m.attr("ImGuiKey_O") = static_cast<ImGuiKey>(ImGuiKey_O);
  m.attr("ImGuiKey_P") = static_cast<ImGuiKey>(ImGuiKey_P);
  m.attr("ImGuiKey_Q") = static_cast<ImGuiKey>(ImGuiKey_Q);
  m.attr("ImGuiKey_R") = static_cast<ImGuiKey>(ImGuiKey_R);
  m.attr("ImGuiKey_S") = static_cast<ImGuiKey>(ImGuiKey_S);
  m.attr("ImGuiKey_T") = static_cast<ImGuiKey>(ImGuiKey_T);
  m.attr("ImGuiKey_U") = static_cast<ImGuiKey>(ImGuiKey_U);
  m.attr("ImGuiKey_V") = static_cast<ImGuiKey>(ImGuiKey_V);
  m.attr("ImGuiKey_W") = static_cast<ImGuiKey>(ImGuiKey_W);
  m.attr("ImGuiKey_X") = static_cast<ImGuiKey>(ImGuiKey_X);
  m.attr("ImGuiKey_Y") = static_cast<ImGuiKey>(ImGuiKey_Y);
  m.attr("ImGuiKey_Z") = static_cast<ImGuiKey>(ImGuiKey_Z);
  m.attr("ImGuiKey_F1") = static_cast<ImGuiKey>(ImGuiKey_F1);
  m.attr("ImGuiKey_F2") = static_cast<ImGuiKey>(ImGuiKey_F2);
  m.attr("ImGuiKey_F3") = static_cast<ImGuiKey>(ImGuiKey_F3);
  m.attr("ImGuiKey_F4") = static_cast<ImGuiKey>(ImGuiKey_F4);
  m.attr("ImGuiKey_F5") = static_cast<ImGuiKey>(ImGuiKey_F5);
  m.attr("ImGuiKey_F6") = static_cast<ImGuiKey>(ImGuiKey_F6);
  m.attr("ImGuiKey_F7") = static_cast<ImGuiKey>(ImGuiKey_F7);
  m.attr("ImGuiKey_F8") = static_cast<ImGuiKey>(ImGuiKey_F8);
  m.attr("ImGuiKey_F9") = static_cast<ImGuiKey>(ImGuiKey_F9);
  m.attr("ImGuiKey_F10") = static_cast<ImGuiKey>(ImGuiKey_F10);
  m.attr("ImGuiKey_F11") = static_cast<ImGuiKey>(ImGuiKey_F11);
  m.attr("ImGuiKey_F12") = static_cast<ImGuiKey>(ImGuiKey_F12);
  m.attr("ImGuiKey_F13") = static_cast<ImGuiKey>(ImGuiKey_F13);
  m.attr("ImGuiKey_F14") = static_cast<ImGuiKey>(ImGuiKey_F14);
  m.attr("ImGuiKey_F15") = static_cast<ImGuiKey>(ImGuiKey_F15);
  m.attr("ImGuiKey_F16") = static_cast<ImGuiKey>(ImGuiKey_F16);
  m.attr("ImGuiKey_F17") = static_cast<ImGuiKey>(ImGuiKey_F17);
  m.attr("ImGuiKey_F18") = static_cast<ImGuiKey>(ImGuiKey_F18);
  m.attr("ImGuiKey_F19") = static_cast<ImGuiKey>(ImGuiKey_F19);
  m.attr("ImGuiKey_F20") = static_cast<ImGuiKey>(ImGuiKey_F20);
  m.attr("ImGuiKey_F21") = static_cast<ImGuiKey>(ImGuiKey_F21);
  m.attr("ImGuiKey_F22") = static_cast<ImGuiKey>(ImGuiKey_F22);
  m.attr("ImGuiKey_F23") = static_cast<ImGuiKey>(ImGuiKey_F23);
  m.attr("ImGuiKey_F24") = static_cast<ImGuiKey>(ImGuiKey_F24);
  m.attr("ImGuiKey_Apostrophe") = static_cast<ImGuiKey>(ImGuiKey_Apostrophe);
  m.attr("ImGuiKey_Comma") = static_cast<ImGuiKey>(ImGuiKey_Comma);
  m.attr("ImGuiKey_Minus") = static_cast<ImGuiKey>(ImGuiKey_Minus);
  m.attr("ImGuiKey_Period") = static_cast<ImGuiKey>(ImGuiKey_Period);
  m.attr("ImGuiKey_Slash") = static_cast<ImGuiKey>(ImGuiKey_Slash);
  m.attr("ImGuiKey_Semicolon") = static_cast<ImGuiKey>(ImGuiKey_Semicolon);
  m.attr("ImGuiKey_Equal") = static_cast<ImGuiKey>(ImGuiKey_Equal);
  m.attr("ImGuiKey_LeftBracket") = static_cast<ImGuiKey>(ImGuiKey_LeftBracket);
  m.attr("ImGuiKey_Backslash") = static_cast<ImGuiKey>(ImGuiKey_Backslash);
  m.attr("ImGuiKey_RightBracket") = static_cast<ImGuiKey>(ImGuiKey_RightBracket);
  m.attr("ImGuiKey_GraveAccent") = static_cast<ImGuiKey>(ImGuiKey_GraveAccent);
  m.attr("ImGuiKey_CapsLock") = static_cast<ImGuiKey>(ImGuiKey_CapsLock);
  m.attr("ImGuiKey_ScrollLock") = static_cast<ImGuiKey>(ImGuiKey_ScrollLock);
  m.attr("ImGuiKey_NumLock") = static_cast<ImGuiKey>(ImGuiKey_NumLock);
  m.attr("ImGuiKey_PrintScreen") = static_cast<ImGuiKey>(ImGuiKey_PrintScreen);
  m.attr("ImGuiKey_Pause") = static_cast<ImGuiKey>(ImGuiKey_Pause);
  m.attr("ImGuiKey_Keypad0") = static_cast<ImGuiKey>(ImGuiKey_Keypad0);
  m.attr("ImGuiKey_Keypad1") = static_cast<ImGuiKey>(ImGuiKey_Keypad1);
  m.attr("ImGuiKey_Keypad2") = static_cast<ImGuiKey>(ImGuiKey_Keypad2);
  m.attr("ImGuiKey_Keypad3") = static_cast<ImGuiKey>(ImGuiKey_Keypad3);
  m.attr("ImGuiKey_Keypad4") = static_cast<ImGuiKey>(ImGuiKey_Keypad4);
  m.attr("ImGuiKey_Keypad5") = static_cast<ImGuiKey>(ImGuiKey_Keypad5);
  m.attr("ImGuiKey_Keypad6") = static_cast<ImGuiKey>(ImGuiKey_Keypad6);
  m.attr("ImGuiKey_Keypad7") = static_cast<ImGuiKey>(ImGuiKey_Keypad7);
  m.attr("ImGuiKey_Keypad8") = static_cast<ImGuiKey>(ImGuiKey_Keypad8);
  m.attr("ImGuiKey_Keypad9") = static_cast<ImGuiKey>(ImGuiKey_Keypad9);
  m.attr("ImGuiKey_KeypadDecimal") = static_cast<ImGuiKey>(ImGuiKey_KeypadDecimal);
  m.attr("ImGuiKey_KeypadDivide") = static_cast<ImGuiKey>(ImGuiKey_KeypadDivide);
  m.attr("ImGuiKey_KeypadMultiply") = static_cast<ImGuiKey>(ImGuiKey_KeypadMultiply);
  m.attr("ImGuiKey_KeypadSubtract") = static_cast<ImGuiKey>(ImGuiKey_KeypadSubtract);
  m.attr("ImGuiKey_KeypadAdd") = static_cast<ImGuiKey>(ImGuiKey_KeypadAdd);
  m.attr("ImGuiKey_KeypadEnter") = static_cast<ImGuiKey>(ImGuiKey_KeypadEnter);
  m.attr("ImGuiKey_KeypadEqual") = static_cast<ImGuiKey>(ImGuiKey_KeypadEqual);
  m.attr("ImGuiKey_AppBack") = static_cast<ImGuiKey>(ImGuiKey_AppBack);
  m.attr("ImGuiKey_AppForward") = static_cast<ImGuiKey>(ImGuiKey_AppForward);
  m.attr("ImGuiKey_GamepadStart") = static_cast<ImGuiKey>(ImGuiKey_GamepadStart);
  m.attr("ImGuiKey_GamepadBack") = static_cast<ImGuiKey>(ImGuiKey_GamepadBack);
  m.attr("ImGuiKey_GamepadFaceUp") = static_cast<ImGuiKey>(ImGuiKey_GamepadFaceUp);
  m.attr("ImGuiKey_GamepadFaceDown") = static_cast<ImGuiKey>(ImGuiKey_GamepadFaceDown);
  m.attr("ImGuiKey_GamepadFaceLeft") = static_cast<ImGuiKey>(ImGuiKey_GamepadFaceLeft);
  m.attr("ImGuiKey_GamepadFaceRight") = static_cast<ImGuiKey>(ImGuiKey_GamepadFaceRight);
  m.attr("ImGuiKey_GamepadDpadUp") = static_cast<ImGuiKey>(ImGuiKey_GamepadDpadUp);
  m.attr("ImGuiKey_GamepadDpadDown") = static_cast<ImGuiKey>(ImGuiKey_GamepadDpadDown);
  m.attr("ImGuiKey_GamepadDpadLeft") = static_cast<ImGuiKey>(ImGuiKey_GamepadDpadLeft);
  m.attr("ImGuiKey_GamepadDpadRight") = static_cast<ImGuiKey>(ImGuiKey_GamepadDpadRight);
  m.attr("ImGuiKey_GamepadL1") = static_cast<ImGuiKey>(ImGuiKey_GamepadL1);
  m.attr("ImGuiKey_GamepadR1") = static_cast<ImGuiKey>(ImGuiKey_GamepadR1);
  m.attr("ImGuiKey_GamepadL2") = static_cast<ImGuiKey>(ImGuiKey_GamepadL2);
  m.attr("ImGuiKey_GamepadR2") = static_cast<ImGuiKey>(ImGuiKey_GamepadR2);
  m.attr("ImGuiKey_GamepadL3") = static_cast<ImGuiKey>(ImGuiKey_GamepadL3);
  m.attr("ImGuiKey_GamepadR3") = static_cast<ImGuiKey>(ImGuiKey_GamepadR3);
  m.attr("ImGuiKey_GamepadLStickUp") = static_cast<ImGuiKey>(ImGuiKey_GamepadLStickUp);
  m.attr("ImGuiKey_GamepadLStickDown") = static_cast<ImGuiKey>(ImGuiKey_GamepadLStickDown);
  m.attr("ImGuiKey_GamepadLStickLeft") = static_cast<ImGuiKey>(ImGuiKey_GamepadLStickLeft);
  m.attr("ImGuiKey_GamepadLStickRight") = static_cast<ImGuiKey>(ImGuiKey_GamepadLStickRight);
  m.attr("ImGuiKey_GamepadRStickUp") = static_cast<ImGuiKey>(ImGuiKey_GamepadRStickUp);
  m.attr("ImGuiKey_GamepadRStickDown") = static_cast<ImGuiKey>(ImGuiKey_GamepadRStickDown);
  m.attr("ImGuiKey_GamepadRStickLeft") = static_cast<ImGuiKey>(ImGuiKey_GamepadRStickLeft);
  m.attr("ImGuiKey_GamepadRStickRight") = static_cast<ImGuiKey>(ImGuiKey_GamepadRStickRight);
  m.attr("ImGuiKey_ModCtrl") = static_cast<ImGuiKey>(ImGuiKey_ModCtrl);
  m.attr("ImGuiKey_ModShift") = static_cast<ImGuiKey>(ImGuiKey_ModShift);
  m.attr("ImGuiKey_ModAlt") = static_cast<ImGuiKey>(ImGuiKey_ModAlt);
  m.attr("ImGuiKey_ModSuper") = static_cast<ImGuiKey>(ImGuiKey_ModSuper);

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
  m.attr("ImGuiCol_Tab") = static_cast<int>(ImGuiCol_Tab);
  m.attr("ImGuiCol_TabHovered") = static_cast<int>(ImGuiCol_TabHovered);
  m.attr("ImGuiCol_TabActive") = static_cast<int>(ImGuiCol_TabActive);
  m.attr("ImGuiCol_TabUnfocused") = static_cast<int>(ImGuiCol_TabUnfocused);
  m.attr("ImGuiCol_TabUnfocusedActive") = static_cast<int>(ImGuiCol_TabUnfocusedActive);
  m.attr("ImGuiCol_PlotLines") = static_cast<int>(ImGuiCol_PlotLines);
  m.attr("ImGuiCol_PlotLinesHovered") = static_cast<int>(ImGuiCol_PlotLinesHovered);
  m.attr("ImGuiCol_PlotHistogram") = static_cast<int>(ImGuiCol_PlotHistogram);
  m.attr("ImGuiCol_PlotHistogramHovered") = static_cast<int>(ImGuiCol_PlotHistogramHovered);
  m.attr("ImGuiCol_TextSelectedBg") = static_cast<int>(ImGuiCol_TextSelectedBg);
  m.attr("ImGuiCol_DragDropTarget") = static_cast<int>(ImGuiCol_DragDropTarget);
  m.attr("ImGuiCol_NavHighlight") = static_cast<int>(ImGuiCol_NavHighlight);
  m.attr("ImGuiCol_NavWindowingHighlight") = static_cast<int>(ImGuiCol_NavWindowingHighlight);
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

