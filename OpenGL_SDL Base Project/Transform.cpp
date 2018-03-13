#include "Transform.h"

Transform::Transform()
{
	mPosition = Vector3D{ 0.0f, 0.0f, 0.0f };
	mRotation = Quaternion();
	mScale = Vector3D{ 1.0f, 1.0f, 1.0f };

	int i;

	OpNum = 0;
	for (i = 0; i < 10; i++)
		TransformOrder[i] = -1;
}

Transform::Transform(Vector3D position, Quaternion rotation, Vector3D scale) : mPosition(position), mRotation(rotation), mScale(scale)
{
	int i;

	OpNum = 0;
	for (i = 0; i < 10; i++)
		TransformOrder[i] = -1;
}

void Transform::UpdateWorldMatrix()
{
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glRotatef(mRotation.r, mRotation.i, mRotation.j, mRotation.k);
	glScalef(mScale.x, mScale.y, mScale.z);
}
