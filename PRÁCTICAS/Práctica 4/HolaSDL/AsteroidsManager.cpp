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
	for (Asteroid* a : objs_) {
		if(a->isActive()) a->update(time);
	}
}

void AsteroidsManager::render(Uint32 time)
{
	for (Asteroid* a : objs_) {
		if (a->isActive()) a->render(time);
	}
}

void AsteroidsManager::receive(Message * msg)
{
	Asteroid* x;
	Vector2D auxVelocity;
	Vector2D auxDirection;
	float auxAngle;

	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		 x = static_cast<BulletAstroidCollision*>(msg)->astroid_;		 auxVelocity = x->getVelocity();		 auxDirection = x->getDirection();		x->setActive(false);
		numOfasteroids_--;
		if (int numgen = x->getGenerations() > 0) {

			int randomNumber = rand() % ((4 - 2) + 1) + 2; //Random entre 2 y 4 

			for (int i = 0; i > randomNumber; i++) {
				x = getAsteroid();
				x->setGenerations(numgen - 1);
				x->setVelocity(auxVelocity);
				auxAngle = rand() % (360 + 1);
				auxDirection.rotate(auxAngle);
				x->setDirection(auxDirection);
				numOfasteroids_++;
			}
		}
		if (numOfasteroids_ <= 0) {
			Message m = ROUND_OVER;
			send(&m);
		}
		break;
		
	case ROUND_START:
		initAsteroids();
		break;
	}
}

void AsteroidsManager::initializeObject(Asteroid * o)
{

	o->setActive(true);
	o->addPhysicsComponent(&circularPhysics_);
	o->addRenderComponent(&asteroidImage_);
	o->addPhysicsComponent(&rotationPhysics_);
}

Asteroid * AsteroidsManager::getAsteroid()
{
	return getObject(game_);
}

void AsteroidsManager::initAsteroids()
{
	for (Asteroid* a : objs_) {
		a->setActive(false);
	}
	for (int i = 0; i < 5; i++) {
		addAsteroid();
	}
}

void AsteroidsManager::addAsteroid()
{
	Asteroid* a = new Asteroid(game_);
	double x, y;

	switch (rand() % 4)
	{
	case 0: //Arriba
		x = rand() % game_->getWindowWidth();
		y = 0;
		break;
	case 1: // Abajo
		x = rand() % game_->getWindowWidth();
		y = game_->getWindowHeight();

		break;
	case 2: //Izquierda
		x = 0;
		y = rand() % game_->getWindowHeight();

		break;
	case 3: //Derecha
		x = game_->getWindowWidth();
		y = rand() % game_->getWindowHeight();
		break;
	}
	a->setPosition(Vector2D(x, y));
	initializeObject(a);
	objs_.push_back(a);

}


