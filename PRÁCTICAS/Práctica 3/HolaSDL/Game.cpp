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

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"


using namespace std;



/*
void Game::run() {

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

		}
		i++;
	}
	renderTexts();

	SDL_RenderPresent(renderer);
}*/