#include "StateCelebrate.h"



StateCelebrate::StateCelebrate()
{
}


StateCelebrate::~StateCelebrate()
{
}

void StateCelebrate::Enter(AICharacter * agent)
{
}

void StateCelebrate::During(AICharacter * agent, float deltaTime)
{
	Level2Character* Denzel = (Level2Character*)GameScreenManager::GetInstance()->GetCurrentScreen()->GetAllGameObjectsWithTag("Denzel").at(0);
	Level2Enemy* Enemy = (Level2Enemy*)agent;

	if (Denzel->GetTimesHit() > Enemy->GetTimesHit())
	{
		Quaternion rotation = agent->GetTransform()->GetRotation();

		rotation.AddScaledVector({ 0.0f,  1.0f, 0.0f }, deltaTime * 2);
		rotation.Normalize();
		agent->GetTransform()->SetRotation(rotation);

		agent->MoveForward(1.0f);
	}
}

void StateCelebrate::Exit(AICharacter * agent)
{
	delete this;
}
