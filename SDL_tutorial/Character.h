#pragma once

#include<vector>
#include <map>
#include <sdl/SDL.h>
#include "SpritePiece.h"
#include "Body.h"
#include "Positioned.h"
#include "SpriteSequence.h"

class Character : public Positioned {

private:
	int currentState;
	std::map<int, SpriteSequence> spriteMap;

public:

	Character(int lookingTo, int x, int y) : Positioned(lookingTo, x, y), spriteMap() {

	};

	~Character() {

	};

	void draw() {

		updateLookingTo();
	}

	SDL_RendererFlip getDrawFlags() {

		if (!getInFrontOf())
			return SDL_FLIP_NONE;

		if (lookingTo == LookingTo::LEFT)
			return SDL_FLIP_HORIZONTAL;

		return SDL_FLIP_NONE;
	};

	void updateLookingTo() {

		if (!getInFrontOf())
			return;	

		Character* characterInFrontOf = (Character*) getInFrontOf();

		if (lookingTo == LookingTo::RIGHT) {

			if (getX() + (getMaxWidth() / 2) > characterInFrontOf->getX() - (characterInFrontOf->getMaxWidth() / 2)) {

				lookingTo = LookingTo::LEFT;
				incX(getMaxWidth());
			}

		} else if (lookingTo == LookingTo::LEFT) {

			if (getX() - (getMaxWidth() / 2) < getInFrontOf()->getX() + (characterInFrontOf->getMaxWidth() / 2)) {

				lookingTo = LookingTo::RIGHT;
				decX(getMaxWidth());
			}
		}
	};

	int getDrawX() {

		if (lookingTo == LookingTo::RIGHT)
			return x;

		return x - currentSprite().getWidth(); // is that correct
		//return x - getMaxWidth();//
	};

	int getDrawY() {

		return y - getMaxHeight();
	};

	int getMaxWidth() {

		return spriteMap.at(currentState).getWidth();
	}

	int getMaxHeight() {

		return spriteMap.at(currentState).getHeight();
	}

	Body getBody() {

		return currentSprite();
	}

	int getCenterX() {

		return x + (currentSprite().getWidth() / 2);
	};

	int getCenterY() {

		return y + (currentSprite().getHeight() / 2);
	};

	void setState(int state) {

		if (currentState == state)
			return;

		currentState = state;
		spriteMap.at(currentState).reset();
	}

	int getState() {

		return currentState;
	}

	void addState(int state, SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector, bool stoppable = false) {

		SpriteSequence spriteSeq(surface, spritePieceVector, stoppable);

		spriteMap.insert(std::pair<int, SpriteSequence>(state, spriteSeq));
	}

	SDL_Surface * getBitmap() {

		return spriteMap.at(currentState).getBitmap();
	};

	size_t size() {

		return spriteMap.at(currentState).size();
	};

	size_t getIndex() {

		return spriteMap.at(currentState).getIndex();
	}

	SpritePiece currentSprite() {

		return spriteMap.at(currentState).current();
	}

	SpritePiece nextSprite() {

		return spriteMap.at(currentState).next();
	}

	SpritePiece nextSpriteCycling() {

		return spriteMap.at(currentState).nextCycling();
	}

	bool hasNextSprite() {

		return spriteMap.at(currentState).hasNext();
	}

	bool isAnimating() {

		SpriteSequence spriteSeq = spriteMap.at(currentState);

		if (!spriteSeq.isStoppable() && !spriteSeq.isFinished() && spriteSeq.hasNext())
			return true;

		return false;
	}

	bool isAnimationFinished() {

		SpriteSequence spriteSeq = spriteMap.at(currentState);

		return spriteSeq.isFinished() || !spriteSeq.hasNext();
	}
};
