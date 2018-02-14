#pragma once
#include "GameCharacter.h"
#include "GameMap.h"
#include "checkML.h"


class SmartGhost;
class Pacman;
class GameStateMachine;

//*CONSTANTES GENERALES*
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

const int FRAME_RATE = 160; // milliseconds per frame -> 6 frames/s

const int NUM_GAME_TEXTURES = 17;
enum enumTextures { EmptyTex, WallTex, FoodTex, VitaminsTex, NewGameTex, LoadGameTex, ExitGameTex, ResumeGameTex, 
	CharactersText, SaveGameTex, MainMenuText, CodeText,MenuBACK,PlayStateBACK,PauseBACK,VictoryBack,DefeatBack };

typedef struct {
	// 1) Nombre del archivo de la imagen
	string filename;
	// 2) Fila y columna de la textura (por si estuviera dividida como un sprite sheet)
	int row = 0;
	int col = 0;
} textAtributes;

const textAtributes GAME_TEXTURES[NUM_GAME_TEXTURES] = { { "empty.png",1,1 },{ "wall.png", 1, 1 },{ "food.png", 1, 1 },{ "vitamin.png", 1, 1 },
{ "newGame.png", 1, 1 },{ "loadGame.png", 1, 1 },{ "exitGame.png", 1, 1 },{ "resumeGame.png", 1, 1 },{ "characters.png", 4, 14 },{ "saveGame.png", 1, 1 },{ "mainMenu.png", 1, 1 },{ "code.png", 1, 1 }
,{ "menuBack.png", 1, 1 },{ "playBack.png", 1, 1 },{ "pauseBack.png", 1, 1 },{ "victoryBack.png", 1, 1 },{ "defeatBack.png", 1, 1 } };

const std::string TEXT_PATHFILE = "..\\images\\";


class MainMenuState;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Posición de la ventana
	int winX = SDL_WINDOWPOS_CENTERED;
	int winY = winX;

	// Texturas del menú
	Texture* textures[NUM_GAME_TEXTURES];

	int delta;

	// *BOOLEANOS DE CONTROL*
	bool exit = false;

	GameStateMachine* stateMachine;

public:

	Game();

	// Bucle del juego
	void run();
	void handleEvents();
	void render();

	GameStateMachine* getStateMachine();

	Texture* getTexture(enumTextures name);
	SDL_Renderer* getRenderer() const { return renderer; };

	void initializeTextures();
	void EXIT() { exit = true; };

	~Game();

};
