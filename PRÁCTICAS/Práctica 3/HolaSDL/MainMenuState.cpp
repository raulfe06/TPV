#include "MainMenuState.h"



MainMenuState::MainMenuState(Game* game, SDL_Renderer* renderer) : GameState(game)
{
	for (int i = 0; i < NUM_MENU_TEXT; i++)
	{
		menuTextures[i] = new Texture();
//		menuTextures[i]->Load(renderer, TEXT_PATHFILE + menuNames[i], 1, 1);
	}
}

// UI
int MainMenuState::checkInsideRect(int x, int y, SDL_Rect rect)
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
/*void MainMenuState::mousePress(SDL_MouseButtonEvent& b) {
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

void MainMenuState::renderCode(const int& count) {
	SDL_Rect destRect;
	destRect.h = 218; destRect.w = 419;
	destRect.x = (WIN_WIDTH) / 2 - (destRect.w / 2); destRect.y = WIN_HEIGHT / 2 - (destRect.h / 2);
	menuTextures[3]->renderFrame(renderer, destRect, 0, count, 1, 11);
	SDL_RenderPresent(renderer);
}


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
