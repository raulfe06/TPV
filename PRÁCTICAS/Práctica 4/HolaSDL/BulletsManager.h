#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include "Observable.h"
#include "Observer.h"
#include "OManager.h"

class BulletsManager : public Observer, public Observable, public OManager<Bullet>
{
public:
	BulletsManager();
	virtual ~BulletsManager();
	virtual std::vector<Bullet*>& getBullets() = 0;

};

