#include "Fighter.h"



Fighter::Fighter(SDLGame* game, int id) : Container(game)
{
	setWidth(defFWidth);
	setHeight(defFHeight);
}


Fighter::~Fighter()
{
}
