#pragma once
#include "State.h"
#include "StatePickUpBall.h"
#include "GameScreenManager.h"

class GameScreenManager;

class StateFindClosestBall :
	public State
{
public:
	StateFindClosestBall();
	~StateFindClosestBall();

	void Update(Character* character, float deltaTime);
	int GetState() { return STATE_FIND_CLOSEST_BALL; }
	State* CheckTransition(Character* character);
private:
	GameObject* mClosestBall;
};

