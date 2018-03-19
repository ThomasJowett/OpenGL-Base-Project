#ifndef _PLAYERCONTROLLER_H
#define _PLAYERCONTROLLER_H

#include "Character.h"
#include "SDL.h"

class PlayerController 
{
public:
	PlayerController(Character* character, int controllerID);
	~PlayerController() { UnPossessCharacter(); }
	void Update(float deltaTime, std::vector<SDL_Event> e);
	void PossessCharacter(Character* character);
	void UnPossessCharacter();
private:
	Character* mCharacter;
	int mControllerID;

	const int mJoystickDeadZone = 2000;

	float mLeftStickAxis_X = 0.0f;
	float mLeftStickAxis_Y = 0.0f;

	float mRightStickAxis_X = 0.0f;
	float mRightStickAxis_Y = 0.0f;
};
#endif // !_PLAYERCONTROLLER_H