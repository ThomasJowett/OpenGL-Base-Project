#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include <string>
#include "Pyramid.h"
#include "Object3DS.h"
#include "Camera.h"
#include "Transformation.h"

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
	void		SetMaterial();
	void		OutputLine(float x, float y, string text);

//--------------------------------------------------------------------------------------------------
private:
	float mCurrentTime;
	//Pyramid * pyramid;
	//float rotation;

	SceneNode* Root;
	Object3DS* m_p3DSModel;
	Object3DS* m_pOBJTracks;
	Object3DS* m_pOBJCabin;
	Object3DS* m_pOBJBoom;
	Object3DS* m_pOBJStick;
	Object3DS* m_pOBJBucket;
	Object3DS* m_pOBJGround;
	Object3DS* m_pOBJTreeTrunk;
	Object3DS* m_pOBJTreeLeaves;


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