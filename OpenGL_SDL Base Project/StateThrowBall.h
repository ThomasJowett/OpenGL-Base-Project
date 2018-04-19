#pragma once
#include "State.h"
#include "StateFindClosestBall.h"
#include "GameScreenManager.h"

class StateThrowBall :
	public State
{
public:
	StateThrowBall();
	~StateThrowBall();

	void Enter(AICharacter* agent)override;
	void During(AICharacter* agent, float deltaTime) override;
	void Exit(AICharacter* agent)override;
};

