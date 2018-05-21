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

class Camera : public SceneNode, public iInput
{
public:
	Camera();
	~Camera();
	void		Initialise(Vector3D eyePosition, Vector3D forward, Vector3D up, float fovY, float nearDepth, float farDepth);
	void		Update(Shader* shader);

	void MoveRight(float scale) override;
	void MoveForward(float scale) override;

	void Yaw(float scale)override;
	void Pitch(float scale)override;
	void Roll(float scale)override;
	void Interact();

	Matrix4x4 GetView() const { return mView; }
	Matrix4x4 GetProjection() const { return mProjection; }

private:
	Vector3D mForward;
	Vector3D mUp;
	Vector3D mRight;

	Matrix4x4 mProjection;
	Matrix4x4 mView;
};

#endif //_CAMERA_H


