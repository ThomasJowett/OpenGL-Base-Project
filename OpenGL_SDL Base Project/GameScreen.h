#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include "GameScreenManager.h"
#include "SoundManager.h"

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, std::vector<SDL_Event> e);
};


#endif //_GAMESCREEN_H