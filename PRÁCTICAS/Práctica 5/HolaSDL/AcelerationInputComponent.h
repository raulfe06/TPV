#pragma once
#include "InputComponent.h"
class AcelerationInputComponent : public InputComponent
{
public:
	AcelerationInputComponent(SDL_Keycode reduceAcel, SDL_Keycode increaseAcel,double thrust, double maxVel,double reductionFactor);
	~AcelerationInputComponent();
	void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	SDL_Keycode reduceAcel_;
	SDL_Keycode increaseAcel_;	
	double thrust_;
	double maxVelocity_;
	double reductionFactor_;
	const double epsilon = 0.1;
};

