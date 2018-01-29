#pragma once
#include <list>
#include "GameObject.h"
#include "Game.h"
#include "checkML.h"


class GameState
{
protected:
	list<GameObject*> scene;
	enumTextures backGroundName;
	Game* game;

	Texture* tex = nullptr;
public:
	GameState(Game* game);
	GameState();
	void renderCode(const int& count);
virtual	~GameState() 
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

		while (!handled && it!= scene.end())
		{
			if ((*it)->handleEvent(e))
				handled = true;
			else
				it++;
		}
	}

	virtual void render(SDL_Renderer* renderer)
	{
		renderBackGround();
		for (GameObject* obj : scene) obj->render(renderer);
	}

	Texture* getTexture(enumTextures name)
	{
		return game->getTexture(name);
	}

	void renderBackGround();
	void setBackName(enumTextures name) { backGroundName = name; };
};

