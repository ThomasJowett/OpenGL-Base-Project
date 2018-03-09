#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include "Vector.h"
#include <SDL.h>
#include <math.h>
#include "SceneNode.h"

class Camera : public SceneNode
{
public:
	Camera(Vector3D target, float yaw, float pitch, float distance);
	~Camera();
	void		Update(float deltaTime, Vector3D target);
	void        Render();

private:
	Vector3D mPosition;
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mRight;
	Vector3D mLookatPos;

	float mDistance = 1000.0f;
	//horizontal angle : toward -z
	float mYaw = M_PI;
	//vertical angle : 0, look at the horizon
	float mPitch = 0.0f;
	bool mMouseButtonDown = false;
};

#endif //_CAMERA_H


