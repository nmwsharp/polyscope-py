#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/affine_remapper.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_parameterization_enums.h"
#include "polyscope/view.h"

namespace py = pybind11;
namespace ps = polyscope;

// For overloaded functions, with C++11 compiler only
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

// clang-format off
void bind_imgui(py::module& m) {


  // === Text
  m.def("TextUnformatted", [](const std::string& s) { ImGui::TextUnformatted(s.c_str()); });


  // InputFloat
  // InputInt
  // InputText
  // Combobox?
  // Text?
  // Color


  // === Inputs
  m.def("Button", [](const std::string& s) { return ImGui::Button(s.c_str()); });
  m.def("Checkbox", [](const std::string& s, bool val) { return std::make_tuple(ImGui::Checkbox(s.c_str(), &val), val); });
  m.def("InputInt", [](const std::string& s, int val, int step, int step_fast) { 
      return std::make_tuple(ImGui::InputInt(s.c_str(), &val, step, step_fast), val); });
  m.def("InputFloat", [](const std::string& s, float val, float step, float step_fast, const std::string& format) { 
      return std::make_tuple(ImGui::InputFloat(s.c_str(), &val, step, step, format.c_str()), val); });
  m.def("SliderFloat", [](const std::string& s, float val, float v_min, float v_max, const std::string& format, float power) { 
      return std::make_tuple(ImGui::SliderFloat(s.c_str(), &val, v_min, v_max, format.c_str(), power), val); });

  
  m.def("InputText", [](const std::string& s, const std::string& val) { 
      static char text_buf[1024 * 16]; 
      snprintf(text_buf, sizeof(text_buf), "%s", val.c_str());
      return std::make_tuple(ImGui::InputText(s.c_str(), text_buf, sizeof(text_buf)), std::string(text_buf)); });

  // === Posiitioning / Sizing / Layout


  // Posiitioning and size
  m.def("Separator", []() { ImGui::Separator(); });
  m.def("SameLine", []() { ImGui::SameLine(); });
  m.def("NewLine", []() { ImGui::NewLine(); });
  m.def("Indent", [](float w) { ImGui::Indent(w); });
  m.def("Unindent", [](float w) { ImGui::Unindent(w); });

  m.def("PushItemWidth", [](float w) { ImGui::PushItemWidth(w); });
  m.def("PopItemWidth", []() { ImGui::PopItemWidth(); });
  m.def("PushID", [](const std::string& s) { ImGui::PushID(s.c_str()); });
  m.def("PopID", []() { ImGui::PopID(); });
  m.def("TreeNode", [](const std::string& s, bool DefaultOpen) { 
      if(DefaultOpen) return ImGui::TreeNodeEx(s.c_str(), ImGuiTreeNodeFlags_DefaultOpen); 
      else return ImGui::TreeNode(s.c_str()); 
    });
  m.def("TreePop", []() { return ImGui::TreePop(); });

}
  
