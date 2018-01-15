#include "Ghost.h"
#include "PlayState.h"
#include <fstream>

bool Ghost::frightened;


// A) INICALIZA LAS VARIABLES DEL FANTASMA -> UTILIZA LA CONSTRUCTORA DEL PADRE, Y LUEGO INICIALIZA LAS VARIABLES PROPIAS
Ghost::Ghost(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol) : GameCharacter(game, renderer, textRow, textCol),
braveFrame(textCol), frightenedFrame(12)
{
}

// B) CARGA LA TEXTURA CORRESPONDIENTE TRAS ACTUALIZAR LA ANIMACI�N
void Ghost::render(SDL_Renderer* renderer)
{
	setAnimation();
	GameCharacter::render(renderer);
}

// C) DETERMINA LA TEXTURA DEPENDIENDO EL ESTADO DEL FANTASMA: VALIENTE O ASUSTADO
void Ghost::setAnimation()
{
	if (frightened)
		textCol = frightenedFrame;
	else
		textCol = braveFrame;
}

// D) ESCOGE UNA DIRECCI�N Y MUEVE AL FANTASMA
void Ghost::update()
{
	// a) Selecciona una direcci�n a tomar
	chooseDir();

	// b) Mueve al fantasma
	game->nextCell(posX, posY, dirX, dirY, posX, posY);
}

// E) OBTIENE LAS POSIBLES DIRECCIONES A TOMAR POR EL FANTASMA
void Ghost::possibleDirs(int& numDirs)
{
	// 1) Reiniciamos las posiciones por si estuvieran ocupadas anteriormente
	numDirs = 0;
	posDirs.clear();

	direcciones dir;
	int nextPosX, nextPosY;

	// 2) Comprobamos para cada direcci�n si el fantasma puede moverse. Es decir, si no hay muro ni hay otro fantasma:
	for (int i = 0; i < NUM_DIRS; i++)
	{
		if (game->nextCell(posX, posY, AllDirs[i].x, AllDirs[i].y, nextPosX, nextPosY) &&!game->existGhost(nextPosX, nextPosY))
		{
			// En caso de ser accesible la posici�n, a�adimos la direcci�n en el vector
			dir.x = AllDirs[i].x;
			dir.y = AllDirs[i].y;
			posDirs.push_back(dir);
			numDirs++;
		}
	}
}

// F) ESCOGE UNA DIRECCI�N ENTRE LAS POSIBLES AL AZAR
void Ghost::chooseDir() {

	direcciones d;
	int n = 0;
	int i = 0;

	bool eliminado = false;

	// 1) Obtenemos las posibles direcciones a tomar
	possibleDirs(numDirs);

	// 2) Comprobamos que haya alguna direcci�n 
	if (numDirs != 0)
	{
		// a) En caso de haberla, miramos si hay m�s de una
		if (numDirs > 1)
		{
			// Si hubiera m�s de una:
			while (i < posDirs.size() && !eliminado)
			{
				// 1) Eliminamos la direcci�n contraria si �sta fuera una de las posibles direcciones
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
		// b) Si solo hubiera una direcci�n, asignamos esa (es decir, la "n = 0" por defecto). En otro caso, asignar�amos la de la posici�n aleatoria ("n = random")
		dirX = posDirs[n].x;
		dirY = posDirs[n].y;
	}
}

void Ghost::saveToFile(ofstream& file) {

	file << ghostType << " ";
	GameCharacter::saveToFile(file);
	file << endl;
}

Ghost::~Ghost()
{
}
