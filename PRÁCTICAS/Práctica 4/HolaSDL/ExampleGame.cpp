#include "ExampleGame.h"
#include "DemoActor.h"
#include "Collisions.h"
#include "BasicKBCtrlComponent.h"
#include "BasicMotionPhysics.h"
#include "FillRectRenderer.h"
#include "ImageRenderer.h"
#include "RotationInputComponent.h"
#include "CircularMotionPhysics.h"
#include "AcelerationInputComponent.h"
#include "GunInputComponent.h"

ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), bulletsManager_(this),fightersManager_(this,&bulletsManager_),astroidsManager_(this),
	collisionManager_(this,&bulletsManager_,&astroidsManager_,&fightersManager_),gameManager_(this),soundManager_(this)
{

	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}


void ExampleGame::initGame() {

	SDL_ShowCursor(0);

	bulletsManager_.registerObserver(&gameManager_);
	bulletsManager_.registerObserver(&fightersManager_);
	bulletsManager_.registerObserver(&astroidsManager_);
	bulletsManager_.registerObserver(&soundManager_);

	astroidsManager_.registerObserver(&bulletsManager_);
	astroidsManager_.registerObserver(&gameManager_);
	astroidsManager_.registerObserver(&fightersManager_);
	astroidsManager_.registerObserver(&soundManager_);

	collisionManager_.registerObserver(&astroidsManager_);
	collisionManager_.registerObserver(&gameManager_);
	collisionManager_.registerObserver(&bulletsManager_);
	collisionManager_.registerObserver(&fightersManager_);
	collisionManager_.registerObserver(&soundManager_);

	gameManager_.registerObserver(&astroidsManager_);
	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&bulletsManager_);
	gameManager_.registerObserver(&soundManager_);

	actors_.push_back(&bulletsManager_);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&astroidsManager_);
	actors_.push_back(&collisionManager_);
	actors_.push_back(&gameManager_);

}

void ExampleGame::closeGame() {
	
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);
		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
	
	
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x0000000));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

