#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Windows.h>
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"

class Transform
{
public:
	Transform();
	Transform(Vector3D position, Quaternion rotation, Vector3D scale);

	void SetPosition(float x, float y, float z) { mPosition = Vector3D{ x,y,z }; }
	void SetPosition(Vector3D position) { mPosition = position; }
	Vector3D GetPosition() const { return mPosition; }

	void SetRotation(Quaternion rotation) { mRotation = rotation; }
	Quaternion GetRotation() const { return mRotation; }

	void SetScale(float x, float y, float z) { mScale = Vector3D{ x,y,z }; }
	void SetScale(Vector3D scale) { mScale = scale; }
	Vector3D GetScale() const { return mScale; }

	Matrix4x4 GetWorldMatrix() const { return mWorldMatrix; }
	void UpdateWorldMatrix();

	Transform operator+=(const Transform other)
	{
		mPosition += other.GetPosition();
		mRotation += other.GetRotation();
		mRotation.Normalize();
		return *this;
	}

private:
	Vector3D mPosition;
	Quaternion mRotation;
	Vector3D mScale;

	Matrix4x4 mWorldMatrix;
};


#endif // !TRANSFORM_H


