#include "GameObjectTransform.h"

void GameObjectTransform::SetPosition(const Vector2f& direction)
{
	_position += direction;
}

void GameObjectTransform::Move(const Vector2f& position)
{
	_position.x = position.x;
	_position.y = position.y;
}

Vector2f GameObjectTransform::GetPosition()
{
	return _position;
}