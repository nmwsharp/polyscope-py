cmake_minimum_required(VERSION 3.1.0)
project(polyscope-py)

# Gather dependencies
set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/eigen/")

# Recurse in to pybind
add_subdirectory(deps/pybind11)

# We need polyscope
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(deps/polyscope)

pybind11_add_module(polyscope_bindings 
  src/cpp/core.cpp
  src/cpp/surface_mesh.cpp
  src/cpp/point_cloud.cpp
  src/cpp/curve_network.cpp
)

target_include_directories(polyscope_bindings PUBLIC "${EIGEN3_INCLUDE_DIR}")
target_link_libraries(polyscope_bindings PRIVATE polyscope)

# make the resulting target actually be called polyscope, without the py
# set_target_properties(polyscope_py PROPERTIES OUTPUT_NAME polyscope)
