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
	AIStateMachine();
	~AIStateMachine();
	AIStateMachine(Character* character) :mCharacter(character) { ; }
	void Update(float deltaTime);
private:
	State* mCurrentState;
	Character* mCharacter;
	void ChangeState();
};
#endif // !_AISTATEMACHINE_H
