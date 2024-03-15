#include "NetworkDelegate.h"

void NetworkDelegate::Awake()
{
	
}

NetworkDelegate::NetworkDelegate(NetworkClient* client, uint16_t id, bool local) : uid(id), isMine(local), networkClient(client) { }

void NetworkDelegate::RegisterNetworkComponent(const std::shared_ptr<NetworkComponent>& component, GameMessage messageType)
{
	networkComponentMap[messageType] = component;
}

bool NetworkDelegate::IsMine() const
{
	return isMine;
}

void NetworkDelegate::SendNetworkMessage(GameMessage flag, networking::message&& msg)
{
	networkClient->Send(flag, std::move(msg));
}

void NetworkDelegate::OnNetworkMessage(GameMessage flag, networking::message&& msg)
{
	if(networkComponentMap.contains(flag))
	{
		networkComponentMap[flag]->OnNetworkMessage(std::move(msg));
	}
}

void NetworkDelegate::ProcessNetworkUpdate(float networkDeltaTime)
{
	for (auto it = networkComponentMap.begin(); it != networkComponentMap.end(); ++it) {
		it->second->NetworkUpdate(networkDeltaTime);
	}
}
