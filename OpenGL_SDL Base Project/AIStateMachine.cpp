#include "AIStateMachine.h"

AICharacter::AICharacter(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:Character(name, transform, appearance, particle, collider, forward)
{
	//mCurrentState->Enter(this);
	mCurrentState = nullptr;
}

AICharacter::~AICharacter()
{
}

void AICharacter::Update(float deltaTime)
{
	if (mCurrentState)
		mCurrentState->During(this, deltaTime);
	Character::Update(deltaTime);
}

void AICharacter::ChangeState(State* newState)
{
	if (newState != mCurrentState)
	{
		mPreviousState = mCurrentState;
		if(mCurrentState)
			mCurrentState->Exit(this);
		mCurrentState = newState;
		if(mCurrentState)
			mCurrentState->Enter(this);
	}
}

void AICharacter::RevertToPreviousState()
{
	ChangeState(mPreviousState);
}

bool AICharacter::IsInState(const State* & state) const
{
	return (state == mCurrentState) ? true : false;
}
