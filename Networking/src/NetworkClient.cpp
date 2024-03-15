#include "NetworkClient.h"

#include "NetworkTransform.h"
#include "Scene.h"
#include "MeshRenderer.h"
#include "NetworkColor.h"

NetworkClient::NetworkClient(Scene* scene) : scene(scene), client(rand() % 65536) { }

bool NetworkClient::Connect(const std::string& host, const uint16_t port)
{
	sheilaThread = client.Start(host, port);
    isConnected = true;

    networking::tsqueue<networking::owned_message>& message_queue = client.message_queue;
	networkLoopThread = std::thread(
		[this, &message_queue]()
		{
            while(isConnected)
            {
                message_queue.Wait();
                while(!message_queue.Empty())
                {
                    networking::owned_message msg = message_queue.Dequeue();

                    uint8_t flag_raw;
                    msg.msg >> flag_raw;

                    GameMessage flag = (GameMessage)flag_raw;

                    std::cout << "Got flag = " << (int)flag_raw << std::endl;

                    if(flag == GameMessage::Spawn)
                    {
                        waitingForSpawn.push_back(msg.peer_id);
                        continue;
                    }

                    if(networkObjectMap.contains(msg.peer_id))
                    {
                        networkObjectMap[msg.peer_id]->OnNetworkMessage(flag, std::move(msg.msg));
                    }
                }
            }
		}
	);

	return true;
}

void NetworkClient::Send(GameMessage flag, networking::message&& msg)
{
    msg << (uint8_t) flag;
    client.SendToAll(std::make_shared<networking::message>(std::move(msg)));
}

void NetworkClient::ProcessNetworkUpdate(float networkDeltaTime)
{
	while(!waitingForSpawn.empty())
	{
		uint16_t id = waitingForSpawn.back();
		waitingForSpawn.pop_back();

		auto go = scene->CreateObject(std::to_string(id));
		go->AddComponent<MeshRenderer>();
		auto delegate = go->AddComponent<NetworkDelegate>(this, id, false);
		go->AddComponent<NetworkTransform>();
		go->AddComponent<NetworkColor>();

		networkObjectMap[id] = delegate;
	}

	for (auto it = networkObjectMap.begin(); it != networkObjectMap.end(); ++it) {
		it->second->ProcessNetworkUpdate(networkDeltaTime);
	}
}

void NetworkClient::SpawnLocalNetworkObject()
{
	uint16_t id = 0;

	auto go = scene->CreateObject(std::to_string(id));
	go->AddComponent<MeshRenderer>();
	auto delegate = go->AddComponent<NetworkDelegate>(this, id, true);
	go->AddComponent<NetworkTransform>();
	go->AddComponent<NetworkColor>();

    std::shared_ptr<networking::message> msg = std::make_shared<networking::message>();
    *msg << (uint8_t) GameMessage::Spawn;

	client.SendToAll(msg);
	networkObjectMap[id] = delegate;
}

bool NetworkClient::IsConnected() const
{
    return isConnected;
}