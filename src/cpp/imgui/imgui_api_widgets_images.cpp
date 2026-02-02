#include "imgui.h"
#include "implot.h"

#include "Eigen/Dense"

#include "../utils.h"
#include "imgui_utils.h"

#include <nanobind/stl/array.h>

// clang-format off
void bind_imgui_api_widgets_images(nb::module_& m) {

    // Widgets: Images
    // IMGUI_API void          Image(ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1));
    m.def(
        "Image",
        [](ImTextureRef tex_ref, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1) {
            ImGui::Image(tex_ref, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1));
        },
        nb::arg("user_texture_ref"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.f, 0.f),
        nb::arg("uv1") = Vec2T(1.f, 1.f));

    // IMGUI_API void          ImageWithBg(ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
    m.def(
        "ImageWithBg",
        [](ImTextureRef tex_ref, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1, const Vec4T& bg_col, const Vec4T& tint_col) {
            ImGui::ImageWithBg(tex_ref, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1), to_vec4(bg_col), to_vec4(tint_col));
        },
        nb::arg("user_texture_ref"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.f, 0.f),
        nb::arg("uv1") = Vec2T(1.f, 1.f),
        nb::arg("bg_col") = Vec4T(0.f, 0.f, 0.f, 0.f),
        nb::arg("tint_col") = Vec4T(1.f, 1.f, 1.f, 1.f));

    // IMGUI_API bool          ImageButton(const char* str_id, ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
    m.def(
        "ImageButton",
        [](const char* str_id, ImTextureRef tex_ref, const Vec2T& image_size, const Vec2T& uv0, const Vec2T& uv1, const Vec4T& bg_col, const Vec4T& tint_col) {
            return ImGui::ImageButton(str_id, tex_ref, to_vec2(image_size), to_vec2(uv0), to_vec2(uv1), to_vec4(bg_col), to_vec4(tint_col));
        },
        nb::arg("str_id"),
        nb::arg("user_texture_ref"),
        nb::arg("image_size"),
        nb::arg("uv0") = Vec2T(0.f, 0.f),
        nb::arg("uv1") = Vec2T(1.f, 1.f),
        nb::arg("bg_col") = Vec4T(0.f, 0.f, 0.f, 0.f),
        nb::arg("tint_col") = Vec4T(1.f, 1.f, 1.f, 1.f));

}
// clang-format on
