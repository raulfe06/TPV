#include "CollisionsManager.h"





CollisionsManager::CollisionsManager(SDLGame * game, BulletsManager * bulletsManager, AsteroidsManager * asteroidManager, FightersManager * fightersManager)
	: GameObject(game),bulletsManager_(bulletsManager),asteroidsManager_(asteroidManager),fightersManager_(fightersManager)
{
}

CollisionsManager::~CollisionsManager()
{
}

void CollisionsManager::update(Uint32 time)
{
	vector<Bullet*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> astroids = asteroidsManager_->getAsteroids();
	Fighter* fighter = fightersManager_->getFighter();
	// fighter with asteroids

	//...


	// bullets with asteroids

	//Para comprobar choques usar el metodo Collisions::collidesWithRotation 
		
}
