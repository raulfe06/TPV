#pragma once
#include "SDL.h"
#include"Texture.h"
#include "checkML.h"


using namespace std;

// *A�adimos la clase para evitar errores de compilaci�n*
class Game;

/*
Clase Pacman: Inicializa a Pacman y controla su direcci�n, movimiento, vidas, etc.

1) Inicializa sus variables y punteros

2) Se comunica con <Game> -> Se renderiza, actualiza su posici�n, guarda la siguiente direcci�n, etc.

*/
class Pacman
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

	// Siguente direcci�n guardada (hasta hacerse posible el cambio de direcci�n)
	int nextDirX, nextDirY;

	// Vidas restantes
	int lifes;

	// Posici�n de la textura del movimiento de Pacman
	int animation = 10;

public:
	// Constructora y destructora de Pacman
	Pacman(int defX, int defY, Texture* texture, int fils, int cols, Game* game);
	Pacman();
	~Pacman();

	// Render de Pacman
	void Render(SDL_Renderer* renderer);

	// Actualizaci�n de la posici�n de Pacman
	void Update();

	// M�todo para cambiar de direcci�n
	void SetDir(SDL_Event event);

	// Comprueba si se ha comido algo, y lo procesa seg�n el resultado
	bool Eat(int& foodX, int& foodY) const;

	// Reinicia la posici�n del Pacman
	void RestartPos() { posX = defX; posY = defY; dirX = nextDirX = 0; dirY = nextDirY = 0; };

	// M�todos de acceso, actualizaci�n, etc.,  de los atributos de Pacman
	int GetPosX() const { return posX; };
	int GetPosY() const { return posY; };

	int GetDefX() const { return defX; };
	int GetDefY() const { return defY; };

	void SetDefX(int x) { this->defX = x; };
	void SetDefY(int y) { this->defY = y; };

	int GetLifes() const { return lifes; };
	void SubLifes() { lifes--; };

	void SetAnimation(int& fil);

	void setLifes(int x) { this->lifes = x; };

};

