#include "Camera.h"
#include "Constants.h"
#include "../gl/glut.h"


static float moveSpeed = 100.0f;
static float lookSpeed = 0.5f;

Camera::Camera() 
{
	//mForward = { 0.0f, 0.0f, 1.0f };
	//mUp = { 0.0f, 1.0f, 0.0f };
	//mRight.Cross(mForward, mUp);
	//mEyePos = Vector3D();

	//mLookatPos = mEyePos + mForward;
}

Camera::~Camera()
{
}

void Camera::Initialise(Vector3D eyePosition, Vector3D forward, Vector3D up, float fovY, float nearDepth, float farDepth)
{
	mEyePos = eyePosition;
	//mTransform->SetPosition(eyePosition);
	mForward = forward;
	mUp = up;
	mRight = Vector3D::Cross(mForward, mUp);
	//mLookAtPos = mEyePos + mForward;

	mProjection = glm::perspective(fovY, (float)SCREEN_WIDTH / SCREEN_HEIGHT, nearDepth, farDepth);

	//mProjection = Matrix4x4::Perspective((fovY * (M_PI/180)), SCREEN_WIDTH / SCREEN_HEIGHT, nearDepth, farDepth);
	//mProjection = Matrix4x4::Perspective((fovY), SCREEN_WIDTH / SCREEN_HEIGHT, nearDepth, farDepth);
}

void Camera::Update()
{
	//mEyePos = GetWorldTransform().GetPosition();

	//mUp = { 0.0f, 1.0f, 0.0f };

	mLookAtPos = mEyePos + mForward;

	//std::cout << mLookAtPos.x << " " << mLookAtPos.y << " " << mLookAtPos.z << std::endl;

	//std::cout << mEyePos.x << " " << mEyePos.y << " " << mEyePos.z << std::endl;

	/*
	//Calculate the Camera Position
	mTransform->SetPosition(mLookatPos.x + mDistance * -sin(mYaw*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)),
		mLookatPos.y + mDistance * -sin((mPitch)*(M_PI / 180)),
		mLookatPos.z + mDistance * cos((mYaw)*(M_PI / 180)) * cos((mPitch)*(M_PI / 180)));
	*/
	glm::vec3 eye = { mEyePos.x , mEyePos.y, mEyePos.z };
	glm::vec3 at = { mLookAtPos.x, mLookAtPos.y, mLookAtPos.z };
	glm::vec3 up = { mUp.x, mUp.y, mUp.z };
	mView = glm::lookAt(eye, at, up);

	//mView = Matrix4x4::LookAt(mEyePos, mLookAtPos, mUp);
}

void Camera::Interact()
{
}

glm::mat4 Camera::GetViewProjection() const
{
	glm::vec3 eye = { mEyePos.x , mEyePos.y, mEyePos.z };
	glm::vec3 forward = { mForward.x, mForward.y, mForward.z };
	glm::vec3 up = { mUp.x, mUp.y, mUp.z };

	return mProjection * glm::lookAt(eye, eye + forward, up);
}

void Camera::MoveRight(float deltaTime, float scale)
{
	mEyePos += mRight * scale;
}

void Camera::MoveForward(float deltaTime, float scale)
{
	mEyePos += mForward * scale;
}

void Camera::Yaw(float deltaTime, float scale)
{
}

void Camera::Pitch(float deltaTime, float scale)
{
}

void Camera::Roll(float deltaTime, float scale)
{
}
