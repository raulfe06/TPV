#pragma once
#include "InputComponent.h"
#include "BulletsManager.h"
class GunInputComponent :
	public InputComponent
{
public:
	GunInputComponent(Observer* bulletsManager_, SDL_Keycode shootKey_,Uint8 shotsPerInterval, Uint32 timeInterval_);
	~GunInputComponent();
	void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	Observer* bulletsManager_;
	SDL_Keycode shootKey_;
	Uint8 shotsPerInterval_;
	Uint32 timeInterval_;
	Uint32 tiempoDisparo_;
};

