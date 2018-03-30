#pragma once
#include "RenderComponent.h"
class BadgeRenderer :
	public RenderComponent
{
	const int BADGE_SIZE = 40;

public:
	BadgeRenderer(SDLGame* game);
	~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	SDL_Rect destRect_;
	Texture* badgeIMG_;
};

