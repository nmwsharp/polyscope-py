// Copyright 2017-2023, Nicholas Sharp and the Polyscope contributors. https://polyscope.run

#pragma once

#include "polyscope/affine_remapper.h"
#include "polyscope/color_management.h"
#include "polyscope/persistent_value.h"
#include "polyscope/pick.h"
#include "polyscope/polyscope.h"
#include "polyscope/render/engine.h"
#include "polyscope/render/managed_buffer.h"
#include "polyscope/scaled_value.h"
#include "polyscope/standardize_data_array.h"
#include "polyscope/structure.h"

namespace polyscope {

// Forward declare gaussian particles
class GaussianParticles;

// Forward declare quantity types
// class GaussianParticlesScalarQuantity;


struct GaussianParticlesPickResult {
  int64_t index;
};

class GaussianParticles : public Structure {
public:
  // === Member functions ===

  // Construct a new structure
  GaussianParticles(std::string name, std::function<void()>& drawCallback, std::function<void()>& extentsCallback,
                    std::function<void()>& deletionCallback);
  virtual ~GaussianParticles();

  // === Overrides

  // Build the imgui display
  virtual void buildCustomUI() override;
  virtual void buildCustomOptionsUI() override;
  virtual void buildPickUI(const PickResult& result) override;

  // Standard structure overrides
  virtual void draw() override;
  virtual void drawDelayed() override;
  virtual void drawPick() override;
  virtual void drawPickDelayed() override;
  virtual void updateObjectSpaceBounds() override;
  virtual std::string typeName() override;
  virtual void refresh() override;

  // Misc data
  static const std::string structureTypeName;
  std::tuple<int32_t, int32_t> getRenderDims();

  int32_t getSubsampleFactor();
  void setSubsampleFactor(int32_t newVal);

  // Manually set the extents of the structure (note: does _not_ automatically update the scene, call refresh() after if
  // you need that.)
  void setExtents(glm::vec3 bbox_min, glm::vec3 bbox_max);


private:
  std::function<void()> drawCallback;
  std::function<void()> extentsCallback;
  std::function<void()> deletionCallback;

  int32_t currImageWidth = -1;
  int32_t currImageHeight = -1;
  int32_t subsampleFactor = 1;

  // === Render data
  std::vector<float> depthsData;
  std::unique_ptr<render::ManagedBuffer<float>> depths;
  std::vector<glm::vec4> colorsData;
  std::unique_ptr<render::ManagedBuffer<glm::vec4>> colors;
  std::shared_ptr<render::ShaderProgram> imageToScreenProgram;


  // === Helpers
  void ensureImagebuffersAllocated();
  void setImageToScreenUniforms();
  void prepareImageToScreenProgram();
};

// Shorthand to add a gaussian particles to polyscope
GaussianParticles* registerGaussianParticles(std::string name, std::function<void()>& drawCallback,
                                             std::function<void()>& extentsCallback,
                                             std::function<void()>& deletionCallback);

// Shorthand to get a gaussian particles from polyscope
inline GaussianParticles* getGaussianParticles(std::string name = "");
inline bool hasGaussianParticles(std::string name = "");
inline void removeGaussianParticles(std::string name = "", bool errorIfAbsent = false);


} // namespace polyscope


// implementations of the inline funcitons
// (this setup is silly from a C++ standpoint, we do it to match other structures)

namespace polyscope {

inline GaussianParticles* registerGaussianParticles(std::string name, std::function<void()>& drawCallback,
                                                    std::function<void()>& extentsCallback,
                                                    std::function<void()>& deletionCallback) {

  checkInitialized();

  GaussianParticles* s = new GaussianParticles(name, drawCallback, extentsCallback, deletionCallback);
  bool success = registerStructure(s);
  if (!success) {
    safeDelete(s);
  }
  return s;
}


// Shorthand to get a gaussian particles from polyscope
inline GaussianParticles* getGaussianParticles(std::string name) {
  return dynamic_cast<GaussianParticles*>(getStructure(GaussianParticles::structureTypeName, name));
}
inline bool hasGaussianParticles(std::string name) { return hasStructure(GaussianParticles::structureTypeName, name); }
inline void removeGaussianParticles(std::string name, bool errorIfAbsent) {
  removeStructure(GaussianParticles::structureTypeName, name, errorIfAbsent);
}

} // namespace polyscope