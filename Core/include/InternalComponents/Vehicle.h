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
    enum class VehicleWheel
    {
        FrontLeft,
        FrontRight,
        RearLeft,
        RearRight,
        SIZE
    };

    struct WheelInfo
    {
        btWheelInfo* wheelInfo = nullptr;
        std::shared_ptr<Transform> transform = nullptr;
    };

	btRaycastVehicle* vehicle = nullptr;
    WheelInfo wheelInfos[static_cast<int>(VehicleWheel::SIZE)]{nullptr};
};
