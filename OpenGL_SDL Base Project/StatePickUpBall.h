#pragma once
#include "State.h"
class StatePickUpBall :public State
{
public:
	StatePickUpBall();
	~StatePickUpBall();

	void Update(Character* character, float deltaTime) override;
	int CheckTransition(Character* character) override;
};

