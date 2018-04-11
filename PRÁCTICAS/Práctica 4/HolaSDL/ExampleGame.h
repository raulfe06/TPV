#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "StarTrekBulletManager.h"
#include "FightersManager.h"
#include "AsteroidsManager.h"
#include "CollisionsManager.h"
#include "GameManager.h"
#include "SoundManager.h"

class ExampleGame: public SDLGame {
	
public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
	bool exit_;
	std::vector<GameObject*> actors_;



	StarTrekBulletManager bulletsManager_;
	FightersManager fightersManager_;
	AsteroidsManager astroidsManager_;
	CollisionsManager collisionManager_;
	GameManager gameManager_;
	SoundManager soundManager_;
};

#endif /* EXAMPLEGAME_H_ */
