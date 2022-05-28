#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <map>

using namespace std;

class GameObjectPlayer;

class Lobby 
{
public:
	void CreatePlayer(uint32_t id, GameObjectPlayer* player);
	GameObjectPlayer* GetPlayersObject(uint32_t id);
	GameObjectPlayer* CreatePlayerAvatar(uint32_t client);
	void RemovePlayer(uint32_t id);
private:
	map<uint32_t, GameObjectPlayer*> _players;
};