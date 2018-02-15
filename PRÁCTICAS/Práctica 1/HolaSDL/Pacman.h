#pragma once
#include "SDL.h"
#include"Texture.h"
#include "checkML.h"


using namespace std;

// *Añadimos la clase para evitar errores de compilación*
class Game;

/*
Clase Pacman: Inicializa a Pacman y controla su dirección, movimiento, vidas, etc.

1) Inicializa sus variables y punteros

2) Se comunica con <Game> -> Se renderiza, actualiza su posición, guarda la siguiente dirección, etc.

*/
class Pacman
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

	// Siguente dirección guardada (hasta hacerse posible el cambio de dirección)
	int nextDirX, nextDirY;

	// Vidas restantes
	int lifes;

	// Posición de la textura del movimiento de Pacman
	int animation = 10;

public:
	// Constructora y destructora de Pacman
	Pacman(int defX, int defY, Texture* texture, int fils, int cols, Game* game);
	Pacman();
	~Pacman();

	// Render de Pacman
	void Render(SDL_Renderer* renderer);

	// Actualización de la posición de Pacman
	void Update();

	// Método para cambiar de dirección
	void SetDir(SDL_Event event);

	// Comprueba si se ha comido algo, y lo procesa según el resultado
	bool Eat(int& foodX, int& foodY) const;

	// Reinicia la posición del Pacman
	void RestartPos() { posX = defX; posY = defY; dirX = nextDirX = 0; dirY = nextDirY = 0; };

	// Métodos de acceso, actualización, etc.,  de los atributos de Pacman
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

