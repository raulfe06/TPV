#include "Font.h"
#include <string>

Font::Font()
{
}
bool Font::load(std::string filename, int size) {
	font = TTF_OpenFont(filename.c_str(), size);
	return  font != nullptr;
}
Font::Font(std::string filename, int size) {
	load(filename, size);
}
SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const {
	return	TTF_RenderText_Solid(font, text.c_str(), color);
}
void Font::free() {
	if (font != nullptr) TTF_CloseFont(font);
	font = nullptr;
}

