#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"

#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include <SDL.h>
#include <string>

#include "Camera.h"
#include "Level1Character.h"


class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render() override;
	void		Update(float deltaTime, std::vector<SDL_Event> events) override;
	void		SetLight();
//--------------------------------------------------------------------------------------------------
private:
	Camera* mCamera;
	PlayerController* mPlayerController;

	float mTimer = 0.0f;
	char mTime[64] = { " " };

	//FPS
	int mInitialTime, mFinalTime, mFrameCount;
	char FPS[64] = { " " };

	char mBallsHit[64] = { " " };

	TextRender* mText;

	unsigned int mLives = 3;
	bool mWon = false;
};


#endif //_GAMESCREENLEVEL1_H