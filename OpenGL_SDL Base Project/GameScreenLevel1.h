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
#include "GameObject.h"
#include "Camera.h"
#include "Constants.h"
#include "OBJLoader.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void		SetLight();
	void		SetMaterial(Material material);
	void		OutputLine(float x, float y, std::string text);

//--------------------------------------------------------------------------------------------------
private:
	std::vector<GameObject*>mGameObjects;
	SceneNode* Root;

	//FPS
	int mInitialTime, mFinalTime, mFrameCount;
	std::string FPS;
};


#endif //_GAMESCREENLEVEL1_H