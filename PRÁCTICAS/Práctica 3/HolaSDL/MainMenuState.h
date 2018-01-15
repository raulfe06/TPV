#pragma once
#include "GameState.h"


//*CONSTANTES GENERALES*
const int NUM_MENU_TEXT = 4;

//const std::string TEXT_PATHFILE = "..\\images\\";
const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class MainMenuState : public GameState
{

private:

	// Texturas del men�
	Texture* menuTextures[NUM_MENU_TEXT];


	bool menu = true;
	bool loading = false;

public:
	MainMenuState(SDL_Renderer* renderer);

	int checkInsideRect(int x, int y, SDL_Rect rect);
	void mousePress(SDL_MouseButtonEvent& b);
	void renderCode(const int& count);
	void renderMenu();
	void loadMenu();

	~MainMenuState();
};

