#pragma once
#include "GameState.h"
#include "checkML.h"


//*CONSTANTES GENERALES*
const int NUM_MENU_TEXT = 4;

//const std::string TEXT_PATHFILE = "..\\images\\";
const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class MainMenuState : public GameState
{

private:
	// Texturas del menú
	Texture* menuTextures[NUM_MENU_TEXT];

	bool menu = true;
	bool loading = false;

public:
	MainMenuState(Game* game);
	
	static void newGame(Game* game);
	static void loadGame(Game* game);
	static void exitGame(Game* game);
	~MainMenuState();
};

