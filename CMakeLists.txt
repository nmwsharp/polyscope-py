cmake_minimum_required(VERSION 3.15.0)
project(polyscope LANGUAGES CXX)

include(FeatureSummary)

option(USE_SYSTEM_EIGEN "Use system-installed Eigen if available" ON)

if(USE_SYSTEM_EIGEN)
  find_package(Eigen3 CONFIG QUIET)
  if(Eigen3_FOUND)
    message(STATUS "Found system Eigen3: ${Eigen3_INCLUDE_DIRS}")
  else()
    message(WARNING "System Eigen not found. Falling back to bundled version.")
    set(USE_SYSTEM_EIGEN OFF)
  endif()
endif()

if(NOT USE_SYSTEM_EIGEN)
  message(STATUS "Using bundled Eigen from deps/eigen")
  set(EIGEN3_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/deps/eigen")
endif()

# Recurse into pybind
set(PYBIND11_NEWPYTHON ON)
add_subdirectory(deps/pybind11)

# Polyscope
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(deps/polyscope)

# The actual pybind module
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
)

set_target_properties(polyscope_bindings PROPERTIES CXX_VISIBILITY_PRESET "default")

if(Eigen3_FOUND AND USE_SYSTEM_EIGEN)
  # Modern approach: link the imported Eigen3::Eigen target
  target_link_libraries(polyscope_bindings PRIVATE Eigen3::Eigen)
else()
  # Fallback: manually include the "deps/eigen" directory
  target_include_directories(polyscope_bindings PRIVATE "${EIGEN3_INCLUDE_DIRS}")
endif()

target_link_libraries(polyscope_bindings PRIVATE polyscope)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

install(TARGETS polyscope_bindings LIBRARY DESTINATION .)