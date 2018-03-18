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
		if (e.type == SDL_CONTROLLERAXISMOTION)
		{
			//Motion on controller
			if (e.caxis.which == mControllerID)
			{
				if (e.caxis.axis == 0) { mLeftStickAxis_X = (e.caxis.value) / 32767.0f; }
				else if (e.caxis.axis == 1) { mLeftStickAxis_Y = (e.caxis.value) / 32767.0f; }
				
				else if (e.caxis.axis == 2) { mRightStickAxis_X = (e.caxis.value) / 32767.0f; }
				else if (e.caxis.axis == 3){ mRightStickAxis_Y = (e.caxis.value) / 32767.0f; }
				else if (e.caxis.axis == 4)
				{
					//left trigger
					std::cout << "left trigger\n";
				}
				else if (e.caxis.axis == 5)
				{
					//right trigger
					std::cout << "right trigger\n";
				}
			}
			
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_r:
				//restart
				break;
			default:
				break;
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
