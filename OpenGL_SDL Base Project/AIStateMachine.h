#ifndef _AISTATEMACHINE_H
#define _AISTATEMACHINE_H

#include "State.h"
#include "Character.h"

class AIStateMachine
{
public:
	AIStateMachine(Character* character) :mCharacter(character) { ; }
	void Update(float deltaTime);
private:
	State mCurrentState;
	Character* mCharacter;
	void ChangeState(State newState);
};
#endif // !_AISTATEMACHINE_H
