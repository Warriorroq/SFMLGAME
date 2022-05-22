#pragma once
#include <olc_net.h>
#include "Game.h"

using namespace olc;
using namespace net;
using namespace std;

class GameClient : public CommonClient<CustomMessages> {
public:
	static GameClient* instance;
	static void CreateClient() 
	{
		instance = new GameClient();
	}

	void ConnectToServer() 
	{
		GameClient::instance->Connect("127.0.0.1", 60000);
		_clientThread = std::thread(&GameClient::GetMessages, this);
	}

	bool isActive;
	GameClient()
	{
		isActive = true;
	};

	void PingServer() {
		Message<CustomMessages> msg;
		msg.header.id = CustomMessages::ServerPing;

		auto time = chrono::system_clock::now();
		msg << time;

		Send(msg);
	}

	void RecieveMessage() {
		if (IsConnected())
		{
			if (!Incoming().IsEmpty())
			{
				auto msg = Incoming().PopFront().msg;
				Game::instance->ReadMessage(msg);
			}
		}
		else
		{
			cout << "Server Down"<<endl;
		}
	}

	void ClientDisconnect()
	{
		isActive = false;
		Disconnect();
	}
private:
	thread _clientThread;

	void GetMessages() {
		while (GameClient::instance->isActive)
		{
			GameClient::instance->RecieveMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
		}
	}
};