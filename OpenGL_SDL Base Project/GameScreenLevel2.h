#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H
#include "GameScreen.h"
#include "Camera.h"
#include <time.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include <SDL.h>
#include "Constants.h"
#include "Level2Character.h"

class GameScreenLevel2 : public GameScreen
{
public:
	GameScreenLevel2();
	~GameScreenLevel2();

	void SetLight();
	void Render()override;
	void Update(float deltaTime, std::vector<SDL_Event> events)override;

private:
	std::vector<GameObject*>mGameObjects;
	SceneNode* Root;
	Camera* mCamera;
	std::vector<PlayerController*>mPlayerControllers;
};

#endif //_GAMESCREENLEVEL2_H