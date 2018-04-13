#pragma once
#include "State.h"
#include "StateThrowBall.h"

class StateReturnToBaseline :public State
{
public:
	StateReturnToBaseline();
	~StateReturnToBaseline();

	void Enter(AICharacter* agent)override;
	void During(AICharacter* agent, float deltaTime) override;
	void Exit(AICharacter* agent)override;
};

