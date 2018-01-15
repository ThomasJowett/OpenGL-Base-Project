#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:

};


#endif //_GAMESCREEN_H