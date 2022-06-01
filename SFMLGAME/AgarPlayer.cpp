#include "AgarPlayer.h"
#include "VectorMath.h"
#include <SFML/Graphics/CircleShape.hpp>

using namespace olc;
using namespace net;
using namespace sf;

const float agarStartValue = 144;
const float agarStandartSpeed = 20;

AgarPlayer::AgarPlayer(long id) : Food(id, agarStartValue)
{	
	p_shape = new CircleShape(std::sqrt(mass));
};

void AgarPlayer::Update() 
{
	position += _velocity;
}

void AgarPlayer::Update(Message<CustomMessages>& msg)
{
	Vector2f velocity;
	msg >> velocity.y >> velocity.x; // get normalize velocity vector
	if (SqrtLength(velocity) > 1)
	{
		std::cout << "cheater id:" << id<<"\n";
		//Destroy();
	}
	velocity *= agarStandartSpeed / dynamic_cast<CircleShape*>(p_shape)->getRadius();
	_velocity = velocity;
}

void AgarPlayer::Eat(Food* food) 
{
	mass += food->mass;
	dynamic_cast<CircleShape*>(p_shape)->setRadius(mass);
	food->Destroy();
}

Message<CustomMessages> AgarPlayer::SendGameObjectState() 
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::UpdateObject;
	msg << position.x << position.y << _velocity.x << _velocity.y << mass << p_id;
	return msg;
}

Message<CustomMessages> AgarPlayer::SendDataToCreateObject()
{
	auto last = dynamic_cast<Food*>(this);
	Message<CustomMessages> msg = last->SendDataToCreateObject();
	ObjectToCreate remove;
	msg >> remove;
	msg << ObjectToCreate::agar;
	return msg;
}
