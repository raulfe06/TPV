#include "PauseState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* game) : GameState (game)
{
	SDL_Rect resumeButton, saveGameButton,mainMenuButton;
	resumeButton = { 0, 0 ,329 ,60 };
	saveGameButton = { 0,200,329,60};
	mainMenuButton = { 0,300,329,60 };


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
	int code =  dynamic_cast<PlayState*>(game->getStateMachine()->currentState())->saveState();
	//dynamic_cast<PlayState*>(game->getStateMachine()->currentState())->saveToFile("levels\\" + to_string(code) + ".pac");
 }
 void PauseState::goToMenu(Game* game) {
	 resume(game);
	 game->getStateMachine()->popState();
 }
