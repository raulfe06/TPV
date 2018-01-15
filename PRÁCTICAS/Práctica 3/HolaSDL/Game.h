#pragma once
#include <list>
#include "GameCharacter.h"
#include "GameMap.h"
#include <iterator>

class SmartGhost;
class Pacman;
class GameStateMachine;

//*CONSTANTES GENERALES*
//const int NUM_MENU_TEXT = 4;


//CONSTANTES DE LOS PUNTOS
//const std::string TEXT_PATHFILE = "..\\images\\";
//const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Texturas del menú
//	Texture* menuTextures[NUM_MENU_TEXT];

	// *BOOLEANOS DE CONTROL*
	bool exit = false;

	GameStateMachine* stateMachine;
	PlayState* test;

public:

	Game();
	// Bucle del juego
	void run();
	void handleEvents();
	void update();
	void render();

};
