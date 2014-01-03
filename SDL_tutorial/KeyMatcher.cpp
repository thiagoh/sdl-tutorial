#include "KeyMatcher.h"

void KeyMatcher::init() {

	_ix = 0;
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
	keys.push_back(key6);
};

KeyMatcher::KeyMatcher(ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int key7) : actionCallback(actionCallback) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
	keys.push_back(key6);
	keys.push_back(key7);
};

void KeyMatcher::reset() {

	_ix = 0;
}

std::vector<int> KeyMatcher::getKeys() {

	return keys;
}

int KeyMatcher::match(const Uint8* keys, int ticks) {

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

ActionCallback* KeyMatcher::getAction() {

	return actionCallback;
}

KeyMatcher::~KeyMatcher(void) {

}
