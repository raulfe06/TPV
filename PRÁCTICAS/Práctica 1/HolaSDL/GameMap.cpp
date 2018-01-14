#include "GameMap.h"
#include"Game.h"
#include"Texture.h"


using namespace std;

// A) CONSTRUCTORA DEL MAPA: CREA LA MATRIZ DIN�MICA DE CELDAS Y APUNTA A <Game>
GameMap::GameMap(int fils, int cols, Game* game)
{
	this->fils = fils;
	this->cols = cols;

	// b) Creamos la matriz din�mica de celdas
	map = new mapCell*[fils];
	for (int i = 0; i < fils; i++)
	{
		map[i] = new mapCell[cols];
	}

	// c) Apuntamos al juego
	this->game = game;
}


// B) REALIZA EL RENDER DE LOS ELEMENTOS DEL MAPA EN SUS RESPECTIVAS POSICIONES
void GameMap::Render(SDL_Renderer* renderer,Texture* textures[], int fils, int cols)
{
	// Recorremos la matriz del mapa:
	for (int i= 0; i < fils; i++)
		for (int j = 0; j < cols; j++)
		{
			// 1) Le asignamos la posici�n al rect�ngulo de destino seg�n el alto y ancho del rect�ngulo (el cual depende de las dimensiones de la ventana)
			destRect.x = j * destRect.w;
			destRect.y = i * destRect.h;

			// 2) Miramos el tipo de celda de dicha posici�n en la matriz, y elegimos la textura:
		//	textures[(int)map[i][j]]->Render(renderer, destRect);
			switch (map[i][j])
			{
			case Wall:
				textures[0]->Render(renderer, destRect);
				break;
			case Food:
				textures[1]->Render(renderer, destRect);
				break;
			case Vitamins:
				textures[2]->Render(renderer, destRect);
				break;
			}
		}
}


// C) DEVUELVE EL TIPO DE CELDA QUE HAY EN LA MATRIZ EN LA POSICI�N INDICADA
mapCell GameMap::GetCell(int posX, int posY) const
{
	// *Invertimos para mirar por '[filas][columas]' (map[i][j])
	return map[posY][posX];
}


// D) ACTUALIZAMOS EL TIPO DE CELDA DE LA POSICI�N DADA
void GameMap::SetCell(int posY, int posX, mapCell cellKind)
{
	map[posY][posX] = cellKind;
}

// E) DESTRUCTORA DEL MAPA (MATRIZ DIN�MICA)
GameMap::~GameMap()
{
	if (map != nullptr) {
		for (int i = 0; i < fils; i++)
		{
			delete map[i];
		}
		delete[] map;
	}
}
