#pragma once

#include "hpclient.h"
#include "NetworkDelegate.h"
#include "GameMessage.h"
#include <map>

class Scene;

class NetworkClient
{
private:
    networking::hole_punching::hpclient client;

	Scene* scene;
	std::thread networkLoopThread;
	std::thread sheilaThread;
	std::map<uint16_t, std::shared_ptr<NetworkDelegate>> networkObjectMap;
	std::vector<uint16_t> waitingForSpawn;

    bool isConnected = false;

public:
	explicit NetworkClient(Scene* scene);
	bool Connect(const std::string& host, const uint16_t port);

    void Send(GameMessage flag, networking::message&& msg);
	void ProcessNetworkUpdate(float networkDeltaTime);
	void SpawnLocalNetworkObject();

    bool IsConnected() const;
};
