#pragma once
#include "SFML/Graphics/Shape.hpp"
#include <olc_net.h>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace olc;
using namespace net;
using namespace sf;

class GameObject
{
public:
	const long& id;
	GameObject(long id) : id(_id), _id(id), p_isAlive(true), p_shape(0) {};

	virtual void Update() {}
	virtual void Draw(RenderWindow& window);
	virtual void GetStateByMessage(Message<CustomMessages>& msg);
	void SetShape(Shape* shape);
	bool IsAlive();

protected:
	Shape* p_shape;
	bool p_isAlive;

private:
	long _id;
};