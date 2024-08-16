from typing import List, Optional, Callable
import json
from pathlib import Path
from pydantic import BaseModel
from collections import defaultdict


class Parameter(BaseModel):
    name: str
    type: str
    default: Optional[str] = None


class Function(BaseModel):
    name: str
    return_type: str
    parameters: List[Parameter]
    description: Optional[str] = None


class Functions(BaseModel):
    namespace: str
    functions: List[Function]


class EnumValue(BaseModel):
    name: str
    value: Optional[str | int] = None
    description: Optional[str] = None


class Enum(BaseModel):
    name: str
    values: List[EnumValue]


class Library(BaseModel):
    functions: Functions
    enums: List[Enum]


library = Library.parse_obj(
    json.loads((Path(__file__).parent / "imgui-bindings.json").read_bytes())
)


class ArgBinding(BaseModel):
    arg_name: Optional[str] = None
    arg_type: Optional[str] = None
    arg_default: Optional[str] = None
    decl_name: Optional[str] = None
    decl: Optional[str] = None
    ret: Optional[str] = None


def const_char_ptr(param: Parameter) -> ArgBinding:
    arg_default = None
    if param.default == "NULL":
        arg_default = '""'
    return ArgBinding(
        arg_name=param.name,
        arg_type=param.type,
        arg_default=arg_default,
        decl_name=param.name,
        decl=None,
        ret=None,
    )


def bool_ptr(param: Parameter) -> ArgBinding:
    if param.default is not None and param.default == "NULL":
        arg_name = "open"
        arg_type = "std::optional<bool>"
        decl_name = param.name
        decl = f"bool *{decl_name} = {arg_name}.has_value() ? &{arg_name}.value() : nullptr;"
        ret = arg_name
        return ArgBinding(
            arg_name=arg_name,
            arg_type=arg_type,
            arg_default="std::nullopt",
            decl_name=decl_name,
            decl=decl,
            ret=ret,
        )
    else:
        arg_name = f"{param.name}_"
        decl = f"bool *{param.name} = &{param.name}_;"
        return ArgBinding(
            arg_name=arg_name,
            arg_type="bool",
            arg_default=None,
            decl_name=param.name,
            decl=decl,
            ret=param.name,
        )


def pass_thru(param: Parameter) -> ArgBinding:
    return ArgBinding(
        arg_name=param.name,
        arg_type=param.type,
        arg_default=param.default,
        decl_name=param.name,
        decl=None,
        ret=None,
    )


def ptr(param: Parameter, type: str) -> ArgBinding:
    arg_name = f"{param.name}_"
    decl = f"{type} *{param.name} = &{param.name}_;"
    return ArgBinding(
        arg_name=arg_name,
        arg_type=type,
        arg_default=param.default,
        decl_name=param.name,
        decl=decl,
        ret=param.name,
    )


double_ptr = lambda param: ptr(param, "double")
float_ptr = lambda param: ptr(param, "float")
int_ptr = lambda param: ptr(param, "int")


def const_char_ptr_array(param: Parameter) -> ArgBinding:
    arg_name = f"{param.name}_"
    decl = f"const auto {param.name} = convert_string_items({param.name}_);"
    return ArgBinding(
        arg_name=arg_name,
        arg_type="const std::vector<std::string>&",
        arg_default=param.default,
        decl_name=f"{param.name}.data()",
        decl=decl,
        ret=None,
    )


def imgui_style_ptr(param: Parameter) -> ArgBinding:
    return ArgBinding(
        arg_name=None,
        arg_type=None,
        arg_default=None,
        decl_name=None,
        decl=None,
        ret=None,
    )


def array_n(param: Parameter, type: str, n: int) -> ArgBinding:
    return ArgBinding(
        arg_name=param.name,
        arg_type=f"std::array<{type}, {n}>",
        arg_default=param.default,
        decl_name=f"{param.name}.data()",
        decl=None,
        ret=param.name,
    )


float_array_2 = lambda param: array_n(param, "float", 2)
float_array_3 = lambda param: array_n(param, "float", 3)
float_array_4 = lambda param: array_n(param, "float", 4)
int_array_2 = lambda param: array_n(param, "int", 2)
int_array_3 = lambda param: array_n(param, "int", 3)
int_array_4 = lambda param: array_n(param, "int", 4)


param_dispatch = {
    "bool*": bool_ptr,
    "bool": pass_thru,
    "const char*": const_char_ptr,
    "ImGuiWindowFlags": pass_thru,
    "ImGuiTreeNodeFlags": pass_thru,
    "ImGuiSelectableFlags": pass_thru,
    "ImGuiInputTextFlags": pass_thru,
    "ImGuiPopupFlags": pass_thru,
    "ImGuiID": pass_thru,
    "ImGuiCol": pass_thru,
    "double*": double_ptr,
    "float*": float_ptr,
    "float[2]": float_array_2,
    "float[3]": float_array_3,
    "float[4]": float_array_4,
    "double": pass_thru,
    "float": pass_thru,
    "int": pass_thru,
    "ImU32": pass_thru,
    "unsigned int": pass_thru,
    "int*": int_ptr,
    "int[2]": int_array_2,
    "int[3]": int_array_3,
    "int[4]": int_array_4,
    "unsigned int*": int_ptr,
    "ImGuiSliderFlags": pass_thru,
    "ImGuiColorEditFlags": pass_thru,
    "ImGuiCond": pass_thru,
    "const ImVec2&": pass_thru,
    "const ImVec4&": pass_thru,
    "ImGuiChildFlags": pass_thru,
    "ImGuiStyleVar": pass_thru,
    "const char* const[]": const_char_ptr_array,
    "ImGuiStyle*": imgui_style_ptr,
}

# TODO: see combo for changing arg names


def esc_description(desc: str) -> str:
    return desc.replace('"', '\\"')


def combo_items_count_param(param: Parameter) -> ArgBinding:
    decl = f"const auto {param.name} = items_.size();"
    return ArgBinding(
        arg_name=None,
        arg_type=None,
        arg_default=None,
        decl_name=param.name,
        decl=decl,
        ret=None,
    )


def color_picker4_ref_col(param: Parameter) -> ArgBinding:
    decl_name = f"{param.name}_"
    decl = f"const float * {decl_name} = {param.name} ? &{param.name}.value()[0] : nullptr;"
    return ArgBinding(
        arg_name=param.name,
        arg_type="const std::optional<std::array<float, 4>>&",
        arg_default="std::nullopt",
        decl_name=decl_name,
        decl=decl,
        ret=None,
    )


def route_param(param: Parameter, func: Function) -> Callable[[Parameter], ArgBinding]:
    if func.name == "Combo" and param.name == "items_count":
        return combo_items_count_param
    if func.name == "ColorPicker4" and param.name == "ref_col":
        return color_picker4_ref_col

    if param.type not in param_dispatch:
        raise ValueError(
            f"Unknown parameter type: {param.type} in function {func.name}"
        )

    return param_dispatch[param.type]


def basic(namespace: str, func: Function) -> str:
    def_args = [
        f'"{func.name}"',
        f"&{namespace}::{func.name}",
    ]
    if func.description is not None:
        def_args.append(f'"{esc_description(func.description)}"')

    py_arg_vals = []
    for param in func.parameters:
        py_arg_val = f'py::arg("{param.name}")'
        if param.default is not None:
            py_arg_val = f"{py_arg_val} = {param.default}"
        py_arg_vals.append(py_arg_val)

    if len(py_arg_vals) > 0:
        def_args.append(", ".join(py_arg_vals))

    return f'm.def({", ".join(def_args)});'


def basic_ref_binding(namespace: str, func: Function) -> str:
    if func.description is None:
        return f'm.def("{func.name}", &{namespace}::{func.name}, py::return_value_policy::reference);'
    else:
        return f'm.def("{func.name}", &{namespace}::{func.name}, "{esc_description(func.description)}", py::return_value_policy::reference);'


def wrapped_binding(namespace: str, func: Function) -> str:
    arg_bindings: List[ArgBinding] = []
    for param in func.parameters:
        f = route_param(param, func)
        arg_bindings.append(f(param))

    arg_vals = []
    for arg_binding in arg_bindings:
        if arg_binding.arg_name is not None and arg_binding.arg_type is not None:
            arg_vals.append(f"{arg_binding.arg_type} {arg_binding.arg_name}")
    args = ", ".join(arg_vals)

    params_decl = "\n".join(
        [
            arg_binding.decl
            for arg_binding in arg_bindings
            if arg_binding.decl is not None
        ]
    )
    params = ", ".join(
        [
            arg_binding.decl_name
            for arg_binding in arg_bindings
            if arg_binding.decl_name is not None
        ]
    )

    rets = []
    if func.return_type == "void":
        call_ret = ""
    else:
        rets.append("res_")
        call_ret = "const auto res_ = "

    for arg_binding in arg_bindings:
        if arg_binding.ret is not None:
            rets.append(arg_binding.ret)
    if len(rets) == 0:
        ret = ""
    elif len(rets) == 1:
        ret = f"return {rets[0]};"
    else:
        ret_args = ", ".join(rets)
        ret = f"return std::make_tuple({ret_args});"

    py_arg_vals = []
    for arg_binding in arg_bindings:
        if arg_binding.arg_name is not None:
            py_arg_val = f'py::arg("{arg_binding.arg_name}")'
            if arg_binding.arg_default is not None:
                py_arg_val = f"{py_arg_val} = {arg_binding.arg_default}"
            py_arg_vals.append(py_arg_val)

    wrap = f"""
    []({args}) {{
        {params_decl}
        {call_ret}{namespace}::{func.name}({params});
        {ret}
    }}
    """

    def_args = [
        f'"{func.name}"',
        wrap,
    ]
    if func.description is not None:
        def_args.append(f'"{esc_description(func.description)}"')
    if len(py_arg_vals) > 0:
        def_args.append(", ".join(py_arg_vals))

    return f'm.def({", ".join(def_args)});'


def fmt_vararg(namespace: str, func: Function) -> str:
    arg_bindings: List[ArgBinding] = []
    for param in func.parameters:
        if param.name in {"fmt", "..."}:
            continue

        f = route_param(param, func)
        arg_bindings.append(f(param))

    args = [
        f"{arg_binding.arg_type} {arg_binding.arg_name}"
        for arg_binding in arg_bindings
        if arg_binding.arg_name is not None
    ]
    args.append("const char* text")
    gen_args = ", ".join(args)

    arg_params = [
        arg_binding.decl_name
        for arg_binding in arg_bindings
        if arg_binding.decl_name is not None
    ]
    arg_params.append('"%s"')
    arg_params.append("text")
    gen_arg_params = ", ".join(arg_params)

    py_args = [
        f'py::arg("{arg_binding.decl_name}")'
        for arg_binding in arg_bindings
        if arg_binding.decl_name is not None
    ]
    py_args.append('py::arg("text")')

    impl = f"[]({gen_args}) {{ {namespace}::{func.name}({gen_arg_params}); }}"
    def_args = [f'"{func.name}"', impl, *py_args]
    return f'm.def({", ".join(def_args)});'


def wrap_input_text(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        [](const char* label,
            const std::string& str,
            ImGuiInputTextFlags flags) {{
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto str_ = str;
            const auto clicked = {namespace}::{func.name}(label, &str_, flags);
            return std::make_tuple(clicked, str_);
        }},
        py::arg("label"),
        py::arg("str"),
        py::arg("flags") = 0);
    """


def wrap_input_text_multiline(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        [](const char* label,
            const std::string& str,
            const ImVec2& size,
            ImGuiInputTextFlags flags) {{
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto str_ = str;
            const auto clicked = {namespace}::{func.name}(label, &str_, size, flags);
            return std::make_tuple(clicked, str_);
        }},
        py::arg("label"),
        py::arg("str"),
        py::arg("size") = ImVec2(0, 0),
        py::arg("flags") = 0);
    """


def wrap_input_text_with_hint(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        [](const char* label,
            const char* hint,
            const std::string& str,
            ImGuiInputTextFlags flags) {{
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            flags |= ImGuiInputTextFlags_CallbackResize;

            auto str_ = str;
            const auto clicked = {namespace}::{func.name}(label, hint, &str_, flags);
            return std::make_tuple(clicked, str_);
        }},
        py::arg("label"),
        py::arg("hint"),
        py::arg("str"),
        py::arg("flags") = 0);
    """


def wrap_set_drag_drop_payload(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        [](const char* type,
            py::bytes& data,
            ImGuiCond cond) {{
            void* data_ = PyBytes_AsString(data.ptr());
            const auto data_size = PyBytes_Size(data.ptr());
            return {namespace}::{func.name}(type, data_, data_size, cond);
        }},
        py::arg("type"),
        py::arg("data"),
        py::arg("cond") = 0);
    """


def wrap_accept_drag_drop_payload(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        [](const char* type, ImGuiDragDropFlags flags) {{
            const auto *payload = {namespace}::{func.name}(type, flags);
            return py::bytes(static_cast<const char *>(payload->Data), payload->DataSize);
        }},
        py::arg("type"),
        py::arg("flags") = 0);
    """


def wrap_get_drag_drop_payload(namespace: str, func: Function) -> str:
    return f"""
    m.def(
        "{func.name}",
        []() {{
            const auto *payload = {namespace}::{func.name}();
            return py::bytes(static_cast<const char *>(payload->Data), payload->DataSize);
        }});
    """


def wrap_color_conversion(namespace: str, func: Function) -> str:
    in_arg_name = "".join([param.name for param in func.parameters[:3]])
    return f"""
    m.def(
        "{func.name}",
        [](const std::tuple<float, float, float>& {in_arg_name}) {{
            float out0, out1, out2;
            {namespace}::{func.name}(
                std::get<0>({in_arg_name}),
                std::get<1>({in_arg_name}),
                std::get<2>({in_arg_name}),
                out0,
                out1,
                out2
            );
            return std::make_tuple(out0, out1, out2);
        }},
        py::arg("{in_arg_name}"));
    """


template_dispatch = {
    "CreateContext": None,
    "DestroyContext": None,
    "GetCurrentContext": None,
    "SetCurrentContext": None,
    "GetIo": basic_ref_binding,
    "GetStyle": basic_ref_binding,
    "NewFrame": basic,
    "EndFrame": basic,
    "Render": basic,
    "GetDrawData": None,
    "ShowDemoWindow": wrapped_binding,
    "ShowMetricsWindow": wrapped_binding,
    "ShowStyleEditor": wrapped_binding,
    "ShowUserGuide": basic,
    "GetVersion": basic,
    "StyleColorsDark": wrapped_binding,
    "StyleColorsLight": wrapped_binding,
    "StyleColorsClassic": wrapped_binding,
    "Begin": wrapped_binding,
    "End": basic,
    "BeginChild": wrapped_binding,
    "EndChild": basic,
    "IsWindowAppearing": basic,
    "IsWindowCollapsed": basic,
    "IsWindowFocused": basic,
    "IsWindowHovered": basic,
    "GetWindowDrawList": None,
    "GetWindowPos": basic,
    "GetWindowSize": basic,
    "SetNextWindowPos": basic,
    "SetNextWindowSize": basic,
    "SetNextWindowSizeConstraints": None,
    "SetNextWindowContentSize": basic,
    "SetNextWindowCollapsed": basic,
    "SetNextWindowFocus": basic,
    "SetNextWindowScroll": basic,
    "SetNextWindowBgAlpha": basic,
    "SetWindowPos": wrapped_binding,
    "SetWindowSize": wrapped_binding,
    "SetWindowCollapsed": wrapped_binding,
    "SetWindowFocus": wrapped_binding,
    "SetWindowFontScale": None,  # Obsolete
    "GetScrollX": basic,
    "GetScrollY": basic,
    "SetScrollX": basic,
    "SetScrollY": basic,
    "GetScrollMaxX": basic,
    "GetScrollMaxY": basic,
    "SetScrollHereX": basic,
    "SetScrollHereY": basic,
    "SetScrollFromPosX": basic,
    "SetScrollFromPosY": basic,
    "PushFont": None,  # TODO
    "PopFont": None,  # TODO
    "PushStyleColor": wrapped_binding,
    "PopStyleColor": basic,
    "PushStyleVar": wrapped_binding,
    "PopStyleVar": basic,
    "PushItemFlag": basic,
    "PopItemFlag": basic,
    "PushItemWidth": basic,
    "PopItemWidth": basic,
    "SetNextItemWidth": basic,
    "CalcItemWidth": basic,
    "PushTextWrapPos": basic,
    "PopTextWrapPos": basic,
    "GetFont": None,  # TODO
    "GetFontSize": basic,
    "GetFontTexUvWhitePixel": basic,
    "GetColorU32": wrapped_binding,
    "GetStyleColorVec4": basic,
    "GetCursorScreenPos": basic,
    "SetCursorScreenPos": basic,
    "GetContentRegionAvail": basic,
    "GetCursorPos": basic,
    "GetCursorPosX": basic,
    "GetCursorPosY": basic,
    "SetCursorPos": basic,
    "SetCursorPosX": basic,
    "SetCursorPosY": basic,
    "GetCursorStartPos": basic,
    "Separator": basic,
    "SameLine": basic,
    "NewLine": basic,
    "Dummy": basic,
    "Unindent": basic,
    "BeginGroup": basic,
    "EndGroup": basic,
    "AlignTextToFramePadding": basic,
    "GetTextLineHeight": basic,
    "GetTextLineHeightWithSpacing": basic,
    "GetFrameHeight": basic,
    "GetFrameHeightWithSpacing": basic,
    "PushID": wrapped_binding,
    "GetID": wrapped_binding,
    "TextUnformatted": basic,
    "Text": fmt_vararg,
    "TextV": None,
    "TextColored": fmt_vararg,
    "TextColoredV": None,
    "TextDisabled": fmt_vararg,
    "TextDisabledV": None,
    "TextWrapped": fmt_vararg,
    "TextWrappedV": None,
    "LabelText": fmt_vararg,
    "LabelTextV": None,
    "BulletText": fmt_vararg,
    "BulletTextV": None,
    "SeparatorText": basic,
    "Button": basic,
    "SmallButton": basic,
    "InvisibleButton": basic,
    "ArrowButton": basic,
    "Checkbox": wrapped_binding,
    "CheckboxFlags": wrapped_binding,
    "RadioButton": wrapped_binding,
    "ProgressBar": wrapped_binding,
    "Bullet": basic,
    "TextLink": basic,
    "TextLinkOpenURL": basic,
    "Image": None,  # TODO
    "ImageButton": None,  # TODO
    "BeginCombo": basic,
    "EndCombo": basic,
    "Combo": wrapped_binding,
    "DragFloat": wrapped_binding,
    "DragFloat2": wrapped_binding,
    "DragFloat3": wrapped_binding,
    "DragFloat4": wrapped_binding,
    "DragFloatRange2": wrapped_binding,
    "DragInt": wrapped_binding,
    "DragInt2": wrapped_binding,
    "DragInt3": wrapped_binding,
    "DragInt4": wrapped_binding,
    "DragIntRange2": wrapped_binding,
    "DragScalar": None,
    "DragScalarN": None,
    "SliderFloat": wrapped_binding,
    "SliderFloat2": wrapped_binding,
    "SliderFloat3": wrapped_binding,
    "SliderFloat4": wrapped_binding,
    "SliderAngle": wrapped_binding,
    "SliderInt": wrapped_binding,
    "SliderInt2": wrapped_binding,
    "SliderInt3": wrapped_binding,
    "SliderInt4": wrapped_binding,
    "SliderScalar": None,
    "SliderScalarN": None,
    "VSliderFloat": wrapped_binding,
    "VSliderInt": wrapped_binding,
    "VSliderScalar": None,
    "InputText": wrap_input_text,
    "InputTextMultiline": wrap_input_text_multiline,
    "InputTextWithHint": wrap_input_text_with_hint,
    "InputFloat": wrapped_binding,
    "InputFloat2": wrapped_binding,
    "InputFloat3": wrapped_binding,
    "InputFloat4": wrapped_binding,
    "InputInt": wrapped_binding,
    "InputInt2": wrapped_binding,
    "InputInt3": wrapped_binding,
    "InputInt4": wrapped_binding,
    "InputDouble": wrapped_binding,
    "InputScalar": None,
    "InputScalarN": None,
    "ColorEdit3": wrapped_binding,
    "ColorEdit4": wrapped_binding,
    "ColorPicker3": wrapped_binding,
    "ColorPicker4": wrapped_binding,
    "ColorButton": basic,
    "SetColorEditOptions": basic,
    "TreeNode": wrapped_binding,
    "TreeNodeV": None,
    "TreeNodeEx": wrapped_binding,
    "TreeNodeExV": None,
    "TreePush": wrapped_binding,
    "TreePop": basic,
    "GetTreeNodeToLabelSpacing": basic,
    "CollapsingHeader": wrapped_binding,
    "SetNextItemOpen": basic,
    "Selectable": wrapped_binding,
    "BeginMultiSelect": basic,
    "EndMultiSelect": basic,
    "SetNextItemSelectionUserData": None,
    "IsItemToggledSelection": basic,
    "BeginListBox": basic,
    "EndListBox": basic,
    "ListBox": wrapped_binding,
    "PlotLines": None,  # TODO
    "PlotHistogram": None,  # TODO
    "Value": wrapped_binding,
    "BeginMenuBar": basic,
    "EndMenuBar": basic,
    "BeginMainMenuBar": basic,
    "EndMainMenuBar": basic,
    "BeginMenu": basic,
    "EndMenu": basic,
    "MenuItem": wrapped_binding,
    "BeginTooltip": basic,
    "EndTooltip": basic,
    "SetTooltip": fmt_vararg,
    "SetTooltipV": None,
    "BeginItemTooltip": basic,
    "EndItemTooltip": basic,
    "SetItemTooltip": fmt_vararg,
    "SetItemTooltipV": None,
    "BeginPopup": basic,
    "BeginPopupModal": wrapped_binding,
    "EndPopup": basic,
    "OpenPopup": wrapped_binding,
    "OpenPopupOnItemClick": basic,
    "CloseCurrentPopup": basic,
    "BeginPopupContextItem": basic,
    "BeginPopupContextWindow": basic,
    "BeginPopupContextVoid": basic,
    "IsPopupOpen": basic,
    "BeginTable": basic,
    "EndTable": basic,
    "TableNextColumn": basic,
    "TableSetColumnIndex": basic,
    "TableSetupColumn": basic,
    "TableSetupScrollFreeze": basic,
    "TableHeader": basic,
    "TableHeadersRow": basic,
    "TableAngledHeadersRow": basic,
    "TableGetSortSpecs": None,  # TODO
    "TableGetColumnCount": basic,
    "TableGetColumnIndex": basic,
    "TableGetRowIndex": basic,
    "TableGetColumnName": basic,
    "TableGetColumnFlags": basic,
    "TableSetColumnEnabled": basic,
    "TableGetHoveredColumn": basic,
    "TableSetBgColor": basic,
    "Columns": basic,
    "NextColumn": basic,
    "GetColumnIndex": basic,
    "GetColumnWidth": basic,
    "SetColumnWidth": basic,
    "GetColumnOffset": basic,
    "SetColumnOffset": basic,
    "GetColumnsCount": basic,
    "BeginTabBar": basic,
    "EndTabBar": basic,
    "BeginTabItem": basic,
    "EndTabItem": basic,
    "TabItemButton": basic,
    "SetTabItemClosed": basic,
    "LogToTTY": basic,
    "LogToFile": basic,
    "LogToClipboard": basic,
    "LogFinish": basic,
    "LogButtons": basic,
    "LogText": fmt_vararg,
    "LogTextV": None,
    "BeginDragDropSource": basic,
    "SetDragDropPayload": wrap_set_drag_drop_payload,
    "EndDragDropSource": basic,
    "BeginDragDropTarget": basic,
    "AcceptDragDropPayload": wrap_accept_drag_drop_payload,
    "EndDragDropTarget": basic,
    "GetDragDropPayload": wrap_get_drag_drop_payload,
    "BeginDisabled": basic,
    "EndDisabled": basic,
    "PushClipRect": basic,
    "PopClipRect": basic,
    "SetItemDefaultFocus": basic,
    "SetKeyboardFocusHere": basic,
    "SetNextItemAllowOverlap": basic,
    "IsItemHovered": basic,
    "IsItemActive": basic,
    "IsItemFocused": basic,
    "IsItemClicked": basic,
    "IsItemVisible": basic,
    "IsItemEdited": basic,
    "IsItemActivated": basic,
    "IsItemDeactivated": basic,
    "IsItemDeactivatedAfterEdit": basic,
    "IsItemToggledOpen": basic,
    "IsAnyItemHovered": basic,
    "IsAnyItemActive": basic,
    "IsAnyItemFocused": basic,
    "GetItemID": basic,
    "GetItemRectMin": basic,
    "GetItemRectMax": basic,
    "GetItemRectSize": basic,
    "GetMainViewport": None,
    "GetBackgroundDrawList": None,
    "IsRectVisible": wrapped_binding,
    "GetTime": basic,
    "GetDrawListSharedData": None,
    "GetStyleColorName": basic,
    "SetStateStorage": None,
    "GetStateStorage": None,
    "CalcTextSize": None,
    "ColorConvertU32ToFloat4": None,
    "ColorConvertFloat4ToU32": None,
    "ColorConvertRGBtoHSV": wrap_color_conversion,
    "ColorConvertHSVtoRGB": wrap_color_conversion,
    "IsKeyDown": basic,
    "IsKeyPressed": basic,
    "IsKeyReleased": basic,
    "IsKeyChordPressed": basic,
    "GetKeyPressedAmount": basic,
    "GetKeyName": basic,
    "SetNextFrameWantCaptureKeyboard": basic,
    "Shortcut": basic,
    "SetNextItemShortcut": basic,
    "SetItemKeyOwner": basic,
    "IsMouseDown": basic,
    "IsMouseClicked": basic,
    "IsMouseReleased": basic,
    "IsMouseDoubleClicked": basic,
    "GetMouseClickedCount": basic,
    "IsMouseHoveringRect": basic,
    "IsMousePosValid": basic,
    "IsAnyMouseDown": basic,
    "IsMouseDragging": basic,
    "GetMouseDragDelta": basic,
    "ResetMouseDragDelta": basic,
    "GetMouseCursor": basic,
    "SetMouseCursor": basic,
    "SetNextFrameWantCaptureMouse": basic,
    "GetClipboardText": basic,
    "LoadIniSettingsFromDisk": basic,
    "LoadIniSettingsFromMemory": None,
    "SaveIniSettingsToDisk": basic,
    "DebugTextEncoding": basic,
    "DebugFlashStyleColor": basic,
    "DebugStartItemPicker": basic,
    "DebugCheckVersionAndDataLayout": basic,
    "SetAllocatorFunctions": None,
    "GetAllocatorFunctions": None,
    "MemAlloc": None,
    "MemFree": None,
}


def funcs_filter(func: Function) -> bool:
    if func.name in {"PushID", "GetID"}:
        for param in func.parameters:
            if param.type == "const void*":
                return False
    elif func.name in {"Combo"}:
        for param in func.parameters:
            if param.type == "const char* (*)(void* user_data, int idx)":
                return False
    elif func.name in {"TreeNode", "TreeNodeEx"}:
        for param in func.parameters:
            if param.type == "const void*" or param.name == "fmt":
                # TODO fmt
                return False
    elif func.name in {"ListBox"}:
        for param in func.parameters:
            if param.name == "getter":
                # TODO fmt
                return False
    elif func.name in {"TreePush"}:
        for param in func.parameters:
            if param.type == "const void*":
                return False
    return True


bound_funcs = []
for func in library.functions.functions:
    if not funcs_filter(func):
        continue

    if func.name in template_dispatch:
        f = template_dispatch[func.name]

        if f is not None:
            res = f(library.functions.namespace, func)
            bound_funcs.append(res)


is_arithmitic_enum = {
    "ImGuiWindowFlags_",
    "ImGuiChildFlags_",
    "ImGuiItemFlags_",
    "ImGuiInputTextFlags_",
    "ImGuiTreeNodeFlags_",
    "ImGuiPopupFlags_",
    "ImGuiSelectableFlags_",
    "ImGuiComboFlags_",
    "ImGuiTabBarFlags_",
    "ImGuiTabItemFlags_",
    "ImGuiFocusedFlags_",
    "ImGuiHoveredFlags_",
    "ImGuiDragDropFlags_",
    "ImGuiInputFlags_",
    "ImGuiConfigFlags_",
    "ImGuiBackendFlags_",
    "ImGuiButtonFlags_",
    "ImGuiColorEditFlags_",
    "ImGuiSliderFlags_",
    "ImGuiTableFlags_",
    "ImGuiTableColumnFlags_",
    "ImGuiTableRowFlags_",
}

bound_enums = []
for enum in library.enums:
    values = []
    for enum_value in enum.values:
        value = f'.value("{enum_value.name}", {enum.name}::{enum_value.name})'
        values.append(value)

    args = ["m", f'"{enum.name}"']
    is_arithmentic = enum.name in is_arithmitic_enum
    if is_arithmentic:
        args.append("py::arithmetic()")

    gen_args = ", ".join(args)
    gen_values = "".join(values)
    bound_enum = f"""
    py::enum_<{enum.name}>({gen_args})
    {gen_values}
    .export_values();
    """

    bound_enums.append(bound_enum)


gen_bound_functions = "\n".join(bound_funcs)
gen_bound_enums = "\n".join(bound_enums)
pybind_module = f"""
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "imgui_utils.h"

namespace py = pybind11;

void bind_imgui_funcs(py::module& m) {{
    {gen_bound_functions}
}}

void bind_imgui_enums(py::module& m) {{
    {gen_bound_enums}
}}

void bind_imgui(py::module& m) {{
    auto mod_imgui = m.def_submodule("imgui", "ImGui bindings");
    bind_imgui_funcs(mod_imgui);
    bind_imgui_enums(mod_imgui);
}}
"""

# print(pybind_module)


dest_path = Path(__file__).parent.parent / "src" / "cpp" / "imgui.cpp"
dest_path.write_text(pybind_module)
