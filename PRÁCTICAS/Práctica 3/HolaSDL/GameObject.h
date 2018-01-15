#pragma once
#include <fstream>
#include "SDL.h"

using namespace std;

class PlayState;

/*
Clase GameObject: clase abstracta

- Inicializa el puntero a <Game>

- Heredan de ella: <GameCharacter> y <GameMap>

*/
class GameObject
{
protected:
	PlayState* game = nullptr;

	GameObject(PlayState* game);
	GameObject();

	// Métodos virtuales puros -> Necesitan ser (re)definidos por las clases hijas 
	virtual void render(SDL_Renderer* renderer) = 0;

	virtual void loadFromFile(ifstream& file) = 0;
	virtual void saveToFile(ofstream& file) = 0;

public:
	virtual void update() {};
	virtual bool handleEvent(SDL_Event& e) { return true; };
	virtual ~GameObject() = 0;
};