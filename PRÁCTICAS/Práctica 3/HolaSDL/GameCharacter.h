#pragma once
#include "SDL.h"
#include "Texture.h"
#include "PacmanObject.h"

//class Game;

/*
Clase GameCharacter: base para los personajes del juego, conteniendo todo lo com�n para ellos

- Contiene variables y punteros comunes -> textura, SDL_Rect, posici�n, etc.

- Define m�todos con la parte com�n para Pacman y los fantasmas -> render, carga desde fichero, etc.

- Heredan de ella: <Pacman> y <Ghost>

*/
class GameCharacter : public PacmanObject
{
protected:

	// Textura propia del personaje
	Texture* texture = nullptr;

	// Fila y columna de la imagen cargada
	int textRow, textCol;

	// Rect�ngulo de destino en el que se pintar� la textura
	SDL_Rect destRect;

	// Posici�n y direcci�n del personaje
	int posX, posY;
	int defX, defY;
	int dirX, dirY;
	
	// M�TODOS
	GameCharacter(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol);
	GameCharacter();
	
	virtual void setAnimation() = 0;

	virtual ~GameCharacter() = 0;

public:
	// M�todos virtuales puros -> sin parte com�n en las clases hijas
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

