#include "SoundManager.h"




SoundManager::SoundManager(SDLGame * game)
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::receive(Message * msg)
{
	switch (msg->id_) {
	case BULLET_CREATED:
		break;
	case BULLET_ASTROID_COLLISION:

		break;
	case ASTROID_FIGHTER_COLLISION:

		break;
	case ROUND_START:

		break;
	case ROUND_OVER:

		break;
	}
}
