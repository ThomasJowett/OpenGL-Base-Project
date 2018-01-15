#include "Camera.h"
#include "Constants.h"
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 100.0f;
static float lookSpeed = 0.5f;
static float distance = 1000.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}

	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e, Vertex3D target)
{
	mLookatPos = target;
	//Detect Input
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x80 != 0))
	{
		mMouseButtonDown = true;
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
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
		distance -= moveSpeed;
	}
	else if (e.wheel.y == -1)
	{
		distance += moveSpeed;
	}

	//Clamp Values
	if (distance < 50.0f)
		distance = 50.0f;
	if (distance > 50000.0f)
		distance = 50000.0f;
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
	mPosition.x = mLookatPos.x + distance * -sin(mYaw*(M_PI / 180)) * cos((mPitch)*(M_PI / 180));
	mPosition.y = mLookatPos.y + distance * -sin((mPitch)*(M_PI / 180));
	mPosition.z = mLookatPos.z + distance * cos((mYaw)*(M_PI / 180)) * cos((mPitch)*(M_PI / 180));

	//Get the forward vector from the camera position - look at position
	mForward = mForward.MakeVector(mPosition, mLookatPos);
	mForward = mForward.GetNormalised();

	//Get the orthonormal right vector
	mRight = mRight.Cross(mForward, mUp);
	mRight = mRight.GetNormalised();

	//Up vector : perpendicular to both forawrd and right, calculate using the cross product
	mUp = mUp.Cross(mRight, mForward);
	mUp = mUp.GetNormalised();
}

void Camera::Render()
{
	glLoadIdentity();
	gluLookAt(mPosition.x, mPosition.y, mPosition.z, mLookatPos.x, mLookatPos.y, mLookatPos.z, mUp.x, mUp.y, mUp.z);
}


