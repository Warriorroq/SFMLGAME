#include <SFML/Graphics.hpp>
#include "GameClient.h"

int main()
{
    GameClient::CreateClient();
    Game::CreateGame();
    GameClient::instance->ConnectToServer();
    Game::instance->Start();
    GameClient::instance->ClientDisconnect();
    return 0;
}