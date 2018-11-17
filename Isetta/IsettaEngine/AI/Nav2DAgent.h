/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Core/Math/Vector2.h"
#include "Nav2DPlane.h"

namespace Isetta {
class Nav2DAgent {
  Math::Vector2 velocity;
  Math::Vector2 linear;
  Nav2DPlane* navPlane;

  void UpdateSteeringData(Math::Vector2 position, float distance);

  float maxAcceleration = 2;
  float maxVelocity = 2;
  float timeToTarget = 0.1f;
  float stopDistance = 0.5f;
  float maxAcceleration2 = 4;
  float maxVelocity2 = 4;
  Math::Vector2 GetAIMovement(float deltaTime);

 public:
  explicit Nav2DAgent(Nav2DPlane* plane, float maxAcc = 2.f, float maxV = 2.f, float timeToTarget = 0.1f, float arriving = 0.5f);
  Math::Vector2 GetAIMovement(Math::Vector2 agentPosition,
                              float deltaTime);
};
}  // namespace Isetta
