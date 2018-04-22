#include "FightersManager.h"
#include "LinearShotGunComponent.h"
#include "MultiBulletsGunComponent.h"




FightersManager::FightersManager(SDLGame* game, Observer* bulletsManager) : GameObject(game), fighter_(game,0),
accelerationComp_(SDLK_s,SDLK_w,0.3,3,0.5),renderComp_(game->getResources()->getImageTexture(Resources::Airplanes), RECT(47, 90, 207, 247)),
rotationComp_(5,SDLK_a,SDLK_d),
gunComp_(vector<GunInputComponent*>
{
	{new LinearShotGunComponent( bulletsManager, SDLK_SPACE, 500) },
	{new LinearShotGunComponent(bulletsManager,SDLK_SPACE, 100) },
	{new MultiBulletsGunComponent(bulletsManager,SDLK_SPACE, 6, 1000) },

})
{
	initializeBadges();
	fighter_.setActive(false);
	fighter_.setPosition(Vector2D(game->getWindowWidth() / 2, game->getWindowHeight() / 2));

	fighter_.addInputComponent(gunComp_[DefaultBullets]);
	currentGun = DefaultBullets;
	for (size_t i = 0; i < gunComp_.size(); i++)
	{
		gunComp_[i]->registerObserver(bulletsManager);
	}

	fighter_.addRenderComponent(&renderComp_);

	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&rotationComp_);

	fighter_.addPhysicsComponent(&basicMotionComp_);
	fighter_.addPhysicsComponent(&circulrMotoionComp_);
}


FightersManager::~FightersManager()
{
	for (size_t i = 0; i < gunComp_.size(); i++)
	{
		delete gunComp_[i];
		gunComp_[i] = nullptr;
	}
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
		fighter_.delInputComponent(gunComp_[currentGun]);
		fighter_.addInputComponent(gunComp_[FasterBullets]);
		fighter_.addRenderComponent(&badges_[FasterBulletsBadge]);
		currentGun = FasterBullets;
		break;
	case BADGE_OFF:
		fighter_.delInputComponent(gunComp_[currentGun]);
		fighter_.addInputComponent(gunComp_[DefaultBullets]);
		fighter_.delRenderComponent(&badges_[FasterBulletsBadge]);
		currentGun = DefaultBullets;
		break;
	case SUPERBULLETS_ON:
		fighter_.addRenderComponent(&badges_[SuperBulletBadge]);

		break;
	case SUPERBULLETS_OFF:
		fighter_.delRenderComponent(&badges_[SuperBulletBadge]);
		currentGun = DefaultBullets;
		break;
	case MULTIBULLETS_ON:
		fighter_.delInputComponent(gunComp_[currentGun]);
		fighter_.addInputComponent(gunComp_[MultiBullets]);
		fighter_.addRenderComponent(&badges_[MultiBulletsBadge]);
		currentGun = MultiBullets;
		break;
	case MULTIBULLETS_OFF:
		fighter_.delInputComponent(gunComp_[currentGun]);
		fighter_.addInputComponent(gunComp_[DefaultBullets]);
		fighter_.delRenderComponent(&badges_[MultiBulletsBadge]);
		currentGun = DefaultBullets;
		break;
	}
}

void FightersManager::initializeBadges()
{
	for (int i = 0; i < NUM_BADGES; i++) {
		badges_.push_back(BadgeRenderer(game_,(Resources::ImageId)i));
	}
}
