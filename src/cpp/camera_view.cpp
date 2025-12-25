#include "Eigen/Dense"

#include "polyscope/camera_view.h"
#include "polyscope/polyscope.h"

#include "utils.h"

// clang-format off
void bind_camera_view(nb::module_& m) {

  // == Helper quantity classes

  // == Main class
  bindStructure<ps::CameraView>(m, "CameraView")

    // basics
    .def("get_camera_parameters", &ps::CameraView::getCameraParameters, "Get camera parameters")
    .def("update_camera_parameters", &ps::CameraView::updateCameraParameters, "Update camera parameters")

    // options
    .def("set_widget_color", &ps::CameraView::setWidgetColor, "Set color")
    .def("get_widget_color", &ps::CameraView::getWidgetColor, "Get color")
    .def("set_widget_thickness", &ps::CameraView::setWidgetThickness, "Set widget thickness")
    .def("get_widget_thickness", &ps::CameraView::getWidgetThickness, "Get widget thickness")
    .def("set_widget_focal_length", &ps::CameraView::setWidgetFocalLength, "Set widget focal length")
    .def("get_widget_focal_length", &ps::CameraView::getWidgetFocalLength, "Get widget focal length")

    // camera controls
    .def("set_view_to_this_camera", &ps::CameraView::setViewToThisCamera, "Set view to this camera")
  ;


  // Static adders and getters
  m.def("register_camera_view", &ps::registerCameraView,
      nb::arg("name"), nb::arg("parameters"), "Register a camera view", nb::rv_policy::reference);
  m.def("remove_camera_view", &ps::removeCameraView, "Remove a camera view by name");
  m.def("get_camera_view", &ps::getCameraView, "Get a camera view by name", nb::rv_policy::reference);
  m.def("has_camera_view", &ps::hasCameraView, "Check for a camera view by name");

}
// clang-format on
