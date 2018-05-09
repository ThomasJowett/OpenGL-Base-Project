#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include "Constants.h"
#include "Vector.h"
#include <SDL.h>
#include <math.h>
#include "SceneNode.h"
#include "iInput.h"
#include "Matrix.h"

class Camera : public SceneNode , public iInput
{
public:
	Camera(float yaw, float pitch, float distance);
	~Camera();
	void		Initialise(Vector3D eyePosition, Vector3D lookAtPosition, Vector3D up, float fovY, float farDepth, float nearDepth);
	void		Update();
	void        Render();

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale)override;
	void Pitch(float deltaTime, float scale)override;
	void Roll(float deltaTime, float scale)override;
	void Interact();

	Matrix4x4 GetView() const { return mView; }
	Matrix4x4 GetProjection() const { return mProjection; }

private:
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mRight;
	Vector3D mLookatPos;

	Matrix4x4 mProjection;
	Matrix4x4 mView;

	float mDistance;
	//horizontal angle : toward -z
	float mYaw;
	//vertical angle : 0, look at the horizon
	float mPitch;
	bool mMouseButtonDown = false;
};

#endif //_CAMERA_H


