#pragma once
#include "Container.h"

const int defAWidth = 30;
const int defAHeight = 30;

class Asteroid :
	public Container
{
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	virtual void setGenerations(int generations);
	virtual int getGenerations();
private:
	int generations_;
};

