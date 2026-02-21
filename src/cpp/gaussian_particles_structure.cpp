// Copyright 2017-2023, Nicholas Sharp and the Polyscope contributors. https://polyscope.run

#include "gaussian_particles_structure.h"

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

// Initialize statics
const std::string GaussianParticles::structureTypeName = "Gaussian Particles";

GaussianParticles::GaussianParticles(std::string name_, std::function<void()>& drawCallback_,
                                     std::function<void()>& extentsCallback_, std::function<void()>& deletionCallback_)
    : Structure(name_, structureTypeName), drawCallback(drawCallback_), extentsCallback(extentsCallback_),
      deletionCallback(deletionCallback_) {

  // note: unlike other structures this does not call updateObjectSpaceBounds() here, to avoid a circular problem with
  // the external class. we call it manually right after creation there.
}

GaussianParticles::~GaussianParticles() { deletionCallback(); }

void GaussianParticles::buildCustomUI() {
  ensureImagebuffersAllocated(); // doing this here ensures we re-render after resizing

  ImGui::Text("# particles: -1");
}
void GaussianParticles::buildCustomOptionsUI() {}
void GaussianParticles::buildPickUI(const PickResult& result) {}

// Standard structure overrides
void GaussianParticles::draw() {}
void GaussianParticles::drawDelayed() {
  if (!isEnabled()) return;


  ensureImagebuffersAllocated();

  drawCallback();

  if (!imageToScreenProgram) {
    prepareImageToScreenProgram();
  }
  setImageToScreenUniforms();
  imageToScreenProgram->draw();
}

void GaussianParticles::drawPick() {}
void GaussianParticles::drawPickDelayed() {}
void GaussianParticles::updateObjectSpaceBounds() { extentsCallback(); }

void GaussianParticles::setExtents(glm::vec3 bbox_min, glm::vec3 bbox_max) {
  std::get<0>(objectSpaceBoundingBox) = bbox_min;
  std::get<1>(objectSpaceBoundingBox) = bbox_max;
  objectSpaceLengthScale = glm::length(bbox_max - bbox_min);
  requestRedraw();
}

std::string GaussianParticles::typeName() { return structureTypeName; }
void GaussianParticles::refresh() {}

std::tuple<int32_t, int32_t> GaussianParticles::getRenderDims() {
  ensureImagebuffersAllocated();
  return std::make_tuple(currImageWidth, currImageHeight);
}

void GaussianParticles::ensureImagebuffersAllocated() {
  int32_t newImageWidth = view::bufferWidth / subsampleFactor;
  int32_t newImageHeight = view::bufferHeight / subsampleFactor;

  if (newImageHeight == currImageHeight && newImageWidth == currImageWidth) {
    return;
  }

  currImageHeight = newImageHeight;
  currImageWidth = newImageWidth;

  depths.reset();
  colors.reset();
  depths = std::make_unique<render::ManagedBuffer<float>>(this, uniquePrefix() + "depths", depthsData);
  colors = std::make_unique<render::ManagedBuffer<glm::vec4>>(this, uniquePrefix() + "colors", colorsData);

  // re-allocate buffers
  depths->setTextureSize(currImageWidth, currImageHeight);
  depths->ensureHostBufferAllocated();
  depths->data = std::vector<float>(currImageWidth * currImageHeight, 0.0f);
  depths->markHostBufferUpdated();

  colors->setTextureSize(currImageWidth, currImageHeight);
  colors->ensureHostBufferAllocated();
  colors->data = std::vector<glm::vec4>(currImageWidth * currImageHeight, glm::vec4(0.0f));
  colors->markHostBufferUpdated();

  requestRedraw();
}

void GaussianParticles::setImageToScreenUniforms() {
  setStructureUniforms(*imageToScreenProgram);

  glm::mat4 P = view::getCameraPerspectiveMatrix();
  glm::mat4 Pinv = glm::inverse(P);

  imageToScreenProgram->setUniform("u_projMatrix", glm::value_ptr(P));
  imageToScreenProgram->setUniform("u_invProjMatrix", glm::value_ptr(Pinv));
  imageToScreenProgram->setUniform("u_viewport", render::engine->getCurrentViewport());
  imageToScreenProgram->setUniform("u_textureTransparency", transparency.get());
  render::engine->setTonemapUniforms(*imageToScreenProgram);
  if (imageToScreenProgram->hasUniform("u_transparency")) {
    imageToScreenProgram->setUniform("u_transparency", 1.0f);
  }
}

void GaussianParticles::prepareImageToScreenProgram() {

  // NOTE: we use INVERSE_TONEMAP to avoid tonemapping the content, but in the presence of transparency this setup
  // cannot exactly preserve the result, since the inversion is applied before compositing but finaltonemapping is
  // applied after compositing.

  // Create the sourceProgram
  // clang-format off
  std::vector<std::string> rules = addStructureRules({
    getImageOriginRule(ImageOrigin::UpperLeft),
    "TEXTURE_SHADE_COLORALPHA", "INVERSE_TONEMAP"
  });
  rules = removeRule(rules, "GENERATE_VIEW_POS");

  imageToScreenProgram = render::engine->requestShader("TEXTURE_DRAW_RAW_RENDERIMAGE_PLAIN", rules);
  // clang-format on

  imageToScreenProgram->setAttribute("a_position", render::engine->screenTrianglesCoords());
  imageToScreenProgram->setTextureFromBuffer("t_depth", depths->getRenderTextureBuffer().get());
  imageToScreenProgram->setTextureFromBuffer("t_color", colors->getRenderTextureBuffer().get());
}

} // namespace polyscope
