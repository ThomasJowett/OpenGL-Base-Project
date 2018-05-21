#include "GameScreen.h"

//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen()
{
	Root = new SceneNode();
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
	mGameObjects.clear();
	if (Root)  delete Root;
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, std::vector<SDL_Event> e)
{
	for (auto playerController : mPlayerControllers)
	{
		playerController->Update(deltaTime, e);
	}
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