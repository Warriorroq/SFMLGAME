#include "GameObject.h"

void GameObject::Draw(RenderWindow& window)
{
	if (p_shape)
		window.draw(*p_shape);
}

void GameObject::GetStateByMessage(Message<CustomMessages>& msg)
{
	if (p_shape)
	{
		Vector2f vec;
		msg >> vec.y >> vec.x;
		p_shape->setPosition(vec);
	}
}

void GameObject::SetShape(Shape* shape) {
	p_shape = shape;
}

bool GameObject::IsAlive()
{
	return p_isAlive;
}
