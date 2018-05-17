#include "StateFindClosestBall.h"

StateFindClosestBall::StateFindClosestBall()
{
}


StateFindClosestBall::~StateFindClosestBall()
{
}

void StateFindClosestBall::Enter(AICharacter * agent)
{
	mClosestBall = nullptr;
}

void StateFindClosestBall::During(AICharacter* agent, float deltaTime)
{
	//find the closest game object with tag ball
	std::vector<GameObject*> gameObjects = GameScreenManager::GetInstance()->GetCurrentScreen()->GetAllGameObjectsWithTag("Ball");

	float closestDistance = FLT_MAX;
	float distance;

	mClosestBall = nullptr;

	Transform agentWorldTransform = agent->GetWorldTransform();
	if (gameObjects.size())
	{
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
		
		Level2Enemy* enemy = dynamic_cast<Level2Enemy*>(agent);

		if (enemy->HasBall())//the ball has been picked up
		{
			agent->ChangeState(new StateReturnToBaseline());
		}
		else
		{
			if (mClosestBall)
			{
				Transform closestBallTransform = mClosestBall->GetWorldTransform();

				if (closestBallTransform.GetPosition().x > agentWorldTransform.GetPosition().x)
				{
					agent->MoveRight(1.0);
				}
				else if (closestBallTransform.GetPosition().x < agentWorldTransform.GetPosition().x)
				{
					agent->MoveRight(-1.0f);
				}

				if (closestBallTransform.GetPosition().z < agentWorldTransform.GetPosition().z)
				{
					agent->MoveForward(1.0);
				}
				else if (closestBallTransform.GetPosition().z > agentWorldTransform.GetPosition().z)
				{
					agent->MoveForward(-1.0);
				}
			}
		}
		return;
	}

	agent->ChangeState(new StateCelebrate());

}

void StateFindClosestBall::Exit(AICharacter * agent)
{
	delete this;
}
