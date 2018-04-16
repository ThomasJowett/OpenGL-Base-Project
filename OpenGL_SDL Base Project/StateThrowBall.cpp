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
	agent->Interact();
	agent->ChangeState(new StateFindClosestBall());
}

void StateThrowBall::Exit(AICharacter * agent)
{
	delete this;
}
