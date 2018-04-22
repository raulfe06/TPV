#pragma once
#include "Container.h"

const int defFWidth = 20;
const int defFHeight = 20;

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

