#pragma once

#include "Component.h"
#include "message.h"

enum class GameMessage : unsigned char;

class NetworkDelegate;

class NetworkComponent : public Component, public std::enable_shared_from_this<NetworkComponent>
{
protected:
	friend class NetworkDelegate;

	std::shared_ptr<NetworkDelegate> networkDelegate;

	virtual void Awake() override;
	virtual void NetworkUpdate(float networkDeltaTime);
	

	bool IsMine() const;
	void SendNetworkMessage(GameMessage flag, networking::message&& msg);
public:
	virtual void OnNetworkMessage(networking::message&& msg) = 0;
};
