
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "PlayState.h"
#include "Pacman.h"

using namespace std;


int main(int argc, char* argv[]){

	bool menu = true;
	PlayState* game = new PlayState();
	while (game->getMenu() && !game->getExit()) {
		game->loadMenu();
	}
	game->run();

	return 0;
}