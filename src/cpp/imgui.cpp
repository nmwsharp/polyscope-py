#include "imgui.h"
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Type translations between Python and ImGui.  Prefer native Python types (tuples, arrays), translating into ImGui
// equivalents.
using Vec2T = std::tuple<float, float>;
using Vec4T = std::tuple<float, float, float, float>;

ImVec2 to_vec2(const Vec2T& v) { return ImVec2(std::get<0>(v), std::get<1>(v)); }
ImVec4 to_vec4(const Vec4T& v) { return ImVec4(std::get<0>(v), std::get<1>(v), std::get<2>(v), std::get<3>(v)); }

Vec2T from_vec2(const ImVec2& v) { return std::make_tuple(v.x, v.y); }
Vec4T from_vec4(const ImVec4& v) { return std::make_tuple(v.x, v.y, v.z, v.w); }

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
void bind_imgui(py::module& parent_module) {

    auto m = parent_module.def_submodule("imgui", "ImGui bindings");

    py::enum_<ImGuiCond_>(m, "ImGuiCond_")
        .value("ImGuiCond_Always", ImGuiCond_Always)
        .value("ImGuiCond_Once", ImGuiCond_Once)
        .value("ImGuiCond_FirstUseEver", ImGuiCond_FirstUseEver)
        .value("ImGuiCond_Appearing", ImGuiCond_Appearing);

    // Parameters stacks (shared)
    // m.def("PushFront")
    // m.def("PopFront")
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
    // GetFont
    m.def("GetFontSize", []() { return ImGui::GetFontSize(); });
    m.def("GetFontTexUvWhitePixel",
          []() { return from_vec2(ImGui::GetFontTexUvWhitePixel()); });
    m.def(
        "GetColorU32",
        [](ImGuiCol idx, float alpha_mul) { return ImGui::GetColorU32(idx, alpha_mul); },
        py::arg("idx"),
        py::arg("alpha_mul") = 1.0f);
    m.def(
        "GetColorU32", [](const ImVec4& col) { return ImGui::GetColorU32(col); }, py::arg("col"));
    m.def(
        "GetColorU32", [](ImU32 col) { return ImGui::GetColorU32(col); }, py::arg("col"));

    // Cursor / Layout
    m.def("separator", []() { ImGui::Separator(); });
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
        [](const Vec2T& local_pos) { return ImGui::SetCursorPos(to_vec2(local_pos)); },
        py::arg("local_pos"));
    m.def(
        "SetCursorPosX",
        [](float local_x) { return ImGui::SetCursorPosX(local_x); },
        py::arg("local_x"));
    m.def(
        "SetCursorPosY",
        [](float local_y) { return ImGui::SetCursorPosY(local_y); },
        py::arg("local_y"));
    m.def("GetCursorStartPos", []() { return from_vec2(ImGui::GetCursorStartPos()); });
    m.def("GetCursorScreenPos", []() { return from_vec2(ImGui::GetCursorScreenPos()); });
    m.def(
        "SetCursorScreenPos",
        [](const Vec2T& pos) { return ImGui::SetCursorScreenPos(to_vec2(pos)); },
        py::arg("pos"));
    m.def("AlignTextToFramePadding", []() { ImGui::AlignTextToFramePadding(); });
    m.def("GetTextLineHeight", []() { ImGui::GetTextLineHeight(); });
    m.def("GetTextLineHeightWithSpacing", []() { ImGui::GetTextLineHeightWithSpacing(); });
    m.def("GetFrameHeight", []() { ImGui::GetFrameHeight(); });
    m.def("GetFrameHeightWithSpacing", []() { ImGui::GetFrameHeightWithSpacing(); });

    // Parameters stacks (current window)
    m.def(
        "PushItemWidth",
        [](float item_width) { ImGui::PushItemWidth(item_width); },
        py::arg("item_width"));
    m.def("PopItemWidth", []() { ImGui::PopItemWidth(); });
    m.def(
        "PushItemWidth",
        [](float item_width) { ImGui::SetNextItemWidth(item_width); },
        py::arg("item_width"));
    m.def("CalcItemWidth", []() { return ImGui::CalcItemWidth(); });
    m.def(
        "PushTextWrapPos",
        [](float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); },
        py::arg("wrap_local_pos_x") = 0.0f);
    m.def("PopTextWrapPos", []() { return ImGui::PopTextWrapPos(); });
    m.def(
        "PushAllowKeyboardFocus",
        [](bool allow_keyboard_focus) { ImGui::PushAllowKeyboardFocus(allow_keyboard_focus); },
        py::arg("allow_keyboard_focus"));
    m.def("PopAllowKeyboardFocus", []() { return ImGui::PopAllowKeyboardFocus(); });
    m.def(
        "PushButtonRepeat",
        [](bool repeat) { ImGui::PushButtonRepeat(repeat); },
        py::arg("allow_keyboard_focus"));
    m.def("PopButtonRepeat", []() { return ImGui::PopButtonRepeat(); });

    // ID stack/scopes
    m.def(
        "PushId", [](const char* str_id) { ImGui::PushID(str_id); }, py::arg("str_id"));
    m.def("PopID", []() { ImGui::PopID(); });
    m.def(
        "GetId", [](const char* str_id) { ImGui::GetID(str_id); }, py::arg("str_id"));

    // Widgets: Text
    m.def(
        "Text", [](const char* fmt) { ImGui::Text("%s", fmt); }, py::arg("text"));
    m.def(
        "TextColored",
        [](const Vec4T& color, const char* fmt) { ImGui::TextColored(to_vec4(color), "%s", fmt); },
        py::arg("color"),
        py::arg("text"));
    m.def(
        "TextDisabled", [](const char* fmt) { ImGui::TextDisabled("%s", fmt); }, py::arg("text"));
    m.def(
        "TextWrapped", [](const char* fmt) { ImGui::TextWrapped("%s", fmt); }, py::arg("text"));
    m.def(
        "LabelText",
        [](const char* label, const char* fmt) { ImGui::LabelText(label, "%s", fmt); },
        py::arg("label"),
        py::arg("text"));
    m.def(
        "BulletText",
        [](const char* label, const char* fmt) { ImGui::BulletText(label, "%s", fmt); },
        py::arg("label"),
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
    // Image
    // ImageButton
    m.def(
        "Checkbox",
        [](const char* label, bool v) {
            auto v_ = v;
            const auto clicked = ImGui::Checkbox(label, &v_);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"));
    m.def(
        "CheckboxFlags",
        [](const char* label, unsigned int flags, unsigned int flags_value) {
            auto flags_ = flags;
            const auto clicked = ImGui::CheckboxFlags(label, &flags_, flags_value);
            return std::make_tuple(clicked, flags_);
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
        [](const char* label, unsigned int v, unsigned int v_button) {
            auto v_ = v;
            const auto clicked = ImGui::CheckboxFlags(label, &v_, v_button);
            return std::make_tuple(clicked, v_);
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
        py::arg("flags"));
    m.def("EndCombo", []() { ImGui::EndCombo(); });
    m.def(
        "Combo",
        [](const char* label,
           int current_item,
           const std::vector<const char*>& items,
           int popup_max_height_in_items) {
            auto current_item_ = current_item;
            const auto clicked = ImGui::Combo(
                label, &current_item_, items.data(), items.size(), popup_max_height_in_items);
            return std::make_tuple(clicked, current_item_);
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
            auto current_item_ = current_item;
            const auto clicked = ImGui::Combo(
                label, &current_item_, items_separated_by_zeros, popup_max_height_in_items);
            return std::make_tuple(clicked, current_item_);
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
            auto v_ = v;
            auto clicked = ImGui::DragFloat(label, &v_, v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "DragFloat2",
        [](const char* label,
           const std::array<float, 2>& v,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked =
                ImGui::DragFloat2(label, v_.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "DragFloat3",
        [](const char* label,
           const std::array<float, 3>& v,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked =
                ImGui::DragFloat3(label, v_.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "DragFloat4",
        [](const char* label,
           const std::array<float, 4>& v,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked =
                ImGui::DragFloat4(label, v_.data(), v_speed, v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "DragFloatRange2",
        [](const char* label,
           const std::array<float, 2>& v_current_min,
           const std::array<float, 2>& v_current_max,
           float v_speed,
           float v_min,
           float v_max,
           const char* format,
           const char* format_max,
           float power) {
            auto v_current_min_ = v_current_min;
            auto v_current_max_ = v_current_max;
            auto clicked = ImGui::DragFloatRange2(label,
                                                  v_current_min_.data(),
                                                  v_current_max_.data(),
                                                  v_speed,
                                                  v_min,
                                                  v_max,
                                                  format,
                                                  format_max,
                                                  power);
            return std::make_tuple(clicked, v_current_min_, v_current_max_);
        },
        py::arg("label"),
        py::arg("v_current_min"),
        py::arg("v_current_max"),
        py::arg("v_speed") = 1.0f,
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("format_max") = nullptr,
        py::arg("power") = 1.0f);

    m.def(
        "DragInt",
        [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format) {
            auto v_ = v;
            auto clicked = ImGui::DragInt(label, &v_, v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
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
           const std::array<int, 2>& v,
           float v_speed,
           int v_min,
           int v_max,
           const char* format) {
            auto v_ = v;
            auto clicked = ImGui::DragInt2(label, v_.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
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
           const std::array<int, 3>& v,
           float v_speed,
           int v_min,
           int v_max,
           const char* format) {
            auto v_ = v;
            auto clicked = ImGui::DragInt3(label, v_.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
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
           const std::array<int, 4>& v,
           float v_speed,
           int v_min,
           int v_max,
           const char* format) {
            auto v_ = v;
            auto clicked = ImGui::DragInt4(label, v_.data(), v_speed, v_min, v_max, format);
            return std::make_tuple(clicked, v_);
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
           const std::array<int, 2>& v_current_min,
           const std::array<int, 2>& v_current_max,
           float v_speed,
           int v_min,
           int v_max,
           const char* format,
           const char* format_max) {
            auto v_current_min_ = v_current_min;
            auto v_current_max_ = v_current_max;
            auto clicked = ImGui::DragIntRange2(label,
                                                v_current_min_.data(),
                                                v_current_max_.data(),
                                                v_speed,
                                                v_min,
                                                v_max,
                                                format,
                                                format_max);
            return std::make_tuple(clicked, v_current_min_, v_current_max_);
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
            auto v_ = v;
            auto clicked = ImGui::SliderFloat(label, &v_, v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "SliderFloat2",
        [](const char* label,
           const std::array<float, 2>& v,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked = ImGui::SliderFloat2(label, v_.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "SliderFloat3",
        [](const char* label,
           const std::array<float, 3>& v,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked = ImGui::SliderFloat3(label, v_.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);
    m.def(
        "SliderFloat4",
        [](const char* label,
           const std::array<float, 4>& v,
           float v_min,
           float v_max,
           const char* format,
           float power) {
            auto v_ = v;
            auto clicked = ImGui::SliderFloat4(label, v_.data(), v_min, v_max, format, power);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("v_min") = 0.0f,
        py::arg("v_max") = 0.0f,
        py::arg("format") = "%.3f",
        py::arg("power") = 1.0f);

    m.def(
        "SliderAngle",
        [](const char* label,
           float v_rad,
           float v_degrees_min,
           float v_degrees_max,
           const char* format) {
            auto v_rad_ = v_rad;
            auto clicked = ImGui::SliderAngle(label, &v_rad_, v_degrees_min, v_degrees_max, format);
            return std::make_tuple(clicked, v_rad_);
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
            auto v_ = v;
            const auto clicked = ImGui::InputFloat(label, &v_, step, step_fast, format, flags);
            return std::make_tuple(clicked, v_);
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
           const std::array<float, 2>& v,
           const char* format,
           ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputFloat2(label, v_.data(), format, flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputFloat3",
        [](const char* label,
           const std::array<float, 3>& v,
           const char* format,
           ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputFloat3(label, v_.data(), format, flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputFloat4",
        [](const char* label,
           const std::array<float, 4>& v,
           const char* format,
           ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputFloat4(label, v_.data(), format, flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("format") = "%.3f",
        py::arg("flags") = 0);
    m.def(
        "InputInt",
        [](const char* label, int v, float step, float step_fast, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt(label, &v_, step, step_fast, flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("step") = 0.f,
        py::arg("step_fast") = 0.f,
        py::arg("flags") = 0);
    m.def(
        "InputInt2",
        [](const char* label, const std::array<int, 2>& v, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt2(label, v_.data(), flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("flags") = 0);
    m.def(
        "InputInt3",
        [](const char* label, const std::array<int, 3>& v, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt3(label, v_.data(), flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
        py::arg("flags") = 0);
    m.def(
        "InputInt4",
        [](const char* label, const std::array<int, 4>& v, ImGuiInputTextFlags flags) {
            auto v_ = v;
            const auto clicked = ImGui::InputInt4(label, v_.data(), flags);
            return std::make_tuple(clicked, v_);
        },
        py::arg("label"),
        py::arg("v"),
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
    m.def("tree_pop", []() { ImGui::TreePop(); });
    m.def("get_tree_node_to_label_spacing", []() { return ImGui::GetTreeNodeToLabelSpacing(); });
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
            auto open_ = open;
            const auto clicked = ImGui::CollapsingHeader(label, &open_, flags);
            return std::make_tuple(clicked, open_);
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
            auto selected_ = selected;
            const auto clicked = ImGui::Selectable(label, &selected, flags, to_vec2(size));
            return std::make_tuple(clicked, selected_);
        },
        py::arg("label"),
        py::arg("selected"),
        py::arg("flags") = 0,
        py::arg("size") = std::make_tuple(0.f, 0.f));

    // Widgets: List Boxes
    m.def(
        "ListBox",
        [](const char* label,
           int current_item,
           const std::vector<const char*>& items,
           int height_in_items) {
            auto current_item_ = current_item;
            const auto clicked =
                ImGui::ListBox(label, &current_item_, items.data(), items.size(), height_in_items);
            return std::make_tuple(clicked, current_item_);
        },
        py::arg("label"),
        py::arg("current_item"),
        py::arg("items"),
        py::arg("height_in_items") = -1);

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
    m.def("end_menu", []() { ImGui::EndMenu(); });
    m.def(
        "MenuItem",
        [](const char* label, const char* shortcut, bool selected, bool enabled) {
            return ImGui::MenuItem(label, shortcut, selected, enabled);
        },
        py::arg("label"),
        py::arg("shortcut") = nullptr,
        py::arg("selected") = false,
        py::arg("enabled") = true);

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
        [](const char* str_id, ImGuiMouseButton mouse_button) {
            return ImGui::BeginPopupContextItem(str_id, mouse_button);
        },
        py::arg("str_id"),
        py::arg("mouse_button") = 1);
    m.def(
        "BeginPopupContextWindow",
        [](const char* str_id, ImGuiMouseButton mouse_button, bool also_over_items) {
            return ImGui::BeginPopupContextWindow(str_id, mouse_button, also_over_items);
        },
        py::arg("str_id"),
        py::arg("mouse_button") = 1,
        py::arg("also_over_items") = true);
    m.def(
        "BeginPopupContextVoid",
        [](const char* str_id, ImGuiMouseButton mouse_button) {
            return ImGui::BeginPopupContextVoid(str_id, mouse_button);
        },
        py::arg("str_id"),
        py::arg("mouse_button") = 1);
    m.def(
        "BeginPopupModal",
        [](const char* str_id, bool open, ImGuiWindowFlags flags) {
            auto open_ = open;
            return ImGui::BeginPopupModal(str_id, &open_, flags);
        },
        py::arg("str_id"),
        py::arg("open"),
        py::arg("flags") = 0);
    m.def("end_popup", []() { ImGui::EndPopup(); });
    m.def(
        "OpenPopupOnItemClick",
        [](const char* str_id, ImGuiMouseButton mouse_button) {
            return ImGui::OpenPopupOnItemClick(str_id, mouse_button);
        },
        py::arg("str_id"),
        py::arg("mouse_button") = 1);
    m.def(
        "IsPopupOpen",
        [](const char* str_id) { return ImGui::IsPopupOpen(str_id); },
        py::arg("str_id"));
    m.def("close_current_popup", []() { ImGui::CloseCurrentPopup(); });

    // Windows
    m.def(
        "Begin",
        [](const char* name, bool open, ImGuiWindowFlags flags) {
            auto open_ = open;
            const auto clicked = ImGui::Begin(name, &open_, flags);
            return std::make_tuple(clicked, open_);
        },
        py::arg("name"),
        py::arg("open"),
        py::arg("flags") = 0);
    m.def("end", []() { ImGui::End(); });

    // Item/Widgets Utilities
    m.def(
        "IsItemHovered",
        [](ImGuiHoveredFlags flags) { return ImGui::IsItemHovered(flags); },
        py::arg("flags") = 0);
    m.def("is_item_active", []() { return ImGui::IsItemActive(); });
    m.def("is_item_focused", []() { return ImGui::IsItemFocused(); });
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
}

