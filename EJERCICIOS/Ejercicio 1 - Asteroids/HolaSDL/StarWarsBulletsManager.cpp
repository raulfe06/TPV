#include "StarWarsBulletsManager.h"
#include "GameComponent.h"
#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"

StarWarsBulletsManager::StarWarsBulletsManager() 
{
	
}


StarWarsBulletsManager::~StarWarsBulletsManager()
{
}

void StarWarsBulletsManager::shoot(GameObject * o, Vector2D p, Vector2D v)
{
	SDL_Color color = { 255,165,0 };
	GameComponent* auxComp_ =  new GameComponent (o->getGame());
	auxComp_->addRenderComponent(new FillRectRenderer(color));
	auxComp_->addPhysicsComponent(new BasicMotionPhysics());
	auxComp_->setPosition(p);
	auxComp_->setVelocity(v);
	auxComp_->setHeight(10);
	auxComp_->setWidth(10);
	bullets.push_back(auxComp_);

}

void StarWarsBulletsManager::update(Uint32 time)
{
	for (GameObject* o : bullets) {
		if(o->isActive())
		o->update(time);
		
		if (o->getPosition().getX() >= o->getGame()->getWindowWidth()) {
			o->setActive(false);
		}
		else if (o->getPosition().getX() <= 0)
		{
			o->setActive(false);

		}
		if (o->getPosition().getY() >= o->getGame()->getWindowHeight()) 
		{
			o->setActive(false);

		}
		else if (o->getPosition().getY() <= 0)
		{
			o->setActive(false);

		}
		//Habria que poner todo con || pero es un coñazo
	}
}

void StarWarsBulletsManager::render(Uint32 time)
{
	for (GameObject* o : bullets) {
		o->render(time);
	}
}
