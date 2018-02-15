#include <iostream>
#include"Game.h"
#include "checkML.h"
using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool menu = true;
	Game* game = new Game;
	while (menu && game->ControlMenu()) {
		game->LoadMenu();
	}
	
	if (game->GetError())
		cout << "An error ocurred trying to initialize the game";
	else
		game->Run();

	delete game;
	return 0;
}