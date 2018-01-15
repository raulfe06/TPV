#pragma once
#include "GameState.h"


//*CONSTANTES GENERALES*
const int NUM_MENU_TEXT = 4;

const std::string TEXT_PATHFILE = "..\\images\\";
const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class MainMenuState : public GameState
{

private:

	// Texturas del menú
	Texture* menuTextures[NUM_MENU_TEXT];

public:
	MainMenuState(SDL_Renderer* renderer);
	~MainMenuState();
};

