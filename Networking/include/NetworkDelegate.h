#pragma once

#include "NetworkComponent.h"
#include "NetworkClient.h"
#include <map>

class NetworkClient;

class NetworkDelegate : public Component
{
private:
	std::map<GameMessage, std::shared_ptr<NetworkComponent>> networkComponentMap;
	NetworkClient* networkClient;
	uint32_t uid;
	bool isMine;

protected:
	void Awake() override;

public:
	explicit NetworkDelegate(NetworkClient* client, uint32_t uid, bool local);
	void RegisterNetworkComponent(const std::shared_ptr<NetworkComponent>& component, GameMessage messageType);
	bool IsMine() const;

	void SendNetworkMessage(olc::net::message<GameMessage>& msg);

	void OnNetworkMessage(olc::net::message<GameMessage>& msg);

	void ProcessNetworkUpdate(float networkDeltaTime);

	std::string GetName() override { return typeid(*this).name(); }
};