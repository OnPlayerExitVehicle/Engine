#pragma once

#include "NetworkComponent.h"

class NetworkTransform : public NetworkComponent
{
private:
	std::shared_ptr<Transform> transform;
	float x = .0f, y = .0f, z = .0f;
    float rotX = .0f, rotY = .0f, rotZ = .0f, rotW = .0f;
	const static float positionChangeMargin;
    const static float rotationChangeMargin;

protected:
	virtual void Awake() override;
	virtual void NetworkUpdate(float networkDeltaTime) override;
	virtual void OnNetworkMessage(networking::message&& msg) override;

	std::string GetName() override { return typeid(*this).name(); }
};