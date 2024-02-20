#pragma once

#include "Component.h"

class MyComponent : public Component
{
	void Awake() override;
	void Update(float deltaTime) override;
	void OnGUI() override;
	std::string GetName() override { return typeid(*this).name(); }
};