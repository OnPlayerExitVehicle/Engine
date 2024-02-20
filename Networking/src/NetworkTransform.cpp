#include "NetworkTransform.h"

#include "NetworkDelegate.h"

void NetworkTransform::Awake()
{
	NetworkComponent::Awake();

	transform = GetTransform();
	
	networkDelegate->RegisterNetworkComponent(shared_from_this(), GameMessage::TransformUpdate);
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

			networking::message<GameMessage> msg;
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

void NetworkTransform::OnNetworkMessage(networking::message<GameMessage>& msg)
{
	msg >> z >> y >> x;
}
