#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"

static GameScreenManager* instance = 0;

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	instance = this;
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenMenu* tempMenuScreen;
	GameScreenLevel1* tempScreen1;

	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
		break;

		case SCREEN_MENU:
			std::cout << "Menu Loaded\n";
			tempMenuScreen = new GameScreenMenu();
			mCurrentScreen = (GameScreen*)tempMenuScreen;
			tempMenuScreen = NULL;
		break;

		case SCREEN_LEVEL1:
			std::cout << "Level 1 Loaded\n";
			tempScreen1 = new GameScreenLevel1();
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
		break;
		
		case SCREEN_GAMEOVER:
		break;
		
		case SCREEN_HIGHSCORES:
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------

GameScreenManager * GameScreenManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameScreenManager(SCREEN_MENU);
	}
	return instance;
}

//--------------------------------------------------------------------------------------------------