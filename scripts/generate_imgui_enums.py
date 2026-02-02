#!/usr/bin/env python3
"""
Generate imgui_enums.cpp from imgui.h

This script parses imgui.h to extract all public-facing enums and generates
nanobind bindings for them.

WARNING: this file is LLM generated, don't trust it.
"""

import re
import sys
from datetime import datetime
from pathlib import Path


def extract_version(content: str) -> str:
    """Extract imgui version from the header."""
    match = re.search(r'#define\s+IMGUI_VERSION\s+"([^"]+)"', content)
    return match.group(1) if match else "unknown"


def find_typed_enums(content: str) -> set[str]:
    """
    Find enums declared as 'enum EnumName : type' (forward declarations).
    These need special binding treatment.
    """
    # Match forward declarations like: enum ImGuiDir : int;
    pattern = r'^enum\s+(Im\w+)\s*:\s*\w+\s*;'
    matches = re.findall(pattern, content, re.MULTILINE)
    return set(matches)


def parse_enum_block(content: str, start_pos: int) -> tuple[list[str], int]:
    """
    Parse an enum block starting from the opening brace.
    Returns list of enum values (deduplicated, preserving order) and the end position.
    """
    # Find the opening brace
    brace_pos = content.find('{', start_pos)
    if brace_pos == -1:
        return [], start_pos

    # Find matching closing brace
    depth = 1
    pos = brace_pos + 1
    while pos < len(content) and depth > 0:
        if content[pos] == '{':
            depth += 1
        elif content[pos] == '}':
            depth -= 1
        pos += 1

    block = content[brace_pos + 1:pos - 1]

    # Extract enum values
    values = []
    for line in block.split('\n'):
        line = line.strip()

        # Skip empty lines and comments
        if not line or line.startswith('//'):
            continue

        # Skip preprocessor directives and their contents
        if line.startswith('#'):
            continue

        # Strip trailing comments before parsing
        if '//' in line:
            line = line[:line.index('//')]

        # Extract the enum value name (before = or , or end of line)
        # Handle multiple values on same line like: ImGuiKey_A, ImGuiKey_B, ImGuiKey_C,
        parts = line.split(',')
        for part in parts:
            part = part.strip()
            if not part:
                continue

            # Get just the identifier (Im* prefix covers ImGui, ImDraw, ImFont, ImTexture, etc.)
            match = re.match(r'(Im\w+)', part)
            if match:
                values.append(match.group(1))

    return values, pos


def parse_enums(content: str) -> list[dict]:
    """
    Parse all enum definitions from imgui.h.
    Returns list of dicts with enum name, prefix, and values.
    """
    enums = []

    # Pattern for enum definition: enum EnumName_ or enum EnumName : type
    # We want the full definition, not forward declarations
    # Matches Im* prefix (ImGui, ImDraw, ImFont, ImTexture, etc.)
    pattern = r'^enum\s+(Im\w+?)(_?)\s*(?::\s*\w+)?\s*\n\{'

    for match in re.finditer(pattern, content, re.MULTILINE):
        enum_name = match.group(1) + match.group(2)
        start_pos = match.start()

        values, _ = parse_enum_block(content, start_pos)

        if values:
            # Determine the prefix (enum values start with this)
            prefix = enum_name

            enums.append({
                'name': enum_name,
                'prefix': prefix,
                'values': values,
            })

    return enums


def generate_cpp(enums: list[dict], typed_enums: set[str], version: str) -> str:
    """Generate the C++ bindings file.

    All enums are bound as nb::enum_ with is_arithmetic() and is_flag() to allow
    bitwise operations and int conversions.
    """
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    lines = [
        "// AUTO-GENERATED FILE - DO NOT EDIT",
        f"// Generated: {now}",
        f"// imgui version: {version}",
        "// Generator: python3 scripts/generate_imgui_enums.py",
        "",
        '#include "imgui.h"',
        "",
        '#include "../utils.h"',
        '#include "imgui_utils.h"',
        "",
        "void bind_imgui_enums(nb::module_& m) {",
        "",
    ]

    for enum in enums:
        enum_name = enum['name']

        lines.append(f"  {{ // {enum_name}")
        lines.append(f"  auto e = nb::enum_<{enum_name}>(m, \"{enum_name}\", nb::is_arithmetic(), nb::is_flag());")

        for value in enum['values']:
            # Calculate padding for alignment
            padding = max(1, 45 - len(value))
            spaces = ' ' * padding

            lines.append(
                f"    e.value(\"{value}\",{spaces}{value});"
                f"{spaces}m.attr(\"{value}\"){spaces}= {enum_name}::{value};"
            )

        lines.append("  ;")
        lines.append("  }")
        lines.append("")

    lines.append("}")
    lines.append("")

    return '\n'.join(lines)


def main():
    # Find imgui.h
    script_dir = Path(__file__).parent
    repo_root = script_dir.parent

    imgui_path = repo_root / "deps/polyscope/deps/imgui/imgui/imgui.h"
    if not imgui_path.exists():
        print(f"Error: Could not find imgui.h at {imgui_path}")
        sys.exit(1)

    output_path = repo_root / "src/cpp/imgui/imgui_enums.cpp"

    # Read imgui.h
    content = imgui_path.read_text()

    # Extract version
    version = extract_version(content)
    print(f"imgui version: {version}")

    # Find typed enums (forward declared with : type)
    typed_enums = find_typed_enums(content)
    print(f"Found {len(typed_enums)} typed enums: {sorted(typed_enums)}")

    # Parse all enums
    enums = parse_enums(content)
    print(f"Found {len(enums)} enum definitions")

    # Generate the C++ file
    cpp_content = generate_cpp(enums, typed_enums, version)

    # Write output
    output_path.write_text(cpp_content)
    print(f"Generated {output_path}")


if __name__ == "__main__":
    main()
