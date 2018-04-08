#include "StatePickUpBall.h"



StatePickUpBall::StatePickUpBall()
{
}


StatePickUpBall::~StatePickUpBall()
{
}

void StatePickUpBall::During(Character* character, float deltaTime)
{
	//Attach ball to character
}

State* StatePickUpBall::CheckTransition(Character * character)
{
	//return character->HasBall() ? STATE_RETURN_TO_BASELINE : STATE_PICKUP_BALL;
	return this;
}
