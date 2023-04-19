#pragma once

#include "Component.h"
#include "olc_net.h"

class NetworkDelegate;

class NetworkComponent : public Component, public std::enable_shared_from_this<NetworkComponent>
{
protected:
	friend class NetworkDelegate;

	std::shared_ptr<NetworkDelegate> networkDelegate;

	virtual void Awake() override;
	virtual void NetworkUpdate(float networkDeltaTime);
	

	bool IsMine() const;
	void SendNetworkMessage(olc::net::message<GameMessage>& msg);
public:
	virtual void OnNetworkMessage(olc::net::message<GameMessage>& msg) = 0;
};
