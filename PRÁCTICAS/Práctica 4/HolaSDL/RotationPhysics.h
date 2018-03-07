#pragma once
#include "PhysicsComponent.h"
class RotationPhysics :
	public PhysicsComponent
{
public:
	RotationPhysics(double angle);
	~RotationPhysics();
	void update(GameObject* o, Uint32 time);
private:
	double angle_;
};

