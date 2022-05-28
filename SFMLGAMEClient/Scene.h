#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <map>
#include <list>

using namespace std;
using namespace sf;

class Scene
{
public:
	Scene() {};
	void Update();
	void Draw(RenderWindow& window);
	void ReactOnMessage(Message<CustomMessages>&);
private:
	void ClearDeadObjects();
	void CreateObject(Message<CustomMessages>&);
	map<long, GameObject*> _objects;
	list<long> _objectsForRemove;
};