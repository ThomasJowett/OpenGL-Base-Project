#include "StateReturnToBaseline.h"



StateReturnToBaseline::StateReturnToBaseline()
{
}


StateReturnToBaseline::~StateReturnToBaseline()
{
}

void StateReturnToBaseline::During(AICharacter * agent, float deltaTime)
{
	if (agent->GetWorldTransform().GetPosition().z > 400.0f)
	{
		agent->ChangeState(new StateThrowBall());
	}
	else
	{
		agent->MoveForward(-1.0f);
	}
	//Attach ball to character
}

void StateReturnToBaseline::Enter(AICharacter * agent)
{
}

void StateReturnToBaseline::Exit(AICharacter * agent)
{
	delete this;
}