#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "StarWarsBulletsManager.h"

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

	GameObject* demoObj_;
	GameObject* plane_;
	GameComponent* demoComp_;
	GameComponent* planeComp_;
	RenderComponent* renderPlane_;
	InputComponent* inputPlane_;
	InputComponent* rotateComp_;
	PhysicsComponent* circularComp_;
	InputComponent* inputComp_;
	PhysicsComponent* physicsComp_;
	RenderComponent* renderComp_;
	InputComponent* acelerationComp_;
	InputComponent* gunInputComp_;

	StarWarsBulletsManager* starWarsManager_;
};

#endif /* EXAMPLEGAME_H_ */
