#include "SpriteUtil.h"
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>

SpriteUtil::SpriteUtil(void)
{
}

SpriteUtil::~SpriteUtil(void)
{
}


Sprite SpriteUtil::process(const char * filename, SDL_Color delimiterColor) {

	SDL_Surface* bitmap = IMG_Load(filename);

	SDL_PixelFormat* format = bitmap->format;
	Uint32* pixels = (Uint32*) bitmap->pixels;
	Uint32 pixel, lastPixel = 0;
	Uint32 delimiterColorPixel = SDL_MapRGBA(format, delimiterColor.r, delimiterColor.g, delimiterColor.b, delimiterColor.a);

	Sprite sprite(bitmap, 0, 0);

	int lastSource = 0;

	for(int i = 0; i < bitmap->w; i++) {

		pixel = pixels[i];

		if (pixel != lastPixel) {

			if (pixel == delimiterColorPixel) {

				i++; // current pixel is the red one, so, advance to next pixel

				if (sprite.empty()) {

					sprite.add(SpritePiece(bitmap, 0, 0, i, bitmap->h));

				} else {

					sprite.add(SpritePiece(bitmap, lastSource, 0, i - lastSource, bitmap->h));
				}

				lastSource = i;
			}

		} else if(i == bitmap->w - 1) {

			sprite.add(SpritePiece(bitmap, lastSource, 0, i - lastSource, bitmap->h));
		}

		lastPixel = pixel;
	}

	SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 255, 0, 0));
	//al_convert_mask_to_alpha(bitmap, al_map_rgba(255, 0, 0, 255));

	return sprite;
}