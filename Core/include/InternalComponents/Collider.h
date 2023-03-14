#pragma once
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include "Component.h"

class Collider : public Component
{
protected:
	btCollisionShape* collider;

public:
	btCollisionShape* GetBulletCollider();
	std::string GetName() override { return typeid(*this).name(); }
};