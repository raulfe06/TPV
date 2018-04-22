#pragma once
#include "InputComponent.h"
#include "Observable.h"
#include "BulletsManager.h"
class GunInputComponent : public InputComponent, public Observable
{
protected:
	Observer* bulletsManager_;
public:
	GunInputComponent(Observer* bulletsManager);
	~GunInputComponent();

	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {};
};

