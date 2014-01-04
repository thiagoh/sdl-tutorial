#include "KeyMatcher.h"

void KeyMatcher::init() {

	_ix = 0;
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

	init();
	keys.push_back(key1);
	keys.push_back(key2);
	keys.push_back(key3);
	keys.push_back(key4);
	keys.push_back(key5);
	keys.push_back(key6);
};

KeyMatcher::KeyMatcher(std::string matcherId, ActionCallback* actionCallback, int key1, int key2, int key3, int key4, int key5, int key6, int key7, int priority) : keyMatcherId(matcherId), actionCallback(actionCallback), priority(priority) {

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

int KeyMatcher::getPriority() const {

	return priority;
}

std::string KeyMatcher::getKeyMatcherId() const {

	return keyMatcherId;
}

KeyMatcher::~KeyMatcher(void) {

}
