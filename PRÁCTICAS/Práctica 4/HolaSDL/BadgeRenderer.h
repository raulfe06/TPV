#pragma once
#include "RenderComponent.h"
class BadgeRenderer :
	public RenderComponent
{
public:
	BadgeRenderer(SDLGame* game);
	~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	SDL_Rect destRect_;
	Texture* badgeIMG_;
};

