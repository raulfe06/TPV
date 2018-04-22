#pragma once
#include "Container.h"

const int defBWidth = 5;
const int defBHeight = 5;

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

