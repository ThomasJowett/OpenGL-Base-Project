#include "PlayerController.h"

PlayerController::PlayerController(Character * character)
{
	PossessCharacter(character);
}

void PlayerController::Update(float deltaTime)
{
	if ((GetAsyncKeyState('A') & 0x80 != 0)) { mCharacter->MoveLeft(deltaTime); }
	if ((GetAsyncKeyState('D') & 0x80 != 0)) { mCharacter->MoveRight(deltaTime); }
	if ((GetAsyncKeyState('W') & 0x80 != 0)) { mCharacter->MoveForward(deltaTime); }
	if ((GetAsyncKeyState('S') & 0x80 != 0)) { mCharacter->MoveBackward(deltaTime); }
	if ((GetAsyncKeyState('Q') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('E') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('R') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('F') & 0x80 != 0)) { ; }
}

void PlayerController::PossessCharacter(Character* character)
{
	mCharacter = character;
}

void PlayerController::UnPossessCharacter()
{
	mCharacter = nullptr;
}
