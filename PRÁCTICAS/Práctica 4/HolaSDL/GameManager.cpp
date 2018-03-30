#include "GameManager.h"



GameManager::GameManager(SDLGame* game) : Container(game), livesRenderer_(game),lives_(3)
{
	
	addPhysicsComponent(&badgeTimer_);
	addRenderComponent(&scoreRenderer_);
	addRenderComponent(&livesRenderer_);
	addInputComponent(&gameCtrl_);
	addRenderComponent(&gameMsg_);
	setRunning(true);
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
}

void GameManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION:
		lives_--;
		//send(&Message(ROUND_OVER)); Quizá no es necesario con el setRunning()
		setRunning(false);
		setBadge(false);
		if (lives_ <= 0) {
			send(&Message(GAME_OVER));
		}
		if (badge_) setBadge(false);
			break;
	case BULLET_ASTROID_COLLISION:
		score_++;
		send(&Message(BADGE_ON));
		badgeTimer_.start(2000);
			break;
	case NO_MORE_ATROIDS:
		if (badge_) setBadge(false);
		send(&Message(ROUND_OVER));
		send(&Message(GAME_OVER));
			break;
		
	}
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
				setRunning(true);
				break;
			}
		}
		Container::handleInput(time, event);
	}
}
