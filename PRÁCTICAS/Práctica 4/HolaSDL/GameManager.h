#pragma once
#include "Container.h"
#include "Observer.h"
#include "Observable.h"
#include "ScoreRenderer.h"
#include "LiveRenderer.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "BadgeTimer.h"

class GameManager :
	public Container , public Observable,public Observer
{
public:
	GameManager(SDLGame* game);
	virtual ~GameManager();
	bool isGameOver() const;
	int getLives() const;
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const;
	void setBadge(bool b);
	void receive(Message* msg);
private:
	int lives_;
	int score_;
	bool badge_;
	bool running_;
	bool gameOver_;

	ScoreRenderer scoreRenderer_;
	LiveRenderer livesRenderer_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;
};

