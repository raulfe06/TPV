#pragma once
#include "Container.h"

class Fighter :
	public Container
{
public:
	Fighter(SDLGame* game, int id);
	virtual ~Fighter();
	int getId() const { return id_; };
private:
	int id_;
};

