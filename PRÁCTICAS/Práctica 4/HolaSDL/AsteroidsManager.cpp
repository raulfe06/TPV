#include "AsteroidsManager.h"



AsteroidsManager::AsteroidsManager(SDLGame* game) : GameObject(game),
asteroidImage_(game->getResources()->getImageTexture(Resources::Asteroid)),rotationPhysics_(ROTATION_ANGLE)
{
	initAsteroids();
}


AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::handleInput(Uint32 time, const SDL_Event & event)
{
}

void AsteroidsManager::update(Uint32 time)
{
	for (Asteroid* a : asteroids_) {
		if(a->isActive()) a->update(time);
	}
}

void AsteroidsManager::render(Uint32 time)
{
	for (Asteroid* a : asteroids_) {
		if (a->isActive()) a->render(time);
	}
}

void AsteroidsManager::receive(Message * msg)
{
	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:

		break;
		
	case ROUND_START:
		initAsteroids();
		break;
	}
}

void AsteroidsManager::initializeObject(Asteroid * o)
{
	/*Añadir componentes*/
}

Asteroid * AsteroidsManager::getAsteroid()
{
	return getObject();
}

void AsteroidsManager::initAsteroids()
{
}


