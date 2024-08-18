
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "imgui_utils.h"

namespace py = pybind11;

void bind_imgui_funcs(py::module& m) {
  m.def("NewFrame", &ImGui::NewFrame,
        "Starts a new ImGui frame. This must be called before any other ImGui commands in a frame.");
  m.def("EndFrame", &ImGui::EndFrame,
        "Ends the current ImGui frame. If you don't need to render data, you can call this without Render().");
  m.def("Render", &ImGui::Render, "Ends the ImGui frame and finalizes the draw data, which can then be rendered.");
  m.def(
      "ShowDemoWindow",
      [](std::optional<bool> open) {
        bool* p_open = open.has_value() ? &open.value() : nullptr;
        ImGui::ShowDemoWindow(p_open);
        return open;
      },
      py::arg("open") = std::nullopt, "Creates a demo window that demonstrates most ImGui features.");
  m.def(
      "ShowMetricsWindow",
      [](std::optional<bool> open) {
        bool* p_open = open.has_value() ? &open.value() : nullptr;
        ImGui::ShowMetricsWindow(p_open);
        return open;
      },
      py::arg("open") = std::nullopt,
      "Creates a Metrics/Debugger window that displays internal state and other metrics.");
  m.def(
      "ShowStyleEditor", []() { ImGui::ShowStyleEditor(); },
      "Opens the style editor, which allows you to customize the style parameters.");
  m.def("ShowUserGuide", &ImGui::ShowUserGuide,
        "Shows a user guide window with basic help and information about ImGui usage.");
  m.def("GetVersion", &ImGui::GetVersion, "Returns the ImGui version as a string.");
  m.def(
      "StyleColorsDark", []() { ImGui::StyleColorsDark(); }, "Applies the default dark style to the current context.");
  m.def(
      "StyleColorsLight", []() { ImGui::StyleColorsLight(); },
      "Applies the default light style to the current context.");
  m.def(
      "StyleColorsClassic", []() { ImGui::StyleColorsClassic(); },
      "Applies the classic ImGui style to the current context.");
  m.def(
      "Begin",
      [](const char* name, std::optional<bool> open, ImGuiWindowFlags flags) {
        bool* p_open = open.has_value() ? &open.value() : nullptr;
        const auto res_ = ImGui::Begin(name, p_open, flags);
        return std::make_tuple(res_, open);
      },
      py::arg("name"), py::arg("open") = std::nullopt, py::arg("flags") = 0,
      "Begins a new window. Returns true if the window is visible.");
  m.def("End", &ImGui::End, "Ends the current window.");
  m.def(
      "BeginChild",
      [](const char* str_id, const ImVec2& size, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags) {
        const auto res_ = ImGui::BeginChild(str_id, size, child_flags, window_flags);
        return res_;
      },
      py::arg("str_id"), py::arg("size") = ImVec2(0, 0), py::arg("child_flags") = 0, py::arg("window_flags") = 0,
      "Begins a child window, which is a self-contained scrolling/clipping region.");
  m.def("EndChild", &ImGui::EndChild, "Ends a child window.");
  m.def("IsWindowAppearing", &ImGui::IsWindowAppearing, "Returns true if the current window is appearing.");
  m.def("IsWindowCollapsed", &ImGui::IsWindowCollapsed, "Returns true if the current window is collapsed.");
  m.def("IsWindowFocused", &ImGui::IsWindowFocused, py::arg("flags") = 0,
        "Returns true if the current window is focused, or its root/child depending on flags.");
  m.def("IsWindowHovered", &ImGui::IsWindowHovered, py::arg("flags") = 0,
        "Returns true if the current window is hovered and hoverable.");
  m.def("GetWindowPos", &ImGui::GetWindowPos, "Returns the current window position in screen space.");
  m.def("GetWindowSize", &ImGui::GetWindowSize, "Returns the current window size.");
  m.def("SetNextWindowPos", &ImGui::SetNextWindowPos, py::arg("pos"), py::arg("cond") = 0,
        py::arg("pivot") = ImVec2(0, 0), "Sets the position for the next window. Call before Begin().");
  m.def("SetNextWindowSize", &ImGui::SetNextWindowSize, py::arg("size"), py::arg("cond") = 0,
        "Sets the size for the next window. Call before Begin().");
  m.def("SetNextWindowContentSize", &ImGui::SetNextWindowContentSize, py::arg("size"),
        "Sets the content size for the next window (scrollable client area). This does not include window decorations "
        "like the title bar or menu bar.");
  m.def("SetNextWindowCollapsed", &ImGui::SetNextWindowCollapsed, py::arg("collapsed"), py::arg("cond") = 0,
        "Sets the collapsed state for the next window. This should be called before Begin().");
  m.def("SetNextWindowFocus", &ImGui::SetNextWindowFocus,
        "Sets the next window to be focused and top-most. This should be called before Begin().");
  m.def("SetNextWindowScroll", &ImGui::SetNextWindowScroll, py::arg("scroll"),
        "Sets the scrolling position for the next window. Use < 0.0f for an axis to leave it unchanged.");
  m.def("SetNextWindowBgAlpha", &ImGui::SetNextWindowBgAlpha, py::arg("alpha"),
        "Sets the background color alpha for the next window. This can be used to override the alpha component of "
        "ImGuiCol_WindowBg/ChildBg/PopupBg.");
  m.def(
      "SetWindowPos", [](const ImVec2& pos, ImGuiCond cond) { ImGui::SetWindowPos(pos, cond); }, py::arg("pos"),
      py::arg("cond") = 0,
      "(Not recommended) Sets the current window position. This should be called within a Begin()/End() block. Prefer "
      "using SetNextWindowPos().");
  m.def(
      "SetWindowSize", [](const ImVec2& size, ImGuiCond cond) { ImGui::SetWindowSize(size, cond); }, py::arg("size"),
      py::arg("cond") = 0,
      "(Not recommended) Sets the current window size. This should be called within a Begin()/End() block. Prefer "
      "using SetNextWindowSize().");
  m.def(
      "SetWindowCollapsed", [](bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(collapsed, cond); },
      py::arg("collapsed"), py::arg("cond") = 0,
      "(Not recommended) Sets the current window collapsed state. Prefer using SetNextWindowCollapsed().");
  m.def(
      "SetWindowFocus", []() { ImGui::SetWindowFocus(); },
      "(Not recommended) Sets the current window to be focused and top-most. Prefer using SetNextWindowFocus().");
  m.def(
      "SetWindowPos", [](const char* name, const ImVec2& pos, ImGuiCond cond) { ImGui::SetWindowPos(name, pos, cond); },
      py::arg("name"), py::arg("pos"), py::arg("cond") = 0, "Sets the position of the window specified by name.");
  m.def(
      "SetWindowSize",
      [](const char* name, const ImVec2& size, ImGuiCond cond) { ImGui::SetWindowSize(name, size, cond); },
      py::arg("name"), py::arg("size"), py::arg("cond") = 0,
      "Sets the size of the window specified by name. Set an axis to 0.0f to force an auto-fit.");
  m.def(
      "SetWindowCollapsed",
      [](const char* name, bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(name, collapsed, cond); },
      py::arg("name"), py::arg("collapsed"), py::arg("cond") = 0,
      "Sets the collapsed state of the window specified by name.");
  m.def(
      "SetWindowFocus", [](const char* name) { ImGui::SetWindowFocus(name); }, py::arg("name"),
      "Sets the window specified by name to be focused and top-most.");
  m.def("GetScrollX", &ImGui::GetScrollX,
        "Returns the horizontal scrolling amount, ranging from 0 to GetScrollMaxX().");
  m.def("GetScrollY", &ImGui::GetScrollY, "Returns the vertical scrolling amount, ranging from 0 to GetScrollMaxY().");
  m.def("SetScrollX", &ImGui::SetScrollX, py::arg("scroll_x"),
        "Sets the horizontal scrolling amount, ranging from 0 to GetScrollMaxX().");
  m.def("SetScrollY", &ImGui::SetScrollY, py::arg("scroll_y"),
        "Sets the vertical scrolling amount, ranging from 0 to GetScrollMaxY().");
  m.def("GetScrollMaxX", &ImGui::GetScrollMaxX,
        "Returns the maximum horizontal scrolling amount, calculated as ContentSize.x - WindowSize.x - "
        "DecorationsSize.x.");
  m.def(
      "GetScrollMaxY", &ImGui::GetScrollMaxY,
      "Returns the maximum vertical scrolling amount, calculated as ContentSize.y - WindowSize.y - DecorationsSize.y.");
  m.def("SetScrollHereX", &ImGui::SetScrollHereX, py::arg("center_x_ratio") = 0.5f,
        "Adjusts the horizontal scrolling amount to make the current cursor position visible. center_x_ratio=0.0 "
        "aligns left, 0.5 centers, 1.0 aligns right.");
  m.def("SetScrollHereY", &ImGui::SetScrollHereY, py::arg("center_y_ratio") = 0.5f,
        "Adjusts the vertical scrolling amount to make the current cursor position visible. center_y_ratio=0.0 aligns "
        "top, 0.5 centers, 1.0 aligns bottom.");
  m.def("SetScrollFromPosX", &ImGui::SetScrollFromPosX, py::arg("local_x"), py::arg("center_x_ratio") = 0.5f,
        "Adjusts the horizontal scrolling amount to make the specified position visible. Use GetCursorStartPos() + "
        "offset to compute a valid position.");
  m.def("SetScrollFromPosY", &ImGui::SetScrollFromPosY, py::arg("local_y"), py::arg("center_y_ratio") = 0.5f,
        "Adjusts the vertical scrolling amount to make the specified position visible. Use GetCursorStartPos() + "
        "offset to compute a valid position.");
  m.def(
      "PushStyleColor", [](ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); }, py::arg("idx"),
      py::arg("col"), "Pushes a style color onto the style color stack, modifying the color specified by idx.");
  m.def(
      "PushStyleColor", [](ImGuiCol idx, const ImVec4& col) { ImGui::PushStyleColor(idx, col); }, py::arg("idx"),
      py::arg("col"), "Pushes a style color onto the style color stack, modifying the color specified by idx.");
  m.def("PopStyleColor", &ImGui::PopStyleColor, py::arg("count") = 1,
        "Pops one or more style colors from the style color stack.");
  m.def(
      "PushStyleVar", [](ImGuiStyleVar idx, float val) { ImGui::PushStyleVar(idx, val); }, py::arg("idx"),
      py::arg("val"),
      "Pushes a style variable onto the style variable stack, modifying the float variable specified by idx.");
  m.def(
      "PushStyleVar", [](ImGuiStyleVar idx, const ImVec2& val) { ImGui::PushStyleVar(idx, val); }, py::arg("idx"),
      py::arg("val"),
      "Pushes a style variable onto the style variable stack, modifying the ImVec2 variable specified by idx.");
  m.def("PopStyleVar", &ImGui::PopStyleVar, py::arg("count") = 1,
        "Pops one or more style variables from the style variable stack.");
  m.def("PushItemFlag", &ImGui::PushItemFlag, py::arg("option"), py::arg("enabled"),
        "Pushes an item flag onto the item flag stack, modifying the specified option.");
  m.def("PopItemFlag", &ImGui::PopItemFlag, "Pops the last item flag pushed onto the item flag stack.");
  m.def("PushItemWidth", &ImGui::PushItemWidth, py::arg("item_width"),
        "Pushes the width of items for common large 'item+label' widgets. >0.0f: width in pixels, <0.0f aligns the "
        "width to the right of the window.");
  m.def("PopItemWidth", &ImGui::PopItemWidth, "Pops the last item width pushed onto the item width stack.");
  m.def("SetNextItemWidth", &ImGui::SetNextItemWidth, py::arg("item_width"),
        "Sets the width of the next common large 'item+label' widget. >0.0f: width in pixels, <0.0f aligns the width "
        "to the right of the window.");
  m.def("CalcItemWidth", &ImGui::CalcItemWidth,
        "Calculates the width of the item given the pushed settings and current cursor position.");
  m.def("PushTextWrapPos", &ImGui::PushTextWrapPos, py::arg("wrap_local_pos_x") = 0.0f,
        "Pushes the word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window; > "
        "0.0f: wrap at 'wrap_pos_x' position in window local space.");
  m.def("PopTextWrapPos", &ImGui::PopTextWrapPos, "Pops the last word-wrapping position pushed onto the stack.");
  m.def("GetFontSize", &ImGui::GetFontSize, "Returns the current font size in pixels, with the current scale applied.");
  m.def("GetFontTexUvWhitePixel", &ImGui::GetFontTexUvWhitePixel,
        "Returns the UV coordinate for a white pixel, useful for drawing custom shapes via the ImDrawList API.");
  m.def(
      "GetColorU32",
      [](ImGuiCol idx, float alpha_mul) {
        const auto res_ = ImGui::GetColorU32(idx, alpha_mul);
        return res_;
      },
      py::arg("idx"), py::arg("alpha_mul") = 1.0f,
      "Retrieves the style color specified by idx, with the style alpha applied and an optional extra alpha "
      "multiplier, packed as a 32-bit value suitable for ImDrawList.");
  m.def(
      "GetColorU32",
      [](const ImVec4& col) {
        const auto res_ = ImGui::GetColorU32(col);
        return res_;
      },
      py::arg("col"),
      "Retrieves the given color with the style alpha applied, packed as a 32-bit value suitable for ImDrawList.");
  m.def(
      "GetColorU32",
      [](ImU32 col, float alpha_mul) {
        const auto res_ = ImGui::GetColorU32(col, alpha_mul);
        return res_;
      },
      py::arg("col"), py::arg("alpha_mul") = 1.0f,
      "Retrieves the given color with the style alpha applied, packed as a 32-bit value suitable for ImDrawList.");
  m.def("GetStyleColorVec4", &ImGui::GetStyleColorVec4, py::arg("idx"),
        "Retrieves the style color as stored in the ImGuiStyle structure. Use this to feed back into PushStyleColor(), "
        "otherwise use GetColorU32() to get the style color with style alpha baked in.");
  m.def("GetCursorScreenPos", &ImGui::GetCursorScreenPos,
        "Returns the current cursor position in absolute screen coordinates. This is typically the best function to "
        "use for getting cursor position.");
  m.def("SetCursorScreenPos", &ImGui::SetCursorScreenPos, py::arg("pos"),
        "Sets the cursor position in absolute screen coordinates.");
  m.def("GetContentRegionAvail", &ImGui::GetContentRegionAvail,
        "Returns the available space from the current position. This is typically the best function to use for getting "
        "the available content region.");
  m.def("GetCursorPos", &ImGui::GetCursorPos, "Returns the current cursor position in window-local coordinates.");
  m.def("GetCursorPosX", &ImGui::GetCursorPosX,
        "Returns the X coordinate of the current cursor position in window-local coordinates.");
  m.def("GetCursorPosY", &ImGui::GetCursorPosY,
        "Returns the Y coordinate of the current cursor position in window-local coordinates.");
  m.def("SetCursorPos", &ImGui::SetCursorPos, py::arg("local_pos"),
        "Sets the cursor position in window-local coordinates.");
  m.def("SetCursorPosX", &ImGui::SetCursorPosX, py::arg("local_x"),
        "Sets the X coordinate of the cursor position in window-local coordinates.");
  m.def("SetCursorPosY", &ImGui::SetCursorPosY, py::arg("local_y"),
        "Sets the Y coordinate of the cursor position in window-local coordinates.");
  m.def("GetCursorStartPos", &ImGui::GetCursorStartPos,
        "Returns the initial cursor position in window-local coordinates. Call GetCursorScreenPos() after Begin() to "
        "get the absolute coordinates version.");
  m.def("Separator", &ImGui::Separator,
        "Creates a separator, generally horizontal. Inside a menu bar or in horizontal layout mode, this becomes a "
        "vertical separator.");
  m.def("SameLine", &ImGui::SameLine, py::arg("offset_from_start_x") = 0.0f, py::arg("spacing") = -1.0f,
        "Lays out widgets horizontally by undoing the last carriage return. The X position is given in window "
        "coordinates.");
  m.def("NewLine", &ImGui::NewLine, "Forces a new line when in a horizontal-layout context or undoes a SameLine().");
  m.def("Dummy", &ImGui::Dummy, py::arg("size"),
        "Adds a dummy item of the given size. Unlike InvisibleButton(), Dummy() won't take mouse clicks or be "
        "navigable.");
  m.def("Unindent", &ImGui::Unindent, py::arg("indent_w") = 0.0f,
        "Moves the content position back to the left by indent_w, or by style.IndentSpacing if indent_w <= 0.");
  m.def("BeginGroup", &ImGui::BeginGroup, "Locks the horizontal starting position for a group of items.");
  m.def("EndGroup", &ImGui::EndGroup,
        "Unlocks the horizontal starting position for a group of items and captures the whole group bounding box as "
        "one 'item.'");
  m.def("AlignTextToFramePadding", &ImGui::AlignTextToFramePadding,
        "Vertically aligns the upcoming text baseline to FramePadding.y, so that it aligns properly with regularly "
        "framed items.");
  m.def("GetTextLineHeight", &ImGui::GetTextLineHeight,
        "Returns the height of a text line, approximately equal to FontSize.");
  m.def("GetTextLineHeightWithSpacing", &ImGui::GetTextLineHeightWithSpacing,
        "Returns the height of a text line, including spacing. Approximately equal to FontSize + style.ItemSpacing.y.");
  m.def("GetFrameHeight", &ImGui::GetFrameHeight,
        "Returns the height of a frame, approximately equal to FontSize + style.FramePadding.y * 2.");
  m.def("GetFrameHeightWithSpacing", &ImGui::GetFrameHeightWithSpacing,
        "Returns the height of a frame, including spacing. Approximately equal to FontSize + style.FramePadding.y * 2 "
        "+ style.ItemSpacing.y.");
  m.def(
      "PushID", [](const char* str_id) { ImGui::PushID(str_id); }, py::arg("str_id"),
      "Pushes a string into the ID stack (will hash the string).");
  m.def(
      "PushID", [](const char* str_id_begin, const char* str_id_end) { ImGui::PushID(str_id_begin, str_id_end); },
      py::arg("str_id_begin"), py::arg("str_id_end"), "Pushes a substring into the ID stack (will hash the string).");
  m.def(
      "PushID", [](int int_id) { ImGui::PushID(int_id); }, py::arg("int_id"),
      "Pushes an integer into the ID stack (will hash the integer).");
  m.def(
      "GetID",
      [](const char* str_id) {
        const auto res_ = ImGui::GetID(str_id);
        return res_;
      },
      py::arg("str_id"),
      "Calculates a unique ID by hashing the entire ID stack with the given parameter. Useful for querying "
      "ImGuiStorage.");
  m.def(
      "GetID",
      [](const char* str_id_begin, const char* str_id_end) {
        const auto res_ = ImGui::GetID(str_id_begin, str_id_end);
        return res_;
      },
      py::arg("str_id_begin"), py::arg("str_id_end"),
      "Calculates a unique ID by hashing the entire ID stack with the given substring.");
  m.def(
      "GetID",
      [](int int_id) {
        const auto res_ = ImGui::GetID(int_id);
        return res_;
      },
      py::arg("int_id"), "Calculates a unique ID by hashing the entire ID stack with the given integer.");
  m.def("Text", [](const char* text) { ImGui::Text("%s", text); }, py::arg("text"), "Displays formatted text.");
  m.def(
      "TextColored", [](const ImVec4& col, const char* text) { ImGui::TextColored(col, "%s", text); }, py::arg("col"),
      py::arg("text"), "Displays formatted text with the specified color.");
  m.def(
      "TextDisabled", [](const char* text) { ImGui::TextDisabled("%s", text); }, py::arg("text"),
      "Displays formatted text in a disabled style (gray color).");
  m.def(
      "TextWrapped", [](const char* text) { ImGui::TextWrapped("%s", text); }, py::arg("text"),
      "Displays formatted text with word-wrapping enabled. The text will wrap at the end of the window or column by "
      "default.");
  m.def(
      "LabelText", [](const char* label, const char* text) { ImGui::LabelText(label, "%s", text); }, py::arg("label"),
      py::arg("text"), "Displays a label and value aligned in the same way as value+label widgets.");
  m.def(
      "BulletText", [](const char* text) { ImGui::BulletText("%s", text); }, py::arg("text"),
      "Displays a bullet followed by formatted text.");
  m.def("SeparatorText", &ImGui::SeparatorText, py::arg("label"),
        "Displays formatted text with a horizontal line separator.");
  m.def("Button", &ImGui::Button, py::arg("label"), py::arg("size") = ImVec2(0, 0),
        "Creates a button with the specified label and size. Returns true when the button is pressed.");
  m.def("SmallButton", &ImGui::SmallButton, py::arg("label"),
        "Creates a small button with the specified label. Useful for embedding within text.");
  m.def("InvisibleButton", &ImGui::InvisibleButton, py::arg("str_id"), py::arg("size"), py::arg("flags") = 0,
        "Creates an invisible button with flexible behavior, frequently used to build custom behaviors using the "
        "public API (along with IsItemActive, IsItemHovered, etc.).");
  m.def("ArrowButton", &ImGui::ArrowButton, py::arg("str_id"), py::arg("dir"),
        "Creates a square button with an arrow shape pointing in the specified direction.");
  m.def(
      "Checkbox",
      [](const char* label, bool v) {
        bool* v_ = &v;
        const auto res_ = ImGui::Checkbox(label, v_);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"),
      "Creates a checkbox with the specified label and boolean value. Returns true when the checkbox is clicked.");
  m.def(
      "CheckboxFlags",
      [](const char* label, int flags, int flags_value) {
        int* flags_ = &flags;
        const auto res_ = ImGui::CheckboxFlags(label, flags_, flags_value);
        return std::make_tuple(res_, flags);
      },
      py::arg("label"), py::arg("flags"), py::arg("flags_value"),
      "Creates a checkbox that toggles specific flags within an integer.");
  m.def(
      "RadioButton",
      [](const char* label, bool active) {
        const auto res_ = ImGui::RadioButton(label, active);
        return res_;
      },
      py::arg("label"), py::arg("active"), "Creates a radio button with the specified label and active state.");
  m.def(
      "RadioButton",
      [](const char* label, int v, int v_button) {
        int* v_ = &v;
        const auto res_ = ImGui::RadioButton(label, v_, v_button);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_button"),
      "Creates a radio button that sets the specified integer value when clicked.");
  m.def(
      "ProgressBar",
      [](float fraction, const ImVec2& size_arg, const std::optional<std::string>& overlay) {
        const char* overlay_ = overlay.has_value() ? overlay.value().c_str() : nullptr;
        ImGui::ProgressBar(fraction, size_arg, overlay_);
      },
      py::arg("fraction"), py::arg("size_arg") = ImVec2(-FLT_MIN, 0), py::arg("overlay") = std::nullopt,
      "Creates a progress bar with the specified fraction of completion, size, and optional overlay text.");
  m.def("Bullet", &ImGui::Bullet,
        "Draws a small circle and keeps the cursor on the same line. Advances cursor x position by "
        "GetTreeNodeToLabelSpacing(), the same distance that TreeNode() uses.");
  m.def("TextLink", &ImGui::TextLink, py::arg("label"),
        "Creates a hyperlink-style text button that returns true when clicked.");
  m.def(
      "TextLinkOpenURL",
      [](const char* label, const std::optional<std::string>& url) {
        const char* url_ = url.has_value() ? url.value().c_str() : nullptr;
        ImGui::TextLinkOpenURL(label, url_);
      },
      py::arg("label"), py::arg("url") = std::nullopt,
      "Creates a hyperlink-style text button that automatically opens the specified URL when clicked.");
  m.def("BeginCombo", &ImGui::BeginCombo, py::arg("label"), py::arg("preview_value"), py::arg("flags") = 0,
        "Begins a combo box (dropdown) with the specified label and preview value. Returns true if the combo box is "
        "open.");
  m.def("EndCombo", &ImGui::EndCombo, "Ends a combo box. Should only be called if BeginCombo() returns true.");
  m.def(
      "Combo",
      [](const char* label, int current_item, const std::vector<std::string>& items, int popup_max_height_in_items) {
        int* current_item_ = &current_item;
        const auto items_ = convert_string_items(items);
        const auto items_count = items_.size();
        const auto res_ = ImGui::Combo(label, current_item_, items_.data(), items_count, popup_max_height_in_items);
        return std::make_tuple(res_, current_item);
      },
      py::arg("label"), py::arg("current_item"), py::arg("items"), py::arg("popup_max_height_in_items") = -1,
      "Creates a combo box (dropdown) with the specified label, current item index, and items array. Returns true if "
      "the selection is changed.");
  m.def(
      "Combo",
      [](const char* label, int current_item, const char* items_separated_by_zeros, int popup_max_height_in_items) {
        int* current_item_ = &current_item;
        const auto res_ = ImGui::Combo(label, current_item_, items_separated_by_zeros, popup_max_height_in_items);
        return std::make_tuple(res_, current_item);
      },
      py::arg("label"), py::arg("current_item"), py::arg("items_separated_by_zeros"),
      py::arg("popup_max_height_in_items") = -1,
      "Creates a combo box (dropdown) with items separated by null characters. Returns true if the selection is "
      "changed.");
  m.def(
      "DragFloat",
      [](const char* label, float v, float v_speed, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        float* v_ = &v;
        const auto res_ = ImGui::DragFloat(label, v_, v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0.0f, py::arg("v_max") = 0.0f,
      py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a draggable float slider with the specified label, value, speed, minimum/maximum values, format string, "
      "and optional flags. Returns true if the value is changed.");
  m.def(
      "DragFloat2",
      [](const char* label, std::array<float, 2> v, float v_speed, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragFloat2(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0.0f, py::arg("v_max") = 0.0f,
      py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a draggable float2 slider with the specified label, value, speed, minimum/maximum values, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "DragFloat3",
      [](const char* label, std::array<float, 3> v, float v_speed, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragFloat3(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0.0f, py::arg("v_max") = 0.0f,
      py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a draggable float3 slider with the specified label, value, speed, minimum/maximum values, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "DragFloat4",
      [](const char* label, std::array<float, 4> v, float v_speed, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragFloat4(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0.0f, py::arg("v_max") = 0.0f,
      py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a draggable float4 slider with the specified label, value, speed, minimum/maximum values, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "DragFloatRange2",
      [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max,
         const char* format, const std::optional<std::string>& format_max, ImGuiSliderFlags flags) {
        float* v_current_min_ = &v_current_min;
        float* v_current_max_ = &v_current_max;
        const char* format_max_ = format_max.has_value() ? format_max.value().c_str() : nullptr;
        const auto res_ = ImGui::DragFloatRange2(label, v_current_min_, v_current_max_, v_speed, v_min, v_max, format,
                                                 format_max_, flags);
        return std::make_tuple(res_, v_current_min, v_current_max);
      },
      py::arg("label"), py::arg("v_current_min"), py::arg("v_current_max"), py::arg("v_speed") = 1.0f,
      py::arg("v_min") = 0.0f, py::arg("v_max") = 0.0f, py::arg("format") = "%.3f",
      py::arg("format_max") = std::nullopt, py::arg("flags") = 0,
      "Creates a draggable float range slider with the specified label, current min/max values, speed, minimum/maximum "
      "values, format strings, and optional flags. Returns true if the values are changed.");
  m.def(
      "DragInt",
      [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
        int* v_ = &v;
        const auto res_ = ImGui::DragInt(label, v_, v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0, py::arg("v_max") = 0,
      py::arg("format") = "%d", py::arg("flags") = 0,
      "Creates a draggable integer slider with the specified label, value, speed, minimum/maximum values, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "DragInt2",
      [](const char* label, std::array<int, 2> v, float v_speed, int v_min, int v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragInt2(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0, py::arg("v_max") = 0,
      py::arg("format") = "%d", py::arg("flags") = 0,
      "Creates a draggable int2 slider with the specified label, value, speed, minimum/maximum values, format string, "
      "and optional flags. Returns true if the value is changed.");
  m.def(
      "DragInt3",
      [](const char* label, std::array<int, 3> v, float v_speed, int v_min, int v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragInt3(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0, py::arg("v_max") = 0,
      py::arg("format") = "%d", py::arg("flags") = 0,
      "Creates a draggable int3 slider with the specified label, value, speed, minimum/maximum values, format string, "
      "and optional flags. Returns true if the value is changed.");
  m.def(
      "DragInt4",
      [](const char* label, std::array<int, 4> v, float v_speed, int v_min, int v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::DragInt4(label, v.data(), v_speed, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_speed") = 1.0f, py::arg("v_min") = 0, py::arg("v_max") = 0,
      py::arg("format") = "%d", py::arg("flags") = 0,
      "Creates a draggable int4 slider with the specified label, value, speed, minimum/maximum values, format string, "
      "and optional flags. Returns true if the value is changed.");
  m.def(
      "DragIntRange2",
      [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max,
         const char* format, const std::optional<std::string>& format_max, ImGuiSliderFlags flags) {
        int* v_current_min_ = &v_current_min;
        int* v_current_max_ = &v_current_max;
        const char* format_max_ = format_max.has_value() ? format_max.value().c_str() : nullptr;
        const auto res_ = ImGui::DragIntRange2(label, v_current_min_, v_current_max_, v_speed, v_min, v_max, format,
                                               format_max_, flags);
        return std::make_tuple(res_, v_current_min, v_current_max);
      },
      py::arg("label"), py::arg("v_current_min"), py::arg("v_current_max"), py::arg("v_speed") = 1.0f,
      py::arg("v_min") = 0, py::arg("v_max") = 0, py::arg("format") = "%d", py::arg("format_max") = std::nullopt,
      py::arg("flags") = 0,
      "Creates a draggable integer range slider with the specified label, current min/max values, speed, "
      "minimum/maximum values, format strings, and optional flags. Returns true if the values are changed.");
  m.def(
      "SliderFloat",
      [](const char* label, float v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) {
        float* v_ = &v;
        const auto res_ = ImGui::SliderFloat(label, v_, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a slider for floating-point values with the specified label, value, min/max range, format string, and "
      "optional flags. Returns true if the value is changed.");
  m.def(
      "SliderFloat2",
      [](const char* label, std::array<float, 2> v, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderFloat2(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a slider for two floating-point values with the specified label, values, min/max range, format string, "
      "and optional flags. Returns true if the values are changed.");
  m.def(
      "SliderFloat3",
      [](const char* label, std::array<float, 3> v, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderFloat3(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a slider for three floating-point values with the specified label, values, min/max range, format "
      "string, and optional flags. Returns true if the values are changed.");
  m.def(
      "SliderFloat4",
      [](const char* label, std::array<float, 4> v, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderFloat4(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a slider for four floating-point values with the specified label, values, min/max range, format string, "
      "and optional flags. Returns true if the values are changed.");
  m.def(
      "SliderAngle",
      [](const char* label, float v_rad, float v_degrees_min, float v_degrees_max, const char* format,
         ImGuiSliderFlags flags) {
        float* v_rad_ = &v_rad;
        const auto res_ = ImGui::SliderAngle(label, v_rad_, v_degrees_min, v_degrees_max, format, flags);
        return std::make_tuple(res_, v_rad);
      },
      py::arg("label"), py::arg("v_rad"), py::arg("v_degrees_min") = -360.0f, py::arg("v_degrees_max") = +360.0f,
      py::arg("format") = "%.0f deg", py::arg("flags") = 0,
      "Creates a slider for angles with the specified label, value in radians, min/max range in degrees, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "SliderInt",
      [](const char* label, int v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
        int* v_ = &v;
        const auto res_ = ImGui::SliderInt(label, v_, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%d",
      py::arg("flags") = 0,
      "Creates a slider for integer values with the specified label, value, min/max range, format string, and optional "
      "flags. Returns true if the value is changed.");
  m.def(
      "SliderInt2",
      [](const char* label, std::array<int, 2> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderInt2(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%d",
      py::arg("flags") = 0,
      "Creates a slider for two integer values with the specified label, values, min/max range, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "SliderInt3",
      [](const char* label, std::array<int, 3> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderInt3(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%d",
      py::arg("flags") = 0,
      "Creates a slider for three integer values with the specified label, values, min/max range, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "SliderInt4",
      [](const char* label, std::array<int, 4> v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) {
        const auto res_ = ImGui::SliderInt4(label, v.data(), v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%d",
      py::arg("flags") = 0,
      "Creates a slider for four integer values with the specified label, values, min/max range, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "VSliderFloat",
      [](const char* label, const ImVec2& size, float v, float v_min, float v_max, const char* format,
         ImGuiSliderFlags flags) {
        float* v_ = &v;
        const auto res_ = ImGui::VSliderFloat(label, size, v_, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("size"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a vertical slider for floating-point values with the specified label, size, value, min/max range, "
      "format string, and optional flags. Returns true if the value is changed.");
  m.def(
      "VSliderInt",
      [](const char* label, const ImVec2& size, int v, int v_min, int v_max, const char* format,
         ImGuiSliderFlags flags) {
        int* v_ = &v;
        const auto res_ = ImGui::VSliderInt(label, size, v_, v_min, v_max, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("size"), py::arg("v"), py::arg("v_min"), py::arg("v_max"), py::arg("format") = "%d",
      py::arg("flags") = 0,
      "Creates a vertical slider for integer values with the specified label, size, value, min/max range, format "
      "string, and optional flags. Returns true if the value is changed.");
  m.def(
      "InputText",
      [](const char* label, const std::string& str, ImGuiInputTextFlags flags) {
        auto str_ = str;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputText(label, &str_, flags);
        return std::make_tuple(res_, str_);
      },
      py::arg("label"), py::arg("str"), py::arg("flags") = 0,
      "Creates a text input field with the specified label, buffer, buffer size, optional flags, callback, and user "
      "data. Returns true if the text is changed.");
  m.def(
      "InputTextMultiline",
      [](const char* label, const std::string& str, const ImVec2& size, ImGuiInputTextFlags flags) {
        auto str_ = str;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputTextMultiline(label, &str_, size, flags);
        return std::make_tuple(res_, str_);
      },
      py::arg("label"), py::arg("str"), py::arg("size") = ImVec2(0, 0), py::arg("flags") = 0,
      "Creates a multiline text input field with the specified label, buffer, buffer size, size, optional flags, "
      "callback, and user data. Returns true if the text is changed.");
  m.def(
      "InputTextWithHint",
      [](const char* label, const char* hint, const std::string& str, ImGuiInputTextFlags flags) {
        auto str_ = str;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputTextWithHint(label, hint, &str_, flags);
        return std::make_tuple(res_, str_);
      },
      py::arg("label"), py::arg("hint"), py::arg("str"), py::arg("flags") = 0,
      "Creates a text input field with a hint, using the specified label, hint, buffer, buffer size, optional flags, "
      "callback, and user data. Returns true if the text is changed.");
  m.def(
      "InputFloat",
      [](const char* label, float v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags) {
        float* v_ = &v;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputFloat(label, v_, step, step_fast, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("step") = 0.0f, py::arg("step_fast") = 0.0f, py::arg("format") = "%.3f",
      py::arg("flags") = 0,
      "Creates a text input field for floating-point values with the specified label, value, optional step, fast step, "
      "format string, and flags. Returns true if the value is changed.");
  m.def(
      "InputFloat2",
      [](const char* label, std::array<float, 2> v, const char* format, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputFloat2(label, v.data(), format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a text input field for two floating-point values with the specified label, values, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "InputFloat3",
      [](const char* label, std::array<float, 3> v, const char* format, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputFloat3(label, v.data(), format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a text input field for three floating-point values with the specified label, values, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "InputFloat4",
      [](const char* label, std::array<float, 4> v, const char* format, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputFloat4(label, v.data(), format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("format") = "%.3f", py::arg("flags") = 0,
      "Creates a text input field for four floating-point values with the specified label, values, format string, and "
      "optional flags. Returns true if the values are changed.");
  m.def(
      "InputInt",
      [](const char* label, int v, int step, int step_fast, ImGuiInputTextFlags flags) {
        int* v_ = &v;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputInt(label, v_, step, step_fast, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("step") = 1, py::arg("step_fast") = 100, py::arg("flags") = 0,
      "Creates a text input field for integer values with the specified label, value, optional step, fast step, and "
      "flags. Returns true if the value is changed.");
  m.def(
      "InputInt2",
      [](const char* label, std::array<int, 2> v, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputInt2(label, v.data(), flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("flags") = 0,
      "Creates a text input field for two integer values with the specified label, values, and optional flags. Returns "
      "true if the values are changed.");
  m.def(
      "InputInt3",
      [](const char* label, std::array<int, 3> v, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputInt3(label, v.data(), flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("flags") = 0,
      "Creates a text input field for three integer values with the specified label, values, and optional flags. "
      "Returns true if the values are changed.");
  m.def(
      "InputInt4",
      [](const char* label, std::array<int, 4> v, ImGuiInputTextFlags flags) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputInt4(label, v.data(), flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("flags") = 0,
      "Creates a text input field for four integer values with the specified label, values, and optional flags. "
      "Returns true if the values are changed.");
  m.def(
      "InputDouble",
      [](const char* label, double v, double step, double step_fast, const char* format, ImGuiInputTextFlags flags) {
        double* v_ = &v;

        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        const auto res_ = ImGui::InputDouble(label, v_, step, step_fast, format, flags);
        return std::make_tuple(res_, v);
      },
      py::arg("label"), py::arg("v"), py::arg("step") = 0.0, py::arg("step_fast") = 0.0, py::arg("format") = "%.6f",
      py::arg("flags") = 0,
      "Creates a text input field for double values with the specified label, value, optional step, fast step, format "
      "string, and flags. Returns true if the value is changed.");
  m.def(
      "ColorEdit3",
      [](const char* label, std::array<float, 3> col, ImGuiColorEditFlags flags) {
        const auto res_ = ImGui::ColorEdit3(label, col.data(), flags);
        return std::make_tuple(res_, col);
      },
      py::arg("label"), py::arg("col"), py::arg("flags") = 0,
      "Edits an RGB color value with an optional set of flags. Returns true if the color was changed.");
  m.def(
      "ColorEdit4",
      [](const char* label, std::array<float, 4> col, ImGuiColorEditFlags flags) {
        const auto res_ = ImGui::ColorEdit4(label, col.data(), flags);
        return std::make_tuple(res_, col);
      },
      py::arg("label"), py::arg("col"), py::arg("flags") = 0,
      "Edits an RGBA color value with an optional set of flags. Returns true if the color was changed.");
  m.def(
      "ColorPicker3",
      [](const char* label, std::array<float, 3> col, ImGuiColorEditFlags flags) {
        const auto res_ = ImGui::ColorPicker3(label, col.data(), flags);
        return std::make_tuple(res_, col);
      },
      py::arg("label"), py::arg("col"), py::arg("flags") = 0,
      "Displays a color picker for an RGB color value with an optional set of flags. Returns true if the color was "
      "changed.");
  m.def(
      "ColorPicker4",
      [](const char* label, std::array<float, 4> col, ImGuiColorEditFlags flags,
         const std::optional<std::array<float, 4>>& ref_col) {
        const float* ref_col_ = ref_col ? &ref_col.value()[0] : nullptr;
        const auto res_ = ImGui::ColorPicker4(label, col.data(), flags, ref_col_);
        return std::make_tuple(res_, col);
      },
      py::arg("label"), py::arg("col"), py::arg("flags") = 0, py::arg("ref_col") = std::nullopt,
      "Displays a color picker for an RGBA color value with an optional set of flags and reference color. Returns true "
      "if the color was changed.");
  m.def("ColorButton", &ImGui::ColorButton, py::arg("desc_id"), py::arg("col"), py::arg("flags") = 0,
        py::arg("size") = ImVec2(0, 0),
        "Displays a color square/button with the specified color, size, and flags. Returns true if the button was "
        "pressed.");
  m.def("SetColorEditOptions", &ImGui::SetColorEditOptions, py::arg("flags"),
        "Sets the color edit options, typically called during application startup. Allows selecting a default format, "
        "picker type, etc.");
  m.def(
      "TreeNode",
      [](const char* label) {
        const auto res_ = ImGui::TreeNode(label);
        return res_;
      },
      py::arg("label"),
      "Creates a tree node with the specified label. Returns true if the node is open, in which case TreePop() should "
      "be called to close it.");
  m.def(
      "TreeNodeEx",
      [](const char* label, ImGuiTreeNodeFlags flags) {
        const auto res_ = ImGui::TreeNodeEx(label, flags);
        return res_;
      },
      py::arg("label"), py::arg("flags") = 0,
      "Creates an extended tree node with the specified label and flags. Returns true if the node is open.");
  m.def(
      "TreePush", [](const char* str_id) { ImGui::TreePush(str_id); }, py::arg("str_id"),
      "Pushes a string into the tree node stack, increasing the indentation level.");
  m.def("TreePop", &ImGui::TreePop,
        "Pops the last element from the tree node stack, decreasing the indentation level.");
  m.def("GetTreeNodeToLabelSpacing", &ImGui::GetTreeNodeToLabelSpacing,
        "Returns the horizontal distance preceding the label when using TreeNode() or Bullet().");
  m.def(
      "CollapsingHeader",
      [](const char* label, ImGuiTreeNodeFlags flags) {
        const auto res_ = ImGui::CollapsingHeader(label, flags);
        return res_;
      },
      py::arg("label"), py::arg("flags") = 0,
      "Creates a collapsible header with the specified label and flags. Returns true if the header is open.");
  m.def(
      "CollapsingHeader",
      [](const char* label, bool p_visible, ImGuiTreeNodeFlags flags) {
        bool* p_visible_ = &p_visible;
        const auto res_ = ImGui::CollapsingHeader(label, p_visible_, flags);
        return std::make_tuple(res_, p_visible);
      },
      py::arg("label"), py::arg("p_visible"), py::arg("flags") = 0,
      "Creates a collapsible header with the specified label, visibility flag, and flags. Returns true if the header "
      "is open.");
  m.def("SetNextItemOpen", &ImGui::SetNextItemOpen, py::arg("is_open"), py::arg("cond") = 0,
        "Sets the next TreeNode or CollapsingHeader open state.");
  m.def(
      "Selectable",
      [](const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size) {
        const auto res_ = ImGui::Selectable(label, selected, flags, size);
        return res_;
      },
      py::arg("label"), py::arg("selected") = false, py::arg("flags") = 0, py::arg("size") = ImVec2(0, 0),
      "Creates a selectable item with the specified label, selection state, flags, and size. Returns true if the item "
      "is clicked.");
  m.def(
      "Selectable",
      [](const char* label, bool p_selected, ImGuiSelectableFlags flags, const ImVec2& size) {
        bool* p_selected_ = &p_selected;
        const auto res_ = ImGui::Selectable(label, p_selected_, flags, size);
        return std::make_tuple(res_, p_selected);
      },
      py::arg("label"), py::arg("p_selected"), py::arg("flags") = 0, py::arg("size") = ImVec2(0, 0),
      "Creates a selectable item with the specified label, pointer to the selection state, flags, and size. Returns "
      "true if the item is clicked.");
  m.def("IsItemToggledSelection", &ImGui::IsItemToggledSelection,
        "Checks if the selection state of the last item was toggled. Useful for retrieving per-item information before "
        "reaching EndMultiSelect.");
  m.def("BeginListBox", &ImGui::BeginListBox, py::arg("label"), py::arg("size") = ImVec2(0, 0),
        "Opens a framed scrolling region for a list box with the specified label and size.");
  m.def("EndListBox", &ImGui::EndListBox,
        "Ends the list box opened by BeginListBox. Should be called only if BeginListBox returned true.");
  m.def(
      "ListBox",
      [](const char* label, int current_item, const std::vector<std::string>& items, int items_count,
         int height_in_items) {
        int* current_item_ = &current_item;
        const auto items_ = convert_string_items(items);
        const auto res_ = ImGui::ListBox(label, current_item_, items_.data(), items_count, height_in_items);
        return std::make_tuple(res_, current_item);
      },
      py::arg("label"), py::arg("current_item"), py::arg("items"), py::arg("items_count"),
      py::arg("height_in_items") = -1,
      "Displays a list box with the specified label, current item index, items array, item count, and optional height "
      "in items. Returns true if the current item was changed.");
  m.def(
      "Value", [](const char* prefix, bool b) { ImGui::Value(prefix, b); }, py::arg("prefix"), py::arg("b"),
      "Displays a boolean value with a prefix in the format \"prefix: value\".");
  m.def(
      "Value", [](const char* prefix, int v) { ImGui::Value(prefix, v); }, py::arg("prefix"), py::arg("v"),
      "Displays an integer value with a prefix in the format \"prefix: value\".");
  m.def(
      "Value",
      [](const char* prefix, float v, const std::optional<std::string>& float_format) {
        const char* float_format_ = float_format.has_value() ? float_format.value().c_str() : nullptr;
        ImGui::Value(prefix, v, float_format_);
      },
      py::arg("prefix"), py::arg("v"), py::arg("float_format") = std::nullopt,
      "Displays a floating-point value with a prefix in the format \"prefix: value\". Optionally specify the format "
      "for the float.");
  m.def("BeginMenuBar", &ImGui::BeginMenuBar,
        "Appends to the menu bar of the current window. Requires ImGuiWindowFlags_MenuBar flag to be set on the parent "
        "window.");
  m.def("EndMenuBar", &ImGui::EndMenuBar, "Ends the menu bar. Should be called only if BeginMenuBar() returned true.");
  m.def("BeginMainMenuBar", &ImGui::BeginMainMenuBar, "Creates and appends to a full-screen menu bar.");
  m.def("EndMainMenuBar", &ImGui::EndMainMenuBar,
        "Ends the main menu bar. Should be called only if BeginMainMenuBar() returned true.");
  m.def("BeginMenu", &ImGui::BeginMenu, py::arg("label"), py::arg("enabled") = true,
        "Creates a sub-menu entry. Should call EndMenu() if this returns true.");
  m.def("EndMenu", &ImGui::EndMenu,
        "Ends the menu created by BeginMenu(). Should be called only if BeginMenu() returned true.");
  m.def(
      "MenuItem",
      [](const char* label, const std::optional<std::string>& shortcut, bool selected, bool enabled) {
        const char* shortcut_ = shortcut.has_value() ? shortcut.value().c_str() : nullptr;
        const auto res_ = ImGui::MenuItem(label, shortcut_, selected, enabled);
        return res_;
      },
      py::arg("label"), py::arg("shortcut") = std::nullopt, py::arg("selected") = false, py::arg("enabled") = true,
      "Creates a menu item with an optional shortcut, selection state, and enabled state. Returns true when "
      "activated.");
  m.def(
      "MenuItem",
      [](const char* label, const char* shortcut, bool p_selected, bool enabled) {
        bool* p_selected_ = &p_selected;
        const auto res_ = ImGui::MenuItem(label, shortcut, p_selected_, enabled);
        return std::make_tuple(res_, p_selected);
      },
      py::arg("label"), py::arg("shortcut"), py::arg("p_selected"), py::arg("enabled") = true,
      "Creates a menu item with an optional shortcut and enabled state, and toggles the selection state if p_selected "
      "is not NULL. Returns true when activated.");
  m.def("BeginTooltip", &ImGui::BeginTooltip,
        "Begins a tooltip window. Should call EndTooltip() if this returns true.");
  m.def("EndTooltip", &ImGui::EndTooltip,
        "Ends the tooltip window. Should be called only if BeginTooltip() or BeginItemTooltip() returned true.");
  m.def(
      "SetTooltip", [](const char* text) { ImGui::SetTooltip("%s", text); }, py::arg("text"),
      "Sets a text-only tooltip. Often used after a call to ImGui::IsItemHovered().");
  m.def("BeginItemTooltip", &ImGui::BeginItemTooltip,
        "Begins a tooltip window if the preceding item was hovered. Should call EndTooltip() if this returns true.");
  m.def(
      "SetItemTooltip", [](const char* text) { ImGui::SetItemTooltip("%s", text); }, py::arg("text"),
      "Sets a text-only tooltip if the preceding item was hovered.");
  m.def("BeginPopup", &ImGui::BeginPopup, py::arg("str_id"), py::arg("flags") = 0,
        "Begins a popup window with the specified ID and flags. Should call EndPopup() if this returns true.");
  m.def(
      "BeginPopupModal",
      [](const char* name, std::optional<bool> open, ImGuiWindowFlags flags) {
        bool* p_open = open.has_value() ? &open.value() : nullptr;
        const auto res_ = ImGui::BeginPopupModal(name, p_open, flags);
        return std::make_tuple(res_, open);
      },
      py::arg("name"), py::arg("open") = std::nullopt, py::arg("flags") = 0,
      "Begins a modal popup window with the specified name and flags. Should call EndPopup() if this returns true.");
  m.def("EndPopup", &ImGui::EndPopup,
        "Ends a popup window. Should be called only if BeginPopup() or BeginPopupModal() returned true.");
  m.def(
      "OpenPopup", [](const char* str_id, ImGuiPopupFlags popup_flags) { ImGui::OpenPopup(str_id, popup_flags); },
      py::arg("str_id"), py::arg("popup_flags") = 0, "Marks the popup as open. Should not be called every frame.");
  m.def(
      "OpenPopup", [](ImGuiID id, ImGuiPopupFlags popup_flags) { ImGui::OpenPopup(id, popup_flags); }, py::arg("id"),
      py::arg("popup_flags") = 0,
      "Marks the popup with the specified ID as open, facilitating calling from nested stacks.");
  m.def(
      "OpenPopupOnItemClick",
      [](const std::optional<std::string>& str_id, ImGuiPopupFlags popup_flags) {
        const char* str_id_ = str_id.has_value() ? str_id.value().c_str() : nullptr;
        ImGui::OpenPopupOnItemClick(str_id_, popup_flags);
      },
      py::arg("str_id") = std::nullopt, py::arg("popup_flags") = 1,
      "Helper to open a popup when clicked on the last item. Defaults to right mouse button click.");
  m.def("CloseCurrentPopup", &ImGui::CloseCurrentPopup, "Manually closes the current popup.");
  m.def(
      "BeginPopupContextItem",
      [](const std::optional<std::string>& str_id, ImGuiPopupFlags popup_flags) {
        const char* str_id_ = str_id.has_value() ? str_id.value().c_str() : nullptr;
        const auto res_ = ImGui::BeginPopupContextItem(str_id_, popup_flags);
        return res_;
      },
      py::arg("str_id") = std::nullopt, py::arg("popup_flags") = 1,
      "Opens and begins a popup when clicked on the last item. Returns true if the popup is open.");
  m.def(
      "BeginPopupContextWindow",
      [](const std::optional<std::string>& str_id, ImGuiPopupFlags popup_flags) {
        const char* str_id_ = str_id.has_value() ? str_id.value().c_str() : nullptr;
        const auto res_ = ImGui::BeginPopupContextWindow(str_id_, popup_flags);
        return res_;
      },
      py::arg("str_id") = std::nullopt, py::arg("popup_flags") = 1,
      "Opens and begins a popup when clicked on the current window. Returns true if the popup is open.");
  m.def(
      "BeginPopupContextVoid",
      [](const std::optional<std::string>& str_id, ImGuiPopupFlags popup_flags) {
        const char* str_id_ = str_id.has_value() ? str_id.value().c_str() : nullptr;
        const auto res_ = ImGui::BeginPopupContextVoid(str_id_, popup_flags);
        return res_;
      },
      py::arg("str_id") = std::nullopt, py::arg("popup_flags") = 1,
      "Opens and begins a popup when clicked in a void area (where there are no windows). Returns true if the popup is "
      "open.");
  m.def("IsPopupOpen", &ImGui::IsPopupOpen, py::arg("str_id"), py::arg("flags") = 0,
        "Returns true if the popup with the specified ID is open.");
  m.def("BeginTable", &ImGui::BeginTable, py::arg("str_id"), py::arg("columns"), py::arg("flags") = 0,
        py::arg("outer_size") = ImVec2(0.0f, 0.0f), py::arg("inner_width") = 0.0f,
        "Begins a table with the specified number of columns and options. Returns true if the table is successfully "
        "created.");
  m.def("EndTable", &ImGui::EndTable,
        "Ends the table created by BeginTable(). Should be called only if BeginTable() returned true.");
  m.def("TableNextColumn", &ImGui::TableNextColumn,
        "Appends into the next column (or the first column of the next row if currently in the last column). Returns "
        "true when the column is visible.");
  m.def("TableSetColumnIndex", &ImGui::TableSetColumnIndex, py::arg("column_n"),
        "Sets the current column index for the next item in the table.");
  m.def(
      "TableSetupColumn", &ImGui::TableSetupColumn, py::arg("label"), py::arg("flags") = 0,
      py::arg("init_width_or_weight") = 0.0f, py::arg("user_id") = 0,
      "Sets up a column in a table. You can provide a label, flags, initial width or weight, and an optional user ID.");
  m.def("TableSetupScrollFreeze", &ImGui::TableSetupScrollFreeze, py::arg("cols"), py::arg("rows"),
        "Freezes the specified number of columns and rows, keeping them visible when the table is scrolled.");
  m.def("TableHeader", &ImGui::TableHeader, py::arg("label"), "Submits a single header cell manually, rarely used.");
  m.def("TableHeadersRow", &ImGui::TableHeadersRow,
        "Submits a row with header cells based on data provided to TableSetupColumn(). Also submits the context menu.");
  m.def("TableAngledHeadersRow", &ImGui::TableAngledHeadersRow,
        "Submits a row with angled headers for columns marked with the ImGuiTableColumnFlags_AngledHeader flag. This "
        "must be the first row.");
  m.def("TableGetColumnCount", &ImGui::TableGetColumnCount, "Returns the number of columns in the current table.");
  m.def("TableGetColumnIndex", &ImGui::TableGetColumnIndex, "Returns the current column index.");
  m.def("TableGetRowIndex", &ImGui::TableGetRowIndex, "Returns the current row index.");
  m.def("TableGetColumnName", &ImGui::TableGetColumnName, py::arg("column_n") = -1,
        "Returns the name of the column specified by column_n. Pass -1 to use the current column.");
  m.def("TableGetColumnFlags", &ImGui::TableGetColumnFlags, py::arg("column_n") = -1,
        "Returns the flags associated with the specified column, or the current column if column_n is -1.");
  m.def("TableSetColumnEnabled", &ImGui::TableSetColumnEnabled, py::arg("column_n"), py::arg("v"),
        "Changes the enabled/disabled state of a column. Set to false to hide the column.");
  m.def("TableGetHoveredColumn", &ImGui::TableGetHoveredColumn,
        "Returns the index of the hovered column, or -1 if no column is hovered.");
  m.def("TableSetBgColor", &ImGui::TableSetBgColor, py::arg("target"), py::arg("color"), py::arg("column_n") = -1,
        "Sets the background color for a cell, row, or column. See ImGuiTableBgTarget_ flags for details.");
  m.def(
      "Columns",
      [](int count, const std::optional<std::string>& id, bool border) {
        const char* id_ = id.has_value() ? id.value().c_str() : nullptr;
        ImGui::Columns(count, id_, border);
      },
      py::arg("count") = 1, py::arg("id") = std::nullopt, py::arg("border") = true,
      "Legacy columns API. Sets up a number of columns. Use Tables instead for new implementations.");
  m.def("NextColumn", &ImGui::NextColumn,
        "Moves to the next column in the current row, or to the first column of the next row if the current row is "
        "finished.");
  m.def("GetColumnIndex", &ImGui::GetColumnIndex, "Returns the current column index in the legacy Columns API.");
  m.def("GetColumnWidth", &ImGui::GetColumnWidth, py::arg("column_index") = -1,
        "Returns the width of the specified column in pixels, or the current column if column_index is -1.");
  m.def("SetColumnWidth", &ImGui::SetColumnWidth, py::arg("column_index"), py::arg("width"),
        "Sets the width of the specified column in pixels.");
  m.def("GetColumnOffset", &ImGui::GetColumnOffset, py::arg("column_index") = -1,
        "Gets the position of the column line in pixels from the left side of the content region.");
  m.def("SetColumnOffset", &ImGui::SetColumnOffset, py::arg("column_index"), py::arg("offset_x"),
        "Sets the position of the column line in pixels from the left side of the content region.");
  m.def("GetColumnsCount", &ImGui::GetColumnsCount, "Returns the number of columns in the legacy Columns API.");
  m.def("BeginTabBar", &ImGui::BeginTabBar, py::arg("str_id"), py::arg("flags") = 0,
        "Begins a tab bar. Returns true if the tab bar is successfully created.");
  m.def("EndTabBar", &ImGui::EndTabBar,
        "Ends the tab bar created by BeginTabBar(). Should be called only if BeginTabBar() returned true.");
  m.def(
      "BeginTabItem",
      [](const char* label, std::optional<bool> open, ImGuiTabItemFlags flags) {
        bool* p_open = open.has_value() ? &open.value() : nullptr;
        const auto res_ = ImGui::BeginTabItem(label, p_open, flags);
        return std::make_tuple(res_, open);
      },
      py::arg("label"), py::arg("open") = std::nullopt, py::arg("flags") = 0,
      "Begins a tab item. Returns true if the tab is selected.");
  m.def("EndTabItem", &ImGui::EndTabItem,
        "Ends the tab item created by BeginTabItem(). Should be called only if BeginTabItem() returned true.");
  m.def("TabItemButton", &ImGui::TabItemButton, py::arg("label"), py::arg("flags") = 0,
        "Creates a tab that behaves like a button. Returns true when clicked.");
  m.def("SetTabItemClosed", &ImGui::SetTabItemClosed, py::arg("tab_or_docked_window_label"),
        "Notifies the TabBar or Docking system of a closed tab or window ahead of time. This is useful to reduce "
        "visual flicker on reorderable tab bars.");
  m.def("LogToTTY", &ImGui::LogToTTY, py::arg("auto_open_depth") = -1,
        "Starts logging output to the terminal (stdout).");
  m.def(
      "LogToFile",
      [](int auto_open_depth, const std::optional<std::string>& filename) {
        const char* filename_ = filename.has_value() ? filename.value().c_str() : nullptr;
        ImGui::LogToFile(auto_open_depth, filename_);
      },
      py::arg("auto_open_depth") = -1, py::arg("filename") = std::nullopt,
      "Starts logging output to a file. If filename is NULL, the log is written to 'imgui_log.txt'.");
  m.def("LogToClipboard", &ImGui::LogToClipboard, py::arg("auto_open_depth") = -1,
        "Starts logging output to the OS clipboard.");
  m.def("LogFinish", &ImGui::LogFinish, "Stops logging and closes any file or clipboard output.");
  m.def("LogButtons", &ImGui::LogButtons, "Helper function to display buttons for logging to tty, file, or clipboard.");
  m.def(
      "LogText", [](const char* text) { ImGui::LogText("%s", text); }, py::arg("text"),
      "Logs formatted text directly to the current log output without displaying it on the screen.");
  m.def("BeginDragDropSource", &ImGui::BeginDragDropSource, py::arg("flags") = 0,
        "Starts a drag-and-drop source. If this returns true, you should call SetDragDropPayload() and "
        "EndDragDropSource().");
  m.def(
      "SetDragDropPayload",
      [](const char* type, py::bytes& data, ImGuiCond cond) {
        void* data_ = PyBytes_AsString(data.ptr());
        const auto data_size = PyBytes_Size(data.ptr());
        const auto res_ = ImGui::SetDragDropPayload(type, data_, data_size, cond);
        return res_;
      },
      py::arg("type"), py::arg("data"), py::arg("cond") = 0,
      "Sets the payload data for the current drag-and-drop operation. The type is a user-defined string.");
  m.def("EndDragDropSource", &ImGui::EndDragDropSource,
        "Ends a drag-and-drop source operation. Should be called only if BeginDragDropSource() returns true.");
  m.def("BeginDragDropTarget", &ImGui::BeginDragDropTarget,
        "Marks an item as a possible drag-and-drop target. If this returns true, you can call AcceptDragDropPayload() "
        "and EndDragDropTarget().");
  m.def(
      "AcceptDragDropPayload",
      [](const char* type, ImGuiDragDropFlags flags) {
        const auto* payload = ImGui::AcceptDragDropPayload(type, flags);
        return py::bytes(static_cast<const char*>(payload->Data), payload->DataSize);
      },
      py::arg("type"), py::arg("flags") = 0,
      "Accepts the drag-and-drop payload if it matches the specified type. Returns the payload data if accepted.");
  m.def("EndDragDropTarget", &ImGui::EndDragDropTarget,
        "Ends a drag-and-drop target operation. Should be called only if BeginDragDropTarget() returns true.");
  m.def(
      "GetDragDropPayload",
      []() {
        const auto* payload = ImGui::GetDragDropPayload();
        return py::bytes(static_cast<const char*>(payload->Data), payload->DataSize);
      },
      "Peeks directly into the current drag-and-drop payload from anywhere. Returns NULL if drag-and-drop is "
      "inactive.");
  m.def("BeginDisabled", &ImGui::BeginDisabled, py::arg("disabled") = true,
        "Disables user interactions and dims item visuals. Can be nested.");
  m.def("EndDisabled", &ImGui::EndDisabled, "Ends the disabled section started by BeginDisabled().");
  m.def("PushClipRect", &ImGui::PushClipRect, py::arg("clip_rect_min"), py::arg("clip_rect_max"),
        py::arg("intersect_with_current_clip_rect"),
        "Pushes a clipping rectangle onto the stack. Mouse hovering is affected by this call.");
  m.def("PopClipRect", &ImGui::PopClipRect, "Pops the last clipping rectangle from the stack.");
  m.def("SetItemDefaultFocus", &ImGui::SetItemDefaultFocus,
        "Sets the last item as the default focused item of a window.");
  m.def("SetKeyboardFocusHere", &ImGui::SetKeyboardFocusHere, py::arg("offset") = 0,
        "Focuses the keyboard on the next widget. Positive offset can be used to access sub-components, and -1 to "
        "access the previous widget.");
  m.def("SetNextItemAllowOverlap", &ImGui::SetNextItemAllowOverlap, "Allows the next item to overlap with others.");
  m.def("IsItemHovered", &ImGui::IsItemHovered, py::arg("flags") = 0,
        "Checks if the last item is hovered and usable. Can be customized with ImGuiHoveredFlags.");
  m.def("IsItemActive", &ImGui::IsItemActive,
        "Checks if the last item is active (e.g., button being held, text field being edited).");
  m.def("IsItemFocused", &ImGui::IsItemFocused,
        "Checks if the last item is focused for keyboard or gamepad navigation.");
  m.def("IsItemClicked", &ImGui::IsItemClicked, py::arg("mouse_button") = 0,
        "Checks if the last item is hovered and clicked with the specified mouse button.");
  m.def("IsItemVisible", &ImGui::IsItemVisible,
        "Checks if the last item is visible (i.e., not clipped or scrolled out of view).");
  m.def("IsItemEdited", &ImGui::IsItemEdited,
        "Checks if the last item modified its underlying value or was pressed during this frame.");
  m.def("IsItemActivated", &ImGui::IsItemActivated,
        "Checks if the last item was just made active (previously inactive).");
  m.def("IsItemDeactivated", &ImGui::IsItemDeactivated,
        "Checks if the last item was just made inactive (previously active). Useful for Undo/Redo patterns.");
  m.def("IsItemDeactivatedAfterEdit", &ImGui::IsItemDeactivatedAfterEdit,
        "Checks if the last item was just made inactive and modified its value while active. Useful for Undo/Redo "
        "patterns.");
  m.def("IsItemToggledOpen", &ImGui::IsItemToggledOpen,
        "Checks if the last item's open state was toggled (e.g., TreeNode()).");
  m.def("IsAnyItemHovered", &ImGui::IsAnyItemHovered, "Checks if any item is currently hovered.");
  m.def("IsAnyItemActive", &ImGui::IsAnyItemActive, "Checks if any item is currently active.");
  m.def("IsAnyItemFocused", &ImGui::IsAnyItemFocused, "Checks if any item is currently focused.");
  m.def("GetItemID", &ImGui::GetItemID, "Returns the ID of the last item.");
  m.def("GetItemRectMin", &ImGui::GetItemRectMin,
        "Returns the upper-left bounding rectangle of the last item in screen space.");
  m.def("GetItemRectMax", &ImGui::GetItemRectMax,
        "Returns the lower-right bounding rectangle of the last item in screen space.");
  m.def("GetItemRectSize", &ImGui::GetItemRectSize, "Returns the size of the last item.");
  m.def(
      "IsRectVisible",
      [](const ImVec2& size) {
        const auto res_ = ImGui::IsRectVisible(size);
        return res_;
      },
      py::arg("size"),
      "Checks if a rectangle (starting from the cursor position) of the given size is visible and not clipped.");
  m.def(
      "IsRectVisible",
      [](const ImVec2& rect_min, const ImVec2& rect_max) {
        const auto res_ = ImGui::IsRectVisible(rect_min, rect_max);
        return res_;
      },
      py::arg("rect_min"), py::arg("rect_max"),
      "Checks if a rectangle defined by rect_min and rect_max is visible and not clipped.");
  m.def("GetTime", &ImGui::GetTime, "Returns the global ImGui time, incremented by io.DeltaTime every frame.");
  m.def("GetStyleColorName", &ImGui::GetStyleColorName, py::arg("idx"),
        "Returns a string representing the enum value of a style color.");
  m.def(
      "ColorConvertRGBtoHSV",
      [](const std::tuple<float, float, float>& rgb) {
        float out0, out1, out2;
        ImGui::ColorConvertRGBtoHSV(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb), out0, out1, out2);
        return std::make_tuple(out0, out1, out2);
      },
      py::arg("rgb"), "Converts RGB color values to HSV.");
  m.def(
      "ColorConvertHSVtoRGB",
      [](const std::tuple<float, float, float>& hsv) {
        float out0, out1, out2;
        ImGui::ColorConvertHSVtoRGB(std::get<0>(hsv), std::get<1>(hsv), std::get<2>(hsv), out0, out1, out2);
        return std::make_tuple(out0, out1, out2);
      },
      py::arg("hsv"), "Converts HSV color values to RGB.");
  m.def("IsKeyDown", &ImGui::IsKeyDown, py::arg("key"), "Checks if a key is being held down.");
  m.def("IsKeyPressed", &ImGui::IsKeyPressed, py::arg("key"), py::arg("repeat") = true,
        "Checks if a key was pressed (transitioned from not pressed to pressed). If repeat is true, considers "
        "io.KeyRepeatDelay / KeyRepeatRate.");
  m.def("IsKeyReleased", &ImGui::IsKeyReleased, py::arg("key"),
        "Checks if a key was released (transitioned from pressed to not pressed).");
  m.def("IsKeyChordPressed", &ImGui::IsKeyChordPressed, py::arg("key_chord"),
        "Checks if a key chord (combination of modifiers and a key) was pressed.");
  m.def("GetKeyPressedAmount", &ImGui::GetKeyPressedAmount, py::arg("key"), py::arg("repeat_delay"), py::arg("rate"),
        "Returns the number of times a key has been pressed considering the provided repeat rate and delay.");
  m.def("GetKeyName", &ImGui::GetKeyName, py::arg("key"), "[DEBUG] Returns the English name of the key.");
  m.def("SetNextFrameWantCaptureKeyboard", &ImGui::SetNextFrameWantCaptureKeyboard, py::arg("want_capture_keyboard"),
        "Overrides the io.WantCaptureKeyboard flag for the next frame.");
  m.def("Shortcut", &ImGui::Shortcut, py::arg("key_chord"), py::arg("flags") = 0,
        "Submits a shortcut route, and returns true if the shortcut is currently active and routed.");
  m.def("SetNextItemShortcut", &ImGui::SetNextItemShortcut, py::arg("key_chord"), py::arg("flags") = 0,
        "Sets the shortcut for the next item.");
  m.def("SetItemKeyOwner", &ImGui::SetItemKeyOwner, py::arg("key"),
        "Sets the key owner to the last item ID if it is hovered or active.");
  m.def("IsMouseDown", &ImGui::IsMouseDown, py::arg("button"), "Checks if a mouse button is being held down.");
  m.def("IsMouseClicked", &ImGui::IsMouseClicked, py::arg("button"), py::arg("repeat") = false,
        "Checks if a mouse button was clicked (transitioned from not pressed to pressed).");
  m.def("IsMouseReleased", &ImGui::IsMouseReleased, py::arg("button"),
        "Checks if a mouse button was released (transitioned from pressed to not pressed).");
  m.def("IsMouseDoubleClicked", &ImGui::IsMouseDoubleClicked, py::arg("button"),
        "Checks if a mouse button was double-clicked.");
  m.def("GetMouseClickedCount", &ImGui::GetMouseClickedCount, py::arg("button"),
        "Returns the number of successive clicks of a mouse button.");
  m.def("IsMouseHoveringRect", &ImGui::IsMouseHoveringRect, py::arg("r_min"), py::arg("r_max"), py::arg("clip") = true,
        "Checks if the mouse is hovering a given bounding rectangle in screen space.");
  m.def(
      "IsMousePosValid",
      [](const std::optional<ImVec2>& mouse_pos) {
        const ImVec2* mouse_pos_ = mouse_pos.has_value() ? &mouse_pos.value() : nullptr;
        const auto res_ = ImGui::IsMousePosValid(mouse_pos_);
        return res_;
      },
      py::arg("mouse_pos") = std::nullopt, "Checks if the mouse position is valid.");
  m.def("IsAnyMouseDown", &ImGui::IsAnyMouseDown, "Checks if any mouse button is being held down.");
  m.def("IsMouseDragging", &ImGui::IsMouseDragging, py::arg("button"), py::arg("lock_threshold") = -1.0f,
        "Checks if the mouse is dragging (moving while holding a button down).");
  m.def("GetMouseDragDelta", &ImGui::GetMouseDragDelta, py::arg("button") = 0, py::arg("lock_threshold") = -1.0f,
        "Returns the delta (change in position) from the initial click position while dragging.");
  m.def("ResetMouseDragDelta", &ImGui::ResetMouseDragDelta, py::arg("button") = 0,
        "Resets the mouse drag delta for the specified button.");
  m.def("GetMouseCursor", &ImGui::GetMouseCursor, "Returns the current desired mouse cursor shape.");
  m.def("SetMouseCursor", &ImGui::SetMouseCursor, py::arg("cursor_type"), "Sets the desired mouse cursor shape.");
  m.def("SetNextFrameWantCaptureMouse", &ImGui::SetNextFrameWantCaptureMouse, py::arg("want_capture_mouse"),
        "Overrides the io.WantCaptureMouse flag for the next frame.");
  m.def("GetClipboardText", &ImGui::GetClipboardText, "Returns the text currently in the clipboard.");
  m.def("LoadIniSettingsFromDisk", &ImGui::LoadIniSettingsFromDisk, py::arg("ini_filename"),
        "Loads ini settings from the specified file.");
  m.def("SaveIniSettingsToDisk", &ImGui::SaveIniSettingsToDisk, py::arg("ini_filename"),
        "Saves ini settings to the specified file.");
  m.def("DebugTextEncoding", &ImGui::DebugTextEncoding, py::arg("text"), "Debugs the text encoding.");
  m.def("DebugFlashStyleColor", &ImGui::DebugFlashStyleColor, py::arg("idx"), "Debugs by flashing a style color.");
  m.def("DebugStartItemPicker", &ImGui::DebugStartItemPicker, "Starts the item picker for debugging.");
  m.def("DebugCheckVersionAndDataLayout", &ImGui::DebugCheckVersionAndDataLayout, py::arg("version_str"),
        py::arg("sz_io"), py::arg("sz_style"), py::arg("sz_vec2"), py::arg("sz_vec4"), py::arg("sz_drawvert"),
        py::arg("sz_drawidx"), "Checks the version and data layout for debugging.");
}

void bind_imgui_enums(py::module& m) {

  py::enum_<ImGuiMultiSelectFlags_>(m, "ImGuiMultiSelectFlags")
      .value("ImGuiMultiSelectFlags_None", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_None)
      .value("ImGuiMultiSelectFlags_SingleSelect", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SingleSelect)
      .value("ImGuiMultiSelectFlags_NoSelectAll", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoSelectAll)
      .value("ImGuiMultiSelectFlags_NoRangeSelect", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoRangeSelect)
      .value("ImGuiMultiSelectFlags_NoAutoSelect", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoSelect)
      .value("ImGuiMultiSelectFlags_NoAutoClear", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoClear)
      .value("ImGuiMultiSelectFlags_NoAutoClearOnReselect",
             ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NoAutoClearOnReselect)
      .value("ImGuiMultiSelectFlags_BoxSelect1d", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelect1d)
      .value("ImGuiMultiSelectFlags_BoxSelect2d", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelect2d)
      .value("ImGuiMultiSelectFlags_BoxSelectNoScroll", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_BoxSelectNoScroll)
      .value("ImGuiMultiSelectFlags_ClearOnEscape", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ClearOnEscape)
      .value("ImGuiMultiSelectFlags_ClearOnClickVoid", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ClearOnClickVoid)
      .value("ImGuiMultiSelectFlags_ScopeWindow", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ScopeWindow)
      .value("ImGuiMultiSelectFlags_ScopeRect", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_ScopeRect)
      .value("ImGuiMultiSelectFlags_SelectOnClick", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SelectOnClick)
      .value("ImGuiMultiSelectFlags_SelectOnClickRelease",
             ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_SelectOnClickRelease)
      .value("ImGuiMultiSelectFlags_NavWrapX", ImGuiMultiSelectFlags_::ImGuiMultiSelectFlags_NavWrapX)
      .export_values();


  py::enum_<ImGuiWindowFlags_>(m, "ImGuiWindowFlags", py::arithmetic())
      .value("ImGuiWindowFlags_None", ImGuiWindowFlags_::ImGuiWindowFlags_None)
      .value("ImGuiWindowFlags_NoTitleBar", ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar)
      .value("ImGuiWindowFlags_NoResize", ImGuiWindowFlags_::ImGuiWindowFlags_NoResize)
      .value("ImGuiWindowFlags_NoMove", ImGuiWindowFlags_::ImGuiWindowFlags_NoMove)
      .value("ImGuiWindowFlags_NoScrollbar", ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar)
      .value("ImGuiWindowFlags_NoScrollWithMouse", ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse)
      .value("ImGuiWindowFlags_NoCollapse", ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)
      .value("ImGuiWindowFlags_AlwaysAutoResize", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)
      .value("ImGuiWindowFlags_NoBackground", ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground)
      .value("ImGuiWindowFlags_NoSavedSettings", ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings)
      .value("ImGuiWindowFlags_NoMouseInputs", ImGuiWindowFlags_::ImGuiWindowFlags_NoMouseInputs)
      .value("ImGuiWindowFlags_MenuBar", ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
      .value("ImGuiWindowFlags_HorizontalScrollbar", ImGuiWindowFlags_::ImGuiWindowFlags_HorizontalScrollbar)
      .value("ImGuiWindowFlags_NoFocusOnAppearing", ImGuiWindowFlags_::ImGuiWindowFlags_NoFocusOnAppearing)
      .value("ImGuiWindowFlags_NoBringToFrontOnFocus", ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus)
      .value("ImGuiWindowFlags_AlwaysVerticalScrollbar", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar)
      .value("ImGuiWindowFlags_AlwaysHorizontalScrollbar",
             ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysHorizontalScrollbar)
      .value("ImGuiWindowFlags_NoNavInputs", ImGuiWindowFlags_::ImGuiWindowFlags_NoNavInputs)
      .value("ImGuiWindowFlags_NoNavFocus", ImGuiWindowFlags_::ImGuiWindowFlags_NoNavFocus)
      .value("ImGuiWindowFlags_UnsavedDocument", ImGuiWindowFlags_::ImGuiWindowFlags_UnsavedDocument)
      .value("ImGuiWindowFlags_NoNav", ImGuiWindowFlags_::ImGuiWindowFlags_NoNav)
      .value("ImGuiWindowFlags_NoDecoration", ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration)
      .value("ImGuiWindowFlags_NoInputs", ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs)
      .value("ImGuiWindowFlags_ChildWindow", ImGuiWindowFlags_::ImGuiWindowFlags_ChildWindow)
      .value("ImGuiWindowFlags_Tooltip", ImGuiWindowFlags_::ImGuiWindowFlags_Tooltip)
      .value("ImGuiWindowFlags_Popup", ImGuiWindowFlags_::ImGuiWindowFlags_Popup)
      .value("ImGuiWindowFlags_Modal", ImGuiWindowFlags_::ImGuiWindowFlags_Modal)
      .value("ImGuiWindowFlags_ChildMenu", ImGuiWindowFlags_::ImGuiWindowFlags_ChildMenu)
      .value("ImGuiWindowFlags_AlwaysUseWindowPadding", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding)
      .value("ImGuiWindowFlags_NavFlattened", ImGuiWindowFlags_::ImGuiWindowFlags_NavFlattened)
      .export_values();


  py::enum_<ImGuiChildFlags_>(m, "ImGuiChildFlags", py::arithmetic())
      .value("ImGuiChildFlags_None", ImGuiChildFlags_::ImGuiChildFlags_None)
      .value("ImGuiChildFlags_Border", ImGuiChildFlags_::ImGuiChildFlags_Border)
      .value("ImGuiChildFlags_AlwaysUseWindowPadding", ImGuiChildFlags_::ImGuiChildFlags_AlwaysUseWindowPadding)
      .value("ImGuiChildFlags_ResizeX", ImGuiChildFlags_::ImGuiChildFlags_ResizeX)
      .value("ImGuiChildFlags_ResizeY", ImGuiChildFlags_::ImGuiChildFlags_ResizeY)
      .value("ImGuiChildFlags_AutoResizeX", ImGuiChildFlags_::ImGuiChildFlags_AutoResizeX)
      .value("ImGuiChildFlags_AutoResizeY", ImGuiChildFlags_::ImGuiChildFlags_AutoResizeY)
      .value("ImGuiChildFlags_AlwaysAutoResize", ImGuiChildFlags_::ImGuiChildFlags_AlwaysAutoResize)
      .value("ImGuiChildFlags_FrameStyle", ImGuiChildFlags_::ImGuiChildFlags_FrameStyle)
      .value("ImGuiChildFlags_NavFlattened", ImGuiChildFlags_::ImGuiChildFlags_NavFlattened)
      .export_values();


  py::enum_<ImGuiItemFlags_>(m, "ImGuiItemFlags", py::arithmetic())
      .value("ImGuiItemFlags_None", ImGuiItemFlags_::ImGuiItemFlags_None)
      .value("ImGuiItemFlags_NoTabStop", ImGuiItemFlags_::ImGuiItemFlags_NoTabStop)
      .value("ImGuiItemFlags_NoNav", ImGuiItemFlags_::ImGuiItemFlags_NoNav)
      .value("ImGuiItemFlags_NoNavDefaultFocus", ImGuiItemFlags_::ImGuiItemFlags_NoNavDefaultFocus)
      .value("ImGuiItemFlags_ButtonRepeat", ImGuiItemFlags_::ImGuiItemFlags_ButtonRepeat)
      .value("ImGuiItemFlags_AutoClosePopups", ImGuiItemFlags_::ImGuiItemFlags_AutoClosePopups)
      .export_values();


  py::enum_<ImGuiInputTextFlags_>(m, "ImGuiInputTextFlags", py::arithmetic())
      .value("ImGuiInputTextFlags_None", ImGuiInputTextFlags_::ImGuiInputTextFlags_None)
      .value("ImGuiInputTextFlags_CharsDecimal", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsDecimal)
      .value("ImGuiInputTextFlags_CharsHexadecimal", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsHexadecimal)
      .value("ImGuiInputTextFlags_CharsScientific", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsScientific)
      .value("ImGuiInputTextFlags_CharsUppercase", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsUppercase)
      .value("ImGuiInputTextFlags_CharsNoBlank", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsNoBlank)
      .value("ImGuiInputTextFlags_AllowTabInput", ImGuiInputTextFlags_::ImGuiInputTextFlags_AllowTabInput)
      .value("ImGuiInputTextFlags_EnterReturnsTrue", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue)
      .value("ImGuiInputTextFlags_EscapeClearsAll", ImGuiInputTextFlags_::ImGuiInputTextFlags_EscapeClearsAll)
      .value("ImGuiInputTextFlags_CtrlEnterForNewLine", ImGuiInputTextFlags_::ImGuiInputTextFlags_CtrlEnterForNewLine)
      .value("ImGuiInputTextFlags_ReadOnly", ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly)
      .value("ImGuiInputTextFlags_Password", ImGuiInputTextFlags_::ImGuiInputTextFlags_Password)
      .value("ImGuiInputTextFlags_AlwaysOverwrite", ImGuiInputTextFlags_::ImGuiInputTextFlags_AlwaysOverwrite)
      .value("ImGuiInputTextFlags_AutoSelectAll", ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll)
      .value("ImGuiInputTextFlags_ParseEmptyRefVal", ImGuiInputTextFlags_::ImGuiInputTextFlags_ParseEmptyRefVal)
      .value("ImGuiInputTextFlags_DisplayEmptyRefVal", ImGuiInputTextFlags_::ImGuiInputTextFlags_DisplayEmptyRefVal)
      .value("ImGuiInputTextFlags_NoHorizontalScroll", ImGuiInputTextFlags_::ImGuiInputTextFlags_NoHorizontalScroll)
      .value("ImGuiInputTextFlags_NoUndoRedo", ImGuiInputTextFlags_::ImGuiInputTextFlags_NoUndoRedo)
      .value("ImGuiInputTextFlags_CallbackCompletion", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCompletion)
      .value("ImGuiInputTextFlags_CallbackHistory", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackHistory)
      .value("ImGuiInputTextFlags_CallbackAlways", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackAlways)
      .value("ImGuiInputTextFlags_CallbackCharFilter", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCharFilter)
      .value("ImGuiInputTextFlags_CallbackResize", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackResize)
      .value("ImGuiInputTextFlags_CallbackEdit", ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackEdit)
      .export_values();


  py::enum_<ImGuiTreeNodeFlags_>(m, "ImGuiTreeNodeFlags", py::arithmetic())
      .value("ImGuiTreeNodeFlags_None", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_None)
      .value("ImGuiTreeNodeFlags_Selected", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Selected)
      .value("ImGuiTreeNodeFlags_Framed", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Framed)
      .value("ImGuiTreeNodeFlags_AllowOverlap", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_AllowOverlap)
      .value("ImGuiTreeNodeFlags_NoTreePushOnOpen", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoTreePushOnOpen)
      .value("ImGuiTreeNodeFlags_NoAutoOpenOnLog", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoAutoOpenOnLog)
      .value("ImGuiTreeNodeFlags_DefaultOpen", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)
      .value("ImGuiTreeNodeFlags_OpenOnDoubleClick", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnDoubleClick)
      .value("ImGuiTreeNodeFlags_OpenOnArrow", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow)
      .value("ImGuiTreeNodeFlags_Leaf", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf)
      .value("ImGuiTreeNodeFlags_Bullet", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Bullet)
      .value("ImGuiTreeNodeFlags_FramePadding", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_FramePadding)
      .value("ImGuiTreeNodeFlags_SpanAvailWidth", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth)
      .value("ImGuiTreeNodeFlags_SpanFullWidth", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanFullWidth)
      .value("ImGuiTreeNodeFlags_SpanTextWidth", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanTextWidth)
      .value("ImGuiTreeNodeFlags_SpanAllColumns", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAllColumns)
      .value("ImGuiTreeNodeFlags_NavLeftJumpsBackHere", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NavLeftJumpsBackHere)
      .value("ImGuiTreeNodeFlags_CollapsingHeader", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_CollapsingHeader)
      .value("ImGuiTreeNodeFlags_AllowItemOverlap", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_AllowItemOverlap)
      .export_values();


  py::enum_<ImGuiPopupFlags_>(m, "ImGuiPopupFlags", py::arithmetic())
      .value("ImGuiPopupFlags_None", ImGuiPopupFlags_::ImGuiPopupFlags_None)
      .value("ImGuiPopupFlags_MouseButtonLeft", ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonLeft)
      .value("ImGuiPopupFlags_MouseButtonRight", ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonRight)
      .value("ImGuiPopupFlags_MouseButtonMiddle", ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonMiddle)
      .value("ImGuiPopupFlags_MouseButtonMask_", ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonMask_)
      .value("ImGuiPopupFlags_MouseButtonDefault_", ImGuiPopupFlags_::ImGuiPopupFlags_MouseButtonDefault_)
      .value("ImGuiPopupFlags_NoReopen", ImGuiPopupFlags_::ImGuiPopupFlags_NoReopen)
      .value("ImGuiPopupFlags_NoOpenOverExistingPopup", ImGuiPopupFlags_::ImGuiPopupFlags_NoOpenOverExistingPopup)
      .value("ImGuiPopupFlags_NoOpenOverItems", ImGuiPopupFlags_::ImGuiPopupFlags_NoOpenOverItems)
      .value("ImGuiPopupFlags_AnyPopupId", ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopupId)
      .value("ImGuiPopupFlags_AnyPopupLevel", ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopupLevel)
      .value("ImGuiPopupFlags_AnyPopup", ImGuiPopupFlags_::ImGuiPopupFlags_AnyPopup)
      .export_values();


  py::enum_<ImGuiSelectableFlags_>(m, "ImGuiSelectableFlags", py::arithmetic())
      .value("ImGuiSelectableFlags_None", ImGuiSelectableFlags_::ImGuiSelectableFlags_None)
      .value("ImGuiSelectableFlags_NoAutoClosePopups", ImGuiSelectableFlags_::ImGuiSelectableFlags_NoAutoClosePopups)
      .value("ImGuiSelectableFlags_SpanAllColumns", ImGuiSelectableFlags_::ImGuiSelectableFlags_SpanAllColumns)
      .value("ImGuiSelectableFlags_AllowDoubleClick", ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick)
      .value("ImGuiSelectableFlags_Disabled", ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled)
      .value("ImGuiSelectableFlags_AllowOverlap", ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowOverlap)
      .value("ImGuiSelectableFlags_Highlight", ImGuiSelectableFlags_::ImGuiSelectableFlags_Highlight)
      .value("ImGuiSelectableFlags_DontClosePopups", ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups)
      .value("ImGuiSelectableFlags_AllowItemOverlap", ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowItemOverlap)
      .export_values();


  py::enum_<ImGuiComboFlags_>(m, "ImGuiComboFlags", py::arithmetic())
      .value("ImGuiComboFlags_None", ImGuiComboFlags_::ImGuiComboFlags_None)
      .value("ImGuiComboFlags_PopupAlignLeft", ImGuiComboFlags_::ImGuiComboFlags_PopupAlignLeft)
      .value("ImGuiComboFlags_HeightSmall", ImGuiComboFlags_::ImGuiComboFlags_HeightSmall)
      .value("ImGuiComboFlags_HeightRegular", ImGuiComboFlags_::ImGuiComboFlags_HeightRegular)
      .value("ImGuiComboFlags_HeightLarge", ImGuiComboFlags_::ImGuiComboFlags_HeightLarge)
      .value("ImGuiComboFlags_HeightLargest", ImGuiComboFlags_::ImGuiComboFlags_HeightLargest)
      .value("ImGuiComboFlags_NoArrowButton", ImGuiComboFlags_::ImGuiComboFlags_NoArrowButton)
      .value("ImGuiComboFlags_NoPreview", ImGuiComboFlags_::ImGuiComboFlags_NoPreview)
      .value("ImGuiComboFlags_WidthFitPreview", ImGuiComboFlags_::ImGuiComboFlags_WidthFitPreview)
      .value("ImGuiComboFlags_HeightMask_", ImGuiComboFlags_::ImGuiComboFlags_HeightMask_)
      .export_values();


  py::enum_<ImGuiTabBarFlags_>(m, "ImGuiTabBarFlags", py::arithmetic())
      .value("ImGuiTabBarFlags_None", ImGuiTabBarFlags_::ImGuiTabBarFlags_None)
      .value("ImGuiTabBarFlags_Reorderable", ImGuiTabBarFlags_::ImGuiTabBarFlags_Reorderable)
      .value("ImGuiTabBarFlags_AutoSelectNewTabs", ImGuiTabBarFlags_::ImGuiTabBarFlags_AutoSelectNewTabs)
      .value("ImGuiTabBarFlags_TabListPopupButton", ImGuiTabBarFlags_::ImGuiTabBarFlags_TabListPopupButton)
      .value("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton",
             ImGuiTabBarFlags_::ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)
      .value("ImGuiTabBarFlags_NoTabListScrollingButtons",
             ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTabListScrollingButtons)
      .value("ImGuiTabBarFlags_NoTooltip", ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTooltip)
      .value("ImGuiTabBarFlags_DrawSelectedOverline", ImGuiTabBarFlags_::ImGuiTabBarFlags_DrawSelectedOverline)
      .value("ImGuiTabBarFlags_FittingPolicyResizeDown", ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyResizeDown)
      .value("ImGuiTabBarFlags_FittingPolicyScroll", ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyScroll)
      .value("ImGuiTabBarFlags_FittingPolicyMask_", ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyMask_)
      .value("ImGuiTabBarFlags_FittingPolicyDefault_", ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyDefault_)
      .export_values();


  py::enum_<ImGuiTabItemFlags_>(m, "ImGuiTabItemFlags", py::arithmetic())
      .value("ImGuiTabItemFlags_None", ImGuiTabItemFlags_::ImGuiTabItemFlags_None)
      .value("ImGuiTabItemFlags_UnsavedDocument", ImGuiTabItemFlags_::ImGuiTabItemFlags_UnsavedDocument)
      .value("ImGuiTabItemFlags_SetSelected", ImGuiTabItemFlags_::ImGuiTabItemFlags_SetSelected)
      .value("ImGuiTabItemFlags_NoCloseWithMiddleMouseButton",
             ImGuiTabItemFlags_::ImGuiTabItemFlags_NoCloseWithMiddleMouseButton)
      .value("ImGuiTabItemFlags_NoPushId", ImGuiTabItemFlags_::ImGuiTabItemFlags_NoPushId)
      .value("ImGuiTabItemFlags_NoTooltip", ImGuiTabItemFlags_::ImGuiTabItemFlags_NoTooltip)
      .value("ImGuiTabItemFlags_NoReorder", ImGuiTabItemFlags_::ImGuiTabItemFlags_NoReorder)
      .value("ImGuiTabItemFlags_Leading", ImGuiTabItemFlags_::ImGuiTabItemFlags_Leading)
      .value("ImGuiTabItemFlags_Trailing", ImGuiTabItemFlags_::ImGuiTabItemFlags_Trailing)
      .value("ImGuiTabItemFlags_NoAssumedClosure", ImGuiTabItemFlags_::ImGuiTabItemFlags_NoAssumedClosure)
      .export_values();


  py::enum_<ImGuiFocusedFlags_>(m, "ImGuiFocusedFlags", py::arithmetic())
      .value("ImGuiFocusedFlags_None", ImGuiFocusedFlags_::ImGuiFocusedFlags_None)
      .value("ImGuiFocusedFlags_ChildWindows", ImGuiFocusedFlags_::ImGuiFocusedFlags_ChildWindows)
      .value("ImGuiFocusedFlags_RootWindow", ImGuiFocusedFlags_::ImGuiFocusedFlags_RootWindow)
      .value("ImGuiFocusedFlags_AnyWindow", ImGuiFocusedFlags_::ImGuiFocusedFlags_AnyWindow)
      .value("ImGuiFocusedFlags_NoPopupHierarchy", ImGuiFocusedFlags_::ImGuiFocusedFlags_NoPopupHierarchy)
      .value("ImGuiFocusedFlags_RootAndChildWindows", ImGuiFocusedFlags_::ImGuiFocusedFlags_RootAndChildWindows)
      .export_values();


  py::enum_<ImGuiHoveredFlags_>(m, "ImGuiHoveredFlags", py::arithmetic())
      .value("ImGuiHoveredFlags_None", ImGuiHoveredFlags_::ImGuiHoveredFlags_None)
      .value("ImGuiHoveredFlags_ChildWindows", ImGuiHoveredFlags_::ImGuiHoveredFlags_ChildWindows)
      .value("ImGuiHoveredFlags_RootWindow", ImGuiHoveredFlags_::ImGuiHoveredFlags_RootWindow)
      .value("ImGuiHoveredFlags_AnyWindow", ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow)
      .value("ImGuiHoveredFlags_NoPopupHierarchy", ImGuiHoveredFlags_::ImGuiHoveredFlags_NoPopupHierarchy)
      .value("ImGuiHoveredFlags_AllowWhenBlockedByPopup", ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenBlockedByPopup)
      .value("ImGuiHoveredFlags_AllowWhenBlockedByActiveItem",
             ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)
      .value("ImGuiHoveredFlags_AllowWhenOverlappedByItem",
             ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlappedByItem)
      .value("ImGuiHoveredFlags_AllowWhenOverlappedByWindow",
             ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlappedByWindow)
      .value("ImGuiHoveredFlags_AllowWhenDisabled", ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenDisabled)
      .value("ImGuiHoveredFlags_NoNavOverride", ImGuiHoveredFlags_::ImGuiHoveredFlags_NoNavOverride)
      .value("ImGuiHoveredFlags_AllowWhenOverlapped", ImGuiHoveredFlags_::ImGuiHoveredFlags_AllowWhenOverlapped)
      .value("ImGuiHoveredFlags_RectOnly", ImGuiHoveredFlags_::ImGuiHoveredFlags_RectOnly)
      .value("ImGuiHoveredFlags_RootAndChildWindows", ImGuiHoveredFlags_::ImGuiHoveredFlags_RootAndChildWindows)
      .value("ImGuiHoveredFlags_ForTooltip", ImGuiHoveredFlags_::ImGuiHoveredFlags_ForTooltip)
      .value("ImGuiHoveredFlags_Stationary", ImGuiHoveredFlags_::ImGuiHoveredFlags_Stationary)
      .value("ImGuiHoveredFlags_DelayNone", ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayNone)
      .value("ImGuiHoveredFlags_DelayShort", ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayShort)
      .value("ImGuiHoveredFlags_DelayNormal", ImGuiHoveredFlags_::ImGuiHoveredFlags_DelayNormal)
      .value("ImGuiHoveredFlags_NoSharedDelay", ImGuiHoveredFlags_::ImGuiHoveredFlags_NoSharedDelay)
      .export_values();


  py::enum_<ImGuiDragDropFlags_>(m, "ImGuiDragDropFlags", py::arithmetic())
      .value("ImGuiDragDropFlags_None", ImGuiDragDropFlags_::ImGuiDragDropFlags_None)
      .value("ImGuiDragDropFlags_SourceNoPreviewTooltip",
             ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoPreviewTooltip)
      .value("ImGuiDragDropFlags_SourceNoDisableHover", ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoDisableHover)
      .value("ImGuiDragDropFlags_SourceNoHoldToOpenOthers",
             ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceNoHoldToOpenOthers)
      .value("ImGuiDragDropFlags_SourceAllowNullID", ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceAllowNullID)
      .value("ImGuiDragDropFlags_SourceExtern", ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceExtern)
      .value("ImGuiDragDropFlags_PayloadAutoExpire", ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadAutoExpire)
      .value("ImGuiDragDropFlags_PayloadNoCrossContext", ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadNoCrossContext)
      .value("ImGuiDragDropFlags_PayloadNoCrossProcess", ImGuiDragDropFlags_::ImGuiDragDropFlags_PayloadNoCrossProcess)
      .value("ImGuiDragDropFlags_AcceptBeforeDelivery", ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptBeforeDelivery)
      .value("ImGuiDragDropFlags_AcceptNoDrawDefaultRect",
             ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptNoDrawDefaultRect)
      .value("ImGuiDragDropFlags_AcceptNoPreviewTooltip",
             ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptNoPreviewTooltip)
      .value("ImGuiDragDropFlags_AcceptPeekOnly", ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptPeekOnly)
      .export_values();


  py::enum_<ImGuiDataType_>(m, "ImGuiDataType")
      .value("ImGuiDataType_S8", ImGuiDataType_::ImGuiDataType_S8)
      .value("ImGuiDataType_U8", ImGuiDataType_::ImGuiDataType_U8)
      .value("ImGuiDataType_S16", ImGuiDataType_::ImGuiDataType_S16)
      .value("ImGuiDataType_U16", ImGuiDataType_::ImGuiDataType_U16)
      .value("ImGuiDataType_S32", ImGuiDataType_::ImGuiDataType_S32)
      .value("ImGuiDataType_U32", ImGuiDataType_::ImGuiDataType_U32)
      .value("ImGuiDataType_S64", ImGuiDataType_::ImGuiDataType_S64)
      .value("ImGuiDataType_U64", ImGuiDataType_::ImGuiDataType_U64)
      .value("ImGuiDataType_Float", ImGuiDataType_::ImGuiDataType_Float)
      .value("ImGuiDataType_Double", ImGuiDataType_::ImGuiDataType_Double)
      .value("ImGuiDataType_Bool", ImGuiDataType_::ImGuiDataType_Bool)
      .value("ImGuiDataType_COUNT", ImGuiDataType_::ImGuiDataType_COUNT)
      .export_values();


  py::enum_<ImGuiDir>(m, "ImGuiDir")
      .value("ImGuiDir_None", ImGuiDir::ImGuiDir_None)
      .value("ImGuiDir_Left", ImGuiDir::ImGuiDir_Left)
      .value("ImGuiDir_Right", ImGuiDir::ImGuiDir_Right)
      .value("ImGuiDir_Up", ImGuiDir::ImGuiDir_Up)
      .value("ImGuiDir_Down", ImGuiDir::ImGuiDir_Down)
      .value("ImGuiDir_COUNT", ImGuiDir::ImGuiDir_COUNT)
      .export_values();


  py::enum_<ImGuiSortDirection>(m, "ImGuiSortDirection")
      .value("ImGuiSortDirection_None", ImGuiSortDirection::ImGuiSortDirection_None)
      .value("ImGuiSortDirection_Ascending", ImGuiSortDirection::ImGuiSortDirection_Ascending)
      .value("ImGuiSortDirection_Descending", ImGuiSortDirection::ImGuiSortDirection_Descending)
      .export_values();


  py::enum_<ImGuiKey>(m, "ImGuiKey")
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
      .value("ImGuiKey_GamepadFaceLeft", ImGuiKey::ImGuiKey_GamepadFaceLeft)
      .value("ImGuiKey_GamepadFaceRight", ImGuiKey::ImGuiKey_GamepadFaceRight)
      .value("ImGuiKey_GamepadFaceUp", ImGuiKey::ImGuiKey_GamepadFaceUp)
      .value("ImGuiKey_GamepadFaceDown", ImGuiKey::ImGuiKey_GamepadFaceDown)
      .value("ImGuiKey_GamepadDpadLeft", ImGuiKey::ImGuiKey_GamepadDpadLeft)
      .value("ImGuiKey_GamepadDpadRight", ImGuiKey::ImGuiKey_GamepadDpadRight)
      .value("ImGuiKey_GamepadDpadUp", ImGuiKey::ImGuiKey_GamepadDpadUp)
      .value("ImGuiKey_GamepadDpadDown", ImGuiKey::ImGuiKey_GamepadDpadDown)
      .value("ImGuiKey_GamepadL1", ImGuiKey::ImGuiKey_GamepadL1)
      .value("ImGuiKey_GamepadR1", ImGuiKey::ImGuiKey_GamepadR1)
      .value("ImGuiKey_GamepadL2", ImGuiKey::ImGuiKey_GamepadL2)
      .value("ImGuiKey_GamepadR2", ImGuiKey::ImGuiKey_GamepadR2)
      .value("ImGuiKey_GamepadL3", ImGuiKey::ImGuiKey_GamepadL3)
      .value("ImGuiKey_GamepadR3", ImGuiKey::ImGuiKey_GamepadR3)
      .value("ImGuiKey_GamepadLStickLeft", ImGuiKey::ImGuiKey_GamepadLStickLeft)
      .value("ImGuiKey_GamepadLStickRight", ImGuiKey::ImGuiKey_GamepadLStickRight)
      .value("ImGuiKey_GamepadLStickUp", ImGuiKey::ImGuiKey_GamepadLStickUp)
      .value("ImGuiKey_GamepadLStickDown", ImGuiKey::ImGuiKey_GamepadLStickDown)
      .value("ImGuiKey_GamepadRStickLeft", ImGuiKey::ImGuiKey_GamepadRStickLeft)
      .value("ImGuiKey_GamepadRStickRight", ImGuiKey::ImGuiKey_GamepadRStickRight)
      .value("ImGuiKey_GamepadRStickUp", ImGuiKey::ImGuiKey_GamepadRStickUp)
      .value("ImGuiKey_GamepadRStickDown", ImGuiKey::ImGuiKey_GamepadRStickDown)
      .value("ImGuiKey_MouseLeft", ImGuiKey::ImGuiKey_MouseLeft)
      .value("ImGuiKey_MouseRight", ImGuiKey::ImGuiKey_MouseRight)
      .value("ImGuiKey_MouseMiddle", ImGuiKey::ImGuiKey_MouseMiddle)
      .value("ImGuiKey_MouseX1", ImGuiKey::ImGuiKey_MouseX1)
      .value("ImGuiKey_MouseX2", ImGuiKey::ImGuiKey_MouseX2)
      .value("ImGuiKey_MouseWheelX", ImGuiKey::ImGuiKey_MouseWheelX)
      .value("ImGuiKey_MouseWheelY", ImGuiKey::ImGuiKey_MouseWheelY)
      .value("ImGuiKey_ReservedForModCtrl", ImGuiKey::ImGuiKey_ReservedForModCtrl)
      .value("ImGuiKey_ReservedForModShift", ImGuiKey::ImGuiKey_ReservedForModShift)
      .value("ImGuiKey_ReservedForModAlt", ImGuiKey::ImGuiKey_ReservedForModAlt)
      .value("ImGuiKey_ReservedForModSuper", ImGuiKey::ImGuiKey_ReservedForModSuper)
      .value("ImGuiKey_COUNT", ImGuiKey::ImGuiKey_COUNT)
      .value("ImGuiMod_None", ImGuiKey::ImGuiMod_None)
      .value("ImGuiMod_Ctrl", ImGuiKey::ImGuiMod_Ctrl)
      .value("ImGuiMod_Shift", ImGuiKey::ImGuiMod_Shift)
      .value("ImGuiMod_Alt", ImGuiKey::ImGuiMod_Alt)
      .value("ImGuiMod_Super", ImGuiKey::ImGuiMod_Super)
      .value("ImGuiMod_Mask_", ImGuiKey::ImGuiMod_Mask_)
      .value("ImGuiKey_NamedKey_BEGIN", ImGuiKey::ImGuiKey_NamedKey_BEGIN)
      .value("ImGuiKey_NamedKey_END", ImGuiKey::ImGuiKey_NamedKey_END)
      .value("ImGuiKey_NamedKey_COUNT", ImGuiKey::ImGuiKey_NamedKey_COUNT)
      .value("ImGuiKey_KeysData_SIZE", ImGuiKey::ImGuiKey_KeysData_SIZE)
      .value("ImGuiKey_KeysData_OFFSET", ImGuiKey::ImGuiKey_KeysData_OFFSET)
      .export_values();


  py::enum_<ImGuiInputFlags_>(m, "ImGuiInputFlags", py::arithmetic())
      .value("ImGuiInputFlags_None", ImGuiInputFlags_::ImGuiInputFlags_None)
      .value("ImGuiInputFlags_Repeat", ImGuiInputFlags_::ImGuiInputFlags_Repeat)
      .value("ImGuiInputFlags_RouteActive", ImGuiInputFlags_::ImGuiInputFlags_RouteActive)
      .value("ImGuiInputFlags_RouteFocused", ImGuiInputFlags_::ImGuiInputFlags_RouteFocused)
      .value("ImGuiInputFlags_RouteGlobal", ImGuiInputFlags_::ImGuiInputFlags_RouteGlobal)
      .value("ImGuiInputFlags_RouteAlways", ImGuiInputFlags_::ImGuiInputFlags_RouteAlways)
      .value("ImGuiInputFlags_RouteOverFocused", ImGuiInputFlags_::ImGuiInputFlags_RouteOverFocused)
      .value("ImGuiInputFlags_RouteOverActive", ImGuiInputFlags_::ImGuiInputFlags_RouteOverActive)
      .value("ImGuiInputFlags_RouteUnlessBgFocused", ImGuiInputFlags_::ImGuiInputFlags_RouteUnlessBgFocused)
      .value("ImGuiInputFlags_RouteFromRootWindow", ImGuiInputFlags_::ImGuiInputFlags_RouteFromRootWindow)
      .value("ImGuiInputFlags_Tooltip", ImGuiInputFlags_::ImGuiInputFlags_Tooltip)
      .export_values();


  py::enum_<ImGuiConfigFlags_>(m, "ImGuiConfigFlags", py::arithmetic())
      .value("ImGuiConfigFlags_None", ImGuiConfigFlags_::ImGuiConfigFlags_None)
      .value("ImGuiConfigFlags_NavEnableKeyboard", ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableKeyboard)
      .value("ImGuiConfigFlags_NavEnableGamepad", ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableGamepad)
      .value("ImGuiConfigFlags_NavEnableSetMousePos", ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableSetMousePos)
      .value("ImGuiConfigFlags_NavNoCaptureKeyboard", ImGuiConfigFlags_::ImGuiConfigFlags_NavNoCaptureKeyboard)
      .value("ImGuiConfigFlags_NoMouse", ImGuiConfigFlags_::ImGuiConfigFlags_NoMouse)
      .value("ImGuiConfigFlags_NoMouseCursorChange", ImGuiConfigFlags_::ImGuiConfigFlags_NoMouseCursorChange)
      .value("ImGuiConfigFlags_NoKeyboard", ImGuiConfigFlags_::ImGuiConfigFlags_NoKeyboard)
      .value("ImGuiConfigFlags_IsSRGB", ImGuiConfigFlags_::ImGuiConfigFlags_IsSRGB)
      .value("ImGuiConfigFlags_IsTouchScreen", ImGuiConfigFlags_::ImGuiConfigFlags_IsTouchScreen)
      .export_values();


  py::enum_<ImGuiBackendFlags_>(m, "ImGuiBackendFlags", py::arithmetic())
      .value("ImGuiBackendFlags_None", ImGuiBackendFlags_::ImGuiBackendFlags_None)
      .value("ImGuiBackendFlags_HasGamepad", ImGuiBackendFlags_::ImGuiBackendFlags_HasGamepad)
      .value("ImGuiBackendFlags_HasMouseCursors", ImGuiBackendFlags_::ImGuiBackendFlags_HasMouseCursors)
      .value("ImGuiBackendFlags_HasSetMousePos", ImGuiBackendFlags_::ImGuiBackendFlags_HasSetMousePos)
      .value("ImGuiBackendFlags_RendererHasVtxOffset", ImGuiBackendFlags_::ImGuiBackendFlags_RendererHasVtxOffset)
      .export_values();


  py::enum_<ImGuiCol_>(m, "ImGuiCol")
      .value("ImGuiCol_Text", ImGuiCol_::ImGuiCol_Text)
      .value("ImGuiCol_TextDisabled", ImGuiCol_::ImGuiCol_TextDisabled)
      .value("ImGuiCol_WindowBg", ImGuiCol_::ImGuiCol_WindowBg)
      .value("ImGuiCol_ChildBg", ImGuiCol_::ImGuiCol_ChildBg)
      .value("ImGuiCol_PopupBg", ImGuiCol_::ImGuiCol_PopupBg)
      .value("ImGuiCol_Border", ImGuiCol_::ImGuiCol_Border)
      .value("ImGuiCol_BorderShadow", ImGuiCol_::ImGuiCol_BorderShadow)
      .value("ImGuiCol_FrameBg", ImGuiCol_::ImGuiCol_FrameBg)
      .value("ImGuiCol_FrameBgHovered", ImGuiCol_::ImGuiCol_FrameBgHovered)
      .value("ImGuiCol_FrameBgActive", ImGuiCol_::ImGuiCol_FrameBgActive)
      .value("ImGuiCol_TitleBg", ImGuiCol_::ImGuiCol_TitleBg)
      .value("ImGuiCol_TitleBgActive", ImGuiCol_::ImGuiCol_TitleBgActive)
      .value("ImGuiCol_TitleBgCollapsed", ImGuiCol_::ImGuiCol_TitleBgCollapsed)
      .value("ImGuiCol_MenuBarBg", ImGuiCol_::ImGuiCol_MenuBarBg)
      .value("ImGuiCol_ScrollbarBg", ImGuiCol_::ImGuiCol_ScrollbarBg)
      .value("ImGuiCol_ScrollbarGrab", ImGuiCol_::ImGuiCol_ScrollbarGrab)
      .value("ImGuiCol_ScrollbarGrabHovered", ImGuiCol_::ImGuiCol_ScrollbarGrabHovered)
      .value("ImGuiCol_ScrollbarGrabActive", ImGuiCol_::ImGuiCol_ScrollbarGrabActive)
      .value("ImGuiCol_CheckMark", ImGuiCol_::ImGuiCol_CheckMark)
      .value("ImGuiCol_SliderGrab", ImGuiCol_::ImGuiCol_SliderGrab)
      .value("ImGuiCol_SliderGrabActive", ImGuiCol_::ImGuiCol_SliderGrabActive)
      .value("ImGuiCol_Button", ImGuiCol_::ImGuiCol_Button)
      .value("ImGuiCol_ButtonHovered", ImGuiCol_::ImGuiCol_ButtonHovered)
      .value("ImGuiCol_ButtonActive", ImGuiCol_::ImGuiCol_ButtonActive)
      .value("ImGuiCol_Header", ImGuiCol_::ImGuiCol_Header)
      .value("ImGuiCol_HeaderHovered", ImGuiCol_::ImGuiCol_HeaderHovered)
      .value("ImGuiCol_HeaderActive", ImGuiCol_::ImGuiCol_HeaderActive)
      .value("ImGuiCol_Separator", ImGuiCol_::ImGuiCol_Separator)
      .value("ImGuiCol_SeparatorHovered", ImGuiCol_::ImGuiCol_SeparatorHovered)
      .value("ImGuiCol_SeparatorActive", ImGuiCol_::ImGuiCol_SeparatorActive)
      .value("ImGuiCol_ResizeGrip", ImGuiCol_::ImGuiCol_ResizeGrip)
      .value("ImGuiCol_ResizeGripHovered", ImGuiCol_::ImGuiCol_ResizeGripHovered)
      .value("ImGuiCol_ResizeGripActive", ImGuiCol_::ImGuiCol_ResizeGripActive)
      .value("ImGuiCol_TabHovered", ImGuiCol_::ImGuiCol_TabHovered)
      .value("ImGuiCol_Tab", ImGuiCol_::ImGuiCol_Tab)
      .value("ImGuiCol_TabSelected", ImGuiCol_::ImGuiCol_TabSelected)
      .value("ImGuiCol_TabSelectedOverline", ImGuiCol_::ImGuiCol_TabSelectedOverline)
      .value("ImGuiCol_TabDimmed", ImGuiCol_::ImGuiCol_TabDimmed)
      .value("ImGuiCol_TabDimmedSelected", ImGuiCol_::ImGuiCol_TabDimmedSelected)
      .value("ImGuiCol_TabDimmedSelectedOverline", ImGuiCol_::ImGuiCol_TabDimmedSelectedOverline)
      .value("ImGuiCol_PlotLines", ImGuiCol_::ImGuiCol_PlotLines)
      .value("ImGuiCol_PlotLinesHovered", ImGuiCol_::ImGuiCol_PlotLinesHovered)
      .value("ImGuiCol_PlotHistogram", ImGuiCol_::ImGuiCol_PlotHistogram)
      .value("ImGuiCol_PlotHistogramHovered", ImGuiCol_::ImGuiCol_PlotHistogramHovered)
      .value("ImGuiCol_TableHeaderBg", ImGuiCol_::ImGuiCol_TableHeaderBg)
      .value("ImGuiCol_TableBorderStrong", ImGuiCol_::ImGuiCol_TableBorderStrong)
      .value("ImGuiCol_TableBorderLight", ImGuiCol_::ImGuiCol_TableBorderLight)
      .value("ImGuiCol_TableRowBg", ImGuiCol_::ImGuiCol_TableRowBg)
      .value("ImGuiCol_TableRowBgAlt", ImGuiCol_::ImGuiCol_TableRowBgAlt)
      .value("ImGuiCol_TextLink", ImGuiCol_::ImGuiCol_TextLink)
      .value("ImGuiCol_TextSelectedBg", ImGuiCol_::ImGuiCol_TextSelectedBg)
      .value("ImGuiCol_DragDropTarget", ImGuiCol_::ImGuiCol_DragDropTarget)
      .value("ImGuiCol_NavHighlight", ImGuiCol_::ImGuiCol_NavHighlight)
      .value("ImGuiCol_NavWindowingHighlight", ImGuiCol_::ImGuiCol_NavWindowingHighlight)
      .value("ImGuiCol_NavWindowingDimBg", ImGuiCol_::ImGuiCol_NavWindowingDimBg)
      .value("ImGuiCol_ModalWindowDimBg", ImGuiCol_::ImGuiCol_ModalWindowDimBg)
      .export_values();


  py::enum_<ImGuiStyleVar_>(m, "ImGuiStyleVar")
      .value("ImGuiStyleVar_Alpha", ImGuiStyleVar_::ImGuiStyleVar_Alpha)
      .value("ImGuiStyleVar_DisabledAlpha", ImGuiStyleVar_::ImGuiStyleVar_DisabledAlpha)
      .value("ImGuiStyleVar_WindowPadding", ImGuiStyleVar_::ImGuiStyleVar_WindowPadding)
      .value("ImGuiStyleVar_WindowRounding", ImGuiStyleVar_::ImGuiStyleVar_WindowRounding)
      .value("ImGuiStyleVar_WindowBorderSize", ImGuiStyleVar_::ImGuiStyleVar_WindowBorderSize)
      .value("ImGuiStyleVar_WindowMinSize", ImGuiStyleVar_::ImGuiStyleVar_WindowMinSize)
      .value("ImGuiStyleVar_WindowTitleAlign", ImGuiStyleVar_::ImGuiStyleVar_WindowTitleAlign)
      .value("ImGuiStyleVar_ChildRounding", ImGuiStyleVar_::ImGuiStyleVar_ChildRounding)
      .value("ImGuiStyleVar_ChildBorderSize", ImGuiStyleVar_::ImGuiStyleVar_ChildBorderSize)
      .value("ImGuiStyleVar_PopupRounding", ImGuiStyleVar_::ImGuiStyleVar_PopupRounding)
      .value("ImGuiStyleVar_PopupBorderSize", ImGuiStyleVar_::ImGuiStyleVar_PopupBorderSize)
      .value("ImGuiStyleVar_FramePadding", ImGuiStyleVar_::ImGuiStyleVar_FramePadding)
      .value("ImGuiStyleVar_FrameRounding", ImGuiStyleVar_::ImGuiStyleVar_FrameRounding)
      .value("ImGuiStyleVar_FrameBorderSize", ImGuiStyleVar_::ImGuiStyleVar_FrameBorderSize)
      .value("ImGuiStyleVar_ItemSpacing", ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing)
      .value("ImGuiStyleVar_ItemInnerSpacing", ImGuiStyleVar_::ImGuiStyleVar_ItemInnerSpacing)
      .value("ImGuiStyleVar_IndentSpacing", ImGuiStyleVar_::ImGuiStyleVar_IndentSpacing)
      .value("ImGuiStyleVar_CellPadding", ImGuiStyleVar_::ImGuiStyleVar_CellPadding)
      .value("ImGuiStyleVar_ScrollbarSize", ImGuiStyleVar_::ImGuiStyleVar_ScrollbarSize)
      .value("ImGuiStyleVar_ScrollbarRounding", ImGuiStyleVar_::ImGuiStyleVar_ScrollbarRounding)
      .value("ImGuiStyleVar_GrabMinSize", ImGuiStyleVar_::ImGuiStyleVar_GrabMinSize)
      .value("ImGuiStyleVar_GrabRounding", ImGuiStyleVar_::ImGuiStyleVar_GrabRounding)
      .value("ImGuiStyleVar_TabRounding", ImGuiStyleVar_::ImGuiStyleVar_TabRounding)
      .value("ImGuiStyleVar_TabBorderSize", ImGuiStyleVar_::ImGuiStyleVar_TabBorderSize)
      .value("ImGuiStyleVar_TabBarBorderSize", ImGuiStyleVar_::ImGuiStyleVar_TabBarBorderSize)
      .value("ImGuiStyleVar_TabBarOverlineSize", ImGuiStyleVar_::ImGuiStyleVar_TabBarOverlineSize)
      .value("ImGuiStyleVar_TableAngledHeadersAngle", ImGuiStyleVar_::ImGuiStyleVar_TableAngledHeadersAngle)
      .value("ImGuiStyleVar_TableAngledHeadersTextAlign", ImGuiStyleVar_::ImGuiStyleVar_TableAngledHeadersTextAlign)
      .value("ImGuiStyleVar_ButtonTextAlign", ImGuiStyleVar_::ImGuiStyleVar_ButtonTextAlign)
      .value("ImGuiStyleVar_SelectableTextAlign", ImGuiStyleVar_::ImGuiStyleVar_SelectableTextAlign)
      .value("ImGuiStyleVar_SeparatorTextBorderSize", ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextBorderSize)
      .value("ImGuiStyleVar_SeparatorTextAlign", ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextAlign)
      .value("ImGuiStyleVar_SeparatorTextPadding", ImGuiStyleVar_::ImGuiStyleVar_SeparatorTextPadding)
      .export_values();


  py::enum_<ImGuiButtonFlags_>(m, "ImGuiButtonFlags", py::arithmetic())
      .value("ImGuiButtonFlags_None", ImGuiButtonFlags_::ImGuiButtonFlags_None)
      .value("ImGuiButtonFlags_MouseButtonLeft", ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonLeft)
      .value("ImGuiButtonFlags_MouseButtonRight", ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonRight)
      .value("ImGuiButtonFlags_MouseButtonMiddle", ImGuiButtonFlags_::ImGuiButtonFlags_MouseButtonMiddle)
      .export_values();


  py::enum_<ImGuiColorEditFlags_>(m, "ImGuiColorEditFlags", py::arithmetic())
      .value("ImGuiColorEditFlags_None", ImGuiColorEditFlags_::ImGuiColorEditFlags_None)
      .value("ImGuiColorEditFlags_NoAlpha", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoAlpha)
      .value("ImGuiColorEditFlags_NoPicker", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoPicker)
      .value("ImGuiColorEditFlags_NoOptions", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoOptions)
      .value("ImGuiColorEditFlags_NoSmallPreview", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoSmallPreview)
      .value("ImGuiColorEditFlags_NoInputs", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs)
      .value("ImGuiColorEditFlags_NoTooltip", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoTooltip)
      .value("ImGuiColorEditFlags_NoLabel", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoLabel)
      .value("ImGuiColorEditFlags_NoSidePreview", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoSidePreview)
      .value("ImGuiColorEditFlags_NoDragDrop", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoDragDrop)
      .value("ImGuiColorEditFlags_NoBorder", ImGuiColorEditFlags_::ImGuiColorEditFlags_NoBorder)
      .value("ImGuiColorEditFlags_AlphaBar", ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar)
      .value("ImGuiColorEditFlags_AlphaPreview", ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreview)
      .value("ImGuiColorEditFlags_AlphaPreviewHalf", ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreviewHalf)
      .value("ImGuiColorEditFlags_HDR", ImGuiColorEditFlags_::ImGuiColorEditFlags_HDR)
      .value("ImGuiColorEditFlags_DisplayRGB", ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayRGB)
      .value("ImGuiColorEditFlags_DisplayHSV", ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayHSV)
      .value("ImGuiColorEditFlags_DisplayHex", ImGuiColorEditFlags_::ImGuiColorEditFlags_DisplayHex)
      .value("ImGuiColorEditFlags_Uint8", ImGuiColorEditFlags_::ImGuiColorEditFlags_Uint8)
      .value("ImGuiColorEditFlags_Float", ImGuiColorEditFlags_::ImGuiColorEditFlags_Float)
      .value("ImGuiColorEditFlags_PickerHueBar", ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueBar)
      .value("ImGuiColorEditFlags_PickerHueWheel", ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueWheel)
      .value("ImGuiColorEditFlags_InputRGB", ImGuiColorEditFlags_::ImGuiColorEditFlags_InputRGB)
      .value("ImGuiColorEditFlags_InputHSV", ImGuiColorEditFlags_::ImGuiColorEditFlags_InputHSV)
      .export_values();


  py::enum_<ImGuiSliderFlags_>(m, "ImGuiSliderFlags", py::arithmetic())
      .value("ImGuiSliderFlags_None", ImGuiSliderFlags_::ImGuiSliderFlags_None)
      .value("ImGuiSliderFlags_AlwaysClamp", ImGuiSliderFlags_::ImGuiSliderFlags_AlwaysClamp)
      .value("ImGuiSliderFlags_Logarithmic", ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic)
      .value("ImGuiSliderFlags_NoRoundToFormat", ImGuiSliderFlags_::ImGuiSliderFlags_NoRoundToFormat)
      .value("ImGuiSliderFlags_NoInput", ImGuiSliderFlags_::ImGuiSliderFlags_NoInput)
      .value("ImGuiSliderFlags_WrapAround", ImGuiSliderFlags_::ImGuiSliderFlags_WrapAround)
      .export_values();


  py::enum_<ImGuiMouseButton_>(m, "ImGuiMouseButton")
      .value("ImGuiMouseButton_Left", ImGuiMouseButton_::ImGuiMouseButton_Left)
      .value("ImGuiMouseButton_Right", ImGuiMouseButton_::ImGuiMouseButton_Right)
      .value("ImGuiMouseButton_Middle", ImGuiMouseButton_::ImGuiMouseButton_Middle)
      .value("ImGuiMouseButton_COUNT", ImGuiMouseButton_::ImGuiMouseButton_COUNT)
      .export_values();


  py::enum_<ImGuiMouseCursor_>(m, "ImGuiMouseCursor")
      .value("ImGuiMouseCursor_None", ImGuiMouseCursor_::ImGuiMouseCursor_None)
      .value("ImGuiMouseCursor_Arrow", ImGuiMouseCursor_::ImGuiMouseCursor_Arrow)
      .value("ImGuiMouseCursor_TextInput", ImGuiMouseCursor_::ImGuiMouseCursor_TextInput)
      .value("ImGuiMouseCursor_ResizeAll", ImGuiMouseCursor_::ImGuiMouseCursor_ResizeAll)
      .value("ImGuiMouseCursor_ResizeNS", ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNS)
      .value("ImGuiMouseCursor_ResizeEW", ImGuiMouseCursor_::ImGuiMouseCursor_ResizeEW)
      .value("ImGuiMouseCursor_ResizeNESW", ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNESW)
      .value("ImGuiMouseCursor_ResizeNWSE", ImGuiMouseCursor_::ImGuiMouseCursor_ResizeNWSE)
      .value("ImGuiMouseCursor_Hand", ImGuiMouseCursor_::ImGuiMouseCursor_Hand)
      .value("ImGuiMouseCursor_NotAllowed", ImGuiMouseCursor_::ImGuiMouseCursor_NotAllowed)
      .value("ImGuiMouseCursor_COUNT", ImGuiMouseCursor_::ImGuiMouseCursor_COUNT)
      .export_values();


  py::enum_<ImGuiMouseSource>(m, "ImGuiMouseSource")
      .value("ImGuiMouseSource_Mouse", ImGuiMouseSource::ImGuiMouseSource_Mouse)
      .value("ImGuiMouseSource_TouchScreen", ImGuiMouseSource::ImGuiMouseSource_TouchScreen)
      .value("ImGuiMouseSource_Pen", ImGuiMouseSource::ImGuiMouseSource_Pen)
      .value("ImGuiMouseSource_COUNT", ImGuiMouseSource::ImGuiMouseSource_COUNT)
      .export_values();


  py::enum_<ImGuiCond_>(m, "ImGuiCond")
      .value("ImGuiCond_None", ImGuiCond_::ImGuiCond_None)
      .value("ImGuiCond_Always", ImGuiCond_::ImGuiCond_Always)
      .value("ImGuiCond_Once", ImGuiCond_::ImGuiCond_Once)
      .value("ImGuiCond_FirstUseEver", ImGuiCond_::ImGuiCond_FirstUseEver)
      .value("ImGuiCond_Appearing", ImGuiCond_::ImGuiCond_Appearing)
      .export_values();


  py::enum_<ImGuiTableFlags_>(m, "ImGuiTableFlags", py::arithmetic())
      .value("ImGuiTableFlags_None", ImGuiTableFlags_::ImGuiTableFlags_None)
      .value("ImGuiTableFlags_Resizable", ImGuiTableFlags_::ImGuiTableFlags_Resizable)
      .value("ImGuiTableFlags_Reorderable", ImGuiTableFlags_::ImGuiTableFlags_Reorderable)
      .value("ImGuiTableFlags_Hideable", ImGuiTableFlags_::ImGuiTableFlags_Hideable)
      .value("ImGuiTableFlags_Sortable", ImGuiTableFlags_::ImGuiTableFlags_Sortable)
      .value("ImGuiTableFlags_NoSavedSettings", ImGuiTableFlags_::ImGuiTableFlags_NoSavedSettings)
      .value("ImGuiTableFlags_ContextMenuInBody", ImGuiTableFlags_::ImGuiTableFlags_ContextMenuInBody)
      .value("ImGuiTableFlags_RowBg", ImGuiTableFlags_::ImGuiTableFlags_RowBg)
      .value("ImGuiTableFlags_BordersInnerH", ImGuiTableFlags_::ImGuiTableFlags_BordersInnerH)
      .value("ImGuiTableFlags_BordersOuterH", ImGuiTableFlags_::ImGuiTableFlags_BordersOuterH)
      .value("ImGuiTableFlags_BordersInnerV", ImGuiTableFlags_::ImGuiTableFlags_BordersInnerV)
      .value("ImGuiTableFlags_BordersOuterV", ImGuiTableFlags_::ImGuiTableFlags_BordersOuterV)
      .value("ImGuiTableFlags_BordersH", ImGuiTableFlags_::ImGuiTableFlags_BordersH)
      .value("ImGuiTableFlags_BordersV", ImGuiTableFlags_::ImGuiTableFlags_BordersV)
      .value("ImGuiTableFlags_BordersInner", ImGuiTableFlags_::ImGuiTableFlags_BordersInner)
      .value("ImGuiTableFlags_BordersOuter", ImGuiTableFlags_::ImGuiTableFlags_BordersOuter)
      .value("ImGuiTableFlags_Borders", ImGuiTableFlags_::ImGuiTableFlags_Borders)
      .value("ImGuiTableFlags_NoBordersInBody", ImGuiTableFlags_::ImGuiTableFlags_NoBordersInBody)
      .value("ImGuiTableFlags_NoBordersInBodyUntilResize", ImGuiTableFlags_::ImGuiTableFlags_NoBordersInBodyUntilResize)
      .value("ImGuiTableFlags_SizingFixedFit", ImGuiTableFlags_::ImGuiTableFlags_SizingFixedFit)
      .value("ImGuiTableFlags_SizingFixedSame", ImGuiTableFlags_::ImGuiTableFlags_SizingFixedSame)
      .value("ImGuiTableFlags_SizingStretchProp", ImGuiTableFlags_::ImGuiTableFlags_SizingStretchProp)
      .value("ImGuiTableFlags_SizingStretchSame", ImGuiTableFlags_::ImGuiTableFlags_SizingStretchSame)
      .value("ImGuiTableFlags_NoHostExtendX", ImGuiTableFlags_::ImGuiTableFlags_NoHostExtendX)
      .value("ImGuiTableFlags_NoHostExtendY", ImGuiTableFlags_::ImGuiTableFlags_NoHostExtendY)
      .value("ImGuiTableFlags_NoKeepColumnsVisible", ImGuiTableFlags_::ImGuiTableFlags_NoKeepColumnsVisible)
      .value("ImGuiTableFlags_PreciseWidths", ImGuiTableFlags_::ImGuiTableFlags_PreciseWidths)
      .value("ImGuiTableFlags_NoClip", ImGuiTableFlags_::ImGuiTableFlags_NoClip)
      .value("ImGuiTableFlags_PadOuterX", ImGuiTableFlags_::ImGuiTableFlags_PadOuterX)
      .value("ImGuiTableFlags_NoPadOuterX", ImGuiTableFlags_::ImGuiTableFlags_NoPadOuterX)
      .value("ImGuiTableFlags_NoPadInnerX", ImGuiTableFlags_::ImGuiTableFlags_NoPadInnerX)
      .value("ImGuiTableFlags_ScrollX", ImGuiTableFlags_::ImGuiTableFlags_ScrollX)
      .value("ImGuiTableFlags_ScrollY", ImGuiTableFlags_::ImGuiTableFlags_ScrollY)
      .value("ImGuiTableFlags_SortMulti", ImGuiTableFlags_::ImGuiTableFlags_SortMulti)
      .value("ImGuiTableFlags_SortTristate", ImGuiTableFlags_::ImGuiTableFlags_SortTristate)
      .value("ImGuiTableFlags_HighlightHoveredColumn", ImGuiTableFlags_::ImGuiTableFlags_HighlightHoveredColumn)
      .value("ImGuiTableFlags_SizingMask_", ImGuiTableFlags_::ImGuiTableFlags_SizingMask_)
      .export_values();


  py::enum_<ImGuiTableColumnFlags_>(m, "ImGuiTableColumnFlags", py::arithmetic())
      .value("ImGuiTableColumnFlags_None", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_None)
      .value("ImGuiTableColumnFlags_Disabled", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_Disabled)
      .value("ImGuiTableColumnFlags_DefaultHide", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_DefaultHide)
      .value("ImGuiTableColumnFlags_DefaultSort", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_DefaultSort)
      .value("ImGuiTableColumnFlags_WidthStretch", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthStretch)
      .value("ImGuiTableColumnFlags_WidthFixed", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthFixed)
      .value("ImGuiTableColumnFlags_NoResize", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoResize)
      .value("ImGuiTableColumnFlags_NoReorder", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoReorder)
      .value("ImGuiTableColumnFlags_NoHide", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHide)
      .value("ImGuiTableColumnFlags_NoClip", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoClip)
      .value("ImGuiTableColumnFlags_NoSort", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSort)
      .value("ImGuiTableColumnFlags_NoSortAscending", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSortAscending)
      .value("ImGuiTableColumnFlags_NoSortDescending", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoSortDescending)
      .value("ImGuiTableColumnFlags_NoHeaderLabel", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHeaderLabel)
      .value("ImGuiTableColumnFlags_NoHeaderWidth", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoHeaderWidth)
      .value("ImGuiTableColumnFlags_PreferSortAscending",
             ImGuiTableColumnFlags_::ImGuiTableColumnFlags_PreferSortAscending)
      .value("ImGuiTableColumnFlags_PreferSortDescending",
             ImGuiTableColumnFlags_::ImGuiTableColumnFlags_PreferSortDescending)
      .value("ImGuiTableColumnFlags_IndentEnable", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentEnable)
      .value("ImGuiTableColumnFlags_IndentDisable", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentDisable)
      .value("ImGuiTableColumnFlags_AngledHeader", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_AngledHeader)
      .value("ImGuiTableColumnFlags_IsEnabled", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsEnabled)
      .value("ImGuiTableColumnFlags_IsVisible", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsVisible)
      .value("ImGuiTableColumnFlags_IsSorted", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsSorted)
      .value("ImGuiTableColumnFlags_IsHovered", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IsHovered)
      .value("ImGuiTableColumnFlags_WidthMask_", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_WidthMask_)
      .value("ImGuiTableColumnFlags_IndentMask_", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_IndentMask_)
      .value("ImGuiTableColumnFlags_StatusMask_", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_StatusMask_)
      .value("ImGuiTableColumnFlags_NoDirectResize_", ImGuiTableColumnFlags_::ImGuiTableColumnFlags_NoDirectResize_)
      .export_values();


  py::enum_<ImGuiTableRowFlags_>(m, "ImGuiTableRowFlags", py::arithmetic())
      .value("ImGuiTableRowFlags_None", ImGuiTableRowFlags_::ImGuiTableRowFlags_None)
      .value("ImGuiTableRowFlags_Headers", ImGuiTableRowFlags_::ImGuiTableRowFlags_Headers)
      .export_values();


  py::enum_<ImGuiTableBgTarget_>(m, "ImGuiTableBgTarget")
      .value("ImGuiTableBgTarget_None", ImGuiTableBgTarget_::ImGuiTableBgTarget_None)
      .value("ImGuiTableBgTarget_RowBg0", ImGuiTableBgTarget_::ImGuiTableBgTarget_RowBg0)
      .value("ImGuiTableBgTarget_RowBg1", ImGuiTableBgTarget_::ImGuiTableBgTarget_RowBg1)
      .value("ImGuiTableBgTarget_CellBg", ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg)
      .export_values();
}

void bind_imgui(py::module& m) {
  auto mod_imgui = m.def_submodule("imgui", "ImGui bindings");
  bind_imgui_funcs(mod_imgui);
  bind_imgui_enums(mod_imgui);
}
