#pragma once
#include <list>
#include "GameCharacter.h"
#include "GameMap.h"
#include <iterator>

#include "GameState.h"

class SmartGhost;
class Pacman;

//*CONSTANTES GENERALES*

//const int WIN_WIDTH = 800;
//const int WIN_HEIGHT = 600;
const int OFFSET = 200;
//const int NUM_MENU_TEXT = 4;


//CONSTANTES DE LOS PUNTOS
const int FOOD_POINTS = 1;
const int NORMAL_GHOST_POINTS = 50;
const int INTELLI_GHOST_POINTS = 100;

const int NUM_TOTAL_LEVELS = 3;
//const std::string TEXT_PATHFILE = "..\\images\\";
//const std::string menuNames[NUM_MENU_TEXT] = { "newGame.png","loadGame.png","menu.png","code.png" };


class PlayState : public GameState
{
private:

	SDL_Renderer* renderer = nullptr;

	//SDL_Rect rectNG, rectLG; //destino de new game y load game
	

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
	

public:
	PlayState(Game* game, SDL_Renderer* renderer,bool loadingFile);

	// Lectura y escritura
	void loadFile(std::string filename);
	void saveToFile(string filename);
	void modifyNumFood(int m) { numFood += m; };

	int saveState();

	// Bucle del juego
	void handleEvents(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
	void endLevel();
	bool getExit() const { return exit; };

	// Mapa
	bool nextCell(int x, int y, int dx, int dy, int& nx, int& ny);
	mapCell getCell(int posX, int posY) const;

	void addScore(int amount) { score += amount; };
	void subFood() { numFood--; };


	// Colisiones
	void checkCapture();
	void restartCharacters();
	bool pacmanEat(int& foodX, int& foodY);	


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

