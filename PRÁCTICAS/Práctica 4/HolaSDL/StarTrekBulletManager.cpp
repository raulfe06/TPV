#include "StarTrekBulletManager.h"



StarTrekBulletManager::StarTrekBulletManager(SDLGame* game) : GameObject(game),bulletRenderer_(SDL_Color{ 255,165,0 }),
bulletPhysics_()
{
	
}


StarTrekBulletManager::~StarTrekBulletManager()
{
}

void StarTrekBulletManager::update(Uint32 time)
{
	for (auto it : objs_) {
		if (it->isActive()) {
			it->update(time);
			if (it->outOfWindow())it->setActive(false);
		}

	}
}

void StarTrekBulletManager::render(Uint32 time)
 {
	for (auto it : objs_) {
		if (it->isActive()) it->render(time);
	}
}

Bullet * StarTrekBulletManager::getBullet()
{
	return getObject(game_);
}

void StarTrekBulletManager::initializeObject(Bullet * o)
{
	SDL_Color color = { 255,165,0 };
	o->addRenderComponent(&bulletRenderer_);
	o->addPhysicsComponent(&bulletPhysics_);
	o->setHeight(10);
	o->setWidth(10);
}

void StarTrekBulletManager::receive(Message * msg)
{
	Fighter* auxFighter;
	switch (msg->id_) {
	case ROUND_START:
		makeBulletsInactive();
		break;
	case ROUND_OVER:
		makeBulletsInactive();
		break;
	case BULLET_ASTROID_COLLISION:
		static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		break;
	case BULLET_FIGHTER_COLLISION:
		static_cast<BulletFighterCollision*>(msg)->bullet_->setActive(false);
		break;
	case FIGHTER_SHOOT:
		FighterIsShooting * m = static_cast<FighterIsShooting*>(msg);
		shoot(m->fighter_, m->bulletPosition_, m->bulletVelocity_);
		send(&Message(BULLET_CREATED));
		break;
	}
}

void StarTrekBulletManager::shoot(Fighter * owner, Vector2D position, Vector2D velocity)
{
	Bullet* auxBullet = getBullet();
	auxBullet->setActive(true);
	auxBullet->setPosition(position);
	auxBullet->setVelocity(velocity);

}

void StarTrekBulletManager::makeBulletsInactive()
{
	for (auto it : objs_) {
		it->setActive(false);
	}
}
