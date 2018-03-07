#pragma once
#include "Container.h"

class Fighter :
	public Container
{
public:
	Fighter(SDLGame* game, int id);
	virtual ~Fighter();
	int getId();
private:
	int id_;
};

