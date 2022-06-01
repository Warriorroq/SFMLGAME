#pragma once
#include "Food.h"

class AgarPlayer : public Food
{
public:
	AgarPlayer(long id);
	void Update() override;
	void Eat(Food*);
	void Update(olc::net::Message<CustomMessages>&) override;
	olc::net::Message<CustomMessages> SendGameObjectState() override;
	olc::net::Message<CustomMessages> SendDataToCreateObject() override;

private:
	sf::Vector2f _velocity;
};