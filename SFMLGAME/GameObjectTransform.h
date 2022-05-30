#pragma once
#include <SFML/System.hpp>

using namespace sf;

class GameObjectTransform
{
public:
	GameObjectTransform(Vector2f position) : _position(position) {};
	~GameObjectTransform() {};
	void Move(const Vector2f& direction);
	void SetPosition(const Vector2f& position);
	Vector2f GetPosition();

private:
	Vector2f _position;
};