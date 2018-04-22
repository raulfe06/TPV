#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "CircularMotionPhysics.h"
#include "AcelerationInputComponent.h"
#include "ImageRenderer.h"
#include "RotationInputComponent.h"
#include "GunInputComponent.h"
#include "BadgeRenderer.h"
#include "BasicMotionPhysics.h"
#include <vector>


class FightersManager : public GameObject,public Observer
{
	enum badges
	{
		FasterBulletsBadge,SuperBulletBadge,MultiBulletsBadge
	};

	enum guns
	{
		DefaultBullets,FasterBullets, MultiBullets
	};
public:
	
	FightersManager(SDLGame* game, Observer* bulletsMamager);
	virtual ~FightersManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	Fighter* getFighter();
	virtual void receive(Message* msg);
private:
	int currentGun;
	Fighter fighter_;

	CircularMotionPhysics circulrMotoionComp_;
	BasicMotionPhysics basicMotionComp_;
	AcelerationInputComponent accelerationComp_;
	ImageRenderer renderComp_;
	RotationInputComponent rotationComp_;

	std::vector<GunInputComponent*>gunComp_;
	std::vector<BadgeRenderer>badges_;
	
	void initializeBadges();
};

