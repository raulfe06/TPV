#pragma once
#include "BulletsManager.h"
#include "BasicMotionPhysics.h"
#include "FillRectRenderer.h"

class StarTrekBulletManager :
	public BulletsManager,public GameObject
{
public:
	StarTrekBulletManager(SDLGame* game);
	StarTrekBulletManager() {};
	virtual ~StarTrekBulletManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time) {};
	virtual std::vector<Bullet*>& getBullets() { return objs_; };
private:
	Bullet* getBullet();
	virtual void initializeObject(Bullet* o) {};
	virtual void receive(Message* msg) {};
	virtual void shoot(Fighter* owner, Vector2D position, Vector2D velocity) {};
	FillRectRenderer bulletRenderer_;
	BasicMotionPhysics bulletPhysics_;
};

