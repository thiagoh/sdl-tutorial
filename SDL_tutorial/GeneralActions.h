#pragma once

#include "ActionCallback.h"

class MoveRightAction : public ActionCallback {

public:
	void act(void* target);
};

class MoveLeftAction : public ActionCallback {
	
public:
	void act(void* target);
};