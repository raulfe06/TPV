#pragma once
#include <list>
#include "GameCharacter.h"
#include "GameMap.h"
//#include "Pacman.h"
#include <iterator>

class SmartGhost;
class Pacman;

//*CONSTANTES GENERALES*

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int OFFSET = 200;
const int NUM_MENU_TEXT = 4;


//CONSTANTES DE LOS PUNTOS
const int FOOD_POINTS = 1;
const int NORMAL_GHOST_POINTS = 50;
const int INTELLI_GHOST_POINTS = 100;

const int NUM_TOTAL_LEVELS = 3;
const int FRAME_RATE = 160; // milliseconds per frame -> 6 frames/s
const std::string TEXT_PATHFILE = "..\\images\\";
const std::string menuNames [NUM_MENU_TEXT] =  { "newGame.png","loadGame.png","menu.png","code.png" };


class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Texturas del menú
	Texture* menuTextures[NUM_MENU_TEXT];

	// Lista de personajes del juego
	std::list<GameCharacter*> characters;



	// *BOOLEANOS DE CONTROL*
	bool exit = false;

public:

	// Bucle del juego
	void run();
	void handleEvents();
	void update();
	void render();

};
