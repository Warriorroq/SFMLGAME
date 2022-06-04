#pragma once
#include <map>

class AgarPlayer;

class Lobby 
{
public:
	void CreatePlayer(uint32_t id, AgarPlayer* player);
	AgarPlayer* GetPlayersObject(uint32_t id);
	AgarPlayer* CreatePlayerAvatar(uint32_t client);
	void RemovePlayer(uint32_t id);
private:
	std::map<uint32_t, AgarPlayer*> _players;
};