#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManager) : GameObject(game), fighter_(game,0),
accelerationComp_(SDLK_s,SDLK_w,10,20,0.5),renderComp_(game->getResources()->getImageTexture(Resources::Airplanes)),
rotationComp_(5,SDLK_a,SDLK_d), 

gunComp1_(bulletsManager,SDLK_SPACE,5,3),gunComp2_(bulletsManager, SDLK_SPACE, 8, 2)
{
	
}


FightersManager::~FightersManager()
{
}

void FightersManager::handleInput(Uint32 time, const SDL_Event & event)
{
	if (fighter_.isActive()) {
		fighter_.handleInput(time,event);
	}
}

void FightersManager::update(Uint32 time)
{
	if (fighter_.isActive()) {
		fighter_.update(time);
	}
}

void FightersManager::render(Uint32 time)
{
	if (fighter_.isActive()) {
		fighter_.render(time);
	}
}

Fighter * FightersManager::getFighter()
{
	return &fighter_;
}

void FightersManager::receive(Message * msg)
{
}
