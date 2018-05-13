#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000000.0f);

	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glShadeModel(GL_SMOOTH);

	//glPolygonMode(GL_FRONT, GL_FILL);


	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ImageRender* image = new ImageRender("Images/Button_Hovered.PNG");
	//ImageRender* image = new ImageRender("Textures/Dodgeball_Diffuse.PNG");
	mImages.push_back(image);

	image = new ImageRender("Images/Button_Normal.PNG");
	mImages.push_back(image);

	image = new ImageRender("Images/DodgeballLogo.PNG");
	mImages.push_back(image);

	mInstructionsText = new TextRender("Fonts/Tabasco.ttf", 16);
	mMenuText = new TextRender("Fonts/Dimbo Regular.ttf", 50);

	mMenuItems.push_back("Level 1");
	mMenuItems.push_back("Level 2");
	mMenuItems.push_back("Test");
	mMenuItems.push_back("Quit");

	mInstructions.push_back("WASD or left stick to move");
	mInstructions.push_back("R to restart");
	mInstructions.push_back("Get to the far side of the court");
	mInstructions.push_back("You can only be hit by three balls or less");

	mHighlightLocation = { 1500, 325 };
	mCurrentButton = 1;
}

GameScreenMenu::~GameScreenMenu()
{
}

void GameScreenMenu::Render()
{
	glLoadIdentity();
	
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glDisable(GL_LIGHTING);

	mImages[1]->DrawImage(1500, 325, 400.0f, 100.0f);
	mImages[1]->DrawImage(1500, 225, 400.0f, 100.0f);
	mImages[1]->DrawImage(1500, 125, 400.0f, 100.0f);
	mImages[1]->DrawImage(1500, 25, 400.0f, 100.0f);
	mImages[1]->DrawImage(1500, 25, 400.0f, 100.0f);
	mImages[2]->DrawImage(20, 170, 1600.0f, 900.0f);
	mImages[0]->DrawImage(mHighlightLocation.x, mHighlightLocation.y, 400.0f, 100.0f);

	for (int i = 0; i <= mInstructions.size() -1; i++)
	{
		mInstructionsText->DisplayText(mInstructions[i].c_str(), SDL_Colour{ 40,10,125 }, 1500, 840 + (i * 20), RIGHT);
	}

	for (int i = 0; i <= mMenuItems.size() - 1; i++)
	{
		mMenuText->DisplayText(mMenuItems[i].c_str(), SDL_Colour{ 40, 10, 125 }, 1700, 350 - (i * 100), CENTER);
	}
}

void GameScreenMenu::Update(float deltaTime, std::vector<SDL_Event> events)
{
	HandleInput(events);
}

void GameScreenMenu::HandleInput(std::vector<SDL_Event> events)
{
	SDL_PumpEvents();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	for (SDL_Event e : events)
	{
		if (SDL_NumJoysticks() > 0)
		{
			if (e.type == SDL_CONTROLLERAXISMOTION)
			{
				if (e.jaxis.which == 0)
				{
					if (e.jaxis.axis == 1)
					{
						if (e.jaxis.value > 20000)
						{
							if (!mHasMovedDown)
							{
								MoveHighlightDown();
								mHasMovedDown = true;
							}
						}
						else
						{
							mHasMovedDown = false;
						}

						if (e.jaxis.value < -20000)
						{
							if (!mHasMovedUp)
							{
								MoveHighlightUp();
								mHasMovedUp = true;
							}
						}
						else
						{
							mHasMovedUp = false;
						}
					}
				}
			}

			else if (e.type == SDL_CONTROLLERBUTTONDOWN)
			{
				switch (e.cbutton.button)
				{
				case SDL_CONTROLLER_BUTTON_A:
					ChangeLevel();
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					MoveHighlightDown();
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					MoveHighlightUp();
					break;
				}
			}

			
		}
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				MoveHighlightUp();
				break;
			case SDLK_DOWN:
				MoveHighlightDown();
				break;
			case SDLK_RETURN:
				ChangeLevel();
				break;
			default:
				break;
			}
		}
	}
}

void GameScreenMenu::MoveHighlightDown()
{
	mHighlightLocation.y -= 100;
	mCurrentButton++;
	if (mCurrentButton > 4)
	{
		mCurrentButton = 1;
		mHighlightLocation = { 1500, 325 };
	}
}

void GameScreenMenu::MoveHighlightUp()
{
	mHighlightLocation.y += 100;
	mCurrentButton--;
	if (mCurrentButton < 1)
	{
		mCurrentButton = 4;
		mHighlightLocation = { 1500, 325-300 };
	}
}

void GameScreenMenu::ChangeLevel()
{
	switch (mCurrentButton)
	{
	case 1:
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL1);
		break;
	case 2:
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL2);
		break;
	case 3:
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_TEST);
		break;
	case 4:
		Quit();
		break;
	}
}

void GameScreenMenu::Quit()
{
	SDL_Event sdlEvent;
	sdlEvent.type = SDL_QUIT;
	SDL_PushEvent(&sdlEvent);
}
