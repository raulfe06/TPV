#include "Asteroid.h"



Asteroid::Asteroid(SDLGame* game) : Container(game)
{
	setActive(true);
	setWidth(30);
	setHeight(30);
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
