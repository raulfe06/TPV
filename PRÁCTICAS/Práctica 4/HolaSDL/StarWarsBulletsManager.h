#pragma once
#include "BulletsManager.h"
class StarWarsBulletsManager :
	public BulletsManager, public GameObject
{
public:
	StarWarsBulletsManager();
	~StarWarsBulletsManager();
	void shoot(GameObject* o, Vector2D p, Vector2D v);
	void handleInput(Uint32 time, const SDL_Event& event) {};
	void update(Uint32 time);
	void render(Uint32 time);
private:
	std::vector<GameObject*> bullets;
};

