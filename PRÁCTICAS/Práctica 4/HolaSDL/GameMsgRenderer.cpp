#include "GameMsgRenderer.h"
#include <string>


GameMsgRenderer::GameMsgRenderer(SDLGame * game, std::string text) : game_(game)
{
	text_ = new Texture(game->getRenderer(), text, *game->getResources()->getFont(Resources::ARIAL24), SDL_Color{ 255,255,0 });
	dest_ = { game->getWindowWidth()/2-200,game->getWindowHeight()/2+50,400,100 };
}

GameMsgRenderer::~GameMsgRenderer()
{
}

void GameMsgRenderer::render(GameObject * o, Uint32 time)
{
	text_->render(game_->getRenderer(), dest_);
}
