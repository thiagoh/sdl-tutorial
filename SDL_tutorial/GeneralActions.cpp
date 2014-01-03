#include "GeneralActions.h"
#include "Character.h"

int moveSpeed = 10;

void MoveRightAction::act(void* target) {

	Character* character = static_cast<Character*>(target);

	character->incX(moveSpeed);
}

void MoveLeftAction::act(void* target) {

	Character* character = static_cast<Character*>(target);

	character->decX(moveSpeed);
}