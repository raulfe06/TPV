#include "MenuButton.h"





void MenuButton::render() {
	SDL_Rect buttonRect = { x,y,w,h };
	text->Render(game->getRenderer(), buttonRect);
}
MenuButton::~MenuButton()
{
}
