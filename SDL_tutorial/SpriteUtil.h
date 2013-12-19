#pragma once

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_image.h>
#include<vector>

namespace LookingTo {
	
	enum {

		RIGHT = 1,
		LEFT = 2
	};
}

class Positioned {
	
public:
	
	int virtual getCenterX() = 0;
	int virtual getCenterY() = 0;
};

class Sprite {

private:
	int sx;
	int sy;
	ALLEGRO_BITMAP * bitmap;
	
public:

	float width;
	float height;
	
	Sprite(ALLEGRO_BITMAP* bitmap, int sx, int sy, float width, float height) : bitmap(bitmap), sx(sx), sy(sy), width(width), height(height) {

	};
	
	~Sprite() {
	
	};
	
	ALLEGRO_BITMAP * getBitmap() {
		
		return bitmap;
	};
	
	ALLEGRO_BITMAP * getSubBitmap() {
	
		return al_create_sub_bitmap(bitmap, sx, sy, (int) width , (int) height);
	};
};

class SpriteSeq : public Positioned {

private:
	int x;
	int y;
	Positioned * inFrontOf;
	
	int lookingTo;
	bool lookingToUpdated;
	
	ALLEGRO_BITMAP * bitmap;
	std::vector<Sprite> sprites;
	unsigned int _curIndex;

public:

	SpriteSeq(ALLEGRO_BITMAP* bitmap, int x, int y) : bitmap(bitmap), x(x), y(y), sprites(), _curIndex(0) {
		
		inFrontOf = 0;
		lookingTo = LookingTo::RIGHT;
		lookingToUpdated = false;
	};
	
	~SpriteSeq() {
		
	};

	void setInFrontOf(Positioned * inFrontOf) {

		this->inFrontOf = inFrontOf;
	}

	int getDrawFlags() {

		if (!inFrontOf)
			return 0;
			
		updateLookingTo();
		
		if (lookingTo == LookingTo::LEFT)
			return ALLEGRO_FLIP_HORIZONTAL;

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

	void incX(int x) {

		this->x += x;
	};

	void incY(int y) {

		this->y += y;
	};
	
	void decX(int x) {

		this->x -= x;
	};

	void decY(int y) {

		this->y -= y;
	};
	
	ALLEGRO_BITMAP * getBitmap() {

		return bitmap;
	};

	ALLEGRO_BITMAP * getSubBitmap() {

		return current().getSubBitmap();
	};

	void add(Sprite sprite) {

		sprites.push_back(sprite);
	};

	bool empty() {

		return sprites.empty();
	};

	size_t size() {

		return sprites.size();
	};

	bool hasNext() {

		return _curIndex + 1 < sprites.size();
	};

	void reset() {

		_curIndex = 0;
	};
	
	Sprite current() {

		return sprites[_curIndex];
	}

	Sprite next() {
	
		if (!hasNext())
			return current();
			
		return sprites[_curIndex++];
	}
};

class SpriteUtil {

public:
	SpriteUtil(void);
	~SpriteUtil(void);
	
	static SpriteSeq process(const char * filename, ALLEGRO_COLOR delimiterColor);
};
