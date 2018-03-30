#include "LiveRenderer.h"
#include "GameManager.h"

LiveRenderer::LiveRenderer(SDLGame * game)
{
	lifeIMG_ = game->getResources()->getImageTexture(Resources::Life);
	
}

LiveRenderer::~LiveRenderer()
{
}

void LiveRenderer::render(GameObject * o, Uint32 time)
{
	
	GameManager* gm = static_cast<GameManager*>(o);
	for (int i = 0; i <gm->getLives(); i++) {
		destRect_ = { (40*i),0,40,40 };
		lifeIMG_->render(gm->getGame()->getRenderer(), destRect_);
	}
}
