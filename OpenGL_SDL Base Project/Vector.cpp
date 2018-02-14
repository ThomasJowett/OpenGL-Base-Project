#include "Vector.h"

Vector3D::Vector3D(float initialX, float initialY, float initialZ)
{
	x = initialX;
	y = initialY;
	z = initialZ;
}

Vector3D::Vector3D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

float Vector3D::GetMagnitude()
{
	return sqrtf(GetSqrMagnitude());
}

float Vector3D::GetSqrMagnitude()
{
	return ((x*x) + (y*y) + (z*z));
}

Vector3D Vector3D::GetNormalized()
{
	float magnitude = GetMagnitude();
	return Vector3D(x / magnitude, y / magnitude, z / magnitude);
}

void Vector3D::Normalize()
{
	x = GetNormalized().x;
	y = GetNormalized().y;
	z = GetNormalized().z;
}

Vector3D Vector3D::Cross(Vector3D v1, Vector3D v2)
{

	x = (v1.y*v2.z) - (v1.z*v2.y);
	y = -((v1.x*v2.z) - (v1.z*v2.x));
	z = (v1.x*v2.y) - (v1.y*v2.x);
	return *this;
}

float Vector3D::Dot(Vector3D v1, Vector3D v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vector3D Vector3D::Reflect(Vector3D v, Vector3D normal)
{
	normal.Normalize();
	return v - (normal * (2.0f * Dot(v, normal)));
}

Vector3D Vector3D::operator*(float scaler)
{
	return Vector3D(x * scaler, y * scaler, z * scaler);
}

Vector3D Vector3D::operator/(float scaler)
{
	return Vector3D();
}

Vector3D Vector3D::operator+(const Vector3D & other)
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D & other)
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator+=(const Vector3D & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3D Vector3D::operator-=(const Vector3D & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Vector3D::operator==(const Vector3D & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vector3D::operator!=(const Vector3D & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return false;
	else
		return true;
}

Vector3D Vector3D::operator=(const Vector3D & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

float sqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   

	return y;
}