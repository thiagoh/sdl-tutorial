#include "Event.h"


void Event::init() {

	_ix = 0;
}

Event::Event(int key1) {

	init();
	keys.push_back(key1);
}
Event::Event(int key1, int key2) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
}
Event::Event(int key1, int key2, int key3) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
}
Event::Event(int key1, int key2, int key3, int key4) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
}
Event::Event(int key1, int key2, int key3, int key4, int key5) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
}
Event::Event(int key1, int key2, int key3, int key4, int key5, int key6) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
	keys.push_back(key6);
}
Event::Event(int key1, int key2, int key3, int key4, int key5, int key6, int key7) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
	keys.push_back(key6);
	keys.push_back(key7);
}

void Event::reset() {

	_ix = 0;
}

std::vector<int> Event::getKeys() {

	return keys;
}

int Event::match(const Uint8* keys, int ticks) {

	if (_ix > 0 && ticks > 200) {

		_ix = 0;
		printf("No match by time\n");
		return EventMatch::MATCH_NO_MATCH;
	}

	if (keys[this->keys[_ix]]) {

		if (this->keys.size() == (_ix + 1)) {

			_ix = 0;
			printf("Full Match %d\n", this->keys[_ix]);
			return EventMatch::MATCH_COMPLETE;

		} else {

			printf("Match %d\n", this->keys[_ix]);
			_ix++;
			return EventMatch::MATCH_PARTIALLY;
		}

	} else {

		if (_ix > 0) {

			printf("Match Partial\n");
			return EventMatch::MATCH_PARTIALLY;

		} else {

			printf("No Match by keys\n");
			return EventMatch::MATCH_NO_MATCH;
		}
	}
}

Event::~Event(void) {

}
