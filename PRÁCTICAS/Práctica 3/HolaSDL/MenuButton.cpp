#include "MenuButton.h"





void MenuButton::render() {
	SDL_Rect buttonRect = { x,y,w,h };
	text->Render(game->getRenderer(), buttonRect);
}
MenuButton::~MenuButton()
{
}
void MenuButton::loadFromFile(ifstream& file) {

 }
void MenuButton::saveToFile(ofstream& file) {

 }