#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/Shape.hpp"
#include <olc_net.h>

class GameObject
{
public:
	const long& id;
	GameObject(const long id) : id(p_id), p_id(id), p_isAlive(true), p_shape(nullptr) {}
	virtual ~GameObject();	
	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);
	virtual olc::net::Message<CustomMessages> SendGameObjectState();
	virtual olc::net::Message<CustomMessages> SendDataToCreateObject();
	virtual void Update(olc::net::Message<CustomMessages>&);
	void SetShape(sf::Shape* shape);
	bool IsAlive();
	void Destroy();
	sf::Vector2f position;

protected:
	virtual void OnDestroy();
	long p_id;
	bool p_isAlive;
	sf::Shape* p_shape;
};