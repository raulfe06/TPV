#include "AsteroidsManager.h"


AsteroidsManager::AsteroidsManager(SDLGame* game) : GameObject(game),
asteroidImage_(game->getResources()->getImageTexture(Resources::Asteroid),RECT(0,0,151,143)),rotationPhysics_(ROTATION_ANGLE),numOfasteroids_(0)
{
	initAsteroids();
}


AsteroidsManager::~AsteroidsManager()
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
	Vector2D auxPosition;
	float auxAngle;

	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		 x = static_cast<BulletAstroidCollision*>(msg)->astroid_;
		 //static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		
		 std::cout << numOfasteroids_ << std::endl;
		 numOfasteroids_--;
		
		if ( x->getGenerations() > 0) 
		{
			auxVelocity = x->getVelocity();
			auxDirection = x->getDirection();
			auxPosition = x->getPosition();

			

			int randomNumber = rand() % 3 + 2; //Random entre 2 y 4 

			for (int i = 0; i < randomNumber; i++)
			{
				Asteroid* a = getAsteroid();

				a->setActive(true);
				a->setGenerations(x->getGenerations() - 1);
				

				auxVelocity.rotate(i * 30);

				a->setDirection(auxDirection);
				a->setPosition(auxPosition);
				a->setVelocity(auxVelocity);

				a->setWidth(x->getWidth() * 3/ 4);
 				a->setHeight(x->getHeight() * 3/ 4);

				numOfasteroids_++;
			}
		}
		x->setActive(false);

		if (numOfasteroids_ <= 0) {
			Message m = NO_MORE_ATROIDS;
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
	//o->setGenerations(4);
	o->addPhysicsComponent(&circularPhysics_);
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
	for (int i = 0; i < ASTEROIDS_NUM; i++)
		addAsteroid();
}

void AsteroidsManager::addAsteroid()
{
	
	double x, y;

	switch (rand() % 3 + 0)
	{
	case 0: //Arriba
		x = rand() % game_->getWindowWidth() + 0;
		y = 0;
		break;
	case 1: // Abajo
		x = rand() % game_->getWindowWidth() + 0;
		y = game_->getWindowHeight();

		break;
	case 2: //Izquierda
		x = 0;
		y = rand() % game_->getWindowHeight() + 0;

		break;
	case 3: //Derecha
		x = game_->getWindowWidth();
		y = rand() % game_->getWindowHeight() + 0;
		break;
	}
	
	Asteroid* a = getAsteroid();
	a->setActive(true);
	a->setPosition(Vector2D(x, y));
	a->setVelocity(getRandomVelocity()*0.1);

	int randomNumber = rand() % 3 + 1; //Random entre 1 y 3 
	a->setGenerations(randomNumber);
	
	numOfasteroids_++;

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
	return Vector2D(x,y);
}


