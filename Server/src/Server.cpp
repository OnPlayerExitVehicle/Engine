#include "olc_net.h"
#include <iostream>
#include <map>

class NetworkServer : public olc::net::server_interface<GameMessage>
{
public:
	NetworkServer(uint16_t nPort) : olc::net::server_interface<GameMessage>(nPort) { }

protected:
	virtual bool OnClientConnectRequest(std::shared_ptr<olc::net::connection<GameMessage>> client) override
	{
		return true;
	}

	virtual void OnClientConnected(std::shared_ptr<olc::net::connection<GameMessage>> client) override
	{
		std::cout << "Size = " << gameObjects.size() << std::endl;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			olc::net::message<GameMessage> msg;
			msg.header.id = GameMessage::Spawn;
			msg << gameObjects[i];
			MessageClient(client, msg);
		}
	}

	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMessage>> client, std::string reason) override
	{
		uint32_t id = client->GetID();
		std::cout << "Client Disconnected [" << id << "], Reason = " << reason << std::endl;

		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), id), gameObjects.end());

		olc::net::message<GameMessage> msg;
		msg.header.id = GameMessage::Despawn;
		msg << id;

		MessageAllClients(msg, client);
	}

	virtual void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg) override
	{
		std::cout << static_cast<std::underlying_type_t<GameMessage>>(msg.header.id) << std::endl;
		uint32_t id = client->GetID();
		switch(msg.header.id) {
			case GameMessage::Spawn: 
				msg << id;
				MessageAllClients(msg, client);
				gameObjects.push_back(id);
				break;
			case GameMessage::TransformUpdate:
				msg << id;
				MessageAllClients(msg, client);
				break;
		}
	}

private:
	std::vector<uint32_t> gameObjects;
};

int main()
{
	NetworkServer server(60000);
	server.Start();

	while(true)
	{
		server.Update(-1, true);
	}
}