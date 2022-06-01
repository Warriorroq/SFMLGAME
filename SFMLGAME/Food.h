#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	Food(long id, float mass) : GameObject(id), mass(mass){}
	olc::net::Message<CustomMessages> SendDataToCreateObject() override;
	float mass;
};