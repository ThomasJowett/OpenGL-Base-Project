#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "Transformation.h"
#include "Teapot.h"

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
	void		OutputLine(float x, float y, string text);

//--------------------------------------------------------------------------------------------------
private:
	std::vector<Teapot*>mTeapots;
	SceneNode* Root;
	GameObject* m_p3DSModel;
	GameObject* m_pOBJTracks;
	GameObject* m_pOBJCabin;
	GameObject* m_pOBJBoom;
	GameObject* m_pOBJStick;
	GameObject* m_pOBJBucket;
	GameObject* m_pOBJGround;
	GameObject* m_pOBJTreeTrunk;
	GameObject* m_pOBJTreeLeaves;


	Transformation * m_pTracksTrans;
	Transformation * m_pCabinTrans;
	Transformation * m_pBoomTrans;
	Transformation * m_pStickTrans;
	Transformation * m_pBucketTrans;
	Transformation * m_pTreeTrans;
	Transformation * m_pTreeLeavesTrans;

	float mCabinRotation, mBoomRotation, mStickRotation, mBucketRotation, mMoveSpeed = 1.0f;

	int mInitialTime, mFinalTime, mFrameCount;
	std::string FPS;
};


#endif //_GAMESCREENLEVEL1_H