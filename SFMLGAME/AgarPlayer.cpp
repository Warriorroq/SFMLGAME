#include "AgarPlayer.h"
#include "VectorMath.h"
#include <SFML/Graphics/CircleShape.hpp>

const float agarStartValue = 144;
const float agarStandartSpeed = 20;

AgarPlayer::AgarPlayer(long id) : Food(id, agarStartValue)
{	
	p_shape = new CircleShape(sqrt(mass));
};

void AgarPlayer::Update() 
{
	transform.Move(_velocity);
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
	velocity *= agarStandartSpeed;
	velocity /= dynamic_cast<CircleShape*>(p_shape)->getRadius();
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
	auto position = transform.GetPosition();
	msg << position.x << position.y << _velocity.x << _velocity.y << mass << p_id;
	return msg;
}

Message<CustomMessages> AgarPlayer::SendDataToCreateObject()
{
	auto last = dynamic_cast<Food*>(this);
	auto msg = last->SendDataToCreateObject();
	ObjectToCreate remove;
	msg >> remove;
	msg << ObjectToCreate::agar;
	return msg;
}
