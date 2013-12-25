#pragma once

#include "Conf.h"
#include "Body.h"
#include <sdl/SDL.h>

namespace LookingTo {

	enum {

		RIGHT = 1,
		LEFT = 2
	};
}

class Positioned {

protected:
	int x;
	int y;
	int lookingTo;
	Positioned * inFrontOf;

public:

	Positioned(int lookingTo, int x, int y) : x(x), y(y), lookingTo(lookingTo) {

		inFrontOf = 0;
	}

	Positioned* getInFrontOf() {

		return inFrontOf;
	}

	void setInFrontOf(Positioned * inFrontOf) {

		this->inFrontOf = inFrontOf;
	}

	int getX() {

		return x;
	};

	int getY() {

		return y;
	};

	void setX(int x) {

		this->x = x;
	};

	void setY(int y) {

		if (y > BOTTOM_BOUNDARY_Y)
			return;

		this->y = y;
	};

	void incX(int delta) {

		this->x += delta;
	};

	void incY(int delta) {

		if (y + delta > BOTTOM_BOUNDARY_Y)
			return;

		this->y += delta;
	};

	void decX(int delta) {

		this->x -= delta;
	};

	void decY(int delta) {

		this->y -= delta;
	};

};
