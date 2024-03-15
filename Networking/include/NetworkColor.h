#pragma once

#include "NetworkComponent.h"
#include "MeshRenderer.h"

class NetworkColor : public NetworkComponent
{
private:
	std::shared_ptr<MeshRenderer> meshRenderer;
	float r = .0f, g = .0f, b = .0f;
	float minimumChange = 0.01f;

protected:
	void Awake() override;
	void NetworkUpdate(float networkDeltaTime) override;
	void OnNetworkMessage(networking::message&& msg) override;

	std::string GetName() override { return typeid(*this).name(); }
};