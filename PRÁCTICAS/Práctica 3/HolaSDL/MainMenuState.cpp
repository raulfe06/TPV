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

void MainMenuState::newGame(Game* game) {
	game->getStateMachine()->pushState(new PlayState(game,game->getRenderer(),false));
}
void MainMenuState::loadGame(Game* game) {
	game->getStateMachine()->pushState(new PlayState(game, game->getRenderer(), true));
}
void MainMenuState::exitGame(Game* game) {
	game->EXIT();
}
// UI


/*
void MainMenuState::renderMenu() {
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
void MainMenuState::loadMenu()
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
}*/


MainMenuState::~MainMenuState()
{
	for (int i = 0; i < NUM_MENU_TEXT; i++)
	{
		menuTextures[i]->Free();
		delete menuTextures[i];
	}
}
