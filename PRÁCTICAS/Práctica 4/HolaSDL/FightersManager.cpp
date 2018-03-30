#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManager) : GameObject(game), fighter_(game,0),
accelerationComp_(SDLK_s,SDLK_w,1,5,0.5),renderComp_(game->getResources()->getImageTexture(Resources::Airplanes), RECT(47, 90, 207, 247)),
rotationComp_(5,SDLK_a,SDLK_d), 

gunComp1_(bulletsManager,SDLK_SPACE,0,500),gunComp2_(bulletsManager, SDLK_SPACE, 0, 100),badgeRenderer_(game)
{
	fighter_.setActive(false);
	fighter_.setPosition(Vector2D(game->getWindowWidth() / 2, game->getWindowHeight() / 2));
	fighter_.addInputComponent(&gunComp1_);
	gunComp1_.registerObserver(bulletsManager);
	gunComp2_.registerObserver(bulletsManager);

	fighter_.addRenderComponent(&renderComp_);

	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&rotationComp_);

	fighter_.addPhysicsComponent(&basicMotionComp_);
	fighter_.addPhysicsComponent(&circulrMotoionComp_);
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
	switch (msg->id_) {
	case ROUND_START:
		fighter_.setActive(true);
		fighter_.setPosition(Vector2D(game_->getWindowWidth() / 2
			, game_->getWindowHeight() / 2));
		break;
	case ROUND_OVER:
		fighter_.setActive(false);
		fighter_.setVelocity(Vector2D(0, 0));
		fighter_.setDirection(Vector2D(1, 0));
		break;
	case BADGE_ON:
		fighter_.delInputComponent(&gunComp1_);
		fighter_.addInputComponent(&gunComp2_);
		fighter_.addRenderComponent(&badgeRenderer_);
		break;
	case BADGE_OFF:
		fighter_.delInputComponent(&gunComp2_);
		fighter_.addInputComponent(&gunComp1_);
		fighter_.delRenderComponent(&badgeRenderer_);
		break;

	}
}
