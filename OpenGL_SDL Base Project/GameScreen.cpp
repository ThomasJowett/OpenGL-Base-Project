#include "GameScreen.h"

//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen()
{
	mGameObjects.clear();
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
	mGameObjects.clear();
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
	Root->Traverse();
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, std::vector<SDL_Event> e)
{
	for (auto gameObject : mGameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

//--------------------------------------------------------------------------------------------------
std::vector<GameObject*> GameScreen::GetAllGameObjectsWithTag(std::string tag) const
{
	std::vector<GameObject*> gameObjectsWithTag;

	for (GameObject* gameObject : mGameObjects)
	{
		if (gameObject->GetName() == tag)
			gameObjectsWithTag.push_back(gameObject);
	}

	return gameObjectsWithTag;
}
//--------------------------------------------------------------------------------------------------