#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include "Constants.h"
#include "Vector.h"
#include <SDL.h>
#include <math.h>
#include "SceneNode.h"
#include "iInput.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "Matrix.h"

class Camera : public SceneNode, public iInput
{
public:
	Camera();
	~Camera();
	void		Initialise(Vector3D eyePosition, Vector3D forward, Vector3D up, float fovY, float nearDepth, float farDepth);
	void		Update();

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale)override;
	void Pitch(float deltaTime, float scale)override;
	void Roll(float deltaTime, float scale)override;
	void Interact();

	Matrix4x4 GetView() const { return mView; }
	Matrix4x4 GetProjection() const { return mProjection; }

	//glm::mat4 GetView() const { return mView; }
	//glm::mat4 GetProjection() const { return mProjection; }

private:
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mRight;
	Vector3D mLookAtPos;
	Vector3D mEyePos;

	Matrix4x4 mProjection;
	Matrix4x4 mView;

	//glm::mat4 mProjection;
	//glm::mat4 mView;

	//float mDistance;
	//horizontal angle : toward -z
	//float mYaw;
	//vertical angle : 0, look at the horizon
	//float mPitch;
};

#endif //_CAMERA_H


