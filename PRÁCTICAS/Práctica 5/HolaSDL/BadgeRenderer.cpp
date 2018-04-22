#include "BadgeRenderer.h"



BadgeRenderer::BadgeRenderer(SDLGame* game,Resources::ImageId badgeImage)
{
	badgeIMG_ = game->getResources()->getImageTexture(badgeImage);
	destRect_ = { game->getWindowWidth() - BADGE_SIZE, 0, BADGE_SIZE, BADGE_SIZE };

}


BadgeRenderer::~BadgeRenderer()
{
}

void BadgeRenderer::render(GameObject * o, Uint32 time)
{
	badgeIMG_->render(o->getGame()->getRenderer(), destRect_);
}
