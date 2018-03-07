#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Observer.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"
#include "OManager.h"

const double ROTATION_ANGLE = 5;
class AsteroidsManager : public GameObject,public Observer, public Observable,public OManager<Asteroid>
{
public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual vector<Asteroid*>& getAsteroids() { return objs_; };
	virtual void receive(Message* msg);
private:
	void initializeObject(Asteroid* o);
	Asteroid* getAsteroid();
	void initAsteroids();
	ImageRenderer asteroidImage_;
	CircularMotionPhysics circularPhysics_;
	RotationPhysics rotationPhysics_;
	int numOfasteroids_;
};

