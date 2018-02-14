#pragma once
#include "PhysicsComponent.h"
class CircularMotionPhysics :
	public PhysicsComponent
{
public:
	void update(GameObject* o, Uint32 time);
	CircularMotionPhysics();
	~CircularMotionPhysics();
};

