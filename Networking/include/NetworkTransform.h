#pragma once

#include "NetworkComponent.h"

class NetworkTransform : public NetworkComponent
{
private:
	std::shared_ptr<Transform> transform;
	float x = .0f, y = .0f, z = .0f;
	float minimumMove = 0.01f;

protected:
	virtual void Awake() override;
	virtual void NetworkUpdate(float networkDeltaTime) override;
	virtual void OnNetworkMessage(olc::net::message<GameMessage>& msg) override;

	std::string GetName() override { return typeid(*this).name(); }
};