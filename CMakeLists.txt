cmake_minimum_required(VERSION 3.1.0)
project(polyscope-py)

# Gather dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Recurse in to pybind
add_subdirectory(deps/pybind11)

# We need polyscope
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(deps/polyscope)

pybind11_add_module(polyscope_bindings 
  src/cpp/core.cpp
  src/cpp/surface_mesh.cpp
)

target_link_libraries(polyscope_bindings PRIVATE polyscope)
target_link_libraries(polyscope_bindings PRIVATE Eigen3::Eigen)

# make the resulting target actually be called polyscope, without the py
# set_target_properties(polyscope_py PROPERTIES OUTPUT_NAME polyscope)
