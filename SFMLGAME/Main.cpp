#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Game.h"
#include <boost/signals2.hpp>
#include <Windows.h>

int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	Game::CreateGame();
	Server::CreateServer();
	Server::instance->StartServer();
	Game::instance->Start();
	return 0;
}