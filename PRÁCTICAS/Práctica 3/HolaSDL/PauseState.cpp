#include "PauseState.h"
#include "MenuButton.h"


PauseState::PauseState(Game* game) : GameState (game)
{
	SDL_Rect resumeButton, saveGameButton;
	resumeButton = { WIN_WIDTH/2-100, WIN_HEIGHT/2+30 ,329 ,60 };
	saveGameButton = { WIN_WIDTH /2-200,WIN_HEIGHT /2+120,329,60};

	menuButtons.push_back(new MenuButton(game,resumeButton.x,resumeButton.y,resumeButton.w,resumeButton.h));

	menuButtons.push_back(new MenuButton(game, saveGameButton.x, saveGameButton.y, saveGameButton.w, saveGameButton.h));


}
bool PauseState::handleEvent(SDL_Event&e) {
	return true;
}

PauseState::~PauseState()
{
}
