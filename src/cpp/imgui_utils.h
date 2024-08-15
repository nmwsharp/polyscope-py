#pragma once

#include "imgui.h"

#include <pybind11/pybind11.h>
#include <vector>


std::vector<const char*> convert_string_items(const std::vector<std::string>& items) {
  auto _items = std::vector<const char*>();
  _items.reserve(items.size());
  for (const auto& item : items) {
    _items.push_back(item.data());
  }
  return _items;
}

namespace PYBIND11_NAMESPACE {
namespace detail {

static bool set_value(float& v, PyObject* obj) {
  if (PyLong_Check(obj)) {
    v = static_cast<float>(PyLong_AsLong(obj));
    return true;
  } else if (PyFloat_Check(obj)) {
    v = static_cast<float>(PyFloat_AsDouble(obj));
    return true;
  }
  return false;
}


template <>
struct type_caster<ImVec2> {
public:
  PYBIND11_TYPE_CASTER(ImVec2, const_name("ImVec2"));

  bool load(handle src, bool) {
    PyObject* obj = src.ptr();
    if (!PyTuple_Check(obj)) {
      return false;
    }
    if (PyTuple_Size(obj) != 2) {
      return false;
    }

    PyObject* item0 = PyTuple_GetItem(obj, 0);
    PyObject* item1 = PyTuple_GetItem(obj, 1);
    if (!(set_value(value.x, item0) && set_value(value.y, item1))) {
      return false;
    }
    return !PyErr_Occurred();
  }

  static handle cast(ImVec2 src, return_value_policy /* policy */, handle /* parent */) {
    PyObject* dst = PyTuple_New(2);
    PyTuple_SetItem(dst, 0, PyFloat_FromDouble(src.x));
    PyTuple_SetItem(dst, 1, PyFloat_FromDouble(src.y));
    return dst;
  }
};


template <>
struct type_caster<ImVec4> {
public:
  PYBIND11_TYPE_CASTER(ImVec4, const_name("ImVec4"));

  bool load(handle src, bool) {
    PyObject* obj = src.ptr();
    if (!PyTuple_Check(obj)) {
      return false;
    }
    if (PyTuple_Size(obj) != 4) {
      return false;
    }

    PyObject* item0 = PyTuple_GetItem(obj, 0);
    PyObject* item1 = PyTuple_GetItem(obj, 1);
    PyObject* item2 = PyTuple_GetItem(obj, 2);
    PyObject* item3 = PyTuple_GetItem(obj, 3);
    if (!(set_value(value.x, item0) && set_value(value.y, item1) && set_value(value.z, item2) &&
          set_value(value.w, item3))) {
      return false;
    }
    return !PyErr_Occurred();
  }

  static handle cast(ImVec4 src, return_value_policy /* policy */, handle /* parent */) {
    PyObject* dst = PyTuple_New(4);
    PyTuple_SetItem(dst, 0, PyFloat_FromDouble(src.x));
    PyTuple_SetItem(dst, 1, PyFloat_FromDouble(src.y));
    PyTuple_SetItem(dst, 2, PyFloat_FromDouble(src.z));
    PyTuple_SetItem(dst, 3, PyFloat_FromDouble(src.w));
    return dst;
  }
};


} // namespace detail
} // namespace PYBIND11_NAMESPACE
