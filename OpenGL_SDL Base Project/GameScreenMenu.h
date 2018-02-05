#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include <SDL.h>
#include "GameScreen.h"
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include <time.h>
#include <string>

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu();
	~GameScreenMenu();

	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void		OutputLine(float x, float y, std::string text);
};
#endif _GAMESCREENMENU_H
