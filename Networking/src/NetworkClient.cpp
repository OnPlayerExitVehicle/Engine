#include "NetworkClient.h"

#include "NetworkTransform.h"
#include "Scene.h"
#include "MeshRenderer.h"

NetworkClient::NetworkClient(Scene* scene) : scene(scene) { }

bool NetworkClient::Connect(const std::string& host, const uint16_t port)
{
	const bool result = client_interface::Connect(host, port);

	if (!result) return false;

	networkLoopThread = std::thread(
		[this]()
		{
			while(IsConnected())
			{
				if(!Incoming().empty())
				{
					auto msg = Incoming().pop_back().msg;

					std::cout << "First Message Length = " << msg.size() << std::endl;
					uint32_t uid;
					msg >> uid;

					if(msg.header.id == GameMessage::Spawn)
					{
						waitingForSpawn.push_back(uid);
						continue;
					}

					if(networkObjectMap.contains(uid))
					{
						std::cout << "Contains" << std::endl;
						std::cout << "Message Length = " << msg.size() << std::endl;
						networkObjectMap[uid]->OnNetworkMessage(msg);
					}
				}
			}
		});

	return true;
}

void NetworkClient::ProcessNetworkUpdate(float networkDeltaTime)
{
	while(!waitingForSpawn.empty())
	{
		uint32_t id = waitingForSpawn.back();
		waitingForSpawn.pop_back();

		auto go = scene->CreateObject(std::to_string(id));
		go->AddComponent<MeshRenderer>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		auto delegate = go->AddComponent<NetworkDelegate>(this, id, false);
		go->AddComponent<NetworkTransform>();

		networkObjectMap[id] = delegate;
	}

	for (auto it = networkObjectMap.begin(); it != networkObjectMap.end(); ++it) {
		it->second->ProcessNetworkUpdate(networkDeltaTime);
	}
}

void NetworkClient::SpawnLocalNetworkObject()
{
	if (!IsConnected()) return;
	uint32_t id = GetID();

	auto go = scene->CreateObject(std::to_string(id));
	go->AddComponent<MeshRenderer>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	auto delegate = go->AddComponent<NetworkDelegate>(this, id, true);
	go->AddComponent<NetworkTransform>();

	olc::net::message<GameMessage> msg;
	msg.header.id = GameMessage::Spawn;

	Send(msg);
	networkObjectMap[id] = delegate;
}
