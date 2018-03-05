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
#include "3DSLoader.h"
#include "Texture2D.h"
#include "Collision.h"
#include "TextRender.h"
#include "SoundEffects.h"
#include "Character.h"
#include "PlayerController.h"

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
//--------------------------------------------------------------------------------------------------
private:
	std::vector<GameObject*>mGameObjects;
	SceneNode* Root;
	Camera* mCamera;
	PlayerController* mPlayerController;

	float mTimer = 0.0f;
	char mTime[64] = { " " };

	//FPS
	int mInitialTime, mFinalTime, mFrameCount;
	char FPS[64] = {" "};

	TextRender* mText;
	
	SoundEffects* mVictorySound;
};


#endif //_GAMESCREENLEVEL1_H