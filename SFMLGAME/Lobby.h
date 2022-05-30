#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <map>
#include "AgarPlayer.h"

using namespace std;

class Lobby 
{
public:
	void CreatePlayer(uint32_t id, AgarPlayer* player);
	AgarPlayer* GetPlayersObject(uint32_t id);
	AgarPlayer* CreatePlayerAvatar(uint32_t client);
	void RemovePlayer(uint32_t id);
private:
	map<uint32_t, AgarPlayer*> _players;
};