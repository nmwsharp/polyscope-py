cmake_minimum_required(VERSION 3.15.0) # minimum imposed by scikit-build-core
project(polyscope LANGUAGES CXX)

# Default to release build
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 20)

## Gather dependencies

# == Eigen
set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/eigen/")

# == Nanobind
if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

# find python version to target for bindings
find_package(Python 3.9 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

# recurse into nanobind
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/nanobind)

# == polyscope
add_subdirectory(deps/polyscope)

nanobind_add_module(polyscope_bindings 
  src/cpp/core.cpp
  src/cpp/surface_mesh.cpp
  src/cpp/point_cloud.cpp
  src/cpp/curve_network.cpp
  src/cpp/volume_mesh.cpp
  src/cpp/volume_grid.cpp
  src/cpp/camera_view.cpp
  src/cpp/floating_quantities.cpp
  src/cpp/implicit_helpers.cpp
  src/cpp/managed_buffer.cpp
  
  src/cpp/utils.h

  # ImGui related things
  src/cpp/imgui/imgui.cpp
  src/cpp/imgui/imgui_enums.cpp
  src/cpp/imgui/implot.cpp

  src/cpp/imgui/imgui_utils.h

)
set_target_properties(polyscope_bindings PROPERTIES CXX_VISIBILITY_PRESET "default")

target_include_directories(polyscope_bindings PUBLIC "${EIGEN3_INCLUDE_DIR}")
target_link_libraries(polyscope_bindings PRIVATE polyscope)

install(TARGETS polyscope_bindings LIBRARY DESTINATION .)