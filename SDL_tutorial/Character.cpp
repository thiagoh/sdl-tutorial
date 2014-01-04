#include "Character.h"

Character::Character(int lookingTo, int x, int y) : Positioned(lookingTo, x, y), states() {
	currentState = 0;
};

Character::~Character() {

};

void Character::draw() {

	updateLookingTo();
}

SDL_RendererFlip Character::getDrawFlags() {

	if (!getInFrontOf())
		return SDL_FLIP_NONE;

	if (lookingTo == LookingTo::LEFT)
		return SDL_FLIP_HORIZONTAL;

	return SDL_FLIP_NONE;
};

void Character::updateLookingTo() {

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

int Character::getDrawX() {

	if (lookingTo == LookingTo::RIGHT)
		return x;

	return x - currentSprite().getWidth(); // is that correct
};

int Character::getDrawY() {

	return y - getMaxHeight();
};

State* Character::getCurrentState() {

	if (currentState == nullptr)
		return defaultState;

	return currentState;
};

std::vector<State*> Character::getStates() {

	return states;
}

std::map<KeyMatcher, State*, orderByPriority> Character::getKeyMatcherToState() {

	return keyMatcherToState;
}

int Character::getMaxWidth() {

	return getCurrentState()->getSpriteSequence()->getWidth();
}

int Character::getMaxHeight() {

	return getCurrentState()->getSpriteSequence()->getHeight();
}

Body Character::getBody() {

	return currentSprite();
}

int Character::getCenterX() {

	return x + (currentSprite().getWidth() / 2);
};

int Character::getCenterY() {

	return y + (currentSprite().getHeight() / 2);
};

void Character::setState(State* state) {

	if (currentState == state)
		return;

	currentState = state;
	currentState->getSpriteSequence()->reset();
}

void Character::setToDefaultState() {

	currentState = defaultState;
}

State* Character::getState() {

	return currentState;
}

void Character::addDefaultState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector) {

	SpriteSequence * spriteSeq = new SpriteSequence(surface, spritePieceVector);
	std::vector<KeyMatcher*> events;

	State * state = new State(spriteSeq, events, true);

	states.insert(states.begin(), state);

	defaultState = state;
}

void Character::addState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector, KeyMatcher* _event, bool stoppable = false) {

	std::vector<KeyMatcher*> events;
	events.push_back(_event);

	addState(surface, spritePieceVector, events, stoppable);
}

void Character::addState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector, std::vector<KeyMatcher*> events, bool stoppable = false) {

	SpriteSequence * spriteSeq = new SpriteSequence(surface, spritePieceVector);

	State * state = new State(spriteSeq, events, stoppable);

	for (std::vector<KeyMatcher*>::iterator it = events.begin(); it != events.end(); it++) {

		keyMatcherToState[**it] = state;
	}

	states.push_back(state);
}

SDL_Surface* Character::getBitmap() {

	return getCurrentState()->getSpriteSequence()->getBitmap();
};

size_t Character::size() {

	return getCurrentState()->getSpriteSequence()->size();
};

size_t Character::getIndex() {

	return getCurrentState()->getSpriteSequence()->getIndex();
}

SpritePiece Character::currentSprite() {

	return getCurrentState()->getSpriteSequence()->current();
}

SpritePiece Character::nextSprite() {

	return getCurrentState()->getSpriteSequence()->next();
}

SpritePiece Character::nextSpriteCycling() {

	return getCurrentState()->getSpriteSequence()->nextCycling();
}

bool Character::hasNextSprite() {

	return getCurrentState()->getSpriteSequence()->hasNext();
}

bool Character::isAnimating() {

	State* state = getCurrentState();
	SpriteSequence * spriteSeq = state->getSpriteSequence();

	if (!state->isStoppable() && !spriteSeq->isFinished() && spriteSeq->hasNext())
		return true;

	return false;
}

bool Character::isAnimationFinished() {

	State* state = getCurrentState();
	SpriteSequence * spriteSeq = state->getSpriteSequence();

	return spriteSeq->isFinished() || !spriteSeq->hasNext();
}
