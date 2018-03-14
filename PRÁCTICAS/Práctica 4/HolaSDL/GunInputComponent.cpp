#include "GunInputComponent.h"
#include <algorithm>

using namespace std;

GunInputComponent::GunInputComponent(Observer* bulletsManager_, SDL_Keycode shootKey_, Uint8 shotsPerInterval, Uint32 timeInterval_) 
 : bulletsManager_(bulletsManager_),shootKey_(shootKey_),shotsPerInterval_(shotsPerInterval),timeInterval_(timeInterval_), tiempoDisparo_(0)
{

}


GunInputComponent::~GunInputComponent()
{
}

void GunInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Vector2D p, v,d;
	double w, h;

	w = o->getWidth();
	h = o->getHeight();
	d = o->getDirection();
	v = o->getVelocity();
	p = o->getPosition();
	Vector2D auxPos{ w / 2, h / 2 };
	auxPos = p + auxPos + d * (h / 2);
	
	Vector2D auxVel(d*max(v.magnitude() * 5, 2.0));

	
	

	if (event.type == SDL_KEYDOWN ) 
	{// time + timeInterval_ < timeInterval_ + tiempoDisparo_

		if (event.key.keysym.sym == shootKey_ && time > tiempoDisparo_+timeInterval_)
		{
			tiempoDisparo_ = time;
			//bulletsManager_->shoot(o, auxPos, auxVel); //CAMBIAR POR MENSAJE
		}
	}
	
	
}
