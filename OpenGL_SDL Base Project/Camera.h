#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include <SDL.h>
#include <math.h>
#include "SceneNode.h"

class Camera : public SceneNode
{
public:
	Camera();
	~Camera();
	static		Camera* GetInstance();
	void		Update(float deltaTime, SDL_Event e, Vertex3D target);
	void        Render();

private:
	Vertex3D mPosition = Vertex3D(1000, 0, 1000);
	Vector3D mForward = Vector3D();
	Vector3D mUp = Vector3D();
	Vector3D mRight = Vector3D();
	Vertex3D mLookatPos = Vertex3D(0, 0, 0);


	//horizontal angle : toward -z
	float mYaw = M_PI;
	//vertical angle : 0, look at the horizon
	float mPitch = 0.0f;
	bool mMouseButtonDown = false;
};

#endif //_CAMERA_H


