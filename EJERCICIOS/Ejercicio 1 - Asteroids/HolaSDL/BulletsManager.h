#pragma once
#include "Vector2D.h"
#include "GameObject.h"
class BulletsManager
{
public:
	BulletsManager();
	~BulletsManager();
	virtual void shoot(GameObject* o, Vector2D p, Vector2D v) = 0;
};

