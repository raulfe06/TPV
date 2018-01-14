#include "Pacman.h"
#include "Game.h"
#include"Texture.h"

using namespace std;
// *Constructora por defecto*
Pacman::Pacman()
{
}


// A) INICALIZA LAS VARIABLES DE PACMAN, SUS PUNTEROS, ETC.
Pacman::Pacman(int defX, int defY, Texture* texture, int fils, int cols, Game* game)
{
	// a) Determinamos el tamaño del rectángulo destino para la textura de Pacman
	destRect.w = WIN_WIDTH / cols;
	destRect.h = (WIN_HEIGHT -100)/ fils;

	// b) Damos valor a la posición inicial en el mapa de Pacman
	this->defX = defX;
	this->defY = defY;

	// c) Inicializamos su posición actual con dicha posición a su vez, su dirección y su número de vidas
	posX = defX;
	posY = defY;

	dirX = nextDirX = 0;
	dirY = nextDirY = 0;

	lifes = 3;

	// d) Apuntamos a su textura y al juego
	this->texture = texture;
	this->game = game;
}


// B) REALIZA EL RENDER DE PACMAN EN SU RESPECTIVA POSICIÓN
void Pacman::Render(SDL_Renderer* renderer) 
{
	int fil;

	// a) Le asignamos la posición al rectángulo de destino según el alto y ancho del rectángulo (el cual depende de las dimensiones de la ventana)
	destRect.x = posX * destRect.w;
	destRect.y = posY * destRect.h;
	// b) Renderizamos su textura en el rectángulo
	SetAnimation(fil);
	texture->RenderFrame(renderer, fil, animation, destRect);
	 
}


// C) ACTUALIZA LA POSICIÓN DE PACMAN
void Pacman::Update()
{
	// a) Con la dirección siguiente guardada, miramos si podemos avanzar en dicha dirección: 
	if (game->NextCell(posX, posY, nextDirX, nextDirY, posX, posY))
	{
		// 1) Si es posible, avanzamos y actualizamos la dirección actual:
		dirX = nextDirX;
		dirY = nextDirY;
		// 2) Si no lo es, probamos con la dirección actual que llevábamos:
	}
	else // b) Miramos si con la dirección actual podemos avanzar -> Si podemos, avanza. Si no, se parará
		game->NextCell(posX, posY, dirX, dirY, posX, posY);
}


// D) ACTUALIZA LA DIRECCIÓN SIGUENTE DE PACMAN SEGÚN LA TECLA DE DIRECCIÓN PULSADA
void Pacman::SetDir(SDL_Event event)
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


// E) COMPRUEBA SI HA COMIDO ALGÚN ELEMENTO DEL MAPA Y PROCESA EL RESULTADO
bool Pacman::Eat(int& foodX, int& foodY) const
{
	// 1) Comprobamos si ha alcanzado alguna casilla con comida: 
	if (game->GetCell(posX, posY) == mapCell::Food)
	{
		// a) En ese caso, devolvemos la posición en la que se encuentra
		foodX = posX;
		foodY = posY;

		return true;
	}
	// 2) Si la posición alcanzada contenía una vitamina en su lugar: 
	else if (game->GetCell(posX, posY) == mapCell::Vitamins)
	{
		// a) Devolvemos la posición en la que se encuentra igualmente
		foodX = posX;
		foodY = posY;

		// b) Activamos la Energía de Pacman
		game->PacmanEnegy(true);

		return true;
	}
	// En cualquier otro caso, simplemente devolvemos 'false' ya que no se habrá comido nada
	else
		return false;
}


// F) DETERMINA LA FILA Y LA COLUMNA DE LA TEXTURA (ES DECIR, DEL SPRITE SHEET) QUE HAY QUE PINTAR SEGÚN LA DIRECCIÓN DE PACMAN
void Pacman::SetAnimation(int& fil)
{
	// 1) Comprobamos si está sin niguna dirección y cargamos la textura en parado
	if (dirX == 0 && dirY == 0)
	{
		fil = 0; animation = 11;
	}
	// 2) En otro caso, indicamos cada posible textura según la dirección del Pacman 
	else if (dirX == 0)
	{
		if (dirY == 1)
			fil = 1;
		else
			fil = 3;
	}

	else if (dirY == 0)
	{
		if (dirX == 1)
			fil = 0;
		else
			fil = 2;
	}
	// 3) Ciclamos además su movimiento con la boca abierta y boca cerrada 
	if (animation == 10)
		animation = 11;
	else
		animation = 10;
}

// DESTRUCTORA DE PACMAN POR DEFECTO
Pacman::~Pacman()
{

}

