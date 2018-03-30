#include "CollisionsManager.h"
#include "Collisions.h"




CollisionsManager::CollisionsManager(SDLGame * game, BulletsManager * bulletsManager, AsteroidsManager * asteroidManager, FightersManager * fightersManager)
	: GameObject(game), bulletsManager_(bulletsManager), asteroidsManager_(asteroidManager), fightersManager_(fightersManager)
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
	auto it = astroids.begin();

	//vector<Asteroid*>::iterator it = astroids.begin();
	bool exit = false;

	while (it != astroids.end() && !exit) {
		if (fighter->isActive() && (*it)->isActive() && Collisions::collidesWithRotation(fighter, *it)) {
			Message m = AstroidFighterCollision(*it, fighter);
			send(&m);
			exit = true;
		}
		else it++;
	}

	// bullets with asteroids
	auto a = astroids.begin();
	auto b = bullets.begin();
	exit = false;

	while (b != bullets.end() && !exit) {
		a = astroids.begin();
		while (a != astroids.end() && !exit) {
			if ((*b)->isActive() && (*a)->isActive() && Collisions::collidesWithRotation(*b, *a)) {
				BulletAstroidCollision m = BulletAstroidCollision(*b, *a);
				send(&m);
				exit = true;
			}
			else a++;
		}
		b++;
	}

}
