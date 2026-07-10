#include "Collider.h"

btCollisionShape* Collider::GetBulletCollider() const noexcept
{
	return collider;
}

Vector3 Collider::GetLocalScaling() const noexcept
{
	return collider->getLocalScaling();
}

void Collider::SetLocalScaling(const Vector3& scaling) noexcept
{
	collider->setLocalScaling(scaling);
}