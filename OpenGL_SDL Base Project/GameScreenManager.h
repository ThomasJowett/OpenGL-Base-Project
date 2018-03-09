#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	~GameScreenManager();
	void Render();
	void Update(float deltaTime, std::vector<SDL_Event> e);

	void ChangeScreen(SCREENS newScreen);

	static GameScreenManager * GetInstance();

private:
	GameScreenManager(SCREENS startScreen);
	
	GameScreen* mCurrentScreen;
};


#endif //_GAMESCREENMANAGER_H