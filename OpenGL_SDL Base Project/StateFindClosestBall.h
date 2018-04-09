#pragma once
#include "State.h"
#include "GameScreenManager.h"

class StateFindClosestBall :
	public State
{
public:
	StateFindClosestBall();
	~StateFindClosestBall();

	void Enter(AICharacter* agent)override;
	void During(AICharacter* agent, float deltaTime)override;
	void Exit(AICharacter* agent)override;
private:
	//GameObject* mClosestBall;
};

