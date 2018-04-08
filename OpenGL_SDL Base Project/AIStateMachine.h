#ifndef _AISTATEMACHINE_H
#define _AISTATEMACHINE_H

#include "State.h"
#include "StatePickUpBall.h"
#include "StateFindClosestBall.h"
//#include "StateReturnToBaseline.h"
//#include "StateThrowBall.h"
//#include "StateDodge.h"
//#include "Character.h"

class AIStateMachine
{
public:
	~AIStateMachine();
	AIStateMachine(Character* character);
	void Update(float deltaTime);
	void ChangeState(State* newState);
private:
	State* mCurrentState;
	Character* mCharacter;
};
#endif // !_AISTATEMACHINE_H
