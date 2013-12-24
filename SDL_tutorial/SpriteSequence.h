#pragma once

#include <sdl/SDL.h>
#include<vector>
#include <map>
#include "SpritePiece.h"

class SpriteSequence {

private:
	SDL_Surface* bitmap;
	bool stoppable;
	bool finished;
	std::vector<SpritePiece> sprites;
	unsigned int _curIndex;

public:

	SpriteSequence(SDL_Surface* bitmap, std::vector<SpritePiece> sprites, bool stoppable) : bitmap(bitmap), sprites(sprites), stoppable(stoppable), _curIndex(0), finished(false) {

	}

	bool isStoppable() {

		return stoppable;
	}

	size_t size() {

		return sprites.size();
	}

	std::vector<SpritePiece> getSprites() {

		return sprites;
	}

	SDL_Surface* getBitmap() {

		return bitmap;
	}

	SpritePiece current() {

		return sprites[_curIndex];
	}

	SpritePiece next() {

		if (!hasNext())
			return current();

		SpritePiece spritePiece = sprites[++_curIndex];

		if (!hasNext())
			finished = true;

		return spritePiece;
	}

	SpritePiece nextCycling() {

		if (hasNext()) {

			return sprites[++_curIndex];

		} else {

			finished = true;
			reset();
			return sprites[_curIndex];
		}
	}

	bool isFinished() {

		return finished;
	}

	size_t getIndex() {

		return _curIndex;
	}

	bool hasNext() {

		return _curIndex + 1 < size();
	};

	void reset() {

		_curIndex = 0;
		finished = false;
	};
};
