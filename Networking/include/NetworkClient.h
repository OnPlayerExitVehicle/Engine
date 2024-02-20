#pragma once

#include "olc_net.h"
#include "NetworkDelegate.h"
#include <map>

class Scene;

class NetworkClient : public networking::client_interface<GameMessage>
{
private:
	Scene* scene;
	std::thread networkLoopThread;
	std::map<uint32_t, std::shared_ptr<NetworkDelegate>> networkObjectMap;
	std::vector<uint32_t> waitingForSpawn;

public:
	explicit NetworkClient(Scene* scene);

	bool Connect(const std::string& host, const uint16_t port) override;
	void ProcessNetworkUpdate(float networkDeltaTime);
	void SpawnLocalNetworkObject();
};
