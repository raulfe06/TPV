#include "GameMap.h"
#include <fstream>
#include "PlayState.h"
#include <iostream>
#include "FileFormatError.h"
using namespace std;

// A) CONSTRUCTORA DEL MAPA: APUNTA A <Game>
GameMap::GameMap(PlayState*playState) : PacmanObject(playState)
{
	for (size_t i = 0; i < NUM_MAP_TEXTURES; i++)
	{
		textures[i] = playState->getTexture((enumTextures)i);
	}
}

// C) CARGAMOS EL MAPA LEYÉNDOLO DE FICHERO
void GameMap::loadFromFile(ifstream& file)
{
		int cell;

		// b) Segun la implementación del archivo, leemos la primera fila para obtener las filas y columnas del mapa
		file >> rows >> cols;
		
		
			if (rows > maxR || cols > maxC) throw FileFormatError("El mapa supera los limites [ "
				+ to_string(maxR) + ", " + to_string(maxC) + "]" );

			playState->setCols(this->cols);
			playState->setFils(this->rows);


			destRect.w = (WIN_WIDTH - 200) / playState->getCols();
			destRect.h = (WIN_HEIGHT) / playState->getFils();

			map = new mapCell*[rows];
			for (int i = 0; i < rows; i++)
			{
				map[i] = new mapCell[cols];
			}
			// d) Recorremos la "matriz" del archivo:
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					// 1) Leemos cada numero... 
					file >> cell;
					if (cell > Vitamins) throw FileFormatError("Se ha encontrado una celda con numero: "
						+ to_string(cell) + " cuyo formato es incorrecto");

					// ...y le damos el tipo de celda según el valor del mismo
					setCell(i, j, (mapCell)cell);
					if (cell == 2 || cell == 3)
						this->playState->modifyNumFood(1);
				}
			}
		
		
		
}

// D) GUARDAMOS EL MAPA EN UN FICHERO DE TEXTO
void GameMap::saveToFile(ofstream& file) {
	file << rows <<" "<< cols << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			
			file << map[i][j];
			if (j != cols - 1) {
				file << " ";
			}
		}
		file << endl;
	}
 }

// E) RENDER DE LAS TEXTURAS DEL MAPA
void GameMap::render(SDL_Renderer* renderer) 
{

	// 1) Recorremos la matriz de celdas
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			destRect.x = j * destRect.w;
			destRect.y = i * destRect.h;

			// 2) Miramos el tipo de celda de dicha posición en la matriz, y elegimos la textura:
			textures[(int)map[i][j]]->Render(renderer, destRect);
		}
}

void GameMap::update()
{
	int foodX, foodY;
	if (playState->pacmanEat(foodX, foodY))
		setCell(foodY, foodX, Empty);
}

// F) DEVUELVE EL TIPO DE CELDA EN LA POSICIÓN DADA
mapCell GameMap::getCell(int posX, int posY) const
{
	// *Invertimos para mirar por '[filas][columas]' (map[i][j])
	return map[posY][posX];
}

//G) ACTUALIZA LA CELDA EN LA POSICIÓN DADA
void GameMap::setCell(int posY, int posX, mapCell cellKind) {
	map[posY][posX] = cellKind;
}

// DESTRUCTORA DEL MAPA (MATRIZ DINÁMICA)
GameMap::~GameMap()
{
	if (map != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete map[i];
		}
		delete[] map;
	}
}
