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

	Transform agentWorldTransform = agent->GetWorldTransform();

	for (GameObject* gameObject : gameObjects)
	{
		if (gameObject->GetPhysicsComponent())
		{
			distance = (agentWorldTransform.GetPosition() - gameObject->GetWorldTransform().GetPosition()).GetSqrMagnitude();
			if (distance < closestDistance)
			{
				closestDistance = distance;
				mClosestBall = gameObject;
			}
		}
	}

	Transform closestBallTransform = mClosestBall->GetWorldTransform();

	Level2Enemy* enemy = dynamic_cast<Level2Enemy*>(agent);

	if (enemy->HasBall())//the ball has been picked up
	{
		agent->ChangeState(new StateReturnToBaseline());
	}
	else
	{
		if (closestBallTransform.GetPosition().x > agentWorldTransform.GetPosition().x)
		{
			agent->MoveRight(deltaTime, 1.0);
		}
		else if (closestBallTransform.GetPosition().x < agentWorldTransform.GetPosition().x)
		{
			agent->MoveRight(deltaTime, -1.0f);
		}

		if (closestBallTransform.GetPosition().z < agentWorldTransform.GetPosition().z)
		{
			agent->MoveForward(deltaTime, 1.0);
		}
		else if (closestBallTransform.GetPosition().z > agentWorldTransform.GetPosition().z)
		{
			agent->MoveForward(deltaTime, -1.0);
		}
	}
}

void StateFindClosestBall::Exit(AICharacter * agent)
{
	delete this;
}
