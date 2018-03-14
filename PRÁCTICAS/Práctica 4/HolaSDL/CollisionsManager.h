#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "BulletsManager.h"
#include "FightersManager.h"
#include "AsteroidsManager.h"
class CollisionsManager :
	public GameObject , public Observable
{
public:
	CollisionsManager(SDLGame* game,
	BulletsManager* bulletsManager,
	AsteroidsManager* asteroidManager,
	FightersManager* fightersManager);

	virtual ~CollisionsManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
private:
	BulletsManager * bulletsManager_;
	AsteroidsManager* asteroidsManager_;
	FightersManager* fightersManager_;
};

