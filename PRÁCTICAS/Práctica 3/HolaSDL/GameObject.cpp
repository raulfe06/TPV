#include "GameObject.h"
#include "PlayState.h"


GameObject::GameObject()
{
}
GameObject::GameObject(PlayState* game)
{
	this->game = game;
}
GameObject::~GameObject()
{
}