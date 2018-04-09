#pragma once
#include "State.h"
class StatePickUpBall :public State
{
public:
	StatePickUpBall();
	~StatePickUpBall();

	void Enter(AICharacter* agent)override;
	void During(AICharacter* agent, float deltaTime) override;
	void Exit(AICharacter* agent)override;
};

