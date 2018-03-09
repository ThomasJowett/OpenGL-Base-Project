#include "PlayerController.h"



PlayerController::PlayerController(Character * character, int controllerID): mControllerID(controllerID)
{
	PossessCharacter(character);
}

void PlayerController::Update(float deltaTime, std::vector<SDL_Event> events)
{
	SDL_PumpEvents();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	if (currentKeyStates[SDL_SCANCODE_A]) { mCharacter->MoveRight(deltaTime, -1.0f); }
	if (currentKeyStates[SDL_SCANCODE_D]) { mCharacter->MoveRight(deltaTime, 1.0f); }
	if (currentKeyStates[SDL_SCANCODE_W]) { mCharacter->MoveForward(deltaTime, 1.0f); }
	if (currentKeyStates[SDL_SCANCODE_S]) { mCharacter->MoveForward(deltaTime, -1.0f); }

	for (SDL_Event e : events)
	{
		if (e.type == SDL_JOYAXISMOTION)
		{
			//Motion on controller
			if (e.jaxis.which == mControllerID)
			{
				if (e.jaxis.axis == 0) { mLeftStickAxis_X = (e.jaxis.value) / 32767.0f; }
				else if (e.jaxis.axis == 1) { mLeftStickAxis_Y = (e.jaxis.value) / 32767.0f; }
				else if (e.jaxis.axis == 2)
				{
					//left trigger
					std::cout << "left trigger\n";
				}
				else if (e.jaxis.axis == 3) { mRightStickAxis_X = (e.jaxis.value) / 32767.0f; }
				else if (e.jaxis.axis == 4){ mRightStickAxis_Y = (e.jaxis.value) / 32767.0f; }
				else if (e.jaxis.axis == 5)
				{
					//right trigger
					std::cout << "right trigger\n";
				}
			}
			
		}
	}
	
	if ((mLeftStickAxis_X*mLeftStickAxis_X) + (mLeftStickAxis_Y*mLeftStickAxis_Y) > mJoystickDeadZone / 32767.0f)
	{
		mCharacter->MoveRight(deltaTime, mLeftStickAxis_X);
		mCharacter->MoveForward(deltaTime, -mLeftStickAxis_Y);
	}
}

void PlayerController::PossessCharacter(Character* character)
{
	mCharacter = character;
}

void PlayerController::UnPossessCharacter()
{
	mCharacter = nullptr;
}
