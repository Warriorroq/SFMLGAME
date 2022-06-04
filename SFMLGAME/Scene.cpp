#include "Scene.h"
#include "Server.h"
#include "AgarPlayer.h"

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
	for (const auto object : _objects)
	{
		auto gameObject = object.second;
		if (gameObject->IsAlive())
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
	Message<CustomMessages> msg;
	msg.header.id = CustomMessages::DeleteObjects;
	for (auto object : _objectsForRemove)
	{
		msg << object;
		_objects.erase(object);
	}
	Server::instance->MessageAllClients(msg);
}

void Scene::ReactOnMessage(shared_ptr<Connection<CustomMessages>> client, Message<CustomMessages>& msg)
{
	//cout << "received " << (uint32_t)msg.header.id << " size" << msg.size()<<"\n";
	switch (msg.header.id)
	{
	case CustomMessages::CreatePlayer:
	{
		auto obj = _lobby.CreatePlayerAvatar(client->GetID());
		AppendObject(obj);
		SynchronizeWithNewPlayer(client);
		Server::instance->MessageAllClients(obj->SendDataToCreateObject(), client);
		break;
	}
	case CustomMessages::UpdateObject:
	{
		auto player = _lobby.GetPlayersObject(client->GetID());
		player->Update(msg);
		break;
	}
	case CustomMessages::Disconnect:
	{
		cout << "disconnected " << client << "\n";

		_lobby.RemovePlayer(client->GetID());
		break;
	}
	default:
		break;

	}
}

void Scene::AppendObject(GameObject* gameObject)
{
	_objects.insert(pair<long,GameObject*>(gameObject->id, gameObject));
}

void Scene::DisconnectPlayer(uint32_t id)
{
	_lobby.RemovePlayer(id);
}

void Scene::SynchronizeWithNewPlayer(shared_ptr<Connection<CustomMessages>> client)
{
	for (auto object : _objects)
		Server::instance->MessageClient(client, object.second->SendDataToCreateObject());
}

void Scene::DestroyGameObject(GameObject* gameObject)
{
	gameObject->Destroy();
	_objectsForRemove.push_back(gameObject->id);
}