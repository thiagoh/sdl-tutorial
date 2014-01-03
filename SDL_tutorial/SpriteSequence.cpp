#include "SpriteSequence.h"

SpriteSequence::SpriteSequence(SDL_Surface* bitmap, std::vector<SpritePiece> sprites) : bitmap(bitmap), sprites(sprites), _curIndex(0), finished(false), Body() {

	std::vector<SpritePiece>::iterator s = std::max_element(sprites.begin(), sprites.end(), SpriteSequence::cmpW);

	setWidth((*s).getWidth());
	setHeight((*s).getHeight());
};

SpriteSequence::~SpriteSequence(void) {

};

size_t SpriteSequence::size() {

	return sprites.size();
};

std::vector<SpritePiece> SpriteSequence::getSprites() {

	return sprites;
};

SDL_Surface* SpriteSequence::getBitmap() {

	return bitmap;
};

SpritePiece SpriteSequence::current() {

	return sprites[_curIndex];
};

SpritePiece SpriteSequence::next() {

	if (!hasNext())
		return current();

	SpritePiece spritePiece = sprites[++_curIndex];

	if (!hasNext())
		finished = true;

	return spritePiece;
};

SpritePiece SpriteSequence::nextCycling() {

	if (hasNext()) {

		return sprites[++_curIndex];

	} else {

		finished = true;
		reset();
		return sprites[_curIndex];
	}
};

bool SpriteSequence::isFinished() {

	return finished;
};

size_t SpriteSequence::getIndex() {

	return _curIndex;
};

bool SpriteSequence::hasNext() {

	return _curIndex + 1 < size();
};

void SpriteSequence::reset() {

	_curIndex = 0;
	finished = false;
};
