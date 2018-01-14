#include "SDL.h"
#include "SDL_image.h"
#include"Texture.h"
#include <iostream>
#include "Font.h"

using namespace std;


// A) LIBERA LA TEXTURA Y EL PUNTERO, Y RESETEA EL TAMAÑO DE LA TEXTURA A 0
void Texture::Free()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}


// B) DADO UN ARCHIVO DE IMAGEN, CARGA LA TEXTURA
bool Texture::Load(SDL_Renderer* renderer, string filename, int numRows, int numCols)
{

	this->numRows = numRows;
	this->numCols = numCols;

	SDL_Surface* tempSurface = IMG_Load(filename.c_str());

	if (tempSurface != nullptr)
	{
		Free();
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (texture != nullptr)
		{
			w = tempSurface->w;
			h = tempSurface->h;
			fw = w / numCols;
			fh = h / numRows;
			SDL_FreeSurface(tempSurface);

			return texture != nullptr;
		}
		else
			return false;
	}
	return texture != nullptr;
}


// C) RENDERIZA LA TEXTURA COMPLETA EN UN RECTÁNGULO DESTINO
void Texture::Render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip)
{
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}


// D) RENDERIZA PARTE DE UNA TEXTURA EN UN RECTÁNGULO DESTINO
void Texture::RenderFrame(SDL_Renderer* renderer, int row, int col, const SDL_Rect& destRect, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	srcRect.w = fw; srcRect.h = fh;
	srcRect.x = col * fw;
	srcRect.y = row * fh;

	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
void Texture::renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int	row, int col, int divH, int divW) {
	SDL_Rect srcRect;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	fw = w / divW;
	fh = h / divH;
	srcRect.w = fw; srcRect.h = fh;
	srcRect.x = col * fw;
	srcRect.y = row * fh;
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

}
bool Texture::loadFromText(SDL_Renderer* renderer, string text, const Font& font, SDL_Color	color) {
	SDL_Surface* textSurface = font.generateSurface(text, color);
	if (textSurface == nullptr)
		cout << "Unable	to	render	text	surface!	SDL_ttf	Error:	"
		<< TTF_GetError() << "\n";
	else {
		Free();
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr) {
			cout << "Unable	to	create	texture	from	text!	SDL	Error:	"
				<< SDL_GetError() << "\n";
			w = h = 0;
		}
		else {
			w = textSurface->w;
			h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return	texture != nullptr;
}

// DESTRUCTORA
Texture::~Texture() {
	Free();
}