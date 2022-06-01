#include "Lobby.h"
#include "IDGiver.h"
#include <SFML/Graphics/RectangleShape.hpp>

using namespace std;
using  namespace sf;

void Lobby::CreatePlayer(uint32_t id, AgarPlayer* player)
{
	_players.insert(pair<uint32_t, AgarPlayer*>(id, player));
}

AgarPlayer* Lobby::GetPlayersObject(uint32_t id)
{
	return _players.find(id)->second;
}

AgarPlayer* Lobby::CreatePlayerAvatar(uint32_t client)
{
	auto id = IDgGiver::IncreaseLastId();
	AgarPlayer* player = new AgarPlayer(id);
	CreatePlayer(client, player);
	return player;
}

void Lobby::RemovePlayer(uint32_t id)
{
	GetPlayersObject(id)->Destroy();
	_players.erase(id);
}
