#include "StateFindClosestBall.h"

StateFindClosestBall::StateFindClosestBall()
{
}


StateFindClosestBall::~StateFindClosestBall()
{
}

void StateFindClosestBall::Enter(AICharacter * agent)
{
	
}

void StateFindClosestBall::During(AICharacter* agent, float deltaTime)
{
	//find the closest game object with tag ball
	std::vector<GameObject*> gameObjects = GameScreenManager::GetInstance()->GetCurrentScreen()->GetAllGameObjectsWithTag("Ball");

	float closestDistance = FLT_MAX;
	float distance;

	for (GameObject* gameObject : gameObjects)
	{
		distance = (agent->GetTransform()->GetPosition() - gameObject->GetTransform()->GetPosition()).GetSqrMagnitude();
		if (distance < closestDistance)
		{
			closestDistance = distance;
			mClosestBall = gameObject;
		}
	}

	if (closestDistance < 10000.0f)
	{
		State* tempState = new StateReturnToBaseline();
		agent->ChangeState(tempState);
	}
	else
	{
		//move towards ball
		agent->MoveForward(deltaTime, 1.0);
	}

	
}

void StateFindClosestBall::Exit(AICharacter * agent)
{
}
