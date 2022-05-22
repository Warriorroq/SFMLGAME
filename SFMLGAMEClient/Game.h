#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <olc_net.h>
#include <thread>

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
	void ReadMessage(Message<CustomMessages>& msg);
	float GetDeltaTime();
	~Game();

protected:
	virtual void LogicUpdate();

private:
	int _updateTimeInMiliseconds;
	Clock _deltaClock;
	Event _event;
	RenderWindow* _window;

	void ThisThreadSleep();
	void Draw();
	Game();
};