#pragma once
#include "GameState.h"
#include "Game.h"
#include <vector>
#include "MenuButton.h"

class PauseState : GameState
{
private:
	vector<MenuButton*> menuButtons;
public:
	PauseState(Game* game);
	~PauseState();
	bool handleEvent(SDL_Event&e);
};

