#pragma once
#include "GameObject.h"

class Vehicle : public Component
{
public:
	void Awake() override;
	void BeforeFixedUpdate() override;
	void FixedUpdate(float fixedDeltaTime) override;
	void OnGUI() override;
	const btRaycastVehicle* GetNativeVehiclePtr() const noexcept;
	std::string GetName() override { return typeid(*this).name(); }

private:
	btRaycastVehicle* vehicle = nullptr;
};