#include "EndState.h"
#include "MenuButton.h"
#include "GameStateMachine.h"

EndState::EndState(Game* game,bool win) : GameState(game)
{
	if (win) {
		setBackName(VictoryBack);
	}
	else setBackName(DefeatBack);
	
	SDL_Rect menuButton = { WIN_WIDTH / 2 - (buttonWidth / 2),WIN_HEIGHT - buttonHeight * 3,buttonWidth ,buttonHeight };

	scene.push_back(new MenuButton(game,menuButton.x, menuButton.y, menuButton.w, menuButton.h,game->getTexture(MainMenuText),goToMenu));



}
void EndState::goToMenu(Game* game) {
	game->getStateMachine()->popState();
	game->getStateMachine()->popState();
}

EndState::~EndState()
{

}
