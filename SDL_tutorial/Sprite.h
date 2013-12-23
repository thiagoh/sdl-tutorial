#pragma once

#include<vector>
#include <sdl/SDL.h>
#include "SpritePiece.h"

class Positioned {
	
public:
	
	int virtual getCenterX() = 0;
	int virtual getCenterY() = 0;
};

class Sprite : public Positioned {

private:
	int x;
	int y;
	Positioned * inFrontOf;
	
	int lookingTo;
	bool lookingToUpdated;
	
	SDL_Surface * bitmap;
	std::vector<SpritePiece> sprites;
	unsigned int _curIndex;

public:

	Sprite(SDL_Surface* bitmap, int x, int y) : bitmap(bitmap), x(x), y(y), sprites(), _curIndex(0) {
		
		inFrontOf = 0;
		lookingTo = LookingTo::RIGHT;
		lookingToUpdated = false;
	};
	
	~Sprite() {
		
	};

	void setInFrontOf(Positioned * inFrontOf) {

		this->inFrontOf = inFrontOf;
	}

	int getDrawFlags() {

		if (!inFrontOf)
			return 0;
			
		updateLookingTo();
		
		if (lookingTo == LookingTo::LEFT)
			return SDL_FLIP_HORIZONTAL;

		return 0;
	};
	
	int virtual getCenterX() {

		return x + (current().width / 2);
	};

	int virtual getCenterY() {

		return y + (current().height / 2);
	};

	int virtual getX() {

		return x;
	};

	int virtual getY() {

		return y;
	};

	void updateLookingTo() {
	
		if (!inFrontOf)
			return;	
			
		int inFrontOfCenterX = inFrontOf->getCenterX();
			
		if (this->getCenterX() > inFrontOfCenterX && lookingTo != LookingTo::LEFT) {
		
			lookingTo = LookingTo::LEFT;
			lookingToUpdated = true;
			
		} else if (this->getCenterX() < inFrontOfCenterX && lookingTo != LookingTo::RIGHT) {
		
			lookingTo = LookingTo::RIGHT;
			lookingToUpdated = true;
		}
	};

	void setX(int x) {

		this->x = x;
	};

	void setY(int y) {

		this->y = y;
	};

	void incX(int delta) {

		this->x += delta;
	};

	void incY(int delta) {

		this->y += delta;
	};
	
	void decX(int delta) {

		this->x -= delta;
	};

	void decY(int delta) {

		this->y -= delta;
	};
	
	SDL_Surface * getBitmap() {

		return bitmap;
	};

	void add(SpritePiece SpritePiece) {

		sprites.push_back(SpritePiece);
	};

	bool empty() {

		return sprites.empty();
	};

	size_t size() {

		return sprites.size();
	};

	size_t getIndex() {

		return _curIndex;
	}

	bool hasNext() {

		return _curIndex + 1 < sprites.size();
	};

	void reset() {

		_curIndex = 0;
	};
	
	SpritePiece current() {

		return sprites[_curIndex];
	}

	SpritePiece next() {
	
		if (!hasNext())
			return current();
			
		return sprites[_curIndex++];
	}
};
