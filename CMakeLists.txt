cmake_minimum_required(VERSION 3.15.0) # minimum imposed by scikit-build-core
project(polyscope LANGUAGES CXX)

option(POLYSCOPE_PY_UNITY_BUILD "Enable Unity builds" ON)

## Gather dependencies

# Eigen
set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/eigen/")

# Recurse in to pybind
set(PYBIND11_NEWPYTHON ON)
add_subdirectory(deps/pybind11)

# We need polyscope
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(deps/polyscope)

pybind11_add_module(polyscope_bindings 
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
  src/cpp/imgui.cpp
  src/cpp/implot.cpp

  src/cpp/utils.h
  src/cpp/imgui_utils.h
)
set_target_properties(polyscope_bindings PROPERTIES CXX_VISIBILITY_PRESET "default")

target_include_directories(polyscope_bindings PUBLIC "${EIGEN3_INCLUDE_DIR}")
target_link_libraries(polyscope_bindings PRIVATE polyscope)

if(POLYSCOPE_PY_UNITY_BUILD)

  # NOTE: these are not perfect, sometimes the explicit template 
  # instantiations get messed up and cause compile errors. The current
  # batch sizes were chosen because they happen to work around that.
  # 
  # However, this does give a nearly 50% speedup, so it can be worth using 
  # for long-running CI builds.

  set_target_properties(polyscope PROPERTIES
      UNITY_BUILD ON
      UNITY_BUILD_BATCH_SIZE 5
  )

  set_target_properties(polyscope_bindings PROPERTIES
      UNITY_BUILD ON
      UNITY_BUILD_BATCH_SIZE 4
  )

endif()

install(TARGETS polyscope_bindings LIBRARY DESTINATION .)