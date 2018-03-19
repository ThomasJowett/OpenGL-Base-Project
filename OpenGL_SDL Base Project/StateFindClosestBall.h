#pragma once
#include "State.h"
#include "StatePickUpBall.h"
class StateFindClosestBall :
	public State
{
public:
	StateFindClosestBall();
	~StateFindClosestBall();

	void Update(Character* character, float deltaTime);
	int GetState() { return STAE_FIND_CLOSEST_BALL; }
	int CheckTransition(Character* character);
private:
	GameObject* mClosestBall;
};

