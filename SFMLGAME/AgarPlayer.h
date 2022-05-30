#pragma once
#include "Food.h"

class AgarPlayer : public Food
{
public:
	AgarPlayer(long id);
	void Update() override;
	void Eat(Food*);
	void Update(Message<CustomMessages>&) override;
	Message<CustomMessages> SendGameObjectState() override;
	Message<CustomMessages> SendDataToCreateObject() override;

private:
	Vector2f _velocity;
};