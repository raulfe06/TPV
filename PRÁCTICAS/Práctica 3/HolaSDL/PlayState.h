#pragma once
#include <list>
#include "GameCharacter.h"
#include "GameMap.h"
#include <iterator>

#include "GameState.h"

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
const std::string menuNames[NUM_MENU_TEXT] = { "newGame.png","loadGame.png","menu.png","code.png" };


class PlayState :public GameState
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Posición de la ventana
	int winX = SDL_WINDOWPOS_CENTERED;
	int winY = winX;

	SDL_Rect rectNG, rectLG; //destino de new game y load game

							 // Texturas del menú
	Texture* menuTextures[NUM_MENU_TEXT];

	// Lista de personajes del juego
	std::list<GameCharacter*> characters;

	// Puntero directo a Pacman
	Pacman* pacman = nullptr;

	// Puntero al mapa del juego
	GameMap* map;

	int rows, cols;
	int numFood = 0;

	// Delta time del juego
	int delta;

	int level;
	int score;
	int numGhosts;

	// *BOOLEANOS DE CONTROL*
	bool error = false;
	bool exit = false;
	bool savingState = false;

	bool menu = true;
	bool win = false;
	bool end = false;
	bool loading = false;

public:
	PlayState();

	// Lectura y escritura
	void loadFile(std::string filename);
	void saveToFile(string filename);
	void modifyNumFood(int m) { numFood += m; };


	// Bucle del juego
	int saveState();
	void run();
	void handleEvents();
	void update();
	void render();
	void endLevel();
	bool getExit() const { return exit; };



	// Mapa
	bool nextCell(int x, int y, int dx, int dy, int& nx, int& ny);
	mapCell getCell(int posX, int posY) const;


	// Colisiones
	void checkCapture();
	void restartCharacters();


	// UI
	int checkInsideRect(int x, int y, struct SDL_Rect rect);
	void mousePress(SDL_MouseButtonEvent& b);

	void renderCode(const int& count);
	void renderMenu();
	bool getMenu() const { return menu; };
	void loadMenu();


	// Fantasmas
	bool existGhost(int posX, int posY);
	bool existGhost(SmartGhost* ghost, int posX, int posY, const bool& adult, bool& spawnGhost);
	void spawnGhost(int posX, int posY);


	// Filas y columnas del nivel
	int getFils() const { return rows; };
	int getCols() const { return cols; };
	void setFils(int fils) { this->rows = fils; };
	void setCols(int cols) { this->cols = cols; };


	// Texto
	void renderTexts();
	void createLevelText();
	void createScoreText();
	void createLivesText();

	~PlayState();
};

