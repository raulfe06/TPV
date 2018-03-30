#pragma once
#include "RenderComponent.h"
class LiveRenderer :
	public RenderComponent
{
public:
	LiveRenderer(SDLGame* game);
	~LiveRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	SDL_Rect destRect_;
	Texture* lifeIMG_;
};

