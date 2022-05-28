#pragma once
#include <olc_net.h>
#include "Game.h"
#include <ddeml.h>

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
		ShowWindow(::GetConsoleWindow(), SW_SHOW);
		cout << "enter ip\n";
		string ip;
		getline(cin, ip);
		GameClient::instance->Connect(ip, 60000);
		//ShowWindow(::GetConsoleWindow(), SW_HIDE);
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
				std::cout << "id " << (uint32_t)msg.header.id << " size " << msg.size() << "\n";
				Game::instance->UpdateByMessage(msg);
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
		Message<CustomMessages> msg;
		msg.header.id = CustomMessages::Disconnect;
		Send(msg);
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