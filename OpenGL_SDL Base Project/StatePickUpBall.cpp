#include "StatePickUpBall.h"



StatePickUpBall::StatePickUpBall()
{
}


StatePickUpBall::~StatePickUpBall()
{
}

void StatePickUpBall::Update(Character* character, float deltaTime)
{
	//Attach ball to character
}

int StatePickUpBall::CheckTransition(Character * character)
{
	//return character->HasBall() ? STATE_RETURN_TO_BASELINE : STATE_PICKUP_BALL;
	return STATE_NONE;
}
