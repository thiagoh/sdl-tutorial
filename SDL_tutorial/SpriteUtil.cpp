#include "SpriteUtil.h"

SpriteUtil::SpriteUtil(void)
{
}

SpriteUtil::~SpriteUtil(void)
{
}


SpriteSeq SpriteUtil::process(const char * filename, ALLEGRO_COLOR delimiterColor) {

	#ifndef _AL_INIT_IMAGE_ADDON
	#define _AL_INIT_IMAGE_ADDON
	al_init_image_addon();
	#endif

	ALLEGRO_BITMAP *bitmap = al_load_bitmap(filename);

	SpriteSeq spriteSeq(bitmap, 0, 0);

	ALLEGRO_COLOR pixel, lastPixel;
	int lastSource = 0;

	for(int i = 0; i <al_get_bitmap_width(bitmap); i++) {

		pixel = al_get_pixel(bitmap, i, 0);

		if (memcmp(&pixel, &lastPixel, sizeof(ALLEGRO_COLOR))) {

			if (!memcmp(&pixel, &delimiterColor, sizeof(ALLEGRO_COLOR))) {

				i++; // current pixel is the red one, so, advance to next pixel
				
				if (spriteSeq.empty()) {

					spriteSeq.add(Sprite(bitmap, 0, 0, i, al_get_bitmap_height(bitmap)));

				} else {

					spriteSeq.add(Sprite(bitmap, lastSource, 0, i - lastSource, al_get_bitmap_height(bitmap)));
				}

				lastSource = i;
			}

		} else if(i == al_get_bitmap_width(bitmap) - 1) {

			spriteSeq.add(Sprite(bitmap, lastSource, 0, i - lastSource, al_get_bitmap_height(bitmap)));
		}

		lastPixel = pixel;
	}

	al_convert_mask_to_alpha(bitmap, al_map_rgba(255, 0, 0, 255));
	
	return spriteSeq;
}