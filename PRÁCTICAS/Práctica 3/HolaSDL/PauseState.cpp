#include "PauseState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* game) : GameState (game)
{
	setBackName(PauseBACK);

	SDL_Rect resumeButton, saveGameButton,mainMenuButton;
	resumeButton = { WIN_WIDTH / 2 - (buttonWidth / 2), buttonHeight ,buttonWidth ,buttonHeight };
	saveGameButton = { WIN_WIDTH / 2 - (buttonWidth / 2),WIN_HEIGHT / 2 - (buttonHeight / 2),buttonWidth ,buttonHeight };
	mainMenuButton = { WIN_WIDTH / 2 - (buttonWidth / 2),WIN_HEIGHT - buttonHeight * 2,buttonWidth ,buttonHeight };


scene.push_back(new MenuButton(game,resumeButton.x,resumeButton.y,resumeButton.w,resumeButton.h,game->getTexture(ResumeGameTex),resume));

scene.push_back(new MenuButton(game, saveGameButton.x, saveGameButton.y, saveGameButton.w, saveGameButton.h,game->getTexture(SaveGameTex),saveGame));

scene.push_back(new MenuButton(game, mainMenuButton.x, mainMenuButton.y, mainMenuButton.w, mainMenuButton.h, game->getTexture(MainMenuText),goToMenu));

	

}
PauseState::~PauseState()
{
}
 void PauseState::resume(Game* game) {
	game->getStateMachine()->popState();
	
}
 void PauseState::saveGame(Game* game) {
	 resume(game);
	int code =  dynamic_cast<PlayState*>(game->getStateMachine()->currentState())->saveState(false);
 }
 void PauseState::goToMenu(Game* game) {
	 resume(game);
	 game->getStateMachine()->popState();
 }
