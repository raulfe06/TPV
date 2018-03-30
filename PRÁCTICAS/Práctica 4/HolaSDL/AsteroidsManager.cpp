#include "AsteroidsManager.h"
#include "BasicMotionPhysics.h"


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
	std::cout << numOfasteroids_ << std::endl;
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
		 static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		 x->setActive(false);
		 numOfasteroids_--;
		
		if (int numgen = x->getGenerations() > 0) 
		{
			auxVelocity = x->getVelocity();
			auxDirection = x->getDirection();
			auxPosition = x->getPosition();

			int randomNumber = rand() % 2 + 2; //Random entre 2 y 4 

			for (int i = 0; i < randomNumber; i++)
			{
				x = getAsteroid();

				x->setActive(true);
				x->setGenerations(numgen - 1);
				

				auxVelocity.rotate(i * 30);

				x->setDirection(auxDirection);
				x->setPosition(auxPosition);
				x->setVelocity(auxVelocity);

				x->setWidth(x->getWidth() / 2);
 				x->setHeight(x->getHeight() / 2);



			//	objs_.push_back(x); YA SE HACE EN EL 'getAsteroid()'
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
	o->setGenerations(4);
	o->addPhysicsComponent(&circularPhysics_);
	o->addRenderComponent(&asteroidImage_);
	o->addPhysicsComponent(&rotationPhysics_);
	o->addPhysicsComponent(new BasicMotionPhysics());
}

Asteroid * AsteroidsManager::getAsteroid()
{
	return getObject(game_);
}

void AsteroidsManager::initAsteroids()
{
	for (Asteroid* a : objs_)
	{
		a->setWidth(defWidth);
		a->setHeight(defHeight);

		a->setActive(false);
	}
	for (int i = 0; i < 5; i++)
		addAsteroid();
}

void AsteroidsManager::addAsteroid()
{
	/*Asteroid* a = new Asteroid(game_);*/
	double x, y;

	//switch (rand() % 3 + 0)
	//{
	//case 0: //Arriba
	//	x = rand() % game_->getWindowWidth() + 0;
	//	y = 0;
	//	break;
	//case 1: // Abajo
	//	x = rand() % game_->getWindowWidth() + 0;
	//	y = game_->getWindowHeight();

	//	break;
	//case 2: //Izquierda
	//	x = 0;
	//	y = rand() % game_->getWindowHeight() + 0;

	//	break;
	//case 3: //Derecha
	//	x = game_->getWindowWidth();
	//	y = rand() % game_->getWindowHeight() + 0;
	//	break;
	//}
	x = game_->getWindowWidth();
	y = rand() % game_->getWindowHeight() + 0;
	Asteroid* a = getAsteroid();
	a->setActive(true);
	a->setPosition(Vector2D(x, y));
	a->setVelocity(Vector2D(-1, 0));

	int randomNumber = rand() % ((3 - 1) + 1) + 1; //Random entre 1 y 3 
	a->setGenerations(randomNumber);
	
	numOfasteroids_++;
	//initializeObject(a);
	//objs_.push_back(a);

}


