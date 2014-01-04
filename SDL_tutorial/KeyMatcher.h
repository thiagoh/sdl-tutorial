#pragma once

#include <sdl/SDL.h>
#include <vector>
#include "ActionCallback.h"

namespace EventMatch {

	enum {

		MATCH_NO_MATCH = 0,
		MATCH_PARTIALLY = 1,
		MATCH_COMPLETE = 2
	};
};

class KeyMatcher {

private:
	int _ix;
	std::string keyMatcherId;
	int priority;
	ActionCallback* actionCallback;
	std::vector<int> keys;
	void init();

public:
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int priority);
	KeyMatcher(std::string keyMatcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int key7, int priority);

	std::vector<int> getKeys();
	void reset();
	int match(const Uint8* keys, int ticks);
	ActionCallback* getAction();

	std::string getKeyMatcherId() const;
	int getPriority() const;

	bool operator<(const KeyMatcher & b) const {

		return getKeyMatcherId().compare(b.getKeyMatcherId()) < 0;
	};

	~KeyMatcher(void);
};