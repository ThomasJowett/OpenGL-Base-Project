#pragma once

#include "Vector.h"
#include "Quaternion.h"

class Matrix4x4
{
public:
	float m[4][4];

	Matrix4x4();
	~Matrix4x4();

	static Matrix4x4 Translate(Vector3D translation);
	static Matrix4x4 Scale(Vector3D scale);
	static Matrix4x4 Rotate(Quaternion rotation);
	static Matrix4x4 Perspective(float fovY, float aspectRatio, float nearDepth, float farDepth);
	static Matrix4x4 LookAt(Vector3D eyePosition, Vector3D lookAtPosition, Vector3D up);


	Matrix4x4 operator*(Matrix4x4 other);
};

