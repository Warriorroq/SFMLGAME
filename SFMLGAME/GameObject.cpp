#include "GameObject.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace olc;
using namespace net;
using namespace sf;

GameObject::~GameObject()
{
	delete p_shape;
}

void GameObject::Update() {}

void GameObject::Draw(RenderWindow& window)
{
	if (p_shape)
	{
		p_shape->setPosition(position);
		window.draw(*p_shape);
	}
}

Message<CustomMessages> GameObject::SendGameObjectState()
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::UpdateObject;
	if (p_shape)
		msg << position.x << position.y;
	msg << p_id;
	return msg;
}

Message<CustomMessages> GameObject::SendDataToCreateObject()
{
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::CreateObject;
	if (p_shape)
	{
		msg<< position.x << position.y;
		if (dynamic_cast<CircleShape*>(p_shape))
			msg << 0;
		else if(dynamic_cast<RectangleShape*>(p_shape))
			msg << 1;
	}
	msg << p_id;
	return msg;
}

void GameObject::SetShape(Shape* shape) 
{
	p_shape = shape;
}

void GameObject::Update(Message<CustomMessages>& msg)
{

}

bool GameObject::IsAlive()
{
	return p_isAlive;
}

void GameObject::Destroy()
{
	p_isAlive = false;
	OnDestroy();
}

void GameObject::OnDestroy() 
{

}