#include "SpritePiece.h"

SpritePiece::SpritePiece(SDL_Surface* bitmap, int sx, int sy, int width, int height) 
	: bitmap(bitmap), sx(sx), sy(sy), Body(width, height) {

};

SpritePiece::~SpritePiece() {

};

SDL_Surface* SpritePiece::getBitmap() {

	return bitmap;
};

SDL_Rect SpritePiece::getClip() {

	SDL_Rect rect;
	rect.h = getHeight();
	rect.w = getWidth();
	rect.x = sx;
	rect.y = sy;

	return rect;
}