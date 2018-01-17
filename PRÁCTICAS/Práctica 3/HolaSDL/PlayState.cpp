#include"PlayState.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include <fstream>
#include "Pacman.h"
#include "SDL.h"
#include <typeinfo>
#include <iostream>
#include <iterator>
#include <SDL_ttf.h>

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

#include "GameStateMachine.h"

using namespace std;


PlayState::PlayState(Game* game, SDL_Renderer* renderer) : GameState(game),renderer(renderer)
{	
}

// LECTURA Y ESCRITURA
void PlayState::loadFile(string filename) {
	score = 0;
	scene.clear();
	auto iteratorCharacters = scene.begin();

	GameCharacter* gch;
	ifstream file;
	int auxGhostType;

	

	map = new GameMap(this);

	try {

		file.open(filename);
		if (!file.good()) throw FileNotFoundError(filename);

		map->loadFromFile(file);
		//map->initializeTextures(renderer);

		// Pacman se crea antes porque necesitarán su puntero
		pacman = new Pacman(this, renderer, 0, 10);
		

		int aux = 0;
		file >> numGhosts;
		for (int i = 0; i < numGhosts; i++)
		{
			Ghost* ghost;
			file >> auxGhostType;
			if (auxGhostType < 0 || auxGhostType > 1) throw FileFormatError("El tipo de fanstasma no es compatible");

			if (auxGhostType == 0)
			{
				ghost = new Ghost(this, renderer, 0, aux * 2, pacman);
				aux++;
			}
			else
			{
				ghost = new SmartGhost(this, renderer, 0, 8, pacman);
			}

			ghost->setType(auxGhostType);
			ghost->loadFromFile(file);
			scene.push_back(ghost);
		}

		pacman->loadFromFile(file);

		scene.push_front(pacman);
		scene.push_front(map);

		file >> score;

		if (!file.fail()) 
		{
			int energyTime;
			file >> energyTime;
			int loadingLives;
			file >> loadingLives;
			pacman->setEnergyTime(energyTime);
			pacman->setLives(loadingLives);
			int energyState;
			file >> energyState;
			pacman->setEnergy(energyState);
			file >> level;
		}
		//loading = false;

		file.close();
	}
	catch (FileNotFoundError& e)
	{
		cout << e.what() << endl;
		level++;
		loadFile("levels\\level0" + to_string(level) + ".pac");

	}
	catch (FileFormatError& e)
	{
		cout << e.what() << endl;
	}



}
void PlayState::saveToFile(string filename) {
	int i = 0;
	ofstream file;
	file.open(filename);
	map->saveToFile(file);
	file << numGhosts << endl;;
	auto it = scene.begin();
	advance(it, 2);
	while (it != scene.end())
	{
		dynamic_cast<GameCharacter*>(*it)->saveToFile(file);
		it++;
	}
	pacman->saveToFile(file);
	file << score << endl;
	file << pacman->getEnergyTime() << endl;
	file << pacman->getLives() << endl;
	file << pacman->getEnergy() << endl;
	file << level << endl;
	file.close();
}

// BUCLE DEL JUEGO
int PlayState::saveState() {
	SDL_Event event;
	int count = 0;
	unsigned int code = 0;
	while (savingState && !exit)
	{
	//	renderCode(count);
		SDL_WaitEvent(&event);

		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else if (event.key.keysym.sym == SDLK_RETURN)
		{
			savingState = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (count <= 9) {
				if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
				{
					code = 10 * code + (event.key.keysym.sym - SDLK_0);
					cout << code << endl;
					count++;
				}
			}
		}
	}
	if (!savingState) saveToFile("levels\\" + to_string(code) + ".pac");
	return code;
}
/*
void PlayState::run() {

	while (level<NUM_TOTAL_LEVELS && !exit) {
		if (loading) {
			while (loading) {
				savingState = true;
				int code = saveState();
				loadFile("levels\\" + to_string(code) + ".pac");
			}
		}
		else
			loadFile("levels\\level0" + to_string(level) + ".pac");
		win = false;
		end = false;

		while (!exit && !win && !end)
		{
			int startTime = SDL_GetTicks();
			handleEvents();
			update();
			render();
			delta = SDL_GetTicks() - startTime;

			if (delta < FRAME_RATE)
				SDL_Delay(FRAME_RATE - delta);
			if (savingState) saveState();

			endLevel();
		}
	}
}*/
void PlayState::handleEvents(SDL_Event& e)
{
     /* if(e.type == SDL_KEYDOWN)
	  {
		  if (e.key.keysym.sym == SDLK_ESCAPE)
			  game->getStateMachine()->pushState(new PauseState(game));
			  
	  }*/

	pacman->handleEvent(e);
}

void PlayState::update() 
{
	GameState::update();
	checkCapture();
}

void PlayState::render(SDL_Renderer* renderer)
{

	GameState::render(renderer);
	renderTexts();
}

void PlayState::endLevel() {
	if (pacman->getLives() == 0) {
		end = true;
	}
	if (numFood == 0) {
		level++;
		win = true;
	}
}

// MAPA
bool PlayState::nextCell(int x, int y, int dx, int dy, int& nx, int& ny)
{
	// 1) Avanzamos la posicion segun la direccion entrante
	nx = x + dx;
	ny = y + dy;

	// 2) Observamos si cruzamos de un lado al otro del mapa:

	// a) Direccion X
	if (nx < 0)
		nx = cols - 1;
	else if (nx >= cols)
		nx = 0;

	// a) Direccion Y
	if (ny < 0)
		ny = rows - 1;
	else if (ny >= rows)
		ny = 0;

	// 3) Miramos si podemos o no avanzar (si hay o no hay muro en la nueva posicion):
	if (map->getCell(nx, ny) != Wall)
	{
		// a) Si NO hay, actualizamos la posicion y devolvemos 'true'
		return true;
	}
	// b) Si lo hubiera, entonces devolvemos 'false'
	else
	{

		nx = x;
		ny = y;
		return false;
	}
}
mapCell PlayState::getCell(int posX, int posY) const
{
	return map->getCell(posX, posY);
}

// COLISIONES
void PlayState::checkCapture()
{
	auto it = scene.begin();
	advance(it, 2);
	bool capture = false;
	// Comprobamos por cada fantasma si coincide la posici�n con la de Pacman:
	while (it != scene.end() && !capture)
	{
		if (pacman->getPosX() == dynamic_cast<GameCharacter*>(*it)->getPosX() && pacman->getPosY() == dynamic_cast<GameCharacter*>(*it)->getPosY())
		{
			// 1) Si coincide, pero la energ�a estuviera ACTIVA... 
			if (pacman->energyEnabled()) {
				dynamic_cast<GameCharacter*>(*it)->restartPos(); // ...reiniciamos la posicion del fantasma
				score += NORMAL_GHOST_POINTS;
			}

			else if (dynamic_cast<Ghost*>(*it)->getType() == 1 && dynamic_cast<SmartGhost*>(*it)->isDead())
			{
				it = scene.erase(it);
				it--;
				score += INTELLI_GHOST_POINTS;
			}
			else
			{
				// En caso contrario, damos por valida la captura y restamos una vida
				capture = true;
				pacman->subLives();
				restartCharacters();
			}
		}
		it++;
	}
}
void PlayState::restartCharacters() {
	auto it = scene.begin();
	advance(it, 1);
	for (it; it != scene.end(); it++) {
		dynamic_cast<GameCharacter*>(*it)->restartPos();
	}
}

bool PlayState::pacmanEat(int& foodX, int& foodY)
{
	bool eat = false;

	if (pacman->eat(foodX, foodY))
	{
		addScore(FOOD_POINTS);
		subFood();
		eat = true;
	}
	return eat;
}

// FANTASMAS
bool PlayState::existGhost(int posX, int posY)
{
	bool ghostFound = false;

	auto it = scene.begin();
	advance(it, 2);
	// Recorremos todos los fantasmas y comprobamos su posición
	while (it != scene.end() && !ghostFound)
	{
		if (dynamic_cast<GameCharacter*>(*it)->getPosX() == posX && dynamic_cast<GameCharacter*>(*it)->getPosY() == posY)
		{
			// Si coincide la posición con alguna de los fantasmas, devuelve 'true'
			ghostFound = true;
		}
		it++;
	}

	return ghostFound;
}
bool PlayState::existGhost(SmartGhost* ghost, int posX, int posY, const bool& adult, bool& spawnGhost)
{
	bool ghostFound = false;
	spawnGhost = false;

	auto it = scene.begin();
	advance(it, 2);
	// Recorremos todos los fantasmas y comprobamos su posición
	while (it != scene.end() && !ghostFound)
	{
		if ((*it) != ghost)
		{
			if (dynamic_cast<GameCharacter*>(*it)->getPosX() == posX && dynamic_cast<GameCharacter*>(*it)->getPosY() == posY)
			{
				// Si coincide la posición con alguna de los fantasmas, devuelve 'true'
				ghostFound = true;

				if (dynamic_cast<Ghost*>(*it)->getType() == 1)
				{
					if (adult && dynamic_cast<SmartGhost*>(*it)->isAdult() && !dynamic_cast<SmartGhost*>(*it)->isDead())
						spawnGhost = true;
				}
			}
		}
		it++;
	}

	return ghostFound;
}
void PlayState::spawnGhost(int posX, int posY)
{
	SmartGhost* smartGhost = new SmartGhost(this, renderer, 0, 8, pacman, posX, posY);
	smartGhost->setType(1);
	scene.push_back(smartGhost);

}

// TEXTO
void PlayState::createLevelText() {
	SDL_Rect destRect;
	destRect.x = 625; destRect.y = 75; destRect.h = 35;  destRect.w = 135;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 255,250,65 };
	texture->loadFromText(renderer, "Level: " + to_string(level), font, fg);
	texture->Render(renderer, destRect);
}
void PlayState::createScoreText() {
	SDL_Rect destRect;
	destRect.x = 625; destRect.y = 300; destRect.h = 35;  destRect.w = 150;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 255,0,0 };
	texture->loadFromText(renderer, "Score: " + to_string(score), font, fg);
	texture->Render(renderer, destRect);
}
void PlayState::createLivesText() {
	SDL_Rect destRect;
	destRect.x = 625; destRect.y = 500; destRect.h = 35;  destRect.w = 135;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 239,6,255 };
	texture->loadFromText(renderer, "Lives: " + to_string(pacman->getLives()), font, fg);
	texture->Render(renderer, destRect);
}
void PlayState::renderTexts() {
	createLevelText();
	createScoreText();
	createLivesText();
}


PlayState::~PlayState()
{
	delete map;
	/*for (int i = 0; i < NUM_MENU_TEXT; i++)
	{
		menuTextures[i]->Free();
		delete menuTextures[i];
	}*/

	renderer = nullptr;
}