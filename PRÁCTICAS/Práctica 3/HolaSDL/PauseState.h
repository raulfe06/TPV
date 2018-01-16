#pragma once
#include "GameState.h"
#include "Game.h"
#include <vector>
#include "MenuButton.h"

class PauseState : GameState
{

public:
	PauseState(Game* game);
	~PauseState();
	bool handleEvent(SDL_Event&e);
};

