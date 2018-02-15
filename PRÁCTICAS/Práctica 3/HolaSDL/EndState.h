#pragma once
#include "GameState.h"
#include "checkML.h"
class EndState : public GameState
{
public:
	EndState(Game* game,bool win);
	static void goToMenu(Game* game);
	~EndState();
};

