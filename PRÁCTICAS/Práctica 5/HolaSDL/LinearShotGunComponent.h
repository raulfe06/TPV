#pragma once
#include "GunInputComponent.h"


class LinearShotGunComponent : public GunInputComponent
{
public:
	LinearShotGunComponent(Observer* bulletsManager_, SDL_Keycode shootKey_, Uint32 timeInterval_);
	~LinearShotGunComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:

	SDL_Keycode shootKey_;
	Uint32 timeInterval_;
	Uint32 tiempoDisparo_;
};


