#include "Camera.h"
#include "Constants.h"
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 100.0f;
static float lookSpeed = 0.5f;

Camera::Camera(Vector3D target, float yaw, float pitch, float distance) : mLookatPos(target), mYaw(yaw), mPitch(pitch), mDistance(distance)
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime, Vector3D target)
{
	mLookatPos = target;
	//Detect Input
	
	/*
	if ((GetAsyncKeyState(VK_LSHIFT) & 0x80 != 0))
	{
		mMouseButtonDown = true;
	}
	else
	{
		mMouseButtonDown = false;
	}

	if (mMouseButtonDown)
	{
		if (e.type == SDL_MOUSEMOTION)
		{
			if (e.motion.xrel < 0)//Left
				mYaw -= lookSpeed * e.motion.xrel* -1;
			else if (e.motion.xrel > 0)//Right
				mYaw += lookSpeed * e.motion.xrel;
			if (e.motion.yrel < 0)//Up
				mPitch += lookSpeed * e.motion.yrel * -1;
			else if (e.motion.yrel > 0)//Down
				mPitch -= lookSpeed * e.motion.yrel;
		}
	}

	if (e.wheel.y == 1)
	{
		mDistance -= moveSpeed;
	}
	else if (e.wheel.y == -1)
	{
		mDistance += moveSpeed;
	}
	*/
	//Clamp Values
	if (mDistance < 50.0f)
		mDistance = 50.0f;
	if (mDistance > 50000.0f)
		mDistance = 50000.0f;
	if (mYaw > 360 || mYaw < -360)
		mYaw = 0;
	if (mPitch > 90)
		mPitch = 90;
	if (mPitch < -90)
		mPitch = -90;

	//Forward Vector: Spherical coordinates to Cartesian coordinates conversion (also known as the 'look' direction)
	/*
	mForward = Vector3D(
		cos(mPitch) * sin(mYaw),
		sin(mPitch),
		cos(mPitch) * cos(mYaw));
	mRight = Vector3D(sin(mYaw - M_PI / 2.0f), 0, cos(mYaw - M_PI / 2.0f));	
	*/
	
	//Reset Up vector
	mUp = { 0.0f, 1.0f, 0.0f };

	//Calculate the Camera Position
	mPosition.x = mLookatPos.x + mDistance * -sin(mYaw*(M_PI / 180)) * cos((mPitch)*(M_PI / 180));
	mPosition.y = mLookatPos.y + mDistance * -sin((mPitch)*(M_PI / 180));
	mPosition.z = mLookatPos.z + mDistance * cos((mYaw)*(M_PI / 180)) * cos((mPitch)*(M_PI / 180));

	//Get the forward vector from the camera position - look at position
	mForward = mLookatPos - mPosition;
	mForward.Normalize();

	//Get the orthonormal right vector
	mRight.Cross(mForward, mUp);
	mRight.Normalize();

	//Up vector : perpendicular to both forawrd and right, calculate using the cross product
	mUp.Cross(mRight, mForward);
	mUp.Normalize();
}


void Camera::Render()
{
	glLoadIdentity();
	gluLookAt(mPosition.x, mPosition.y, mPosition.z, mLookatPos.x, mLookatPos.y, mLookatPos.z, mUp.x, mUp.y, mUp.z);
}