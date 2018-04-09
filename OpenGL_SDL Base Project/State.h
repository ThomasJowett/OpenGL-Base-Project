#ifndef _STATE_H
#define _STATE_H

//#include "AIStateMachine.h"

class AICharacter;

enum STATES
{
	STATE_NONE = 0,
	STATE_FIND_CLOSEST_BALL,
	STATE_PICKUP_BALL,
	STATE_RETURN_TO_BASELINE,
	STATE_THROW_BALL,
	STATE_DODGE
};

class State
{
public:
	State() { ; }
	~State() { ; }

	virtual void Enter(AICharacter* agent) = 0;
	virtual void During(AICharacter* agent, float deltaTime) = 0;
	virtual void Exit(AICharacter* agent) = 0;
};

#endif // !_STATE_H

