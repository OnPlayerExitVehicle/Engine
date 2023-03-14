#pragma once
#include "Component.h"

class TestComponent : public Component
{
public:
	bool isCamera;
private:
	void Awake() override;
	void Update(float deltaTime) override;

public:
	std::string GetName() override { return typeid(*this).name(); }
};