#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/affine_remapper.h"
#include "polyscope/curve_network.h"
#include "polyscope/pick.h"
#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/surface_parameterization_enums.h"
#include "polyscope/view.h"
#include "polyscope/volume_mesh.h"

namespace py = pybind11;
namespace ps = polyscope;

// For overloaded functions, with C++11 compiler only
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;


// Forward-declare bindings from other files
void bind_surface_mesh(py::module& m);
void bind_point_cloud(py::module& m);
void bind_curve_network(py::module& m);
void bind_volume_mesh(py::module& m);
void bind_imgui(py::module& m);

// Signal handler (makes ctrl-c work, etc)
void checkSignals() {
  if (PyErr_CheckSignals() != 0) throw py::error_already_set();
}
void defaultCallback() { checkSignals(); }

// Actual binding code
// clang-format off
PYBIND11_MODULE(polyscope_bindings, m) {
  m.doc() = "Polyscope low-level bindings";
  

  // Register a cleanup function which will run when the module is exiting.
  // Suggested at: https://pybind11.readthedocs.io/en/stable/advanced/misc.html#module-destructors
  // We use it to ensure any Python data held on the C++ side gets properly deleted and cleaned up. This
  // is particularly difficult to do any other way, because Polyscope extensively uses static variables 
  // to hold this state, so we can't just fall back on some other object's lifetime.
  auto atexit = py::module_::import("atexit");
  atexit.attr("register")(py::cpp_function([]() {
        ps::state::userCallback = nullptr;
        if (ps::render::engine != nullptr) {
          ps::shutdown();
        }
  }));
  
  // === Basic flow 
  m.def("init", &ps::init, py::arg("backend")="", "Initialize Polyscope");
  m.def("checkInitialized", &ps::checkInitialized);
  m.def("isInitialized", &ps::isInitialized);
  m.def("show", [](size_t forFrames) {
        if (ps::state::userCallback == nullptr) {
          bool oldVal = ps::options::openImGuiWindowForUserCallback;
          ps::options::openImGuiWindowForUserCallback = false;
          ps::state::userCallback = defaultCallback; // use the default callback to ensure signals get checked
          ps::show(forFrames);
          ps::state::userCallback = nullptr;
          ps::options::openImGuiWindowForUserCallback = oldVal;
        } else {
          // otherwise, we can just directly call show()
          // (the set_user_callback()) function ensures that the signal check is performed in
          // this case
          ps::show(forFrames);
        }
      },
      py::arg("forFrames")=std::numeric_limits<size_t>::max()
  );
  m.def("shutdown", &ps::shutdown);

  // === Structure management
  m.def("remove_all_structures", &ps::removeAllStructures, "Remove all structures from polyscope");
  
  // === Screenshots
  m.def("screenshot", overload_cast_<bool>()(&ps::screenshot), "Take a screenshot");
  m.def("named_screenshot", overload_cast_<std::string, bool>()(&ps::screenshot), "Take a screenshot");
  m.def("set_screenshot_extension", [](std::string x) { ps::options::screenshotExtension = x; });

  // === Small options
  m.def("set_program_name", [](std::string x) { ps::options::programName = x; });
  m.def("set_verbosity", [](int x) { ps::options::verbosity = x; });
  m.def("set_print_prefix", [](std::string x) { ps::options::printPrefix = x; });
  m.def("set_max_fps", [](int x) { ps::options::maxFPS = x; });
  m.def("set_errors_throw_exceptions", [](bool x) { ps::options::errorsThrowExceptions = x; });
  m.def("set_use_prefs_file", [](bool x) { ps::options::usePrefsFile = x; });
  m.def("set_always_redraw", [](bool x) { ps::options::alwaysRedraw = x; });
  m.def("set_enable_render_error_checks", [](bool x) { ps::options::enableRenderErrorChecks = x; });
  m.def("set_autocenter_structures", [](bool x) { ps::options::autocenterStructures = x; });
  m.def("set_autoscale_structures", [](bool x) { ps::options::autoscaleStructures = x; });
  m.def("set_build_gui", [](bool x) { ps::options::buildGui = x; });
  m.def("set_open_imgui_window_for_user_callback", [](bool x) { ps::options::openImGuiWindowForUserCallback= x; });
  m.def("set_invoke_user_callback_for_nested_show", [](bool x) { ps::options::invokeUserCallbackForNestedShow = x; });
  m.def("set_give_focus_on_show", [](bool x) { ps::options::giveFocusOnShow = x; });
  m.def("set_navigation_style", [](ps::view::NavigateStyle x) { ps::view::style = x; });
  m.def("set_up_dir", [](ps::view::UpDir x) { ps::view::setUpDir(x); });

  // === Scene extents
  m.def("set_automatically_compute_scene_extents", [](bool x) { ps::options::automaticallyComputeSceneExtents = x; });
  m.def("set_length_scale", [](float x) { ps::state::lengthScale = x; });
  m.def("get_length_scale", []() { return ps::state::lengthScale; });
  m.def("set_bounding_box", [](glm::vec3 low, glm::vec3 high) { ps::state::boundingBox = std::tuple<glm::vec3, glm::vec3>(low, high); });
  m.def("get_bounding_box", []() { return ps::state::boundingBox; });

  // === Camera controls
  m.def("reset_camera_to_home_view", ps::view::resetCameraToHomeView);
  m.def("look_at", [](glm::vec3 location, glm::vec3 target, bool flyTo) { 
      ps::view::lookAt(location, target, flyTo); 
  });
  m.def("look_at_dir", [](glm::vec3 location, glm::vec3 target, glm::vec3 upDir, bool flyTo) { 
      ps::view::lookAt(location, target, upDir, flyTo); 
  });
  m.def("set_view_projection_mode", [](ps::ProjectionMode x) { ps::view::projectionMode = x; });
  
  // === Messages
  m.def("info", ps::info, "Send an info message");
  m.def("warning", ps::warning, "Send a warning message");
  m.def("error", ps::error, "Send an error message");
  m.def("terminating_error", ps::terminatingError, "Send a terminating error message");

  // === Callback
  m.def("set_user_callback", [](const std::function<void(void)>& func) { 
      // Create a wrapper which checks signals before calling the passed fuction
      // Captures by value, because otherwise func seems to become invalid. This is probably happening
      // on the Python side, and could be fixed with some Pybind11 keep_alive-s or something, but in
      // lieu of figuring that out capture by value seems fine.
      // See also the atexit() cleanup registered above, which is used to ensure any bound functions get deleted and we can exit cleanly.
      auto wrapperFunc = [=]()  { 
        checkSignals(); 
        func();
      };
      ps::state::userCallback = wrapperFunc;
  });
  m.def("clear_user_callback", []() {ps::state::userCallback = nullptr;});

  // === Pick
  m.def("have_selection", [](){ return ps::pick::haveSelection();});
  m.def("get_selection", [](){
    const auto selection = ps::pick::getSelection();
    const auto * structure = std::get<0>(selection);
    if (structure == nullptr) {
      return std::make_tuple(std::string(), size_t{0});
    }
    return std::make_tuple(structure->name, std::get<1>(selection));
  });
  m.def(
    "set_selection",
    [](const std::string &name, size_t index){
      for(const auto &structureTypeName : std::array<std::string, 4>{
        ps::PointCloud::structureTypeName,
        ps::CurveNetwork::structureTypeName,
        ps::SurfaceMesh::structureTypeName,
        ps::VolumeMesh::structureTypeName
      }) {
        if (ps::hasStructure(structureTypeName, name)) {
          auto * structure = ps::getStructure(structureTypeName, name);
          ps::pick::setSelection(std::make_pair(structure, index));
          break;
        }
      }
    },
    py::arg("name"),
    py::arg("index")
  );

  // === Ground plane and shadows
  m.def("set_ground_plane_mode", [](ps::GroundPlaneMode x) { ps::options::groundPlaneMode = x; });
  m.def("set_ground_plane_height_factor", [](float x, bool isRelative) { ps::options::groundPlaneHeightFactor.set(x, isRelative); });
  m.def("set_shadow_blur_iters", [](int x) { ps::options::shadowBlurIters = x; });
  m.def("set_shadow_darkness", [](float x) { ps::options::shadowDarkness = x; });
  
  // === Transparency
  m.def("set_transparency_mode", [](ps::TransparencyMode x) { ps::options::transparencyMode = x; });
  m.def("set_transparency_render_passes", [](int n) { ps::options::transparencyRenderPasses = n; });
  
  // === Materials
  m.def("load_static_material", ps::loadStaticMaterial, "Load a static material");
  m.def("load_blendable_material_explicit", overload_cast_<std::string, std::array<std::string,4>>()(&ps::loadBlendableMaterial), 
        "Load a blendable material from explicit names");
  m.def("load_blendable_material_baseext", overload_cast_<std::string, std::string, std::string>()(&ps::loadBlendableMaterial), 
        "Load a blendable material from base and ext names");
  
  // === Colormaps
  m.def("load_color_map", ps::loadColorMap, "Load a color map from file");
  
  // === Rendering
  m.def("set_SSAA_factor", [](int n) { ps::options::ssaaFactor = n; });

  // === Slice planes
  py::class_<ps::SlicePlane>(m, "SlicePlane")
   .def(py::init<std::string>())
   .def_readonly("name", &ps::SlicePlane::name) 
   .def("set_pose", &ps::SlicePlane::setPose, "set pose")
   .def("set_active", &ps::SlicePlane::setActive, "set active")
   .def("get_active", &ps::SlicePlane::getActive, "get active")
   .def("set_draw_plane", &ps::SlicePlane::setDrawPlane, "set draw plane")
   .def("get_draw_plane", &ps::SlicePlane::getDrawPlane, "get draw plane")
   .def("set_draw_widget", &ps::SlicePlane::setDrawWidget, "set draw widget")
   .def("get_draw_widget", &ps::SlicePlane::getDrawWidget, "get draw widget")
   .def("set_volume_mesh_to_inspect", &ps::SlicePlane::setVolumeMeshToInspect, "set name of inspected volume mesh")
   .def("get_volume_mesh_to_inspect", &ps::SlicePlane::getVolumeMeshToInspect, "get name of inspected volume mesh");

  m.def("add_scene_slice_plane", ps::addSceneSlicePlane, "add a slice plane", py::return_value_policy::reference);
  m.def("remove_last_scene_slice_plane", ps::removeLastSceneSlicePlane, "remove last scene plane");
  
  // === Enums
  
  py::enum_<ps::view::NavigateStyle>(m, "NavigateStyle")
    .value("turntable", ps::view::NavigateStyle::Turntable)
    .value("free", ps::view::NavigateStyle::Free)
    .value("planar", ps::view::NavigateStyle::Planar)
    .value("arcball", ps::view::NavigateStyle::Arcball)
    .export_values(); 
  
  py::enum_<ps::ProjectionMode>(m, "ProjectionMode")
    .value("perspective", ps::ProjectionMode::Perspective)
    .value("orthographic", ps::ProjectionMode::Orthographic)
    .export_values(); 
  
  py::enum_<ps::view::UpDir>(m, "UpDir")
    .value("x_up", ps::view::UpDir::XUp)
    .value("y_up", ps::view::UpDir::YUp)
    .value("z_up", ps::view::UpDir::ZUp)
    .value("neg_x_up", ps::view::UpDir::NegXUp)
    .value("neg_y_up", ps::view::UpDir::NegYUp)
    .value("neg_z_up", ps::view::UpDir::NegZUp)
    .export_values(); 

  py::enum_<ps::DataType>(m, "DataType")
    .value("standard", ps::DataType::STANDARD)
    .value("symmetric", ps::DataType::SYMMETRIC)
    .value("magnitude", ps::DataType::MAGNITUDE)
    .export_values(); 

  py::enum_<ps::VectorType>(m, "VectorType")
    .value("standard", ps::VectorType::STANDARD)
    .value("ambient", ps::VectorType::AMBIENT)
    .export_values(); 
  
  py::enum_<ps::ParamCoordsType>(m, "ParamCoordsType")
    .value("unit", ps::ParamCoordsType::UNIT)
    .value("world", ps::ParamCoordsType::WORLD)
    .export_values(); 
  
  py::enum_<ps::ParamVizStyle>(m, "ParamVizStyle")
    .value("checker", ps::ParamVizStyle::CHECKER)
    .value("grid", ps::ParamVizStyle::GRID)
    .value("local_check", ps::ParamVizStyle::LOCAL_CHECK)
    .value("local_rad", ps::ParamVizStyle::LOCAL_RAD)
    .export_values(); 

  py::enum_<ps::BackFacePolicy>(m, "BackFacePolicy")
    .value("identical", ps::BackFacePolicy::Identical)
    .value("different", ps::BackFacePolicy::Different)
    .value("custom", ps::BackFacePolicy::Custom)
    .value("cull", ps::BackFacePolicy::Cull)
    .export_values(); 
  
  py::enum_<ps::GroundPlaneMode>(m, "GroundPlaneMode")
    .value("none", ps::GroundPlaneMode::None)
    .value("tile", ps::GroundPlaneMode::Tile)
    .value("tile_reflection", ps::GroundPlaneMode::TileReflection)
    .value("shadow_only", ps::GroundPlaneMode::ShadowOnly)
    .export_values(); 
  
  py::enum_<ps::TransparencyMode>(m, "TransparencyMode")
    .value("none", ps::TransparencyMode::None)
    .value("simple", ps::TransparencyMode::Simple)
    .value("pretty", ps::TransparencyMode::Pretty)
    .export_values(); 
  
  py::enum_<ps::PointRenderMode>(m, "PointRenderMode")
    .value("sphere", ps::PointRenderMode::Sphere)
    .value("quad", ps::PointRenderMode::Quad)
    .export_values(); 

  // === Mini bindings for a little bit of glm
  py::class_<glm::vec3>(m, "glm_vec3").
    def(py::init<float, float, float>())
   .def("as_tuple",
        [](const glm::vec3& x) {
        return std::tuple<float, float, float>(x[0], x[1], x[2]);
        });
  
  py::class_<glm::vec4>(m, "glm_vec4").
    def(py::init<float, float, float, float>())
   .def("as_tuple",
        [](const glm::vec4& x) {
        return std::tuple<float, float, float, float>(x[0], x[1], x[2], x[3]);
        });

  // === Bind structures defined in other files
  bind_surface_mesh(m);
  bind_point_cloud(m);
  bind_curve_network(m);
  bind_volume_mesh(m);
  bind_imgui(m);

}

// clang-format on
