#include "GameCharacter.h"
#include "Game.h"
#include <fstream>

using namespace std;
GameCharacter::GameCharacter()
{
}



// A) SE INICIALIZA A PARTIR DE <GameObject>, CREA LA TEXTURA DEL PERSONAJE Y OBTIENE LAS MEDIDAS DE SU RECT�NGULO DESTINO
GameCharacter::GameCharacter(Game* game, SDL_Renderer* renderer, int row, int col) : GameObject(game), textRow(row), textCol(col)
{
	// 1) Creamos la textura, carg�ndola del spritesheet de personajes
	texture = new Texture();
	texture->Load(renderer, "..\\images\\characters1.png", 4, 14);

	// 2) Obtenemos las medidas del rect�ngulo de destino, donde se pintar� la textura cargada 
	destRect.w = (WIN_WIDTH-OFFSET) / game->getCols();
	destRect.h = (WIN_HEIGHT) / game->getFils();
}

// B) PARTE COM�N DE LA CARGA DE FICHERO -> OBTIENE POSICIONES Y DIRECCI�N
void GameCharacter::loadFromFile(ifstream& file)
{
	int aux;
	// Posici�n actual
	file >> aux;
	posY = aux;
	file >> aux;
	posX = aux;

	// Posici�n inicial
	file >> aux;
	defY = aux;
	file >> aux;
	defX = aux;

	// Direcci�n actual
	file >> aux;
	dirY = aux;
	file >> aux;
	dirX = aux;
}

// C) PARTE COM�N DEL GUARDADO -> GUARDA POSICIONES Y DIRECCI�N
void GameCharacter::saveToFile(ofstream& file)
{
	file << this->posY << " " << this->posX << " " <<
		this->defY << " " << this->defX << " " << this->dirX << " " << this->dirY;
}

// D) PARTE COM�N DEL RENDER -> CALCULA LA POSICI�N DE DESTINO, Y RENDERIZA LA TEXTURA COMO TAL
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