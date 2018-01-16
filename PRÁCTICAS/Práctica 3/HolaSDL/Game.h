#pragma once
#include <list>
#include "GameCharacter.h"
#include "GameMap.h"
#include <iterator>

class SmartGhost;
class Pacman;
class GameStateMachine;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

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

	// Posición de la ventana
	int winX = SDL_WINDOWPOS_CENTERED;
	int winY = winX;

	// Texturas del menú
//	Texture* menuTextures[NUM_MENU_TEXT];

	int delta;

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


	bool getExit() const { return exit; };
	

	SDL_Renderer* getRenderer() { return renderer; };
	GameStateMachine* getStateMachine();

	~Game();

};
