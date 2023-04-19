#include "NetworkDelegate.h"

void NetworkDelegate::Awake()
{
	
}

NetworkDelegate::NetworkDelegate(NetworkClient* client, uint32_t id, bool local) : uid(id), isMine(local), networkClient(client) { }

void NetworkDelegate::RegisterNetworkComponent(const std::shared_ptr<NetworkComponent>& component, GameMessage messageType)
{
	networkComponentMap[messageType] = component;
}

bool NetworkDelegate::IsMine() const
{
	return isMine;
}

void NetworkDelegate::SendNetworkMessage(olc::net::message<GameMessage>& msg)
{
	networkClient->Send(msg);
}

void NetworkDelegate::OnNetworkMessage(olc::net::message<GameMessage>& msg)
{
	if(networkComponentMap.contains(msg.header.id))
	{
		std::cout << "Contains 2" << std::endl;
		networkComponentMap[msg.header.id]->OnNetworkMessage(msg);
	}
}

void NetworkDelegate::ProcessNetworkUpdate(float networkDeltaTime)
{
	for (auto it = networkComponentMap.begin(); it != networkComponentMap.end(); ++it) {
		it->second->NetworkUpdate(networkDeltaTime);
	}
}
