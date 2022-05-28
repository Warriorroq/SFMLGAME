#include "GameObjectPlayer.h"
#include "Server.h"

void GameObjectPlayer::Update()
{
	p_shape->setPosition(p_shape->getPosition() + _velocity);
}

void GameObjectPlayer::SetVelocity(Vector2f& velocity)
{
	_velocity = velocity;
	Server::instance->MessageAllClients(SendGameObjectState());
}

void GameObjectPlayer::Kill()
{
	p_isAlive = false;
}