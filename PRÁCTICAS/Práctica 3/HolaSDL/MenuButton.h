#pragma once
#include "Texture.h"
#include "Game.h"
#include "checkML.h"

const int buttonWidth = 398;
const int buttonHeight = 98;

class MenuButton : public GameObject
{
private:
	int x,
		y,
		w,
		h;
	Texture* text;
	
	typedef void CallBackOnClick(Game* game);

	CallBackOnClick* cbOnClick;

	Game* game;
public:
	MenuButton(Game* game,int x,int y,int w,int h,Texture* tex,CallBackOnClick* callBack); 

	bool handleEvent(SDL_Event& e);
	 void render(SDL_Renderer* renderer);
	~MenuButton();
};

