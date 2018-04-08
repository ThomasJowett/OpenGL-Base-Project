#include "Transform.h"

Transform::Transform()
{
	mPosition = Vector3D{ 0.0f, 0.0f, 0.0f };
	mRotation = Quaternion();
	mScale = Vector3D{ 1.0f, 1.0f, 1.0f };
}

Transform::Transform(Vector3D position, Quaternion rotation, Vector3D scale) : mPosition(position), mRotation(rotation), mScale(scale)
{
}

void Transform::UpdateWorldMatrix()
{
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	float angle;
	Vector3D axis;
	Quaternion::CreateAxisAngleRotationMatrix(mRotation, angle, axis);
	glRotatef(angle,axis.x,axis.y, axis.z);
	glScalef(mScale.x, mScale.y, mScale.z);
}