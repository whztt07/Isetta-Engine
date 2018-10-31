/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <vector>
#include "Scene/Component.h"

namespace Isetta {
BEGIN_COMPONENT(DebugCollision, Component, true)
private:
int collisions = 0;
int enterHandle, exitHandle;
std::vector<class Collider*> colliders;
class CollisionHandler* handler;

public:
void OnEnable() override;
void OnDisable() override;
void OnCollisionEnter(class Collider* const other);
void OnCollisionExit(class Collider* const other);
END_COMPONENT(DebugCollision, Component)
}  // namespace Isetta