// ImGuiStyle struct bindings

#include "imgui_utils.h"

// clang-format off

void bind_imgui_style(nb::module_& m) {

    #define VEC2_PROPERTY(name)                            \
        def_prop_rw(#name, [](const ImGuiStyle& style) {  \
            return from_vec2(style.name);                  \
        }, [](ImGuiStyle& style, const Vec2T& value) {     \
            style.name = to_vec2(value);                   \
        })

    nb::class_<ImGuiStyle>(m, "ImGuiStyle")
        // Main
        .def_rw("Alpha", &ImGuiStyle::Alpha)
        .def_rw("DisabledAlpha", &ImGuiStyle::DisabledAlpha)

        // Window
        .VEC2_PROPERTY(WindowPadding)
        .def_rw("WindowRounding", &ImGuiStyle::WindowRounding)
        .def_rw("WindowBorderSize", &ImGuiStyle::WindowBorderSize)
        .def_rw("WindowBorderHoverPadding", &ImGuiStyle::WindowBorderHoverPadding)
        .VEC2_PROPERTY(WindowMinSize)
        .VEC2_PROPERTY(WindowTitleAlign)
        .def_rw("WindowMenuButtonPosition", &ImGuiStyle::WindowMenuButtonPosition)

        // Child windows
        .def_rw("ChildRounding", &ImGuiStyle::ChildRounding)
        .def_rw("ChildBorderSize", &ImGuiStyle::ChildBorderSize)

        // Popups
        .def_rw("PopupRounding", &ImGuiStyle::PopupRounding)
        .def_rw("PopupBorderSize", &ImGuiStyle::PopupBorderSize)

        // Frames
        .VEC2_PROPERTY(FramePadding)
        .def_rw("FrameRounding", &ImGuiStyle::FrameRounding)
        .def_rw("FrameBorderSize", &ImGuiStyle::FrameBorderSize)

        // Spacing
        .VEC2_PROPERTY(ItemSpacing)
        .VEC2_PROPERTY(ItemInnerSpacing)
        .VEC2_PROPERTY(CellPadding)
        .VEC2_PROPERTY(TouchExtraPadding)
        .def_rw("IndentSpacing", &ImGuiStyle::IndentSpacing)
        .def_rw("ColumnsMinSpacing", &ImGuiStyle::ColumnsMinSpacing)

        // Scrollbars
        .def_rw("ScrollbarSize", &ImGuiStyle::ScrollbarSize)
        .def_rw("ScrollbarRounding", &ImGuiStyle::ScrollbarRounding)

        // Grab handles
        .def_rw("GrabMinSize", &ImGuiStyle::GrabMinSize)
        .def_rw("GrabRounding", &ImGuiStyle::GrabRounding)
        .def_rw("LogSliderDeadzone", &ImGuiStyle::LogSliderDeadzone)

        // Images
        .def_rw("ImageBorderSize", &ImGuiStyle::ImageBorderSize)

        // Tabs
        .def_rw("TabRounding", &ImGuiStyle::TabRounding)
        .def_rw("TabBorderSize", &ImGuiStyle::TabBorderSize)
        .def_rw("TabCloseButtonMinWidthSelected", &ImGuiStyle::TabCloseButtonMinWidthSelected)
        .def_rw("TabCloseButtonMinWidthUnselected", &ImGuiStyle::TabCloseButtonMinWidthUnselected)
        .def_rw("TabBarBorderSize", &ImGuiStyle::TabBarBorderSize)
        .def_rw("TabBarOverlineSize", &ImGuiStyle::TabBarOverlineSize)

        // Tables
        .def_rw("TableAngledHeadersAngle", &ImGuiStyle::TableAngledHeadersAngle)
        .VEC2_PROPERTY(TableAngledHeadersTextAlign)

        // Widgets
        .def_rw("ColorButtonPosition", &ImGuiStyle::ColorButtonPosition)
        .VEC2_PROPERTY(ButtonTextAlign)
        .VEC2_PROPERTY(SelectableTextAlign)

        // Separators
        .def_rw("SeparatorTextBorderSize", &ImGuiStyle::SeparatorTextBorderSize)
        .VEC2_PROPERTY(SeparatorTextAlign)
        .VEC2_PROPERTY(SeparatorTextPadding)

        // Display
        .VEC2_PROPERTY(DisplayWindowPadding)
        .VEC2_PROPERTY(DisplaySafeAreaPadding)
        .def_rw("MouseCursorScale", &ImGuiStyle::MouseCursorScale)

        // Anti-aliasing
        .def_rw("AntiAliasedLines", &ImGuiStyle::AntiAliasedLines)
        .def_rw("AntiAliasedLinesUseTex", &ImGuiStyle::AntiAliasedLinesUseTex)
        .def_rw("AntiAliasedFill", &ImGuiStyle::AntiAliasedFill)

        // Tessellation
        .def_rw("CurveTessellationTol", &ImGuiStyle::CurveTessellationTol)
        .def_rw("CircleTessellationMaxError", &ImGuiStyle::CircleTessellationMaxError)

        // Colors
        // TODO think about making this more similar to the C++ style
        // Provide indexed access to color array
        .def("GetColor", [](const ImGuiStyle& style, int idx) {
            if (idx < 0 || idx >= ImGuiCol_COUNT) {
                throw std::out_of_range("Color index out of range: " + std::to_string(idx));
            }
            return from_vec4(style.Colors[idx]);
        }, nb::arg("idx"), "Get color by index")

        .def("SetColor", [](ImGuiStyle& style, int idx, const Vec4T& color) {
            if (idx < 0 || idx >= ImGuiCol_COUNT) {
                throw std::out_of_range("Color index out of range: " + std::to_string(idx));
            }
            style.Colors[idx] = to_vec4(color);
        }, nb::arg("idx"), nb::arg("color"), "Set color by index")

        .def("GetColorCount", [](ImGuiStyle& style) {
            return static_cast<uint32_t>(ImGuiCol_COUNT);
        }, "Get total number of colors")

        // Behaviors
        .def_rw("HoverStationaryDelay", &ImGuiStyle::HoverStationaryDelay)
        .def_rw("HoverDelayShort", &ImGuiStyle::HoverDelayShort)
        .def_rw("HoverDelayNormal", &ImGuiStyle::HoverDelayNormal)
        .def_rw("HoverFlagsForTooltipMouse", &ImGuiStyle::HoverFlagsForTooltipMouse)
        .def_rw("HoverFlagsForTooltipNav", &ImGuiStyle::HoverFlagsForTooltipNav)

        // Methods
        .def("ScaleAllSizes", &ImGuiStyle::ScaleAllSizes, nb::arg("scale_factor"))
    ;

    #undef VEC2_PROPERTY
}
