#pragma once
#include "Bullet/src/btBulletDynamicsCommon.h"
#include "Component.h"

class Collider : public Component
{
protected:
	btCollisionShape* collider;

public:
	btCollisionShape* GetBulletCollider();
	std::string GetName() override { return typeid(*this).name(); }
};