#pragma once
#include "GameObject.h"
#include "SFML/System.hpp"

using namespace sf;

class GameObjectPlayer : public GameObject
{
public:
	GameObjectPlayer(int id) : GameObject(id){};
	void Update() override;
	void SetVelocity(Vector2f&);
	void Kill();
private:
	Vector2f _velocity;
};