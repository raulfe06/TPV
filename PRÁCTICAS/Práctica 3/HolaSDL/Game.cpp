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

#include"GameStateMachine.h"
#include"PlayState.h"
#include "MainMenuState.h"


using namespace std;

Game::Game()
{
	stateMachine = new GameStateMachine();

	test = new PlayState();
	stateMachine->pushState(test);
	test->loadFile("levels\\level0" + to_string(1) + ".pac");

}

void Game::run() 
{

	while (!exit)
	{
		int startTime = SDL_GetTicks();
		handleEvents();
		stateMachine->currentState()->update();
		render();
		delta = SDL_GetTicks() - startTime;

		if (delta < FRAME_RATE)
			SDL_Delay(FRAME_RATE - delta);
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	// Mientras NO queden eventos por procesar en la cola...
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT)

			exit = true;
		else
			stateMachine->currentState()->handleEvents(event);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	stateMachine->currentState()->render();

	SDL_RenderPresent(renderer);
}