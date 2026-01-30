import polyscope_bindings as psb
import polyscope.imgui as psim

import polyscope

import os

from collections.abc import Sequence
from typing import Any, Literal, TypeAlias, NoReturn, TypeVar
from enum import Enum
from numpy.typing import NDArray

## General purpose [string or enum] --> enum


def normalize_string(value: str) -> str:
    return value.lower().replace("_", "")


E = TypeVar("E", bound=Enum)


def to_enum(enum: type[E], value: str | E) -> E:
    if isinstance(value, enum):
        return value

    if isinstance(value, str):
        if value in enum.__members__:
            return enum.__members__[value]

    raise ValueError(
        f"Bad specifier '{value}', should be one of the strings {{{','.join(enum.__members__.keys())}}}"
    )

def from_enum(value: Enum) -> str:
    return value.name

# Most enums are defined in the C++ bindings in core.cpp

# Some additional python-only enums
class Backend(Enum):
    auto = 0
    openGL3_glfw = 1
    openGL3_egl = 2
    openGL_mock = 3

# Mapping for some common characters, to support our legacy get_key_code() function.
# The more proper solution is to use the ImGui enum names directly like psim.ImGuiKey_W; only a subset of them are mapped get_key_code() and the dict below.
# The full list can be found in the ImGui source, or in this issue https://github.com/ocornut/imgui/issues/4921
keycode_dict = {
    " ": psim.ImGuiKey_Space,
    "0": psim.ImGuiKey_0,
    "1": psim.ImGuiKey_1,
    "2": psim.ImGuiKey_2,
    "3": psim.ImGuiKey_3,
    "4": psim.ImGuiKey_4,
    "5": psim.ImGuiKey_5,
    "6": psim.ImGuiKey_6,
    "7": psim.ImGuiKey_7,
    "8": psim.ImGuiKey_8,
    "9": psim.ImGuiKey_9,
    "A": psim.ImGuiKey_A,
    "B": psim.ImGuiKey_B,
    "C": psim.ImGuiKey_C,
    "D": psim.ImGuiKey_D,
    "E": psim.ImGuiKey_E,
    "F": psim.ImGuiKey_F,
    "G": psim.ImGuiKey_G,
    "H": psim.ImGuiKey_H,
    "I": psim.ImGuiKey_I,
    "J": psim.ImGuiKey_J,
    "K": psim.ImGuiKey_K,
    "L": psim.ImGuiKey_L,
    "M": psim.ImGuiKey_M,
    "N": psim.ImGuiKey_N,
    "O": psim.ImGuiKey_O,
    "P": psim.ImGuiKey_P,
    "Q": psim.ImGuiKey_Q,
    "R": psim.ImGuiKey_R,
    "S": psim.ImGuiKey_S,
    "T": psim.ImGuiKey_T,
    "U": psim.ImGuiKey_U,
    "V": psim.ImGuiKey_V,
    "W": psim.ImGuiKey_W,
    "X": psim.ImGuiKey_X,
    "Y": psim.ImGuiKey_Y,
    "Z": psim.ImGuiKey_Z,
    "'": psim.ImGuiKey_Apostrophe,
    ",": psim.ImGuiKey_Comma,
    "-": psim.ImGuiKey_Minus,
    ".": psim.ImGuiKey_Period,
    "/": psim.ImGuiKey_Slash,
    ";": psim.ImGuiKey_Semicolon,
    "=": psim.ImGuiKey_Equal,
    "[": psim.ImGuiKey_LeftBracket,
    "\\": psim.ImGuiKey_Backslash,
    "]": psim.ImGuiKey_RightBracket,
}


def get_key_code(k: str):
    if len(k) != 1:
        raise ValueError("pass a single character")
    if k.islower():
        k = k.upper()

    if k not in keycode_dict:
        raise ValueError(
            f"character {k} not in keycode mapping. For keys which have multiple characters on them, try the other character (like @ vs 2). Alternately, don't use this function, look up the appropriate enum from the imgui documentation, use them like polyscope.imgui.ImGuiKey_Semicolon"
        )

    return keycode_dict[k]
