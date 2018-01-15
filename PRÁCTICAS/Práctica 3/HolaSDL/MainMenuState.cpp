#include "MainMenuState.h"



MainMenuState::MainMenuState(SDL_Renderer* renderer)
{
	for (int i = 0; i < NUM_MENU_TEXT; i++)
	{
		menuTextures[i] = new Texture();
		menuTextures[i]->Load(renderer, TEXT_PATHFILE + menuNames[i], 1, 1);
	}
}


MainMenuState::~MainMenuState()
{
}
