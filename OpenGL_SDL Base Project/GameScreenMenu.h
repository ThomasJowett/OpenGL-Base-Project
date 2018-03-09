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
#include "Texture2D.h"
#include "TextRender.h"

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu();
	~GameScreenMenu();

	void		Render() override;
	void		Update(float deltaTime, std::vector<SDL_Event> e) override;
	void		DrawTextured2DSquare();
private:
	GLuint splashscreenTextureID;
	TextRender* mControlsText;
};
#endif _GAMESCREENMENU_H
