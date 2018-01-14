#include "Font.h"
#include <string>
#include "SDLError.h"
#include <iostream>

Font::Font()
{
}
bool Font::load(std::string filename, int size) {

	try
	{
		font = TTF_OpenFont(filename.c_str(), size);

		if (font == nullptr)
			throw SDLError(TTF_GetError());

		return  font != nullptr;
	}
	catch (SDLError& e)
	{
		cout << e.what() << endl;
	}
}
Font::Font(std::string filename, int size)
{
	load(filename, size);
}

SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const 
{
	try
	{
	if (TTF_RenderText_Solid(font, text.c_str(), color) == nullptr)
		throw SDLError(TTF_GetError());

	return TTF_RenderText_Solid(font, text.c_str(), color);
	}
	catch (SDLError& e)
	{
		cout << e.what() << endl;
	}
}
void Font::free() {
	if (font != nullptr)
		TTF_CloseFont(font);

	font = nullptr;
}

