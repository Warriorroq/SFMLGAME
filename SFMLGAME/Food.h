#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	Food(long id, float mass) : mass(mass), GameObject(id){};
	Message<CustomMessages> SendDataToCreateObject() override;
	float mass;
};