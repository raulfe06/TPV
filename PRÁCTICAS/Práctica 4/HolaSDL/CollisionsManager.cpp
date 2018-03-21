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
	bool exit = false;

	while (it != astroids.end() && !exit) {
		if (Collisions::collidesWithRotation(fighter, *it)) {
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

	while (a != astroids.end() && !exit) {
		while (b != bullets.end() && !exit) {
			if (Collisions::collidesWithRotation(*b, *a)) {
				Message m = BulletAstroidCollision(*b, *a);
				send(&m);
				exit = true;
			}
			else b++;
		}
		a++;
	}

}
