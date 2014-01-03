#pragma once

#include <vector>
#include "SpriteSequence.h"
#include "KeyMatcher.h"

class State {

private:
	SpriteSequence* spriteSequence;
	std::vector<KeyMatcher*> events;
	bool stoppable;

public:

	State(SpriteSequence* spriteSequence, std::vector<KeyMatcher*> events, bool stoppable);
	~State(void);

	bool isStoppable();
	std::vector<KeyMatcher*> getEvents();
	SpriteSequence* getSpriteSequence();
};

