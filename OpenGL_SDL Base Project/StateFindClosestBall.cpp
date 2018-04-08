#include "StateFindClosestBall.h"

StateFindClosestBall::StateFindClosestBall()
{
}


StateFindClosestBall::~StateFindClosestBall()
{
}

void StateFindClosestBall::Update(Character * character, float deltaTime)
{
	//GameScreenManager::GetInstance()->GetCurrentScreen()->GetAllGameObjects();
	//find the closest game object with tag ball
}

State* StateFindClosestBall::CheckTransition(Character * character)
{
	/*
	if ((character->GetTransform()->GetPosition() - mClosestBall->GetTransform()->GetPosition()).GetMagnitude() < 100.0f)
	{
		StatePickUpBall* tempState;
		return tempState;
	}
	else
	{
		return this;
	}*/

	return this;
}
