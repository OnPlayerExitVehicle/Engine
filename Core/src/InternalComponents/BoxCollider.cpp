#include "BoxCollider.h"

void BoxCollider::Awake()
{
	auto transform = GetTransform();
	collider = new btBoxShape(btVector3(transform->scale.x / 2, transform->scale.y / 2, transform->scale.z / 2));
}