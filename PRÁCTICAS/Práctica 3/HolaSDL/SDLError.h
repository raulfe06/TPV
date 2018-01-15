#pragma once
#include "PacmanError.h"

class SDLError : public PacmanError
{

public:
	SDLError(const string& m) : PacmanError("de SDL: " + m){};
};

