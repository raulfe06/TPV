#pragma once
#include "InputComponent.h"
class RotationInputComponent : public InputComponent
{
public:
	RotationInputComponent(double angle,SDL_Keycode left,SDL_Keycode right);
	~RotationInputComponent();
	void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);

private:
	SDL_Keycode left_;
	SDL_Keycode right_;
	double angle_;
};

