#include "CircularMotionPhysics.h"



void CircularMotionPhysics::update(GameObject* o, Uint32 time)
{
	Vector2D aux;
	if (o->getPosition().getX() > o->getGame()->getWindowWidth()) {
		aux = { 0, o->getPosition().getY() };
		o->setPosition(aux);
	}
	else if (o->getPosition().getX() < 0)
	{
		aux = { (double)o->getGame()->getWindowWidth(), o->getPosition().getY() };
		o->setPosition(aux);
	}
	if (o->getPosition().getY() > o->getGame()->getWindowHeight() ) {
		aux = { o->getPosition().getX(), 0 };
		o->setPosition(aux);
	}
	else if (o->getPosition().getY() < 0)
	{
		aux = { o->getPosition().getX(), (double)o->getGame()->getWindowHeight() };
		o->setPosition(aux);
	}
	
	
}

CircularMotionPhysics::CircularMotionPhysics()
{
}


CircularMotionPhysics::~CircularMotionPhysics()
{
}
