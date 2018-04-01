#include "GameManager.h"



GameManager::GameManager(SDLGame* game) : Container(game), livesRenderer_(game),lives_(3), killCount_(defCount),
gameMsg_(game, CONTINUE_TEXT)
{
	addRenderComponent(&gameMsg_);
	addPhysicsComponent(&badgeTimer_);
	addRenderComponent(&scoreRenderer_);
	addRenderComponent(&livesRenderer_);
	addInputComponent(&gameCtrl_);
	setRunning(false);
}


GameManager::~GameManager()
{
	
}

bool GameManager::isGameOver() const
{
	return gameOver_;
}

int GameManager::getLives() const
{
	return lives_;
}

bool GameManager::isRunning() const
{
	return running_;
}

void GameManager::setRunning(bool running)
{
	if (running_ != running) {
		running_ = running;
		Message m = { running ? ROUND_START : ROUND_OVER };
		if (!running && !gameOver_) addRenderComponent(&gameMsg_);
		else delRenderComponent(&gameMsg_);
		send(&m);
		if (gameOver_ && running)
			gameOver_ = false;
	}
	
}

int GameManager::getScore() const
{
	return score_;
}

void GameManager::setBadge(bool b)
{
	badge_ = b;

	if (badge_) {
		send(&Message(BADGE_ON));
	}
	else if(!badge_)send(&Message(BADGE_OFF));
}

void GameManager::resetCount()
{
		killCount_ = defCount;
		send(&Message(BADGE_OFF));
}

void GameManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION:
		lives_--;
		setRunning(false);
		setBadge(false);
		if (lives_ <= 0) {
			send(&Message(GAME_OVER));
			gameOver_ = true;
			game_->stop(); // PARA ACABAR EL JUEGO
		}
		if (badge_) setBadge(false);
		break;
	case BULLET_ASTROID_COLLISION:
		score_++;
		killCount_--;
       		if (killCount_ == 0)
		{
       			send(&Message(BADGE_ON));
 			badgeTimer_.start(5000);
		}
			break;
	case NO_MORE_ATROIDS:
		if (badge_) setBadge(false);
		send(&Message(ROUND_OVER));
		send(&Message(GAME_OVER));
		gameOver_ = true;
		game_->stop(); // PARA ACABAR EL JUEGO
		setRunning(false);
		break;

	}
}

void GameManager::restartGame()
{
	lives_ = 3;
	score_ = 0;
	killCount_ = defCount;
	badge_ = false;
	running_ = true;
	gameOver_ = false;
	delRenderComponent(&gameMsg_);
	send(&Message(ROUND_START));
}

void GameManager::handleInput(Uint32 time, const SDL_Event & event)
{
	if (!isRunning())
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				if (gameOver_) {
					restartGame();
				}
				setRunning(true);
				break;
			}
		}
		Container::handleInput(time, event);
	}
}
