#pragma once
#include "PacmanObject.h"
#include "Texture.h"
#include "SDL.h"
class PlayState;

// Tipos de celda para el mapa
enum mapCell { Empty, Wall, Food, Vitamins };

/*typedef struct {
	// 1) Nombre del archivo de la imagen
	string filename;
	// 2) Fila y columna de la textura (por si estuviera dividida como un sprite sheet)
	int row = 0;
	int col = 0;
} textAtributes;

// Arrays con los atrubitos de cada textura del mapa
const textAtributes TEXTURE_ATRIBUTES[NUM_MAP_TEXTURES] = { {"empty.png",1,1}, { "wall.png", 1, 1 },{ "food.png", 1, 1 },{ "vitamin.png", 1, 1 } };
*/

const int NUM_MAP_TEXTURES = 4; // Casilla vacía, Muro, Comida, Vitamina

const int maxR = 50;
const int maxC = 50;
/*
Clase GameMap: crea la matriz, a partir de la cual se creará y actualizará el nivel

- Crea la matriz dinámica de celdas.
- Crea sus texturas estáticas.
- Se comunica con <Game> -> Indica, actualiza, etc., sus celdas

*/

class Pacman;

class GameMap : public PacmanObject
{
private:
	SDL_Rect destRect;

	// Matriz dinámica de celdas
	mapCell **map = nullptr;

	// Array de texturas del mapa
	Texture* textures[NUM_MAP_TEXTURES];

	// Filas y columnas del mapa
	int rows, cols;
	
public:
	GameMap(PlayState*game);

	 void loadFromFile(ifstream& file);
	 void saveToFile(ofstream& file);

	 void render(SDL_Renderer* renderer);
	 void update();

	 mapCell getCell(int posX, int posY) const;
	 void setCell(int posX, int posY, mapCell cellKind);
	
	
	~GameMap();
};

