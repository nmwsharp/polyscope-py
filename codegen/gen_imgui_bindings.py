from typing import List, Optional, Callable
import json
from pathlib import Path
from pydantic import BaseModel
from collections import defaultdict
from functools import partial
from enum import Enum, StrEnum


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


library: Library = Library.parse_obj(
    json.loads((Path(__file__).parent / "imgui-bindings.json").read_bytes())
)


def as_string_literal(s: str) -> str:
    return f'"{s}"'


class ArgBinding(BaseModel):
    arg_name: Optional[str] = None
    arg_type: Optional[str] = None
    arg_default: Optional[str] = None
    decl_name: Optional[str] = None
    decl: Optional[str] = None
    ret: Optional[str] = None
    ret_type: Optional[str] = None

    def pybind_arg_arg(self) -> Optional[str]:
        if self.arg_name is None:
            return None

        arg = f"py::arg({as_string_literal(self.arg_name)})"
        if self.arg_default is not None:
            arg = f"{arg} = {self.arg_default}"
        return arg

    def cpp_arg(self) -> Optional[str]:
        if self.arg_name is None:
            return None

        return f"{self.arg_type} {self.arg_name}"


def const_char_ptr(param: Parameter) -> ArgBinding:
    if param.default == "NULL":
        arg_name = param.name
        decl_name = f"{param.name}_"
        decl = f"const char *{decl_name} = {arg_name}.has_value() ? {arg_name}.c_str() : nullptr;"
        return ArgBinding(
            arg_name=arg_name,
            arg_type="const std::optional<std::string>&",
            arg_default="std::nullopt",
            decl_name=decl_name,
            decl=decl,
            ret=None,
        )
    else:
        arg_default = None
        if param.default is not None:
            arg_default = param.default
        return ArgBinding(
            arg_name=param.name,
            arg_type=param.type,
            arg_default=arg_default,
            decl_name=param.name,
            decl=None,
            ret=None,
        )


def const_imvec2_ptr(param: Parameter) -> ArgBinding:
    if param.default == "NULL":
        arg_name = param.name
        decl_name = f"{param.name}_"
        decl = f"const ImVec2 *{decl_name} = {arg_name}.has_value() ? &{arg_name}.value() : nullptr;"
        return ArgBinding(
            arg_name=arg_name,
            arg_type="const std::optional<ImVec2>&",
            arg_default="std::nullopt",
            decl_name=decl_name,
            decl=decl,
            ret=None,
        )
    else:
        raise ValueError("Not Implemented")


def ptr(param: Parameter, type: str) -> ArgBinding:
    arg_name = param.name
    decl_name = f"{param.name}_"
    decl = f"{type} *{decl_name} = &{arg_name};"
    return ArgBinding(
        arg_name=arg_name,
        arg_type=type,
        arg_default=param.default,
        decl_name=decl_name,
        decl=decl,
        ret=arg_name,
        ret_type=type,
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
            ret_type=arg_type,
        )
    else:
        return ptr(param, "bool")


def pass_thru(param: Parameter) -> ArgBinding:
    return ArgBinding(
        arg_name=param.name,
        arg_type=param.type,
        arg_default=param.default,
        decl_name=param.name,
        decl=None,
        ret=None,
    )


double_ptr = partial(ptr, type="double")
float_ptr = partial(ptr, type="float")
int_ptr = partial(ptr, type="int")


def const_char_ptr_array(param: Parameter) -> ArgBinding:
    arg_name = param.name
    decl_name = f"{param.name}_"
    decl = f"const auto {decl_name} = convert_string_items({arg_name});"
    return ArgBinding(
        arg_name=arg_name,
        arg_type="const std::vector<std::string>&",
        arg_default=param.default,
        decl_name=f"{decl_name}.data()",
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
    arg_type = f"std::array<{type}, {n}>"
    return ArgBinding(
        arg_name=param.name,
        arg_type=arg_type,
        arg_default=param.default,
        decl_name=f"{param.name}.data()",
        decl=None,
        ret=param.name,
        ret_type=arg_type,
    )


def const_void_ptr(param: Parameter) -> ArgBinding:
    arg_name = param.name
    decl_name = f"{param.name}_"
    decl = f"void* {decl_name} = PyBytes_AsString({arg_name}.ptr());"
    return ArgBinding(
        arg_name=arg_name,
        arg_type="py::bytes&",
        arg_default=param.default,
        decl_name=decl_name,
        decl=decl,
        ret=None,
    )


float_array_2 = partial(array_n, type="float", n=2)
float_array_3 = partial(array_n, type="float", n=3)
float_array_4 = partial(array_n, type="float", n=4)
int_array_2 = partial(array_n, type="int", n=2)
int_array_3 = partial(array_n, type="int", n=3)
int_array_4 = partial(array_n, type="int", n=4)


param_dispatch = {
    "bool*": bool_ptr,
    "bool": pass_thru,
    "const char*": const_char_ptr,
    "ImGuiWindowFlags": pass_thru,
    "ImGuiTreeNodeFlags": pass_thru,
    "ImGuiSelectableFlags": pass_thru,
    "ImGuiInputTextFlags": pass_thru,
    "ImGuiPopupFlags": pass_thru,
    "ImGuiDragDropFlags": pass_thru,
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
    "const void*": const_void_ptr,
    "ImGuiTabItemFlags": pass_thru,
    "const ImVec2*": const_imvec2_ptr,
}


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


def const_char_ptr_fmt(param: Parameter) -> ArgBinding:
    return ArgBinding(
        arg_name=None,
        arg_type=None,
        arg_default=None,
        decl_name='"%s"',
        decl=None,
        ret=None,
    )


def elipses(param: Parameter) -> ArgBinding:
    arg_name = "text"
    return ArgBinding(
        arg_name=arg_name,
        arg_type="const char *",
        arg_default=None,
        decl_name=arg_name,
        decl=None,
        ret=None,
    )


def char_ptr_buf(param: Parameter) -> ArgBinding:
    arg_name = "str"
    decl_name = "str_"
    decl = f"auto {decl_name} = {arg_name};"
    return ArgBinding(
        arg_name=arg_name,
        arg_type="const std::string&",
        arg_default=None,
        decl_name=f"&{decl_name}",
        decl=decl,
        ret=decl_name,
        ret_type="const char*",
    )


def input_text_flags(param: Parameter) -> ArgBinding:
    decl = f"""
    IM_ASSERT(({param.name} & ImGuiInputTextFlags_CallbackResize) == 0);
    {param.name} |= ImGuiInputTextFlags_CallbackResize;
    """
    return ArgBinding(
        arg_name=param.name,
        arg_type=param.type,
        arg_default=param.default,
        decl_name=param.name,
        decl=decl,
        ret=None,
    )


def empty(param: Parameter) -> ArgBinding:
    return ArgBinding()


def drag_drop_size(param: Parameter) -> ArgBinding:
    decl_name = "data_size"
    decl = f"const auto {decl_name} = PyBytes_Size(data.ptr());"
    return ArgBinding(
        arg_name=None,
        arg_type=None,
        arg_default=None,
        decl_name=decl_name,
        decl=decl,
        ret=None,
    )


def route_param(param: Parameter, func: Function) -> Callable[[Parameter], ArgBinding]:
    if func.name == "Combo" and param.name == "items_count":
        return combo_items_count_param
    if func.name == "ColorPicker4" and param.name == "ref_col":
        return color_picker4_ref_col
    if param.name == "fmt" and param.type == "const char*":
        return const_char_ptr_fmt
    if param.name == "...":
        return elipses
    if param.name == "buf" and param.type == "char*":
        return char_ptr_buf
    if param.name == "flags" and param.type == "ImGuiInputTextFlags":
        return input_text_flags
    if param.name == "buf_size" and param.type == "size_t":
        return empty
    if param.type == "ImGuiInputTextCallback":
        return empty
    if param.name == "user_data" and param.type == "void*":
        return empty
    if func.name == "SetDragDropPayload" and param.name == "sz":
        return drag_drop_size

    if param.type not in param_dispatch:
        raise ValueError(
            f"Unknown parameter type: {param.type} in function {func.name}"
        )

    return param_dispatch[param.type]


class FuncBindingStyle(StrEnum):
    FunctionPtr = "FunctionPtr"
    Lambda = "Lambda"


class CustomReturn(BaseModel):
    ret_assign: str
    ret_expr: str


class BoundFunction(BaseModel):
    namespace: str
    func: Function
    binding_style: FuncBindingStyle
    py_args: List[ArgBinding]
    ret_types: List[str]
    ret_custom: Optional[CustomReturn] = None
    ret_policy: Optional[str] = None

    def cpp_name(self) -> str:
        return f"{self.namespace}::{self.func.name}"

    def cpp_func_ptr(self) -> str:
        return f"&{self.cpp_name()}"

    def pybind_name_arg(self) -> str:
        return as_string_literal(self.func.name)

    def pybind_args(self) -> List[str]:
        args = []
        for py_arg in self.py_args:
            arg = py_arg.pybind_arg_arg()
            if arg is not None:
                args.append(arg)
        return args

    def cpp_args(self) -> List[str]:
        args = []
        for py_arg in self.py_args:
            arg = py_arg.cpp_arg()
            if arg is not None:
                args.append(arg)
        return args

    def pybind_description_arg(self) -> Optional[str]:
        if self.func.description is None:
            return None
        return as_string_literal(esc_description(self.func.description))


def function_ptr(
    namespace: str,
    func: Function,
    ret_policy: Optional[str] = None,
) -> BoundFunction:
    py_args: List[ArgBinding] = []
    for param in func.parameters:
        py_args.append(
            ArgBinding(
                arg_name=param.name,
                arg_type=param.type,
                arg_default=param.default,
            )
        )

    ret_types = []
    if func.return_type != "void":
        ret_types.append(func.return_type)

    return BoundFunction(
        namespace=namespace,
        func=func,
        binding_style=FuncBindingStyle.FunctionPtr,
        py_args=py_args,
        ret_types=ret_types,
        ret_policy=ret_policy,
    )


def drag_drop_payload(namespace: str, func: Function) -> CustomReturn:
    name = "payload"
    return CustomReturn(
        ret_assign=f"const auto *{name}",
        ret_expr=f"py::bytes(static_cast<const char*>({name}->Data), {name}->DataSize)",
    )


custom_ret_dispatch = {
    "AcceptDragDropPayload": drag_drop_payload,
    "GetDragDropPayload": drag_drop_payload,
}


def collect_ret_types(func: Function, py_args: List[ArgBinding]) -> List[str]:
    ret_types = []
    if func.return_type != "void":
        ret_types.append(func.return_type)

    for py_arg in py_args:
        if py_arg.ret_type is not None:
            ret_types.append(py_arg.ret_type)

    return ret_types


def wrapped_binding(namespace: str, func: Function) -> BoundFunction:
    py_args: List[ArgBinding] = []
    for param in func.parameters:
        f = route_param(param, func)
        py_args.append(f(param))

    ret_custom: Optional[CustomReturn] = None
    if func.name in custom_ret_dispatch:
        ret_custom = custom_ret_dispatch[func.name](namespace, func)

    return BoundFunction(
        namespace=namespace,
        func=func,
        binding_style=FuncBindingStyle.Lambda,
        py_args=py_args,
        ret_custom=ret_custom,
        ret_types=collect_ret_types(func, py_args),
    )


def wrap_color_conversion(namespace: str, func: Function) -> BoundFunction:
    arg_name = "".join([param.name for param in func.parameters[:3]])
    decl_name = (
        f"std::get<0>({arg_name}), std::get<1>({arg_name}), std::get<2>({arg_name})"
    )
    py_args = [
        ArgBinding(
            arg_name=arg_name,
            arg_type="const std::tuple<float, float, float>&",
            arg_default=None,
            decl_name=decl_name,
        ),
        ArgBinding(
            decl="float out0, out1, out2;",
            decl_name="out0, out1, out2",
            ret="std::make_tuple(out0, out1, out2)",
            ret_type="std::tuple<float, float, float>",
        ),
    ]

    return BoundFunction(
        namespace=namespace,
        func=func,
        binding_style=FuncBindingStyle.Lambda,
        py_args=py_args,
        ret_types=collect_ret_types(func, py_args),
    )


function_ptr_ret_reference = partial(
    function_ptr,
    ret_policy="py::return_value_policy::reference",
)


template_dispatch = {
    "CreateContext": None,
    "DestroyContext": None,
    "GetCurrentContext": None,
    "SetCurrentContext": None,
    "GetIO": None,  # TODO
    "GetStyle": None,  # TODO
    "NewFrame": function_ptr,
    "EndFrame": function_ptr,
    "Render": function_ptr,
    "GetDrawData": None,
    "ShowDemoWindow": wrapped_binding,
    "ShowMetricsWindow": wrapped_binding,
    "ShowStyleEditor": wrapped_binding,
    "ShowUserGuide": function_ptr,
    "GetVersion": function_ptr,
    "StyleColorsDark": wrapped_binding,
    "StyleColorsLight": wrapped_binding,
    "StyleColorsClassic": wrapped_binding,
    "Begin": wrapped_binding,
    "End": function_ptr,
    "BeginChild": wrapped_binding,
    "EndChild": function_ptr,
    "IsWindowAppearing": function_ptr,
    "IsWindowCollapsed": function_ptr,
    "IsWindowFocused": function_ptr,
    "IsWindowHovered": function_ptr,
    "GetWindowDrawList": None,
    "GetWindowPos": function_ptr,
    "GetWindowSize": function_ptr,
    "SetNextWindowPos": function_ptr,
    "SetNextWindowSize": function_ptr,
    "SetNextWindowSizeConstraints": None,
    "SetNextWindowContentSize": function_ptr,
    "SetNextWindowCollapsed": function_ptr,
    "SetNextWindowFocus": function_ptr,
    "SetNextWindowScroll": function_ptr,
    "SetNextWindowBgAlpha": function_ptr,
    "SetWindowPos": wrapped_binding,
    "SetWindowSize": wrapped_binding,
    "SetWindowCollapsed": wrapped_binding,
    "SetWindowFocus": wrapped_binding,
    "SetWindowFontScale": None,  # Obsolete
    "GetScrollX": function_ptr,
    "GetScrollY": function_ptr,
    "SetScrollX": function_ptr,
    "SetScrollY": function_ptr,
    "GetScrollMaxX": function_ptr,
    "GetScrollMaxY": function_ptr,
    "SetScrollHereX": function_ptr,
    "SetScrollHereY": function_ptr,
    "SetScrollFromPosX": function_ptr,
    "SetScrollFromPosY": function_ptr,
    "PushFont": None,  # TODO
    "PopFont": None,  # TODO
    "PushStyleColor": wrapped_binding,
    "PopStyleColor": function_ptr,
    "PushStyleVar": wrapped_binding,
    "PopStyleVar": function_ptr,
    "PushItemFlag": function_ptr,
    "PopItemFlag": function_ptr,
    "PushItemWidth": function_ptr,
    "PopItemWidth": function_ptr,
    "SetNextItemWidth": function_ptr,
    "CalcItemWidth": function_ptr,
    "PushTextWrapPos": function_ptr,
    "PopTextWrapPos": function_ptr,
    "GetFont": None,  # TODO
    "GetFontSize": function_ptr,
    "GetFontTexUvWhitePixel": function_ptr,
    "GetColorU32": wrapped_binding,
    "GetStyleColorVec4": function_ptr,
    "GetCursorScreenPos": function_ptr,
    "SetCursorScreenPos": function_ptr,
    "GetContentRegionAvail": function_ptr,
    "GetCursorPos": function_ptr,
    "GetCursorPosX": function_ptr,
    "GetCursorPosY": function_ptr,
    "SetCursorPos": function_ptr,
    "SetCursorPosX": function_ptr,
    "SetCursorPosY": function_ptr,
    "GetCursorStartPos": function_ptr,
    "Separator": function_ptr,
    "SameLine": function_ptr,
    "NewLine": function_ptr,
    "Dummy": function_ptr,
    "Unindent": function_ptr,
    "BeginGroup": function_ptr,
    "EndGroup": function_ptr,
    "AlignTextToFramePadding": function_ptr,
    "GetTextLineHeight": function_ptr,
    "GetTextLineHeightWithSpacing": function_ptr,
    "GetFrameHeight": function_ptr,
    "GetFrameHeightWithSpacing": function_ptr,
    "PushID": wrapped_binding,
    "GetID": wrapped_binding,
    # "TextUnformatted": function_ptr,
    "TextUnformatted": None,  # TODO
    "Text": wrapped_binding,
    "TextV": None,
    "TextColored": wrapped_binding,
    "TextColoredV": None,
    "TextDisabled": wrapped_binding,
    "TextDisabledV": None,
    "TextWrapped": wrapped_binding,
    "TextWrappedV": None,
    "LabelText": wrapped_binding,
    "LabelTextV": None,
    "BulletText": wrapped_binding,
    "BulletTextV": None,
    "SeparatorText": function_ptr,
    "Button": function_ptr,
    "SmallButton": function_ptr,
    "InvisibleButton": function_ptr,
    "ArrowButton": function_ptr,
    "Checkbox": wrapped_binding,
    "CheckboxFlags": wrapped_binding,
    "RadioButton": wrapped_binding,
    "ProgressBar": wrapped_binding,
    "Bullet": function_ptr,
    "TextLink": function_ptr,
    "TextLinkOpenURL": wrapped_binding,
    "Image": None,  # TODO
    "ImageButton": None,  # TODO
    "BeginCombo": function_ptr,
    "EndCombo": function_ptr,
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
    "InputText": wrapped_binding,
    "InputTextMultiline": wrapped_binding,
    "InputTextWithHint": wrapped_binding,
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
    "ColorButton": function_ptr,
    "SetColorEditOptions": function_ptr,
    "TreeNode": wrapped_binding,
    "TreeNodeV": None,
    "TreeNodeEx": wrapped_binding,
    "TreeNodeExV": None,
    "TreePush": wrapped_binding,
    "TreePop": function_ptr,
    "GetTreeNodeToLabelSpacing": function_ptr,
    "CollapsingHeader": wrapped_binding,
    "SetNextItemOpen": function_ptr,
    "Selectable": wrapped_binding,
    "BeginMultiSelect": None,  # TODO
    "EndMultiSelect": None,  # TODO
    "SetNextItemSelectionUserData": None,
    "IsItemToggledSelection": function_ptr,
    "BeginListBox": function_ptr,
    "EndListBox": function_ptr,
    "ListBox": wrapped_binding,
    "PlotLines": None,  # TODO
    "PlotHistogram": None,  # TODO
    "Value": wrapped_binding,
    "BeginMenuBar": function_ptr,
    "EndMenuBar": function_ptr,
    "BeginMainMenuBar": function_ptr,
    "EndMainMenuBar": function_ptr,
    "BeginMenu": function_ptr,
    "EndMenu": function_ptr,
    "MenuItem": wrapped_binding,
    "BeginTooltip": function_ptr,
    "EndTooltip": function_ptr,
    "SetTooltip": wrapped_binding,
    "SetTooltipV": None,
    "BeginItemTooltip": function_ptr,
    "EndItemTooltip": function_ptr,
    "SetItemTooltip": wrapped_binding,
    "SetItemTooltipV": None,
    "BeginPopup": function_ptr,
    "BeginPopupModal": wrapped_binding,
    "EndPopup": function_ptr,
    "OpenPopup": wrapped_binding,
    "OpenPopupOnItemClick": wrapped_binding,
    "CloseCurrentPopup": function_ptr,
    "BeginPopupContextItem": wrapped_binding,
    "BeginPopupContextWindow": wrapped_binding,
    "BeginPopupContextVoid": wrapped_binding,
    "IsPopupOpen": function_ptr,
    "BeginTable": function_ptr,
    "EndTable": function_ptr,
    "TableNextColumn": function_ptr,
    "TableSetColumnIndex": function_ptr,
    "TableSetupColumn": function_ptr,
    "TableSetupScrollFreeze": function_ptr,
    "TableHeader": function_ptr,
    "TableHeadersRow": function_ptr,
    "TableAngledHeadersRow": function_ptr,
    "TableGetSortSpecs": None,  # TODO
    "TableGetColumnCount": function_ptr,
    "TableGetColumnIndex": function_ptr,
    "TableGetRowIndex": function_ptr,
    "TableGetColumnName": function_ptr,
    "TableGetColumnFlags": function_ptr,
    "TableSetColumnEnabled": function_ptr,
    "TableGetHoveredColumn": function_ptr,
    "TableSetBgColor": function_ptr,
    "Columns": wrapped_binding,
    "NextColumn": function_ptr,
    "GetColumnIndex": function_ptr,
    "GetColumnWidth": function_ptr,
    "SetColumnWidth": function_ptr,
    "GetColumnOffset": function_ptr,
    "SetColumnOffset": function_ptr,
    "GetColumnsCount": function_ptr,
    "BeginTabBar": function_ptr,
    "EndTabBar": function_ptr,
    "BeginTabItem": wrapped_binding,
    "EndTabItem": function_ptr,
    "TabItemButton": function_ptr,
    "SetTabItemClosed": function_ptr,
    "LogToTTY": function_ptr,
    "LogToFile": wrapped_binding,
    "LogToClipboard": function_ptr,
    "LogFinish": function_ptr,
    "LogButtons": function_ptr,
    "LogText": wrapped_binding,
    "LogTextV": None,
    "BeginDragDropSource": function_ptr,
    "SetDragDropPayload": wrapped_binding,
    "EndDragDropSource": function_ptr,
    "BeginDragDropTarget": function_ptr,
    "AcceptDragDropPayload": wrapped_binding,
    "EndDragDropTarget": function_ptr,
    "GetDragDropPayload": wrapped_binding,
    "BeginDisabled": function_ptr,
    "EndDisabled": function_ptr,
    "PushClipRect": function_ptr,
    "PopClipRect": function_ptr,
    "SetItemDefaultFocus": function_ptr,
    "SetKeyboardFocusHere": function_ptr,
    "SetNextItemAllowOverlap": function_ptr,
    "IsItemHovered": function_ptr,
    "IsItemActive": function_ptr,
    "IsItemFocused": function_ptr,
    "IsItemClicked": function_ptr,
    "IsItemVisible": function_ptr,
    "IsItemEdited": function_ptr,
    "IsItemActivated": function_ptr,
    "IsItemDeactivated": function_ptr,
    "IsItemDeactivatedAfterEdit": function_ptr,
    "IsItemToggledOpen": function_ptr,
    "IsAnyItemHovered": function_ptr,
    "IsAnyItemActive": function_ptr,
    "IsAnyItemFocused": function_ptr,
    "GetItemID": function_ptr,
    "GetItemRectMin": function_ptr,
    "GetItemRectMax": function_ptr,
    "GetItemRectSize": function_ptr,
    "GetMainViewport": None,
    "GetBackgroundDrawList": None,
    "IsRectVisible": wrapped_binding,
    "GetTime": function_ptr,
    "GetDrawListSharedData": None,
    "GetStyleColorName": function_ptr,
    "SetStateStorage": None,
    "GetStateStorage": None,
    "CalcTextSize": None,
    "ColorConvertU32ToFloat4": None,
    "ColorConvertFloat4ToU32": None,
    "ColorConvertRGBtoHSV": wrap_color_conversion,
    "ColorConvertHSVtoRGB": wrap_color_conversion,
    "IsKeyDown": function_ptr,
    "IsKeyPressed": function_ptr,
    "IsKeyReleased": function_ptr,
    "IsKeyChordPressed": function_ptr,
    "GetKeyPressedAmount": function_ptr,
    "GetKeyName": function_ptr,
    "SetNextFrameWantCaptureKeyboard": function_ptr,
    "Shortcut": function_ptr,
    "SetNextItemShortcut": function_ptr,
    "SetItemKeyOwner": function_ptr,
    "IsMouseDown": function_ptr,
    "IsMouseClicked": function_ptr,
    "IsMouseReleased": function_ptr,
    "IsMouseDoubleClicked": function_ptr,
    "GetMouseClickedCount": function_ptr,
    "IsMouseHoveringRect": function_ptr,
    "IsMousePosValid": wrapped_binding,
    "IsAnyMouseDown": function_ptr,
    "IsMouseDragging": function_ptr,
    "GetMouseDragDelta": function_ptr,
    "ResetMouseDragDelta": function_ptr,
    "GetMouseCursor": function_ptr,
    "SetMouseCursor": function_ptr,
    "SetNextFrameWantCaptureMouse": function_ptr,
    "GetClipboardText": function_ptr,
    "LoadIniSettingsFromDisk": function_ptr,
    "LoadIniSettingsFromMemory": None,
    "SaveIniSettingsToDisk": function_ptr,
    "DebugTextEncoding": function_ptr,
    "DebugFlashStyleColor": function_ptr,
    "DebugStartItemPicker": function_ptr,
    "DebugCheckVersionAndDataLayout": function_ptr,
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
    elif func.name in {"CheckboxFlags", "Value"}:
        if func.parameters[-1].type == "unsigned int":
            return False
    return True


def gen_def(bound_func: BoundFunction, f: str) -> str:
    args = [
        bound_func.pybind_name_arg(),
        f,
    ]
    args.extend(bound_func.pybind_args())
    description_arg = bound_func.pybind_description_arg()
    if description_arg is not None:
        args.append(description_arg)

    if bound_func.ret_policy is not None:
        args.append(bound_func.ret_policy)

    args_str = ", ".join(args)
    return f"m.def({args_str});"


def gen_function_ptr_binding(bound_func: BoundFunction) -> str:
    return gen_def(bound_func, bound_func.cpp_func_ptr())


def gen_lambda_binding(bound_func: BoundFunction) -> str:
    args = ", ".join(bound_func.cpp_args())
    decls = "\n".join(
        [py_arg.decl for py_arg in bound_func.py_args if py_arg.decl is not None]
    )
    f_call_args = ", ".join(
        [
            py_arg.decl_name
            for py_arg in bound_func.py_args
            if py_arg.decl_name is not None
        ]
    )

    ret_names = []
    f_call = f"{bound_func.cpp_name()}({f_call_args});"
    if bound_func.func.return_type == "void":
        call = f_call
    else:
        if bound_func.ret_custom is None:
            call = f"const auto res_ = {f_call}"
            ret_names.append("res_")
        else:
            call = f"{bound_func.ret_custom.ret_assign} = {f_call}"
            ret_names.append(bound_func.ret_custom.ret_expr)

    ret_names.extend(
        [py_arg.ret for py_arg in bound_func.py_args if py_arg.ret is not None]
    )
    if len(ret_names) == 0:
        ret = ""
    elif len(ret_names) == 1:
        ret = f"return {ret_names[0]};"
    else:
        ret_args = ", ".join(ret_names)
        ret = f"return std::make_tuple({ret_args});"

    f_lambda = f"""
    []({args}) {{
        {decls}
        {call}
        {ret}
    }}
    """

    return gen_def(bound_func, f_lambda)


bound_funcs = []
for func in library.functions.functions:
    if not funcs_filter(func):
        continue

    if func.name in template_dispatch:
        f = template_dispatch[func.name]

        if f is not None:
            bound_func = f(library.functions.namespace, func)
            bound_funcs.append(bound_func)


gen_funcs: List[str] = []
for bound_func in bound_funcs:
    if bound_func.binding_style == FuncBindingStyle.FunctionPtr:
        gen_funcs.append(gen_function_ptr_binding(bound_func))
    elif bound_func.binding_style == FuncBindingStyle.Lambda:
        gen_funcs.append(gen_lambda_binding(bound_func))

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


def enum_py_name(name: str) -> str:
    enum_name = enum.name
    if enum_name.endswith("_"):
        enum_name = enum_name[:-1]
    return enum_name


bound_enums = []
for enum in library.enums:
    values = []
    for enum_value in enum.values:
        value = f'.value("{enum_value.name}", {enum.name}::{enum_value.name})'
        values.append(value)

    enum_name = enum_py_name(enum.name)

    args = ["m", f'"{enum_name}"']
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


gen_bound_functions = "\n".join(gen_funcs)
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

# # print(pybind_module)


dest_path = Path(__file__).parent.parent / "src" / "cpp" / "imgui.cpp"
dest_path.write_text(pybind_module)

cpp_type_to_py_type = {
    "std::optional<bool>": "Optional[bool]",
    "const char*": "str",
    "const char *": "str",
    "const ImVec2&": "Tuple[float, float]",
    "const ImVec4&": "Tuple[float, float, float, float]",
    "std::array<float, 2>": "Tuple[float, float]",
    "std::array<float, 3>": "Tuple[float, float, float]",
    "std::array<float, 4>": "Tuple[float, float, float, float]",
    "const std::vector<std::string>&": "List[str]",
    "std::array<int, 2>": "Tuple[int, int]",
    "std::array<int, 3>": "Tuple[int, int, int]",
    "std::array<int, 4>": "Tuple[int, int, int, int]",
    "const std::optional<std::array<float, 4>>&": "Optional[Tuple[float, float, float, float]]",
    "ImU32": "int",
    "const std::tuple<float, float, float>&": "Tuple[float, float, float]",
    "std::tuple<float, float, float>": "Tuple[float, float, float]",
    "const std::string&": "str",
    "double": "float",
    "py::bytes&": "bytes",
    "const std::optional<std::string>&": "Optional[str]",
    "const std::optional<ImVec2>&": "Optional[Tuple[float, float]]",
    "size_t": "int",
    "const ImGuiPayload*": "bytes",
    "ImVec2": "Tuple[float, float]",
}


def py_type(cpp_type: str) -> str:
    if cpp_type in cpp_type_to_py_type:
        return cpp_type_to_py_type[cpp_type]
    else:
        return cpp_type


def py_default(py_arg: ArgBinding, default: str) -> str:
    if default == "std::nullopt":
        return None
    elif "ImVec2" in default:
        return (
            default.replace("ImVec2", "")
            .replace("f", "")
            .replace("FLT_MIN", "1.175494e-38")
        )
    elif default[-1] == "f":
        return default[:-1]
    elif default == "false":
        return "False"
    elif default == "true":
        return "True"
    else:
        return default


def binding_pyi(bound_func: BoundFunction) -> str:
    def_args: List[str] = []
    for py_arg in bound_func.py_args:
        if py_arg.arg_name is not None:
            def_arg = f"{py_arg.arg_name}: {py_type(py_arg.arg_type)}"
            if py_arg.arg_default is not None:
                default = py_default(py_arg, py_arg.arg_default)
                def_arg += f" = {default}"
            def_args.append(def_arg)

    def_rets: List[str] = []
    if bound_func.func.return_type != "void":
        def_rets.append(f"{py_type(bound_func.func.return_type)}")
    for py_arg in bound_func.py_args:
        if py_arg.ret_type is not None:
            def_rets.append(f"{py_type(py_arg.ret_type)}")

    # if bound_func.func.name == "GetID":
    #     print(bound_func)
    #     raise ValueError("x")

    def_args_str = ", ".join(def_args)

    if len(def_rets) == 0:
        def_ret_str = "None"
    elif len(def_rets) == 1:
        def_ret_str = def_rets[0]
    else:
        def_ret_str = f"Tuple[{', '.join(def_rets)}]"

    return f"def {bound_func.func.name}({def_args_str}) -> {def_ret_str}: ..."


pyi_bound_funcs = []
for bound_func in bound_funcs:
    pyi_bound_funcs.append(binding_pyi(bound_func))

pyi_bound_enums = []
for enum in library.enums:
    enum_name = enum_py_name(enum.name)
    lines = []
    lines.append(f"class {enum_name}(Enum):")
    gen_value = 0
    for enum_value in enum.values:
        if enum_value.value is None:
            value = gen_value
            gen_value += 1
        else:
            value = enum_value.value
        lines.append(f"    {enum_value.name} = {value}")

    pyi_bound_enums.append("\n".join(lines))


pyi_gen_bound_enums = "\n\n".join(pyi_bound_enums)
pyi_gen_bound_funcs = "\n".join(pyi_bound_funcs)
pyi_module = f"""
from typing import List, NewType, Optional, Tuple, Union, overload
from enum import Enum

ImGuiID = NewType("ImGuiID", int)
ImGuiKeyChord = NewType("ImGuiKeyChord", int)

{pyi_gen_bound_enums}

{pyi_gen_bound_funcs}
"""

print(pyi_module)
pyi_dest_path = (
    Path(__file__).parent.parent / "src" / "polyscope_bindings" / "imgui.pyi"
)
print(pyi_dest_path)
pyi_dest_path.write_text(pyi_module)


# TODO: set enum value defaults to enum name
# e.g. ImGuiChildFlags = 0

# wrong return type
# def PushID(str_id: str) -> None: ...
# def PushID(str_id_begin: str, str_id_end: str) -> None: ...
# def PushID(int_id: int) -> None: ...
# def GetID(str_id: str) -> None: ...
# def GetID(str_id_begin: str, str_id_end: str) -> None: ...
# def GetID(int_id: int) -> None: ...
