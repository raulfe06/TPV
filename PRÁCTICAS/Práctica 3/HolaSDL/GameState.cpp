#include "GameState.h"


void GameState::renderCode(const int& count) {
	SDL_Rect destRect;
	destRect.h = 218; destRect.w = 419;
	destRect.x = (WIN_WIDTH) / 2 - (destRect.w / 2); destRect.y = WIN_HEIGHT / 2 - (destRect.h / 2);
	Texture* text = new Texture();
	text = game->getTexture(CodeText);
	text->renderFrame(game->getRenderer(), destRect, 0, count, 1, 11);
	SDL_RenderPresent(game->getRenderer());
}GameState::GameState(Game* game) : game(game)
{
}
GameState::GameState()
{

}
void GameState::renderBackGround() {

	
	SDL_Rect dest = { 0,0,WIN_WIDTH,WIN_HEIGHT };
	Texture* text = game->getTexture(backGroundName);
	text->Render(game->getRenderer(), dest);
}


