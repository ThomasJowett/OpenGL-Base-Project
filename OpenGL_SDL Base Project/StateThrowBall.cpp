#include "StateThrowBall.h"



StateThrowBall::StateThrowBall()
{
}


StateThrowBall::~StateThrowBall()
{
}

void StateThrowBall::Enter(AICharacter * agent)
{
}

void StateThrowBall::During(AICharacter * agent, float deltaTime)
{
	GameObject* character = GameScreenManager::GetInstance()->GetCurrentScreen()->GetAllGameObjectsWithTag("Denzel")[0];
	if (character->GetTransform()->GetPosition().x > agent->GetTransform()->GetPosition().x+10.0f)
	{
		agent->MoveRight(1.0f);
	}
	else if (character->GetTransform()->GetPosition().x < agent->GetTransform()->GetPosition().x- 10.0f)
	{
		agent->MoveRight(-1.0f);
	}
	else
	{
		agent->Interact();
		agent->ChangeState(new StateFindClosestBall());
	}
}

void StateThrowBall::Exit(AICharacter * agent)
{
	delete this;
}
