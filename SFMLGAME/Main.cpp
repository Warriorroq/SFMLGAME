#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Game.h"
#include <boost/signals2.hpp>

int main()
{
	Server::CreateServer();
	Game::CreateGame();
	Server::instance->StartServer();
	Game::instance->Start();
	return 0;
}