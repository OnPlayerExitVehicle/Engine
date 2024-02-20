#include "olc_net.h"
#include <iostream>
#include <map>

using namespace networking;

class NetworkServer : public server_interface<GameMessage>
{
public:
	NetworkServer(uint16_t nPort) : server_interface<GameMessage>(nPort) { }

protected:
	virtual bool OnClientConnectRequest(std::shared_ptr<connection<GameMessage>> client) override
	{
		return true;
	}

	virtual void OnClientConnected(std::shared_ptr<connection<GameMessage>> client) override
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			std::cout << "Sending" << std::endl;
			message<GameMessage> msg;
			msg.header.id = GameMessage::Spawn;
			msg << gameObjects[i];
			MessageClient(client, msg);
		}
	}

	virtual void OnClientDisconnect(std::shared_ptr<connection<GameMessage>> client, std::string reason) override
	{
		uint32_t id = client->GetID();
		std::cout << "Client Disconnected [" << id << "], Reason = " << reason << std::endl;

		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), id), gameObjects.end());

		message<GameMessage> msg;
		msg.header.id = GameMessage::Despawn;
		msg << id;

		MessageAllClients(msg, client);
	}

	virtual void OnMessage(std::shared_ptr<connection<GameMessage>> client, message<GameMessage>& msg) override
	{
		uint32_t id = client->GetID();
		switch(msg.header.id) {
			case GameMessage::Spawn: 
				msg << id;
				std::cout << std::format("[{}] Spawned new gameobject", id) << std::endl;
				MessageAllClients(msg, client);
				gameObjects.push_back(id);
				break;
			default:
				msg << id;
				MessageAllClients(msg, client);
				break;
		}
	}

private:
	std::vector<uint32_t> gameObjects;
};

int main(int argc, char* argv[])
{
	uint16_t port;
	if(argc > 1)
	{
		char** tmp;
		port = (uint16_t)strtoul(argv[1], tmp, 10);
		std::cout << "Starting the server from port = " << port << std::endl;
	}
	else
	{
		std::cout << "Port value must be given! Usage = server [port]" << std::endl;
		return EXIT_FAILURE;
	}
	NetworkServer server(port);
	server.Start();

	while(true)
	{
		server.Update(-1, true);
	}
}