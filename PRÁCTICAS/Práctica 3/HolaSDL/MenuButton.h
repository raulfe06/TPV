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
	MenuButton(Game* game,int x,int y,int w,int h) : game(game), x(x), y(y), w(w), h(h) {}; //Hay que pasarle la textura y darle valor a text
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);

	void render();
	~MenuButton();
};

