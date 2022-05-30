#pragma once
#include <SFML/Graphics.hpp>
#include <olc_net.h>
#include <mutex>
#include "Scene.h"
#include <queue>

using namespace olc;
using namespace net;
using namespace sf;

class Game
{
public:
	static Game* instance;
	RenderWindow& GetRenderWindow();

	static void CreateGame();
	static bool IsGameWorking();
	void Start();
	void Update();
	void PollEvents();
	void AppendObjectToScene(GameObject*);
	void DestroyGameObject(GameObject*);
	void DisconnectPlayer(uint32_t);
	void AddMessageToQueue(shared_ptr<Connection<CustomMessages>>, Message<CustomMessages>&);
	float GetDeltaTime();	
	~Game();

protected:
	virtual void LogicUpdate();
	void LoadContent();

private:
	int _updateTimeInMiliseconds;
	Scene _scene;
	Clock _deltaClock;
	Event _event;
	RenderWindow* _window;
	std::mutex _drawMutext;
	queue<tuple<shared_ptr<Connection<CustomMessages>>, Message<CustomMessages>>> _serverMessages;

	void ReadMessages();
	void ThisThreadSleep();
	void Draw();
	Game();
};