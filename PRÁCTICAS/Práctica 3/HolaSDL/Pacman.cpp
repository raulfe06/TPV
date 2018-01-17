#include "Pacman.h"
#include"PlayState.h"
#include <fstream>
#include <iostream>

using namespace std;


Pacman::Pacman()
{
}

// A) CREA A PACMAN 
Pacman::Pacman(PlayState* playState, SDL_Renderer* renderer, int textRow, int textCol) : GameCharacter(playState, renderer, textRow, textCol)
{
}

// B) REDEFINE EL MÉTODO DEL PADRE PARA OBTENER LAS VIDAS
void Pacman::loadFromFile(ifstream& file) {

	GameCharacter::loadFromFile(file);
	this->lives = 3;
}

// C) REDEFINE EL MÉTODO DEL PADRE PARA GUARDAR ENERGÍA Y VIDAS 
void Pacman::saveToFile(ofstream& file)
{
	GameCharacter::saveToFile(file);
	file << endl;
}

// D) REDEFINE EL MÉTODO DEL PADRE PARA ACTUALIZAR LA ANIMACIÓN 
void Pacman::render(SDL_Renderer* renderer)
{
	setAnimation();
	GameCharacter::render(renderer);
}

bool Pacman::handleEvent(SDL_Event& e)
{
	setDir(e);

	return true;
}

// E) DETERMINA LA FILA Y LA COLUMNA DE LA TEXTURA (ES DECIR, DEL SPRITESHEET) QUE HAY QUE PINTAR SEGÚN LA DIRECCIÓN DE PACMAN
void Pacman::setAnimation()
{
	// 1) Comprobamos si está sin niguna dirección y cargamos la textura en parado
	if (dirX == 0 && dirY == 0)
	{
		textRow = 0; textCol = 11;
	}
	// 2) En otro caso, indicamos cada posible textura según la dirección del Pacman 
	else if (dirX == 0)
	{
		if (dirY == 1)
			textRow = 1;
		else
			textRow = 3;
	}

	else if (dirY == 0)
	{
		if (dirX == 1)
			textRow = 0;
		else
			textRow = 2;
	}
	// 3) Ciclamos además su movimiento con la boca abierta y boca cerrada 
	if (textCol == 10)
		textCol = 11;
	else
		textCol = 10;
}

// F) ACTUALIZA LA POSICIÓN DE PACMAN
void Pacman::update() 
{
	if (getEnergy())
		timer();

	// a) Con la dirección siguiente guardada, miramos si podemos avanzar en dicha dirección: 
	if (playState->nextCell(posX, posY, nextDirX, nextDirY, posX, posY))
	{
		// 1) Si es posible, avanzamos y actualizamos la dirección actual:
		dirX = nextDirX;
		dirY = nextDirY;
		// 2) Si no lo es, probamos con la dirección actual que llevábamos:
	}
	else // b) Miramos si con la dirección actual podemos avanzar -> Si podemos, avanza. Si no, se parará
		playState->nextCell(posX, posY, dirX, dirY, posX, posY);

	playState->checkCapture();
}

// G) ACTUALIZA LA DIRECCIÓN SIGUENTE DE PACMAN SEGÚN LA TECLA DE DIRECCIÓN PULSADA
void Pacman::setDir(SDL_Event& event)
{
	// 1) Miramos la pulsación de la tecla:
	if (event.type == SDL_KEYDOWN)
	{
		// a) Dirección X
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
		{
			nextDirX = -1;
			nextDirY = 0;
		}
		else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
		{
			nextDirX = 1;
			nextDirY = 0;
		}

		// b) Dirección Y
		else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
		{
			nextDirX = 0;
			nextDirY = -1;
		}
		else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
		{
			nextDirX = 0;
			nextDirY = 1;
		}
		// 2) Actualizamos la dirección siguente (nextDirX, nextDirY), que queda guardada hasta que se efectúa y pasa a ser la dirección actual (dirX, dirY)
	}
}

// H) COMPRUEBA SI HA COMIDO ALGÚN ELEMENTO DEL MAPA Y PROCESA EL RESULTADO
bool Pacman::eat(int& foodX, int& foodY) 
{
	// 1) Comprobamos si ha alcanzado alguna casilla con comida: 
	if (playState->getCell(posX, posY) == mapCell::Food)
	{
		// a) En ese caso, devolvemos la posición en la que se encuentra
		foodX = posX;
		foodY = posY;

		return true;
	}
	// 2) Si la posición alcanzada contenía una vitamina en su lugar: 
	else if (playState->getCell(posX, posY) == mapCell::Vitamins)
	{
		// a) Devolvemos la posición en la que se encuentra igualmente
		foodX = posX;
		foodY = posY;

		// b) Activamos la energía de Pacman
		pacmanEnergy(true);

		return true;
	}
	// En cualquier otro caso, simplemente devolvemos 'false' ya que no se habrá comido nada
	else
		return false;
}

// I) ACTIVA/DESACTIVA LA ENERGÍA DE PACMAN SEGÚN EL PARÁMETRO 'power', Y REINICIA SU DURACIÓN
void Pacman::pacmanEnergy(bool power)
{
	energyTime = ENERGY_TIME;
	energy = power;
}

// J) CONTADOR PARA EL TIEMPO DE USO DE LA ENERGÍA DE PACMAN
void Pacman::timer()
{
	/*
	Restamos a "EnergyTime" el tiempo de cada tick (Es decir, FRAME_RATE):

	Como el bucle del juego está controlado por el delta, a mayor FRAME_RATE, MENOS ticks de MAYOR duración se harán,
	y a menor FRAME_RATE, M�S ticks de MENOR duración se harán.

	Por tanto, la duración acaba siendo siempre equivalente independientemente de una mayor o menor resta,
	puesto que los ticks, a su vez, aumentan o disminuyen proporcionalmente.
	*/

	if (energyTime > 0)
	{
		energyTime -= FRAME_RATE;
	}
	else
	{
		pacmanEnergy(false);
	}
}



Pacman::~Pacman()
{
}