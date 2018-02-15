#include "RotationInputComponent.h"





RotationInputComponent::RotationInputComponent(double angle, SDL_Keycode left, SDL_Keycode right) 
	: angle_(angle) , left_(left) , right_(right)
{
}

RotationInputComponent::~RotationInputComponent()
{
}

void RotationInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Vector2D angle = o->getDirection();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == left_) {
			angle.rotate(-angle_);
		}
		else if (event.key.keysym.sym == right_) {
			angle.rotate(angle_);
		}
	}

	o->setDirection(angle);
}
