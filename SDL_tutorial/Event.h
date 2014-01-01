#pragma once

#include <sdl/SDL.h>
#include <vector>

namespace EventMatch {

	enum {

		MATCH_NO_MATCH = 0,
		MATCH_PARTIALLY = 1,
		MATCH_COMPLETE = 2
	};
};

class Event {

private:
	int _ix;
	std::vector<int> keys;
	void init();

public:
	Event(int key1);
	Event(int key1, int key2);
	Event(int key1, int key2, int key3);
	Event(int key1, int key2, int key3, int key4);
	Event(int key1, int key2, int key3, int key4, int key5);
	Event(int key1, int key2, int key3, int key4, int key5, int key6);
	Event(int key1, int key2, int key3, int key4, int key5, int key6, int key7);

	std::vector<int> getKeys();
	void reset();
	int match(const Uint8* keys, int ticks);

	~Event(void);
};

