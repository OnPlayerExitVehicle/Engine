#include "NetworkColor.h"

#include "NetworkDelegate.h"
#include "GameObject.h"

void NetworkColor::Awake()
{
	NetworkComponent::Awake();

	meshRenderer = GetGameObject()->GetComponent<MeshRenderer>();
	
	networkDelegate->RegisterNetworkComponent(shared_from_this(), GameMessage::ColorUpdate);
}

void NetworkColor::NetworkUpdate(float networkDeltaTime)
{
	glm::vec3& currentColor = meshRenderer->GetMaterial().color;

	if(IsMine())
	{
		if(abs(currentColor.r - r) > minimumChange || 
		   abs(currentColor.g - g) > minimumChange ||
		   abs(currentColor.b - b) > minimumChange)
		{
			r = currentColor.r;
			g = currentColor.g;
			b = currentColor.b;

			networking::message<GameMessage> msg;
			msg.header.id = GameMessage::ColorUpdate;
			msg << r << g << b;

			SendNetworkMessage(msg);
		}
	}
	else
	{
		currentColor.r = r;
		currentColor.g = g;
		currentColor.b = b;
	}
}

void NetworkColor::OnNetworkMessage(networking::message<GameMessage>& msg)
{
	msg >> b >> g >> r;
}
