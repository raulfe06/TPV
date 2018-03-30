#pragma once
#include "RenderComponent.h"
class GameMsgRenderer :
	public RenderComponent
{
public:
	GameMsgRenderer(SDLGame* game, std::string text);
	~GameMsgRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	Texture * text_;
	SDLGame* game_;
	SDL_Rect dest_;
};

