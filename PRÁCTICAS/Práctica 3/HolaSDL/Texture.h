#pragma once
#include <string>
#include "SDL.h"
#include "Font.h"
#include "checkML.h"

using namespace std;
/*
Clase Texture: Carga las texturas y las renderiza en cada determinado rectángulo

1) Carga la textura del archivo que se le dé
2) Renderiza la textura (o parte de ella, por frames) en un rectángulo destino

*/
class  Texture
{
private:
	// Punteros a la textura y renderer 
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Tamaño de la textura ( en píxels)
	int w = 0;
	int h = 0;

	// Tamaño del frame (en píxels)
	int fw = 0;
	int fh = 0;

	// Filas y columnas del SpriteSheet (por defecto a 1, como una textura completa)
	int numRows = 1;
	int numCols = 1;

public:

	// Libera la textura guardada y su puntero
	void Free();
	~Texture();

	// Carga la textura de un archivo de imagen
	bool Load(SDL_Renderer* renderer, string filename, int numRows = 1, int numCols = 1);

	// Renderiza la textura completa en un rectángulo destino
	void Render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Renderiza un frame de la textura en un rectángulo destino
	void RenderFrame(SDL_Renderer* renderer, int row, int col, const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int	row, int col, int divH, int divW);

	bool loadFromText(SDL_Renderer* renderer, string text, const Font& font, SDL_Color	color);
};
