#pragma once
#include "Texture.h"
#include "Game.h"
class MenuButton
{
private:
	int x,
		y,
		w,
		h;
	Texture* text;
	
	Game* game;
public:
	MenuButton(Game* game,int x,int y,int w,int h) : game(game), x(x), y(y), w(w), h(h) {};
	void render();
	~MenuButton();
};

