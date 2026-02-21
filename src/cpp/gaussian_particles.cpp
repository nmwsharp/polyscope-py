#include "utils.h"

#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h>

#include "gaussian_particles_structure.h"

// === Bindings

// clang-format off
void bind_gaussian_particles(nb::module_& m) {

  // == Helper classes
  nb::class_<ps::GaussianParticlesPickResult>(m, "GaussianParticlesPickResult")
   .def(nb::init<>())
   .def_ro("index", &ps::GaussianParticlesPickResult::index)
  ;

  // == Main class
  bindStructure<ps::GaussianParticles>(m, "GaussianParticles")

    // basics

    // options

    // picking
        
    // quantities
    
    
    // internal
    .def("get_render_dims", &ps::GaussianParticles::getRenderDims)
    .def("set_extents", &ps::GaussianParticles::setExtents)
    .def("update_object_space_bounds", &ps::GaussianParticles::updateObjectSpaceBounds)

    ;

  // Static adders and getters
  m.def("register_gaussian_particles", &ps::registerGaussianParticles, 
      nb::arg("name"), nb::arg("draw_func"), nb::arg("extents_callback"), nb::arg("deletion_callback"), "Register gaussian particles", 
      nb::rv_policy::reference);
  m.def("remove_gaussian_particles", &polyscope::removeGaussianParticles, "Remove gaussian particles by name");
  m.def("get_gaussian_particles", &polyscope::getGaussianParticles, "Get gaussian particles by name", nb::rv_policy::reference);
  m.def("has_gaussian_particles", &polyscope::hasGaussianParticles, "Check for gaussian particles by name");

}
// clang-format on