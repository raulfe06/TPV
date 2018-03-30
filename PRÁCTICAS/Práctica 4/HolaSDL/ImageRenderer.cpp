#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image,SDL_Rect src) : image_(image),src_(src) {
}


ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());
	
	Vector2D a(0, -1);
	Vector2D b = o->getDirection();
	double angle = a.angle(b);

	image_->render(o->getGame()->getRenderer(), rect,angle,&src_);
}
