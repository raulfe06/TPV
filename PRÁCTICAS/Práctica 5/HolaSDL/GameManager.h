#pragma once
#include "Container.h"
#include "Observer.h"
#include "Observable.h"
#include "ScoreRenderer.h"
#include "LiveRenderer.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "BadgeTimer.h"

const int defCount = 10;
class GameManager :
	public Container , public Observable,public Observer
{

	const string CONTINUE_TEXT = "PRESS SPACE TO CONTINUE";
public:
	GameManager(SDLGame* game);
	virtual ~GameManager();
	bool isGameOver() const;
	int getLives() const;
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const;
	void selectBadge();
	void badgeOff();
	void resetCount();
	void receive(Message* msg);
	void restartGame();

	virtual void handleInput(Uint32 time, const SDL_Event& event);

private:
	int lives_;
	int score_;
	int killCount_;
	bool badge_;
	bool running_;
	bool gameOver_;

	int cycle_;

	ScoreRenderer scoreRenderer_;
	LiveRenderer livesRenderer_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;

	Message* badgeOut;
};

