#include "BadgeRenderer.h"



BadgeRenderer::BadgeRenderer(SDLGame* game)
{
	badgeIMG_ = game->getResources()->getImageTexture(Resources::Badge);
	destRect_ = { game->getWindowWidth() - 128, 0, 128, 128 };

}


BadgeRenderer::~BadgeRenderer()
{
}

void BadgeRenderer::render(GameObject * o, Uint32 time)
{
	badgeIMG_->render(o->getGame()->getRenderer(), destRect_);
}
