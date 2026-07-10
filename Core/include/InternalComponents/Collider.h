#pragma once
#include "Bullet/src/btBulletDynamicsCommon.h"
#include "Component.h"

class Collider : public Component
{
protected:
	btCollisionShape* collider;

public:
	btCollisionShape* GetBulletCollider() const noexcept;
	Vector3 GetLocalScaling() const noexcept;
	void SetLocalScaling(const Vector3& scaling) noexcept;
	std::string GetName() override { return typeid(*this).name(); }
};