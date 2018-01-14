#pragma once
#include "SDL.h"
#include "Texture.h"
#include <vector>
#include "checkML.h"


using namespace std;

// *A�adimos la clase para evitar errores de compilaci�n*
class Game;

/*
Clase Ghost: Inicializa un fantasma y controla su direcci�n, movimiento, etc.

1) Inicializa sus variables y punteros

2) Se comunica con <Game> -> Se renderiza, actualiza su posici�n, guarda la siguiente direcci�n, etc.

*/
const int NUM_DIRS = 4;

class Ghost
{
private:

	Texture* texture = nullptr;
	Game* game = nullptr;

	SDL_Rect destRect;

	// Posici�n inicial
	int defX, defY;

	// Posici�n actual
	int posX, posY;

	// Direcci�n actual
	int dirX, dirY;

	// Numero de direcciones posibles a tomar
	int numDirs;

	// Struct de pares formado por la direcci�n en el 'eje x' y en el 'eje y'
	struct direcciones {
		int x = 0;
		int y = 0;
	};
	// Array auxuliar con las 4 posibles direcciones a tomar
	const direcciones AllDirs[NUM_DIRS] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	// Vector formado por las posibles direcciones a tomar por el fantasma
	vector <direcciones> posDirs;

	// M�TODOS PRIVADOS: 

	// Obtiene las posibles direcciones a tomar por el fantasma 
	void PossibleDirs(int& numDirs);

	// De las posibles direcciones, escoge una al azar
	void ChooseDir();

public:
	// Constructora y destructora del fantasma
	Ghost(int defX, int defY, int fils, int cols, Game* game, Texture* texture);
	Ghost();
	~Ghost();

	// Render del fantasma 
	void Render(SDL_Renderer* renderer, int row, int col, bool power);

	// Elige una direcci�n y mueve al fantasma
	void Update();

	// Reinicia la posici�n del fantasma
	void RestartPos() { posX = defX; posY = defY; };

	// M�todos de acceso, actualizaci�n, etc.
	int GetPosX() const { return posX; };
	int GetPosY() const { return posY; };	

	int GetDefX() const { return defX; };
	int GetDefY() const { return defY; };

	void SetDefX(int x) { this->defX = x; };
	void SetDefY(int y) { this->defY = y; };

};
