#include "NetworkComponent.h"
#include "GameObject.h"
#include "NetworkDelegate.h"

void NetworkComponent::Awake()
{
	if (!GetGameObject()->TryGetComponent<NetworkDelegate>(networkDelegate))
	{
		throw std::exception("No network delegate!");
	}
}

void NetworkComponent::NetworkUpdate(float networkDeltaTime) { }

bool NetworkComponent::IsMine() const
{
	return networkDelegate->IsMine();
}

void NetworkComponent::SendNetworkMessage(olc::net::message<GameMessage>& msg)
{
	networkDelegate->SendNetworkMessage(msg);
}
