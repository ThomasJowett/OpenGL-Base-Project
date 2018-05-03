#pragma once
#include "State.h"
#include "GameScreenManager.h"
#include "GameScreen.h"
#include "Level2Character.h"
#include "Level2Enemy.h"

class StateCelebrate :
	public State
{
public:
	StateCelebrate();
	~StateCelebrate();

	void Enter(AICharacter* agent)override;
	void During(AICharacter* agent, float deltaTime)override;
	void Exit(AICharacter* agent)override;
};

