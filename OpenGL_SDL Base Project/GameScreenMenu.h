#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include <SDL.h>
#include <vector>
#include "GameScreen.h"
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include <time.h>
#include <string>
#include "TextRender.h"
#include "ImageRender.h"

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu();
	~GameScreenMenu();

	void		Render() override;
	void		Update(float deltaTime, std::vector<SDL_Event> events) override;
private:
	TextRender* mInstructionsText;
	TextRender* mMenuText;
	void MoveHighlightDown();
	void MoveHighlightUp();
	void ChangeLevel();
	void Quit();

	bool mHasMovedDown;
	bool mHasMovedUp;

	Vector2D mHighlightLocation;
	int mCurrentButton;
protected:
	void HandleInput(std::vector<SDL_Event > events);
	std::vector<std::string> mMenuItems;
	std::vector<std::string> mInstructions;
	std::vector<ImageRender*>mImages;
};
#endif _GAMESCREENMENU_H
