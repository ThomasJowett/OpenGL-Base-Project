#include "AIStateMachine.h"

AICharacter::AICharacter(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward, State* initialState)
	:Character(name, transform, appearance, particle, collider, forward), mCurrentState(initialState)
{
	mCurrentState->Enter(this);
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

		mCurrentState->Exit(this);
		mCurrentState = newState;
		mCurrentState->Enter(this);
	}
}

void AICharacter::RevertToPreviousState()
{
	ChangeState(mPreviousState);
}
