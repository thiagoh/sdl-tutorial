#pragma once

#include <sdl/SDL.h>
#include "Sprite.h"

class SpriteUtil {

public:
	SpriteUtil(void);
	~SpriteUtil(void);
	
	static Sprite process(const char * filename, SDL_Color delimiterColor);
};
