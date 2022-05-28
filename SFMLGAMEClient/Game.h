#pragma once
#include <SFML/Graphics.hpp>
#include <boost/signals2.hpp>
#include <memory>
#include <olc_net.h>
#include <thread>
#include "Scene.h"
#include <mutex>

using namespace olc;
using namespace net;
using namespace sf;

class Game
{
public:
	static Game* instance;
	boost::signals2::signal<void(sf::Event::MouseMoveEvent)> onMouseMove;

	RenderWindow& GetRenderWindow();
	static void CreateGame();
	static bool IsGameWorking();
	void Start();
	void Update();
	void PollEvents();
	void UpdateByMessage(Message<CustomMessages>& msg);
	float GetDeltaTime();
	~Game();

protected:
	virtual void LogicUpdate();
	void LoadContent();

private:
	int _updateTimeInMiliseconds;
	Clock _deltaClock;
	Event _event;
	RenderWindow* _window;
	Scene _scene;
	std::mutex _drawMutext;

	void ThisThreadSleep();
	void Draw();
	Game();
};