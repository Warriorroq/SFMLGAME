#include "GameObject.h"

void GameObject::Draw(RenderWindow& window)
{
	if (_shape)
		window.draw(*_shape);
}

void GameObject::GetStateByMessage(Message<CustomMessages>& msg)
{
	if (_shape)
	{
		Vector2f vec;
		msg >> vec.y >> vec.x;
		_shape->setPosition(vec);
	}
}

void GameObject::SetShape(Shape* shape) {
	_shape = shape;
}
