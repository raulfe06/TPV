#pragma once
#include "Game.h"

class GameObject 
{
protected:
	Game* game;
public:

	virtual bool handleEvent(SDL_Event& e) {};
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void update() {};

	GameObject(Game* game);
	GameObject();
	~GameObject();
};

