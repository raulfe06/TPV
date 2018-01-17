#include "GameCharacter.h"
#include"PlayState.h"
#include <fstream>
#include "FileFormatError.h"
#include <iostream>

using namespace std;
GameCharacter::GameCharacter()
{
}

// A) SE INICIALIZA A PARTIR DE <PacmanObject>, CREA LA TEXTURA DEL PERSONAJE Y OBTIENE LAS MEDIDAS DE SU RECTÁNGULO DESTINO
GameCharacter::GameCharacter(PlayState* game, SDL_Renderer* renderer, int row, int col) : PacmanObject(game), textRow(row), textCol(col)
{
	// 1) Creamos la textura, cargándola del spritesheet de personajes
	texture = new Texture();
	texture->Load(renderer, "..\\images\\characters1.png", 4, 14);

	// 2) Obtenemos las medidas del rectángulo de destino, donde se pintará la textura cargada 
	destRect.w = (WIN_WIDTH-OFFSET) / game->getCols();
	destRect.h = (WIN_HEIGHT) / game->getFils();
}

// B) PARTE COMÚN DE LA CARGA DE FICHERO -> OBTIENE POSICIONES Y DIRECCIÓN
void GameCharacter::loadFromFile(ifstream& file)
{
	int aux;
	// Posición actual
	file >> aux;
	posY = aux;
	file >> aux;
	posX = aux;

	// Posición inicial
	file >> aux;
	defY = aux;
	file >> aux;
	defX = aux;

	// Dirección actual
	file >> aux;
	dirY = aux;
	file >> aux;
	dirX = aux;
	try {
		if (dirY > 1 || dirY < -1) throw FileFormatError("Direccion Y del objeto incorrectas, se ha asignado DirY = 1");
	}
	catch (FileFormatError& e) {
		cout << e.what() << endl;
		dirY = 1;
	}
	try {
		if (dirX > 1 || dirX < -1) throw FileFormatError("Direccion X del objeto incorrectas, se ha asignado DirX = 1");
	}
	catch (FileFormatError& e) {
		cout << e.what() << endl;
		dirX = 1;
	}
}

// C) PARTE COMÚN DEL GUARDADO -> GUARDA POSICIONES Y DIRECCIÓN
void GameCharacter::saveToFile(ofstream& file)
{
	file << this->posY << " " << this->posX << " " <<
		this->defY << " " << this->defX << " " << this->dirX << " " << this->dirY;
}

// D) PARTE COMÚN DEL RENDER -> CALCULA LA POSICIÓN DE DESTINO, Y RENDERIZA LA TEXTURA COMO TAL
void GameCharacter::render(SDL_Renderer* renderer) 
{
	destRect.x = posX * destRect.w;
	destRect.y = posY * destRect.h;
	
	texture->RenderFrame(renderer, textRow, textCol, destRect);
	//texture->Render(renderer, destRect);
}


// DESTRUCTORA -> LIBERA LA TEXTURA
GameCharacter::~GameCharacter()
{
	game = nullptr;
	texture->Free();
}