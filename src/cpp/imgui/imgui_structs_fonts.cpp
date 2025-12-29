// Font structs: ImFontAtlas and ImFont

#include "imgui_utils.h"

// clang-format off

void bind_imgui_fonts(nb::module_& m) {

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

        // IMGUI_API void              ClearInputData();           // Clear input data (all ImFontConfig structures including sizes, TTF data, glyph ranges, etc.) = all the data used to build the texture and fonts.
        .def("ClearInputData", &ImFontAtlas::ClearInputData, "Clear input data")

        // IMGUI_API void              ClearFonts();               // Clear input+output font data (same as ClearInputData() + glyphs storage, UV coordinates).
        .def("ClearFonts", &ImFontAtlas::ClearFonts, "Clear fonts")

        // IMGUI_API void              ClearTexData();             // Clear output texture data (CPU side). Saves RAM once the texture has been copied to graphics memory.
        .def("ClearTexData", &ImFontAtlas::ClearTexData, "Clear texture data")

        // IMGUI_API void              Clear();                    // Clear all input and output.
        .def("Clear", &ImFontAtlas::Clear, "Clear all")

        // IMGUI_API bool              Build();                    // Build pixels data. This is called automatically for you by the GetTexData*** functions.
        .def("Build", &ImFontAtlas::Build, "Build atlas")

        // bool                        IsBuilt() const             { return Fonts.Size > 0 && TexReady; }
        .def("IsBuilt", &ImFontAtlas::IsBuilt, "Check if atlas is built")

        // void                        SetTexID(ImTextureID id)    { TexID = id; }
        // Not bound - ImTextureID is a void* pointer

        // IMGUI_API const ImWchar*    GetGlyphRangesDefault();
        // Not bound - returns pointer to static data, difficult to use from Python

        // IMGUI_API const ImWchar*    GetGlyphRangesGreek();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesKorean();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesJapanese();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesChineseFull();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesChineseSimplifiedCommon();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesCyrillic();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesThai();
        // Not bound - returns pointer to static data

        // IMGUI_API const ImWchar*    GetGlyphRangesVietnamese();
        // Not bound - returns pointer to static data

        // Properties
        .def_rw("Flags", &ImFontAtlas::Flags, "Build flags")
        .def_rw("TexDesiredWidth", &ImFontAtlas::TexDesiredWidth, "Texture width desired by user before Build()")
        .def_rw("TexGlyphPadding", &ImFontAtlas::TexGlyphPadding, "Padding between glyphs within texture in pixels")
        .def_ro("TexWidth", &ImFontAtlas::TexWidth, "Texture width calculated during Build()")
        .def_ro("TexHeight", &ImFontAtlas::TexHeight, "Texture height calculated during Build()")
        .def_prop_ro("TexUvScale", [](const ImFontAtlas& atlas) { return from_vec2(atlas.TexUvScale); }, "Texture UV scale")
        .def_prop_ro("TexUvWhitePixel", [](const ImFontAtlas& atlas) { return from_vec2(atlas.TexUvWhitePixel); }, "Texture coordinates to a white pixel")
    ;

    // ImFont - Runtime data for a single font
    nb::class_<ImFont>(m, "ImFont")
        // IMGUI_API ImFontGlyph*      FindGlyph(ImWchar c);
        // Not bound - returns pointer to glyph data

        // IMGUI_API ImFontGlyph*      FindGlyphNoFallback(ImWchar c);
        // Not bound - returns pointer to glyph data

        // float                       GetCharAdvance(ImWchar c)       { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }
        .def("GetCharAdvance", &ImFont::GetCharAdvance, nb::arg("c"), "Get character advance")

        // bool                        IsLoaded() const                { return ContainerAtlas != NULL; }
        .def("IsLoaded", &ImFont::IsLoaded, "Check if font is loaded")

        // const char*                 GetDebugName() const            { return Sources ? Sources->Name : "<unknown>"; }
        .def("GetDebugName", &ImFont::GetDebugName, "Get debug name")

        // IMGUI_API ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL);
        .def("CalcTextSizeA", [](ImFont& font, float size, float max_width, float wrap_width, const char* text_begin) {
            return from_vec2(font.CalcTextSizeA(size, max_width, wrap_width, text_begin, nullptr, nullptr));
        }, nb::arg("size"), nb::arg("max_width"), nb::arg("wrap_width"), nb::arg("text_begin"), "Calculate text size")

        // Properties
        .def_ro("FontSize", &ImFont::FontSize, "Height of characters/line, set during loading")
        .def_rw("Scale", &ImFont::Scale, "Base font scale, multiplied by the per-window font scale")
        .def_ro("Ascent", &ImFont::Ascent, "Ascent: distance from top to bottom of e.g. 'A'")
        .def_ro("Descent", &ImFont::Descent, "Descent")
        .def_ro("ContainerAtlas", &ImFont::ContainerAtlas, nb::rv_policy::reference, "What we has been loaded into")
    ;
}

// clang-format on
