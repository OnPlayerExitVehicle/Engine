#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
protected:
	void Awake() override;

public:
	std::string GetName() override { return typeid(*this).name(); }
};