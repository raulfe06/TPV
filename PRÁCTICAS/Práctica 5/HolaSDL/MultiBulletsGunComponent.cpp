#include "MultiBulletsGunComponent.h"
#include <algorithm>



MultiBulletsGunComponent::MultiBulletsGunComponent(Observer* bulletsManager, SDL_Keycode shootKey_, Uint8 numBullets, Uint32 timeInterval_) : 
	GunInputComponent(bulletsManager), shootKey_(shootKey_), numBullets_(numBullets), timeInterval_(timeInterval_), tiempoDisparo_(0)
{
}


MultiBulletsGunComponent::~MultiBulletsGunComponent()
{
}

void MultiBulletsGunComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{

	Fighter* f = static_cast<Fighter*>(o);

	Vector2D p, v, d;
	double w, h;

	w = o->getWidth();
	h = o->getHeight();
	d = o->getDirection();
	v = o->getVelocity();
	p = o->getPosition();
	Vector2D auxPos{ w / 2, h / 2 };
	auxPos = p + auxPos; // +d * (h / 2); */

	Vector2D auxVel(d*max(v.magnitude() * 5, 2.0));

	if (event.type == SDL_KEYDOWN)
	{// time + timeInterval_ < timeInterval_ + tiempoDisparo_

		if (event.key.keysym.sym == shootKey_ && time > tiempoDisparo_ + timeInterval_)
		{
			tiempoDisparo_ = time;

			double angle = 360.0 / numBullets_;
			for (size_t i = 0; i < numBullets_; i++)
			{
				auxVel.rotate(angle);
				send(&FighterIsShooting(f, auxPos, auxVel));
			}
		}
	}
}
