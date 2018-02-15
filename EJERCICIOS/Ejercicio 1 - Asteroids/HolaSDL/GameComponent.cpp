#include "GameComponent.h"

GameComponent::GameComponent(SDLGame* game) :
		GameObject(game), inputComp_(), physicsComp_(), renderComp_() {
}

GameComponent::~GameComponent() {
}

void GameComponent::handleInput(Uint32 time, const SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		ic->handleInput(this, time, event);
	}
}

void GameComponent::update(Uint32 time) {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(this, time);
	}
}

void GameComponent::render(Uint32 time) {
	for (RenderComponent* rc : renderComp_) {
		rc->render(this, time);
	}
}

void GameComponent::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void GameComponent::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void GameComponent::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void GameComponent::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end())
		physicsComp_.erase(position);
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}
