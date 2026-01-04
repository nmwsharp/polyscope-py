// Font structs: ImFontAtlas and ImFont

#include "imgui_utils.h"

// clang-format off

void bind_imgui_fonts(nb::module_& m) {

    // ImFontBaked - Font runtime data for a given size
    nb::class_<ImFontBaked>(m, "ImFontBaked")
        // IMGUI_API void              ClearOutputData();
        .def("ClearOutputData", &ImFontBaked::ClearOutputData, "Clear output data")

        // IMGUI_API ImFontGlyph*      FindGlyph(ImWchar c);
        // Not bound - returns pointer to glyph data

        // IMGUI_API ImFontGlyph*      FindGlyphNoFallback(ImWchar c);
        // Not bound - returns pointer to glyph data

        // IMGUI_API float             GetCharAdvance(ImWchar c);
        .def("GetCharAdvance", &ImFontBaked::GetCharAdvance, nb::arg("c"), "Get character advance")

        // IMGUI_API bool              IsGlyphLoaded(ImWchar c);
        .def("IsGlyphLoaded", &ImFontBaked::IsGlyphLoaded, nb::arg("c"), "Check if glyph is loaded")

        // Properties
        .def_ro("FallbackAdvanceX", &ImFontBaked::FallbackAdvanceX, "Fallback character advance")
        .def_ro("Size", &ImFontBaked::Size, "Font size in pixels")
        .def_ro("RasterizerDensity", &ImFontBaked::RasterizerDensity, "Density this is baked at")
        .def_ro("Ascent", &ImFontBaked::Ascent, "Ascent: distance from top to bottom of e.g. 'A'")
        .def_ro("Descent", &ImFontBaked::Descent, "Descent")
        .def_ro("OwnerFont", &ImFontBaked::OwnerFont, nb::rv_policy::reference, "Parent font")
    ;

    // ImFontAtlas - Font atlas for loading and building fonts
    nb::class_<ImFontAtlas>(m, "ImFontAtlas")
        // IMGUI_API ImFont*           AddFont(const ImFontConfig* font_cfg);
        // Not bound - requires ImFontConfig pointer management

        // IMGUI_API ImFont*           AddFontDefault(const ImFontConfig* font_cfg = NULL);
        .def("AddFontDefault", [](ImFontAtlas& atlas) {
            return atlas.AddFontDefault(nullptr);
        }, nb::rv_policy::reference, "Add default font")

        // IMGUI_API ImFont*           AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
        .def("AddFontFromFileTTF", [](ImFontAtlas& atlas, const std::string& filename, float size_pixels) {
            return atlas.AddFontFromFileTTF(filename.c_str(), size_pixels, nullptr, nullptr);
        }, nb::arg("filename"), nb::arg("size_pixels"), nb::rv_policy::reference, "Add font from TTF file")

        // IMGUI_API ImFont*           AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
        .def("AddFontFromMemoryCompressedBase85TTF", [](ImFontAtlas& atlas, const char* compressed_font_data_base85, float size_pixels) {
            return atlas.AddFontFromMemoryCompressedBase85TTF(compressed_font_data_base85, size_pixels, nullptr, nullptr);
        }, nb::arg("compressed_font_data_base85"), nb::arg("size_pixels"), nb::rv_policy::reference, "Add font from compressed base85 data")

        // IMGUI_API void              RemoveFont(ImFont* font);
        .def("RemoveFont", &ImFontAtlas::RemoveFont, nb::arg("font"), "Remove font from atlas")

        // IMGUI_API void              Clear();                    // Clear all input and output.
        .def("Clear", &ImFontAtlas::Clear, "Clear all")

        // IMGUI_API void              CompactCache();             // Compact cached glyphs and texture.
        .def("CompactCache", &ImFontAtlas::CompactCache, "Compact cache")

        // IMGUI_API bool              Build();                    // Build pixels data. This is called automatically for you by the GetTexData*** functions.
        .def("Build", &ImFontAtlas::Build, "Build atlas")

        // Properties
        .def_rw("Flags", &ImFontAtlas::Flags, "Build flags")
        .def_rw("Flags", &ImFontAtlas::Flags, "Build flags")
        .def_rw("TexGlyphPadding", &ImFontAtlas::TexGlyphPadding, "Padding between glyphs within texture in pixels")
        .def_prop_ro("TexUvScale", [](const ImFontAtlas& atlas) { return from_vec2(atlas.TexUvScale); }, "Texture UV scale")
        .def_prop_ro("TexUvWhitePixel", [](const ImFontAtlas& atlas) { return from_vec2(atlas.TexUvWhitePixel); }, "Texture coordinates to a white pixel")
    ;

    // ImFont - Runtime data for a single font
    nb::class_<ImFont>(m, "ImFont")
        // IMGUI_API ImFontGlyph*      FindGlyph(ImWchar c);
        // Not bound - returns pointer to glyph data

        // IMGUI_API ImFontGlyph*      FindGlyphNoFallback(ImWchar c);
        // Not bound - returns pointer to glyph data

        // bool                        IsLoaded() const                { return ContainerAtlas != NULL; }
        .def("IsLoaded", &ImFont::IsLoaded, "Check if font is loaded")

        // const char*                 GetDebugName() const            { return Sources ? Sources->Name : "<unknown>"; }
        .def("GetDebugName", &ImFont::GetDebugName, "Get debug name")

        // IMGUI_API ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL);
        .def("CalcTextSizeA", [](ImFont& font, float size, float max_width, float wrap_width, const char* text_begin) {
            return from_vec2(font.CalcTextSizeA(size, max_width, wrap_width, text_begin, nullptr, nullptr));
        }, nb::arg("size"), nb::arg("max_width"), nb::arg("wrap_width"), nb::arg("text_begin"), "Calculate text size")

        // IMGUI_API const char*       CalcWordWrapPosition(float size, const char* text, const char* text_end, float wrap_width);
        .def("CalcWordWrapPosition", [](ImFont& font, float size, std::string text, float wrap_width) {
            return font.CalcWordWrapPosition(size, text.c_str(), nullptr, wrap_width);
        }, nb::arg("size"), nb::arg("text"), nb::arg("wrap_width"), "Calculate word wrap position")

        // IMGUI_API ImFontBaked*      GetFontBaked(float font_size, float density = -1.0f);
        .def("GetFontBaked", &ImFont::GetFontBaked, nb::arg("font_size"), nb::arg("density") = -1.0f, nb::rv_policy::reference, "Get or create baked data for given size")

        // Properties
        .def_rw("Scale", &ImFont::Scale, "Base font scale, multiplied by the per-window font scale")
        .def_ro("OwnerAtlas", &ImFont::OwnerAtlas, nb::rv_policy::reference, "What we have been loaded into")
    ;
}

// clang-format on
