#include "Lobby.h"
#include "GameObjectPlayer.h"
#include "IDGiver.h"

void Lobby::CreatePlayer(uint32_t id, GameObjectPlayer* player)
{
	_players.insert(pair<uint32_t, GameObjectPlayer*>(id, player));
}

GameObjectPlayer* Lobby::GetPlayersObject(uint32_t id)
{
	return _players.find(id)->second;
}

GameObjectPlayer* Lobby::CreatePlayerAvatar(uint32_t client)
{
	auto id = IDgGiver::IncreaseLastId();
	GameObjectPlayer* player = new GameObjectPlayer(id);
	RectangleShape* rect = new RectangleShape(Vector2f(100, 100));
	rect->setFillColor(Color::White);
	rect->setPosition(Vector2f(100, 100));
	player->SetShape(rect);
	CreatePlayer(client, player);
	return player;
}

void Lobby::RemovePlayer(uint32_t id)
{
	GetPlayersObject(id)->Kill();
	_players.erase(id);
}
