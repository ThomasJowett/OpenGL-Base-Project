#pragma once
#include "State.h"
class StatePickUpBall :public State
{
public:
	StatePickUpBall();
	~StatePickUpBall();

	void During(Character* character, float deltaTime) override;
	State* CheckTransition(Character* character) override;
};

