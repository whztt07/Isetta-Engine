/*
 * Copyright (c) 2018 Isetta
 */
#include "Graphics/CameraComponent.h"
#include <utility>
#include "Core/Debug/Assert.h"
#include "Graphics/RenderModule.h"
#include "Scene/Component.h"
#include "Scene/Entity.h"
#include "Scene/Transform.h"
#include "Util.h"

namespace Isetta {
RenderModule* CameraComponent::renderModule{nullptr};
CameraComponent* CameraComponent::_main{nullptr};

CameraComponent::CameraComponent(std::string cameraName)
    : name{std::move(cameraName)}, renderNode(NULL), renderResource(NULL) {
  ASSERT(renderModule != nullptr);
  renderModule->cameraComponents.push_back(this);
  if (!_main) {
    _main = this;
  }
}

void CameraComponent::OnEnable() {
  ASSERT(renderModule != nullptr);
  renderNode =
      h3dAddCameraNode(H3DRootNode, name.c_str(), renderModule->pipelineRes);
  h3dSetNodeParamI(renderNode, H3DCamera::OccCullingI, 1);
  ResizeViewport();
}

void CameraComponent::OnDisable() { h3dRemoveNode(renderNode); }
void CameraComponent::UpdateH3DTransform() const {
  Transform::SetH3DNodeTransform(renderNode, GetTransform());
}

void CameraComponent::ResizeViewport() const {
  int width, height;
  ASSERT(renderModule != nullptr);
  ASSERT(renderModule->winHandle != nullptr);
  glfwGetWindowSize(renderModule->winHandle, &width, &height);
  h3dSetNodeParamI(renderNode, H3DCamera::ViewportXI, 0);
  h3dSetNodeParamI(renderNode, H3DCamera::ViewportYI, 0);
  h3dSetNodeParamI(renderNode, H3DCamera::ViewportWidthI, width);
  h3dSetNodeParamI(renderNode, H3DCamera::ViewportHeightI, height);
  h3dResizePipelineBuffers(renderModule->pipelineRes, width, height);
}

void CameraComponent::SetupCameraViewport() const {
  int width, height;
  ASSERT(renderModule != nullptr);
  ASSERT(renderModule->winHandle != nullptr);
  glfwGetWindowSize(renderModule->winHandle, &width, &height);
  h3dSetupCameraView(renderNode, fov, static_cast<float>(width) / height,
                     nearPlane, farPlane);
}
}  // namespace Isetta
