#include "RotationPhysics.h"



RotationPhysics::RotationPhysics(double angle) : angle_(angle)
{
}


RotationPhysics::~RotationPhysics()
{
}

void RotationPhysics::update(GameObject * o, Uint32 time)
{
	Vector2D angle = o->getDirection();
	angle.rotate(-angle_);
	o->setDirection(angle);
}
