#pragma once

#include <sdl/SDL.h>
#include "Body.h"

class SpritePiece : public Body {

private:
	int sx;
	int sy;
	SDL_Surface* bitmap;
	
public:

	SpritePiece(SDL_Surface* bitmap, int sx, int sy, int width, int height);
	~SpritePiece();
	
	SDL_Surface* getBitmap();
	SDL_Rect getClip();
};