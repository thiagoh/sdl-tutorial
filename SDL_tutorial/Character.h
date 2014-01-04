#pragma once

#include<vector>
#include <map>
#include <sdl/SDL.h>
#include "KeyMatcher.h"
#include "SpritePiece.h"
#include "Body.h"
#include "Positioned.h"
#include "SpriteSequence.h"
#include "State.h"

/*
struct orderByPriority {

	bool operator()(const KeyMatcher & a, const KeyMatcher & b) {

		return b.getPriority() < a.getPriority();
	}
};
*/

class Character : public Positioned {

private:
	std::vector<State*> states;
	std::map<KeyMatcher, State*> keyMatcherToState;
	State* currentState;
	State* defaultState;

public:

	Character(int lookingTo, int x, int y);
	~Character();

	void draw();

	SDL_RendererFlip getDrawFlags();

	void updateLookingTo();

	int getDrawX();
	int getDrawY();

	int getMaxWidth();
	int getMaxHeight();

	Body getBody();

	int getCenterX();
	int getCenterY();

	State* getCurrentState();
	std::vector<State*> getStates();
	std::map<KeyMatcher, State*> getKeyMatcherToState();
	void setState(State* state);
	void setToDefaultState();
	State* getState();

	void addDefaultState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector);
	void addState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector, KeyMatcher* _event, bool stoppable);
	void addState(SDL_Surface* surface, std::vector<SpritePiece> spritePieceVector, std::vector<KeyMatcher*> events, bool stoppable);

	SDL_Surface * getBitmap();
	size_t size();
	size_t getIndex();

	SpritePiece currentSprite();
	SpritePiece nextSprite();
	SpritePiece nextSpriteCycling();
	bool hasNextSprite();
	bool isAnimating();
	bool isAnimationFinished();
};
