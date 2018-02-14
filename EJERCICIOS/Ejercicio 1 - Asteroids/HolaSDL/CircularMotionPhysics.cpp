#include "CircularMotionPhysics.h"



void CircularMotionPhysics::update(GameObject* o, Uint32 time)
{
	Vector2D pos = o->getPosition() + o->getVelocity();
	Vector2D aux;

	if (pos.getX() >= o->getGame()->getWindowWidth()) {
		aux = { 0, pos.getY() };
		o->setPosition(aux);
	}
	else if (pos.getX() <= 0)
	{
		aux = { (double)o->getGame()->getWindowWidth(), pos.getY() };
		o->setPosition(aux);
	}
	if (pos.getY() >= o->getGame()->getWindowHeight() ) {
		aux = { pos.getX(), 0 };
		o->setPosition(aux);
	}
	else if (pos.getY() <= 0)
	{
		aux = { pos.getX(), (double)o->getGame()->getWindowHeight() };
		o->setPosition(aux);
	}
	 
}

CircularMotionPhysics::CircularMotionPhysics()
{
}


CircularMotionPhysics::~CircularMotionPhysics()
{
}
