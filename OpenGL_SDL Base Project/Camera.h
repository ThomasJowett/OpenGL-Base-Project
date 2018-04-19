#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include "Vector.h"
#include <SDL.h>
#include <math.h>
#include "SceneNode.h"
#include "iInput.h"

class Camera : public SceneNode , public iInput
{
public:
	Camera(float yaw, float pitch, float distance);
	~Camera();
	void		Update(float deltaTime, std::vector<SDL_Event> events);
	void        Render();

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale)override;
	void Pitch(float deltaTime, float scale)override;
	void Roll(float deltaTime, float scale)override;
	void Interact();

private:
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mRight;
	Vector3D mLookatPos;

	float mDistance;
	//horizontal angle : toward -z
	float mYaw;
	//vertical angle : 0, look at the horizon
	float mPitch;
	bool mMouseButtonDown = false;
};

#endif //_CAMERA_H


