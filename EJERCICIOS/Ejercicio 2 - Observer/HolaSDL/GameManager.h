#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Container.h"
#include "Observable.h"

/*
 *
 */
class GameManager: public Container, public Observable,public Observer {
public:
	GameManager(SDLGame* game, int winningScore);
	virtual ~GameManager();

	bool isGameOver() const;
	int getLeftScore() const;
	void setLeftScore(int leftScore);
	int getRightScore() const;
	void setRightScore(int rightScore);
	bool isRunning() const;
	void setRunning(bool running);

private:
	int leftScore_;
	int rightScore_;
	int winningScore_;
	bool running_;
	bool gameOver_;
	void receive(Message msg);
};

#endif /* GAMEMANAGER_H_ */
