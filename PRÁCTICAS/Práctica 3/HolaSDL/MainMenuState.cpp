#include "MainMenuState.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* game) : GameState(game)
{
	setBackName(MenuBACK);

	SDL_Rect newGameButton, loadGameButton, exitGameButton;
	
	newGameButton = { WIN_WIDTH/2-(buttonWidth/2), buttonHeight ,buttonWidth ,buttonHeight };
	loadGameButton = { WIN_WIDTH / 2 - (buttonWidth / 2),WIN_HEIGHT/2-(buttonHeight/2),buttonWidth ,buttonHeight };
	exitGameButton = { WIN_WIDTH / 2 - (buttonWidth / 2),WIN_HEIGHT-buttonHeight*2,buttonWidth ,buttonHeight };

	scene.push_back(new MenuButton(game, newGameButton.x, newGameButton.y, newGameButton.w, newGameButton.h, game->getTexture(NewGameTex),newGame));

	scene.push_back(new MenuButton(game, loadGameButton.x, loadGameButton.y, loadGameButton.w, loadGameButton.h, game->getTexture(LoadGameTex),loadGame));

	scene.push_back(new MenuButton(game, exitGameButton.x, exitGameButton.y, exitGameButton.w, exitGameButton.h, game->getTexture(ExitGameTex),exitGame));

}

void MainMenuState::newGame(Game* game)
{
	game->getStateMachine()->pushState(new PlayState(game,game->getRenderer(),false));
}

void MainMenuState::loadGame(Game* game)
{
	game->getStateMachine()->pushState(new PlayState(game, game->getRenderer(), true));
}

void MainMenuState::exitGame(Game* game)
{
	game->EXIT();
}


MainMenuState::~MainMenuState()
{

}
