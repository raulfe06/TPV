
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
#include "Pacman.h"

using namespace std;


int main(int argc, char* argv[]){

	bool menu = true;
	Game* game = new Game();
	while (game->getMenu() && !game->getExit()) {
		game->loadMenu();
	}
	game->run();

	return 0;
}