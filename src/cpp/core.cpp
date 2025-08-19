#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Eigen/Dense"

#include "polyscope/affine_remapper.h"
#include "polyscope/camera_parameters.h"
#include "polyscope/curve_network.h"
#include "polyscope/messages.h"
#include "polyscope/pick.h"
#include "polyscope/point_cloud.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/types.h"
#include "polyscope/view.h"
#include "polyscope/volume_mesh.h"

#include "utils.h"

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
void bind_volume_grid(py::module& m);
void bind_camera_view(py::module& m);
void bind_floating_quantities(py::module& m);
void bind_implicit_helpers(py::module& m);
void bind_managed_buffer(py::module& m);
void bind_imgui(py::module& m);
void bind_implot(py::module& m);

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
          ps::shutdown(true);
        }
  }));
  
  // === Basic flow 
  m.def("init", &ps::init, py::arg("backend")="auto", "Initialize Polyscope");
  m.def("check_initialized", &ps::checkInitialized);
  m.def("is_initialized", &ps::isInitialized);
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
  m.def("unshow", &ps::unshow);
  m.def("window_requests_close", &ps::windowRequestsClose);
  m.def("frame_tick", &ps::frameTick);
  m.def("shutdown", &ps::shutdown);

  // === Render engine related things
  m.def("get_render_engine_backend_name", &ps::render::getRenderEngineBackendName);
  m.def("is_headless", &ps::isHeadless);
  m.def("set_allow_headless_backends", [](bool x) { ps::options::allowHeadlessBackends = x; });

  // === Structure management
  m.def("remove_all_structures", &ps::removeAllStructures, "Remove all structures from polyscope");
  
  // === Screenshots
  py::class_<ps::ScreenshotOptions>(m, "ScreenshotOptions")
   .def(py::init<>())
   .def_readwrite("include_UI", &ps::ScreenshotOptions::includeUI)
   .def_readwrite("transparent_background", &ps::ScreenshotOptions::transparentBackground)
  ;
  m.def("screenshot", overload_cast_<const ps::ScreenshotOptions&>()(&ps::screenshot), "Take a screenshot");
  m.def("screenshot_to_buffer", [](const ps::ScreenshotOptions& opts) { 
      std::vector<unsigned char> buff = ps::screenshotToBuffer(opts);
      return py::array(buff.size(), buff.data());
    }, "Take a screenshot to buffer");
  m.def("named_screenshot", overload_cast_<std::string, const ps::ScreenshotOptions&>()(&ps::screenshot), "Take a screenshot");
  m.def("set_screenshot_extension", [](std::string x) { ps::options::screenshotExtension = x; });

  // === Small options
  m.def("set_program_name", [](std::string x) { ps::options::programName = x; });
  m.def("set_verbosity", [](int x) { ps::options::verbosity = x; });
  m.def("set_print_prefix", [](std::string x) { ps::options::printPrefix = x; });
  m.def("set_errors_throw_exceptions", [](bool x) { ps::options::errorsThrowExceptions = x; });
  m.def("set_max_fps", [](int x) { ps::options::maxFPS = x; });
  m.def("set_enable_vsync", [](bool x) { ps::options::enableVSync = x; });
  m.def("set_use_prefs_file", [](bool x) { ps::options::usePrefsFile = x; });
  m.def("set_do_default_mouse_interaction", [](bool x) { ps::state::doDefaultMouseInteraction = x; });
  m.def("request_redraw", []() { ps::requestRedraw(); });
  m.def("get_redraw_requested", []() { return ps::redrawRequested(); });
  m.def("set_always_redraw", [](bool x) { ps::options::alwaysRedraw = x; });
  m.def("set_frame_tick_limit_fps_mode", [](ps::LimitFPSMode x) { ps::options::frameTickLimitFPSMode = x; });
  m.def("set_enable_render_error_checks", [](bool x) { ps::options::enableRenderErrorChecks = x; });
  m.def("set_egl_device_index", [](int x) { ps::options::eglDeviceIndex = x; });
  m.def("set_autocenter_structures", [](bool x) { ps::options::autocenterStructures = x; });
  m.def("set_autoscale_structures", [](bool x) { ps::options::autoscaleStructures = x; });
  m.def("set_ui_scale", [](float x) { ps::options::uiScale = x; });
  m.def("get_ui_scale", []() { return ps::options::uiScale; });
  m.def("set_build_gui", [](bool x) { ps::options::buildGui = x; });
  m.def("set_user_gui_is_on_right_side", [](bool x) { ps::options::userGuiIsOnRightSide = x; });
  m.def("set_build_default_gui_panels", [](bool x) { ps::options::buildDefaultGuiPanels = x; });
  m.def("set_render_scene", [](bool x) { ps::options::renderScene = x; });
  m.def("set_open_imgui_window_for_user_callback", [](bool x) { ps::options::openImGuiWindowForUserCallback= x; });
  m.def("set_invoke_user_callback_for_nested_show", [](bool x) { ps::options::invokeUserCallbackForNestedShow = x; });
  m.def("set_give_focus_on_show", [](bool x) { ps::options::giveFocusOnShow = x; });
  m.def("set_hide_window_after_show", [](bool x) { ps::options::hideWindowAfterShow = x; });
  m.def("set_warn_for_invalid_values", [](bool x) { ps::options::warnForInvalidValues = x; });
  m.def("set_display_message_popups", [](bool x) { ps::options::displayMessagePopups = x; });


  // === Scene extents
  m.def("set_automatically_compute_scene_extents", [](bool x) { ps::options::automaticallyComputeSceneExtents = x; });
  m.def("set_length_scale", [](float x) { ps::state::lengthScale = x; });
  m.def("get_length_scale", []() { return ps::state::lengthScale; });
  m.def("set_bounding_box", [](glm::vec3 low, glm::vec3 high) { ps::state::boundingBox = std::tuple<glm::vec3, glm::vec3>(low, high); });
  m.def("get_bounding_box", []() { return ps::state::boundingBox; });

  // === Camera controls & View
  m.def("set_navigation_style", [](ps::view::NavigateStyle x) { ps::view::style = x; });
  m.def("get_navigation_style", ps::view::getNavigateStyle);
  m.def("set_up_dir", [](ps::UpDir x) { ps::view::setUpDir(x); });
  m.def("get_up_dir", ps::view::getUpDir);
  m.def("set_front_dir", [](ps::FrontDir x) { ps::view::setFrontDir(x); });
  m.def("get_front_dir", ps::view::getFrontDir);
  m.def("set_vertical_fov_degrees", ps::view::setVerticalFieldOfViewDegrees);
  m.def("get_vertical_fov_degrees", ps::view::getVerticalFieldOfViewDegrees);
  m.def("get_aspect_ratio_width_over_height", ps::view::getAspectRatioWidthOverHeight);
  m.def("reset_camera_to_home_view", ps::view::resetCameraToHomeView);
  m.def("look_at", [](glm::vec3 location, glm::vec3 target, bool flyTo) { 
      ps::view::lookAt(location, target, flyTo); 
  });
  m.def("look_at_dir", [](glm::vec3 location, glm::vec3 target, glm::vec3 upDir, bool flyTo) { 
      ps::view::lookAt(location, target, upDir, flyTo); 
  });
  m.def("set_view_projection_mode", [](ps::ProjectionMode x) { ps::view::projectionMode = x; });
  m.def("get_view_camera_parameters", &ps::view::getCameraParametersForCurrentView);
  m.def("set_view_camera_parameters", &ps::view::setViewToCamera);
  m.def("set_camera_view_matrix", [](Eigen::Matrix4f mat) { ps::view::setCameraViewMatrix(eigen2glm(mat)); });
  m.def("get_camera_view_matrix", []() { return glm2eigen(ps::view::getCameraViewMatrix()); });
  m.def("set_view_center", [](glm::vec3 pos, bool flyTo) { ps::view::setViewCenter(pos, flyTo); });
  m.def("get_view_center", &ps::view::getViewCenter);
  m.def("set_window_size", &ps::view::setWindowSize);
  m.def("get_window_size", &ps::view::getWindowSize);
  m.def("get_buffer_size", &ps::view::getBufferSize);
  m.def("set_window_resizable", &ps::view::setWindowResizable);
  m.def("get_window_resizable", &ps::view::getWindowResizable);
  m.def("set_view_from_json", &ps::view::setViewFromJson);
  m.def("get_view_as_json", &ps::view::getViewAsJson);
  m.def("screen_coords_to_world_ray", &ps::view::screenCoordsToWorldRay);
  m.def("set_background_color", [](glm::vec4 c) { for(int i = 0; i < 4; i++) ps::view::bgColor[i] = c[i]; });
  m.def("get_background_color", []() { return glm2eigen(glm::vec4{
        ps::view::bgColor[0], ps::view::bgColor[1], ps::view::bgColor[2], ps::view::bgColor[3] 
      }); 
  });

  
  // === "Advanced" UI management
  m.def("build_polyscope_gui", &ps::buildPolyscopeGui);
  m.def("build_structure_gui", &ps::buildStructureGui);
  m.def("build_pick_gui", &ps::buildPickGui);
  m.def("build_user_gui_and_invoke_callback", &ps::buildUserGuiAndInvokeCallback);
  
  // === Messages
  m.def("info", overload_cast_<int, std::string>()(&ps::info), "Send an info message");
  m.def("warning", &ps::warning, "Send a warning message");
  m.def("error", &ps::error, "Send an error message");
  m.def("terminating_error", &ps::terminatingError, "Send a terminating error message");

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

  py::class_<ps::PickResult>(m, "PickResult")
   .def(py::init<>())
   .def_readonly("is_hit", &ps::PickResult::isHit)
  //  .def_readonly("structure", &ps::PickResult::structure)
   .def_readonly("structure_handle", &ps::PickResult::structureHandle)
   .def_readonly("structure_type", &ps::PickResult::structureType)
   .def_readonly("structure_name", &ps::PickResult::structureName)
   .def_readonly("quantity_name", &ps::PickResult::quantityName)
   .def_readonly("screen_coords", &ps::PickResult::screenCoords)
   .def_readonly("buffer_inds", &ps::PickResult::bufferInds)
   .def_readonly("position", &ps::PickResult::position)
   .def_readonly("depth", &ps::PickResult::depth)
   .def_readonly("local_index", &ps::PickResult::localIndex)
  ;

  // stateful selection
  m.def("have_selection", &ps::haveSelection);
  m.def("get_selection", &ps::getSelection);
  m.def("reset_selection", &ps::resetSelection);
  // inentionally no binding to set_selection(), it is low-level and not obvious how to bind

  // query what is under a pixel
  m.def("pick_at_screen_coords", &ps::pickAtScreenCoords);
  m.def("pick_at_buffer_inds", &ps::pickAtBufferInds);

  // === Ground plane and shadows
  m.def("set_ground_plane_mode", [](ps::GroundPlaneMode x) { ps::options::groundPlaneMode = x; });
  m.def("set_ground_plane_height_mode", [](ps::GroundPlaneHeightMode x) { ps::options::groundPlaneHeightMode = x; });
  m.def("set_ground_plane_height_factor", [](float x, bool isRelative) { ps::options::groundPlaneHeightFactor.set(x, isRelative); });
  m.def("set_ground_plane_height", [](float x) { ps::options::groundPlaneHeight = x; });
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
  

  // === Structure

  // (this is the generic structure class, subtypes get bound in their respective files)
  py::class_<ps::Structure>(m, "Structure")
   .def_readonly("name", &ps::Structure::name) 
  ;
  
  // === Groups
 
  py::class_<ps::Group>(m, "Group")
   .def(py::init<std::string>())
   .def_readonly("name", &ps::Group::name) 
   .def("add_child_group", &ps::Group::addChildGroup)
   .def("add_child_structure", &ps::Group::addChildStructure)
   .def("remove_child_group", &ps::Group::removeChildGroup)
   .def("remove_child_structure", &ps::Group::removeChildStructure)
   .def("set_enabled", &ps::Group::setEnabled, py::return_value_policy::reference)
   .def("set_show_child_details", &ps::Group::setShowChildDetails)
   .def("set_hide_descendants_from_structure_lists", &ps::Group::setHideDescendantsFromStructureLists)
   .def("get_child_structure_names", [](ps::Group& g) { 
        std::vector<std::string> names;
        for(ps::WeakHandle<ps::Structure>& wh : g.childrenStructures) {
            if(wh.isValid()) {
              names.push_back(wh.get().getName());
            }
        }
        return names;
    })
   .def("get_child_group_names", [](ps::Group& g) { 
        std::vector<std::string> names;
        for(ps::WeakHandle<ps::Group>& wh : g.childrenGroups) {
            if(wh.isValid()) {
              names.push_back(wh.get().name);
            }
        }
        return names;
    })
  ;

  // create/get/delete
  m.def("create_group", &ps::createGroup, py::return_value_policy::reference);
  m.def("get_group", &ps::getGroup, py::return_value_policy::reference);
  m.def("remove_group", overload_cast_<std::string, bool>()(&ps::removeGroup));
  m.def("remove_all_groups", &ps::removeAllGroups);


  // === Low-level internals access
  // (warning, 'advanced' users only, may change)
  m.def("get_final_scene_color_texture_native_handle", []() { ps::render::engine->getFinalSceneColorTexture().getNativeBufferID(); });

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
  
  // === Camera Parameters
  py::class_<ps::CameraIntrinsics>(m, "CameraIntrinsics")
   .def(py::init<>())
   .def_static("from_FoV_deg_vertical_and_aspect", &ps::CameraIntrinsics::fromFoVDegVerticalAndAspect)
   .def_static("from_FoV_deg_horizontal_and_aspect", &ps::CameraIntrinsics::fromFoVDegHorizontalAndAspect)
   .def_static("from_FoV_deg_horizontal_and_vertical", &ps::CameraIntrinsics::fromFoVDegHorizontalAndVertical)
  ;
  py::class_<ps::CameraExtrinsics>(m, "CameraExtrinsics")
   .def(py::init<>())
   .def_static("from_vectors", &ps::CameraExtrinsics::fromVectors<Eigen::Vector3f,Eigen::Vector3f,Eigen::Vector3f>)
   .def_static("from_matrix", [](Eigen::Matrix4f mat) { return ps::CameraExtrinsics::fromMatrix(eigen2glm(mat)); })
  ;
  py::class_<ps::CameraParameters>(m, "CameraParameters")
   .def(py::init<ps::CameraIntrinsics, ps::CameraExtrinsics>())
   .def("get_intrinsics", [](ps::CameraParameters& c) { return c.intrinsics; })
   .def("get_extrinsics", [](ps::CameraParameters& c) { return c.extrinsics; })
   .def("get_T", [](ps::CameraParameters& c) { return glm2eigen(c.getT()); })
   .def("get_R", [](ps::CameraParameters& c) { return glm2eigen(c.getR()); })
   .def("get_view_mat", [](ps::CameraParameters& c) { return glm2eigen(c.getViewMat()); })
   .def("get_E", [](ps::CameraParameters& c) { return glm2eigen(c.getE()); })
   .def("get_position", [](ps::CameraParameters& c) { return glm2eigen(c.getPosition()); })
   .def("get_look_dir", [](ps::CameraParameters& c) { return glm2eigen(c.getLookDir()); })
   .def("get_up_dir", [](ps::CameraParameters& c) { return glm2eigen(c.getUpDir()); })
   .def("get_right_dir", [](ps::CameraParameters& c) { return glm2eigen(c.getRightDir()); })
   .def("get_camera_frame", [](ps::CameraParameters& c) { 
       return std::make_tuple(glm2eigen(c.getLookDir()), glm2eigen(c.getUpDir()), glm2eigen(c.getRightDir()));
    })
   .def("get_fov_vertical_deg", &ps::CameraParameters::getFoVVerticalDegrees)
   .def("get_aspect", &ps::CameraParameters::getAspectRatioWidthOverHeight)
   .def("generate_camera_rays", [](ps::CameraParameters& c, size_t dimX, size_t dimY, ps::ImageOrigin origin) { 
        std::vector<glm::vec3> rays = c.generateCameraRays(dimX, dimY, origin);
        Eigen::MatrixXf raysOut(rays.size(), 3);
        for(size_t i = 0; i < rays.size(); i++) {
          raysOut(i,0) = rays[i].x;
          raysOut(i,1) = rays[i].y;
          raysOut(i,2) = rays[i].z;
        }
       return raysOut;
     })
   .def("generate_camera_ray_corners", [](ps::CameraParameters& c) { 
        std::array<glm::vec3,4> rays = c.generateCameraRayCorners();
        Eigen::MatrixXf raysOut(4, 3);
        for(size_t i = 0; i < rays.size(); i++) {
          raysOut(i,0) = rays[i].x;
          raysOut(i,1) = rays[i].y;
          raysOut(i,2) = rays[i].z;
        }
       return raysOut;
     })
  ;
  
  // === Weak Handles
  // (used for lifetime tracking tricks)
  py::class_<ps::GenericWeakHandle>(m, "GenericWeakHandle")
   .def(py::init<>())
   .def("is_valid", &ps::GenericWeakHandle::isValid)
   .def("get_unique_ID", &ps::GenericWeakHandle::getUniqueID)
  ;

  // === Enums
  
  py::enum_<ps::view::NavigateStyle>(m, "NavigateStyle")
    .value("turntable", ps::view::NavigateStyle::Turntable)
    .value("free", ps::view::NavigateStyle::Free)
    .value("planar", ps::view::NavigateStyle::Planar)
    .value("arcball", ps::view::NavigateStyle::Arcball)
    .value("none", ps::view::NavigateStyle::None)
    .value("first_person", ps::view::NavigateStyle::FirstPerson)
    ; 
  
  py::enum_<ps::ProjectionMode>(m, "ProjectionMode")
    .value("perspective", ps::ProjectionMode::Perspective)
    .value("orthographic", ps::ProjectionMode::Orthographic)
    ; 
  
  py::enum_<ps::UpDir>(m, "UpDir")
    .value("x_up", ps::UpDir::XUp)
    .value("y_up", ps::UpDir::YUp)
    .value("z_up", ps::UpDir::ZUp)
    .value("neg_x_up", ps::UpDir::NegXUp)
    .value("neg_y_up", ps::UpDir::NegYUp)
    .value("neg_z_up", ps::UpDir::NegZUp)
    ; 
  
  py::enum_<ps::FrontDir>(m, "FrontDir")
    .value("x_front", ps::FrontDir::XFront)
    .value("y_front", ps::FrontDir::YFront)
    .value("z_front", ps::FrontDir::ZFront)
    .value("neg_x_front", ps::FrontDir::NegXFront)
    .value("neg_y_front", ps::FrontDir::NegYFront)
    .value("neg_z_front", ps::FrontDir::NegZFront)
    ; 

  py::enum_<ps::DataType>(m, "DataType")
    .value("standard", ps::DataType::STANDARD)
    .value("symmetric", ps::DataType::SYMMETRIC)
    .value("magnitude", ps::DataType::MAGNITUDE)
    .value("categorical", ps::DataType::CATEGORICAL)
    ; 

  py::enum_<ps::VectorType>(m, "VectorType")
    .value("standard", ps::VectorType::STANDARD)
    .value("ambient", ps::VectorType::AMBIENT)
    ; 
  
  py::enum_<ps::ParamCoordsType>(m, "ParamCoordsType")
    .value("unit", ps::ParamCoordsType::UNIT)
    .value("world", ps::ParamCoordsType::WORLD)
    ; 
  
  py::enum_<ps::ParamVizStyle>(m, "ParamVizStyle")
    .value("checker", ps::ParamVizStyle::CHECKER)
    .value("checker_islands", ps::ParamVizStyle::CHECKER_ISLANDS)
    .value("grid", ps::ParamVizStyle::GRID)
    .value("local_check", ps::ParamVizStyle::LOCAL_CHECK)
    .value("local_rad", ps::ParamVizStyle::LOCAL_RAD)
    ; 

  py::enum_<ps::BackFacePolicy>(m, "BackFacePolicy")
    .value("identical", ps::BackFacePolicy::Identical)
    .value("different", ps::BackFacePolicy::Different)
    .value("custom", ps::BackFacePolicy::Custom)
    .value("cull", ps::BackFacePolicy::Cull)
    ; 
  
  py::enum_<ps::LimitFPSMode>(m, "LimitFPSMode")
    .value("ignore_limits", ps::LimitFPSMode::IgnoreLimits)
    .value("block_to_hit_target", ps::LimitFPSMode::BlockToHitTarget)
    .value("skip_frames_to_hit_target", ps::LimitFPSMode::SkipFramesToHitTarget)
    ; 
  
  py::enum_<ps::GroundPlaneMode>(m, "GroundPlaneMode")
    .value("none", ps::GroundPlaneMode::None)
    .value("tile", ps::GroundPlaneMode::Tile)
    .value("tile_reflection", ps::GroundPlaneMode::TileReflection)
    .value("shadow_only", ps::GroundPlaneMode::ShadowOnly)
    ; 
  
  py::enum_<ps::GroundPlaneHeightMode>(m, "GroundPlaneHeightMode")
    .value("automatic", ps::GroundPlaneHeightMode::Automatic)
    .value("manual", ps::GroundPlaneHeightMode::Manual)
    ; 
  
  py::enum_<ps::TransparencyMode>(m, "TransparencyMode")
    .value("none", ps::TransparencyMode::None)
    .value("simple", ps::TransparencyMode::Simple)
    .value("pretty", ps::TransparencyMode::Pretty)
    ; 
    
    py::enum_<ps::CurveNetworkElement>(m, "CurveNetworkElement")
    .value("node", ps::CurveNetworkElement::NODE)
    .value("edge", ps::CurveNetworkElement::EDGE)
    ;

    py::enum_<ps::MeshElement>(m, "MeshElement")
    .value("vertex", ps::MeshElement::VERTEX)
    .value("face", ps::MeshElement::FACE)
    .value("edge", ps::MeshElement::EDGE)
    .value("halfedge", ps::MeshElement::HALFEDGE)
    .value("corner", ps::MeshElement::CORNER)
    ; 

  py::enum_<ps::MeshSelectionMode>(m, "MeshSelectionMode")
    .value("auto", ps::MeshSelectionMode::Auto)
    .value("vertices_only", ps::MeshSelectionMode::VerticesOnly)
    .value("faces_only", ps::MeshSelectionMode::FacesOnly)
    ; 

    py::enum_<ps::VolumeMeshElement>(m, "VolumeMeshElement")
    .value("vertex", ps::VolumeMeshElement::VERTEX)
    .value("edge", ps::VolumeMeshElement::EDGE)
    .value("face", ps::VolumeMeshElement::FACE)
    .value("cell", ps::VolumeMeshElement::CELL)
    ; 
    
    py::enum_<ps::VolumeGridElement>(m, "VolumeGridElement")
    .value("node", ps::VolumeGridElement::NODE)
    .value("cell", ps::VolumeGridElement::CELL)
    ; 
  
  py::enum_<ps::PointRenderMode>(m, "PointRenderMode")
    .value("sphere", ps::PointRenderMode::Sphere)
    .value("quad", ps::PointRenderMode::Quad)
    ; 
  
  py::enum_<ps::FilterMode>(m, "FilterMode")
    .value("linear", ps::FilterMode::Linear)
    .value("nearest", ps::FilterMode::Nearest)
    ; 
  
  py::enum_<ps::ImageOrigin>(m, "ImageOrigin")
    .value("lower_left", ps::ImageOrigin::LowerLeft)
    .value("upper_left", ps::ImageOrigin::UpperLeft)
    ; 
  
  py::enum_<ps::MeshShadeStyle>(m, "MeshShadeStyle")
    .value("smooth", ps::MeshShadeStyle::Smooth)
    .value("flat", ps::MeshShadeStyle::Flat)
    .value("tri_flat", ps::MeshShadeStyle::TriFlat)
    ; 
  
  py::enum_<ps::IsolineStyle>(m, "IsolineStyle")
    .value("stripe", ps::IsolineStyle::Stripe)
    .value("contour", ps::IsolineStyle::Contour)
    ; 
  
  py::enum_<ps::ImplicitRenderMode>(m, "ImplicitRenderMode")
    .value("sphere_march", ps::ImplicitRenderMode::SphereMarch)
    .value("fixed_step", ps::ImplicitRenderMode::FixedStep)
    ; 
  
  py::enum_<ps::ManagedBufferType>(m, "ManagedBufferType")
    .value(ps::typeName(ps::ManagedBufferType::Float   ).c_str(),   ps::ManagedBufferType::Float   )
    .value(ps::typeName(ps::ManagedBufferType::Double  ).c_str(),   ps::ManagedBufferType::Double  )
    .value(ps::typeName(ps::ManagedBufferType::Vec2    ).c_str(),   ps::ManagedBufferType::Vec2    )
    .value(ps::typeName(ps::ManagedBufferType::Vec3    ).c_str(),   ps::ManagedBufferType::Vec3    )
    .value(ps::typeName(ps::ManagedBufferType::Vec4    ).c_str(),   ps::ManagedBufferType::Vec4    )
    .value(ps::typeName(ps::ManagedBufferType::Arr2Vec3).c_str(),   ps::ManagedBufferType::Arr2Vec3)
    .value(ps::typeName(ps::ManagedBufferType::Arr3Vec3).c_str(),   ps::ManagedBufferType::Arr3Vec3)
    .value(ps::typeName(ps::ManagedBufferType::Arr4Vec3).c_str(),   ps::ManagedBufferType::Arr4Vec3)
    .value(ps::typeName(ps::ManagedBufferType::UInt32  ).c_str(),   ps::ManagedBufferType::UInt32  )
    .value(ps::typeName(ps::ManagedBufferType::Int32   ).c_str(),   ps::ManagedBufferType::Int32   )
    .value(ps::typeName(ps::ManagedBufferType::UVec2   ).c_str(),   ps::ManagedBufferType::UVec2   )
    .value(ps::typeName(ps::ManagedBufferType::UVec3   ).c_str(),   ps::ManagedBufferType::UVec3   )
    .value(ps::typeName(ps::ManagedBufferType::UVec4   ).c_str(),   ps::ManagedBufferType::UVec4   )
    ; 
  
  py::enum_<ps::DeviceBufferType>(m, "DeviceBufferType")
    .value("attribute", ps::DeviceBufferType::Attribute)
    .value("texture1d", ps::DeviceBufferType::Texture1d)
    .value("texture2d", ps::DeviceBufferType::Texture2d)
    .value("texture3d", ps::DeviceBufferType::Texture3d)
    ; 

  // === Mini bindings for a little bit of glm
  py::class_<glm::vec2>(m, "glm_vec2").
    def(py::init<float, float>())
   .def("as_tuple",
        [](const glm::vec2& x) {
        return std::tuple<float, float>(x[0], x[1]);
        });

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
  
  py::class_<glm::ivec2>(m, "glm_ivec2").
    def(py::init<int32_t, int32_t>())
   .def("as_tuple",
        [](const glm::ivec2& x) {
        return std::tuple<int32_t, int32_t>(x[0], x[1]); 
        });

  py::class_<glm::uvec3>(m, "glm_uvec3").
    def(py::init<uint32_t, uint32_t, uint32_t>())
   .def("as_tuple",
        [](const glm::uvec3& x) {
        return std::tuple<uint32_t, uint32_t, uint32_t>(x[0], x[1], x[2]); 
        });


  // === Bind structures defined in other files
  bind_floating_quantities(m);
  bind_implicit_helpers(m);
  bind_point_cloud(m);
  bind_curve_network(m);
  bind_surface_mesh(m);
  bind_volume_mesh(m);
  bind_volume_grid(m);
  bind_camera_view(m);
  bind_managed_buffer(m);
  bind_imgui(m);
  bind_implot(m);

}

// clang-format on
