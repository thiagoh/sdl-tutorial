#include "State.h"

State::State(SpriteSequence* spriteSequence, std::vector<KeyMatcher*> events, bool stoppable) : spriteSequence(spriteSequence), events(events), stoppable(stoppable) {
};

State::~State(void) {
};

bool State::isStoppable() {

	return stoppable;
}

std::vector<KeyMatcher*> State::getEvents() {
	return events;
}

SpriteSequence* State::getSpriteSequence() {
	return spriteSequence;
}


