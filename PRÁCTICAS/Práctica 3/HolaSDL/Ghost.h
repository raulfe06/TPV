#pragma once
#include <vector>
#include "GameCharacter.h"
#include <fstream>

using namespace std;

// CONSTANTES: 
const int NUM_DIRS = 4;

/*
Clase Ghost: Inicializa un fantasma y controla su dirección, movimiento, etc.

- Contiene variables propias de un fantasma -> estado: asustado o valiente, posibles direcciones, etc.

- Define (y redefine) métodos propios de Pacman -> render propio de su movimiento, update, etc.

- Hereda de ella: <SmartGhost>

*/

class Pacman;
class Ghost : public GameCharacter
{
protected:
	// Atributo estático -> Va a ser el mismo para todas las instancias de la clase. De esta manera, todos los fantasmas se "asustan" mirando a la misma variable
	static bool frightened;


	// Puntero a Pacman para conocer su posición en el mapa
	Pacman* pacman = nullptr;


	// Tipo de fantasma -> normal (0) o inteligente (1)
	int ghostType;

	// Posición en el spritesheet para cada estado
	int frightenedFrame;
	int braveFrame;

	// Direcciones posibles a tomar por el fantasma
	int numDirs;

	// Struct de pares formado por la dirección en el 'eje x' y en el 'eje y'
	struct direcciones {
		int x;
		int y;
	};
	// Array auxuliar con las 4 posibles direcciones a tomar
	const direcciones AllDirs[NUM_DIRS] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

	// Vector formado por las posibles direcciones a tomar por el fantasma
	std::vector<direcciones> posDirs;

	// MÉTODOS:

	void chooseDir();
	void possibleDirs(int& numDirs);
	virtual void setAnimation();
	
public:
	Ghost(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol, Pacman* pac);

	virtual void render(SDL_Renderer* renderer);
	virtual void update();

	static void toggleFear(bool afraid) { frightened = afraid; };

	int getType()const { return ghostType; };
	void setType(int type) { this->ghostType = type; };
	void saveToFile(ofstream& file);

	~Ghost();
};

