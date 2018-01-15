#include "PauseState.h"
#include "MenuButton.h"


PauseState::PauseState(Game* game) : GameState (game)
{
	SDL_Rect resumeButton, saveGameButton;
	resumeButton = { 800/2-100, 600/2+30 ,329 ,60 };
	saveGameButton = {800/2-200,600/2+120,329,60};

	menuButtons.push_back(new MenuButton(game,resumeButton.x,resumeButton.y,resumeButton.w,resumeButton.h));

	menuButtons.push_back(new MenuButton(game, saveGameButton.x, saveGameButton.y, saveGameButton.w, saveGameButton.h));


}
bool PauseState::handleEvent(SDL_Event&e) {
	return true;
}

PauseState::~PauseState()
{
}
