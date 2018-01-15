#pragma once
#include "Ghost.h"

// CONSTANTES: 
const int COOLDOWN = 20;
const int CHILD_AGE = 8;
const int ADULT_AGE = 20;
const int MAX_AGE = 100;

class Pacman;

/*
Clase SmartGhost: Controla la edad, posible spawn de un nuevo fantasma, etc.

- Contiene variables propias de un fantasma inteligente -> edad, posible spawn de nuevo fantasma, puntero a Pacman, etc.

- Define (y redefine) métodos propios de Pacman -> render propio de su movimiento, update, etc.

*/
class SmartGhost : public Ghost
{
private:
	// Puntero a Pacman para conocer su posición en el mapa
	Pacman* pacman = nullptr;

	// Edad inicial y actual
	int defAge;
	int age;

	// Tiempo restante hasta otra posible reproducción
	int cooldown;

	// Variables de control
	bool dead;
	bool spawnGhost;

	// MÉTODOS: 
	void possibleDirs(int& numDirs);
	void chooseDir();
	void smartMovement();
	void setAnimation();
	

public:
	SmartGhost(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol, Pacman* pacman, int defX = 0, int defY = 0);

	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file);

	void render(SDL_Renderer* renderer);
	void update();


	bool isDead() { return dead; };
	bool isAdult() { return age >= ADULT_AGE; };

	void restartPos() { GameCharacter::restartPos(); age = defAge; };
	
	~SmartGhost();
};

