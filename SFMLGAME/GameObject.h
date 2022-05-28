#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/Shape.hpp"
#include <olc_net.h>

using namespace olc;
using namespace net;
using namespace sf;

class GameObject
{
public:
	const long& id;
	GameObject(long id) : id(p_id), p_id(id), p_isAlive(true), p_shape(0) {};
	virtual ~GameObject();	
	virtual void Update();
	virtual void Draw(RenderWindow& window);
	virtual Message<CustomMessages> SendGameObjectState();
	virtual Message<CustomMessages> SendDataToCreateObject();
	virtual void Update(Message<CustomMessages>&);
	void SetShape(Shape* shape);
	bool IsAlive();

protected:
	bool p_isAlive;
	Shape* p_shape;
	long p_id;
};