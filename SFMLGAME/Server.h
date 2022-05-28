#pragma once
#pragma once
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 
#include <asio.hpp>
#include <thread>
#include "olc_net.h"
#include <ComfortableStream.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "Game.h"

class Server : public CommonServer<CustomMessages> {
public:
	static shared_ptr<Server> instance;
	static void CreateServer() 
	{
		instance = make_shared<Server>(60000);
	}

	void StartServer() 
	{
		instance->Start();
		p_serverThread = shared_ptr<thread>(new thread([this]() {UpdateServer(); }));
	}

	void StopServer()
	{
		Stop();
	}

	Server(uint16_t port) : CommonServer<CustomMessages>(port) {};

protected:
	static shared_ptr<thread> p_serverThread;
	virtual bool OnClientConnect(std::shared_ptr<Connection<CustomMessages>> client)
	{
		Message<CustomMessages> msg;
		msg.header.id = CustomMessages::ServerAccept;
		client->Send(msg);
		return true;
	}

	virtual void OnClientDisconnect(std::shared_ptr<Connection<CustomMessages>> client){}

	virtual void OnMessage(std::shared_ptr<Connection<CustomMessages>> client, Message<CustomMessages>& msg)
	{
		Game::instance->AddMessageToQueue(client, msg);
	}

private:
	void UpdateServer() 
	{
		while (Game::instance->GetRenderWindow().isOpen())
		{
			Update(1, true);			
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
		}
	}
};