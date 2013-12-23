#pragma once

#include <sdl/SDL.h>

namespace LookingTo {
	
	enum {

		RIGHT = 1,
		LEFT = 2
	};
}

class SpritePiece {

private:
	int sx;
	int sy;
	SDL_Surface* bitmap;
	
public:

	float width;
	float height;
	
	SpritePiece(SDL_Surface* bitmap, int sx, int sy, float width, float height);
	~SpritePiece();
	
	SDL_Surface* getBitmap();
	SDL_Rect getClip();
	
};