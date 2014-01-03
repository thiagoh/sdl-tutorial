#pragma once

#include <sdl/SDL.h>
#include<vector>
#include <map>
#include <algorithm>
#include "SpritePiece.h"

class SpriteSequence : public Body {

private:
	SDL_Surface* bitmap;
	bool finished;
	std::vector<SpritePiece> sprites;
	unsigned int _curIndex;
	static bool cmpW(SpritePiece& s1, SpritePiece& s2) { return s1.getWidth() < s2.getWidth(); }	

public:

	SpriteSequence(SDL_Surface* bitmap, std::vector<SpritePiece> sprites);
	~SpriteSequence(void);

	size_t size();
	std::vector<SpritePiece> getSprites();
	SDL_Surface* getBitmap();
	SpritePiece current();
	SpritePiece next();
	SpritePiece nextCycling();

	bool isFinished();
	size_t getIndex();
	bool hasNext();
	void reset();
};
