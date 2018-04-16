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

	if (closestDistance < 5000.0f)
	{
		agent->ChangeState(new StateReturnToBaseline());
	}
	else
	{
		if (mClosestBall->GetTransform()->GetPosition().x > agent->GetTransform()->GetPosition().x)
		{
			agent->MoveRight(deltaTime, 1.0);
		}
		else if (mClosestBall->GetTransform()->GetPosition().x < agent->GetTransform()->GetPosition().x)
		{
			agent->MoveRight(deltaTime, -1.0f);
		}

		if (mClosestBall->GetTransform()->GetPosition().z < agent->GetTransform()->GetPosition().z)
		{
			agent->MoveForward(deltaTime, 1.0);
		}
		else if (mClosestBall->GetTransform()->GetPosition().z > agent->GetTransform()->GetPosition().z)
		{
			agent->MoveForward(deltaTime, -1.0);
		}
	}
}

void StateFindClosestBall::Exit(AICharacter * agent)
{
	delete this;
}
