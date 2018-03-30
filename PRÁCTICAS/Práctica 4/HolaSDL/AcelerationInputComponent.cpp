#include "AcelerationInputComponent.h"



AcelerationInputComponent::AcelerationInputComponent(SDL_Keycode reduceAcel, SDL_Keycode increaseAcel,double thrust,double maxVel,double reductionFactor) 
	: reduceAcel_(reduceAcel),increaseAcel_(increaseAcel) , thrust_(thrust), maxVelocity_(maxVel), reductionFactor_(reductionFactor)
{
}


AcelerationInputComponent::~AcelerationInputComponent()
{
}

void AcelerationInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == reduceAcel_) {
			o->setVelocity(o->getVelocity()*reductionFactor_);
			
		}
		else if (event.key.keysym.sym == increaseAcel_)
		{
			o->setVelocity(o->getVelocity() + o->getDirection()*thrust_);
		}

		if (o->getVelocity().magnitude() > maxVelocity_) {
			
			Vector2D auxVel_;
			auxVel_ = o->getVelocity();
			auxVel_.normalize();
			auxVel_ = auxVel_ * maxVelocity_;
			o->setVelocity(auxVel_);
			
		}
		else if (o->getVelocity().magnitude() < epsilon) { //Cuando la velocidad es muy pequeña se pone a 0
			o->setVelocity(Vector2D(0, 0));
		}
	}
}
