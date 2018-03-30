#pragma once
#include "Container.h"

const int defWidth = 30;
const int defHeight = 30;

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

