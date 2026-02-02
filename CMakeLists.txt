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
  src/cpp/imgui/imgui_structs.cpp
  src/cpp/imgui/imgui_structs_fonts.cpp
  src/cpp/imgui/imgui_macros.cpp
  src/cpp/imgui/imgui_structs_io.cpp
  src/cpp/imgui/imgui_structs_style.cpp
  src/cpp/imgui/imgui_structs_drawlist.cpp

  src/cpp/imgui/imgui_api_main.cpp
  src/cpp/imgui/imgui_api_context_creation.cpp
  src/cpp/imgui/imgui_api_demo_debug.cpp
  src/cpp/imgui/imgui_api_styles.cpp
  src/cpp/imgui/imgui_api_windows.cpp
  src/cpp/imgui/imgui_api_child_windows.cpp
  src/cpp/imgui/imgui_api_window_utilities.cpp
  src/cpp/imgui/imgui_api_window_manipulation.cpp
  src/cpp/imgui/imgui_api_scrolling.cpp
  src/cpp/imgui/imgui_api_parameter_stacks.cpp
  src/cpp/imgui/imgui_api_style_read.cpp
  src/cpp/imgui/imgui_api_cursor_layout.cpp
  src/cpp/imgui/imgui_api_id_stack.cpp
  src/cpp/imgui/imgui_api_widgets_text.cpp
  src/cpp/imgui/imgui_api_widgets_main.cpp
  src/cpp/imgui/imgui_api_widgets_images.cpp
  src/cpp/imgui/imgui_api_widgets_combo.cpp
  src/cpp/imgui/imgui_api_widgets_drag.cpp
  src/cpp/imgui/imgui_api_widgets_sliders.cpp
  src/cpp/imgui/imgui_api_widgets_input.cpp
  src/cpp/imgui/imgui_api_widgets_color.cpp
  src/cpp/imgui/imgui_api_widgets_trees.cpp
  src/cpp/imgui/imgui_api_widgets_selectables.cpp
  src/cpp/imgui/imgui_api_widgets_listbox.cpp
  src/cpp/imgui/imgui_api_data_plotting.cpp
  src/cpp/imgui/imgui_api_menus.cpp
  src/cpp/imgui/imgui_api_tooltips.cpp
  src/cpp/imgui/imgui_api_popups.cpp
  src/cpp/imgui/imgui_api_tables.cpp
  src/cpp/imgui/imgui_api_columns_legacy.cpp
  src/cpp/imgui/imgui_api_tab_bars.cpp
  src/cpp/imgui/imgui_api_logging.cpp
  src/cpp/imgui/imgui_api_drag_drop.cpp
  src/cpp/imgui/imgui_api_disabling.cpp
  src/cpp/imgui/imgui_api_clipping.cpp
  src/cpp/imgui/imgui_api_focus_activation.cpp
  src/cpp/imgui/imgui_api_overlapping_items.cpp
  src/cpp/imgui/imgui_api_item_query.cpp
  src/cpp/imgui/imgui_api_viewports.cpp
  src/cpp/imgui/imgui_api_draw_lists.cpp
  src/cpp/imgui/imgui_api_misc_utils.cpp
  src/cpp/imgui/imgui_api_text_utils.cpp
  src/cpp/imgui/imgui_api_color_utils.cpp
  src/cpp/imgui/imgui_api_inputs_keyboard.cpp
  src/cpp/imgui/imgui_api_inputs_mouse.cpp
  src/cpp/imgui/imgui_api_clipboard.cpp
  src/cpp/imgui/imgui_api_settings.cpp
  src/cpp/imgui/imgui_api_debug.cpp
  src/cpp/imgui/imgui_api_allocators.cpp

  src/cpp/imgui/implot.cpp
  src/cpp/imgui/implot_enums.cpp

  src/cpp/imgui/imgui_utils.h

)
set_target_properties(polyscope_bindings PROPERTIES CXX_VISIBILITY_PRESET "default")

target_include_directories(polyscope_bindings PUBLIC "${EIGEN3_INCLUDE_DIR}")
target_link_libraries(polyscope_bindings PRIVATE polyscope)

# Generate type stubs
nanobind_add_stub(
  polyscope_stub
  MODULE polyscope_bindings

  PYTHON_PATH $<TARGET_FILE_DIR:polyscope_bindings>
  DEPENDS polyscope_bindings

  MARKER_FILE py.typed

  RECURSIVE

  OUTPUT_PATH .
  OUTPUT
      __init__.pyi
      imgui.pyi
      implot.pyi
)

# Copy stub files into the appropriate place in the source directory after build
set(STUB_FILES __init__.pyi imgui.pyi implot.pyi)
foreach(STUB_FILE ${STUB_FILES})
  add_custom_command(
    TARGET polyscope_stub POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/polyscope_bindings/${STUB_FILE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/polyscope_bindings/${STUB_FILE}
    VERBATIM
  )
endforeach()


install(TARGETS polyscope_bindings LIBRARY DESTINATION .)