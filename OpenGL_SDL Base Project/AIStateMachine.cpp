#include "AIStateMachine.h"

AIStateMachine::AIStateMachine()
{
	mCurrentState = new StateFindClosestBall();
}

AIStateMachine::~AIStateMachine()
{
}

void AIStateMachine::Update(float deltaTime)
{
	mCurrentState->Update(mCharacter, deltaTime);
}

void AIStateMachine::ChangeState(State* newState)
{
	if (newState->CheckTransition(mCharacter) != mCurrentState->CheckTransition(mCharacter))
	{
		mCurrentState->Exit();
		mCurrentState = newState;
		mCurrentState->Enter();
	}
}
