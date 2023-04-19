#include "NetworkTransform.h"

#include "NetworkDelegate.h"

void NetworkTransform::Awake()
{
	NetworkComponent::Awake();

	transform = GetTransform();
	if(!IsMine() || true)
	{
		networkDelegate->RegisterNetworkComponent(shared_from_this(), GameMessage::TransformUpdate);
	}
}

void NetworkTransform::NetworkUpdate(float networkDeltaTime)
{
	Vector3& currentPosition = transform->position;

	if(IsMine())
	{
		if(abs(currentPosition.x - x) > minimumMove || 
		   abs(currentPosition.y - y) > minimumMove ||
		   abs(currentPosition.z - z) > minimumMove)
		{
			x = currentPosition.x;
			y = currentPosition.y;
			z = currentPosition.z;

			olc::net::message<GameMessage> msg;
			msg.header.id = GameMessage::TransformUpdate;
			msg << x << y << z;

			SendNetworkMessage(msg);
		}
	}
	else
	{
		currentPosition.x = x;
		currentPosition.y = y;
		currentPosition.z = z;
	}
}

void NetworkTransform::OnNetworkMessage(olc::net::message<GameMessage>& msg)
{
	std::cout << "Contains 3" << std::endl;
	msg >> z >> y >> x;
}
