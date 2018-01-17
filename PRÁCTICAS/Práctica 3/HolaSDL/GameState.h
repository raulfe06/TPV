#pragma once
#include <list>
#include "GameObject.h"
#include "Game.h"


class GameState
{
protected:
	list<GameObject*> scene;
	
	Game* game;
public:
	GameState(Game* game);
	GameState();
	~GameState() 
	{
		for (GameObject* obj : scene) delete obj;
	};

	virtual void update()
	{
		for (GameObject* obj : scene) obj->update();
	}

	virtual void handleEvents(SDL_Event& e)
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

	virtual void render(SDL_Renderer* renderer)
	{
		for (GameObject* obj : scene) obj->render(renderer);
	}

	Texture* getTexture(enumTextures name)
	{
		return game->getTexture(name);
	}
};

