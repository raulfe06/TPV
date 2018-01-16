#pragma once
#include "GameState.h"
#include <vector>
#include "MenuButton.h"

//*CONSTANTES GENERALES*
const int NUM_MENU_TEXT = 4;

//const std::string TEXT_PATHFILE = "..\\images\\";
const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class MainMenuState : public GameState
{

private:

	// Texturas del menú
	Texture* menuTextures[NUM_MENU_TEXT]; //Esto no deberia estar en el game??

	SDL_Rect startGame, loadGame, exitGame;

	bool menu = true;
	bool loading = false;

public:
	MainMenuState(Game* game);

	int checkInsideRect(int x, int y, SDL_Rect rect);
	void mousePress(SDL_MouseButtonEvent& b);
	void renderCode(const int& count); //añadirlo a scene y luego quitarlo (?)
	void handleEvent(SDL_Event& e);
	

	~MainMenuState();
};

