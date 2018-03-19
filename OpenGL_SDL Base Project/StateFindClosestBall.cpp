#include "StateFindClosestBall.h"



StateFindClosestBall::StateFindClosestBall()
{
}


StateFindClosestBall::~StateFindClosestBall()
{
}

void StateFindClosestBall::Update(Character * character, float deltaTime)
{
	//find the closest game object with tag ball
}

int StateFindClosestBall::CheckTransition(Character * character)
{
	if ((character->GetTransform()->GetPosition() - mClosestBall->GetTransform()->GetPosition()).GetMagnitude() < 100.0f)
	{
		return STATE_PICKUP_BALL;
	}
	else
	{
		return STAE_FIND_CLOSEST_BALL;
	}
}
