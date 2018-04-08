#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include "GameScreenManager.h"
#include "SoundManager.h"
#include "Constants.h"
#include "OBJLoader.h"
#include "Collision.h"
#include "TextRender.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Character.h"
#include "PlayerController.h"

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, std::vector<SDL_Event> e);
	std::vector<GameObject*> GetAllGameObjects()const { return mGameObjects; }
protected:
	SceneNode* Root;
	std::vector<GameObject*>mGameObjects;
};


#endif //_GAMESCREEN_H