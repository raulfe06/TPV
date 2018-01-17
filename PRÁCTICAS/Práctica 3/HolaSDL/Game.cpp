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
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			throw SDLError(SDL_GetError());

		if (TTF_Init() < 0)
			throw SDLError(TTF_GetError());
		// b) Creamos la ventana y el renderer
		window = SDL_CreateWindow("PACMAN", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr || renderer == nullptr)
		{
			throw SDLError(SDL_GetError());
		}
		else
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //RGB y alpha

	}
	catch (SDLError& e)
	{
		char out = ' ';
		cout << e.what() << endl;

		cout << "\nPulse la tecla 'x' para salir" << endl;

		while (out != 'x')
		{
			cin >> out;
		}
		exit = true;
	}

	stateMachine = new GameStateMachine();

	test = new PlayState(this, renderer);
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

	stateMachine->currentState()->render(renderer);

	SDL_RenderPresent(renderer);
}

GameStateMachine* Game::getStateMachine()
{
	return stateMachine;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
Texture* Game::getTexture(enumTextures name) {
	return textures[name];
}
void Game::initializeTextures() {
	//Inicializa las texturas
	for (int i = 0; i < NUM_GAME_TEXTURES; i++)
	{
		textures[i] = new Texture();
		const textAtributes& atributes = GAME_TEXTURES[i];
		textures[i]->Load(renderer, TEXT_PATHFILE + atributes.filename, atributes.row, atributes.col);
	}
}