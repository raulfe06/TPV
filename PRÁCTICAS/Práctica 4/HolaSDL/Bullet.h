#pragma once
#include "Container.h"
class Bullet :
	public Container
{
public:
	Bullet(SDLGame* game);
	virtual ~Bullet();
	void setFighterId(int id);
	int getFighterId();
	bool outOfWindow();
private:
	int fighterId_;
};

