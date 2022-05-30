#include "GamerObjectPlayer.h"

void GameObjectPlayer::Update()
{
	p_shape->setPosition(p_shape->getPosition() + _velocity);
}

void GameObjectPlayer::SetVelocity(Vector2f& velocity)
{
	_velocity = velocity;
}

void GameObjectPlayer::Kill()
{
	p_isAlive = false;
}

void GameObjectPlayer::GetStateByMessage(Message<CustomMessages>& msg)
{
	Vector2f velocity;
	msg >> velocity.y >> velocity.x;
	SetVelocity(velocity);
	if (p_shape)
	{
		Vector2f vec;
		msg >> vec.y >> vec.x;
		p_shape->setPosition(vec);
	}
}