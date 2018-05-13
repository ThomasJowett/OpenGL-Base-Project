#include "Matrix.h"



Matrix4x4::Matrix4x4()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}


Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::Translate(Vector3D translation)
{
	Matrix4x4 mResult;
	mResult.m[0][3] = translation.x;
	mResult.m[1][3] = translation.y;
	mResult.m[2][3] = translation.z;
	mResult.m[0][0] = 1.0f;
	mResult.m[1][1] = 1.0f;
	mResult.m[2][2] = 1.0f;
	mResult.m[3][3] = 1.0f;
	return mResult;
}

Matrix4x4 Matrix4x4::Scale(Vector3D scale)
{
	Matrix4x4 mResult;
	mResult.m[0][0] = scale.x;
	mResult.m[1][1] = scale.y;
	mResult.m[2][2] = scale.z;
	mResult.m[3][3] = 1.0f;
	return mResult;
}

Matrix4x4 Matrix4x4::Rotate(Quaternion rotation)
{
	Matrix4x4 mResult;
	mResult.m[0][0] = 1 - 2 * rotation.j*rotation.j - 2 * rotation.k*rotation.k;
	mResult.m[0][1] = 2 * rotation.i*rotation.j - 2 * rotation.k*rotation.r;
	mResult.m[0][2] = 2 * rotation.i*rotation.k + 2 * rotation.j*rotation.r;
	mResult.m[0][3] = 0.0f;

	mResult.m[1][0] = 2 * rotation.i*rotation.j + 2 * rotation.r*rotation.k;
	mResult.m[1][1] = 1 - 2 * rotation.i*rotation.i - 2 * rotation.k*rotation.k;
	mResult.m[1][2] = 2 * rotation.j*rotation.k - 2 * rotation.r*rotation.i;
	mResult.m[1][3] = 0.0f;

	mResult.m[2][0] = 2 * rotation.i*rotation.k - 2 * rotation.r*rotation.j;
	mResult.m[2][1] = 2 * rotation.j*rotation.k + 2 * rotation.r*rotation.i;
	mResult.m[2][2] = 1 - 2 * rotation.i*rotation.i - 2 * rotation.j*rotation.j;
	mResult.m[2][3] = 0.0f;

	mResult.m[3][0] = 0.0f;
	mResult.m[3][1] = 0.0f;
	mResult.m[3][2] = 0.0f;
	mResult.m[3][3] = 1.0f;
	return mResult;
}

Matrix4x4 Matrix4x4::Perspective(float fovY, float aspectRatio, float nearDepth, float farDepth)
{
	float tanHalfFovY = (tan(fovY / 2));

	Matrix4x4 mResult;
	mResult.m[0][0] = 1 / (tanHalfFovY * aspectRatio);
	mResult.m[0][1] = 0.0f;
	mResult.m[0][2] = 0.0f;
	mResult.m[0][3] = 0.0f;

	mResult.m[1][0] = 0.0f;
	mResult.m[1][1] = 1 / tanHalfFovY;
	mResult.m[1][2] = 0.0f;
	mResult.m[1][3] = 0.0f;

	mResult.m[2][0] = 0.0f;
	mResult.m[2][1] = 0.0f;
	mResult.m[2][2] = farDepth / (nearDepth - farDepth);
	mResult.m[2][3] = -1.0f;

	mResult.m[3][0] = 0.0f;
	mResult.m[3][1] = 0.0f;
	mResult.m[3][2] = -(farDepth * nearDepth) / (farDepth - nearDepth);
	mResult.m[3][3] = 0.0f;
	return mResult;
}

Matrix4x4 Matrix4x4::LookAt(Vector3D eyePosition, Vector3D lookAtPosition, Vector3D up)
{
	Vector3D f = (lookAtPosition - eyePosition).GetNormalized();
	Vector3D s = (Vector3D::Cross(f, up)).GetNormalized();
	Vector3D u = Vector3D::Cross(s, f);
	
	Matrix4x4 mResult;
	
	mResult.m[0][0] = s.x;
	mResult.m[0][1] = u.x;
	mResult.m[0][2] = -f.x;
	mResult.m[0][3] = 0.0f;

	mResult.m[1][0] = s.y;
	mResult.m[1][1] = u.y;
	mResult.m[1][2] = -f.y;
	mResult.m[1][3] = 0.0f;

	mResult.m[2][0] = s.z;
	mResult.m[2][1] = u.z;
	mResult.m[2][2] = -f.z;
	mResult.m[2][3] = 0.0f;

	mResult.m[3][0] = -Vector3D::Dot(s, eyePosition);
	mResult.m[3][1] = -Vector3D::Dot(up, eyePosition);
	mResult.m[3][2] = Vector3D::Dot(f, eyePosition);
	mResult.m[3][3] = 1.0f;
	
	return mResult;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 other)
{
	Matrix4x4 mResult;
	// Cache the invariants in registers
	float x = m[0][0];
	float y = m[0][1];
	float z = m[0][2];
	float w = m[0][3];
	// Perform the operation on the first row
	mResult.m[0][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[0][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[0][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[0][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	// Repeat for all the other rows
	x = m[1][0];
	y = m[1][1];
	z = m[1][2];
	w = m[1][3];
	mResult.m[1][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[1][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[1][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[1][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	x = m[2][0];
	y = m[2][1];
	z = m[2][2];
	w = m[2][3];
	mResult.m[2][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[2][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[2][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[2][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	x = m[3][0];
	y = m[3][1];
	z = m[3][2];
	w = m[3][3];
	mResult.m[3][0] = (other.m[0][0] * x) + (other.m[1][0] * y) + (other.m[2][0] * z) + (other.m[3][0] * w);
	mResult.m[3][1] = (other.m[0][1] * x) + (other.m[1][1] * y) + (other.m[2][1] * z) + (other.m[3][1] * w);
	mResult.m[3][2] = (other.m[0][2] * x) + (other.m[1][2] * y) + (other.m[2][2] * z) + (other.m[3][2] * w);
	mResult.m[3][3] = (other.m[0][3] * x) + (other.m[1][3] * y) + (other.m[2][3] * z) + (other.m[3][3] * w);
	return mResult;
}
