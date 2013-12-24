#pragma once

#include <sdl/SDL.h>
#include "Body.h"

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

	void setInFrontOf(Positioned * inFrontOf) {

		this->inFrontOf = inFrontOf;
	}

	virtual Body getBody() = 0;

	SDL_RendererFlip getDrawFlags() {

		if (!inFrontOf)
			return SDL_FLIP_NONE;

		updateLookingTo();

		if (lookingTo == LookingTo::LEFT)
			return SDL_FLIP_HORIZONTAL;

		return SDL_FLIP_NONE;
	};

	void updateLookingTo() {

		if (!inFrontOf)
			return;	

		if (lookingTo == LookingTo::RIGHT) {

			if (getRawX() + getBody().getWidth() > inFrontOf->getRawX()) {

				lookingTo = LookingTo::LEFT;
			}

		} else if (lookingTo == LookingTo::LEFT) {

			if (getRawX() < inFrontOf->getRawX() + inFrontOf->getBody().getWidth()) {

				lookingTo = LookingTo::RIGHT;
			}
		}
	};

	int getRawX() {

		return x;
	};

	int getX() {

		if (lookingTo == LookingTo::RIGHT)
			return x;

		return x - getBody().getWidth();
	};

	int getY() {

		return y;
	};

	void setX(int x) {

		this->x = x;
	};

	void setY(int y) {

		this->y = y;
	};
};
