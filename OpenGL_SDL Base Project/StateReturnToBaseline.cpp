#include "StateReturnToBaseline.h"



StateReturnToBaseline::StateReturnToBaseline()
{
}


StateReturnToBaseline::~StateReturnToBaseline()
{
}

void StateReturnToBaseline::During(AICharacter * agent, float deltaTime)
{
	if (agent->GetTransform()->GetPosition().z < -300.0f)
	{

	}

	//Attach ball to character
}

void StateReturnToBaseline::Enter(AICharacter * agent)
{
}

void StateReturnToBaseline::Exit(AICharacter * agent)
{
}