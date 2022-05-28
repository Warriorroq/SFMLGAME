#include "Scene.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

void Scene::Draw(RenderWindow& window)
{
	for (auto object : _objects)
	{
		object.second->Draw(window);
	}
}

void Scene::Update()
{
	for (auto object : _objects)
	{
		auto gameObject = object.second;
		if (gameObject->isAlive)
		{
			gameObject->Update();
		}
		else
		{
			_objectsForRemove.push_back(object.first);
		}
	}
	ClearDeadObjects();
}

void Scene::ClearDeadObjects()
{
	for (auto object : _objectsForRemove)
	{
		_objects.erase(object);
	}
}

void Scene::CreateObject(Message<CustomMessages>& msg)
{
	long id = -1;
	msg >> id;
	GameObject* object = new GameObject(id);
	if (msg.size() != 0)
	{
		Shape* shape = 0;
		int shapeId;
		Vector2f position;
		msg >> shapeId >>position.y >> position.x;
		if (0 == shapeId)
			shape = new CircleShape(5);
		else if (1 == shapeId)
			shape = new RectangleShape(Vector2f(100, 100));
		shape->setFillColor(Color::White);
		shape->setPosition(position);
		object->SetShape(shape);
	}
	_objects.insert(pair<long,GameObject*>(id, object));
}

void Scene::ReactOnMessage(Message<CustomMessages>& msg)
{
	switch (msg.header.id)
	{
	case CustomMessages::CreateObject:
	{
		CreateObject(msg);
		break;
	}
	case CustomMessages::UpdateObject:
	{
		long id;
		msg >> id;
		_objects.find(id)->second->GetStateByMessage(msg);
		break;
	}
	default:
		break;
	}
}