#include "Camera.h"
#include "Constants.h"


static float moveSpeed = 100.0f;
static float lookSpeed = 0.5f;

Camera::Camera() 
{
}

Camera::~Camera()
{
}

void Camera::Initialise(Vector3D eyePosition, Vector3D forward, Vector3D up, float fovY, float nearDepth, float farDepth)
{
	mTransform->SetPosition(eyePosition);
	mForward = forward;
	mUp = up;
	mRight = Vector3D::Cross(mForward, mUp);

	mProjection = Matrix4x4::Perspective((fovY), (float)SCREEN_WIDTH / SCREEN_HEIGHT, nearDepth, farDepth);
}

void Camera::Update()
{
	Vector3D mEyePos = GetWorldTransform().GetPosition();

	//mUp = { 0.0f, 1.0f, 0.0f };

	Vector3D mLookAtPos = mEyePos + mForward;

	/*
	//Calculate the Camera Position
	mTransform->SetPosition(mLookatPos.x + mDistance * -sin(mYaw*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)),
		mLookatPos.y + mDistance * -sin((mPitch)*(M_PI / 180)),
		mLookatPos.z + mDistance * cos((mYaw)*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)));
	*/

	mView = Matrix4x4::LookAt(mEyePos, mLookAtPos, mUp);
}

void Camera::Interact()
{
}

void Camera::MoveRight(float scale)
{
	mTransform->SetPosition(mTransform->GetPosition() + (mTransform->GetRotation() * mRight * scale));
}

void Camera::MoveForward(float scale)
{
	mTransform->SetPosition(mTransform->GetPosition() + (mTransform->GetRotation() * mForward * scale));
}

void Camera::Yaw(float scale)
{
}

void Camera::Pitch(float scale)
{
}

void Camera::Roll(float scale)
{
}
