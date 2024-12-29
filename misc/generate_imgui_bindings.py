import os, sys, json, shutil, subprocess, re
from typing import List, Dict

from pprint import pprint

# =============================================================
# ==== Step 0: Path management and other setup
# =============================================================

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
IMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "polyscope", "deps", "imgui", "imgui")
CIMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "cimgui")
CIMGUI_IMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "cimgui", "imgui")
DEFINITIONS_PATH = os.path.join(CIMGUI_ROOT, "generator", "output", "definitions.json")
OUPUT_FILENAME = "imgui_bindings.cpp"


# =============================================================
# ==== Step 1: Make sure we have the right version of the 
# ====         cimgui repo available
# =============================================================

# Make sure the cimgui repo been cloned
if not os.path.isdir(CIMGUI_ROOT):
    raise ValueError("Please clone https://github.com/cimgui/cimgui into deps/cimgui. Checkout the commit which matches the current imgui version.")

# Helper to test versions
def check_git_repo_commit(repo_path):
    if not os.path.isdir(os.path.join(PROJECT_ROOT, "deps", "cimgui")):
        raise ValueError(f"No directory at {repo_path}")

    cmd = "git -C {} rev-parse HEAD && git -C {} describe --tags".format(repo_path, repo_path)
    print(f"Testing git repo with cmd: {cmd}")

    result = subprocess.check_output(cmd, shell=True, text=True)
    commit_hash, tag = result.strip().split('\n')

    print(f"\nRepo at {repo_path} has:")
    print(f" commit: {commit_hash}")
    print(f"    tag: {tag}")

    return commit_hash, tag

# Test that the proper versions are checked out
imgui_commit, imgui_tag = check_git_repo_commit(IMGUI_ROOT)
cimgui_commit, cimgui_tag = check_git_repo_commit(CIMGUI_IMGUI_ROOT)
if imgui_commit != cimgui_commit:

    print(f"""\nThe cimgui library maintains its own copy of imgui, which must match polyscope's verion of imgui. 
    cimgui/imgui commit: {cimgui_commit}  
    imgui commit: {imgui_commit}. 
Please check out the correct version of cimgui to {CIMGUI_ROOT}

cimgui tags its branchs with names matching imgui versions. You can probably 
get the correct one with something like `git checkout 1.90.4`.  Don't forget 
`git submodule update --recursive` after.  Exiting.
    """)
    sys.exit()


# =============================================================
# ==== Step 2: Setup and grab the spec
# =============================================================

with open(DEFINITIONS_PATH, 'r') as file:
    definitions = json.load(file)

# print(definitions)

# =============================================================
# ==== Step 3: Emit bindings code
# =============================================================

##  Generate bindings for function definitions

def is_modifiable_arg(argtype):
    pointer_pattern = r"^(?!const).*\*$" # matches 'float*' but not 'const char*'
    if re.match(pointer_pattern, argtype):
        argtype = argtype[:-1]
        return True, argtype, "&", ""
    
    array_pattern = r"^([a-zA-Z_][a-zA-Z0-9_]*)\[([0-9]+)\]" # matches int[3] and float[4], etc
    match = re.search(array_pattern, argtype)
    if match:
        argtype = match.group(1) # "float"
        arrcount = match.group(2) # "4"
        return True, f"std::array<{argtype},{arrcount}>", "", ".data()"

    return False, None, None, None

def strip_modifiable_pointer(arg_type):
    return arg_type[:-1]

def find_modifiable_arg(func_variant):
    """Check if any of the args get modified"""
    for arg in func_variant['argsT']:
        if is_modifiable_arg(arg):
            return arg['name']

    return None

def emit_func_binding(func_c_name, func_variant):
    # if func_c_name not in ["igBegin", "igEnd"]:
    #     return
    print(f"\nEmitting binding for {func_c_name}")
    pprint(func_variant)
    funcname = func_variant['funcname']
    rettype = func_variant["ret"]

    # Build the args at the start and end of the function
    arg_params = []
    call_arg_params = []
    arg_annotations = []
    mod_argnames = []
    for arg in func_variant["argsT"]:
        argname = arg["name"]
        argtype = arg["type"]

        this_arg_is_modifable = False
        call_prefix = ""
        call_postfix = ""
        this_arg_is_modifable, new_argtype, new_call_prefix, new_call_postfix = is_modifiable_arg(argtype)
        if this_arg_is_modifable:
            print(f" -- arg {argname} is modifable")
            mod_argnames.append(argname)
            argtype = new_argtype
            call_prefix = new_call_prefix
            call_postfix = new_call_postfix

        # handle conversions for vector types
        if "ImVec2" in argtype:
            argtype = argtype.replace("ImVec2", "Vec2T")
            call_prefix = call_prefix + "to_vec2("
            call_postfix = ")" + call_postfix
        if "ImVec4" in argtype:
            argtype = argtype.replace("ImVec4", "Vec4T")
            call_prefix = call_prefix + "to_vec4("
            call_postfix = ")" + call_postfix

        # the args list that appears in the binding def
        arg_params.append(f"""{argtype} {argname}""")

        # the args
        call_arg_params.append(f"""{call_prefix}{argname}{call_postfix}""")

        default_str = ""
        default_val = func_variant["defaults"].get(argname, None)
        if default_val is not None and default_val != "NULL":
            # TODO what to do with functions like StyleColorsDark that pass a pointer but we want the null default as an option 
            default_str = f""" = {default_val}"""
        arg_annotations.append(f"""py::arg("{argname}"){default_str}""")

    arg_params_str = ", ".join(arg_params)
    call_arg_params_str = ", ".join(call_arg_params)
    arg_annotations_str = ",\n        ".join(arg_annotations)
    if len(arg_annotations) > 0: arg_annotations_str = "\n        " + arg_annotations_str
    has_mod_args = (len(mod_argnames) > 0)

    # Generate the body
    body = ""
    if has_mod_args:
            if rettype == 'void':
                if len(mod_argnames) == 1:
                    # return a single value, the modified argument
                    body = f"""ImGui::{funcname}({call_arg_params_str});
        return {mod_argnames[0]};"""
                else:
                    # return a tuple of the modified arguments
                    body = f"""ImGui::{funcname}({call_arg_params_str});
                return std::make_tuple(retval, {", ".join(mod_argnames)});"""
            else:
                # return a tuple of the modified arguments, with the return value as the first tuple entry
                body = f"""const {rettype} retval = ImGui::{funcname}({call_arg_params_str});
            return std::make_tuple(retval, {", ".join(mod_argnames)});"""
    else:
            body = f"""return ImGui::{funcname}({call_arg_params_str});"""

    # Form the full stirng
    func_str = f"""
    // {funcname}
    m.def(
        "{funcname}",
        []({arg_params_str}) {{
            {body}
        }}, {arg_annotations_str}
        );
"""

    print(func_str)
    return func_str

    # Decide if it's a 

"""
    m.def(
        "Begin",
        [](const char* name, bool open, ImGuiWindowFlags flags) {
            const auto clicked = ImGui::Begin(name, &open, flags);
            return std::make_tuple(clicked, open);
        },
        py::arg("name"),
        py::arg("open"),
        py::arg("flags") = 0);
"""


definitions_bindings_list = []
for func_name in definitions:
    print(f"Generating bindings for {func_name}")
    func_variants = definitions[func_name]
    for func_variant in func_variants:

        # Skip anything marked 'internal'
        # (entries with no location key are destructors which we also want to skip)
        # pprint(func_variant)
        if func_variant.get('constructor', False):
            print(" -- skipping, marked as constructor")
            continue
        if func_variant.get('destructor', False):
            print(" -- skipping, marked as destructor")
            continue
        if "internal" in func_variant.get('location', ""):
            print(" -- skipping, marked as internal")
            continue
        if func_variant["stname"] != "":
            print(" -- skipping, marked as structure method")
            continue

        binding_str = emit_func_binding(func_name, func_variant)
        definitions_bindings_list.append(binding_str)



# Combine together into one file
definitions_bindings_str = "\n".join(definitions_bindings_list)

header_literal = """
#include "imgui.h"

#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
"""

utilities_literal = """
// Type translations between Python and ImGui.  Prefer native Python types (tuples, arrays), translating into ImGui
// equivalents.
using Vec2T = std::tuple<float, float>;
using Vec4T = std::tuple<float, float, float, float>;

ImVec2 to_vec2(const Vec2T& v) {{ return ImVec2(std::get<0>(v), std::get<1>(v)); }
ImVec4 to_vec4(const Vec4T& v) {{ return ImVec4(std::get<0>(v), std::get<1>(v), std::get<2>(v), std::get<3>(v)); }

Vec2T from_vec2(const ImVec2& v) { return std::make_tuple(v.x, v.y); }
Vec4T from_vec4(const ImVec4& v) { return std::make_tuple(v.x, v.y, v.z, v.w); }
"""

combined_str = f"""
{header_literal}

// =================================
// === Manual utilities
// =================================

{utilities_literal}


// =================================
// === Definitions
// =================================

{definitions_bindings_str}
"""

print(f"Writing output to {OUPUT_FILENAME}")
with open(OUPUT_FILENAME, 'w') as outfile:
    outfile.write(combined_str)

# generate_bindings(definitions, 'imgui_generated.cpp')