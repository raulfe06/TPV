#include "GameManager.h"



GameManager::GameManager(SDLGame* game) : Container(game), livesRenderer_(game),lives_(3), killCount_(0),
gameMsg_(game, CONTINUE_TEXT), badgeOut(nullptr)
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
	delete badgeOut;
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

void GameManager::selectBadge()
{
	badgeOff();

	if (cycle_ == 0) 
	{
		send(&Message(BADGE_ON));
		badgeOut = new Message(BADGE_OFF);
		
		cycle_++;
	}
	else if (cycle_ == 1)
	{
		send(&Message(SUPERBULLETS_ON));
		badgeOut = new Message(SUPERBULLETS_OFF);

		cycle_++;
	}
	else if (cycle_ == 2)
	{
		send(&Message(MULTIBULLETS_ON));
		badgeOut = new Message(MULTIBULLETS_OFF);

		cycle_ = 0;
	}
}

void GameManager::badgeOff()
{
	if (badgeOut != nullptr)
	{
		send(badgeOut);

		delete badgeOut;
		badgeOut = nullptr;
	}
}

void GameManager::resetCount()
{
		killCount_ = 0;
		send(&Message(BADGE_OFF));
}

void GameManager::receive(Message * msg)
{
	switch (msg->id_) 
	{
	case ASTROID_FIGHTER_COLLISION:
		lives_--;
		setRunning(false);
		badgeOff();
		resetCount();
		if (lives_ <= 0) {
			send(&Message(GAME_OVER));
			gameOver_ = true;
			game_->stop(); // PARA ACABAR EL JUEGO
		}
		//if (badge_) setBadge(false);
		break;

	case BULLET_ASTROID_COLLISION:
		score_++;
		killCount_++;
		cout << "Kill Count: " << killCount_ << endl;
		if (killCount_ % 10 == 0)
		{
			selectBadge();
			badgeTimer_.start(10000);
		}
		break;

	case NO_MORE_ATROIDS:
		badgeOff();
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
	killCount_ = 0;
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
