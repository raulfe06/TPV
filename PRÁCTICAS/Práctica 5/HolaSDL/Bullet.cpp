#include "Bullet.h"


Bullet::Bullet(SDLGame* game) : Container(game)
{
	setActive(true);
	setWidth(defBWidth);
	setHeight(defBHeight);
}


Bullet::~Bullet()
{
}

void Bullet::setFighterId(int id)
{
	fighterId_ = id;
}

int Bullet::getFighterId()
{
	return fighterId_;
}

bool Bullet::outOfWindow()
{
	bool out = false;

	if (getPosition().getX() >= game_->getWindowWidth()) out = true;

	else if (getPosition().getX() <= 0) out = true;

	if (getPosition().getY() >= game_->getWindowHeight()) out = true;

	else if (getPosition().getY() <= 0) out = true;

	return out;

}
