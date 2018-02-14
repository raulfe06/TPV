#include "MenuButton.h"
#include <iostream>

 MenuButton::MenuButton(Game* game, int x, int y, int w, int h,Texture* tex, CallBackOnClick* callBack) : game(game), x(x), y(y), w(w), h(h),text(tex),cbOnClick(callBack){
	 
	 this->text = tex;
	 
		
}
void MenuButton::render(SDL_Renderer* renderer)
{
	SDL_Rect buttonRect = { x,y,w,h };
	text->Render(renderer, buttonRect);
}
bool MenuButton::handleEvent(SDL_Event& e)
{
	bool handled = false;
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point mouse_position;
		SDL_Rect rect = { x,y,w,h };
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

		if (SDL_PointInRect(&mouse_position, &rect)) 
		{
			handled = true;
			cbOnClick(game);
		}
	}
	return handled;
}
MenuButton::~MenuButton()
{
}
