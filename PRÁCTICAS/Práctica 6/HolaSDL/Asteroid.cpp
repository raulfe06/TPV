#include "Asteroid.h"

Asteroid::Asteroid(SDLGame* game) :
		Container(game), id_(-1) {
	setActive(true);
	setWidth(defAWidth);
	setHeight(defAHeight);
}

Asteroid::~Asteroid() {
}


void Asteroid::setAsteroidId(Uint32 id) {
	id_ = id;
}

Uint8 Asteroid::getAsteroidId() {
	return id_;
}
void Asteroid::setGenerations(int generations)
{
	generations_ = generations;
}

int Asteroid::getGenerations()
{
	return generations_;
}
