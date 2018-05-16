#include "AsteroidsManager.h"


AsteroidsManager::AsteroidsManager(SDLGame* game, GameManager* gm) : GameObject(game),gm_(gm),
asteroidImage_(game->getResources()->getImageTexture(Resources::Astroid), RECT(0, 0, 151, 143)),
rotationPhysics_(ROTATION_ANGLE), numOfasteroids_(0),timeInterval(10000),timePassed(0)
{
	initAsteroids();
}


AsteroidsManager::~AsteroidsManager()
{
}


void AsteroidsManager::update(Uint32 time)
{
	for (Asteroid* a : objs_) {
		if (a->isActive()) a->update(time);
	}
	if (time - timePassed > timeInterval && getGame()->isMasterClient()) {
		timePassed = time;
		if(gm_->getState() == GameManager::GameState::RUNNING)
		addAsteroid();
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
	Vector2D auxPosition;
	float auxAngle;

	switch (msg->mType_)
	{
	//case BULLET_ASTROID_COLLISION:
	//	x = static_cast<BulletAstroidCollision*>(msg)->astroid_;
	//	//static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);

	//	std::cout << numOfasteroids_ << std::endl;
	//	numOfasteroids_--;

	//	if (x->getGenerations() > 0)
	//	{
	//		auxVelocity = x->getVelocity();
	//		auxDirection = x->getDirection();
	//		auxPosition = x->getPosition();



	//		int randomNumber = rand() % 3 + 2; //Random entre 2 y 4 

	//		for (int i = 0; i < randomNumber; i++)
	//		{
	//			Asteroid* a = getAsteroid();

	//			a->setActive(true);
	//			a->setGenerations(x->getGenerations() - 1);


	//			auxVelocity.rotate(i * 30);

	//			a->setDirection(auxDirection);
	//			a->setPosition(auxPosition);
	//			a->setVelocity(auxVelocity);

	//			a->setWidth(x->getWidth() * 3 / 4);
	//			a->setHeight(x->getHeight() * 3 / 4);

	//			numOfasteroids_++;
	//		}
	//	}
	//	x->setActive(false);

	//	if (numOfasteroids_ <= 0) {
	//		//Message m = NO_MORE_ATROIDS;
	//		//send(&m);
	//	}
	//	break;

	case GAME_START:
		break;
	case GAME_OVER:
		disableAsteroids();
		break;
	case CREATE_ASTEROID:
		AsteroidCreated * aux = static_cast<AsteroidCreated*>(msg);
		Asteroid * a = getAsteroid();
		a->setVelocity(aux->vel_);
		a->setDirection(aux->dir_);
		a->setPosition(aux->pos_);
		a->setHeight(aux->height_);
		a->setWidth(aux->width_);
		break;
	}
}

void AsteroidsManager::disableAsteroids() 
	{
		for (Asteroid* b : objs_)
			b->setActive(false);
	}

void AsteroidsManager::initializeObject(Asteroid * o)
{

	o->setActive(true);
	o->addPhysicsComponent(&deactiveOnExitBordersPhysics_);
	o->addRenderComponent(&asteroidImage_);
	o->addPhysicsComponent(&rotationPhysics_);
	o->addPhysicsComponent(&posPhysics_);
}

Asteroid * AsteroidsManager::getAsteroid()
{
	return getObject(game_);
}

void AsteroidsManager::initAsteroids()
{
	numOfasteroids_ = 0;
	for (Asteroid* a : objs_)
	{
		a->setWidth(defAWidth);
		a->setHeight(defAHeight);

		a->setActive(false);
	}
	/*for (int i = 0; i < ASTEROIDS_NUM; i++)
		addAsteroid();*/
}

void AsteroidsManager::addAsteroid()
{
	Asteroid* a = getAsteroid();

	Vector2D vel((1 - 2 * (rand() % 2))*((rand() % 10) + 1), ((rand() % 10) + 1));
	vel.normalize();
	vel = vel * 0.5;
	Vector2D pos(rand() % getGame()->getWindowWidth(), rand() % 30);
	Vector2D dir(0, -1);
	double width = (rand() % 10) + 20;
	double height = (rand() % 10) + 20;

	a->setActive(true);
	a->setPosition(pos);
	a->setVelocity(vel);
	a->setDirection(dir);
	a->setHeight(height);
	a->setWidth(width);

	send(&AsteroidCreated(pos, dir, vel, width, height));

}

Vector2D AsteroidsManager::getRandomVelocity()
{
	int x, y;
	int randomNum = rand() % 8 + 1;
	switch (randomNum)
	{
	case 1:
		x = -1;
		y = 0;
		break;
	case 2:
		x = 1;
		y = 0;
		break;
	case 3:
		x = 0;
		y = 1;
		break;
	case 4:
		x = 0;
		y = -1;
		break;
	case 5:
		x = 1;
		y = 1;
		break;
	case 6:
		x = -1;
		y = -1;
		break;
	case 7:
		x = -1;
		y = 1;
		break;
	case 8:
		x = 1;
		y = -1;
		break;
	}
	return Vector2D(x, y);
}


