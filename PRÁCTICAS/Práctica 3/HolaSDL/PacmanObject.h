#pragma once
#include <fstream>
#include "SDL.h"
#include "GameObject.h"
#include "checkML.h"

using namespace std;

class PlayState;


/*
Clase PacmanObject: clase abstracta

- Inicializa el puntero a <Game>

- Heredan de ella: <GameCharacter> y <GameMap>

*/
class PacmanObject : public GameObject
{
protected:

	PlayState* playState;

	PacmanObject(PlayState* playState);
	PacmanObject() {};

	// Métodos virtuales puros -> Necesitan ser (re)definidos por las clases hijas 
	

	virtual void loadFromFile(ifstream& file) = 0;
	virtual void saveToFile(ofstream& file) = 0;

public:
	virtual void update() {};
	virtual bool handleEvent(SDL_Event& e) { return true; };
	virtual void render(SDL_Renderer* renderer) {};
	virtual ~PacmanObject() = 0;
};