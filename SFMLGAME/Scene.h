#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <map>
#include <list>
#include <olc_net.h>
#include "Lobby.h"

using namespace olc;
using namespace net;
using namespace std;
using namespace sf;

class Scene 
{
public:
	Scene() {};
	void Update();
	void Draw(RenderWindow& window);
	void ReactOnMessage(shared_ptr<Connection<CustomMessages>>, Message<CustomMessages>&);
	void AppendObject(GameObject*);
	void DisconnectPlayer(uint32_t);
	void SynchronizeWithNewPlayer(shared_ptr<Connection<CustomMessages>>);
private:
	Lobby _lobby;
	map<long, GameObject*> _objects;
	list<long> _objectsForRemove;

	void ClearDeadObjects();
};