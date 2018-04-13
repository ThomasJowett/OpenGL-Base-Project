#ifndef _AISTATEMACHINE_H
#define _AISTATEMACHINE_H

#include "State.h"
#include "Character.h"

class State;

class AICharacter : public Character
{
public:
	~AICharacter();
	AICharacter(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);
	void Update(float deltaTime);
	void ChangeState(State* newState);
	void RevertToPreviousState();

	State* GetCurrentState() const { return mCurrentState; }
	State* GetPreviousState() const { return mPreviousState; }

	bool IsInState(const State*& state)const;
private:
	State* mCurrentState;
	State* mPreviousState;
};
#endif // !_AISTATEMACHINE_H
