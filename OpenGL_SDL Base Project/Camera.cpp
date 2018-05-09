#include "Camera.h"
#include "Constants.h"
#include "../gl/glut.h"

static float moveSpeed = 100.0f;
static float lookSpeed = 0.5f;

Camera::Camera(float yaw, float pitch, float distance) 
	: mYaw(yaw), mPitch(pitch), mDistance(distance)
{
	mForward = { 0.0f, 0.0f, 1.0f };
	mUp = { 0.0f, 1.0f, 0.0f };
	mRight.Cross(mForward, mUp);

	mLookatPos = mTransform->GetPosition() + mForward;
}

Camera::~Camera()
{
}

void Camera::Initialise(Vector3D eyePosition, Vector3D lookAtPosition, Vector3D up, float fovY, float farDepth, float nearDepth)
{
	mTransform->SetPosition(eyePosition);
	mProjection = Matrix4x4::Perspective(fovY, SCREEN_WIDTH / SCREEN_HEIGHT, nearDepth, farDepth);

}

void Camera::Update()
{
	if (pParent)
		mLookatPos = pParent->GetTransform()->GetPosition();

	//Detect Input
	SDL_PumpEvents();
/*
	for (SDL_Event e : events)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			mMouseButtonDown = true;
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			mMouseButtonDown = false;
		}

		if (mMouseButtonDown)
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				if (e.motion.xrel != 0)//Left
					Yaw(deltaTime, lookSpeed *e.motion.xrel);
				if (e.motion.yrel != 0)//Up
					Pitch(deltaTime, lookSpeed * e.motion.yrel * -1);
			}
		}
		/*
		if (e.wheel.y == 1)
		{
			mDistance -= moveSpeed;
		}
		else if (e.wheel.y == -1)
		{
			mDistance += moveSpeed;
		}
	}
	//Clamp Values
	if (mDistance < 50.0f)
		mDistance = 50.0f;
	if (mDistance > 50000.0f)
		mDistance = 50000.0f;
	*/
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
	mTransform->SetPosition(mLookatPos.x + mDistance * -sin(mYaw*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)),
		mLookatPos.y + mDistance * -sin((mPitch)*(M_PI / 180)),
		mLookatPos.z + mDistance * cos((mYaw)*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)));

	//Get the forward vector from the camera position - look at position
	mForward = mLookatPos - mTransform->GetPosition();
	mForward.Normalize();

	//Get the orthonormal right vector
	mRight.Cross(mForward, mUp);
	mRight.Normalize();

	//Up vector : perpendicular to both forawrd and right, calculate using the cross product
	mUp.Cross(mRight, mForward);
	mUp.Normalize();

	mView = Matrix4x4::LookAt(mTransform->GetPosition(), mLookatPos, mUp);
}

void Camera::Render()
{
	glLoadIdentity();
	gluLookAt(mTransform->GetPosition().x, mTransform->GetPosition().y, mTransform->GetPosition().z, mLookatPos.x, mLookatPos.y, mLookatPos.z, mUp.x, mUp.y, mUp.z);
}
void Camera::Interact()
{
}

void Camera::MoveRight(float deltaTime, float scale)
{
}

void Camera::MoveForward(float deltaTime, float scale)
{
}

void Camera::Yaw(float deltaTime, float scale)
{
	mYaw += scale;
	if (mYaw > 360 || mYaw < -360)
		mYaw = 0;
}

void Camera::Pitch(float deltaTime, float scale)
{
	mPitch += scale;
	if (mPitch > 89)
		mPitch = 89;
	if (mPitch < -89)
		mPitch = -89;
}

void Camera::Roll(float deltaTime, float scale)
{
}
