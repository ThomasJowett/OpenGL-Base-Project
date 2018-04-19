#ifndef _STATE_H
#define _STATE_H

#include "AIStateMachine.h"


class AICharacter;

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

