#pragma once

#include "Container.h"
#include "ImageRenderer.h"
#include "BasicMotionPhysics.h"
#include "RotationPhysics.h"


const int defAWidth = 30;
const int defAHeight = 30;

/*
 *
 */
class Asteroid: public Container {
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	void setAsteroidId(Uint32 id);
	Uint8 getAsteroidId();
	virtual void setGenerations(int generations);
	virtual int getGenerations();

private:
	Uint8 id_;
	int generations_;
};

