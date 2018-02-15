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
	// a) Determinamos el tama�o del rect�ngulo destino para la textura de Pacman
	destRect.w = WIN_WIDTH / cols;
	destRect.h = (WIN_HEIGHT -100)/ fils;

	// b) Damos valor a la posici�n inicial en el mapa de Pacman
	this->defX = defX;
	this->defY = defY;

	// c) Inicializamos su posici�n actual con dicha posici�n a su vez, su direcci�n y su n�mero de vidas
	posX = defX;
	posY = defY;

	dirX = nextDirX = 0;
	dirY = nextDirY = 0;

	lifes = 3;

	// d) Apuntamos a su textura y al juego
	this->texture = texture;
	this->game = game;
}


// B) REALIZA EL RENDER DE PACMAN EN SU RESPECTIVA POSICI�N
void Pacman::Render(SDL_Renderer* renderer) 
{
	int fil;

	// a) Le asignamos la posici�n al rect�ngulo de destino seg�n el alto y ancho del rect�ngulo (el cual depende de las dimensiones de la ventana)
	destRect.x = posX * destRect.w;
	destRect.y = posY * destRect.h;
	// b) Renderizamos su textura en el rect�ngulo
	SetAnimation(fil);
	texture->RenderFrame(renderer, fil, animation, destRect);
	 
}


// C) ACTUALIZA LA POSICI�N DE PACMAN
void Pacman::Update()
{
	// a) Con la direcci�n siguiente guardada, miramos si podemos avanzar en dicha direcci�n: 
	if (game->NextCell(posX, posY, nextDirX, nextDirY, posX, posY))
	{
		// 1) Si es posible, avanzamos y actualizamos la direcci�n actual:
		dirX = nextDirX;
		dirY = nextDirY;
		// 2) Si no lo es, probamos con la direcci�n actual que llev�bamos:
	}
	else // b) Miramos si con la direcci�n actual podemos avanzar -> Si podemos, avanza. Si no, se parar�
		game->NextCell(posX, posY, dirX, dirY, posX, posY);
}


// D) ACTUALIZA LA DIRECCI�N SIGUENTE DE PACMAN SEG�N LA TECLA DE DIRECCI�N PULSADA
void Pacman::SetDir(SDL_Event event)
{
	// 1) Miramos la pulsaci�n de la tecla:
	if (event.type == SDL_KEYDOWN)
	{
		// a) Direcci�n X
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

		// b) Direcci�n Y
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
		// 2) Actualizamos la direcci�n siguente (nextDirX, nextDirY), que queda guardada hasta que se efect�a y pasa a ser la direcci�n actual (dirX, dirY)
	}
}


// E) COMPRUEBA SI HA COMIDO ALG�N ELEMENTO DEL MAPA Y PROCESA EL RESULTADO
bool Pacman::Eat(int& foodX, int& foodY) const
{
	// 1) Comprobamos si ha alcanzado alguna casilla con comida: 
	if (game->GetCell(posX, posY) == mapCell::Food)
	{
		// a) En ese caso, devolvemos la posici�n en la que se encuentra
		foodX = posX;
		foodY = posY;

		return true;
	}
	// 2) Si la posici�n alcanzada conten�a una vitamina en su lugar: 
	else if (game->GetCell(posX, posY) == mapCell::Vitamins)
	{
		// a) Devolvemos la posici�n en la que se encuentra igualmente
		foodX = posX;
		foodY = posY;

		// b) Activamos la Energ�a de Pacman
		game->PacmanEnegy(true);

		return true;
	}
	// En cualquier otro caso, simplemente devolvemos 'false' ya que no se habr� comido nada
	else
		return false;
}


// F) DETERMINA LA FILA Y LA COLUMNA DE LA TEXTURA (ES DECIR, DEL SPRITE SHEET) QUE HAY QUE PINTAR SEG�N LA DIRECCI�N DE PACMAN
void Pacman::SetAnimation(int& fil)
{
	// 1) Comprobamos si est� sin niguna direcci�n y cargamos la textura en parado
	if (dirX == 0 && dirY == 0)
	{
		fil = 0; animation = 11;
	}
	// 2) En otro caso, indicamos cada posible textura seg�n la direcci�n del Pacman 
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
	// 3) Ciclamos adem�s su movimiento con la boca abierta y boca cerrada 
	if (animation == 10)
		animation = 11;
	else
		animation = 10;
}

// DESTRUCTORA DE PACMAN POR DEFECTO
Pacman::~Pacman()
{

}

