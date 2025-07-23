#pragma once

namespace py = pybind11;
namespace ps = polyscope;

// Type translations between Python and ImGui.  Prefer native Python types (tuples, arrays), translating into ImGui
// equivalents.
using Vec2T = std::tuple<float, float>;
using Vec4T = std::tuple<float, float, float, float>;

inline ImVec2 to_vec2(const Vec2T& v) { return ImVec2(std::get<0>(v), std::get<1>(v)); }
inline ImVec4 to_vec4(const Vec4T& v) { return ImVec4(std::get<0>(v), std::get<1>(v), std::get<2>(v), std::get<3>(v)); }

inline Vec2T from_vec2(const ImVec2& v) { return std::make_tuple(v.x, v.y); }
inline Vec4T from_vec4(const ImVec4& v) { return std::make_tuple(v.x, v.y, v.z, v.w); }


inline std::vector<const char*> convert_string_items(const std::vector<std::string>& items) {
  auto _items = std::vector<const char*>();
  _items.reserve(items.size());
  for (const auto& item : items) {
    _items.push_back(item.data());
  }
  return _items;
}