#pragma once
#include "State.h"
#include "StateReturnToBaseline.h"
 
#include "GameScreenManager.h"
#include "GameScreen.h"
#include "Level2Enemy.h"

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
	GameObject* mClosestBall;
};

