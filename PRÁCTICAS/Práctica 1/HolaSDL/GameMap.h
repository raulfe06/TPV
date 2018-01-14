#pragma once
#include "SDL.h"
#include"Texture.h"
#include "checkML.h"


using namespace std;

// *Añadimos la clase para evitar errores de compilación*
class Game;

// *Cada tipo de celda posible para el mapa*
enum mapCell { Empty, Wall, Food, Vitamins };
/*
Clase GameMap: crea la matriz, a partir de la cual se creará y actualizará el nivel

1) Crea la matriz dinámica de celdas.
2) Crea sus texturas estáticas.
3) Se comunica con <Game> -> Indica, actualiza, etc., sus celdas

*/
class GameMap
{
private:
	// Puntero al juego
	Game* game = nullptr;

	// Matriz dinámica de celdas
	mapCell **map = nullptr;

	// Rectángulo de destino en el que se pintará cada textura
	SDL_Rect destRect;
	int fils, cols;
public:
	// Constructora y destructora del mapa
	GameMap(int fils, int cols, Game* game);
	~GameMap();

	// Render de los elementos del mapa
	void Render(SDL_Renderer* renderer,Texture* textures[], int fils, int cols);

	// Metodos para acceder, actualizar, etc., las celdas del mapa
	mapCell GetCell(int posX, int posY) const;
	void SetCell(int posX, int posY, mapCell cellKind);
};
