#pragma once
#include "SDL.h"
#include "Texture.h"
#include <vector>
#include "checkML.h"


using namespace std;

// *Añadimos la clase para evitar errores de compilación*
class Game;

/*
Clase Ghost: Inicializa un fantasma y controla su dirección, movimiento, etc.

1) Inicializa sus variables y punteros

2) Se comunica con <Game> -> Se renderiza, actualiza su posición, guarda la siguiente dirección, etc.

*/
const int NUM_DIRS = 4;

class Ghost
{
private:

	Texture* texture = nullptr;
	Game* game = nullptr;

	SDL_Rect destRect;

	// Posición inicial
	int defX, defY;

	// Posición actual
	int posX, posY;

	// Dirección actual
	int dirX, dirY;

	// Numero de direcciones posibles a tomar
	int numDirs;

	// Struct de pares formado por la dirección en el 'eje x' y en el 'eje y'
	struct direcciones {
		int x = 0;
		int y = 0;
	};
	// Array auxuliar con las 4 posibles direcciones a tomar
	const direcciones AllDirs[NUM_DIRS] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	// Vector formado por las posibles direcciones a tomar por el fantasma
	vector <direcciones> posDirs;

	// MÉTODOS PRIVADOS: 

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

	// Elige una dirección y mueve al fantasma
	void Update();

	// Reinicia la posición del fantasma
	void RestartPos() { posX = defX; posY = defY; };

	// Métodos de acceso, actualización, etc.
	int GetPosX() const { return posX; };
	int GetPosY() const { return posY; };	

	int GetDefX() const { return defX; };
	int GetDefY() const { return defY; };

	void SetDefX(int x) { this->defX = x; };
	void SetDefY(int y) { this->defY = y; };

};
