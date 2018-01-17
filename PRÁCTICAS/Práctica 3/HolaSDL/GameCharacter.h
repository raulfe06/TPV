#pragma once
#include "SDL.h"
#include "Texture.h"
#include "PacmanObject.h"

//class Game;

/*
Clase GameCharacter: base para los personajes del juego, conteniendo todo lo común para ellos

- Contiene variables y punteros comunes -> textura, SDL_Rect, posición, etc.

- Define métodos con la parte común para Pacman y los fantasmas -> render, carga desde fichero, etc.

- Heredan de ella: <Pacman> y <Ghost>

*/
class GameCharacter : public PacmanObject
{
protected:

	// Textura propia del personaje
	Texture* texture = nullptr;

	// Fila y columna de la imagen cargada
	int textRow, textCol;

	// Rectángulo de destino en el que se pintará la textura
	SDL_Rect destRect;

	// Posición y dirección del personaje
	int posX, posY;
	int defX, defY;
	int dirX, dirY;
	
	// MÉTODOS
	GameCharacter(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol);
	GameCharacter();
	
	virtual void setAnimation() = 0;

	virtual ~GameCharacter() = 0;

public:
	// Métodos virtuales puros -> sin parte común en las clases hijas
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);

	virtual void render(SDL_Renderer* renderer);
	virtual void update() = 0; 


	virtual void restartPos() { posX = defX; posY = defY; dirX = dirY = 0; };
	int getPosX() const { return posX; };
	int getPosY() const { return posY; };
	int getDefX() const { return defX; };
	int getDefY() const { return defY; };
};

