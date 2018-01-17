#pragma once
#include "Texture.h"
#include "Game.h"
class MenuButton : public GameObject
{
private:
	int x,
		y,
		w,
		h;
	Texture* text;
	
	Game* game;
public:
	MenuButton(Game* game,int x,int y,int w,int h,Texture* tex); 

	bool handleEvent(SDL_Event& e);
	 void render(SDL_Renderer* renderer);
	~MenuButton();
};

