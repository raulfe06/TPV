#pragma once
#include <fstream>
#include "SDL.h"

using namespace std;

class Game;

/*
Clase GameObject: clase abstracta

- Inicializa el puntero a <Game>

- Heredan de ella: <GameCharacter> y <GameMap>

*/
class GameObject
{
protected:
	Game* game = nullptr;

	GameObject(Game* game);
	GameObject();

	// Métodos virtuales puros -> Necesitan ser (re)definidos por las clases hijas 
	virtual void render(SDL_Renderer* renderer) = 0;

	virtual void loadFromFile(ifstream& file) = 0;
	virtual void saveToFile(ofstream& file) = 0;

	virtual ~GameObject() = 0;
};