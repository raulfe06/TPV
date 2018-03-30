#include "Asteroid.h"



Asteroid::Asteroid(SDLGame* game) : Container(game)
{
	setActive(true);
	setWidth(defWidth);
	setHeight(defHeight);
}


Asteroid::~Asteroid()
{
}

void Asteroid::setGenerations(int generations)
{
	generations_ = generations;
}

int Asteroid::getGenerations()
{
	return generations_;
}
