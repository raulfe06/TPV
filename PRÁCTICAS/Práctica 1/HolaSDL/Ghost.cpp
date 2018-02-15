#include "Ghost.h"
#include "Game.h"
#include "Texture.h"


using namespace std;

// *Constructora por defecto*
Ghost::Ghost()
{

}

// A) INICALIZA LAS VARIABLES DEL FANTASMA, SUS PUNTEROS, ETC.
Ghost::Ghost(int defX, int defY, int fils, int cols, Game* game, Texture* texture)
{
	// a) Determinamos el tamaño del rectángulo destino para la textura del fantasma
	destRect.w = WIN_WIDTH / cols;
	destRect.h = (WIN_HEIGHT -100)/ fils;

	// b) Damos valor a la posición inicial en el mapa del fantasma
	this->defX = defX;
	this->defY = defY;

	
	// c) Inicializamos su posición actual con dicha posición a su vez, y sus posibles direcciones a '0'
	this->posX = defX;
	this->posY = defY;

	numDirs = 0;

	// d) Apuntamos a su textura y al juego
	this->game = game;
	this->texture = texture;

}

// B) REALIZA EL RENDER DEL FANTASMA EN SU RESPECTIVA POSICIÓN, Y TENIENDO EN CUENTA LA ENERGÍA DE PACMAN
void Ghost::Render(SDL_Renderer* renderer, int row, int col, bool power) {
	// a) Le asignamos la posición al rectángulo de destino según el alto y ancho del rectángulo (el cual depende de las dimensiones de la ventana)
	destRect.x = posX * destRect.w;
	destRect.y = posY * destRect.h;

	// b) Renderizamos su textura en el rectángulo:

	if(!power) // 1) Si la energía de Pacman NO está activa, renderizamos la textura normal del fantasma 
	texture->RenderFrame(renderer, row, col, destRect);
	else // 2) Si estuviera activa, entonces usamos la textura del fantasma asustado 
		texture->RenderFrame(renderer, 0, 12, destRect);
}


// C) ELIGE UNA DIRECCIÓN Y MUEVE AL FANTASMA
void Ghost::Update()
{
	ChooseDir();

	// a) Mueve al fantasma
	game->NextCell(posX, posY, dirX, dirY, posX, posY);

	// b) Comprobacion de colisiones entre el fantasma y pacman

}


// D) OBTIENE LAS POSIBLES DIRECCIONES A TOMAR POR EL FANTASMA
void Ghost::PossibleDirs(int& numDirs)
{
	// 1) Reiniciamos las posiciones por si estuvieran ocupadas anteriormente
	numDirs = 0;
	posDirs.clear();

	direcciones dir;
	int nextPosX, nextPosY;

	// 2) Comprobamos para cada dirección si el fantasma puede moverse. Es decir, si no hay muro ni hay otro fantasma:
	for (int i = 0; i < NUM_DIRS; i++)
	{
		if (game->NextCell(posX, posY, AllDirs[i].x, AllDirs[i].y, nextPosX, nextPosY) && !game->ExistGhost(nextPosX, nextPosY))
		{
			// En caso de ser accesible la posición, añadimos la dirección en el vector
			dir.x = AllDirs[i].x;
			dir.y = AllDirs[i].y;
			posDirs.push_back(dir);
			numDirs++;
		}
	}
}


// E) ESCOGE UNA DIRECCIÓN ENTRE LAS POSIBLES AL AZAR
void Ghost::ChooseDir() 
{
	direcciones d;
	int n = 0;
	int i = 0;
	
	bool eliminado = false;

	// 1) Obtenemos las posibles direcciones a tomar
	PossibleDirs(numDirs);

	// 2) Comprobamos que haya alguna dirección 
	if (numDirs != 0)
	{
		// a) En caso de haberla, miramos si hay más de una
		 if (numDirs > 1)
		{
			 // Si hubiera más de una:
			while (i < posDirs.size() && !eliminado)
			{
				// 1) Eliminamos la dirección contraria si ésta fuera una de las posibles direcciones
				if (posDirs[i].x == -dirX && posDirs[i].y == -dirY) {
					posDirs.erase(posDirs.begin() + i);
					numDirs--;
					eliminado = true;
				}
				i++;
			}
			// 2) Escogemos entre las otras direcciones restantes aleatoriamente
			n = rand() % (numDirs);
		}
		 // b) Si solo hubiera una dirección, asignamos esa (es decir, la "n = 0" por defecto). En otro caso, asignaríamos la de la posición aleatoria ("n = random")
		 dirX = posDirs[n].x;
		 dirY = posDirs[n].y;
	}
}

// DESTRUCTORA POR DEFECTO
Ghost::~Ghost()
{
}
