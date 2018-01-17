#pragma once
#include <SDL_ttf.h>
#include <string>
#include "checkML.h"

class Font
{
private:
	TTF_Font* font = nullptr;
public:
	Font();
	Font(std::string filename, int	size);
	void free();
	bool load(std::string filename, int size);
	SDL_Surface* generateSurface(std::string text, SDL_Color color)	const;
	~Font() { free(); };
};

