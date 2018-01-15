#pragma once
#include <list>
#include "GameObject.h"
#include "Game.h"
class GameState
{
private:
	list<GameObject*> scene;
	
	PlayState* game;
public:
	GameState();
	~GameState() 
	{
		for (GameObject* obj : scene) delete obj;
	};

	void update()
	{
		for (GameObject* obj : scene) obj->update();
	}

	void handleEvents(SDL_Event& e)
	{
		bool handled = false;

		auto it = scene.begin();

		while (it!= scene.end() && !handled)
		{
			if ((*it)->handleEvent(e))
				handled = true;
			else
				it++;
		}
	}

	void render()
	{
		for (GameObject* obj : scene) obj->render();
	}
};

