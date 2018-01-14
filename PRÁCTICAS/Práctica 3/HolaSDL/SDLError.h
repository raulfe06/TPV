#pragma once
#include "PacmanError.h"
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

class SDLError : public PacmanError
{

public:
	SDLError(const string& m) : PacmanError("de SDL: " + m){};
};

