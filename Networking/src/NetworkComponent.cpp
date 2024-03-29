#include "NetworkComponent.h"
#include "GameObject.h"
#include "NetworkDelegate.h"

void NetworkComponent::Awake()
{
	assert(GetGameObject()->TryGetComponent<NetworkDelegate>(networkDelegate));
}

void NetworkComponent::NetworkUpdate(float networkDeltaTime) { }

bool NetworkComponent::IsMine() const
{
	return networkDelegate->IsMine();
}

void NetworkComponent::SendNetworkMessage(GameMessage flag, networking::message&& msg)
{
	networkDelegate->SendNetworkMessage(flag, std::move(msg));
}
