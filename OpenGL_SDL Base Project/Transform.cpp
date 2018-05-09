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
	Quaternion::CreateAxisAngleRotation(mRotation, angle, axis);
	glRotatef(angle,axis.x,axis.y, axis.z);
	glScalef(mScale.x, mScale.y, mScale.z);

	Matrix4x4 scale = Matrix4x4::Scale(mScale);
	Matrix4x4 rotation = Matrix4x4::Rotate(mRotation);
	Matrix4x4 translation = Matrix4x4::Translate(mPosition);

	mWorldMatrix = scale * rotation * translation;
}