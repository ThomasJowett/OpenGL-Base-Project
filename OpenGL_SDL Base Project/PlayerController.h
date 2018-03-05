#ifndef _PLAYERCONTROLLER_H
#define _PLAYERCONTROLLER_H

#include <Windows.h>
#include "Character.h"

class PlayerController 
{
public:
	PlayerController(Character* character);
	~PlayerController() {}
	void Update(float deltaTime);
	void PossessCharacter(Character* character);
	void UnPossessCharacter();
private:
	bool mIsMovingForward;
	bool mIsMovingBackward;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	Character* mCharacter;
};
#endif // !_PLAYERCONTROLLER_H