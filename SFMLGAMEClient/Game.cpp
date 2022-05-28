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
	PollEvents();
	thread _logic = thread(&Game::LogicUpdate, this);
	Draw();
	_logic.join();
	ThisThreadSleep();
}
Vector2f velocity;
Vector2f newVelocity;
void Game::PollEvents()
{
	if (GetRenderWindow().pollEvent(_event))
	{
		switch (_event.type)
		{
		case Event::Closed:
		{
			GetRenderWindow().close();
			GameClient::instance->ClientDisconnect();
			break;
		}
		case Event::MouseMoved:
		{
			onMouseMove(_event.mouseMove);
			break;
		}
		case Event::KeyPressed:
		{
			if (_event.key.code == Keyboard::C)
			{
				Message<CustomMessages> msg;
				msg.header.id = CustomMessages::CreatePlayer;
				GameClient::instance->Send(msg);
			}
			if (_event.key.code == Keyboard::D)
			{
				newVelocity.x = 10;
			}
			else if (_event.key.code == Keyboard::A)
			{
				newVelocity.x = -10;
			}
			if (newVelocity != velocity)
			{
				Message<CustomMessages> msg;
				msg.header.id = CustomMessages::UpdateObject;
				msg << newVelocity.y << newVelocity.x << PlayerAction::VeclocityChanged;
				GameClient::instance->Send(msg);
				velocity = newVelocity;
			}
			break;
		}
		case Event::KeyReleased:
		{
			if (_event.key.code == Keyboard::D || _event.key.code == Keyboard::A)
			{
				newVelocity.x = 0;
			}
			if (newVelocity != velocity)
			{
				Message<CustomMessages> msg;
				msg.header.id = CustomMessages::UpdateObject;
				msg << newVelocity.y << newVelocity.x << PlayerAction::VeclocityChanged;
				GameClient::instance->Send(msg);
				velocity = newVelocity;
			}
			break;
		}
		default:
			break;
		}
	}
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
	_drawMutext.lock();
	_window->clear();
	_scene.Draw(*_window);
	_window->display();
	_drawMutext.unlock();
}

float Game::GetDeltaTime()
{
	return (float)_deltaClock.getElapsedTime().asMilliseconds() / (float)secondInMiliseconds;
}

void Game::UpdateByMessage(Message<CustomMessages>& msg)
{
	_scene.ReactOnMessage(msg);
}

void Game::LoadContent()
{

}

void Game::Start()
{
	LoadContent();
	while (IsGameWorking()) {
		instance->Update();
	}
}