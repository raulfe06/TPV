#pragma once
#include <fstream>
#include "SDL.h"
#include "checkML.h"

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

	GameObject();

	// Métodos virtuales puros -> Necesitan ser (re)definidos por las clases hijas

public:
	virtual void update() {};
	virtual bool handleEvent(SDL_Event& e) { return true; };
	virtual void render(SDL_Renderer* renderer) {};
	virtual ~GameObject() = 0;
};