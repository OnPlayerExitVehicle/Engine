#include "PlaneCollider.h"

void PlaneCollider::Awake()
{
	collider = new btStaticPlaneShape(btVector3(.0f, 1.0f, .0f), .0f);
}