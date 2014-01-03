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
	ActionCallback* actionCallback;
	std::vector<int> keys;
	void init();

public:
	KeyMatcher(ActionCallback* actionCallback, int key1);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6);
	KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int key7);

	std::vector<int> getKeys();
	void reset();
	int match(const Uint8* keys, int ticks);
	ActionCallback* getAction();

	~KeyMatcher(void);
};