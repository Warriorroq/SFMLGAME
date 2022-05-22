#include "Game.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <limits.h>
#include "GameClient.h"

using namespace std;

Game* Game::instance = 0;
const int secondInMiliseconds = 1000;

void Game::CreateGame()
{
	instance = new Game();
}

Game::Game()
{
	_window = new RenderWindow(VideoMode(800, 600), " ");
	_updateTimeInMiliseconds = secondInMiliseconds / 60;
}

Game::~Game()
{
	delete _window;
}

RenderWindow& Game::GetRenderWindow()
{
	return *_window;
}

bool Game::IsGameWorking()
{
	return instance->GetRenderWindow().isOpen();
}

void Game::Update()
{
	thread _draw = thread(&Game::Draw, this);
	thread _logic = thread(&Game::LogicUpdate, this);
	_draw.join();
	_logic.join();
	if (GetRenderWindow().pollEvent(_event))
	{
		if (_event.type == Event::Closed) {

			GetRenderWindow().close();
		}
	}
	ThisThreadSleep();
}

void Game::ThisThreadSleep()
{
	int timeElapsed = _deltaClock.getElapsedTime().asMilliseconds();
	int waitTime = _updateTimeInMiliseconds - timeElapsed;
	this_thread::sleep_for(chrono::milliseconds(clamp(waitTime, 0, INT_MAX)));
	_deltaClock.restart();
}

void Game::LogicUpdate()
{

}

void Game::Draw()
{

}

float Game::GetDeltaTime()
{
	return (float)_deltaClock.getElapsedTime().asMilliseconds() / (float)secondInMiliseconds;
}

void Game::ReadMessage(Message<CustomMessages>& msg)
{
	cout << (int)msg.header.id << endl;
	switch (msg.header.id)
	{
	default:
	{
		break;
	}
	}
}

void Game::Start()
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::CreateObject;
	msg << ObjectForCreation::Player;
	GameClient::instance->Send(msg);

	while (IsGameWorking()) {
		instance->Update();
	}
}