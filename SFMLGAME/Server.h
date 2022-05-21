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
		_isActive = true;
		instance->Start();
		p_serverThread = shared_ptr<thread>(new thread([this]() {UpdateServer(); }));
	}

	void StopServer()
	{
		_isActive = false;
		Stop();
	}

	Server(uint16_t port) : CommonServer<CustomMessages>(port) {
		_isActive = false;
	};

protected:
	static shared_ptr<thread> p_serverThread;
	virtual bool OnClientConnect(std::shared_ptr<Connection<CustomMessages>> client)
	{
		Message<CustomMessages> msg;
		msg.header.id = CustomMessages::ServerAccept;
		client->Send(msg);
		return true;
	}

	virtual void OnClientDisconnect(std::shared_ptr<Connection<CustomMessages>> client)
	{
		Print("Removing client ");
		PrintLine(client->GetID());
	}

	virtual void OnMessage(std::shared_ptr<Connection<CustomMessages>> client, Message<CustomMessages>& msg)
	{
		Game::instance->ReadServerMessage(msg);
	}

private:
	bool _isActive;
	void UpdateServer() 
	{
		while (_isActive)
		{
			Update(1);			
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
		}
	}
};