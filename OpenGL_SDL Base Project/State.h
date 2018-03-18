#ifndef _STATE_H
#define _STATE_H

#include "Character.h"

enum STATES
{
	STATE_NONE = 0,
	STAE_FIND_CLOSEST_BALL,
	STATE_PICKUP_BALL,
	STATE_RETURN_TO_BASELINE,
	STATE_THROW_BALL,
	STATE_DODGE
};

class State
{
public:
	State() { ; }
	~State() { ; }

	virtual void Enter() { ; }
	virtual void Exit() { ; }
	virtual void Update(Character* character, float deltaTime) { ; }
	virtual int GetState() { return STATE_NONE; }
	virtual int CheckTransition(Character* character) { return STATE_NONE; }

};
#endif // !_STATE_H

