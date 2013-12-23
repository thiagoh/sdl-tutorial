#include "SpritePiece.h"

SpritePiece::SpritePiece(SDL_Surface* bitmap, int sx, int sy, float width, float height) 
	: bitmap(bitmap), sx(sx), sy(sy), width(width), height(height) {

};

SpritePiece::~SpritePiece() {

};

SDL_Surface* SpritePiece::getBitmap() {

	return bitmap;
};

SDL_Rect SpritePiece::getClip() {

	SDL_Rect rect;
	rect.h = height;
	rect.w = width;
	rect.x = sx;
	rect.y = sy;

	return rect;
}