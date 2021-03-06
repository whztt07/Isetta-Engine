/*
 * Copyright (c) 2018 Isetta
 */
#include "AI/Nav2DAgent.h"

namespace Isetta {
Math::Vector2 Nav2DAgent::GetAIMovement(Math::Vector2 agentPosition,
                                        float deltaTime) {
  float distance = navPlane->GetDistanceToTarget(agentPosition);

  UpdateSteeringData(agentPosition, distance);
  Math::Vector2 velocity;
  if (distance < stopDistance) {
    velocity = Math::Vector2::zero;
  } else {
    velocity = GetAIMovement(deltaTime);
  }

  return velocity;
}

Math::Vector2 Nav2DAgent::GetAIMovement(float deltaTime) {
  velocity += linear * deltaTime;
  if (velocity.SqrMagnitude() > maxVelocity2) {
    velocity.Normalize();
    velocity *= maxVelocity;
  }
  return velocity;
}

Nav2DAgent::Nav2DAgent(Nav2DPlane* plane, float maxAcc, float maxV,
                       float timeToTarget, float arriving)
    : navPlane{plane},
      maxAcceleration{maxAcc},
      maxVelocity{maxV},
      timeToTarget{timeToTarget},
      stopDistance{arriving},
      maxAcceleration2{maxAcc * maxAcc},
      maxVelocity2{maxV * maxV} {}

void Nav2DAgent::UpdateSteeringData(Math::Vector2 position, float distance) {
  float targetSpeed;
  if (distance > stopDistance * 2) {
    targetSpeed = maxVelocity;
  } else {
    targetSpeed = maxVelocity * distance / (stopDistance * 2);
  }
  Math::Vector2 targetVelocity =
      navPlane->GetDirectionByPosition(position) * targetSpeed;
  linear = targetVelocity - velocity;
  linear /= timeToTarget;
  if (linear.SqrMagnitude() > maxAcceleration2) {
    linear.Normalize();
    linear *= maxAcceleration;
  }
}
}  // namespace Isetta
