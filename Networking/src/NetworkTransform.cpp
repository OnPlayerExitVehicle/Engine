#include "NetworkTransform.h"

#include "NetworkDelegate.h"

const float NetworkTransform::positionChangeMargin = .01f;
const float NetworkTransform::rotationChangeMargin = .001f;

void NetworkTransform::Awake()
{
	NetworkComponent::Awake();

	transform = GetTransform();
	
	networkDelegate->RegisterNetworkComponent(shared_from_this(), GameMessage::TransformUpdate);
}

void NetworkTransform::NetworkUpdate(float networkDeltaTime)
{
	Vector3& currentPosition = transform->position;
    Quaternion& currentRotation = transform->rotation;

	if(IsMine())
	{
		if(abs(currentPosition.x - x) > positionChangeMargin ||
		   abs(currentPosition.y - y) > positionChangeMargin ||
           abs(currentPosition.z - z) > positionChangeMargin ||
           abs(currentRotation.x - rotX) > rotationChangeMargin ||
           abs(currentRotation.y - rotY) > rotationChangeMargin ||
           abs(currentRotation.z - rotZ) > rotationChangeMargin ||
           abs(currentRotation.w - rotW) > rotationChangeMargin)
		{
			x = currentPosition.x;
			y = currentPosition.y;
			z = currentPosition.z;
            rotX = currentRotation.x;
            rotY = currentRotation.y;
            rotZ = currentRotation.z;
            rotW = currentRotation.w;

			networking::message msg;
			msg << x << y << z << rotX << rotY << rotZ << rotW;

			SendNetworkMessage(GameMessage::TransformUpdate, std::move(msg));
		}
	}
	else
	{
		currentPosition.x = x;
		currentPosition.y = y;
		currentPosition.z = z;
        currentRotation.x = rotX;
        currentRotation.y = rotY;
        currentRotation.z = rotZ;
        currentRotation.w = rotW;
	}
}

void NetworkTransform::OnNetworkMessage(networking::message&& msg)
{
	msg >> rotW >> rotZ >> rotY >> rotX >> z >> y >> x;
}
