#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
protected:
	void Awake() override;
public:
	std::string GetName() override { return typeid(*this).name(); }
};