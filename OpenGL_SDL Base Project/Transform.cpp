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
	Matrix4x4 scale = Matrix4x4::Scale(mScale);
	Matrix4x4 rotation = Matrix4x4::Rotate(mRotation);
	Matrix4x4 translation = Matrix4x4::Translate(mPosition);

	mWorldMatrix = translation * rotation * scale;
}