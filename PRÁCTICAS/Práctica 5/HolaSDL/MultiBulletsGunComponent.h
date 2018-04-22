#pragma once
#include "GunInputComponent.h"
class MultiBulletsGunComponent :
	public GunInputComponent
{

private:
	SDL_Keycode shootKey_;
	Uint32 timeInterval_;
	Uint32 tiempoDisparo_;
	Uint8 numBullets_;
public:
	MultiBulletsGunComponent(Observer* bulletsManager, SDL_Keycode shootKey_, Uint8 numBullets, Uint32 timeInterval_);
	~MultiBulletsGunComponent();

	void handleInput(GameObject * o, Uint32 time, const SDL_Event & event);
};

