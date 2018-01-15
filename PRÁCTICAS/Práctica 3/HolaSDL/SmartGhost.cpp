#include "SmartGhost.h"
#include "Pacman.h"
#include "Game.h"
#include "FileFormatError.h"
#include <iostream>

// A) INICALIZA LAS VARIABLES DEL FANTASMA INTELIGENTE -> UTILIZA LA CONSTRUCTORA DEL PADRE, Y LUEGO INICIALIZA LAS VARIABLES PROPIAS
SmartGhost::SmartGhost(Game* game, SDL_Renderer* renderer, int textRow, int textCol, Pacman* pacman, int defX, int defY) : Ghost(game, renderer, textRow, textCol),
pacman(pacman), dead(false), cooldown(0), age(0)
{
	// 1) En caso de crearse por reproducci�n, se le da valor a la posici�n por defecto
	this->defX = defX;
	this->defY = defY;
	posX = defX;
	posY = defY;

}

// B) REDEFINE EL M�TODO DE <GameCharacter> PARA CARGAR LA EDAD INICIAL
void SmartGhost::loadFromFile(ifstream& file)
{
	GameCharacter::loadFromFile(file);
	file >> age;
	try {
		if (age < 0 || age >100) throw FileFormatError("La edad del fantasma Inteligente est� fuera del rango [0,100]");
	}
	catch(FileFormatError& e){
		cout << e.what() << endl;

	}
	defAge = age;
}

// C) REDEFINE EL M�TODO DE <GameCharacter> PARA GUARDAR LA EDAD ACTUAL
void SmartGhost::saveToFile(ofstream& file)
{
	file << ghostType << " ";

	GameCharacter::saveToFile(file);
	file << " " << age;
	file << endl;
}

// D) CARGA LA TEXTURA CORRESPONDIENTE TRAS ACTUALIZAR LA ANIMACI�N
void SmartGhost::render(SDL_Renderer* renderer)
{
	setAnimation();

	texture->RenderFrame(renderer, textRow, textCol, destRect);
}

// E) SELECCIONA LA TEXTURA DEPENDIENDO DEL ESTADO DEL FANTASMA, AS� COMO DE LA EDAD DEL MISMO
void SmartGhost::setAnimation()
{
	// 1) Calculamos el tama�o del rect�ngulo base, as� como la distancia al centro
	double width = ((WIN_WIDTH - OFFSET) / game->getCols());
	double height = (WIN_HEIGHT / game->getFils());

	double centerX = ((WIN_WIDTH - OFFSET) / game->getCols()) / 2;
	double centerY = (WIN_HEIGHT / game->getFils()) / 2;

	double scale = 1;

	// 2) Seleccionamos la escala a la que pintaremos el fantasma con respecto al rect�ngulo destino, dependiendo de la edad
	if (age < CHILD_AGE)
		scale = 0.5;

	else if (age < ADULT_AGE)
		scale = 0.75;

	// 3) Con los datos anteriores, calculamos el rect�ngulo de destino para la textura
	destRect.w = width * scale;
	destRect.h = height * scale;

	destRect.x = (posX * width) + (centerX*(1 - scale));
	destRect.y = (posY * height) + (centerY*(1 - scale));

	// 4) Pintamos una u otroa textura dependiendo del estado del fantasma 
	if (frightened || dead)
		textCol = frightenedFrame;
	else
		textCol = braveFrame;
}

// F) ACTUALIZA LA POSICI�N DEL FANTASMA DE UNA U OTRA MANERA DEPENDIENDO DE LA EDAD DEL MISMO
void SmartGhost::update()
{
	// Mientras no haya sobrepasado su edad m�xima:
	if (age < MAX_AGE)
	{
		// a) Miramos si el cooldown est� activo, y en tal caso lo reducimos
		if (cooldown > 0)
			cooldown--;

		// b) Si a�n est� en la m�nima edad, �ste no podr� moverse y podr� ser comido por Pacman 
		if (age < CHILD_AGE)
			dead = true;
		else
		{
			dead = false;
			// c) Si est� en la edad "adolescente", �ste se mover� como un fantasma normal
		 if (age < ADULT_AGE)
			Ghost::update();
		else
			// d) A partir de que alcanza la edad adulta, ya se comporta como un fantasma inteligente
			smartMovement();
		}
		age++;
	}
	// Cuando sobrepasa la edad m�xima, queda parado y puede ser comido por Pacman
	else
	{
		dead = true;
	}
}

// G) MOVIMIENTO DE FANTASMA INTELIGENTE
void SmartGhost::smartMovement()
{
	// 1) Elegimos una direcci�n y movemos al fantasma
	chooseDir();

	game->nextCell(posX, posY, dirX, dirY, posX, posY);

	// 2) Si en dicha posici�n hay un fantasma inteligente adulto, y tenemos el cooldown a '0'...
	game->existGhost(this, posX, posY, isAdult(), spawnGhost);
	if (spawnGhost  && cooldown == 0)
	{
		// ...reiniciamos el cooldown...
		cooldown = COOLDOWN;
		// ... y spawneamos un fantasma
		game->spawnGhost(posX, posY);
	}
}

// H) OBTIENE LAS POSIBLES DIRECCIONES A TOMAR POR EL FANTASMA
void SmartGhost::possibleDirs(int& numDirs)
{
	// 1) Reiniciamos las posiciones por si estuvieran ocupadas anteriormente
	numDirs = 0;
	posDirs.clear();

	direcciones dir;
	int nextPosX, nextPosY;

	// 2) Comprobamos para cada direcci�n si el fantasma puede moverse. Es decir, si no hay muro ni hay otro fantasma:
	for (int i = 0; i < NUM_DIRS; i++)
	{
		if (game->nextCell(posX, posY, AllDirs[i].x, AllDirs[i].y, nextPosX, nextPosY) && (!game->existGhost(this, nextPosX, nextPosY, isAdult(), spawnGhost)) || spawnGhost)
		{
			// En caso de ser accesible la posici�n, a�adimos la direcci�n en el vector
			dir.x = AllDirs[i].x;
			dir.y = AllDirs[i].y;
			posDirs.push_back(dir);
			numDirs++;
		}
	}
}

// I) ESCOGE UNA DIRECCI�N EN FUNCI�N DE LA POSICI�N DE PACMAN -> LA QUE LE ACERQUE M�S A �STE
void SmartGhost::chooseDir()
{
	direcciones d;
	int n = 0;
	int i = 0;

	int bestDir;

	bool eliminado = false;

	// 1) Obtenemos las posibles direcciones a tomar
	possibleDirs(numDirs);

	// 2) Comprobamos que haya alguna direcci�n 
	if (numDirs != 0)
	{
		// a) En caso de haberla, miramos si hay m�s de una
		if (numDirs > 1)
		{
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
			
			// auxiliar, cualquier direcci�n ser� menor
			bestDir = 5000;

			// 2) Miramos la posici�n que deje m�s cercano al fantasma de Pacman
			for (size_t i = 0; i < posDirs.size(); i++)
			{
				// Eje X
				int auxDirX = posX + posDirs[i].x;
				if (auxDirX < pacman->getPosX())
					auxDirX = pacman->getPosX() - auxDirX;
				else
					auxDirX = auxDirX - pacman->getPosX();

				// Eje Y
				int auxDirY = posY + posDirs[i].y;
				if (auxDirY < pacman->getPosY())
					auxDirY = pacman->getPosY() - auxDirY;
				else
					auxDirY = auxDirY - pacman->getPosY();

				// Miramos si la direcci�n calculada es mejor 
				int auxDir = auxDirX + auxDirY;
				if (auxDir < bestDir)
				{
					bestDir = auxDir;
					n = i;
				}
			}
		}
		// b) Si solo hubiera una direcci�n, asignamos esa (es decir, la "n = 0" por defecto). En otro caso, asignar�amos la direcci�n que se acerca m�s a Pacman
		dirX = posDirs[n].x;
		dirY = posDirs[n].y;
	}
	else
	{
		dirX = dirY = 0;
	}
}


SmartGhost::~SmartGhost()
{
}
