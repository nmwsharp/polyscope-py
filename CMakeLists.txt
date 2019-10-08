cmake_minimum_required(VERSION 3.8.0)

project(polyscope-py)
cmake_minimum_required(VERSION 3.1)
project(polyscope-py)

# Gather dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Recurse in to pybind
add_subdirectory(pybind11)

# We need polyscope
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(polyscope)

pybind11_add_module(polyscope_py src/polyscope_py.cpp)
target_link_libraries(polyscope_py PRIVATE polyscope)
target_link_libraries(polyscope_py PRIVATE Eigen3::Eigen)

# make the resulting target actually be called polyscope, without the py
set_target_properties(polyscope_py PROPERTIES OUTPUT_NAME polyscope)
