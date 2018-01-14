#include "Game.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include <fstream>
#include "Pacman.h"
#include "SDL.h"
#include <typeinfo>
#include <iostream>
#include <iterator>
#include <SDL_ttf.h>

using namespace std;


Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	// b) Creamos la ventana y el renderer
	window = SDL_CreateWindow("PACMAN", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		error = true;
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //RGB y alpha

	for (int i = 0; i < NUM_MENU_TEXT; i++) {
		menuTextures[i] = new Texture();
		menuTextures[i]->Load(renderer, TEXT_PATHFILE + menuNames[i], 1, 1);
	}
	
}

// LECTURA Y ESCRITURA
void Game::loadFile(string filename) {
	score = 0;
	characters.clear();
	list<GameCharacter*>::iterator iteratorCharacters;

	GameCharacter* gch;
	ifstream file;
	int auxGhostType;
	iteratorCharacters = characters.begin();

	map = new GameMap(this);

	file.open(filename);
	if (!file.fail()) {
		map->loadFromFile(file);
		map->initializeTextures(renderer);


		// Pacman se crea antes que los fantasmas porque los smartGhost necesitarán su puntero
		pacman = new Pacman(this, renderer, 0, 10);

		int aux = 0;
		file >> numGhosts;
		for (int i = 0; i < numGhosts; i++)
		{
			file >> auxGhostType;

			if (auxGhostType == 0)
			{
				Ghost* ghost = new Ghost(this, renderer, 0, aux * 2);
				ghost->setType(auxGhostType);
				ghost->loadFromFile(file);
				characters.push_back(ghost);
				aux++;
			}
			else
			{
				SmartGhost* smartGhost = new SmartGhost(this, renderer, 0, 8, pacman);
				smartGhost->setType(auxGhostType);
				smartGhost->loadFromFile(file);
				characters.push_back(smartGhost);
			}
		}

		pacman->loadFromFile(file);
		characters.push_front(pacman);

		if (loading) {
			file >> score;
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
		loading = false;
	}
	else loading = true;
	
	file.close();
}
void Game::saveToFile(string filename) {
	list<GameCharacter*>::iterator it;
	int i = 0;
	ofstream file;
	file.open(filename);
	map->saveToFile(file);
	file << numGhosts << endl;;
	it = characters.begin();
	advance(it, 1);
	while (it != characters.end())
	{
		(*it)->saveToFile(file);
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
int Game::saveState() {
	SDL_Event event;
	int count = 0;
	unsigned int code = 0;
	while (savingState && !exit)
	{
		renderCode(count);
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
	if (!savingState && !loading) saveToFile(to_string(code) + ".pac");
	return code;
}
void Game::run() {

	while (level<NUM_TOTAL_LEVELS && !exit) {
		if (loading) {
			while (loading) {
				savingState = true;
				int code = saveState();
				loadFile(to_string(code) + ".pac");
			}
		}
		else loadFile("level0" + to_string(level) + ".pac");
		win = false;
		end = false;

		while (!exit && !win && !end)
		{
			int startTime = SDL_GetTicks();
			handleEvents();
			cout << score << endl;
			update();
			render();
			delta = SDL_GetTicks() - startTime;

			if (delta < FRAME_RATE)
				SDL_Delay(FRAME_RATE - delta);
			if (savingState) saveState();

			endLevel();
		}
	}
}
void Game::handleEvents()
{
	SDL_Event event;

	// Mientras NO queden eventos por procesar en la cola...
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)

			exit = true;
		if (event.key.keysym.sym == SDLK_g) {
			savingState = true;
		}
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		
		// ...entramos al bucle y metemos todos los eventos en la cola para procesarlos
		pacman->setDir(event);
	}
}
void Game::update() {
	cout << numFood << endl;

	list<GameCharacter*>::iterator it = characters.begin();
	advance(it, 1);
	if (pacman->getEnergy())
	{
		pacman->timer();
	}
	int foodX, foodY;
	if (pacman->eat(foodX, foodY))
	{
		map->setCell(foodY, foodX, Empty);
		score += FOOD_POINTS;
		numFood--;
	}
	pacman->update();
	checkCapture();
	while (it != characters.end())
	{
		(*it)->update();

		++it;
	}
	checkCapture();
}
void Game::render()
{
	list<GameCharacter*>::iterator it = characters.begin();
	advance(it, 1);

	int i = 0;
	SDL_RenderClear(renderer);


	map->render(renderer);

	pacman->render(renderer);

	if (pacman->energyEnabled())
		dynamic_cast<Ghost*>(*it)->toggleFear(true);
	else
		dynamic_cast<Ghost*>(*it)->toggleFear(false);

	for (it; it != characters.end(); it++)
	{
		(*it)->render(renderer);
		/*if(pacman->energyEnabled())
		(*it)->render(renderer);
		else
		{

		}*/
		i++;
	}
	renderTexts();

	SDL_RenderPresent(renderer);
}
void Game::endLevel() {
	if (pacman->getLives() == 0) {
		end = true;
	}
	if (numFood == 0) {
		level++;
		win = true;
	}
}

// MAPA
bool Game::nextCell(int x, int y, int dx, int dy, int& nx, int& ny)
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
mapCell Game::getCell(int posX, int posY) const
{
	return map->getCell(posX, posY);
}

// COLISIONES
void Game::checkCapture()
{
	list<GameCharacter*>::iterator it = characters.begin();
	advance(it, 1);
	bool capture = false;
	// Comprobamos por cada fantasma si coincide la posici�n con la de Pacman:
	while (it != characters.end() && !capture)
	{
		if (pacman->getPosX() == (*it)->getPosX() && pacman->getPosY() == (*it)->getPosY())
		{
			// 1) Si coincide, pero la energ�a estuviera ACTIVA... 
			if (pacman->energyEnabled()) {
				(*it)->restartPos(); // ...reiniciamos la posicion del fantasma
				score += NORMAL_GHOST_POINTS;
			}

			else if (dynamic_cast<Ghost*>(*it)->getType() == 1 && dynamic_cast<SmartGhost*>(*it)->isDead())
			{
				it = characters.erase(it);
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
void Game::restartCharacters() {
	list<GameCharacter*>::iterator it;
	for (it = characters.begin(); it != characters.end(); it++) {
		(*it)->restartPos();
	}
}

// UI
int Game::checkInsideRect(int x, int y, SDL_Rect rect)
{

	if (x >= rect.x && x < (rect.x + rect.w))
	{
		if (y >= rect.y && y < (rect.y + rect.h))
		{
			return 1;
		}
	}
	return 0;
}
void Game::mousePress(SDL_MouseButtonEvent& b) {
	if (b.button == SDL_BUTTON_LEFT) {

		if (checkInsideRect(b.x, b.y, rectNG) == 1) {
			level = 1;
			menu = false;
		}
		else if (checkInsideRect(b.x, b.y, rectLG) == 1) {
			loading = true;
			menu = false;
		}
	}
}

void Game::renderCode(const int& count) {
	SDL_Rect destRect;
	destRect.h = 218; destRect.w = 419;
	destRect.x = (WIN_WIDTH) / 2 - (destRect.w / 2); destRect.y = WIN_HEIGHT / 2 - (destRect.h / 2);
	menuTextures[3]->renderFrame(renderer, destRect, 0, count, 1, 11);
	SDL_RenderPresent(renderer);
}
void Game::renderMenu() {
	SDL_Rect destRect1, destRect2, destRectFondo;

	destRectFondo.x = destRectFondo.y = 0; destRectFondo.w = WIN_WIDTH; destRectFondo.h = WIN_HEIGHT;
	menuTextures[2]->Render(renderer, destRectFondo);

	destRect1.x = (WIN_WIDTH) / 2 - 200;
	destRect1.y = WIN_HEIGHT / 2 + 30; destRect1.w = 329; destRect1.h = 60;

	rectNG = destRect1;

	menuTextures[0]->Render(renderer, destRect1);

	destRect2.x = (WIN_WIDTH) / 2 - 200; destRect2.y = WIN_HEIGHT / 2 + 120; destRect2.w = 329; destRect2.h = 60;

	rectLG = destRect2;

	menuTextures[1]->Render(renderer, destRect2);

	SDL_RenderPresent(renderer);
}
void Game::loadMenu()
{
	SDL_Event event;

	renderMenu();

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mousePress(event.button);
		}
		if (event.type == SDL_QUIT) {
			exit = true;
		}
	}
}

// FANTASMAS
bool Game::existGhost(int posX, int posY)
{
	bool ghostFound = false;

	list<GameCharacter*>::iterator it = characters.begin();
	advance(it, 1);
	// Recorremos todos los fantasmas y comprobamos su posición
	while (it != characters.end() && !ghostFound)
	{
		if ((*it)->getPosX() == posX && (*it)->getPosY() == posY)
		{
			// Si coincide la posición con alguna de los fantasmas, devuelve 'true'
			ghostFound = true;
		}
		it++;
	}

	return ghostFound;
}
bool Game::existGhost(SmartGhost* ghost, int posX, int posY, const bool& adult, bool& spawnGhost)
{
	bool ghostFound = false;
	spawnGhost = false;

	list<GameCharacter*>::iterator it = characters.begin();
	advance(it, 1);
	// Recorremos todos los fantasmas y comprobamos su posición
	while (it != characters.end() && !ghostFound)
	{
		if ((*it) != ghost)
		{
			if ((*it)->getPosX() == posX && (*it)->getPosY() == posY)
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
void Game::spawnGhost(int posX, int posY)
{
	SmartGhost* smartGhost = new SmartGhost(this, renderer, 0, 8, pacman, posX, posY);
	smartGhost->setType(1);
	characters.push_back(smartGhost);

}

// TEXTO
void Game::createLevelText() {
	SDL_Rect destRect;
	destRect.x =625; destRect.y = 75; destRect.h = 35;  destRect.w = 135;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 255,250,65 };
	texture->loadFromText(renderer, "Level: "+to_string(level), font, fg);
	texture->Render(renderer, destRect);
}
void Game::createScoreText() {
	SDL_Rect destRect;
	destRect.x = 625; destRect.y = 300; destRect.h = 35;  destRect.w = 150;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 255,0,0 };
	texture->loadFromText(renderer, "Score: " + to_string(score), font, fg);
	texture->Render(renderer, destRect);
}
void Game::createLivesText() {
	SDL_Rect destRect;
	destRect.x = 625; destRect.y = 500; destRect.h = 35;  destRect.w = 135;
	Font font = Font("arial.ttf", 12);
	Texture* texture = new Texture();
	SDL_Color fg = { 239,6,255 };
	texture->loadFromText(renderer, "Lives: " + to_string(pacman->getLives()), font, fg);
	texture->Render(renderer, destRect);
}
void Game::renderTexts() {
	createLevelText();
	createScoreText();
	createLivesText();
}


Game::~Game()
{
	delete map;
	for (int i = 0; i < NUM_MENU_TEXT; i++) 
	{
		menuTextures[i]->Free();
		delete menuTextures[i];
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}