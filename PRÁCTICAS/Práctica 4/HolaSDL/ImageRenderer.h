#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* image, SDL_Rect src);

	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	Texture* image_;
	SDL_Rect src_;
};

#endif /* IMAGERENDERER_H_ */
