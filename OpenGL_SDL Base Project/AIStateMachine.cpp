#include "AIStateMachine.h"

AIStateMachine::AIStateMachine(Character* character) :mCharacter(character)
{
	mCurrentState = new StateFindClosestBall();
	mCurrentState->Enter();
}

AIStateMachine::~AIStateMachine()
{
}

void AIStateMachine::Update(float deltaTime)
{
	if (mCurrentState)
		mCurrentState->During(mCharacter, deltaTime);

	ChangeState(mCurrentState->CheckTransition(mCharacter));
}

void AIStateMachine::ChangeState(State* newState)
{
	if (newState != mCurrentState)
	{
		mCurrentState->Exit();
		mCurrentState = newState;
		mCurrentState->Enter();
	}
}
