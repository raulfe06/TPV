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

const int NUM_GAME_TEXTURES = 13;
//CONSTANTES DE LOS PUNTOS
enum enumTextures { EmptyTex, WallTex, FoodTex, VitaminsTex , NewGameTex,LoadGameTex,ExitGameTex,ResumeGameTex,PacmanText,GhostText,SmartGhostText,CodeTex,SaveGameTex };

typedef struct {
	// 1) Nombre del archivo de la imagen
	string filename;
	// 2) Fila y columna de la textura (por si estuviera dividida como un sprite sheet)
	int row = 0;
	int col = 0;
} textAtributes;

const textAtributes GAME_TEXTURES[NUM_GAME_TEXTURES] = { { "empty.png",1,1 },{ "wall.png", 1, 1 },{ "food.png", 1, 1 },{ "vitamin.png", 1, 1 },
{ "newGame.png", 1, 1 },{ "loadGame.png", 1, 1 },{ "exitGame.png", 1, 1 },{ "resumeGame.png", 1, 1 },{ "characters.png", 1, 11 },{ "characters.png", 1, 1 }
,{ "characters.png", 1, 9 },{ "saveGame.png", 1, 9 } };

const std::string TEXT_PATHFILE = "..\\images\\";
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

	void initializeTextures();

	Texture* textures[NUM_GAME_TEXTURES];

public:

	Game();

	// Bucle del juego
	void run();
	void handleEvents();
	void update();
	void render();
	Texture* getTexture(enumTextures name);

	bool getExit() const { return exit; };
	

	SDL_Renderer* getRenderer() { return renderer; };
	GameStateMachine* getStateMachine();

	~Game();

};
