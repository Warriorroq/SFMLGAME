#include "Game.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <limits.h>
#include <thread>
#include <Windows.h>

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

void Game::PollEvents() 
{
	if (GetRenderWindow().pollEvent(_event))
	{
		switch (_event.type)
		{
		case Event::Closed:
		{
			GetRenderWindow().close();
			break;
		}
		case Event::KeyPressed:
		{
			if(_event.key.code == Keyboard::C)
				ShowWindow(::GetConsoleWindow(), SW_SHOW);
			if (_event.key.code == Keyboard::H)
				ShowWindow(::GetConsoleWindow(), SW_HIDE);
		}
		default:
			break;
		}
	}
}

void Game::Update()
{
	ReadMessages();
	PollEvents();
	thread logic = thread(&Game::LogicUpdate, this);	
	Draw();
	logic.join();
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
	_scene.Update();
}

void Game::Draw()
{
	_window->clear();
	_scene.Draw(*_window);
	_window->display();
}

float Game::GetDeltaTime()
{
	return (float)_deltaClock.getElapsedTime().asMilliseconds() / (float)secondInMiliseconds;
}

void Game::AddMessageToQueue(shared_ptr<Connection<CustomMessages>> client, Message<CustomMessages>& msg)
{
	_serverMessages.push(tuple<shared_ptr<Connection<CustomMessages>>, Message<CustomMessages>>(client, msg));
}

void Game::ReadMessages()
{
	while (!_serverMessages.empty())
	{
		auto message = _serverMessages.front();
		_serverMessages.pop();
		_scene.ReactOnMessage(get<0>(message), get<1>(message));
	}
}

void Game::LoadContent()
{

}

void Game::Start()
{
	::ShowWindow(GetConsoleWindow(), SW_HIDE);
	LoadContent();
	while (IsGameWorking()) {
		instance->Update();
	}
}

void Game::AppendObjectToScene(GameObject* gameObject)
{
	_scene.AppendObject(gameObject);
}

void Game::DisconnectPlayer(uint32_t id)
{
	cout << "disconnect " << id << endl;
	_scene.DisconnectPlayer(id);
}